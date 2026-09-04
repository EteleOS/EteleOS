/*-
 * PeteleOS: libraries/core/libelf/gen_libelf.c, time write: 2026/09/03
 * This file uses the Apache-2.0 license
 */

/*
 * Host generator replacing m4 for libelf.
 *
 * Follows the HOSTCC pattern used by kernel/arch/amd64/conf/Makefile.amd64
 * and kernel/core/kern/genassym.sh: compiled with $(HOSTCC) and run on the
 * build host to emit libelf_msize.c, libelf_fsize.c, libelf_convert.c
 * byte-identical to the former m4 output.
 *
 * Usage: gen_libelf {msize|fsize|convert} [output-file]
 *   With no output-file, writes to stdout.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#endif

#include "elf_types_data.h"


static const char msize_prefix[] =
	"/*-\n"
	" * Copyright (c) 2006,2008-2011 Joseph Koshy\n"
	" * All rights reserved.\n"
	" *\n"
	" * Redistribution and use in source and binary forms, with or without\n"
	" * modification, are permitted provided that the following conditions\n"
	" * are met:\n"
	" * 1. Redistributions of source code must retain the above copyright\n"
	" *    notice, this list of conditions and the following disclaimer.\n"
	" * 2. Redistributions in binary form must reproduce the above copyright\n"
	" *    notice, this list of conditions and the following disclaimer in the\n"
	" *    documentation and/or other materials provided with the distribution.\n"
	" *\n"
	" * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS `AS IS' AND\n"
	" * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE\n"
	" * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE\n"
	" * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE\n"
	" * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL\n"
	" * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS\n"
	" * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)\n"
	" * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT\n"
	" * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY\n"
	" * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF\n"
	" * SUCH DAMAGE.\n"
	" */\n"
	"\n"
	"#include <assert.h>\n"
	"#include <libelf.h>\n"
	"#include <string.h>\n"
	"\n"
	"#include \"_libelf.h\"\n"
	"\n"
	"ELFTC_VCSID(\"$Id: libelf_msize.m4,v 1.2 2020/05/18 06:46:23 jsg Exp $\");\n"
	"\n"
	"/* WARNING: GENERATED FROM libelf_msize.m4. */\n"
	"\n"
	"struct msize {\n"
	"\tsize_t\tmsz32;\n"
	"\tsize_t\tmsz64;\n"
	"};\n"
	"\n"
	"\n"
	"\n"
	"static struct msize msize[ELF_T_NUM] = {\n";

static const char msize_suffix[] =
	"\n"
	"};\n"
	"\n"
	"/*\n"
	" * Returns the memory size of the specified ELF type 't' of ELF\n"
	" * class 'ec' and ELF version 'version'.\n"
	" *\n"
	" * If the specified combination of ELF type, class, and version is\n"
	" * unsupported then a value of 0 will be returned and the appropriate\n"
	" * library error code set.\n"
	" */\n"
	"size_t\n"
	"_libelf_msize(Elf_Type t, int elfclass, unsigned int version)\n"
	"{\n"
	"\tsize_t sz;\n"
	"\n"
	"\tassert(elfclass == ELFCLASS32 || elfclass == ELFCLASS64);\n"
	"\tassert((signed) t >= ELF_T_FIRST && t <= ELF_T_LAST);\n"
	"\n"
	"\tif (version != EV_CURRENT) {\n"
	"\t\tLIBELF_SET_ERROR(VERSION, 0);\n"
	"\t\treturn (0);\n"
	"\t}\n"
	"\n"
	"\tsz = (elfclass == ELFCLASS32) ? msize[t].msz32 : msize[t].msz64;\n"
	"\n"
	"\tif (sz == 0) {\n"
	"\t\tLIBELF_SET_ERROR(UNIMPL, 0);\n"
	"\t\treturn (0);\n"
	"\t}\n"
	"\n"
	"\treturn (sz);\n"
	"}\n";

static const char fsize_prefix[] =
	"/*-\n"
	" * Copyright (c) 2006,2008-2011 Joseph Koshy\n"
	" * All rights reserved.\n"
	" *\n"
	" * Redistribution and use in source and binary forms, with or without\n"
	" * modification, are permitted provided that the following conditions\n"
	" * are met:\n"
	" * 1. Redistributions of source code must retain the above copyright\n"
	" *    notice, this list of conditions and the following disclaimer.\n"
	" * 2. Redistributions in binary form must reproduce the above copyright\n"
	" *    notice, this list of conditions and the following disclaimer in the\n"
	" *    documentation and/or other materials provided with the distribution.\n"
	" *\n"
	" * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS `AS IS' AND\n"
	" * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE\n"
	" * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE\n"
	" * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE\n"
	" * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL\n"
	" * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS\n"
	" * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)\n"
	" * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT\n"
	" * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY\n"
	" * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF\n"
	" * SUCH DAMAGE.\n"
	" */\n"
	"\n"
	"#include <libelf.h>\n"
	"\n"
	"#include \"_libelf.h\"\n"
	"\n"
	"ELFTC_VCSID(\"$Id: libelf_fsize.m4,v 1.1 2019/02/01 05:27:38 jsg Exp $\");\n"
	"\n"
	"/* WARNING: GENERATED FROM libelf_fsize.m4. */\n"
	"\n"
	"/*\n"
	" * Create an array of file sizes from the elf_type definitions\n"
	" */\n"
	"\n"
	"\n"
	"\n"
	"struct fsize {\n"
	"\tsize_t fsz32;\n"
	"\tsize_t fsz64;\n"
	"};\n"
	"\n"
	"static struct fsize fsize[ELF_T_NUM] = {\n";

static const char fsize_suffix[] =
	"\n"
	"};\n"
	"\n"
	"size_t\n"
	"_libelf_fsize(Elf_Type t, int ec, unsigned int v, size_t c)\n"
	"{\n"
	"\tsize_t sz;\n"
	"\n"
	"\tsz = 0;\n"
	"\tif (v != EV_CURRENT)\n"
	"\t\tLIBELF_SET_ERROR(VERSION, 0);\n"
	"\telse if ((int) t < ELF_T_FIRST || t > ELF_T_LAST)\n"
	"\t\tLIBELF_SET_ERROR(ARGUMENT, 0);\n"
	"\telse {\n"
	"\t\tsz = ec == ELFCLASS64 ? fsize[t].fsz64 : fsize[t].fsz32;\n"
	"\t\tif (sz == 0)\n"
	"\t\t\tLIBELF_SET_ERROR(UNIMPL, 0);\n"
	"\t}\n"
	"\n"
	"\treturn (sz*c);\n"
	"}\n";

