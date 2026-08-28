#!/usr/bin/perl
# PeteleOS: resources/zoneinfo/zishrink.pl, time wirte: 2026/08/26
# This file uses the Apache-2.0 license
#
# --- Original upstream header follows (preserved verbatim) ---
#
# Convert tzdata source into a smaller version of itself.

# Contributed by Paul Eggert.  This file is in the public domain.

# This is not a general-purpose converter; it is designed for current tzdata.
# 'zic' should treat this script's output as if it were identical to
# this script's input.
#
# --- End of original upstream header ---
#
# NOTE (PeteleOS): This is a line-for-line Perl port of the upstream
# zishrink.awk tzdata tool.  See the project README / conversion report
# for details on why this was ported, and the caveat that future
# upstream tzdata changes to zishrink.awk will need to be manually
# re-applied here rather than simply re-vendored.
#
# The original script relies on gawk-specific behavior (PROCINFO) to sort
# its output for more-compressible results when run under gawk, and falls
# back to unsorted/insertion-order output under other awk implementations
# (e.g. the one-true-awk used on OpenBSD).  This port always sorts (the
# "gawk" branch), which is a deterministic superset of behavior and is what
# this project's build actually observes since its "awk" is gawk.

use strict;
use warnings;
no warnings 'numeric';

my %used_hashes;   # record_hash: n -> name
my %rule;          # rule name -> abbreviation

my @rule_output_line;   # index by nrule_out
my $nrule_out = 0;
my @link_output_line;   # index by nlink_out
my $nlink_out = 0;
my %zonedef;             # zonename -> concatenated output lines (joined by \n)
my %linkdef;              # zonename -> field[2] (target), used in vanguard+gawk mode
my %rule_used;             # rule reference name -> 1

my $zonename = '';
my $startdef;

# -v variables passed on the command line by the Makefile.
my $dataform = defined $ENV{dataform} ? $ENV{dataform} : '';
my $version  = defined $ENV{version}  ? $ENV{version}  : '';
my $redo     = defined $ENV{redo}     ? $ENV{redo}     : '';
my $deps     = defined $ENV{deps}     ? $ENV{deps}     : '';

# Record a hash N for the new name NAME, checking for collisions.
sub record_hash {
    my ($n, $name) = @_;
    if ($used_hashes{$n}) {
        printf "# ! collision: %s %s\n", $used_hashes{$n}, $name;
        exit 1;
    }
    $used_hashes{$n} = $name;
}

# Return a shortened rule name representing NAME,
# and record this relationship to the hash table.
sub gen_rule_name {
    my ($name) = @_;
    # Use a simple mnemonic: the first two letters.
    my $n = substr($name, 0, 2);
    record_hash($n, $name);
    return $n;
}

