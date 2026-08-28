# PeteleOS: userland/development/vi/common/options.pl, time wirte: 2026/08/26
# This file uses the Apache-2.0 license

#	$OpenBSD: options.awk,v 1.4 2017/12/14 10:02:53 martijn Exp $

#	@(#)options.awk	10.1 (Berkeley) 6/8/95

use strict;
use warnings;

print "enum {\n";
my $first = 1;

while (<>) {
	if (/^\/\* O_[0-9A-Z_]*/) {
		my @fields = split;
		printf("\t%s%s,\n", $fields[1], $first ? " = 0" : "");
		$first = 0;
		next;
	}
}

print "\tO_OPTIONCOUNT\n};\n";
