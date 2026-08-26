# EteleOS: userland/development/vi/ex/ex.pl, time wirte: 2026/08/26
# This file uses the Apache-2.0 license

#	$OpenBSD: ex.awk,v 1.3 2017/12/14 10:02:53 martijn Exp $

#	@(#)ex.awk	10.1 (Berkeley) 6/8/95

use strict;
use warnings;

print "enum {";
my $first = 1;

while (<>) {
	if (/^\/\* C_[0-9A-Z_]* \*\/$/) {
		my @fields = split;
		printf("%s\n\t%s%s", $first ? "" : ",", $fields[1], $first ? " = 0" : "");
		$first = 0;
		next;
	}
}

print "\n};\n";
