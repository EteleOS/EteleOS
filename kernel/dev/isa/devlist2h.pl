#!/usr/bin/perl
# PeteleOS: kernel/dev/isa/devlist2h.pl, time wirte: 2026/08/26
# This file uses the Apache-2.0 license
#
# Converted from devlist2h.awk (see original comment block below for
# provenance). Functionally equivalent Perl port.
#
#	$OpenBSD: devlist2h.awk,v 1.6 2001/01/29 06:16:14 mickey Exp $
#	$NetBSD: devlist2h.awk,v 1.2 1996/01/22 21:08:09 cgd Exp $
#
# Copyright (c) 1995, 1996 Christopher G. Demetriou
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. All advertising materials mentioning features or use of this software
#    must display the following acknowledgement:
#      This product includes software developed by Christopher G. Demetriou.
# 4. The name of the author may not be used to endorse or promote products
#    derived from this software without specific prior written permission
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
# OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
# NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
# THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
use strict;
use warnings;

my $dfile_name = "pnpdevs.h";
open(my $D, '>', $dfile_name) or die "cannot open $dfile_name: $!";

my $nproducts = 0;
my @products;	# array of [driver, pnpid, comment]

my $nr = 0;
while (my $line = <>) {
	$nr++;
	chomp $line;

	if ($nr == 1) {
		my $version = $line;
		$version =~ s/\$//g;

		print $D "/*\n";
		print $D " * THIS FILE AUTOMATICALLY GENERATED.  DO NOT EDIT.\n";
		print $D " *\n";
		print $D " * generated from:\n";
		print $D " *\t$version\n";
		print $D " */\n";

		next;
	}

	my @f = split(' ', $line);

	next if !@f || $f[0] eq "";
	next if substr($f[0], 0, 1) eq "#";
	next if (defined($f[1]) && substr($f[1], 0, 1) eq "#");

	my $field1 = $f[0];
	my $field2 = $f[1];

	my $lastx;
	do {
		$nproducts++;
		my $idx = $nproducts - 1;
		my $x = index($field1, "/");
		$lastx = $x;
		if ($x >= 0) {
			$products[$idx][0] = substr($field1, 0, $x);
		} else {
			$products[$idx][0] = $field1;
		}
		$products[$idx][1] = $field2;	# pnp id

		if ($x >= 0) {
			$field1 = substr($field1, $x + 1);
		} else {
			$field1 = "";
		}
	} while ($lastx >= 0 && $field1 ne "");

	next;
}

print $D "\n";

print $D "const struct isapnp_knowndev isapnp_knowndevs[] = {\n";
for (my $i = 0; $i < $nproducts; $i++) {
	printf $D "\t{ {\"%s\"}, {\"%s\"} },", $products[$i][1],
	    $products[$i][0];
	if ($products[$i][2]) {
		printf $D "\t/* %s */", $products[$i][2];
	}
	print $D "\n";
}
print $D "};\n";

close($D);
