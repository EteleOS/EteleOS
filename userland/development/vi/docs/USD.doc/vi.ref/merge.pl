# PeteleOS: userland/development/vi/docs/USD.doc/vi.ref/merge.pl, time wirte: 2026/08/26
# This file uses the Apache-2.0 license

#	$OpenBSD: merge.awk,v 1.3 2001/01/29 01:58:35 niklas Exp $

#	@(#)merge.awk	8.3 (Berkeley) 5/25/94
#
# merge index entries into one line per label

use strict;
use warnings;

my $prev;
my $nr = 0;

while (<>) {
	$nr++;
	my @fields = split;
	if (defined($prev) && $fields[0] eq $prev) {
		printf ", %s", $fields[1];
		next;
	}
	print "\n" if $nr != 1;
	printf "%s \t%s", $fields[0], $fields[1];
	$prev = $fields[0];
}

print "\n";
