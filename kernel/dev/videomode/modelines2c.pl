# EteleOS: kernel/dev/videomode/modelines2c.pl, time wirte: 2026/08/26
# This file uses the Apache-2.0 license
#
#	$NetBSD: modelines2c.awk,v 1.5 2011/03/21 19:32:26 jdc Exp $
#	$OpenBSD: modelines2c.awk,v 1.3 2024/11/06 09:34:10 miod Exp $
#
# Copyright (c) 2006 Itronix Inc.
# All rights reserved.
#
# Written by Garrett D'Amore for Itronix Inc.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. The name of Itronix Inc. may not be used to endorse
#    or promote products derived from this software without specific
#    prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY ITRONIX INC. ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
# TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL ITRONIX INC. BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#

use strict;
use warnings;
no warnings 'uninitialized';

my $nmodes = 0;
my @dmodes;
my $nr = 0;

while (my $line = <>) {
	chomp $line;
	$nr++;

	if ($nr == 1) {
		my @v = split(/\$/, $line);
		my $version = $v[1];

		print "/*\t\$OpenBSD" . "\$\t*/\n\n";
		print "/*\n";
		print " * THIS FILE AUTOMATICALLY GENERATED.  DO NOT EDIT.\n";
		print " *\n";
		print " * generated from:\n";
		printf(" *\t%s\n", $version);
		print " */\n\n";

		print "#include <sys/types.h>\n";

		print "#include <dev/videomode/videomode.h>\n\n";

		print "/*\n";
		print " * These macros help the modelines below fit on one line.\n";
		print " */\n";
		print "#define HP VID_PHSYNC\n";
		print "#define HN VID_NHSYNC\n";
		print "#define VP VID_PVSYNC\n";
		print "#define VN VID_NVSYNC\n";
		print "#define I VID_INTERLACE\n";
		print "#define DS VID_DBLSCAN\n";
		print "\n";

		print "#define M(nm,hr,vr,clk,hs,he,ht,vs,ve,vt,f) \\\n";
		print "\t{ clk, hr, hs, he, ht, vr, vs, ve, vt, f, nm } \n\n";

		print "const struct videomode videomode_list[] = {\n";

		next;
	}

	if ($line =~ /^ModeLine/) {
		my @f = split(' ', $line);

		my $dotclock =   $f[2];

		my $hdisplay =   $f[3];
		my $hsyncstart = $f[4];
		my $hsyncend =   $f[5];
		my $htotal =     $f[6];

		my $vdisplay =   $f[7];
		my $vsyncstart = $f[8];
		my $vsyncend =   $f[9];
		my $vtotal =     $f[10];

		my $iflag =      "";
		my $iflags =     "";
		my $hflags =     "HP";
		my $vflags =     "VP";

		if ($f[11] =~ /^-/) {
			$hflags = "HN";
		}

		if ($f[12] =~ /^-/) {
			$vflags = "VN";
		}

		my $ifactor = 1.0;
		if ($f[13] =~ /[Ii][Nn][Tt][Ee][Rr][Ll][Aa][Cc][Ee]/) {
			$iflag = "i";
			$iflags = "|I";
			$ifactor = 2.0;
		}

		# We truncate the vrefresh figure, but some mode descriptions rely
		# on rounding, so we can't win here.  Adding an additional .1
		# compensates to some extent.

		my $hrefresh = ($dotclock * 1000000) / $htotal;
		my $vrefresh = int((($hrefresh * $ifactor) / $vtotal) + .1);

		my $modestr = sprintf("%dx%dx%d%s", $hdisplay, $vdisplay, $vrefresh, $iflag);

		printf("M(\"%s\",%d,%d,%d,%d,%d,%d,%d,%d,%d,%s),\n",
		    $modestr,
		    $hdisplay, $vdisplay, $dotclock * 1000,
		    $hsyncstart, $hsyncend, $htotal,
		    $vsyncstart, $vsyncend, $vtotal, $hflags . "|" . $vflags . $iflags);

		$modestr = sprintf("%dx%dx%d%s",
		    $hdisplay/2 , $vdisplay/2, $vrefresh, $iflag);

		$dmodes[$nmodes] = sprintf("M(\"%s\",%d,%d,%d,%d,%d,%d,%d,%d,%d,%s),",
		    $modestr,
		    $hdisplay/2, $vdisplay/2, $dotclock * 1000 / 2,
		    $hsyncstart/2, $hsyncend/2, $htotal/2,
		    $vsyncstart/2, $vsyncend/2, $vtotal/2,
		    $hflags . "|" . $vflags . "|DS" . $iflags);

		$nmodes = $nmodes + 1;
	}
}

print "\n/* Derived Double Scan Modes */\n\n";

for (my $i = 0; $i < $nmodes; $i++) {
	print "$dmodes[$i]\n";
}

print "};\n\n";
printf("const int videomode_count = %d;\n", $nmodes);
