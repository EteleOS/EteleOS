#!/usr/bin/perl
# EteleOS: installer/miniroot/list2sh.pl, time wirte: 2026/08/26
# This file uses the Apache-2.0 license
#
# Converted from the original AWK implementation.
# Original header preserved below for provenance:
#
#	$OpenBSD: list2sh.awk,v 1.23 2021/02/13 18:46:52 semarie Exp $

use strict;
use warnings;

print "cd \${OBJDIR}\n";
print "\n";

my $nr = 0;
while (my $line = <>) {
	$nr++;
	chomp $line;
	my $F0 = $line;

	if ($F0 eq '' || $F0 =~ /^#/) {
		print "$F0\n";
		next;
	}

	# awk default field splitting: split on runs of whitespace,
	# ignoring leading/trailing whitespace.
	my @F = split(' ', $F0);
	my $NF = scalar(@F);
	my $F1 = defined($F[0]) ? $F[0] : '';

	if ($F1 eq 'COPY') {
		printf("echo '%s'\n", $F0);
		printf("test -f \${TARGDIR}/%s && rm -fr \${TARGDIR}/%s\n", $F[2], $F[2]);
		printf("cp %s \${TARGDIR}/%s\n", $F[1], $F[2]);
		next;
	}
	if ($F1 eq 'REMOVE') {
		printf("echo '%s'\n", $F0);
		printf("rm -f \${TARGDIR}/%s\n", $F[1]);
		next;
	}
	if ($F1 eq 'MKDIR') {
		printf("echo '%s'\n", $F0);
		printf("mkdir -p \${TARGDIR}/%s\n", $F[1]);
		next;
	}
	if ($F1 eq 'STRIP') {
		printf("echo '%s'\n", $F0);
		printf("test -f \${TARGDIR}/%s && rm -fr \${TARGDIR}/%s\n", $F[2], $F[2]);
		printf("objcopy -S %s \${TARGDIR}/%s\n", $F[1], $F[2]);
		next;
	}
	if ($F1 eq 'LINK') {
		printf("echo '%s'\n", $F0);
		for (my $i = 3; $i <= $NF; $i++) {
			my $fi = $F[$i - 1];
			printf("test -f \${TARGDIR}/%s && rm -f \${TARGDIR}/%s\n", $fi, $fi);
			printf("(cd \${TARGDIR}; ln %s %s)\n", $F[1], $fi);
		}
		next;
	}
	if ($F1 eq 'SYMLINK') {
		printf("echo '%s'\n", $F0);
		for (my $i = 3; $i <= $NF; $i++) {
			my $fi = $F[$i - 1];
			printf("test -f \${TARGDIR}/%s && rm -f \${TARGDIR}/%s\n", $fi, $fi);
			printf("(cd \${TARGDIR}; ln -s %s %s)\n", $F[1], $fi);
		}
		next;
	}
	if ($F1 eq 'ARGVLINK') {
		# crunchgen directive; ignored here
		next;
	}
	if ($F1 eq 'SRCDIRS') {
		# crunchgen directive; ignored here
		next;
	}
	if ($F1 eq 'LIBS') {
		# crunchgen directive; ignored here
		next;
	}
	if ($F1 eq 'CRUNCHSPECIAL') {
		# crunchgen directive; ignored here
		next;
	}
	if ($F1 eq 'TZ') {
		printf("echo '%s'\n", $F0);
		printf("(cd \${TARGDIR}; sh \$UTILS/maketz.sh \$DESTDIR)\n");
		next;
	}
	if ($F1 eq 'COPYDIR') {
		printf("echo '%s'\n", $F0);
		printf("(cd \${TARGDIR}/%s && find . ! -name . | xargs /bin/rm -rf)\n",
		    $F[2]);
		printf("(cd %s && pax -pe -rw . \${TARGDIR}/%s)\n", $F[1], $F[2]);
		next;
	}
	if ($F1 eq 'SPECIAL') {
		# escaping shell quotation is ugly whether you use " or ', use cat <<'!' ...
		my $work = $F0;
		$work =~ s/[\\]/\\\\/g;
		$work =~ s/["]/\\"/g;
		$work =~ s/[\$]/\\\$/g;
		$work =~ s/[`]/\\`/g;
		printf("echo \"%s\"\n", $work);
		$work = $F0;
		$work =~ s/^[ \t]*\Q$F1\E[ \t]*//;
		printf("(cd \${TARGDIR}; %s)\n", $work);
		next;
	}
	if ($F1 eq 'TERMCAP') {
		# tic -r flag may generate harmless warning about pccon+base:
		#     "terminal 'pccon+base': enter_reverse_mode but no exit_attribute_mode"
		printf("echo '%s'\n", $F0);
		printf("(cd \${TARGDIR}; tic -C -x -r -e %s \${UTILS}/../../share/termtypes/termtypes.master | sed -e '/^#.*/d' -e '/^\$\$/d' > %s)\n",
		    $F[1], $F[2]);
		next;
	}
	if ($F1 eq 'SCRIPT') {
		printf("echo '%s'\n", $F0);
		printf("sed -e '/^[ \t]*#[ \t].*\$/d' -e '/^[ \t]*#\$/d' < %s > \${TARGDIR}/%s\n",
		    $F[1], $F[2]);
		next;
	}

	printf("echo '%s'\n", $F0);
	printf("echo 'Unknown keyword \"%s\" at line %d of input.'\n", $F1, $nr);
	printf("exit 1\n");
	exit 1;
}

print "\n";
print "exit 0\n";
exit 0;
