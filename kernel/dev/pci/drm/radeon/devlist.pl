# EteleOS: kernel/dev/pci/drm/radeon/devlist.pl, time wirte: 2026/08/26
# This file uses the Apache-2.0 license
#
# Converted from devlist.awk

use strict;
use warnings;

print "/* THIS FILE AUTOMATICALLY GENERATED.  DO NOT EDIT. */\n";
print "static const struct pci_matchid radeon_devices[] = {\n";

while (<>) {
	chomp;
	if (/0, CHIP/) {
		my $val = substr($_, 2, 14);
		print "\t{ $val },\n";
	}
}

print "};\n";
