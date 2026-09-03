#!/usr/bin/perl
#
# PeteleOS: userland/network/httpd/toheader.pl, time write: 2026/09/03
# This file uses the Apache-2.0 license
#
# toheader.pl - replaces toheader.sed
#
# Converts a text input file into a C array-of-strings fragment
# (used to embed css.h.in / js.h.in into server_file.c as css.h / js.h).
#
# Equivalent to the original sed script:
#
#   # first line of input is the variable declaration, don't touch that
#   2,$ {
#   # XXX beware of the order ! we have to quote \ and " before inserting \n"
#           s/\\/\\\\/g
#           s/"/\\"/g
#           s/^/    "/
#           s/$/\\n"/
#   }
#   # and append a ; at the end !
#   $s/$/;/
#
my @lines = <>;
for (my $i = 0; $i <= $#lines; $i++) {
    $_ = $lines[$i];
    if ($i == 0) { print; next }
    chomp;
    s/\\/\\\\/g;
    s/"/\\"/g;
    my $out = "    \"$_\\n\"";
    $out .= ";" if $i == $#lines;   # equivalent to sed's $s/$/;/
    print "$out\n";
}