static const char convert_prefix[] =
	"/*-\n"
	" * Copyright (c) 2006-2011 Joseph Koshy\n"
	" * All rights reserved.\n"
	" *\n"
	" * Redistribution and use in source and binary forms, with or without\n"
	" * modification, are permitted provided that the following conditions\n"
	" * are met:\n"
	" * 1. Redistributions of source code must retain the above copyright\n"
	" *    notice, this list of conditions and the following disclaimer.\n"
	" * 2. Redistributions in binary form must reproduce the above copyright\n"
	" *    notice, this list of conditions and the following disclaimer in the\n"
	" *    documentation and/or other materials provided with the distribution.\n"
	" *\n"
	" * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS `AS IS' AND\n"
	" * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE\n"
	" * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE\n"
	" * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE\n"
	" * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL\n"
	" * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS\n"
	" * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)\n"
	" * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT\n"
	" * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY\n"
	" * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF\n"
	" * SUCH DAMAGE.\n"
	" */\n"
	"\n"
	"#include <assert.h>\n"
	"#include <libelf.h>\n"
	"#include <string.h>\n"
	"#include <stdint.h>\n"
	"\n"
	"#include \"_libelf.h\"\n"
	"\n"
	"ELFTC_VCSID(\"$Id: libelf_convert.m4,v 1.3 2020/05/18 06:46:23 jsg Exp $\");\n"
	"\n"
	"/* WARNING: GENERATED FROM libelf_convert.m4. */\n"
	"\n"
	"\n"
	"\n"
	"/*\n"
	" * C macros to byte swap integral quantities.\n"
	" */\n"
	"\n"
	"#define\tSWAP_BYTE(X)\tdo { (void) (X); } while (0)\n"
	"#define\tSWAP_IDENT(X)\tdo { (void) (X); } while (0)\n"
	"#define\tSWAP_HALF(X)\tdo {\t\t\t\t\t\t\\\n"
	"\t\tuint16_t _x = (uint16_t) (X);\t\t\t\t\\\n"
	"\t\tuint32_t _t = _x & 0xFFU;\t\t\t\t\\\n"
	"\t\t_t <<= 8U; _x >>= 8U; _t |= _x & 0xFFU;\t\t\t\\\n"
	"\t\t(X) = (uint16_t) _t;\t\t\t\t\t\\\n"
	"\t} while (0)\n"
	"#define\t_SWAP_WORD(X, T) do {\t\t\t\t\t\t\\\n"
	"\t\tuint32_t _x = (uint32_t) (X);\t\t\t\t\\\n"
	"\t\tuint32_t _t = _x & 0xFF;\t\t\t\t\\\n"
	"\t\t_t <<= 8; _x >>= 8; _t |= _x & 0xFF;\t\t\t\\\n"
	"\t\t_t <<= 8; _x >>= 8; _t |= _x & 0xFF;\t\t\t\\\n"
	"\t\t_t <<= 8; _x >>= 8; _t |= _x & 0xFF;\t\t\t\\\n"
	"\t\t(X) = (T) _t;\t\t\t\t\t\t\\\n"
	"\t} while (0)\n"
	"#define\tSWAP_ADDR32(X)\t_SWAP_WORD(X, Elf32_Addr)\n"
	"#define\tSWAP_OFF32(X)\t_SWAP_WORD(X, Elf32_Off)\n"
	"#define\tSWAP_SWORD(X)\t_SWAP_WORD(X, Elf32_Sword)\n"
	"#define\tSWAP_WORD(X)\t_SWAP_WORD(X, Elf32_Word)\n"
	"#define\t_SWAP_WORD64(X, T) do {\t\t\t\t\t\t\\\n"
	"\t\tuint64_t _x = (uint64_t) (X);\t\t\t\t\\\n"
	"\t\tuint64_t _t = _x & 0xFF;\t\t\t\t\\\n"
	"\t\t_t <<= 8; _x >>= 8; _t |= _x & 0xFF;\t\t\t\\\n"
	"\t\t_t <<= 8; _x >>= 8; _t |= _x & 0xFF;\t\t\t\\\n"
	"\t\t_t <<= 8; _x >>= 8; _t |= _x & 0xFF;\t\t\t\\\n"
	"\t\t_t <<= 8; _x >>= 8; _t |= _x & 0xFF;\t\t\t\\\n"
	"\t\t_t <<= 8; _x >>= 8; _t |= _x & 0xFF;\t\t\t\\\n"
	"\t\t_t <<= 8; _x >>= 8; _t |= _x & 0xFF;\t\t\t\\\n"
	"\t\t_t <<= 8; _x >>= 8; _t |= _x & 0xFF;\t\t\t\\\n"
	"\t\t(X) = (T) _t;\t\t\t\t\t\t\\\n"
	"\t} while (0)\n"
	"#define\tSWAP_ADDR64(X)\t_SWAP_WORD64(X, Elf64_Addr)\n"
	"#define\tSWAP_LWORD(X)\t_SWAP_WORD64(X, Elf64_Lword)\n"
	"#define\tSWAP_OFF64(X)\t_SWAP_WORD64(X, Elf64_Off)\n"
	"#define\tSWAP_SXWORD(X)\t_SWAP_WORD64(X, Elf64_Sxword)\n"
	"#define\tSWAP_XWORD(X)\t_SWAP_WORD64(X, Elf64_Xword)\n"
	"\n"
	"/*\n"
	" * C macros to write out various integral values.\n"
	" *\n"
	" * Note:\n"
	" * - The destination pointer could be unaligned.\n"
	" * - Values are written out in native byte order.\n"
	" * - The destination pointer is incremented after the write.\n"
	" */\n"
	"#define\tWRITE_BYTE(P,X) do {\t\t\t\t\t\t\\\n"
	"\t\tunsigned char *const _p = (unsigned char *) (P);\t\\\n"
	"\t\t_p[0]\t\t= (unsigned char) (X);\t\t\t\\\n"
	"\t\t(P)\t\t= _p + 1;\t\t\t\t\\\n"
	"\t} while (0)\n"
	"#define\tWRITE_HALF(P,X)\tdo {\t\t\t\t\t\t\\\n"
	"\t\tuint16_t _t\t= (X);\t\t\t\t\t\\\n"
	"\t\tunsigned char *const _p\t= (unsigned char *) (P);\t\\\n"
	"\t\tconst unsigned char *const _q = (unsigned char *) &_t;\t\\\n"
	"\t\t_p[0]\t\t= _q[0];\t\t\t\t\\\n"
	"\t\t_p[1]\t\t= _q[1];\t\t\t\t\\\n"
	"\t\t(P)\t\t= _p + 2;\t\t\t\t\\\n"
	"\t} while (0)\n"
	"#define\tWRITE_WORD(P,X) do {\t\t\t\t\t\t\\\n"
	"\t\tuint32_t _t\t= (uint32_t) (X);\t\t\t\\\n"
	"\t\tunsigned char *const _p\t= (unsigned char *) (P);\t\\\n"
	"\t\tconst unsigned char *const _q = (unsigned char *) &_t;\t\\\n"
	"\t\t_p[0]\t\t= _q[0];\t\t\t\t\\\n"
	"\t\t_p[1]\t\t= _q[1];\t\t\t\t\\\n"
	"\t\t_p[2]\t\t= _q[2];\t\t\t\t\\\n"
	"\t\t_p[3]\t\t= _q[3];\t\t\t\t\\\n"
	"\t\t(P)\t\t= _p + 4;\t\t\t\t\\\n"
	"\t} while (0)\n"
	"#define\tWRITE_ADDR32(P,X)\tWRITE_WORD(P,X)\n"
	"#define\tWRITE_OFF32(P,X)\tWRITE_WORD(P,X)\n"
	"#define\tWRITE_SWORD(P,X)\tWRITE_WORD(P,X)\n"
	"#define\tWRITE_WORD64(P,X)\tdo {\t\t\t\t\t\\\n"
	"\t\tuint64_t _t\t= (uint64_t) (X);\t\t\t\\\n"
	"\t\tunsigned char *const _p\t= (unsigned char *) (P);\t\\\n"
	"\t\tconst unsigned char *const _q = (unsigned char *) &_t;\t\\\n"
	"\t\t_p[0]\t\t= _q[0];\t\t\t\t\\\n"
	"\t\t_p[1]\t\t= _q[1];\t\t\t\t\\\n"
	"\t\t_p[2]\t\t= _q[2];\t\t\t\t\\\n"
	"\t\t_p[3]\t\t= _q[3];\t\t\t\t\\\n"
	"\t\t_p[4]\t\t= _q[4];\t\t\t\t\\\n"
	"\t\t_p[5]\t\t= _q[5];\t\t\t\t\\\n"
	"\t\t_p[6]\t\t= _q[6];\t\t\t\t\\\n"
	"\t\t_p[7]\t\t= _q[7];\t\t\t\t\\\n"
	"\t\t(P)\t\t= _p + 8;\t\t\t\t\\\n"
	"\t} while (0)\n"
	"#define\tWRITE_ADDR64(P,X)\tWRITE_WORD64(P,X)\n"
	"#define\tWRITE_LWORD(P,X)\tWRITE_WORD64(P,X)\n"
	"#define\tWRITE_OFF64(P,X)\tWRITE_WORD64(P,X)\n"
	"#define\tWRITE_SXWORD(P,X)\tWRITE_WORD64(P,X)\n"
	"#define\tWRITE_XWORD(P,X)\tWRITE_WORD64(P,X)\n"
	"#define\tWRITE_IDENT(P,X)\tdo {\t\t\t\t\t\\\n"
	"\t\t(void) memcpy((P), (X), sizeof((X)));\t\t\t\\\n"
	"\t\t(P)\t\t= (P) + EI_NIDENT;\t\t\t\\\n"
	"\t} while (0)\n"
	"\n"
	"/*\n"
	" * C macros to read in various integral values.\n"
	" *\n"
	" * Note:\n"
	" * - The source pointer could be unaligned.\n"
	" * - Values are read in native byte order.\n"
	" * - The source pointer is incremented appropriately.\n"
	" */\n"
	"\n"
	"#define\tREAD_BYTE(P,X)\tdo {\t\t\t\t\t\t\\\n"
	"\t\tconst unsigned char *const _p =\t\t\t\t\\\n"
	"\t\t\t(const unsigned char *) (P);\t\t\t\\\n"
	"\t\t(X)\t\t= _p[0];\t\t\t\t\\\n"
	"\t\t(P)\t\t= (P) + 1;\t\t\t\t\\\n"
	"\t} while (0)\n"
	"#define\tREAD_HALF(P,X)\tdo {\t\t\t\t\t\t\\\n"
	"\t\tuint16_t _t;\t\t\t\t\t\t\\\n"
	"\t\tunsigned char *const _q = (unsigned char *) &_t;\t\\\n"
	"\t\tconst unsigned char *const _p =\t\t\t\t\\\n"
	"\t\t\t(const unsigned char *) (P);\t\t\t\\\n"
	"\t\t_q[0]\t\t= _p[0];\t\t\t\t\\\n"
	"\t\t_q[1]\t\t= _p[1];\t\t\t\t\\\n"
	"\t\t(P)\t\t= (P) + 2;\t\t\t\t\\\n"
	"\t\t(X)\t\t= _t;\t\t\t\t\t\\\n"
	"\t} while (0)\n"
	"#define\t_READ_WORD(P,X,T) do {\t\t\t\t\t\t\\\n"
	"\t\tuint32_t _t;\t\t\t\t\t\t\\\n"
	"\t\tunsigned char *const _q = (unsigned char *) &_t;\t\\\n"
	"\t\tconst unsigned char *const _p =\t\t\t\t\\\n"
	"\t\t\t(const unsigned char *) (P);\t\t\t\\\n"
	"\t\t_q[0]\t\t= _p[0];\t\t\t\t\\\n"
	"\t\t_q[1]\t\t= _p[1];\t\t\t\t\\\n"
	"\t\t_q[2]\t\t= _p[2];\t\t\t\t\\\n"
	"\t\t_q[3]\t\t= _p[3];\t\t\t\t\\\n"
	"\t\t(P)\t\t= (P) + 4;\t\t\t\t\\\n"
	"\t\t(X)\t\t= (T) _t;\t\t\t\t\\\n"
	"\t} while (0)\n"
	"#define\tREAD_ADDR32(P,X)\t_READ_WORD(P, X, Elf32_Addr)\n"
	"#define\tREAD_OFF32(P,X)\t\t_READ_WORD(P, X, Elf32_Off)\n"
	"#define\tREAD_SWORD(P,X)\t\t_READ_WORD(P, X, Elf32_Sword)\n"
	"#define\tREAD_WORD(P,X)\t\t_READ_WORD(P, X, Elf32_Word)\n"
	"#define\t_READ_WORD64(P,X,T)\tdo {\t\t\t\t\t\\\n"
	"\t\tuint64_t _t;\t\t\t\t\t\t\\\n"
	"\t\tunsigned char *const _q = (unsigned char *) &_t;\t\\\n"
	"\t\tconst unsigned char *const _p =\t\t\t\t\\\n"
	"\t\t\t(const unsigned char *) (P);\t\t\t\\\n"
	"\t\t_q[0]\t\t= _p[0];\t\t\t\t\\\n"
	"\t\t_q[1]\t\t= _p[1];\t\t\t\t\\\n"
	"\t\t_q[2]\t\t= _p[2];\t\t\t\t\\\n"
	"\t\t_q[3]\t\t= _p[3];\t\t\t\t\\\n"
	"\t\t_q[4]\t\t= _p[4];\t\t\t\t\\\n"
	"\t\t_q[5]\t\t= _p[5];\t\t\t\t\\\n"
	"\t\t_q[6]\t\t= _p[6];\t\t\t\t\\\n"
	"\t\t_q[7]\t\t= _p[7];\t\t\t\t\\\n"
	"\t\t(P)\t\t= (P) + 8;\t\t\t\t\\\n"
	"\t\t(X)\t\t= (T) _t;\t\t\t\t\\\n"
	"\t} while (0)\n"
	"#define\tREAD_ADDR64(P,X)\t_READ_WORD64(P, X, Elf64_Addr)\n"
	"#define\tREAD_LWORD(P,X)\t\t_READ_WORD64(P, X, Elf64_Lword)\n"
	"#define\tREAD_OFF64(P,X)\t\t_READ_WORD64(P, X, Elf64_Off)\n"
	"#define\tREAD_SXWORD(P,X)\t_READ_WORD64(P, X, Elf64_Sxword)\n"
	"#define\tREAD_XWORD(P,X)\t\t_READ_WORD64(P, X, Elf64_Xword)\n"
	"#define\tREAD_IDENT(P,X)\t\tdo {\t\t\t\t\t\\\n"
	"\t\t(void) memcpy((X), (P), sizeof((X)));\t\t\t\\\n"
	"\t\t(P)\t\t= (P) + EI_NIDENT;\t\t\t\\\n"
	"\t} while (0)\n"
	"\n"
	"#define\tROUNDUP2(V,N)\t(V) = ((((V) + (N) - 1)) & ~((N) - 1))\n"
	"\n"
	"/*[*/\n";

