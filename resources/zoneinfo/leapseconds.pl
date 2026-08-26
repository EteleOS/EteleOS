#!/usr/bin/perl
# EteleOS: resources/zoneinfo/leapseconds.pl, time wirte: 2026/08/26
# This file uses the Apache-2.0 license
#
# --- Original upstream header follows (preserved verbatim) ---
#
# Generate zic format 'leapseconds' from NIST/IERS format 'leap-seconds.list'.

# This file is in the public domain.

# This program uses awk arithmetic.  POSIX requires awk to support
# exact integer arithmetic only through 10**10, which means for NTP
# timestamps this program works only to the year 2216, which is the
# year 1900 plus 10**10 seconds.  However, in practice
# POSIX-conforming awk implementations invariably use IEEE-754 double
# and so support exact integers through 2**53.  By the year 2216,
# POSIX will almost surely require at least 2**53 for awk, so for NTP
# timestamps this program should be good until the year 285,428,681
# (the year 1900 plus 2**53 seconds).  By then leap seconds will be
# long obsolete, as the Earth will likely slow down so much that
# there will be more than 25 hours per day and so some other scheme
# will be needed.
#
# --- End of original upstream header ---

use strict;
use warnings;

# EXPIRES_LINE is passed via -v EXPIRES_LINE=... in the awk invocation;
# here we take it from the environment, defaulting to 0 like the awk did
# when unset (empty/undef is falsy in both awk and Perl).
my $EXPIRES_LINE = defined $ENV{EXPIRES_LINE} ? $ENV{EXPIRES_LINE} : '';

my @monthabbr = (
    undef, "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec",
);

# sstamp_init constants
# Days in month N, where March is month 0 and January month 10.
my @ss_mon_days = (31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 31);

my $ss_year_days = 365;
my $ss_quadyear_days = $ss_year_days * 4 + 1;
my $ss_century_days = $ss_quadyear_days * 25 - 1;
my $ss_quadcentury_days = $ss_century_days * 4 + 1;

my $ss_NTP = 109513;

# sstamp_to_ymdhMs - convert seconds timestamp to date and time.
#
# Call as:
#
#    sstamp_to_ymdhMs(sstamp, epoch_days)
#
# where:
#
#    sstamp - is the seconds timestamp.
#    epoch_days - is the timestamp epoch in Gregorian days since 1600-03-01.
#	$ss_NTP is appropriate for an NTP sstamp.
#
# Both arguments should be nonnegative integers.
# Returns a hashref with keys:
#
#    year	- Gregorian calendar year
#    month	- month of the year (1-January to 12-December)
#    mday	- day of the month (1-31)
#    hour	- hour (0-23)
#    min	- minute (0-59)
#    sec	- second (0-59)
#    wday	- day of week (0-Sunday to 6-Saturday)
sub sstamp_to_ymdhMs {
    my ($sstamp, $epoch_days) = @_;

    my %ss;
    $ss{hour} = int($sstamp / 3600) % 24;
    $ss{min}  = int($sstamp / 60) % 60;
    $ss{sec}  = $sstamp % 60;

    # Start with a count of days since 1600-03-01 Gregorian.
    my $day = $epoch_days + int($sstamp / (24 * 60 * 60));

    my $quadcentury = int($day / $ss_quadcentury_days);
    $day -= $quadcentury * $ss_quadcentury_days;
    $ss{wday} = ($day + 3) % 7;
    my $century = int($day / $ss_century_days);
    $century -= ($century == 4) ? 1 : 0;
    $day -= $century * $ss_century_days;
    my $quadyear = int($day / $ss_quadyear_days);
    $day -= $quadyear * $ss_quadyear_days;
    my $year = int($day / $ss_year_days);
    $year -= ($year == 4) ? 1 : 0;
    $day -= $year * $ss_year_days;

    my $month;
    for ($month = 0; $month < 11; $month++) {
        last if $day < $ss_mon_days[$month];
        $day -= $ss_mon_days[$month];
    }

    $ss{mday} = $day + 1;
    if ($month <= 9) {
        $ss{month} = $month + 3;
    } else {
        $ss{month} = $month - 9;
        $year++;
    }
    $ss{year} = 1600 + $quadcentury * 400 + $century * 100 + $quadyear * 4 + $year;

    return \%ss;
}

