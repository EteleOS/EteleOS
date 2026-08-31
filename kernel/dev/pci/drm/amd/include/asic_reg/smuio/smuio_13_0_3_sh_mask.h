/*
 * Copyright 2022 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */
#ifndef _smuio_13_0_3_SH_MASK_HEADER
#define _smuio_13_0_3_SH_MASK_HEADER

// addressBlock: aid_smuio_smuio_misc_SmuSmuioDec
//SMUIO_MCM_CONFIG
#define SMUIO_MCM_CONFIG__DIE_ID__SHIFT 0x0
#define SMUIO_MCM_CONFIG__PKG_TYPE__SHIFT 0x2
#define SMUIO_MCM_CONFIG__SOCKET_ID__SHIFT 0x8
#define SMUIO_MCM_CONFIG__TOPOLOGY_ID__SHIFT 0x12
#define SMUIO_MCM_CONFIG__DIE_ID_MASK 0x00000003L
#define SMUIO_MCM_CONFIG__PKG_TYPE_MASK 0x0000003CL
#define SMUIO_MCM_CONFIG__SOCKET_ID_MASK 0x00000F00L
#define SMUIO_MCM_CONFIG__TOPOLOGY_ID_MASK 0x007C0000L
#endif