static const char convert_middle[] =
	"/*]*/\n"
	"\n"
	"/*\n"
	" * Sections of type ELF_T_BYTE are never byteswapped, consequently a\n"
	" * simple memcpy suffices for both directions of conversion.\n"
	" */\n"
	"\n"
	"static int\n"
	"_libelf_cvt_BYTE_tox(unsigned char *dst, size_t dsz, unsigned char *src,\n"
	"    size_t count, int byteswap)\n"
	"{\n"
	"\t(void) byteswap;\n"
	"\tif (dsz < count)\n"
	"\t\treturn (0);\n"
	"\tif (dst != src)\n"
	"\t\t(void) memcpy(dst, src, count);\n"
	"\treturn (1);\n"
	"}\n"
	"\n"
	"/*\n"
	" * Sections of type ELF_T_GNUHASH start with a header containing 4 32-bit\n"
	" * words.  Bloom filter data comes next, followed by hash buckets and the\n"
	" * hash chain.\n"
	" *\n"
	" * Bloom filter words are 64 bit wide on ELFCLASS64 objects and are 32 bit\n"
	" * wide on ELFCLASS32 objects.  The other objects in this section are 32\n"
	" * bits wide.\n"
	" *\n"
	" * Argument srcsz denotes the number of bytes to be converted.  In the\n"
	" * 32-bit case we need to translate srcsz to a count of 32-bit words.\n"
	" */\n"
	"\n"
	"static int\n"
	"_libelf_cvt_GNUHASH32_tom(unsigned char *dst, size_t dsz, unsigned char *src,\n"
	"    size_t srcsz, int byteswap)\n"
	"{\n"
	"\treturn (_libelf_cvt_WORD_tom(dst, dsz, src, srcsz / sizeof(uint32_t),\n"
	"\t\tbyteswap));\n"
	"}\n"
	"\n"
	"static int\n"
	"_libelf_cvt_GNUHASH32_tof(unsigned char *dst, size_t dsz, unsigned char *src,\n"
	"    size_t srcsz, int byteswap)\n"
	"{\n"
	"\treturn (_libelf_cvt_WORD_tof(dst, dsz, src, srcsz / sizeof(uint32_t),\n"
	"\t\tbyteswap));\n"
	"}\n"
	"\n"
	"static int\n"
	"_libelf_cvt_GNUHASH64_tom(unsigned char *dst, size_t dsz, unsigned char *src,\n"
	"    size_t srcsz, int byteswap)\n"
	"{\n"
	"\tsize_t sz;\n"
	"\tuint64_t t64, *bloom64;\n"
	"\tElf_GNU_Hash_Header *gh;\n"
	"\tuint32_t n, nbuckets, nchains, maskwords, shift2, symndx, t32;\n"
	"\tuint32_t *buckets, *chains;\n"
	"\n"
	"\tsz = 4 * sizeof(uint32_t);\t/* File header is 4 words long. */\n"
	"\tif (dsz < sizeof(Elf_GNU_Hash_Header) || srcsz < sz)\n"
	"\t\treturn (0);\n"
	"\n"
	"\t/* Read in the section header and byteswap if needed. */\n"
	"\tREAD_WORD(src, nbuckets);\n"
	"\tREAD_WORD(src, symndx);\n"
	"\tREAD_WORD(src, maskwords);\n"
	"\tREAD_WORD(src, shift2);\n"
	"\n"
	"\tsrcsz -= sz;\n"
	"\n"
	"\tif (byteswap) {\n"
	"\t\tSWAP_WORD(nbuckets);\n"
	"\t\tSWAP_WORD(symndx);\n"
	"\t\tSWAP_WORD(maskwords);\n"
	"\t\tSWAP_WORD(shift2);\n"
	"\t}\n"
	"\n"
	"\t/* Check source buffer and destination buffer sizes. */\n"
	"\tsz = nbuckets * sizeof(uint32_t) + maskwords * sizeof(uint64_t);\n"
	"\tif (srcsz < sz || dsz < sz + sizeof(Elf_GNU_Hash_Header))\n"
	"\t\treturn (0);\n"
	"\n"
	"\tgh = (Elf_GNU_Hash_Header *) (uintptr_t) dst;\n"
	"\tgh->gh_nbuckets  = nbuckets;\n"
	"\tgh->gh_symndx    = symndx;\n"
	"\tgh->gh_maskwords = maskwords;\n"
	"\tgh->gh_shift2    = shift2;\n"
	"\n"
	"\tdsz -= sizeof(Elf_GNU_Hash_Header);\n"
	"\tdst += sizeof(Elf_GNU_Hash_Header);\n"
	"\n"
	"\tbloom64 = (uint64_t *) (uintptr_t) dst;\n"
	"\n"
	"\t/* Copy bloom filter data. */\n"
	"\tfor (n = 0; n < maskwords; n++) {\n"
	"\t\tREAD_XWORD(src, t64);\n"
	"\t\tif (byteswap)\n"
	"\t\t\tSWAP_XWORD(t64);\n"
	"\t\tbloom64[n] = t64;\n"
	"\t}\n"
	"\n"
	"\t/* The hash buckets follows the bloom filter. */\n"
	"\tdst += maskwords * sizeof(uint64_t);\n"
	"\tbuckets = (uint32_t *) (uintptr_t) dst;\n"
	"\n"
	"\tfor (n = 0; n < nbuckets; n++) {\n"
	"\t\tREAD_WORD(src, t32);\n"
	"\t\tif (byteswap)\n"
	"\t\t\tSWAP_WORD(t32);\n"
	"\t\tbuckets[n] = t32;\n"
	"\t}\n"
	"\n"
	"\tdst += nbuckets * sizeof(uint32_t);\n"
	"\n"
	"\t/* The hash chain follows the hash buckets. */\n"
	"\tdsz -= sz;\n"
	"\tsrcsz -= sz;\n"
	"\n"
	"\tif (dsz < srcsz)\t/* Destination lacks space. */\n"
	"\t\treturn (0);\n"
	"\n"
	"\tnchains = (uint32_t) (srcsz / sizeof(uint32_t));\n"
	"\tchains = (uint32_t *) (uintptr_t) dst;\n"
	"\n"
	"\tfor (n = 0; n < nchains; n++) {\n"
	"\t\tREAD_WORD(src, t32);\n"
	"\t\tif (byteswap)\n"
	"\t\t\tSWAP_WORD(t32);\n"
	"\t\t*chains++ = t32;\n"
	"\t}\n"
	"\n"
	"\treturn (1);\n"
	"}\n"
	"\n"
	"static int\n"
	"_libelf_cvt_GNUHASH64_tof(unsigned char *dst, size_t dsz, unsigned char *src,\n"
	"    size_t srcsz, int byteswap)\n"
	"{\n"
	"\tuint32_t *s32;\n"
	"\tsize_t sz, hdrsz;\n"
	"\tuint64_t *s64, t64;\n"
	"\tElf_GNU_Hash_Header *gh;\n"
	"\tuint32_t maskwords, n, nbuckets, nchains, t0, t1, t2, t3, t32;\n"
	"\n"
	"\thdrsz = 4 * sizeof(uint32_t);\t/* Header is 4x32 bits. */\n"
	"\tif (dsz < hdrsz || srcsz < sizeof(Elf_GNU_Hash_Header))\n"
	"\t\treturn (0);\n"
	"\n"
	"\tgh = (Elf_GNU_Hash_Header *) (uintptr_t) src;\n"
	"\n"
	"\tt0 = nbuckets = gh->gh_nbuckets;\n"
	"\tt1 = gh->gh_symndx;\n"
	"\tt2 = maskwords = gh->gh_maskwords;\n"
	"\tt3 = gh->gh_shift2;\n"
	"\n"
	"\tsrc   += sizeof(Elf_GNU_Hash_Header);\n"
	"\tsrcsz -= sizeof(Elf_GNU_Hash_Header);\n"
	"\tdsz   -= hdrsz;\n"
	"\n"
	"\tsz = gh->gh_nbuckets * sizeof(uint32_t) + gh->gh_maskwords *\n"
	"\t    sizeof(uint64_t);\n"
	"\n"
	"\tif (srcsz < sz || dsz < sz)\n"
	"\t\treturn (0);\n"
	"\n"
	"\t/* Write out the header. */\n"
	"\tif (byteswap) {\n"
	"\t\tSWAP_WORD(t0);\n"
	"\t\tSWAP_WORD(t1);\n"
	"\t\tSWAP_WORD(t2);\n"
	"\t\tSWAP_WORD(t3);\n"
	"\t}\n"
	"\n"
	"\tWRITE_WORD(dst, t0);\n"
	"\tWRITE_WORD(dst, t1);\n"
	"\tWRITE_WORD(dst, t2);\n"
	"\tWRITE_WORD(dst, t3);\n"
	"\n"
	"\t/* Copy the bloom filter and the hash table. */\n"
	"\ts64 = (uint64_t *) (uintptr_t) src;\n"
	"\tfor (n = 0; n < maskwords; n++) {\n"
	"\t\tt64 = *s64++;\n"
	"\t\tif (byteswap)\n"
	"\t\t\tSWAP_XWORD(t64);\n"
	"\t\tWRITE_WORD64(dst, t64);\n"
	"\t}\n"
	"\n"
	"\ts32 = (uint32_t *) s64;\n"
	"\tfor (n = 0; n < nbuckets; n++) {\n"
	"\t\tt32 = *s32++;\n"
	"\t\tif (byteswap)\n"
	"\t\t\tSWAP_WORD(t32);\n"
	"\t\tWRITE_WORD(dst, t32);\n"
	"\t}\n"
	"\n"
	"\tsrcsz -= sz;\n"
	"\tdsz   -= sz;\n"
	"\n"
	"\t/* Copy out the hash chains. */\n"
	"\tif (dsz < srcsz)\n"
	"\t\treturn (0);\n"
	"\n"
	"\tnchains = (uint32_t) (srcsz / sizeof(uint32_t));\n"
	"\tfor (n = 0; n < nchains; n++) {\n"
	"\t\tt32 = *s32++;\n"
	"\t\tif (byteswap)\n"
	"\t\t\tSWAP_WORD(t32);\n"
	"\t\tWRITE_WORD(dst, t32);\n"
	"\t}\n"
	"\n"
	"\treturn (1);\n"
	"}\n"
	"\n"
	"/*\n"
	" * Elf_Note structures comprise a fixed size header followed by variable\n"
	" * length strings.  The fixed size header needs to be byte swapped, but\n"
	" * not the strings.\n"
	" *\n"
	" * Argument count denotes the total number of bytes to be converted.\n"
	" * The destination buffer needs to be at least count bytes in size.\n"
	" */\n"
	"static int\n"
	"_libelf_cvt_NOTE_tom(unsigned char *dst, size_t dsz, unsigned char *src,\n"
	"    size_t count, int byteswap)\n"
	"{\n"
	"\tuint32_t namesz, descsz, type;\n"
	"\tElf_Note *en;\n"
	"\tsize_t sz, hdrsz;\n"
	"\n"
	"\tif (dsz < count)\t/* Destination buffer is too small. */\n"
	"\t\treturn (0);\n"
	"\n"
	"\thdrsz = 3 * sizeof(uint32_t);\n"
	"\tif (count < hdrsz)\t\t/* Source too small. */\n"
	"\t\treturn (0);\n"
	"\n"
	"\tif (!byteswap) {\n"
	"\t\t(void) memcpy(dst, src, count);\n"
	"\t\treturn (1);\n"
	"\t}\n"
	"\n"
	"\t/* Process all notes in the section. */\n"
	"\twhile (count > hdrsz) {\n"
	"\t\t/* Read the note header. */\n"
	"\t\tREAD_WORD(src, namesz);\n"
	"\t\tREAD_WORD(src, descsz);\n"
	"\t\tREAD_WORD(src, type);\n"
	"\n"
	"\t\t/* Translate. */\n"
	"\t\tSWAP_WORD(namesz);\n"
	"\t\tSWAP_WORD(descsz);\n"
	"\t\tSWAP_WORD(type);\n"
	"\n"
	"\t\t/* Copy out the translated note header. */\n"
	"\t\ten = (Elf_Note *) (uintptr_t) dst;\n"
	"\t\ten->namesz = namesz;\n"
	"\t\ten->descsz = descsz;\n"
	"\t\ten->type = type;\n"
	"\n"
	"\t\tdsz -= sizeof(Elf_Note);\n"
	"\t\tdst += sizeof(Elf_Note);\n"
	"\t\tcount -= hdrsz;\n"
	"\n"
	"\t\tROUNDUP2(namesz, 4U);\n"
	"\t\tROUNDUP2(descsz, 4U);\n"
	"\n"
	"\t\tsz = namesz + descsz;\n"
	"\n"
	"\t\tif (count < sz || dsz < sz)\t/* Buffers are too small. */\n"
	"\t\t\treturn (0);\n"
	"\n"
	"\t\t/* Copy the remainder of the note as-is. */\n"
	"\t\t(void) memcpy(dst, src, sz);\n"
	"\n"
	"\t\tsrc += sz;\n"
	"\t\tdst += sz;\n"
	"\n"
	"\t\tcount -= sz;\n"
	"\t\tdsz -= sz;\n"
	"\t}\n"
	"\n"
	"\treturn (1);\n"
	"}\n"
	"\n"
	"static int\n"
	"_libelf_cvt_NOTE_tof(unsigned char *dst, size_t dsz, unsigned char *src,\n"
	"    size_t count, int byteswap)\n"
	"{\n"
	"\tuint32_t namesz, descsz, type;\n"
	"\tElf_Note *en;\n"
	"\tsize_t sz;\n"
	"\n"
	"\tif (dsz < count)\n"
	"\t\treturn (0);\n"
	"\n"
	"\tif (!byteswap) {\n"
	"\t\t(void) memcpy(dst, src, count);\n"
	"\t\treturn (1);\n"
	"\t}\n"
	"\n"
	"\twhile (count > sizeof(Elf_Note)) {\n"
	"\n"
	"\t\ten = (Elf_Note *) (uintptr_t) src;\n"
	"\t\tnamesz = en->namesz;\n"
	"\t\tdescsz = en->descsz;\n"
	"\t\ttype = en->type;\n"
	"\n"
	"\t\tsz = namesz;\n"
	"\t\tROUNDUP2(sz, 4U);\n"
	"\t\tsz += descsz;\n"
	"\t\tROUNDUP2(sz, 4U);\n"
	"\n"
	"\t\tSWAP_WORD(namesz);\n"
	"\t\tSWAP_WORD(descsz);\n"
	"\t\tSWAP_WORD(type);\n"
	"\n"
	"\t\tWRITE_WORD(dst, namesz);\n"
	"\t\tWRITE_WORD(dst, descsz);\n"
	"\t\tWRITE_WORD(dst, type);\n"
	"\n"
	"\t\tsrc += sizeof(Elf_Note);\n"
	"\t\tcount -= sizeof(Elf_Note);\n"
	"\n"
	"\t\tif (count < sz)\n"
	"\t\t\tsz = count;\n"
	"\n"
	"\t\t/* Copy the remainder of the note as-is. */\n"
	"\t\t(void) memcpy(dst, src, sz);\n"
	"\n"
	"\t\tsrc += sz;\n"
	"\t\tdst += sz;\n"
	"\t\tcount -= sz;\n"
	"\t}\n"
	"\n"
	"\treturn (1);\n"
	"}\n"
	"\n"
	"struct converters {\n"
	"\tint\t(*tof32)(unsigned char *dst, size_t dsz, unsigned char *src,\n"
	"\t\t    size_t cnt, int byteswap);\n"
	"\tint\t(*tom32)(unsigned char *dst, size_t dsz, unsigned char *src,\n"
	"\t\t    size_t cnt, int byteswap);\n"
	"\tint\t(*tof64)(unsigned char *dst, size_t dsz, unsigned char *src,\n"
	"\t\t    size_t cnt, int byteswap);\n"
	"\tint\t(*tom64)(unsigned char *dst, size_t dsz, unsigned char *src,\n"
	"\t\t    size_t cnt, int byteswap);\n"
	"};\n"
	"\n"
	"\n"
	"static struct converters cvt[ELF_T_NUM] = {\n"
	"\t/*[*/\n";