print "# Allowance for leap seconds added to each time zone file.\n";
print "\n";
print "# This file is in the public domain.\n";
print "\n";
print "# This file is generated automatically from the data in the public-domain\n";
print "# NIST/IERS format leap-seconds.list file, which can be copied from\n";
print "# <https://hpiers.obspm.fr/iers/bul/bulc/ntp/leap-seconds.list>\n";
print "# or via a less-secure protocol and with different comments and\n";
print "# less volatile last-modified and expiration timestamps, from\n";
print "# <ftp://ftp.boulder.nist.gov/pub/time/leap-seconds.list>.\n";
print "# For more about leap-seconds.list, please see\n";
print "# The NTP Timescale and Leap Seconds\n";
print "# <https://www.eecis.udel.edu/~mills/leap.html>.\n";
print "\n";
print "# The rules for leap seconds are specified in Annex 1 (Time scales) of:\n";
print "# Standard-frequency and time-signal emissions.\n";
print "# International Telecommunication Union - Radiocommunication Sector\n";
print "# (ITU-R) Recommendation TF.460-6 (02/2002)\n";
print "# <https://www.itu.int/rec/R-REC-TF.460-6-200202-I/>.\n";
print "# The International Earth Rotation and Reference Systems Service (IERS)\n";
print "# periodically uses leap seconds to keep UTC to within 0.9 s of UT1\n";
print "# (a proxy for Earth's angle in space as measured by astronomers)\n";
print "# and publishes leap second data in a copyrighted file\n";
print "# <https://hpiers.obspm.fr/iers/bul/bulc/Leap_Second.dat>.\n";
print "# See: Levine J. Coordinated Universal Time and the leap second.\n";
print "# URSI Radio Sci Bull. 2016;89(4):30-6. doi:10.23919/URSIRSB.2016.7909995\n";
print "# <https://ieeexplore.ieee.org/document/7909995>.\n";
print "\n";
print "# There were no leap seconds before 1972, as no official mechanism\n";
print "# accounted for the discrepancy between atomic time (TAI) and the earth's\n";
print "# rotation.  The first (\"1 Jan 1972\") data line in leap-seconds.list\n";
print "# does not denote a leap second; it denotes the start of the current definition\n";
print "# of UTC.\n";
print "\n";
print "# All leap-seconds are Stationary (S) at the given UTC time.\n";
print "# The correction (+ or -) is made at the given time, so in the unlikely\n";
print "# event of a negative leap second, a line would look like this:\n";
print "# Leap\tYEAR\tMON\tDAY\t23:59:59\t-\tS\n";
print "# Typical lines look like this:\n";
print "# Leap\tYEAR\tMON\tDAY\t23:59:60\t+\tS\n";

my $last_lines = "";
my $updated;
my $expires;
my $old_TAI_minus_UTC;

while (my $line = <>) {
    chomp $line;
    # In case the input has CRLF form a la NIST.
    $line =~ s/\r$//;

    if ($line =~ /^#[ \t]*[Uu]pdated through/ || $line =~ /^#[ \t]*[Ff]ile expires on/) {
        $last_lines .= "$line\n";
    }

    if ($line =~ /^#\$[ \t]/) {
        my @f = split ' ', $line;
        $updated = $f[1];
    }
    if ($line =~ /^#\@[ \t]/) {
        my @f = split ' ', $line;
        $expires = $f[1];
    }

    next if $line =~ /^[ \t]*#/;

    my @fields = split ' ', $line;
    my $NTP_timestamp = $fields[0];
    my $TAI_minus_UTC = $fields[1];
    if (defined $old_TAI_minus_UTC && $old_TAI_minus_UTC) {
        my $sign;
        if ($old_TAI_minus_UTC < $TAI_minus_UTC) {
            $sign = "23:59:60\t+";
        } else {
            $sign = "23:59:59\t-";
        }
        my $ss = sstamp_to_ymdhMs($NTP_timestamp - 1, $ss_NTP);
        printf "Leap\t%d\t%s\t%d\t%s\tS\n",
            $ss->{year}, $monthabbr[$ss->{month}], $ss->{mday}, $sign;
    }
    $old_TAI_minus_UTC = $TAI_minus_UTC;
}

print "\n";

if ($expires) {
    my $ss = sstamp_to_ymdhMs($expires, $ss_NTP);

    print "# UTC timestamp when this leap second list expires.\n";
    print "# Any additional leap seconds will come after this.\n";
    if (!$EXPIRES_LINE) {
        print "# This Expires line is commented out for now,\n";
        print "# so that pre-2020a zic implementations do not reject this file.\n";
    }
    printf "%sExpires %.4d\t%s\t%.2d\t%.2d:%.2d:%.2d\n",
        ($EXPIRES_LINE ? "" : "#"),
        $ss->{year}, $monthabbr[$ss->{month}], $ss->{mday}, $ss->{hour}, $ss->{min}, $ss->{sec};
} else {
    print "# (No Expires line, since the expires time is unknown.)\n";
}

# The difference between the NTP and POSIX epochs is 70 years
# (including 17 leap days), each 24 hours of 60 minutes of 60
# seconds each.
my $epoch_minus_NTP = ((1970 - 1900) * 365 + 17) * 24 * 60 * 60;

print "\n";
print "# Here are POSIX timestamps for the data in this file.\n";
print "# \"#updated\" gives the last time the leap seconds data changed\n";
print "# or, if this file was derived from the IERS leap-seconds.list,\n";
print "# the last time that file changed in any way.\n";
print "# \"#expires\" gives the first time this file might be wrong;\n";
print "# if this file was derived from the IERS leap-seconds.list,\n";
print "# this is typically a bit less than one year after \"updated\".\n";
if ($updated) {
    my $ss = sstamp_to_ymdhMs($updated, $ss_NTP);
    printf "#updated %d (%.4d-%.2d-%.2d %.2d:%.2d:%.2d UTC)\n",
        $updated - $epoch_minus_NTP,
        $ss->{year}, $ss->{month}, $ss->{mday}, $ss->{hour}, $ss->{min}, $ss->{sec};
} else {
    print "#(updated time unknown)\n";
}
if ($expires) {
    my $ss = sstamp_to_ymdhMs($expires, $ss_NTP);
    printf "#expires %d (%.4d-%.2d-%.2d %.2d:%.2d:%.2d UTC)\n",
        $expires - $epoch_minus_NTP,
        $ss->{year}, $ss->{month}, $ss->{mday}, $ss->{hour}, $ss->{min}, $ss->{sec};
} else {
    print "#(expires time unknown)\n";
}
printf "\n%s", $last_lines;
