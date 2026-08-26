#!/usr/bin/perl
# EteleOS: resources/zoneinfo/ziguard.pl, time wirte: 2026/08/26
# This file uses the Apache-2.0 license
#
# --- Original upstream header follows (preserved verbatim) ---
#
# Convert tzdata source into vanguard or rearguard form.

# Contributed by Paul Eggert.  This file is in the public domain.

# This is not a general-purpose converter; it is designed for current tzdata.
# It just converts from current source to main, vanguard, and rearguard forms.
# Although it might be nice for it to be idempotent, or to be useful
# for converting back and forth between formats,
# it does not do these nonessential tasks now.
#
# This script can convert from main to vanguard form and vice versa.
# There is no need to convert rearguard to other forms.
#
# When converting to vanguard form, the output can use the line
# "Zone GMT 0 - GMT" which TZUpdater 2.3.2 mistakenly rejects.
#
# When converting to vanguard form, the output can use negative SAVE
# values.
#
# When converting to rearguard form, the output uses only nonnegative
# SAVE values.  The idea is for the output data to simulate the behavior
# of the input data as best it can within the constraints of the
# rearguard format.
#
# --- End of original upstream header ---
#
# NOTE (EteleOS): This is a line-for-line Perl port of the upstream
# ziguard.awk tzdata tool.  See the project README / conversion report
# for details on why this was ported, and the caveat that future
# upstream tzdata changes to ziguard.awk will need to be manually
# re-applied here rather than simply re-vendored.

use strict;
use warnings;
no warnings 'numeric';  # awk silently coerces non-numeric strings to 0

# Given a FIELD like "-0:30", return a minute count like -30.
sub get_minutes {
    my ($field) = @_;
    my $sign = ($field =~ /^-/) ? -1 : 1;
    my $hours = numify($field);
    my $minutes = 0;
    if ($field =~ /:/) {
        $minutes = $field;
        $minutes =~ s/[^:]*://;
        $minutes = numify($minutes);
    }
    return 60 * $hours + $sign * $minutes;
}

# Emulate awk's "+field" numeric coercion (leading numeric prefix, else 0).
sub numify {
    my ($s) = @_;
    return $s + 0;
}

# Emulate awk/C truncated-toward-zero modulo (Perl's % is floored for
# negative operands, which differs from awk when values can be negative).
sub cmod {
    my ($a, $b) = @_;
    return $a - $b * int($a / $b);
}

# Emulate awk/C truncating integer division (Perl's int() already
# truncates toward zero, matching awk's int()).
sub cdiv {
    my ($a, $b) = @_;
    return int($a / $b);
}

# Given an OFFSET, which is a minute count like 300 or 330,
# return a %z-style abbreviation like "+05" or "+0530".
sub offset_abbr {
    my ($offset) = @_;
    my $hours = cdiv($offset, 60);
    my $minutes = cmod($offset, 60);
    if ($minutes) {
        return sprintf("%+.4d", $hours * 100 + $minutes);
    } else {
        return sprintf("%+.2d", $hours);
    }
}

# Round TIMESTAMP (a +-hh:mm:ss.dddd string) to the nearest second.
sub round_to_second {
    my ($timestamp) = @_;
    my $dot_dddd = $timestamp;
    if (!($dot_dddd =~ s/^[+-]?[0-9]+:[0-9]+:[0-9]+\././)) {
        return $timestamp;
    }
    my ($hh, $mm, $ss) = ($timestamp, $timestamp, $timestamp);
    $ss =~ s/^[-+]?[0-9]+:[0-9]+://;
    $mm =~ s/^[-+]?[0-9]+://;
    $mm =~ s/:.*//;
    $hh =~ s/^[-+]?//;
    $hh =~ s/:.*//;
    $ss =~ s/:.*//;
    $hh = numify($hh);
    $mm = numify($mm);
    $ss = numify($ss);
    my $seconds = 3600 * $hh + 60 * $mm + $ss;
    my $subseconds = numify($dot_dddd);
    $seconds += (0.5 < $subseconds || ($subseconds == 0.5 && (cmod($seconds, 2)))) ? 1 : 0;
    return sprintf("%s%d:%.2d:%.2d", ($timestamp =~ /^-/ ? "-" : ""),
        cdiv($seconds, 3600), cmod(cdiv($seconds, 60), 60), cmod($seconds, 60));
}