static const char convert_suffix[] =
	"\n"
	"\t/*]*/\n"
	"\n"
	"\t/*\n"
	"\t * Types that need hand-coded converters follow.\n"
	"\t */\n"
	"\n"
	"\t[ELF_T_BYTE] = {\n"
	"\t\t.tof32 = _libelf_cvt_BYTE_tox,\n"
	"\t\t.tom32 = _libelf_cvt_BYTE_tox,\n"
	"\t\t.tof64 = _libelf_cvt_BYTE_tox,\n"
	"\t\t.tom64 = _libelf_cvt_BYTE_tox\n"
	"\t},\n"
	"\n"
	"\t[ELF_T_NOTE] = {\n"
	"\t\t.tof32 = _libelf_cvt_NOTE_tof,\n"
	"\t\t.tom32 = _libelf_cvt_NOTE_tom,\n"
	"\t\t.tof64 = _libelf_cvt_NOTE_tof,\n"
	"\t\t.tom64 = _libelf_cvt_NOTE_tom\n"
	"\t}\n"
	"};\n"
	"\n"
	"/*\n"
	" * Return a translator function for the specified ELF section type, conversion\n"
	" * direction, ELF class and ELF machine.\n"
	" */\n"
	"_libelf_translator_function *\n"
	"_libelf_get_translator(Elf_Type t, int direction, int elfclass, int elfmachine)\n"
	"{\n"
	"\tassert(elfclass == ELFCLASS32 || elfclass == ELFCLASS64);\n"
	"\tassert(direction == ELF_TOFILE || direction == ELF_TOMEMORY);\n"
	"\tassert(t >= ELF_T_FIRST && t <= ELF_T_LAST);\n"
	"\n"
	"\t/* TODO: Handle MIPS64 REL{,A} sections (ticket #559). */\n"
	"\t(void) elfmachine;\n"
	"\n"
	"\treturn ((elfclass == ELFCLASS32) ?\n"
	"\t    (direction == ELF_TOFILE ? cvt[t].tof32 : cvt[t].tom32) :\n"
	"\t    (direction == ELF_TOFILE ? cvt[t].tof64 : cvt[t].tom64));\n"
	"}\n";

