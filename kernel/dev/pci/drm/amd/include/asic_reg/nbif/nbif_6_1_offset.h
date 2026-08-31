/*
 * Copyright (C) 2017  Advanced Micro Devices, Inc.
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
#ifndef _nbif_6_1_OFFSET_HEADER
#define _nbif_6_1_OFFSET_HEADER

// addressBlock: gdc_GDCDEC
// base address: 0x1400000
#define mmBIF_SDMA0_DOORBELL_RANGE 0x4f0af0 // duplicate
#define mmBIF_SDMA0_DOORBELL_RANGE_BASE_IDX 3
#define mmBIF_SDMA1_DOORBELL_RANGE 0x4f0af1 // duplicate
#define mmBIF_SDMA1_DOORBELL_RANGE_BASE_IDX 3
#define mmBIF_IH_DOORBELL_RANGE 0x4f0af2 // duplicate
#define mmBIF_IH_DOORBELL_RANGE_BASE_IDX 3
#define mmBIF_MMSCH0_DOORBELL_RANGE 0x4f0af3 // duplicate
#define mmBIF_MMSCH0_DOORBELL_RANGE_BASE_IDX 3
// memoryMap:EP0F0Reg
// addressBlock: bif_bx_pf_SYSDEC
// base address: 0x0
#define mmBIOS_SCRATCH_0 0x004c // duplicate
#define mmBIOS_SCRATCH_0_BASE_IDX 0
#define mmBIOS_SCRATCH_1 0x004d // duplicate
#define mmBIOS_SCRATCH_1_BASE_IDX 0
#define mmBIOS_SCRATCH_2 0x004e // duplicate
#define mmBIOS_SCRATCH_2_BASE_IDX 0
#define mmBIOS_SCRATCH_3 0x004f // duplicate
#define mmBIOS_SCRATCH_3_BASE_IDX 0
#define mmBIOS_SCRATCH_4 0x0050 // duplicate
#define mmBIOS_SCRATCH_4_BASE_IDX 0
#define mmBIOS_SCRATCH_5 0x0051 // duplicate
#define mmBIOS_SCRATCH_5_BASE_IDX 0
#define mmBIOS_SCRATCH_6 0x0052 // duplicate
#define mmBIOS_SCRATCH_6_BASE_IDX 0
#define mmBIOS_SCRATCH_7 0x0053 // duplicate
#define mmBIOS_SCRATCH_7_BASE_IDX 0
#define mmBIOS_SCRATCH_8 0x0054 // duplicate
#define mmBIOS_SCRATCH_8_BASE_IDX 0
#define mmBIOS_SCRATCH_9 0x0055 // duplicate
#define mmBIOS_SCRATCH_9_BASE_IDX 0
#define mmBIOS_SCRATCH_10 0x0056 // duplicate
#define mmBIOS_SCRATCH_10_BASE_IDX 0
#define mmBIOS_SCRATCH_11 0x0057 // duplicate
#define mmBIOS_SCRATCH_11_BASE_IDX 0
#define mmBIOS_SCRATCH_12 0x0058 // duplicate
#define mmBIOS_SCRATCH_12_BASE_IDX 0
#define mmBIOS_SCRATCH_13 0x0059 // duplicate
#define mmBIOS_SCRATCH_13_BASE_IDX 0
#define mmBIOS_SCRATCH_14 0x005a // duplicate
#define mmBIOS_SCRATCH_14_BASE_IDX 0
#define mmBIOS_SCRATCH_15 0x005b // duplicate
#define mmBIOS_SCRATCH_15_BASE_IDX 0
// addressBlock: bif_bx_pf_SYSPFVFDEC
// base address: 0x0
#define mmMM_INDEX 0x0000 // duplicate
#define mmMM_INDEX_BASE_IDX 0
#define mmMM_DATA 0x0001 // duplicate
#define mmMM_DATA_BASE_IDX 0
#define mmMM_INDEX_HI 0x0006 // duplicate
#define mmMM_INDEX_HI_BASE_IDX 0
#define mmPCIE_INDEX 0x000c // duplicate
#define mmPCIE_INDEX_BASE_IDX 0
#define mmPCIE_DATA 0x000d // duplicate
#define mmPCIE_DATA_BASE_IDX 0
#define mmPCIE_INDEX2 0x000e // duplicate
#define mmPCIE_INDEX2_BASE_IDX 0
#define mmPCIE_DATA2 0x000f // duplicate
#define mmPCIE_DATA2_BASE_IDX 0
// addressBlock: bif_bx_pf_BIFDEC1
// base address: 0x0
#define mmBUS_CNTL 0x0e07 // duplicate
#define mmBUS_CNTL_BASE_IDX 0
#define mmINTERRUPT_CNTL 0x0e11 // duplicate
#define mmINTERRUPT_CNTL_BASE_IDX 0
#define mmINTERRUPT_CNTL2 0x0e12 // duplicate
#define mmINTERRUPT_CNTL2_BASE_IDX 0
#define mmBIF_CLK_CTRL 0x0e1a // duplicate
#define mmBIF_CLK_CTRL_BASE_IDX 0
#define mmBIF_DOORBELL_CNTL 0x0e1c // duplicate
#define mmBIF_DOORBELL_CNTL_BASE_IDX 0
#define mmBIF_DOORBELL_INT_CNTL 0x0e1d // duplicate
#define mmBIF_DOORBELL_INT_CNTL_BASE_IDX 0
#define mmBIF_FB_EN 0x0e1f // duplicate
#define mmBIF_FB_EN_BASE_IDX 0
#define mmBACO_CNTL 0x0e2b // duplicate
#define mmBACO_CNTL_BASE_IDX 0
#define mmREMAP_HDP_MEM_FLUSH_CNTL 0x0e4d // duplicate
#define mmREMAP_HDP_MEM_FLUSH_CNTL_BASE_IDX 0
#define mmREMAP_HDP_REG_FLUSH_CNTL 0x0e4e // duplicate
#define mmREMAP_HDP_REG_FLUSH_CNTL_BASE_IDX 0
#define mmBIF_RB_CNTL 0x0e4f // duplicate
#define mmBIF_RB_CNTL_BASE_IDX 0
// addressBlock: rcc_pf_0_BIFDEC1
// base address: 0x0
#define mmRCC_BACO_CNTL_MISC_BASE_IDX 0
// addressBlock: rcc_strap_BIFDEC1
// base address: 0x0
#define mmRCC_DEV0_EPF0_STRAP0 0x0d2f // duplicate
#define mmRCC_DEV0_EPF0_STRAP0_BASE_IDX 0
// addressBlock: bif_bx_pf_BIFPFVFDEC1
// base address: 0x0
#define mmDOORBELL_SELFRING_GPA_APER_BASE_HIGH 0x0e13 // duplicate
#define mmDOORBELL_SELFRING_GPA_APER_BASE_HIGH_BASE_IDX 0
#define mmDOORBELL_SELFRING_GPA_APER_BASE_LOW 0x0e14 // duplicate
#define mmDOORBELL_SELFRING_GPA_APER_BASE_LOW_BASE_IDX 0
#define mmDOORBELL_SELFRING_GPA_APER_CNTL 0x0e15 // duplicate
#define mmDOORBELL_SELFRING_GPA_APER_CNTL_BASE_IDX 0
#define mmHDP_REG_COHERENCY_FLUSH_CNTL 0x0e16 // duplicate
#define mmHDP_REG_COHERENCY_FLUSH_CNTL_BASE_IDX 0
#define mmHDP_MEM_COHERENCY_FLUSH_CNTL 0x0e17 // duplicate
#define mmHDP_MEM_COHERENCY_FLUSH_CNTL_BASE_IDX 0
#define mmGPU_HDP_FLUSH_REQ 0x0e26 // duplicate
#define mmGPU_HDP_FLUSH_REQ_BASE_IDX 0
#define mmGPU_HDP_FLUSH_DONE 0x0e27 // duplicate
#define mmGPU_HDP_FLUSH_DONE_BASE_IDX 0
#define mmMAILBOX_MSGBUF_TRN_DW0 0x0e56 // duplicate
#define mmMAILBOX_MSGBUF_TRN_DW0_BASE_IDX 0
#define mmMAILBOX_MSGBUF_TRN_DW1 0x0e57 // duplicate
#define mmMAILBOX_MSGBUF_TRN_DW1_BASE_IDX 0
#define mmMAILBOX_MSGBUF_TRN_DW2 0x0e58 // duplicate
#define mmMAILBOX_MSGBUF_TRN_DW2_BASE_IDX 0
#define mmMAILBOX_MSGBUF_TRN_DW3 0x0e59 // duplicate
#define mmMAILBOX_MSGBUF_TRN_DW3_BASE_IDX 0
#define mmMAILBOX_MSGBUF_RCV_DW0 0x0e5a // duplicate
#define mmMAILBOX_MSGBUF_RCV_DW0_BASE_IDX 0
#define mmMAILBOX_MSGBUF_RCV_DW1 0x0e5b // duplicate
#define mmMAILBOX_MSGBUF_RCV_DW1_BASE_IDX 0
#define mmMAILBOX_MSGBUF_RCV_DW2 0x0e5c // duplicate
#define mmMAILBOX_MSGBUF_RCV_DW2_BASE_IDX 0
#define mmMAILBOX_MSGBUF_RCV_DW3 0x0e5d // duplicate
#define mmMAILBOX_MSGBUF_RCV_DW3_BASE_IDX 0
#define mmMAILBOX_CONTROL 0x0e5e // duplicate
#define mmMAILBOX_CONTROL_BASE_IDX 0
#define mmMAILBOX_INT_CNTL 0x0e5f // duplicate
#define mmMAILBOX_INT_CNTL_BASE_IDX 0
// addressBlock: rcc_pf_0_BIFPFVFDEC1
// base address: 0x0
#define mmRCC_DOORBELL_APER_EN 0x0de0 // duplicate
#define mmRCC_DOORBELL_APER_EN_BASE_IDX 0
#define mmRCC_CONFIG_MEMSIZE 0x0de3 // duplicate
#define mmRCC_CONFIG_MEMSIZE_BASE_IDX 0
#ifndef mmRCC_IOV_FUNC_IDENTIFIER
#define mmRCC_IOV_FUNC_IDENTIFIER 0x0de5 // duplicate
#define mmRCC_IOV_FUNC_IDENTIFIER_BASE_IDX 0
#endif
// addressBlock: syshub_mmreg_ind_syshubdec
// base address: 0x0
#define mmSYSHUB_INDEX 0x0008
#define mmSYSHUB_INDEX_BASE_IDX 0
#define mmSYSHUB_DATA 0x0009
#define mmSYSHUB_DATA_BASE_IDX 0
#endif
