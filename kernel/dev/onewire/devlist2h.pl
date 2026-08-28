#!/usr/bin/perl
# PeteleOS: kernel/dev/onewire/devlist2h.pl, time wirte: 2026/08/26
# This file uses the Apache-2.0 license
#
# Converted from devlist2h.awk (see original comment block below for
# provenance). Functionally equivalent Perl port.
#
# $OpenBSD: devlist2h.awk,v 1.4 2007/02/28 22:31:32 deraadt Exp $

#
# Copyright (c) 2006 Alexander Yurchenko <grange@openbsd.org>
#
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
# ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
# OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
#
use strict;
use warnings;

my $hfile_name = "onewiredevs.h";
my $dfile_name = "onewiredevs_data.h";

open(my $H, '>', $hfile_name) or die "cannot open $hfile_name: $!";
open(my $D, '>', $dfile_name) or die "cannot open $dfile_name: $!";

my $nr = 0;
while (my $line = <>) {
	$nr++;
	chomp $line;

	if ($nr == 1) {
		my $version = $line;
		$version =~ s/\$//g;

		print $H "/*\t\$OpenBSD\$\t*/\n\n" .
		    "/*\n * THIS FILE AUTOMATICALLY GENERATED.  DO NOT EDIT.\n" .
		    " *\n * Generated from:\n *\t$version\n */\n\n";

		print $D "/*\t\$OpenBSD\$\t*/\n\n" .
		    "/*\n * THIS FILE AUTOMATICALLY GENERATED.  DO NOT EDIT.\n" .
		    " *\n * Generated from:\n *\t$version\n */\n\n";

		print $D "struct onewire_family {\n";
		print $D "\tint\t\tof_type;\n";
		print $D "\tconst char\t*of_name;\n";
		print $D "};\n\n";

		print $D "static const struct onewire_family " .
		    "onewire_famtab[] = {\n";

		next;
	}

	my @f = split(' ', $line);

	if (@f && $f[0] eq "family") {
		my $upname = uc($f[1]);
		printf $H "#define ONEWIRE_FAMILY_%s\t%s\n", $upname, $f[2];
		printf $D "\t{ ONEWIRE_FAMILY_%s, \"", $upname;

		my $nf = scalar(@f) - 1;
		for (my $i = 3; $i <= $nf; $i++) {
			print $D " " if $i > 3;
			print $D $f[$i];
		}
		print $D "\" },\n";
		next;
	}
}

print $D "\t{ 0, NULL }\n};\n";

close($H);
close($D);
