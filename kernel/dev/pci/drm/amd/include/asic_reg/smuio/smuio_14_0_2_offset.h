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
#ifndef _smuio_14_0_2_OFFSET_HEADER
#define _smuio_14_0_2_OFFSET_HEADER

// addressBlock: smuio_smuio_tsc_SmuSmuioDec
// base address: 0x5a8a0
#define regGOLDEN_TSC_COUNT_UPPER 0x002d
#define regGOLDEN_TSC_COUNT_UPPER_BASE_IDX 1
#define regGOLDEN_TSC_COUNT_LOWER 0x002e
#define regGOLDEN_TSC_COUNT_LOWER_BASE_IDX 1
// addressBlock: smuio_smuio_misc_SmuSmuioDec
// base address: 0x5a000
#define regSMUIO_MCM_CONFIG 0x0023
#define regSMUIO_MCM_CONFIG_BASE_IDX 0
// addressBlock: smuio_smuio_rom_SmuSmuioDec
// base address: 0x5a380
#define regCGTT_ROM_CLK_CTRL0 0x00e3
#define regCGTT_ROM_CLK_CTRL0_BASE_IDX 0
#define regROM_INDEX 0x00e4
#define regROM_INDEX_BASE_IDX 0
#define regROM_DATA 0x00e5
#define regROM_DATA_BASE_IDX 0
#endif
