#!/usr/bin/perl
# PeteleOS: kernel/dev/mii/devlist2h.pl, time wirte: 2026/08/26
# This file uses the Apache-2.0 license
#
# Converted from devlist2h.awk (see original comment block below for
# provenance). Functionally equivalent Perl port.
#
#	$OpenBSD: devlist2h.awk,v 1.3 2023/01/04 14:42:46 jsg Exp $
#	$NetBSD: devlist2h.awk,v 1.2 1998/09/05 14:42:06 christos Exp $
#
# Copyright (c) 1998 The NetBSD Foundation, Inc.
# All rights reserved.
#
# This code is derived from software contributed to The NetBSD Foundation
# by Christos Zoulas.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
# ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
# TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
# BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
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
#      This model includes software developed by Christopher G. Demetriou.
# 4. The name of the author(s) may not be used to endorse or promote models
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

sub collectline {
	my ($fields, $f) = @_;
	my $nf = scalar(@$fields) - 1;
	my $oparen = 0;
	my $line = "";
	while ($f <= $nf) {
		my $tok = $fields->[$f];
		if ($tok eq "#") {
			$line .= "(";
			$oparen = 1;
			$f++;
			next;
		}
		if ($oparen) {
			$line .= $tok;
			$line .= " " if $f < $nf;
			$f++;
			next;
		}
		$line .= $tok;
		$line .= " " if $f < $nf;
		$f++;
	}
	$line .= ")" if $oparen;
	return $line;
}

my $hfile_name = "miidevs.h";
open(my $H, '>', $hfile_name) or die "cannot open $hfile_name: $!";

my $nmodels = 0;
my $nouis = 0;
my @ouis;
my @models;

my $nr = 0;
while (my $line = <>) {
	$nr++;
	chomp $line;

	if ($nr == 1) {
		my $version = $line;
		$version =~ s/\$//g;

		print $H "/*\t\$OpenBSD\$\t*/\n\n";
		print $H "/*\n";
		print $H " * THIS FILE AUTOMATICALLY GENERATED.  DO NOT EDIT.\n";
		print $H " *\n";
		print $H " * generated from:\n";
		print $H " *\t$version\n";
		print $H " */\n";

		next;
	}

	my @f = split(' ', $line);

	if (@f && $f[0] eq "oui") {
		$nouis++;
		my $idx = $nouis - 1;
		$ouis[$idx][0] = $f[1];	# name
		$ouis[$idx][1] = $f[2];	# id
		printf $H "#define\tMII_OUI_%s\t%s\t", $ouis[$idx][0],
		    $ouis[$idx][1];
		$ouis[$idx][2] = collectline(\@f, 3);
		printf $H "/* %s */\n", $ouis[$idx][2];
		next;
	}
	if (@f && $f[0] eq "model") {
		$nmodels++;
		my $idx = $nmodels - 1;
		$models[$idx][0] = $f[1];	# oui name
		$models[$idx][1] = $f[2];	# model id
		$models[$idx][2] = $f[3];	# id

		printf $H "#define\tMII_MODEL_%s_%s\t%s\n", $models[$idx][0],
		    $models[$idx][1], $models[$idx][2];

		$models[$idx][3] = collectline(\@f, 4);

		printf $H "#define\tMII_STR_%s_%s\t\"%s\"\n",
		    $models[$idx][0], $models[$idx][1],
		    $models[$idx][3];

		next;
	}

	print $H "$line\n";
}

close($H);
