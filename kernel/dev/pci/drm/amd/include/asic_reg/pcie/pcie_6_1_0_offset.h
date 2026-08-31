/*
 * Copyright 2023 Advanced Micro Devices, Inc.
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
#ifndef _pcie_6_1_0_OFFSET_HEADER
#define _pcie_6_1_0_OFFSET_HEADER

// addressBlock: pcie_container_pcie0_pswusp0_pciedir_p
// base address: 0x1a340000
#define regPCIE_LC_CNTL 0x100a0
#define regPCIE_LC_CNTL_BASE_IDX 1
#define regPCIE_LC_CNTL3 0x100b5
#define regPCIE_LC_CNTL3_BASE_IDX 1
#define regPCIE_LC_CNTL4 0x100b6
#define regPCIE_LC_CNTL4_BASE_IDX 1
#define regPCIE_LC_CNTL7 0x100bc
#define regPCIE_LC_CNTL7_BASE_IDX 1
#define regPCIE_LC_RXRECOVER_RXSTANDBY_CNTL 0x10102
#define regPCIE_LC_RXRECOVER_RXSTANDBY_CNTL_BASE_IDX 1
// addressBlock: pcie_container_pcie0_pciedir
// base address: 0x1a380000
#define regPCIE_CONFIG_CNTL 0x20011
#define regPCIE_CONFIG_CNTL_BASE_IDX 1
#define regPCIE_CNTL2 0x2001c
#define regPCIE_CNTL2_BASE_IDX 1
#define regCPM_CONTROL 0x20118
#define regCPM_CONTROL_BASE_IDX 1
#endif
