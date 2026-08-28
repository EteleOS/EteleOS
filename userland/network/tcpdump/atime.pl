# PeteleOS: userland/network/tcpdump/atime.pl, time wirte: 2026/08/26
# This file uses the Apache-2.0 license
#
# Converted from atime.awk to Perl.
#
# The original atime.awk carried no separate copyright/license header
# of its own; it is one of the small ftp-trace analysis scripts
# distributed alongside OpenBSD's tcpdump (see README in this
# directory). Its original comments are preserved below verbatim.
#
# given a tcpdump ftp trace, output one line for each ack
# in the form
#   <ack time> <seq no>
# where <ack time> is the time packet was acked (in seconds with
# zero at time of first packet) and <seq no> is the tcp sequence
# number of the ack divided by 1024 (i.e., Kbytes acked).
#
# usage: perl atime.pl tracedata

use strict;
use warnings;

my $tzero;

while (my $line = <>) {
	chomp $line;
	my @f = split ' ', $line;
	next unless defined $f[5] && $f[5] =~ /^ack/;
	next if defined $f[4] && $f[4] =~ /[SFR]/;

	# convert time to seconds
	my @t = split /:/, $f[0];
	my $tim = $t[0] * 3600 + $t[1] * 60 + $t[2];
	if (!$tzero) {
		$tzero = $tim;
	}
	# get packet sequence number
	printf "%7.2f\t%g\n", $tim - $tzero, $f[6] / 1024;
}
