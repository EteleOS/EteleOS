#!/usr/bin/perl
# EteleOS: kernel/dev/pci/devlist2h.pl, time wirte: 2026/08/26
# This file uses the Apache-2.0 license
#
# Converted from devlist2h.awk (see original comment block below for
# provenance). Functionally equivalent Perl port.
#
#	$OpenBSD: devlist2h.awk,v 1.8 2007/02/21 13:17:28 deraadt Exp $
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

my $dfile_name = "pcidevs_data.h";
my $hfile_name = "pcidevs.h";

open(my $D, '>', $dfile_name) or die "cannot open $dfile_name: $!";
open(my $H, '>', $hfile_name) or die "cannot open $hfile_name: $!";

my $nproducts = 0;
my $nvendor_dup = 0;
my $nvendors = 0;
my $blanklines = 0;
my %vendorindex;
my @vendors;	# [name, id, comment_words...]
my @products;	# [vendorname, productid, id, comment_words...]

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
		print $D " */\n\n";

		print $H "/*\n";
		print $H " * THIS FILE AUTOMATICALLY GENERATED.  DO NOT EDIT.\n";
		print $H " *\n";
		print $H " * generated from:\n";
		print $H " *\t$version\n";
		print $H " */\n";

		next;
	}

	my @f = split(' ', $line);
	my $nf = scalar(@f) - 1;

	if (@f > 0 && $f[0] eq "vendor") {
		$nvendors++;
		my $idx = $nvendors - 1;

		if (exists $vendorindex{$f[1]}) {
			print "duplicate vendor name $f[1]\n";
			$nvendor_dup++;
		}

		$vendorindex{$f[1]} = $nvendors;
		$vendors[$idx][0] = $f[1];	# name
		$vendors[$idx][1] = $f[2];	# id
		printf $H "#define\tPCI_VENDOR_%s\t%s\t", $vendors[$idx][0],
		    $vendors[$idx][1];

		my $i = 2; my $fidx = 3;

		my $ocomment = 0; my $oparen = 0;
		if ($fidx <= $nf) {
			print $H "\t/* ";
			$ocomment = 1;
		}
		while ($fidx <= $nf) {
			if ($f[$fidx] eq "#") {
				print $H "(";
				$oparen = 1;
				$fidx++;
				next;
			}
			if ($oparen) {
				print $H $f[$fidx];
				print $H " " if $fidx < $nf;
				$fidx++;
				next;
			}
			$vendors[$idx][$i] = $f[$fidx];
			print $H $vendors[$idx][$i];
			print $H " " if $fidx < $nf;
			$i++; $fidx++;
		}
		print $H ")" if $oparen;
		print $H " */" if $ocomment;
		print $H "\n";

		next;
	}

	if (@f > 0 && $f[0] eq "product") {
		$nproducts++;
		my $idx = $nproducts - 1;
		$products[$idx][0] = $f[1];	# vendor name
		$products[$idx][1] = $f[2];	# product id
		$products[$idx][2] = $f[3];	# id
		printf $H "#define\tPCI_PRODUCT_%s_%s\t%s\t", $products[$idx][0],
		    $products[$idx][1], $products[$idx][2];

		my $i = 3; my $fidx = 4;

		my $ocomment = 0; my $oparen = 0;
		if ($fidx <= $nf) {
			print $H "\t/* ";
			$ocomment = 1;
		}
		while ($fidx <= $nf) {
			if ($f[$fidx] eq "#") {
				print $H "(";
				$oparen = 1;
				$fidx++;
				next;
			}
			if ($oparen) {
				print $H $f[$fidx];
				print $H " " if $fidx < $nf;
				$fidx++;
				next;
			}
			$products[$idx][$i] = $f[$fidx];
			print $H $products[$idx][$i];
			print $H " " if $fidx < $nf;
			$i++; $fidx++;
		}
		print $H ")" if $oparen;
		print $H " */" if $ocomment;
		print $H "\n";

		next;
	}

	$blanklines++ if $line eq "";
	print $H "$line\n";
	print $D "$line\n" if $blanklines < 2;
}

# END: print out the match tables

print $D "\n";

if ($nvendor_dup > 0) {
	close($D);
	close($H);
	exit(1);
}

print $D "/* Descriptions of known vendors and devices. */\n";
print $D "struct pci_known_vendor {\n";
print $D "\tpci_vendor_id_t vendor;\n";
print $D "\tconst char *vendorname;\n";
print $D "};\n\n";

print $D "struct pci_known_product {\n";
print $D "\tpci_vendor_id_t vendor;\n";
print $D "\tpci_product_id_t product;\n";
print $D "\tconst char *productname;\n";
print $D "};\n\n";

print $D "static const struct pci_known_product pci_known_products[] = {\n";
for (my $i = 0; $i < $nproducts; $i++) {
	print $D "\t{\n";
	printf $D "\t    PCI_VENDOR_%s, PCI_PRODUCT_%s_%s,\n",
	    $products[$i][0], $products[$i][0], $products[$i][1];

	print $D "\t    \"";
	my $j = 3;
	my $needspace = 0;
	while (defined($products[$i][$j]) && $products[$i][$j] ne "") {
		print $D " " if $needspace;
		print $D $products[$i][$j];
		$needspace = 1;
		$j++;
	}
	print $D "\",\n";
	print $D "\t},\n";
}
print $D "\t{ 0, 0, NULL, }\n";
print $D "};\n\n";

print $D "static const struct pci_known_vendor pci_known_vendors[] = {\n";
for (my $i = 0; $i < $nvendors; $i++) {
	print $D "\t{\n";
	printf $D "\t    PCI_VENDOR_%s,\n", $vendors[$i][0];
	print $D "\t    \"";
	my $j = 2;
	my $needspace = 0;
	while (defined($vendors[$i][$j]) && $vendors[$i][$j] ne "") {
		print $D " " if $needspace;
		print $D $vendors[$i][$j];
		$needspace = 1;
		$j++;
	}
	print $D "\",\n";
	print $D "\t},\n";
}
print $D "\t{ 0, NULL, }\n";
print $D "};\n";

close($H);
close($D);
