#!/bin/sh
# Verify that committed RPC C/header files match the pinned rpcgen output.
# This is intentionally a maintainer/CI check, not part of the normal build.
set -eu

ROOT=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
RPCGEN=${RPCGEN:-rpcgen}
RPCGEN_VERSION='rpcgen (rpcsvc-proto) 1.4.2'

if ! actual_version=$($RPCGEN --version 2>&1); then
	echo "error: cannot run $RPCGEN --version" >&2
	exit 1
fi
if [ "$actual_version" != "$RPCGEN_VERSION" ]; then
	echo "error: expected $RPCGEN_VERSION; got: $actual_version" >&2
	exit 1
fi

workdir=$(mktemp -d "${TMPDIR:-/tmp}/peteleos-rpcgen.XXXXXX")
trap 'rm -rf "$workdir"' EXIT HUP INT TERM
libdir="$ROOT/libraries/extra/librpcsvc"
failed=0

generate() {
	output=$1
	shift
	mkdir -p "$(dirname "$workdir/$output")"
	(
		cd "$libdir"
		"$RPCGEN" "$@" -o "$workdir/$output"
	)
}

compare() {
	generated=$1
	committed=$2
	if ! cmp -s "$workdir/$generated" "$ROOT/$committed"; then
		echo "error: stale generated file: $committed" >&2
		diff -u "$ROOT/$committed" "$workdir/$generated" || true
		failed=1
	fi
}

for spec in bootparam_prot klm_prot mount nfs_prot nlm_prot rnusers rusers \
	rquota rstat rwall sm_inter spray yp yppasswd; do
	generate "librpcsvc/$spec.c" -C -c "$spec.x"
	generate "librpcsvc/$spec.h" -C -h "$spec.x"
	compare "librpcsvc/$spec.c" "libraries/extra/librpcsvc/$spec.c"
	compare "librpcsvc/$spec.h" "libraries/extra/librpcsvc/$spec.h"
done

generate 'rpc.statd/sm_inter_svc.c' -L -C -m sm_inter.x
generate 'rpc.statd/sm_inter.h' -L -C -h sm_inter.x
compare 'rpc.statd/sm_inter_svc.c' 'userland/system/rpc.statd/sm_inter_svc.c'
compare 'rpc.statd/sm_inter.h' 'userland/system/rpc.statd/sm_inter.h'

generate 'rpc.lockd/nlm_prot_svc.c' -L -C -m nlm_prot.x
generate 'rpc.lockd/nlm_prot.h' -L -C -h nlm_prot.x
compare 'rpc.lockd/nlm_prot_svc.c' 'userland/system/rpc.lockd/nlm_prot_svc.c'
compare 'rpc.lockd/nlm_prot.h' 'userland/system/rpc.lockd/nlm_prot.h'

generate 'rpc.bootparamd/bootparam_prot_svc.c' -C -m bootparam_prot.x
generate 'rpc.bootparamd/bootparam_prot.h' -C -h bootparam_prot.x
compare 'rpc.bootparamd/bootparam_prot_svc.c' \
	'userland/system/rpc.bootparamd/bootparam_prot_svc.c'
compare 'rpc.bootparamd/bootparam_prot.h' \
	'userland/system/rpc.bootparamd/bootparam_prot.h'

if [ "$failed" -ne 0 ]; then
	exit 1
fi
echo "rpcgen output is current ($RPCGEN_VERSION)"
