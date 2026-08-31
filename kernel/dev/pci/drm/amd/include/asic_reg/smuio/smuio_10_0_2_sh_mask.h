/*

 * Copyright (C) 2023  Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef _smuio_10_0_2_SH_MASK_HEADER
// addressBlock: smuio_smuio_misc_SmuSmuioDec
//SMUIO_MCM_CONFIG
#define SMUIO_MCM_CONFIG__DIE_ID__SHIFT 0x0
#define SMUIO_MCM_CONFIG__PKG_TYPE__SHIFT 0x2
#define SMUIO_MCM_CONFIG__SOCKET_ID__SHIFT 0x5
#define SMUIO_MCM_CONFIG__DIE_ID_MASK 0x00000003L
#define SMUIO_MCM_CONFIG__PKG_TYPE_MASK 0x0000001CL
#define SMUIO_MCM_CONFIG__SOCKET_ID_MASK 0x00000020L
//SMUIO_GFX_MISC_CNTL
#define SMUIO_GFX_MISC_CNTL__SMU_GFX_cold_vs_gfxoff__SHIFT 0x0
#define SMUIO_GFX_MISC_CNTL__PWR_GFXOFF_STATUS__SHIFT 0x1
#define SMUIO_GFX_MISC_CNTL__SMU_GFX_cold_vs_gfxoff_MASK 0x00000001L
#define SMUIO_GFX_MISC_CNTL__PWR_GFXOFF_STATUS_MASK 0x00000006L
// addressBlock: smuio_smuio_svi0_SmuSmuioDec
//SMUSVI0_TEL_PLANE0
#define SMUSVI0_TEL_PLANE0__SVI0_PLANE0_VDDCOR__SHIFT 0x10
#define SMUSVI0_TEL_PLANE0__SVI0_PLANE0_VDDCOR_MASK 0x01FF0000L
//SMUSVI0_PLANE0_CURRENTVID
#define SMUSVI0_PLANE0_CURRENTVID__CURRENT_SVI0_PLANE0_VID__SHIFT 0x18
#define SMUSVI0_PLANE0_CURRENTVID__CURRENT_SVI0_PLANE0_VID_MASK 0xFF000000L
#endif
