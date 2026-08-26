#!/usr/bin/perl
# EteleOS: installer/miniroot/trimcerts.pl, time wirte: 2026/08/26
# This file uses the Apache-2.0 license
#
# Converted from the original AWK implementation.
# Original header preserved below for provenance:
#
#	$OpenBSD: trimcerts.awk,v 1.2 2019/05/15 20:27:42 sthen Exp $
#
# Copyright (c) 2018 Stuart Henderson <sthen@openbsd.org>
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
#
#	read in a formatted list of X509 certificates with long decodes,
#	output only short comments plus the certificates themselves
#

use strict;
use warnings;

if (scalar(@ARGV) != 2) {
	print "usage: perl trimcerts.pl cert.pem outputfile\n";
	exit 1;
}

my ($certfile, $outputfile) = @ARGV;

open(my $in, '<', $certfile) or die "trimcerts.pl: cannot open $certfile: $!\n";
open(my $out, '>', $outputfile) or die "trimcerts.pl: cannot open $outputfile: $!\n";

my $incert = 0;
while (my $line = <$in>) {
	if ($line =~ /^-----BEGIN CERTIFICATE-----/) {
		$incert = 1;
	}
	if ($line =~ /^#/ || $incert) {
		print $out $line;
	}
	if ($line =~ /^-----END CERTIFICATE-----/) {
		$incert = 0;
	}
}

close($in);
close($out);

system("chmod", "444", $outputfile);
system("chown", "root:bin", $outputfile);