/* Helpers: classification matching libelf_convert.m4 / msize / fsize rules. */

static int streq(const char *a, const char *b)
{
	return strcmp(a, b) == 0;
}

static int is_prim(const char *name)
{
	return streq(name, "ADDR") || streq(name, "BYTE") ||
	    streq(name, "HALF") || streq(name, "LWORD") ||
	    streq(name, "OFF") || streq(name, "SWORD") ||
	    streq(name, "SXWORD") || streq(name, "WORD") ||
	    streq(name, "XWORD");
}

static int is_sizedep(const char *name)
{
	return streq(name, "ADDR") || streq(name, "OFF");
}

/* Map Elf32_/Elf64_ cname to field table. Returns field count, sets *out. */
static int lookup_fields(const char *cname, const struct elf_field **out)
{
	if (streq(cname, "Elf32_Cap")) { *out = Elf32_Cap_fields; return 2; }
	if (streq(cname, "Elf64_Cap")) { *out = Elf64_Cap_fields; return 2; }
	if (streq(cname, "Elf32_Dyn")) { *out = Elf32_Dyn_fields; return 2; }
	if (streq(cname, "Elf64_Dyn")) { *out = Elf64_Dyn_fields; return 2; }
	if (streq(cname, "Elf32_Ehdr")) { *out = Elf32_Ehdr_fields; return 14; }
	if (streq(cname, "Elf64_Ehdr")) { *out = Elf64_Ehdr_fields; return 14; }
	if (streq(cname, "Elf32_Move")) { *out = Elf32_Move_fields; return 5; }
	if (streq(cname, "Elf64_Move")) { *out = Elf64_Move_fields; return 5; }
	if (streq(cname, "Elf32_Phdr")) { *out = Elf32_Phdr_fields; return 8; }
	if (streq(cname, "Elf64_Phdr")) { *out = Elf64_Phdr_fields; return 8; }
	if (streq(cname, "Elf32_Rel")) { *out = Elf32_Rel_fields; return 2; }
	if (streq(cname, "Elf64_Rel")) { *out = Elf64_Rel_fields; return 2; }
	if (streq(cname, "Elf32_Rela")) { *out = Elf32_Rela_fields; return 3; }
	if (streq(cname, "Elf64_Rela")) { *out = Elf64_Rela_fields; return 3; }
	if (streq(cname, "Elf32_Shdr")) { *out = Elf32_Shdr_fields; return 10; }
	if (streq(cname, "Elf64_Shdr")) { *out = Elf64_Shdr_fields; return 10; }
	if (streq(cname, "Elf32_Sym")) { *out = Elf32_Sym_fields; return 6; }
	if (streq(cname, "Elf64_Sym")) { *out = Elf64_Sym_fields; return 6; }
	if (streq(cname, "Elf32_Syminfo")) { *out = Elf32_Syminfo_fields; return 2; }
	if (streq(cname, "Elf64_Syminfo")) { *out = Elf64_Syminfo_fields; return 2; }
	if (streq(cname, "Elf32_Verdaux")) { *out = Elf32_Verdaux_fields; return 2; }
	if (streq(cname, "Elf64_Verdaux")) { *out = Elf64_Verdaux_fields; return 2; }
	if (streq(cname, "Elf32_Verdef")) { *out = Elf32_Verdef_fields; return 7; }
	if (streq(cname, "Elf64_Verdef")) { *out = Elf64_Verdef_fields; return 7; }
	if (streq(cname, "Elf32_Verneed")) { *out = Elf32_Verneed_fields; return 5; }
	if (streq(cname, "Elf64_Verneed")) { *out = Elf64_Verneed_fields; return 5; }
	if (streq(cname, "Elf32_Vernaux")) { *out = Elf32_Vernaux_fields; return 5; }
	if (streq(cname, "Elf64_Vernaux")) { *out = Elf64_Vernaux_fields; return 5; }
	*out = NULL;
	return 0;
}

/* ---------- msize ---------- */

static void gen_msize(FILE *out)
{
	int i;
	fputs(msize_prefix, out);
	for (i = 0; i < ELF_TYPE_REALCOUNT; i++) {
		const char *name = elf_type_list[i].name;
		const char *suffix = elf_type_list[i].suffix;
		char s32[128], s64[128];
		if (streq(name, "BYTE") || streq(name, "GNUHASH") ||
		    streq(name, "NOTE") || streq(name, "VDEF") ||
		    streq(name, "VNEED")) {
			strcpy(s32, "1");
			strcpy(s64, "1");
		} else if (streq(name, "MOVEP")) {
			strcpy(s32, "0");
			strcpy(s64, "0");
		} else if (streq(name, "SXWORD")) {
			strcpy(s32, "0");
			strcpy(s64, "sizeof(Elf64_Sxword)");
		} else if (streq(name, "XWORD")) {
			strcpy(s32, "0");
			strcpy(s64, "sizeof(Elf64_Xword)");
		} else {
			snprintf(s32, sizeof(s32), "sizeof(Elf32_%s)", suffix);
			snprintf(s64, sizeof(s64), "sizeof(Elf64_%s)", suffix);
		}
		fprintf(out, "[ELF_T_%s] = { .msz32 = %s, .msz64 = %s },\n\n",
		    name, s32, s64);
	}
	fputs(msize_suffix, out);
}

/* ---------- fsize ---------- */

/* Map upper-case basic type to C suffix case for sizeof(). */
static const char *fsize_c_suffix(const char *ftype)
{
	if (streq(ftype, "BYTE")) return NULL;	/* handled as 1 */
	if (streq(ftype, "IDENT")) return NULL;	/* handled as EI_NIDENT */
	if (streq(ftype, "HALF")) return "Half";
	if (streq(ftype, "WORD")) return "Word";
	if (streq(ftype, "LWORD")) return "Lword";
	if (streq(ftype, "ADDR")) return "Addr";
	if (streq(ftype, "OFF")) return "Off";
	if (streq(ftype, "SWORD")) return "Sword";
	if (streq(ftype, "XWORD")) return "Xword";
	if (streq(ftype, "SXWORD")) return "Sxword";
	return ftype;
}

