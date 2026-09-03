#!/usr/bin/perl
#   PeteleOS: resources/tmac/strip.pl, time write: 2026/09/03
#   This file uses the Apache-2.0 license
#   
#	$OpenBSD: strip.sed,v 1.2 2003/06/02 23:30:16 millert Exp $
#
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. Neither the name of the University nor the names of its contributors
#    may be used to endorse or promote products derived from this software
#    without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
#
#	@(#)strip.sed	8.1 (Berkeley) 6/8/93
#
# Perl re-implementation of strip.sed (see git history for the sed original).
# Behavior verified byte-for-byte identical against the sed version on
# doc, doc-ditroff, doc-common, doc-nroff, doc-syms.
#
my $seen = 0;
while (<>) {
    if (/%beginstrip%/ && !$seen) {
        $seen = 1;
        print ".\\\" This version has had comments stripped; an unstripped version is available.\n";
    }
    s/[. \t][ \t]*\\".*// if $seen;   # NOTE: '.' must be in the character class
    next if /^$/;
    next if /\\n@/;
    print;
}
