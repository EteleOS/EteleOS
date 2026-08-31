/*
 * SMU_7_1_0 Register documentation
 *
 * Copyright (C) 2014  Advanced Micro Devices, Inc.
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

#ifndef SMU_7_1_0_D_H
#define SMU_7_1_0_D_H

#define mmGCK_SMC_IND_INDEX 0x80
#define mmGCK_SMC_IND_DATA 0x81
#define ixCG_DCLK_CNTL 0xc050009c
#define ixCG_DCLK_STATUS 0xc05000a0
#define ixCG_VCLK_CNTL 0xc05000a4
#define ixCG_VCLK_STATUS 0xc05000a8
#define ixCG_ECLK_CNTL 0xc05000ac
#define ixCG_ECLK_STATUS 0xc05000b0
#define ixCG_ACLK_CNTL 0xc05000dc
#define ixGCK_DFS_BYPASS_CNTL 0xc0500118
#define ixCG_SPLL_FUNC_CNTL 0xc0500140
#define ixCG_SPLL_FUNC_CNTL_2 0xc0500144
#define ixCG_SPLL_FUNC_CNTL_3 0xc0500148
#define ixCG_SPLL_FUNC_CNTL_4 0xc050014c
#define ixCG_SPLL_SPREAD_SPECTRUM 0xc0500164
#define ixCG_SPLL_SPREAD_SPECTRUM_2 0xc0500168
#define ixMPLL_BYPASSCLK_SEL 0xc050019c
#define ixCG_CLKPIN_CNTL 0xc05001a0
#define ixCG_CLKPIN_CNTL_2 0xc05001a4
#define ixCG_CLKPIN_CNTL_DC 0xc0500204
#define ixTHM_CLK_CNTL 0xc05001a8
#define ixMISC_CLK_CTRL 0xc05001ac
#define mmSMC_IND_INDEX_0 0x80
#define mmSMC_IND_DATA_0 0x81
#define mmSMC_IND_INDEX_4 0x88
#define mmSMC_IND_DATA_4 0x89
#define mmSMC_IND_ACCESS_CNTL 0x90
#define mmSMC_MESSAGE_0 0x94
#define mmSMC_RESP_0 0x95
#define mmSMC_MSG_ARG_0 0xa4
#define ixSMC_SYSCON_CLOCK_CNTL_0 0x80000004
#define ixSMC_SYSCON_MISC_CNTL 0x80000010
#define ixSMC_SYSCON_MSG_ARG_0 0x80000068
#define ixSMC_PC_C 0x80000370
#define ixSMC_SCRATCH9 0x80000424
#define mmGPIOPAD_MASK 0x182
#define mmGPIOPAD_A 0x183
#define mmGPIOPAD_EN 0x184
#define mmGPIOPAD_PU_EN 0x192
#define mmGPIOPAD_PD_EN 0x193
#define ixSMU_STATUS 0xe0003088
#define ixSMU_EFUSE_0 0xc0100000
#define ixFIRMWARE_FLAGS 0x3f800
#define ixSMU_PM_STATUS_95 0x3ff7c
#define ixCG_THERMAL_INT_CTRL 0xc2100028
#define ixGENERAL_PWRMGT 0xc0200000
#define ixCNB_PWRMGT_CNTL 0xc0200004
#define ixSCLK_PWRMGT_CNTL 0xc0200008
#define ixTARGET_AND_CURRENT_PROFILE_INDEX 0xc0200014
#define ixCG_FREQ_TRAN_VOTING_0 0xc02001a8
#define ixCG_DISPLAY_GAP_CNTL 0xc0200060
#define ixCG_DISPLAY_GAP_CNTL2 0xc0200230
#define ixCG_ULV_PARAMETER 0xc020015c
#define ixLCAC_SX0_OVR_SEL 0xc0400d04
#define ixLCAC_SX0_OVR_VAL 0xc0400d08
#define ixLCAC_MC0_CNTL 0xc0400d30
#define ixLCAC_MC0_OVR_SEL 0xc0400d34
#define ixLCAC_MC0_OVR_VAL 0xc0400d38
#define ixLCAC_MC1_CNTL 0xc0400d3c
#define ixLCAC_MC1_OVR_SEL 0xc0400d40
#define ixLCAC_MC1_OVR_VAL 0xc0400d44
#define ixLCAC_MC2_OVR_SEL 0xc0400d4c
#define ixLCAC_MC2_OVR_VAL 0xc0400d50
#define ixLCAC_MC3_OVR_SEL 0xc0400d58
#define ixLCAC_MC3_OVR_VAL 0xc0400d5c
#define ixLCAC_CPL_CNTL 0xc0400d80
#define ixLCAC_CPL_OVR_SEL 0xc0400d84
#define ixLCAC_CPL_OVR_VAL 0xc0400d88
#define ixROM_CNTL 0xc0600000
#define ixCGTT_ROM_CLK_CTRL0 0xc060000c
#define ixROM_INDEX 0xc0600010
#define ixROM_DATA 0xc0600014
#endif /* SMU_7_1_0_D_H */