# Return a link line resulting by changing OLDLINE to link to TARGET
# from LINKNAME, instead of linking to OLDTARGET from LINKNAME.
# Align data columns the same as they were in OLDLINE.
# Also, replace any existing white space followed by comment with COMMENT.
sub make_linkline {
    my ($oldline, $target, $linkname, $oldtarget, $comment) = @_;
    $comment = '' unless defined $comment;
    my $oldprefix = "Link\t$oldtarget\t";
    my $oldprefixlen = length($oldprefix);
    my $replsuffix;
    if (substr($oldline, 0, $oldprefixlen) eq $oldprefix) {
        # Use tab stops to preserve LINKNAME's column.
        $replsuffix = substr($oldline, $oldprefixlen);
        $replsuffix =~ s/[\t ]*#.*//;
        my $oldtargettabs = int(length($oldtarget) / 8) + 1;
        my $targettabs = int(length($target) / 8) + 1;
        for (; $targettabs < $oldtargettabs; $targettabs++) {
            $replsuffix = "\t" . $replsuffix;
        }
        for (; $oldtargettabs < $targettabs && $replsuffix =~ /^\t/; $targettabs--) {
            $replsuffix = substr($replsuffix, 1);
        }
    } else {
        # Odd format line; don't bother lining up its replacement nicely.
        $replsuffix = $linkname;
    }
    return "Link\t$target\t$replsuffix$comment";
}

# --- BEGIN block equivalent ---

my %dataform_type = (vanguard => 1, main => 1, rearguard => 1);

my $PACKRATLIST = $ENV{PACKRATLIST};
my $PACKRATDATA = $ENV{PACKRATDATA};
my $DATAFORM    = $ENV{DATAFORM};

my %packratlist;
if ($PACKRATLIST) {
    open(my $plfh, '<', $PACKRATLIST) or die "$0: can't open PACKRATLIST '$PACKRATLIST': $!\n";
    while (my $l = <$plfh>) {
        chomp $l;
        next if $l =~ /^#/;
        my @f = split ' ', $l;
        $packratlist{$f[2]} = 1 if defined $f[2];
    }
    close $plfh;
}