sub prehash_rule_names {
    # Rule names are not part of the tzdb API, so substitute shorter
    # ones.  Shortening them consistently from one release to the next
    # simplifies comparison of the output.  That being said, the
    # 1-letter names below are not standardized in any way, and can
    # change arbitrarily from one release to the next, as the main goal
    # here is compression not comparison.

    # Abbreviating these rules names to one letter saved the most space
    # circa 2018e.
    %rule = (
        Arg        => "A",
        Brazil     => "B",
        Canada     => "C",
        Denmark    => "D",
        EU         => "E",
        France     => "F",
        "GB-Eire"  => "G",
        Halifax    => "H",
        Italy      => "I",
        Jordan     => "J",
        Egypt      => "K", # "Kemet" in ancient Egyptian
        Libya      => "L",
        Morocco    => "M",
        Neth       => "N",
        Poland     => "O", # arbitrary
        Palestine  => "P",
        Cuba       => "Q", # Its start sounds like "Q".
        Russia     => "R",
        Syria      => "S",
        Turkey     => "T",
        Uruguay    => "U",
        Vincennes  => "V",
        Winn       => "W",
        Mongol     => "X", # arbitrary
        NT_YK      => "Y",
        Zion       => "Z",
        Austria    => "a",
        Belgium    => "b",
        "C-Eur"    => "c",
        Algeria    => "d", # country code DZ
        "E-Eur"    => "e",
        Taiwan     => "f", # Formosa
        Greece     => "g",
        Hungary    => "h",
        Iran       => "i",
        StJohns    => "j",
        Chatham    => "k", # arbitrary
        Lebanon    => "l",
        Mexico     => "m",
        Tunisia    => "n", # country code TN
        Moncton    => "o", # arbitrary
        Port       => "p",
        Albania    => "q", # arbitrary
        Regina     => "r",
        Spain      => "s",
        Toronto    => "t",
        US         => "u",
        Louisville => "v", # ville
        Iceland    => "w", # arbitrary
        Chile      => "x", # arbitrary
        Para       => "y", # country code PY
        Romania    => "z", # arbitrary
        Macau      => "_", # arbitrary

        # Use ISO 3166 alpha-2 country codes for remaining names that are
        # countries.  This is more systematic, and avoids collisions
        # (e.g., Malta and Moldova).
        Armenia   => "AM",
        Aus       => "AU",
        Azer      => "AZ",
        Barb      => "BB",
        Dhaka     => "BD",
        Bulg      => "BG",
        Bahamas   => "BS",
        Belize    => "BZ",
        Swiss     => "CH",
        Cook      => "CK",
        PRC       => "CN",
        Cyprus    => "CY",
        Czech     => "CZ",
        Germany   => "DE",
        DR        => "DO",
        Ecuador   => "EC",
        Finland   => "FI",
        Fiji      => "FJ",
        Falk      => "FK",
        Ghana     => "GH",
        Guat      => "GT",
        Hond      => "HN",
        Haiti     => "HT",
        Eire      => "IE",
        Iraq      => "IQ",
        Japan     => "JP",
        Kyrgyz    => "KG",
        ROK       => "KR",
        Latvia    => "LV",
        Lux       => "LX",
        Moldova   => "MD",
        Malta     => "MT",
        Mauritius => "MU",
        Namibia   => "NA",
        Nic       => "NI",
        Norway    => "NO",
        Peru      => "PE",
        Phil      => "PH",
        Pakistan  => "PK",
        Sudan     => "SD",
        Salv      => "SV",
        Tonga     => "TO",
        Vanuatu   => "VU",

        # Avoid collisions.
        Detroit => "Dt", # De = Denver
    );

    for my $name (keys %rule) {
        record_hash($rule{$name}, $name);
    }
}

sub make_line {
    my ($n, $field) = @_; # hashref, 1-based semantics (index 1..n)
    my $r = defined $field->{1} ? $field->{1} : '';
    for (my $f = 2; $f <= $n; $f++) {
        $r .= " " . (defined $field->{$f} ? $field->{$f} : '');
    }
    return $r;
}

# awk split(str, arr): splits on runs of whitespace, discarding leading/
# trailing whitespace, returns count; arr is populated 1-based.
sub awk_split {
    my ($str) = @_;
    my @parts = split ' ', $str;
    my %field;
    for my $i (0 .. $#parts) {
        $field{$i + 1} = $parts[$i];
    }
    return (scalar(@parts), \%field);
}

