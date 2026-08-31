/*
 * GMC_7_1 Register documentation
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

#ifndef GMC_7_1_D_H
#define GMC_7_1_D_H

#define mmMC_ARB_MISC3 0x9cd
#define mmMC_ARB_RAMCFG 0x9d8
#define mmMC_ARB_DRAM_TIMING 0x9dd
#define mmMC_ARB_DRAM_TIMING2 0x9de
#define mmMC_ARB_WTM_CNTL_RD 0x9df
#define mmMC_ARB_WTM_GRPWT_RD 0x9e1
#define mmMC_ARB_RFSH_RATE 0x9ec
#define mmMC_ARB_DRAM_TIMING_1 0x9fc
#define mmMC_ARB_DRAM_TIMING2_1 0x9ff
#define mmMC_ARB_BURST_TIME 0xa02
#define mmMC_CG_CONFIG 0x96f
#define mmMC_CITF_MISC_RD_CG 0x992
#define mmMC_CITF_MISC_WR_CG 0x993
#define mmMC_CITF_MISC_VM_CG 0x994
#define mmMC_HUB_MISC_HUB_CG 0x82e
#define mmMC_HUB_MISC_VM_CG 0x82f
#define mmMC_HUB_MISC_SIP_CG 0x830
#define mmMC_HUB_RDREQ_DMIF_LIMIT 0x848
#define mmMC_HUB_RDREQ_UVD 0x861
#define mmMC_HUB_WDP_UMC 0x877
#define mmMC_SHARED_CHMAP 0x801
#define mmMC_RD_GRP_OTH 0x807
#define mmMC_VM_FB_LOCATION 0x809
#define mmMC_VM_AGP_TOP 0x80a
#define mmMC_VM_AGP_BOT 0x80b
#define mmMC_VM_AGP_BASE 0x80c
#define mmMC_VM_SYSTEM_APERTURE_LOW_ADDR 0x80d
#define mmMC_VM_SYSTEM_APERTURE_HIGH_ADDR 0x80e
#define mmMC_VM_SYSTEM_APERTURE_DEFAULT_ADDR 0x80f
#define mmMC_VM_MX_L1_TLB_CNTL 0x819
#define mmMC_VM_FB_OFFSET 0x81a
#define mmMC_MEM_POWER_LS 0x82a
#define mmMC_SHARED_BLACKOUT_CNTL 0x82b
#define mmMC_XPB_P2P_BAR_CFG 0x903
#define mmMC_XPB_CLK_GAT 0x91e
#define mmATC_MISC_CG 0xcd4
#define mmATC_VMID_PASID_MAPPING_UPDATE_STATUS 0xce6
#define mmATC_VMID0_PASID_MAPPING 0xce7
#define mmGMCON_RENG_RAM_INDEX 0xd40
#define mmGMCON_RENG_RAM_DATA 0xd41
#define mmGMCON_RENG_EXECUTE 0xd42
#define mmGMCON_MISC 0xd43
#define mmGMCON_MISC2 0xd44
#define mmGMCON_PGFSM_CONFIG 0xd4e
#define mmGMCON_PGFSM_WRITE 0xd4f
#define mmGMCON_MISC3 0xd51
#define mmGMCON_LPT_TARGET 0xd53
#define mmGMCON_DEBUG 0xd5f
#define mmVM_L2_CNTL 0x500
#define mmVM_L2_CNTL2 0x501
#define mmVM_L2_CNTL3 0x502
#define mmVM_CONTEXT0_CNTL 0x504
#define mmVM_CONTEXT1_CNTL 0x505
#define mmVM_CONTEXT0_CNTL2 0x50c
#define mmVM_CONTEXT1_CNTL2 0x50d
#define mmVM_CONTEXT8_PAGE_TABLE_BASE_ADDR 0x50e
#define mmVM_INVALIDATE_REQUEST 0x51e
#define mmVM_INVALIDATE_RESPONSE 0x51f
#define mmVM_PRT_APERTURE0_LOW_ADDR 0x52c
#define mmVM_PRT_APERTURE1_LOW_ADDR 0x52d
#define mmVM_PRT_APERTURE2_LOW_ADDR 0x52e
#define mmVM_PRT_APERTURE3_LOW_ADDR 0x52f
#define mmVM_PRT_APERTURE0_HIGH_ADDR 0x530
#define mmVM_PRT_APERTURE1_HIGH_ADDR 0x531
#define mmVM_PRT_APERTURE2_HIGH_ADDR 0x532
#define mmVM_PRT_APERTURE3_HIGH_ADDR 0x533
#define mmVM_PRT_CNTL 0x534
#define mmVM_CONTEXT1_PROTECTION_FAULT_STATUS 0x537
#define mmVM_CONTEXT1_PROTECTION_FAULT_MCCLIENT 0x539
#define mmVM_CONTEXT1_PROTECTION_FAULT_ADDR 0x53f
#define mmVM_CONTEXT0_PROTECTION_FAULT_DEFAULT_ADDR 0x546
#define mmVM_CONTEXT1_PROTECTION_FAULT_DEFAULT_ADDR 0x547
#define mmVM_CONTEXT0_PAGE_TABLE_BASE_ADDR 0x54f
#define mmVM_CONTEXT0_PAGE_TABLE_START_ADDR 0x557
#define mmVM_CONTEXT1_PAGE_TABLE_START_ADDR 0x558
#define mmVM_CONTEXT0_PAGE_TABLE_END_ADDR 0x55f
#define mmVM_CONTEXT1_PAGE_TABLE_END_ADDR 0x560
#define mmVM_L2_CG 0x570
#define mmVM_L2_CONTEXT1_IDENTITY_APERTURE_LOW_ADDR 0x575
#define mmVM_L2_CONTEXT1_IDENTITY_APERTURE_HIGH_ADDR 0x576
#define mmVM_L2_CONTEXT_IDENTITY_PHYSICAL_OFFSET 0x577
#define mmMC_SEQ_CNTL_2 0xad4
#define mmMC_SEQ_DRAM 0xa26
#define mmMC_SEQ_RAS_TIMING 0xa28
#define mmMC_SEQ_CAS_TIMING 0xa29
#define mmMC_SEQ_MISC_TIMING 0xa2a
#define mmMC_SEQ_MISC_TIMING2 0xa2b
#define mmMC_SEQ_PMG_TIMING 0xa2c
#define mmMC_SEQ_RD_CTL_D0 0xa2d
#define mmMC_SEQ_RD_CTL_D1 0xa2e
#define mmMC_SEQ_WR_CTL_D0 0xa2f
#define mmMC_SEQ_WR_CTL_D1 0xa30
#define mmMC_SEQ_WR_CTL_2 0xad5
#define mmMC_PMG_CMD_EMRS 0xa83
#define mmMC_PMG_CMD_MRS 0xaab
#define mmMC_PMG_CMD_MRS1 0xad1
#define mmMC_PMG_CMD_MRS2 0xad7
#define mmMC_PMG_AUTO_CMD 0xa34
#define mmMC_PMG_AUTO_CFG 0xa35
#define mmMC_SEQ_TRAIN_WAKEUP_CNTL 0xa3a
#define mmMC_IO_RXCNTL_DPHY0_D0 0xa4c
#define mmMC_IO_RXCNTL_DPHY1_D0 0xa4d
#define mmMC_IO_RXCNTL_DPHY0_D1 0xa52
#define mmMC_IO_RXCNTL_DPHY1_D1 0xa53
#define mmMC_SEQ_MISC0 0xa80
#define mmMC_SEQ_MISC1 0xa81
#define mmMC_SEQ_RESERVE_M 0xa82
#define mmMC_SEQ_SUP_CNTL 0xa32
#define mmMC_SEQ_SUP_PGM 0xa33
#define mmMC_SEQ_MISC5 0xa95
#define mmMC_SEQ_MISC6 0xa96
#define mmMC_SEQ_MISC7 0xa99
#define mmMC_SEQ_RAS_TIMING_LP 0xa9b
#define mmMC_SEQ_CAS_TIMING_LP 0xa9c
#define mmMC_SEQ_MISC_TIMING_LP 0xa9d
#define mmMC_SEQ_MISC_TIMING2_LP 0xa9e
#define mmMC_SEQ_RD_CTL_D0_LP 0xac7
#define mmMC_SEQ_RD_CTL_D1_LP 0xac8
#define mmMC_SEQ_WR_CTL_D0_LP 0xa9f
#define mmMC_SEQ_WR_CTL_D1_LP 0xaa0
#define mmMC_SEQ_WR_CTL_2_LP 0xad6
#define mmMC_SEQ_PMG_CMD_EMRS_LP 0xaa1
#define mmMC_SEQ_PMG_CMD_MRS_LP 0xaa2
#define mmMC_SEQ_PMG_CMD_MRS1_LP 0xad2
#define mmMC_SEQ_PMG_CMD_MRS2_LP 0xad8
#define mmMC_SEQ_PMG_TIMING_LP 0xad3
#define mmMCLK_PWRMGT_CNTL 0xae8
#define mmDLL_CNTL 0xae9
#define mmMPLL_CNTL_MODE 0xaec
#define mmMPLL_FUNC_CNTL 0xaed
#define mmMPLL_FUNC_CNTL_1 0xaee
#define mmMPLL_FUNC_CNTL_2 0xaef
#define mmMPLL_AD_FUNC_CNTL 0xaf0
#define mmMPLL_DQ_FUNC_CNTL 0xaf1
#define mmMPLL_SS1 0xaf3
#define mmMPLL_SS2 0xaf4
#define mmMPLL_CONTROL 0xaf5
#define mmMC_SEQ_PMG_PG_HWCNTL 0xab9
#define mmMC_SEQ_IO_DEBUG_INDEX 0xa91
#define mmMC_SEQ_IO_DEBUG_DATA 0xa92
#define ixMC_IO_DEBUG_UP_13 0xd
#define ixMC_IO_DEBUG_UP_159 0x9f
#define mmMC_SEQ_G5PDX_CTRL 0xd81
#define mmMC_SEQ_G5PDX_CTRL_LP 0xd82
#define mmMC_SEQ_G5PDX_CMD0 0xd83
#define mmMC_SEQ_G5PDX_CMD0_LP 0xd84
#define mmMC_SEQ_G5PDX_CMD1 0xd85
#define mmMC_SEQ_G5PDX_CMD1_LP 0xd86
#define mmMC_SEQ_PMG_DVS_CTL 0xd8a
#define mmMC_SEQ_PMG_DVS_CTL_LP 0xd8b
#define mmMC_SEQ_PMG_DVS_CMD 0xd8c
#define mmMC_SEQ_PMG_DVS_CMD_LP 0xd8d
#define mmMC_SEQ_DLL_STBY 0xd8e
#define mmMC_SEQ_DLL_STBY_LP 0xd8f
#endif /* GMC_7_1_D_H */