# The command line should set DATAFORM.
if (!$dataform_type{$DATAFORM // ''}) {
    exit 1;
}

# --- Main record-processing loop ---

my @line;       # line[NR] = $0 (1-indexed, like awk NR)
my %linkline;   # linkline[name] = NR
my %linktarget; # linktarget[name] = target

my $zone = '';
my $stdoff_subst0;
my $stdoff_subst1;
my $NR = 0;

while (my $raw = <>) {
    chomp $raw;
    my $line0 = $raw;
    $NR++;
    my $FILENAME = $ARGV;

    my @F = split ' ', $line0;
    # awk $0 is whole line, $1..$NF are fields (whitespace split, leading ws stripped)
    my $NF = scalar @F;

    # $1 == "#PACKRATLIST" && $2 == PACKRATLIST
    if (defined $F[0] && $F[0] eq '#PACKRATLIST' && defined $F[1] && defined $PACKRATLIST && $F[1] eq $PACKRATLIST) {
        $line0 =~ s/^#PACKRATLIST[\t ]+[^\t ]+[\t ]+//;
        @F = split ' ', $line0;
        $NF = scalar @F;
    }

    # /^Zone/ { zone = $2 }
    if ($line0 =~ /^Zone/) {
        $zone = $F[1] // '';
    }

    if ($DATAFORM ne "main") {
        my $in_comment = ($line0 =~ /^#/) ? 1 : 0;
        my $uncomment = 0;
        my $comment_out = 0;

        # Helper to fetch $(in_comment+N) style 1-based field, awk-safe (undef -> '')
        my $fld = sub {
            my ($idx) = @_; # 1-based
            return defined $F[$idx - 1] ? $F[$idx - 1] : '';
        };

        # Czechoslovakia negative SAVE values
        if ($zone eq "Europe/Prague" && $line0 =~ /^#?[\t ]+[01]:00[\t ]/
            && $line0 =~ /1947 Feb 23/) {
            my $val = $fld->($in_comment + 2);
            if ((($val ne "-") ? 1 : 0) == (($DATAFORM ne "rearguard") ? 1 : 0)) {
                $uncomment = $in_comment;
            } else {
                $comment_out = !$in_comment;
            }
        }

        # Ireland negative SAVE values
        my $Rule_Eire = ($line0 =~ /^#?Rule[\t ]+Eire[\t ]/) ? 1 : 0;
        my $f4 = $fld->($in_comment + 4);
        my $Zone_Dublin_post_1968 =
            ($zone eq "Europe/Dublin" && $line0 =~ /^#?[\t ]+[01]:00[\t ]/
             && (!$f4 || 1968 < $f4)) ? 1 : 0;
        if ($Rule_Eire || $Zone_Dublin_post_1968) {
            my $cond = ($Rule_Eire
                        || ($Zone_Dublin_post_1968 && $fld->($in_comment + 3) eq "IST/GMT"))
                        ? 1 : 0;
            if ($cond == (($DATAFORM ne "rearguard") ? 1 : 0)) {
                $uncomment = $in_comment;
            } else {
                $comment_out = !$in_comment;
            }
        }

        # Namibia negative SAVE values
        my $Rule_Namibia = ($line0 =~ /^#?Rule[\t ]+Namibia[\t ]/) ? 1 : 0;
        my $ic2 = $fld->($in_comment + 2);
        my $ic3 = $fld->($in_comment + 3);
        my $ic4 = $fld->($in_comment + 4);
        my $Zone_using_Namibia_rule =
            ($zone eq "Africa/Windhoek" && $line0 =~ /^#?[\t ]+[12]:00[\t ]/
             && ($ic2 eq "Namibia"
                 || ($ic2 eq "-" && $ic3 eq "CAT"
                     && ((1994 <= $ic4 && $ic4 <= 2017)
                         || $in_comment + 3 == $NF)))) ? 1 : 0;
        if ($Rule_Namibia || $Zone_using_Namibia_rule) {
            my $cond;
            if ($Rule_Namibia) {
                my $f9 = $fld->(9);
                my $f10 = $fld->(10);
                $cond = (($f9 =~ /^-/) || ($f9 == 0 && $f10 eq "CAT")) ? 1 : 0;
            } else {
                $cond = ($fld->($in_comment + 1) eq "2:00" && $fld->($in_comment + 2) eq "Namibia") ? 1 : 0;
            }
            if ($cond == (($DATAFORM ne "rearguard") ? 1 : 0)) {
                $uncomment = $in_comment;
            } else {
                $comment_out = !$in_comment;
            }
        }

        # Portugal %z preference
        if ($line0 =~ /^#?[\t ]+-[12]:00[\t ]+((Port|W-Eur)[\t ]+[%+-]|-[\t ]+(%z|-01)[\t ]+1982 Mar 28)/) {
            my $hasz = ($line0 =~ /%z/) ? 1 : 0;
            if ($hasz == (($DATAFORM eq "rearguard") ? 1 : 0)) {
                $comment_out = !$in_comment;
            } else {
                $uncomment = $in_comment;
            }
        }

        # Vanguard "Zone GMT 0 - GMT" workaround
        if ($line0 =~ /^#?(Zone|Link)[\t ]+(Etc\/)?GMT[\t ]/) {
            my $eq = (($F[1] // '') eq "GMT") ? 1 : 0;
            if ($eq == (($DATAFORM eq "vanguard") ? 1 : 0)) {
                $uncomment = $in_comment;
            } else {
                $comment_out = !$in_comment;
            }
        }

        if ($uncomment) {
            $line0 =~ s/^#//;
        }
        if ($comment_out) {
            $line0 = "#" . $line0;
        }

        # refresh fields after possible comment mutation
        @F = split ' ', $line0;
        $NF = scalar @F;

        # Prefer explicit abbreviations in rearguard form, %z otherwise.
        if ($DATAFORM eq "rearguard") {
            if ($line0 =~ /^[^#]*%z/) {
                my $stdoff_column = 2 * (($line0 =~ /^Zone/) ? 1 : 0) + 1;
                my $rules_column = $stdoff_column + 1;
                my $stdoff = get_minutes($F[$stdoff_column - 1] // '');
                my $rules = $F[$rules_column - 1] // '';
                my $stdabbr = offset_abbr($stdoff);
                my $abbr;
                if ($rules eq "-") {
                    $abbr = $stdabbr;
                } else {
                    my $dstabbr_only = ($rules =~ /^[+0-9-]/) ? 1 : 0;
                    my $dstoff;
                    if ($dstabbr_only) {
                        $dstoff = get_minutes($rules);
                    } else {
                        if ($rules eq "Morocco" && $NF == 3) {
                            $dstoff = -60;
                        } elsif ($rules eq "NBorneo") {
                            $dstoff = 20;
                        } elsif ((($rules eq "Cook" || $rules eq "LH") && $NF == 3)
                                 || ($rules eq "Uruguay"
                                     && $line0 =~ /[\t ](1942 Dec 14|1960|1970|1974 Dec 22)$/)) {
                            $dstoff = 30;
                        } elsif ($rules eq "Uruguay" && $line0 =~ /[\t ]1974 Mar 10$/) {
                            $dstoff = 90;
                        } else {
                            $dstoff = 60;
                        }
                    }
                    my $dstabbr = offset_abbr($stdoff + $dstoff);
                    if ($dstabbr_only) {
                        $abbr = $dstabbr;
                    } else {
                        $abbr = "$stdabbr/$dstabbr";
                    }
                }
                $line0 =~ s/%z/$abbr/;
            }
        } else {
            if ($line0 =~ s/^(Zone[\t ]+[^\t ]+)?[\t ]+[^\t ]+[\t ]+[^\t ]+[\t ]+[-+][^\t ]+/$&CHANGE-TO-%z/) {
                # substituted
            }
            $line0 =~ s/-00CHANGE-TO-%z/-00/;
            $line0 =~ s/[-+][^\t ]+CHANGE-TO-//;
        }

        @F = split ' ', $line0;
        $NF = scalar @F;

        # Normally, prefer whole seconds.  However, prefer subseconds
        # if generating vanguard form and the otherwise-undocumented
        # VANGUARD_SUBSECONDS environment variable is set.
        if (defined $F[0] && $F[0] eq "#STDOFF") {
            my $stdoff = $F[1] // '';
            my $rounded_stdoff = round_to_second($stdoff);
            if ($DATAFORM eq "vanguard" && $ENV{VANGUARD_SUBSECONDS}) {
                $stdoff_subst0 = $rounded_stdoff;
                $stdoff_subst1 = $stdoff;
            } else {
                $stdoff_subst0 = $stdoff;
                $stdoff_subst1 = $rounded_stdoff;
            }
        } elsif (defined $stdoff_subst0 && $stdoff_subst0 ne '' && $stdoff_subst0 ne '0') {
            my $stdoff_column = 2 * (($line0 =~ /^Zone/) ? 1 : 0) + 1;
            my $stdoff_column_val = $F[$stdoff_column - 1] // '';
            if ($stdoff_column_val eq $stdoff_subst0) {
                my $q = quotemeta($stdoff_subst0);
                $line0 =~ s/$q/$stdoff_subst1/;
            } elsif ($stdoff_column_val ne $stdoff_subst1) {
                $stdoff_subst0 = 0;
            }
        }

        @F = split ' ', $line0;
        $NF = scalar @F;

        # Japan rule line adjustment for rearguard form.
        if ($line0 =~ /^Rule/ && defined $F[1] && $F[1] eq "Japan") {
            if ($DATAFORM eq "rearguard") {
                if (($F[6] // '') eq "Sat>=8" && ($F[7] // '') eq "25:00") {
                    $line0 =~ s/Sat>=8/Sun>=9/;
                    $line0 =~ s/25:00/ 1:00/;
                }
            } else {
                if (($F[6] // '') eq "Sun>=9" && ($F[7] // '') eq "1:00") {
                    $line0 =~ s/Sun>=9/Sat>=8/;
                    $line0 =~ s/ 1:00/25:00/;
                }
            }
            @F = split ' ', $line0;
            $NF = scalar @F;
        }

        # Morocco negative SAVE values for rearguard form.
        if (defined $F[1] && $F[1] eq "Morocco") {
            if ($line0 =~ /^Rule/) {
                if (defined $F[3] && $F[3] =~ /^201[78]$/ && defined $F[5] && $F[5] eq "Oct") {
                    if ($DATAFORM eq "rearguard") {
                        $line0 =~ s/\t2018\t/\t2017\t/;
                    } else {
                        $line0 =~ s/\t2017\t/\t2018\t/;
                    }
                    @F = split ' ', $line0;
                    $NF = scalar @F;
                }

                if (defined $F[2] && 2019 <= $F[2]) {
                    if (($F[7] // '') eq "2:00") {
                        if ($DATAFORM eq "rearguard") {
                            $line0 =~ s/\t0\t/\t1:00\t/;
                        } else {
                            $line0 =~ s/\t1:00\t/\t0\t/;
                        }
                    } else {
                        if ($DATAFORM eq "rearguard") {
                            $line0 =~ s/\t-1:00\t/\t0\t/;
                        } else {
                            $line0 =~ s/\t0\t/\t-1:00\t/;
                        }
                    }
                    @F = split ' ', $line0;
                    $NF = scalar @F;
                }
            }
            if (defined $F[0] && $F[0] =~ /^[+0-9-]/ && $NF == 3) {
                if ($DATAFORM eq "rearguard") {
                    $line0 =~ s/1:00\tMorocco/0:00\tMorocco/;
                    $line0 =~ s/\t\+01\/\+00$/\t+00\/+01/;
                } else {
                    $line0 =~ s/0:00\tMorocco/1:00\tMorocco/;
                    $line0 =~ s/\t\+00\/\+01$/\t+01\/+00/;
                }
                @F = split ' ', $line0;
                $NF = scalar @F;
            }
        }
    }

    # /^Zone/ { packrat_ignored = ... }
    our $packrat_ignored;
    if ($line0 =~ /^Zone/) {
        $packrat_ignored = ($FILENAME eq ($PACKRATDATA // '') && $PACKRATLIST && !$packratlist{$F[1] // ''}) ? 1 : 0;
    }
    if ($packrat_ignored && $line0 !~ /^Rule/) {
        $line0 = "#" . $line0;
    }
    @F = split ' ', $line0;
    $NF = scalar @F;

    # Vanguard Link with "#=" target annotation.
    if ($line0 =~ /^Link/ && defined $F[3] && $F[3] eq "#=" && $DATAFORM eq "vanguard") {
        $line0 = make_linkline($line0, $F[4], $F[2], $F[1]);
        @F = split ' ', $line0;
        $NF = scalar @F;
    }

    # If a Link line is followed by a Link or Zone line for the same data,
    # comment out the earlier Link line.
    if ($line0 =~ /^Zone/) {
        my $key = $F[1] // '';
        if (defined $linkline{$key}) {
            my $ln = $linkline{$key};
            $line[$ln] =~ s/^Link/#Link/;
        }
    }
    if ($line0 =~ /^Link/) {
        my $key = $F[2] // '';
        if (defined $linkline{$key}) {
            my $ln = $linkline{$key};
            $line[$ln] =~ s/^Link/#Link/;
        }
        $linkline{$key} = $NR;
        $linktarget{$key} = $F[1] // '';
    }

    $line[$NR] = $line0;
}

# Return a link line resulting by changing OLDLINE to link to TARGET (see above)

sub cut_link_chains_short {
    for my $linkname (keys %linktarget) {
        my $target = $linktarget{$linkname};
        my $t = $linktarget{$target};
        if ($t) {
            # TARGET is itself a link name.  Replace the line
            # "Link TARGET LINKNAME" with "Link T LINKNAME #= TARGET",
            # where T is at the end of the chain of links that LINKNAME points to.
            while (my $u = $linktarget{$t}) {
                $t = $u;
            }
            my $l = $linkline{$linkname};
            $line[$l] = make_linkline($line[$l], $t, $linkname, $target, "\t#= $target");
        }
    }
}

if ($DATAFORM ne "vanguard") {
    cut_link_chains_short();
}
for (my $i = 1; $i <= $NR; $i++) {
    print "$line[$i]\n";
}
