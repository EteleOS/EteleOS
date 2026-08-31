/*
 *
 * Copyright (C) 2016 Advanced Micro Devices, Inc.
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

#ifndef SMU_6_0_D_H
#define SMU_6_0_D_H

#define ixLCAC_MC0_CNTL 0x011C
#define ixLCAC_MC0_OVR_SEL 0x011D
#define ixLCAC_MC0_OVR_VAL 0x011E
#define ixLCAC_MC1_CNTL 0x011F
#define ixLCAC_MC1_OVR_SEL 0x0120
#define ixLCAC_MC1_OVR_VAL 0x0121
#define ixLCAC_MC2_OVR_SEL 0x0123
#define ixLCAC_MC2_OVR_VAL 0x0124
#define ixLCAC_MC3_OVR_SEL 0x0126
#define ixLCAC_MC3_OVR_VAL 0x0127
#define mmCG_SPLL_FUNC_CNTL 0x0180
#define mmCG_SPLL_FUNC_CNTL_2 0x0181
#define mmCG_SPLL_FUNC_CNTL_3 0x0182
#define mmCG_SPLL_FUNC_CNTL_4 0x0183
#define mmCG_SPLL_STATUS 0x0185
#define mmSPLL_CNTL_MODE 0x0186
#define mmCG_SPLL_SPREAD_SPECTRUM 0x0188
#define mmCG_SPLL_SPREAD_SPECTRUM_2 0x0189
#define mmCG_SPLL_AUTOSCALE_CNTL 0x018B
#define mmMPLL_BYPASSCLK_SEL 0x0197
#define mmCG_CLKPIN_CNTL 0x0198
#define mmCG_CLKPIN_CNTL_2 0x0199
#define mmTHM_CLK_CNTL 0x019B
#define mmMISC_CLK_CNTL 0x019C
#define mmCG_THERMAL_CTRL 0x01C0
#define mmCG_THERMAL_STATUS 0x01C1
#define mmCG_THERMAL_INT 0x01C2
#define mmCG_MULT_THERMAL_CTRL 0x01C4
#define mmCG_MULT_THERMAL_STATUS 0x01C5
#define mmCG_FDO_CTRL0 0x01D5
#define mmCG_FDO_CTRL1 0x01D6
#define mmCG_FDO_CTRL2 0x01D7
#define mmCG_TACH_CTRL 0x01DC
#define mmCG_TACH_STATUS 0x01DD
#define mmGENERAL_PWRMGT 0x1E0
#define mmCG_TPC 0x1E1
#define mmSCLK_PWRMGT_CNTL 0x1E2
#define mmTARGET_AND_CURRENT_PROFILE_INDEX 0x01E6
#define mmCG_FTV 0x01EF
#define mmCG_FFCT_0 0x01F0
#define mmCG_BSP 0x01FF
#define mmCG_GIT 0x0201
#define mmCG_SSP 0x0203
#define mmCG_DISPLAY_GAP_CNTL 0x020A
#define mmCG_ULV_CONTROL 0x021E
#define mmCG_ULV_PARAMETER 0x021F
#define mmSMC_SCRATCH0 0x0221
#define mmCG_CAC_CTRL 0x022E
#define ixSMC_PC_C 0x80000370
#define mmGPIOPAD_A 0x05E7
#define mmGPIOPAD_EN 0x05E8
#define mmGPIOPAD_MASK 0x05E6
#define mmGPIOPAD_PD_EN 0x05F4
#define mmGPIOPAD_PU_EN 0x05F3
#define mmSMC_IND_ACCESS_CNTL 0x008A
#define mmSMC_IND_DATA_0 0x0081
#define mmSMC_IND_INDEX_0 0x0080
#define mmSMC_MESSAGE_0 0x008B
#define mmSMC_RESP_0 0x008C
#endif