static void gen_fsize(FILE *out)
{
	int i;
	fputs(fsize_prefix, out);
	for (i = 0; i < ELF_TYPE_REALCOUNT; i++) {
		const char *name = elf_type_list[i].name;
		const char *suffix = elf_type_list[i].suffix;
		char s32[4096], s64[4096];
		if (streq(name, "BYTE") || streq(name, "GNUHASH") ||
		    streq(name, "NOTE") || streq(name, "VDEF") ||
		    streq(name, "VNEED")) {
			strcpy(s32, "1");
			strcpy(s64, "1");
		} else if (streq(name, "MOVEP")) {
			strcpy(s32, "0");
			strcpy(s64, "0");
		} else if (streq(name, "SXWORD")) {
			strcpy(s32, "0");
			strcpy(s64, "sizeof(Elf64_Sxword)");
		} else if (streq(name, "XWORD")) {
			strcpy(s32, "0");
			strcpy(s64, "sizeof(Elf64_Xword)");
		} else {
			char c32[64], c64[64];
			const struct elf_field *f32, *f64;
			int n32, n64, k;
			snprintf(c32, sizeof(c32), "Elf32_%s", suffix);
			snprintf(c64, sizeof(c64), "Elf64_%s", suffix);
			n32 = lookup_fields(c32, &f32);
			n64 = lookup_fields(c64, &f64);
			if (n32 > 0) {
				s32[0] = '\0';
				for (k = 0; k < n32; k++) {
					const char *cs = fsize_c_suffix(f32[k].ftype);
					char tok[128];
					if (cs == NULL) {
						if (streq(f32[k].ftype, "BYTE"))
							strcpy(tok, "1");
						else
							strcpy(tok, "EI_NIDENT");
					} else {
						snprintf(tok, sizeof(tok),
						    "sizeof(Elf32_%s)", cs);
					}
					strcat(s32, tok);
					strcat(s32, "+");
				}
				strcat(s32, "0");
			} else {
				snprintf(s32, sizeof(s32),
				    "sizeof(Elf32_%s)", suffix);
			}
			if (n64 > 0) {
				s64[0] = '\0';
				for (k = 0; k < n64; k++) {
					const char *cs = fsize_c_suffix(f64[k].ftype);
					char tok[128];
					if (cs == NULL) {
						if (streq(f64[k].ftype, "BYTE"))
							strcpy(tok, "1");
						else
							strcpy(tok, "EI_NIDENT");
					} else {
						snprintf(tok, sizeof(tok),
						    "sizeof(Elf64_%s)", cs);
					}
					strcat(s64, tok);
					strcat(s64, "+");
				}
				strcat(s64, "0");
			} else {
				snprintf(s64, sizeof(s64),
				    "sizeof(Elf64_%s)", suffix);
			}
		}
		fprintf(out, "[ELF_T_%s] = { .fsz32 = %s, .fsz64 = %s },\n\n",
		    name, s32, s64);
	}
	fputs(fsize_suffix, out);
}

/* ---------- convert ---------- */

/* Emit SWAP lines for struct cname, variable var (t or a), class bits. */
static void emit_swap(FILE *out, const char *cname, const char *var, int bits)
{
	const struct elf_field *fields;
	int n, k;
	int is_aux = (strcmp(var, "a") == 0);
	/* class prefix for comment is derived from cname directly */
	n = lookup_fields(cname, &fields);
	if (is_aux)
		fprintf(out, "\t\t\t\t/* Swap an %s */\n", cname);
	else
		fprintf(out, "\t\t\t/* Swap an %s */\n", cname);
	for (k = 0; k < n; k++) {
		const char *ft = fields[k].ftype;
		if (streq(ft, "ADDR") || streq(ft, "OFF")) {
			fprintf(out, "\t\t\tSWAP_%s%d(%s.%s);\n",
			    ft, bits, var, fields[k].fname);
		} else {
			fprintf(out, "\t\t\tSWAP_%s(%s.%s);\n",
			    ft, var, fields[k].fname);
		}
	}
	fprintf(out, "\t\t\t/**/\n");
}

static void emit_write(FILE *out, const char *cname, const char *var, int bits)
{
	const struct elf_field *fields;
	int n, k;
	int is_aux = (strcmp(var, "a") == 0);
	(void) bits;
	n = lookup_fields(cname, &fields);
	if (is_aux)
		fprintf(out, "\t\t\t/* Write an %s */\n", cname);
	else
		fprintf(out, "\t\t/* Write an %s */\n", cname);
	for (k = 0; k < n; k++) {
		const char *ft = fields[k].ftype;
		if (streq(ft, "ADDR") || streq(ft, "OFF")) {
			fprintf(out, "\t\tWRITE_%s%d(dst,%s.%s);\n",
			    ft, bits, var, fields[k].fname);
		} else {
			fprintf(out, "\t\tWRITE_%s(dst,%s.%s);\n",
			    ft, var, fields[k].fname);
		}
	}
	fprintf(out, "\t\t/**/\n");
}

static void emit_read(FILE *out, const char *cname, const char *var, int bits)
{
	const struct elf_field *fields;
	int n, k;
	int is_aux = (strcmp(var, "a") == 0);
	(void) bits;
	n = lookup_fields(cname, &fields);
	if (is_aux)
		fprintf(out, "\t\t\t/* Read an %s */\n", cname);
	else
		fprintf(out, "\t\t/* Read an %s */\n", cname);
	for (k = 0; k < n; k++) {
		const char *ft = fields[k].ftype;
		if (streq(ft, "ADDR") || streq(ft, "OFF")) {
			fprintf(out, "\t\tREAD_%s%d(s,%s.%s);\n",
			    ft, bits, var, fields[k].fname);
		} else {
			fprintf(out, "\t\tREAD_%s(s,%s.%s);\n",
			    ft, var, fields[k].fname);
		}
	}
	fprintf(out, "\t\t/**/\n");
}

