#!/bin/sh
#
# ltmain.sh: generalized library-building support script for EteleOS.
# Part of the EteleOS build tools. No external license — written for
# EteleOS. Appended to the output of ltconfig to form the "libtool"
# script used by Makefiles (xenocara, userland, etc).
#
# Supports only what EteleOS needs: Clang + lld + ELF shared/static
# libraries on amd64, arm64, riscv64. No AIX/HP-UX/IRIX/SCO/Windows
# branches, no dlopen self-tests, no multi-OS versioning schemes.

progname=$(basename "$0")
modename="$progname"
rm="rm -f"
mv="mv -f"
mkdir="mkdir -p"

show=echo
run=
mode=

usage() {
	cat <<EOF
Usage: $progname [OPTION]... --mode=MODE MODE-ARGS...

MODE must be one of: compile, link, install, uninstall, execute, finish
EOF
}

# ---- Parse global options up to the mode-specific arguments ----
while [ $# -gt 0 ]; do
	case "$1" in
	--mode=*) mode="${1#--mode=}"; shift ;;
	--mode) mode="$2"; shift 2 ;;
	--dry-run|-n) run=:; shift ;;
	--quiet|--silent) show=:; shift ;;
	--help) usage; exit 0 ;;
	--version) echo "$progname (EteleOS libtool)"; exit 0 ;;
	--config)
		sed -e '1,/^### BEGIN LIBTOOL CONFIG/d' -e '/^### END LIBTOOL CONFIG/,$d' "$0"
		exit 0
		;;
	*) break ;;
	esac
done

if [ -z "$mode" ]; then
	# Infer mode the same way real libtool does, for compatibility
	# with Makefiles that don't pass --mode explicitly.
	case "$1" in
	*cc|*++|clang*) mode=link
		for a; do [ "$a" = -c ] && { mode=compile; break; }; done ;;
	*install*|cp|mv) mode=install ;;
	*rm) mode=uninstall ;;
	esac
fi

# ---- helper: strip directory, get basename without known suffix ----
strip_suffix() { echo "$1" | sed -e 's/\.[^.]*$//'; }
basename_of() { echo "$1" | sed -e 's%^.*/%%'; }
dirname_of() { local d; d=$(echo "$1" | sed -e 's%/[^/]*$%%'); [ "$d" = "$1" ] && d="."; echo "$d"; }

case "$mode" in

# ================= COMPILE =================
compile)
	modename="$modename: compile"
	base_compile=
	srcfile=
	libobj=
	static_only=no

	for arg; do
		case "$arg" in
		-o) prev_o=yes; continue ;;
		-static) static_only=yes; continue ;;
		esac
		if [ "$prev_o" = yes ]; then libobj="$arg"; prev_o=; continue; fi
		srcfile="$arg"
		base_compile="$base_compile $arg"
	done

	[ -z "$srcfile" ] && { echo "$modename: no source file given" >&2; exit 1; }
	[ -z "$libobj" ] && libobj=$(basename_of "$(strip_suffix "$srcfile").lo")

	obj=$(echo "$libobj" | sed -e "s/\.lo\$/.${objext}/")
	dir=$(dirname_of "$libobj")
	objdir_path="$dir/$objdir"
	$run $mkdir "$objdir_path"

	# PIC object (for the shared library), then plain object (for .a),
	# unless the caller asked for -static only.
	if [ "$build_libtool_libs" != no ] && [ "$static_only" != yes ]; then
		pic_obj="$objdir_path/$(basename_of "$obj")"
		cmd="$CC $base_compile $pic_flag -DPIC -o $pic_obj"
		$show "$cmd"; $run eval "$cmd" || exit 1
		$run cp "$pic_obj" "$dir/$libobj" 2>/dev/null || $run mv "$pic_obj" "$dir/$libobj"
	fi
	if [ "$build_old_libs" != no ]; then
		cmd="$CC $base_compile -o $obj"
		$show "$cmd"; $run eval "$cmd" || exit 1
	fi
	exit 0
	;;

