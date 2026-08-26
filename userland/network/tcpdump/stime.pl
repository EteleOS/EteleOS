# EteleOS: userland/network/tcpdump/stime.pl, time wirte: 2026/08/26
# This file uses the Apache-2.0 license
#
# Converted from stime.awk to Perl.
#
# The original stime.awk carried no separate copyright/license header
# of its own; it is one of the small ftp-trace analysis scripts
# distributed alongside OpenBSD's tcpdump (see README in this
# directory). Its original comments are preserved below verbatim.
#
# given a tcpdump ftp trace, output one line for each send
# in the form
#   <send time> <seq no>
# where <send time> is the time packet was sent (in seconds with
# zero at time of first packet) and <seq no> is the tcp sequence
# number of the packet divided by 1024 (i.e., Kbytes sent).
#
# usage: perl stime.pl tracedata

use strict;
use warnings;

my $tzero;

while (my $line = <>) {
	chomp $line;
	my @f = split ' ', $line;
	next if defined $f[5] && $f[5] =~ /^ack/;
	next if defined $f[4] && $f[4] =~ /[SFR]/;

	# convert time to seconds
	my @t = split /:/, $f[0];
	my $tim = $t[0] * 3600 + $t[1] * 60 + $t[2];
	if (!$tzero) {
		$tzero = $tim;
	}
	# get packet sequence number
	my $i = index($f[5], ':');
	my $strtSeq = substr($f[5], 0, $i);
	printf "%7.2f\t%g\n", $tim - $tzero, $strtSeq / 1024;
}
