# PeteleOS: userland/network/tcpdump/packetdat.pl, time wirte: 2026/08/26
# This file uses the Apache-2.0 license
#
# Converted from packetdat.awk to Perl.
#
# The original packetdat.awk carried no separate copyright/license
# header of its own; it is one of the small ftp-trace analysis scripts
# distributed alongside OpenBSD's tcpdump (see README in this
# directory). Its original comments are preserved below verbatim.
#
# we need to know (usual) packet size to convert byte numbers
# to packet numbers
#
# print out per-packet data in the form:
#  <packet #>
#  <start sequence #>
#  <1st send time>
#  <last send time>
#  <1st ack time>
#  <last ack time>
#  <# sends>
#  <# acks>
#
# usage: perl packetdat.pl [packetsize=NNN] tracedata

use strict;
use warnings;

my $packetsize = 0;

# emulate awk's "var=value" command-line assignment convention
my @files;
foreach my $arg (@ARGV) {
	if ($arg =~ /^packetsize=(\S+)$/) {
		$packetsize = $1 + 0;
	} else {
		push @files, $arg;
	}
}
@ARGV = @files;

$packetsize = 512 if $packetsize <= 0;

my %firstSend;
my %lastSend;
my %seqNo;
my %timesSent;
my %firstAck;
my %lastAck;
my %timesAcked;
my $maxId = 0;
my $totalPackets = 0;
my $totalAcks = 0;

while (my $line = <>) {
	chomp $line;
	my @f = split ' ', $line;
	next if defined $f[4] && $f[4] =~ /[SR]/;

	my @t = split /:/, $f[0];
	my $tim = $t[0] * 3600 + $t[1] * 60 + $t[2];

	if (!defined $f[5] || $f[5] ne 'ack') {
		my $i = index($f[5], ':');
		my $strtSeq = substr($f[5], 0, $i);
		my $id = 1.5 + ($strtSeq - 1) / $packetsize;
		$id = int($id);
		$maxId = $id if $maxId < $id;
		if (!$firstSend{$id}) {
			$firstSend{$id} = $tim;
			$seqNo{$id} = $strtSeq;
		}
		$lastSend{$id} = $tim;
		$timesSent{$id}++;
		$totalPackets++;
	} else {
		my $id = 1 + ($f[6] - 2) / $packetsize;
		$id = int($id);
		$timesAcked{$id}++;
		$firstAck{$id} = $tim if !$firstAck{$id};
		$lastAck{$id} = $tim;
		$totalAcks++;
	}
}

print "# $maxId chunks.  $totalPackets packets sent.  $totalAcks acks.\n";

# for packets that were implicitly acked, make the ack time
# be the ack time of next explicitly acked packet.
for (my $i = $maxId - 1; $i > 0; $i--) {
	while ($i > 0 && !$firstAck{$i}) {
		$lastAck{$i} = $firstAck{$i} = $firstAck{$i + 1};
		$i--;
	}
}

my $tzero = $firstSend{1} // 0;
for (my $i = 1; $i <= $maxId; $i++) {
	printf "%d\t%d\t%.2f\t%.2f\t%.2f\t%.2f\t%d\t%d\n",
		$i, $seqNo{$i} // 0,
		($firstSend{$i} // 0) - $tzero, ($lastSend{$i} // 0) - $tzero,
		($firstAck{$i} // 0) - $tzero, ($lastAck{$i} // 0) - $tzero,
		$timesSent{$i} // 0, $timesAcked{$i} // 0;
}