# Process the input line LINE and save it for later output.
sub process_input_line {
    my ($line) = @_;

    # Remove comments, normalize spaces, and append a space to each line.
    $line =~ s/#.*//;
    $line .= " ";
    $line =~ s/[\t ]+/ /g;

    # Abbreviate keywords and determine line type.
    my $linkline = ($line =~ s/^Link /L /) ? 1 : 0;
    my $ruleline = ($line =~ s/^Rule /R /) ? 1 : 0;
    my $zoneline = ($line =~ s/^Zone /Z /) ? 1 : 0;

    # Replace FooAsia rules with the same rules without "Asia", as they
    # are duplicates.
    if ($line =~ /[^ ]Asia /) {
        return if $ruleline;
        my $rstart = $-[0] + 1; # awk RSTART (1-based)
        $line = substr($line, 0, $rstart) . substr($line, $rstart + 4);
    }

    # Abbreviate times.
    while ($line =~ /[: ]0+[0-9]/) {
        my $rstart  = $-[0] + 1;
        my $rlength = $+[0] - $-[0];
        $line = substr($line, 0, $rstart) . substr($line, $rstart + $rlength - 2);
    }
    while ($line =~ /:0[^:]/) {
        my $rstart = $-[0] + 1;
        $line = substr($line, 0, $rstart - 1) . substr($line, $rstart + 1);
    }

    # Abbreviate weekday names.
    while ($line =~ / (last)?(Mon|Wed|Fri)[ <>]/) {
        my $end = $-[0] + 1 + ($+[0] - $-[0]); # RSTART + RLENGTH
        $line = substr($line, 0, $end - 4) . substr($line, $end - 2);
    }
    while ($line =~ / (last)?(Sun|Tue|Thu|Sat)[ <>]/) {
        my $end = $-[0] + 1 + ($+[0] - $-[0]);
        $line = substr($line, 0, $end - 3) . substr($line, $end - 2);
    }

    # Abbreviate "max", "min", "only" and month names.
    # Although "max" and "min" can both be abbreviated to just "m",
    # the longer forms "ma" and "mi" are needed with zic 2023d and earlier.
    my $maxsub = $dataform eq "vanguard" ? " m " : " ma ";
    my $minsub = $dataform eq "vanguard" ? " m " : " mi ";
    $line =~ s/ max / ${maxsub} /g;
    $line =~ s/ min / ${minsub} /g;
    $line =~ s/ only / o /g;
    $line =~ s/ Jan / Ja /g;
    $line =~ s/ Feb / F /g;
    $line =~ s/ Apr / Ap /g;
    $line =~ s/ Aug / Au /g;
    $line =~ s/ Sep / S /g;
    $line =~ s/ Oct / O /g;
    $line =~ s/ Nov / N /g;
    $line =~ s/ Dec / D /g;

    # Strip leading and trailing space.
    $line =~ s/^ //;
    $line =~ s/ $//;

    # Remove unnecessary trailing zero fields.
    $line =~ s/ 0+$//;

    # Remove unnecessary trailing days-of-month "1".
    if ($line =~ /[A-Za-z] 1$/) {
        my $rstart = $-[0] + 1;
        $line = substr($line, 0, $rstart);
    }

    # Remove unnecessary trailing " Ja" (for January).
    $line =~ s/ Ja$//;

    my ($n, $field) = awk_split($line);

    # Record which rule names are used, and generate their abbreviations.
    my $f = $zoneline ? 4 : ($linkline || $ruleline ? 0 : 2);
    my $r = $f == 0 ? '' : (defined $field->{$f} ? $field->{$f} : '');
    if ($r ne '' && $r =~ /^[^-+0-9]/) {
        $rule_used{$r} = 1;
    }

    if ($zoneline) {
        $zonename = $startdef = defined $field->{2} ? $field->{2} : '';
    } elsif ($linkline) {
        $zonename = $startdef = defined $field->{3} ? $field->{3} : '';
    } elsif ($ruleline) {
        $zonename = "";
    }

    # Save the information for later output.
    my $outline = make_line($n, $field);
    if ($ruleline) {
        $rule_output_line[$nrule_out++] = $outline;
    } elsif ($linkline) {
        # In vanguard format with gawk, links are output sorted by
        # destination.  This project's build always runs under gawk,
        # so replicate that here (see header note above).
        if ($dataform eq "vanguard") {
            $linkdef{$zonename} = defined $field->{2} ? $field->{2} : '';
        } else {
            $link_output_line[$nlink_out++] = $outline;
        }
    } else {
        $zonedef{$zonename} = ($zoneline ? "" : (defined $zonedef{$zonename} ? $zonedef{$zonename} . "\n" : "")) . $outline;
    }
}

