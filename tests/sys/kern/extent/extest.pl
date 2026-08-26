# EteleOS: tests/sys/kern/extent/extest.pl, time wirte: 2026/08/26
# This file uses the Apache-2.0 license
#
# Converted from extest.awk to Perl.
#
# $OpenBSD: extest.awk,v 1.3 2019/09/11 12:30:34 kettenis Exp $
# $NetBSD: extest.awk,v 1.6 2002/02/21 03:59:25 mrg Exp $

use strict;
use warnings;

my $first = 1;
my $align = "EX_NOALIGN";
my $boundary = "EX_NOBOUNDARY";
my $flags = "0";

print "#include <sys/types.h>\n";
print "#include <sys/extent.h>\n\n";
print "#include <stdio.h>\n";
print "#include <stdlib.h>\n";
print "#include <string.h>\n";
print "int main(void) {\n";
print "struct extent *ex; int error; long result;\n";

while (my $line = <>) {
	chomp $line;
	my @f = split(' ', $line);
	next unless @f;

	if ($f[0] eq "extent") {
		if ($first == 0) {
			print "extent_destroy(ex);\n";
		}

		$align = "EX_NOALIGN";
		$boundary = "EX_NOBOUNDARY";

		printf("printf(\"output for %s\\n\");\n", $f[1]);

		if (!defined($f[4]) || $f[4] eq "") {
			$flags = "0";
		} else {
			$flags = $f[4];
		}
		printf("ex = extent_create(\"%s\", %s, %s, 0, 0, 0, %s);\n",
		       $f[1], $f[2], $f[3], $flags);

		$first = 0;
	} elsif ($f[0] eq "align") {
		$align = $f[1];
	} elsif ($f[0] eq "boundary") {
		$boundary = $f[1];
	} elsif ($f[0] eq "alloc_region") {
		if (!defined($f[3]) || $f[3] eq "") {
			$flags = "0";
		} else {
			$flags = $f[3];
		}
		printf("error = extent_alloc_region(ex, %s, %s, %s);\n",
		       $f[1], $f[2], $flags);
		print "if (error)\n\tprintf(\"error: %s\\n\", strerror(error));\n";
	} elsif ($f[0] eq "alloc_subregion") {
		printf("error = extent_alloc_subregion(ex, %s, %s, %s,\n",
		       $f[1], $f[2], $f[3]);
		printf("\t%s, 0, %s, 0, &result);\n", $align, $boundary);
		print "if (error)\n\tprintf(\"error: %s\\n\", strerror(error));\n";
		print "else\n\tprintf(\"result: 0x%lx\\n\", result);\n";
	} elsif ($f[0] eq "free") {
		if (!defined($f[3]) || $f[3] eq "") {
			$flags = "0";
		} else {
			$flags = $f[3];
		}
		printf("error = extent_free(ex, %s, %s, %s);\n", $f[1], $f[2], $flags);
		print "if (error)\n\tprintf(\"error: %s\\n\", strerror(error));\n";
	} elsif ($f[0] eq "print") {
		print "extent_print(ex);\n";
	}
}

print "exit (0);\n";
print "}\n";
