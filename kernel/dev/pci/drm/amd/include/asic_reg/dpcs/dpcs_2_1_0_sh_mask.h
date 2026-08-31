/*
 * Copyright (C) 2019  Advanced Micro Devices, Inc.
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
#ifndef _dpcs_2_1_0_SH_MASK_HEADER
#define _dpcs_2_1_0_SH_MASK_HEADER

//DPCSTX0_DPCSTX_TX_CNTL
#define DPCSTX0_DPCSTX_TX_CNTL__DPCS_TX_DATA_SWAP__SHIFT 0xe
#define DPCSTX0_DPCSTX_TX_CNTL__DPCS_TX_DATA_ORDER_INVERT__SHIFT 0xf
#define DPCSTX0_DPCSTX_TX_CNTL__DPCS_TX_DATA_SWAP_MASK 0x00004000L
#define DPCSTX0_DPCSTX_TX_CNTL__DPCS_TX_DATA_ORDER_INVERT_MASK 0x00008000L
//RDPCSTX0_RDPCSTX_CLOCK_CNTL
#define RDPCSTX0_RDPCSTX_CLOCK_CNTL__RDPCS_SYMCLK_DIV2_GATE_DIS__SHIFT 0x8
#define RDPCSTX0_RDPCSTX_CLOCK_CNTL__RDPCS_SYMCLK_DIV2_EN__SHIFT 0x9
#define RDPCSTX0_RDPCSTX_CLOCK_CNTL__RDPCS_SYMCLK_DIV2_CLOCK_ON__SHIFT 0xa
#define RDPCSTX0_RDPCSTX_CLOCK_CNTL__RDPCS_SYMCLK_DIV2_GATE_DIS_MASK 0x00000100L
#define RDPCSTX0_RDPCSTX_CLOCK_CNTL__RDPCS_SYMCLK_DIV2_EN_MASK 0x00000200L
#define RDPCSTX0_RDPCSTX_CLOCK_CNTL__RDPCS_SYMCLK_DIV2_CLOCK_ON_MASK 0x00000400L
#endif