sub omit_unused_rules {
    for (my $i = 0; $i < $nrule_out; $i++) {
        my ($n, $field) = awk_split($rule_output_line[$i]);
        if (!$rule_used{defined $field->{2} ? $field->{2} : ''}) {
            $rule_output_line[$i] = "";
        }
    }
}

sub abbreviate_rule_names {
    for (my $i = 0; $i < $nrule_out; $i++) {
        my ($n, $field) = awk_split($rule_output_line[$i]);
        if ($n) {
            my $r = defined $field->{2} ? $field->{2} : '';
            if ($r ne '' && $r =~ /^[^-+0-9]/) {
                my $abbr = $rule{$r};
                if (!$abbr) {
                    $abbr = $rule{$r} = gen_rule_name($r);
                }
                $field->{2} = $abbr;
                $rule_output_line[$i] = make_line($n, $field);
            }
        }
    }
    for my $zn (keys %zonedef) {
        my @zonelines = split /\n/, $zonedef{$zn}, -1;
        my $newdef = "";
        for (my $i = 0; $i <= $#zonelines; $i++) {
            my $newline = $zonelines[$i];
            my ($n, $field) = awk_split($newline);
            my $f = ($i == 0) ? 4 : 2;
            my $r = defined $field->{$f} ? ($rule{$field->{$f}} // '') : '';
            if ($r ne '') {
                $field->{$f} = $r;
                $newline = make_line($n, $field);
            }
            $newdef = ($newdef ne "" ? $newdef . "\n" : "") . $newline;
        }
        $zonedef{$zn} = $newdef;
    }
}

sub output_saved_lines {
    for (my $i = 0; $i < $nrule_out; $i++) {
        print "$rule_output_line[$i]\n" if $rule_output_line[$i] ne "";
    }

    # This project's build runs under gawk, which (per the original script)
    # sorts zone output by name for better compressibility.
    for my $zn (sort keys %zonedef) {
        print "$zonedef{$zn}\n";
    }

    if ($nlink_out) {
        for (my $i = 0; $i < $nlink_out; $i++) {
            print "$link_output_line[$i]\n";
        }
    } else {
        # Under gawk, output links sorted by destination (value), which
        # also helps compressibility a bit.  Ties are broken by index
        # (zone name) ascending, matching gawk's @val_type_asc order.
        for my $zn (sort { $linkdef{$a} cmp $linkdef{$b} || $a cmp $b } keys %linkdef) {
            printf "L %s %s\n", $linkdef{$zn}, $zn;
        }
    }
}

# --- BEGIN block equivalent ---

# Files that the output normally depends on.
my %default_dep = map { $_ => 1 } qw(
    africa antarctica asia australasia backward etcetera europe factory
    northamerica southamerica ziguard.awk zishrink.awk
);

my ($ndeps, $dep) = awk_split($deps);
my $ddeps = "";
for (my $i = 1; $i <= $ndeps; $i++) {
    my $d = $dep->{$i};
    if ($default_dep{$d}) {
        $default_dep{$d}++;
    } else {
        $ddeps .= " $d";
    }
}
for my $d (keys %default_dep) {
    if ($default_dep{$d} == 1) {
        $ddeps .= " !$d";
    }
}
print "# version $version\n";
if ($dataform ne "main") {
    print "# dataform $dataform\n";
}
if ($redo ne "posix_right") {
    print "# redo $redo\n";
}
if ($ddeps ne "") {
    print "# ddeps$ddeps\n";
}
print "# This zic input file is in the public domain.\n";

prehash_rule_names();

# --- Main record-processing loop ---

while (my $raw = <>) {
    chomp $raw;
    if ($raw =~ /^[\t ]*[^#\t ]/) {
        process_input_line($raw);
    }
}

omit_unused_rules();
abbreviate_rule_names();
output_saved_lines();