/* MAKEPRIMFUNCS(elftype, ctype, bits, extra) */
static void gen_prim(FILE *out, const char *elftype, const char *ctype,
    int bits, const char *extra)
{
	/* tof */
	fprintf(out, "static int\n");
	fprintf(out, "_libelf_cvt_%s%s_tof(unsigned char *dst, size_t dsz, unsigned char *src,\n",
	    elftype, extra);
	fprintf(out, "    size_t count, int byteswap)\n");
	fprintf(out, "{\n");
	fprintf(out, "\tElf%d_%s t, *s = (Elf%d_%s *) (uintptr_t) src;\n",
	    bits, ctype, bits, ctype);
	fprintf(out, "\tsize_t c;\n");
	fprintf(out, "\n");
	fprintf(out, "\t(void) dsz;\n");
	fprintf(out, "\n");
	fprintf(out, "\tif (!byteswap) {\n");
	fprintf(out, "\t\t(void) memcpy(dst, src, count * sizeof(*s));\n");
	fprintf(out, "\t\treturn (1);\n");
	fprintf(out, "\t}\n");
	fprintf(out, "\n");
	fprintf(out, "\tfor (c = 0; c < count; c++) {\n");
	fprintf(out, "\t\tt = *s++;\n");
	fprintf(out, "\t\tSWAP_%s%s(t);\n", elftype, extra);
	fprintf(out, "\t\tWRITE_%s%s(dst,t);\n", elftype, extra);
	fprintf(out, "\t}\n");
	fprintf(out, "\n");
	fprintf(out, "\treturn (1);\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	/* tom */
	fprintf(out, "static int\n");
	fprintf(out, "_libelf_cvt_%s%s_tom(unsigned char *dst, size_t dsz, unsigned char *src,\n",
	    elftype, extra);
	fprintf(out, "    size_t count, int byteswap)\n");
	fprintf(out, "{\n");
	fprintf(out, "\tElf%d_%s t, *d = (Elf%d_%s *) (uintptr_t) dst;\n",
	    bits, ctype, bits, ctype);
	fprintf(out, "\tsize_t c;\n");
	fprintf(out, "\n");
	fprintf(out, "\tif (dsz < count * sizeof(Elf%d_%s))\n", bits, ctype);
	fprintf(out, "\t\treturn (0);\n");
	fprintf(out, "\n");
	fprintf(out, "\tif (!byteswap) {\n");
	fprintf(out, "\t\t(void) memcpy(dst, src, count * sizeof(*d));\n");
	fprintf(out, "\t\treturn (1);\n");
	fprintf(out, "\t}\n");
	fprintf(out, "\n");
	fprintf(out, "\tfor (c = 0; c < count; c++) {\n");
	fprintf(out, "\t\tREAD_%s%s(src,t);\n", elftype, extra);
	fprintf(out, "\t\tSWAP_%s%s(t);\n", elftype, extra);
	fprintf(out, "\t\t*d++ = t;\n");
	fprintf(out, "\t}\n");
	fprintf(out, "\n");
	fprintf(out, "\treturn (1);\n");
	fprintf(out, "}\n");
}

/* MAKECOMPFUNCS(elftype, ctype, bits) */
static void gen_comp(FILE *out, const char *elftype, const char *ctype, int bits)
{
	char cname[64];
	snprintf(cname, sizeof(cname), "Elf%d_%s", bits, ctype);
	/* tof */
	fprintf(out, "static int\n");
	fprintf(out, "_libelf_cvt_%s%d_tof(unsigned char *dst, size_t dsz, unsigned char *src,\n",
	    elftype, bits);
	fprintf(out, "    size_t count, int byteswap)\n");
	fprintf(out, "{\n");
	fprintf(out, "\t%s\tt, *s;\n", cname);
	fprintf(out, "\tsize_t c;\n");
	fprintf(out, "\n");
	fprintf(out, "\t(void) dsz;\n");
	fprintf(out, "\n");
	fprintf(out, "\ts = (%s *) (uintptr_t) src;\n", cname);
	fprintf(out, "\tfor (c = 0; c < count; c++) {\n");
	fprintf(out, "\t\tt = *s++;\n");
	fprintf(out, "\t\tif (byteswap) {\n");
	emit_swap(out, cname, "t", bits);
	fprintf(out, "\t\t}\n");
	emit_write(out, cname, "t", bits);
	fprintf(out, "\t}\n");
	fprintf(out, "\n");
	fprintf(out, "\treturn (1);\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	/* tom */
	fprintf(out, "static int\n");
	fprintf(out, "_libelf_cvt_%s%d_tom(unsigned char *dst, size_t dsz, unsigned char *src,\n",
	    elftype, bits);
	fprintf(out, "    size_t count, int byteswap)\n");
	fprintf(out, "{\n");
	fprintf(out, "\t%s\tt, *d;\n", cname);
	fprintf(out, "\tunsigned char\t*s,*s0;\n");
	fprintf(out, "\tsize_t\t\tfsz;\n");
	fprintf(out, "\n");
	fprintf(out, "\tfsz = elf%d_fsize(ELF_T_%s, (size_t) 1, EV_CURRENT);\n",
	    bits, elftype);
	fprintf(out, "\td   = ((%s *) (uintptr_t) dst) + (count - 1);\n", cname);
	fprintf(out, "\ts0  = src + (count - 1) * fsz;\n");
	fprintf(out, "\n");
	fprintf(out, "\tif (dsz < count * sizeof(%s))\n", cname);
	fprintf(out, "\t\treturn (0);\n");
	fprintf(out, "\n");
	fprintf(out, "\twhile (count--) {\n");
	fprintf(out, "\t\ts = s0;\n");
	emit_read(out, cname, "t", bits);
	fprintf(out, "\t\tif (byteswap) {\n");
	emit_swap(out, cname, "t", bits);
	fprintf(out, "\t\t}\n");
	fprintf(out, "\t\t*d-- = t; s0 -= fsz;\n");
	fprintf(out, "\t}\n");
	fprintf(out, "\n");
	fprintf(out, "\treturn (1);\n");
	fprintf(out, "}\n");
}

/* FSZ helper for version sizes: HALF->2, WORD->4 */
static int vers_field_size(const char *ftype)
{
	if (streq(ftype, "HALF"))
		return 2;
	if (streq(ftype, "WORD"))
		return 4;
	return 0;
}

static int vers_struct_size(const char *cname)
{
	const struct elf_field *f;
	int n, k, sz = 0;
	n = lookup_fields(cname, &f);
	for (k = 0; k < n; k++)
		sz += vers_field_size(f[k].ftype);
	return sz;
}

/* MAKE_VERSION_CONVERTER(elftype, base, aux, prefix, bits) */
static void gen_version_one(FILE *out, const char *elftype, const char *base,
    const char *aux, const char *pfx, int bits)
{
	char cbase[64], caux[64];
	int verfsz, auxfsz;
	snprintf(cbase, sizeof(cbase), "Elf%d_%s", bits, base);
	snprintf(caux, sizeof(caux), "Elf%d_%s", bits, aux);
	verfsz = vers_struct_size(cbase);
	auxfsz = vers_struct_size(caux);
	/* tof */
	fprintf(out, "static int\n");
	fprintf(out, "_libelf_cvt_%s%d_tof(unsigned char *dst, size_t dsz, unsigned char *src,\n",
	    elftype, bits);
	fprintf(out, "    size_t count, int byteswap)\n");
	fprintf(out, "{\n");
	fprintf(out, "\t%s\tt;\n", cbase);
	fprintf(out, "\t%s\ta;\n", caux);
	fprintf(out, "\tconst size_t\tverfsz = %d;\n", verfsz);
	fprintf(out, "\tconst size_t\tauxfsz = %d;\n", auxfsz);
	fprintf(out, "\tconst size_t\tvermsz = sizeof(%s);\n", cbase);
	fprintf(out, "\tconst size_t\tauxmsz = sizeof(%s);\n", caux);
	fprintf(out, "\tunsigned char * const dstend = dst + dsz;\n");
	fprintf(out, "\tunsigned char * const srcend = src + count;\n");
	fprintf(out, "\tunsigned char\t*dtmp, *dstaux, *srcaux;\n");
	fprintf(out, "\tElf%d_Word\taux, anext, cnt, vnext;\n", bits);
	fprintf(out, "\n");
	fprintf(out, "\tfor (dtmp = dst, vnext = ~0U;\n");
	fprintf(out, "\t     vnext != 0 && dtmp + verfsz <= dstend && src + vermsz <= srcend;\n");
	fprintf(out, "\t     dtmp += vnext, src += vnext) {\n");
	fprintf(out, "\n");
	fprintf(out, "\t\t/* Read in an %s structure. */\n", cbase);
	fprintf(out, "\t\tt = *((%s *) (uintptr_t) src);\n", cbase);
	fprintf(out, "\n");
	fprintf(out, "\t\taux = t.%s_aux;\n", pfx);
	fprintf(out, "\t\tcnt = t.%s_cnt;\n", pfx);
	fprintf(out, "\t\tvnext = t.%s_next;\n", pfx);
	fprintf(out, "\n");
	fprintf(out, "\t\tif (byteswap) {\n");
	emit_swap(out, cbase, "t", bits);
	fprintf(out, "\t\t}\n");
	fprintf(out, "\n");
	fprintf(out, "\t\tdst = dtmp;\n");
	emit_write(out, cbase, "t", bits);
	fprintf(out, "\n");
	fprintf(out, "\t\tif (aux < verfsz)\n");
	fprintf(out, "\t\t\treturn (0);\n");
	fprintf(out, "\n");
	fprintf(out, "\t\t/* Process AUX entries. */\n");
	fprintf(out, "\t\tfor (anext = ~0U, dstaux = dtmp + aux, srcaux = src + aux;\n");
	fprintf(out, "\t\t     cnt != 0 && anext != 0 && dstaux + auxfsz <= dstend &&\n");
	fprintf(out, "\t\t\tsrcaux + auxmsz <= srcend;\n");
	fprintf(out, "\t\t     dstaux += anext, srcaux += anext, cnt--) {\n");
	fprintf(out, "\n");
	fprintf(out, "\t\t\t/* Read in an %s structure. */\n", caux);
	fprintf(out, "\t\t\ta = *((%s *) (uintptr_t) srcaux);\n", caux);
	fprintf(out, "\t\t\tanext = a.%sa_next;\n", pfx);
	fprintf(out, "\n");
	fprintf(out, "\t\t\tif (byteswap) {\n");
	emit_swap(out, caux, "a", bits);
	fprintf(out, "\t\t\t}\n");
	fprintf(out, "\n");
	fprintf(out, "\t\t\tdst = dstaux;\n");
	emit_write(out, caux, "a", bits);
	fprintf(out, "\t\t}\n");
	fprintf(out, "\n");
	fprintf(out, "\t\tif (anext || cnt)\n");
	fprintf(out, "\t\t\treturn (0);\n");
	fprintf(out, "\t}\n");
	fprintf(out, "\n");
	fprintf(out, "\tif (vnext)\n");
	fprintf(out, "\t\treturn (0);\n");
	fprintf(out, "\n");
	fprintf(out, "\treturn (1);\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	/* tom */
	fprintf(out, "static int\n");
	fprintf(out, "_libelf_cvt_%s%d_tom(unsigned char *dst, size_t dsz, unsigned char *src,\n",
	    elftype, bits);
	fprintf(out, "    size_t count, int byteswap)\n");
	fprintf(out, "{\n");
	fprintf(out, "\t%s\tt, *dp;\n", cbase);
	fprintf(out, "\t%s\ta, *ap;\n", caux);
	fprintf(out, "\tconst size_t\tverfsz = %d;\n", verfsz);
	fprintf(out, "\tconst size_t\tauxfsz = %d;\n", auxfsz);
	fprintf(out, "\tconst size_t\tvermsz = sizeof(%s);\n", cbase);
	fprintf(out, "\tconst size_t\tauxmsz = sizeof(%s);\n", caux);
	fprintf(out, "\tunsigned char * const dstend = dst + dsz;\n");
	fprintf(out, "\tunsigned char * const srcend = src + count;\n");
	fprintf(out, "\tunsigned char\t*dstaux, *s, *srcaux, *stmp;\n");
	fprintf(out, "\tElf%d_Word\taux, anext, cnt, vnext;\n", bits);
	fprintf(out, "\n");
	fprintf(out, "\tfor (stmp = src, vnext = ~0U;\n");
	fprintf(out, "\t     vnext != 0 && stmp + verfsz <= srcend && dst + vermsz <= dstend;\n");
	fprintf(out, "\t     stmp += vnext, dst += vnext) {\n");
	fprintf(out, "\n");
	fprintf(out, "\t\t/* Read in a %s structure. */\n", elftype);
	fprintf(out, "\t\ts = stmp;\n");
	emit_read(out, cbase, "t", bits);
	fprintf(out, "\t\tif (byteswap) {\n");
	emit_swap(out, cbase, "t", bits);
	fprintf(out, "\t\t}\n");
	fprintf(out, "\n");
	fprintf(out, "\t\tdp = (%s *) (uintptr_t) dst;\n", cbase);
	fprintf(out, "\t\t*dp = t;\n");
	fprintf(out, "\n");
	fprintf(out, "\t\taux = t.%s_aux;\n", pfx);
	fprintf(out, "\t\tcnt = t.%s_cnt;\n", pfx);
	fprintf(out, "\t\tvnext = t.%s_next;\n", pfx);
	fprintf(out, "\n");
	fprintf(out, "\t\tif (aux < vermsz)\n");
	fprintf(out, "\t\t\treturn (0);\n");
	fprintf(out, "\n");
	fprintf(out, "\t\t/* Process AUX entries. */\n");
	fprintf(out, "\t\tfor (anext = ~0U, dstaux = dst + aux, srcaux = stmp + aux;\n");
	fprintf(out, "\t\t     cnt != 0 && anext != 0 && dstaux + auxmsz <= dstend &&\n");
	fprintf(out, "\t\t\tsrcaux + auxfsz <= srcend;\n");
	fprintf(out, "\t\t     dstaux += anext, srcaux += anext, cnt--) {\n");
	fprintf(out, "\n");
	fprintf(out, "\t\t\ts = srcaux;\n");
	emit_read(out, caux, "a", bits);
	fprintf(out, "\n");
	fprintf(out, "\t\t\tif (byteswap) {\n");
	emit_swap(out, caux, "a", bits);
	fprintf(out, "\t\t\t}\n");
	fprintf(out, "\n");
	fprintf(out, "\t\t\tanext = a.%sa_next;\n", pfx);
	fprintf(out, "\n");
	fprintf(out, "\t\t\tap = ((%s *) (uintptr_t) dstaux);\n", caux);
	fprintf(out, "\t\t\t*ap = a;\n");
	fprintf(out, "\t\t}\n");
	fprintf(out, "\n");
	fprintf(out, "\t\tif (anext || cnt)\n");
	fprintf(out, "\t\t\treturn (0);\n");
	fprintf(out, "\t}\n");
	fprintf(out, "\n");
	fprintf(out, "\tif (vnext)\n");
	fprintf(out, "\t\treturn (0);\n");
	fprintf(out, "\n");
	fprintf(out, "\treturn (1);\n");
	fprintf(out, "}\n");
}

static void gen_convert(FILE *out)
{
	fputs(convert_prefix, out);
	fputs("\n", out);
	gen_prim(out, "ADDR", "Addr", 32, "32");
	fputs("\t \n", out);
	gen_prim(out, "ADDR", "Addr", 64, "64");
	fputs("\n", out);
	gen_comp(out, "CAP", "Cap", 32);
	fputs("       \n", out);
	gen_comp(out, "CAP", "Cap", 64);
	fputs("\n", out);
	gen_comp(out, "DYN", "Dyn", 32);
	fputs("       \n", out);
	gen_comp(out, "DYN", "Dyn", 64);
	fputs("\n", out);
	gen_comp(out, "EHDR", "Ehdr", 32);
	fputs("       \n", out);
	gen_comp(out, "EHDR", "Ehdr", 64);
	fputs("\n", out);
	gen_prim(out, "HALF", "Half", 64, "");
	fputs("\n", out);
	gen_prim(out, "LWORD", "Lword", 64, "");
	fputs("\n", out);
	gen_comp(out, "MOVE", "Move", 32);
	fputs("       \n", out);
	gen_comp(out, "MOVE", "Move", 64);
	fputs("\n", out);
	gen_prim(out, "OFF", "Off", 32, "32");
	fputs("\t \n", out);
	gen_prim(out, "OFF", "Off", 64, "64");
	fputs("\n", out);
	gen_comp(out, "PHDR", "Phdr", 32);
	fputs("       \n", out);
	gen_comp(out, "PHDR", "Phdr", 64);
	fputs("\n", out);
	gen_comp(out, "REL", "Rel", 32);
	fputs("       \n", out);
	gen_comp(out, "REL", "Rel", 64);
	fputs("\n", out);
	gen_comp(out, "RELA", "Rela", 32);
	fputs("       \n", out);
	gen_comp(out, "RELA", "Rela", 64);
	fputs("\n", out);
	gen_comp(out, "SHDR", "Shdr", 32);
	fputs("       \n", out);
	gen_comp(out, "SHDR", "Shdr", 64);
	fputs("\n", out);
	gen_prim(out, "SWORD", "Sword", 64, "");
	fputs("\n", out);
	gen_prim(out, "SXWORD", "Sxword", 64, "");
	fputs("\n", out);
	gen_comp(out, "SYMINFO", "Syminfo", 32);
	fputs("       \n", out);
	gen_comp(out, "SYMINFO", "Syminfo", 64);
	fputs("\n", out);
	gen_comp(out, "SYM", "Sym", 32);
	fputs("       \n", out);
	gen_comp(out, "SYM", "Sym", 64);
	fputs("\n", out);
	gen_prim(out, "WORD", "Word", 64, "");
	fputs("\n", out);
	gen_prim(out, "XWORD", "Xword", 64, "");
	fputs("\n\n", out);
	gen_version_one(out, "VDEF", "Verdef", "Verdaux", "vd", 32);
	fputs("   \n", out);
	gen_version_one(out, "VDEF", "Verdef", "Verdaux", "vd", 64);
	fputs("\n", out);
	gen_version_one(out, "VNEED", "Verneed", "Vernaux", "vn", 32);
	fputs("   \n", out);
	gen_version_one(out, "VNEED", "Verneed", "Vernaux", "vn", 64);
}

static void gen_table(FILE *out)
{
	int i;
	/* Order for CONVERTER_NAMES: ELF_TYPE_LIST excluding NOCVT (BYTE, NOTE, MOVEP, NUM). */
	const char *tbl[] = {
		"ADDR", "CAP", "DYN", "EHDR", "GNUHASH", "HALF", "LWORD",
		"MOVE", "OFF", "PHDR", "REL", "RELA", "SHDR", "SWORD",
		"SXWORD", "SYMINFO", "SYM", "VDEF", "VNEED", "WORD", "XWORD",
		NULL
	};
	for (i = 0; tbl[i] != NULL; i++) {
		const char *nm = tbl[i];
		char t32_tof[128], t32_tom[128], t64_tof[128], t64_tom[128];
		if (streq(nm, "SXWORD") || streq(nm, "XWORD")) {
			snprintf(t32_tof, sizeof(t32_tof), "NULL");
			snprintf(t32_tom, sizeof(t32_tom), "NULL");
			snprintf(t64_tof, sizeof(t64_tof), "_libelf_cvt_%s_tof", nm);
			snprintf(t64_tom, sizeof(t64_tom), "_libelf_cvt_%s_tom", nm);
		} else if (is_prim(nm) && !is_sizedep(nm)) {
			snprintf(t32_tof, sizeof(t32_tof), "_libelf_cvt_%s_tof", nm);
			snprintf(t32_tom, sizeof(t32_tom), "_libelf_cvt_%s_tom", nm);
			snprintf(t64_tof, sizeof(t64_tof), "_libelf_cvt_%s_tof", nm);
			snprintf(t64_tom, sizeof(t64_tom), "_libelf_cvt_%s_tom", nm);
		} else {
			snprintf(t32_tof, sizeof(t32_tof), "_libelf_cvt_%s32_tof", nm);
			snprintf(t32_tom, sizeof(t32_tom), "_libelf_cvt_%s32_tom", nm);
			snprintf(t64_tof, sizeof(t64_tof), "_libelf_cvt_%s64_tof", nm);
			snprintf(t64_tom, sizeof(t64_tom), "_libelf_cvt_%s64_tom", nm);
		}
		fprintf(out, "\t[ELF_T_%s] = {\n", nm);
		fprintf(out, "\t\t.tof32 = %s,\n", t32_tof);
		fprintf(out, "\t\t.tom32 = %s,\n", t32_tom);
		fprintf(out, "\t\t.tof64 = %s,\n", t64_tof);
		fprintf(out, "\t\t.tom64 = %s\n", t64_tom);
		fprintf(out, "\t},\n\n");
	}
}

int main(int argc, char **argv)
{
	const char *mode;
	FILE *out = stdout;
	if (argc < 2) {
		fprintf(stderr, "usage: %s {msize|fsize|convert} [output]\n", argv[0]);
		return 2;
	}
	mode = argv[1];
	if (argc >= 3) {
		out = fopen(argv[2], "wb");
		if (!out) {
			perror(argv[2]);
			return 1;
		}
	} else {
#ifdef _WIN32
		_setmode(_fileno(stdout), _O_BINARY);
#endif
	}
	if (streq(mode, "msize")) {
		gen_msize(out);
	} else if (streq(mode, "fsize")) {
		gen_fsize(out);
	} else if (streq(mode, "convert")) {
		gen_convert(out);
		fputs(convert_middle, out);
		gen_table(out);
		fputs(convert_suffix, out);
	} else {
		fprintf(stderr, "%s: unknown mode %s\n", argv[0], mode);
		return 2;
	}
	if (out != stdout)
		fclose(out);
	return 0;
}