# ================= LINK =================
link)
	modename="$modename: link"
	objs= libobjs= deplibs= linkopts= output= rpath_dirs=
	is_lib=no version_info=

	while [ $# -gt 0 ]; do
		arg="$1"; shift
		case "$arg" in
		-o) output="$1"; shift ;;
		-rpath) rpath_dirs="$rpath_dirs $1"; shift ;;
		-version-info) version_info="$1"; shift ;;
		-L*) linkopts="$linkopts $arg"; deplibs="$deplibs $arg" ;;
		-l*) deplibs="$deplibs $arg" ;;
		-static|-all-static|-module|-export-dynamic|-no-undefined) ;;
		*.lo) libobjs="$libobjs $arg" ;;
		*.o|*.obj) objs="$objs $arg" ;;
		*.la)
			# Pull in the real archive/shared lib this points to.
			deplibs="$deplibs $arg"
			;;
		*) linkopts="$linkopts $arg" ;;
		esac
	done

	[ -z "$output" ] && { echo "$modename: -o output file required" >&2; exit 1; }
	outname=$(basename_of "$output")
	outdir=$(dirname_of "$output")

	case "$outname" in
	lib*.la)
		name=$(echo "$outname" | sed -e 's/^lib//' -e 's/\.la$//')
		release= versuffix=
		if [ -n "$version_info" ]; then
			current=$(echo "$version_info" | cut -d: -f1)
			versuffix=".${current:-0}"
		fi
		objdir_path="$outdir/$objdir"
		$run $mkdir "$objdir_path"

		realname="lib${name}${versuffix}.so"
		soname="$realname"
		lib="$objdir_path/$realname"

		# Object files that went into the .lo compile step.
		shared_objs=$(echo "$libobjs" | sed -e "s/\.lo/.${objext}/g")

		if [ "$build_libtool_libs" != no ]; then
			cmd="$CC -shared $shared_objs $deplibs $linkopts -Wl,-soname,$soname -o $lib"
			$show "$cmd"; $run eval "$cmd" || exit 1
			$run ln -sf "$realname" "$objdir_path/lib${name}.so"
		fi

		if [ "$build_old_libs" != no ]; then
			plain_objs=$(echo "$libobjs" | sed -e "s/\.lo/.${objext}/g")
			oldlib="$objdir_path/lib${name}.a"
			cmd="$AR cru $oldlib $plain_objs $objs"
			$show "$cmd"; $run eval "$cmd" || exit 1
			$run $RANLIB "$oldlib"
		fi

		# .la metadata file, so `install` mode and dependents can find things.
		$run $rm "$output"
		cat > "$output" <<-EOF
			# $outname - EteleOS libtool library file
			dlname='$realname'
			library_names='$realname lib${name}.so'
			old_library='lib${name}.a'
			dependency_libs='$deplibs'
			libdir='${rpath_dirs:-/usr/local/lib}'
		EOF
		exit 0
		;;
	*.a|*.lib)
		objdir_path="$outdir/$objdir"
		plain_objs=$(echo "$libobjs" | sed -e "s/\.lo/.${objext}/g")
		cmd="$AR cru $output $objs $plain_objs"
		$show "$cmd"; $run eval "$cmd" || exit 1
		$run $RANLIB "$output"
		exit 0
		;;
	*)
		# Building a program.
		plain_objs=$(echo "$libobjs" | sed -e "s/\.lo/.${objext}/g")
		rpath_flags=
		for d in $rpath_dirs; do rpath_flags="$rpath_flags -Wl,-rpath,$d"; done
		cmd="$CC $objs $plain_objs $deplibs $linkopts $rpath_flags -o $output"
		$show "$cmd"; $run eval "$cmd" || exit 1
		exit 0
		;;
	esac
	;;

# ================= INSTALL =================
install)
	modename="$modename: install"
	install_prog="$1"; shift
	files=
	for arg; do
		case "$arg" in
		-*) install_prog="$install_prog $arg" ;;
		*) files="$files $arg" ;;
		esac
	done
	set -- $files
	dest="${!#}"          # last argument is the destination
	[ -d "$dest" ] || { echo "$modename: '$dest' is not a directory" >&2; exit 1; }

	for file; do
		[ "$file" = "$dest" ] && continue
		case "$file" in
		*.la)
			# Install the real shared lib + static lib named in the .la.
			. "$file"
			dir=$(dirname_of "$file")/$objdir
			for n in $library_names; do
				$show "$install_prog $dir/$n $dest/$n"
				$run $install_prog "$dir/$n" "$dest/$n"
			done
			[ -n "$old_library" ] && {
				$show "$install_prog $dir/$old_library $dest/$old_library"
				$run $install_prog "$dir/$old_library" "$dest/$old_library"
			}
			;;
		*)
			$show "$install_prog $file $dest"
			$run $install_prog "$file" "$dest"
			;;
		esac
	done
	exit 0
	;;

# ================= UNINSTALL =================
uninstall)
	modename="$modename: uninstall"
	rmprog="$1"; shift
	for file; do
		case "$file" in
		*.la)
			dir=$(dirname_of "$file")
			. "$file"
			for n in $library_names; do $run $rmprog "$dir/$n"; done
			[ -n "$old_library" ] && $run $rmprog "$dir/$old_library"
			$run $rmprog "$file"
			;;
		*) $run $rmprog "$file" ;;
		esac
	done
	exit 0
	;;

# ================= EXECUTE =================
execute)
	modename="$modename: execute"
	cmd="$1"; shift
	exec "$cmd" "$@"
	;;

# ================= FINISH =================
finish)
	echo "Libraries installed. Run ldconfig if needed."
	exit 0
	;;

*)
	echo "$modename: unknown or missing --mode ('$mode')" >&2
	usage >&2
	exit 1
	;;
esac
