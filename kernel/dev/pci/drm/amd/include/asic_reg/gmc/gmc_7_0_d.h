/*
 * GMC_7_0 Register documentation
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

#ifndef GMC_7_0_D_H
#define GMC_7_0_D_H

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
#define mmMC_FUS_DRAM0_BANK_ADDR_MAPPING 0xa11
#define mmMC_FUS_DRAM1_BANK_ADDR_MAPPING 0xa12
#endif /* GMC_7_0_D_H */
