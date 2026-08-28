# PeteleOS: tests/lib/libssl/symbols/symbols.pl, time wirte: 2026/08/26
# This file uses the Apache-2.0 license
#
# Converted from symbols.awk to Perl.
#
# $OpenBSD: symbols.awk,v 1.4 2024/05/08 06:54:43 tb Exp $
#
# Copyright (c) 2018,2020,2023 Theo Buehler <tb@openbsd.org>
#
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
# ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
# OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

# usage: perl symbols.pl < Symbols.list > symbols.c

use strict;
use warnings;

print "#include <stdio.h>\n\n";

print "#include <openssl/dtls1.h>\n";
print "#include <openssl/ssl.h>\n";
print "#include <openssl/tls1.h>\n\n";

print "#include <openssl/srtp.h>\n\n";		# depends on ssl.h

my %symbols;

while (my $line = <>) {
	chomp $line;
	$symbols{$line} = $line;

	# Undefine aliases, so we don't accidentally leave them in Symbols.list.
	printf("#ifdef %s\n#undef %s\n#endif\n", $line, $line);
}

print "\nint\nmain(void)\n{\n";
print "\tsize_t i;\n";

print "\tstruct {\n";
print "\t\tconst char *const name;\n";
print "\t\tconst void *addr;\n";
print "\t} symbols[] = {\n";

for my $symbol (keys %symbols) {
	print "\t\t{\n";
	printf("\t\t\t.name = \"%s\",\n", $symbol);
	printf("\t\t\t.addr = &%s,\n", $symbol);
	print "\t\t},\n";
}

print "\t\};\n\n";

print "\tfor (i = 0; i < sizeof(symbols) / sizeof(symbols[0]); i++)\n";
print "\t\tfprintf(stderr, \"%s: %p\\n\", symbols[i].name, symbols[i].addr);\n";
print "\n\tprintf(\"OK\\n\");\n";
print "\n\treturn 0;\n}\n";
