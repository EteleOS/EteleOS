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
#ifndef _nbio_6_1_OFFSET_HEADER
#define _nbio_6_1_OFFSET_HEADER

// addressBlock: nbio_nbif_bif_bx_pf_SYSPFVFDEC[0..767]
// base address: 0x0
#define mmMM_INDEX 0x0000
#define mmMM_INDEX_BASE_IDX 0
#define mmMM_DATA 0x0001
#define mmMM_DATA_BASE_IDX 0
#define mmMM_INDEX_HI 0x0006
#define mmMM_INDEX_HI_BASE_IDX 0
// addressBlock: nbio_nbif_bif_bx_pf_SYSDEC[0..767]
// base address: 0x0
#define mmPCIE_INDEX 0x000c
#define mmPCIE_INDEX_BASE_IDX 0
#define mmPCIE_DATA 0x000d
#define mmPCIE_DATA_BASE_IDX 0
#define mmPCIE_INDEX2 0x000e
#define mmPCIE_INDEX2_BASE_IDX 0
#define mmPCIE_DATA2 0x000f
#define mmPCIE_DATA2_BASE_IDX 0
#define mmBIOS_SCRATCH_0 0x0038
#define mmBIOS_SCRATCH_0_BASE_IDX 1
#define mmBIOS_SCRATCH_1 0x0039
#define mmBIOS_SCRATCH_1_BASE_IDX 1
#define mmBIOS_SCRATCH_2 0x003a
#define mmBIOS_SCRATCH_2_BASE_IDX 1
#define mmBIOS_SCRATCH_3 0x003b
#define mmBIOS_SCRATCH_3_BASE_IDX 1
#define mmBIOS_SCRATCH_4 0x003c
#define mmBIOS_SCRATCH_4_BASE_IDX 1
#define mmBIOS_SCRATCH_5 0x003d
#define mmBIOS_SCRATCH_5_BASE_IDX 1
#define mmBIOS_SCRATCH_6 0x003e
#define mmBIOS_SCRATCH_6_BASE_IDX 1
#define mmBIOS_SCRATCH_7 0x003f
#define mmBIOS_SCRATCH_7_BASE_IDX 1
#define mmBIOS_SCRATCH_8 0x0040
#define mmBIOS_SCRATCH_8_BASE_IDX 1
#define mmBIOS_SCRATCH_9 0x0041
#define mmBIOS_SCRATCH_9_BASE_IDX 1
#define mmBIOS_SCRATCH_10 0x0042
#define mmBIOS_SCRATCH_10_BASE_IDX 1
#define mmBIOS_SCRATCH_11 0x0043
#define mmBIOS_SCRATCH_11_BASE_IDX 1
#define mmBIOS_SCRATCH_12 0x0044
#define mmBIOS_SCRATCH_12_BASE_IDX 1
#define mmBIOS_SCRATCH_13 0x0045
#define mmBIOS_SCRATCH_13_BASE_IDX 1
#define mmBIOS_SCRATCH_14 0x0046
#define mmBIOS_SCRATCH_14_BASE_IDX 1
#define mmBIOS_SCRATCH_15 0x0047
#define mmBIOS_SCRATCH_15_BASE_IDX 1
// addressBlock: nbio_nbif_syshub_mmreg_ind_syshubdec[32..39]
// base address: 0x20
#define mmSYSHUB_INDEX 0x0008
#define mmSYSHUB_INDEX_BASE_IDX 0
#define mmSYSHUB_DATA 0x0009
#define mmSYSHUB_DATA_BASE_IDX 0
// addressBlock: nbio_nbif_rcc_strap_BIFDEC1[13440..14975]
// base address: 0x3480
#define mmRCC_BIF_STRAP0 0x0000
#define mmRCC_BIF_STRAP0_BASE_IDX 2
#define mmRCC_DEV0_EPF0_STRAP0 0x000f
#define mmRCC_DEV0_EPF0_STRAP0_BASE_IDX 2
// addressBlock: nbio_nbif_rcc_pf_0_BIFPFVFDEC1[13440..14975]
// base address: 0x3480
#define mmRCC_PF_0_0_RCC_DOORBELL_APER_EN 0x00c0
#define mmRCC_PF_0_0_RCC_DOORBELL_APER_EN_BASE_IDX 2
#define mmRCC_PF_0_0_RCC_CONFIG_MEMSIZE 0x00c3
#define mmRCC_PF_0_0_RCC_CONFIG_MEMSIZE_BASE_IDX 2
// addressBlock: nbio_nbif_rcc_pf_0_BIFDEC1[13440..14975]
// base address: 0x3480
#define mmRCC_BACO_CNTL_MISC_BASE_IDX 2
// addressBlock: nbio_nbif_bif_bx_pf_BIFDEC1[13440..14975]
// base address: 0x3480
#define mmBUS_CNTL 0x00e7
#define mmBUS_CNTL_BASE_IDX 2
#define mmINTERRUPT_CNTL 0x00f1
#define mmINTERRUPT_CNTL_BASE_IDX 2
#define mmINTERRUPT_CNTL2 0x00f2
#define mmINTERRUPT_CNTL2_BASE_IDX 2
#define mmBIF_DOORBELL_CNTL 0x00fc
#define mmBIF_DOORBELL_CNTL_BASE_IDX 2
#define mmBIF_DOORBELL_INT_CNTL 0x00fd
#define mmBIF_DOORBELL_INT_CNTL_BASE_IDX 2
#define mmBIF_FB_EN 0x00ff
#define mmBIF_FB_EN_BASE_IDX 2
#define mmBACO_CNTL 0x010b
#define mmBACO_CNTL_BASE_IDX 2
#define mmREMAP_HDP_MEM_FLUSH_CNTL 0x012d
#define mmREMAP_HDP_MEM_FLUSH_CNTL_BASE_IDX 2
#define mmREMAP_HDP_REG_FLUSH_CNTL 0x012e
#define mmREMAP_HDP_REG_FLUSH_CNTL_BASE_IDX 2
#define mmBIF_RB_CNTL 0x012f
#define mmBIF_RB_CNTL_BASE_IDX 2
// addressBlock: nbio_nbif_bif_bx_pf_BIFPFVFDEC1
// base address: 0x0
#define mmBIF_BX_PF0_DOORBELL_SELFRING_GPA_APER_BASE_HIGH 0x00f3
#define mmBIF_BX_PF0_DOORBELL_SELFRING_GPA_APER_BASE_HIGH_BASE_IDX 2
#define mmBIF_BX_PF0_DOORBELL_SELFRING_GPA_APER_BASE_LOW 0x00f4
#define mmBIF_BX_PF0_DOORBELL_SELFRING_GPA_APER_BASE_LOW_BASE_IDX 2
#define mmBIF_BX_PF0_DOORBELL_SELFRING_GPA_APER_CNTL 0x00f5
#define mmBIF_BX_PF0_DOORBELL_SELFRING_GPA_APER_CNTL_BASE_IDX 2
#define mmBIF_BX_PF0_GPU_HDP_FLUSH_REQ 0x0106
#define mmBIF_BX_PF0_GPU_HDP_FLUSH_REQ_BASE_IDX 2
#define mmBIF_BX_PF0_GPU_HDP_FLUSH_DONE 0x0107
#define mmBIF_BX_PF0_GPU_HDP_FLUSH_DONE_BASE_IDX 2
#define mmBIF_BX_PF0_MAILBOX_MSGBUF_TRN_DW0 0x0136
#define mmBIF_BX_PF0_MAILBOX_MSGBUF_TRN_DW0_BASE_IDX 2
#define mmBIF_BX_PF0_MAILBOX_MSGBUF_TRN_DW1 0x0137
#define mmBIF_BX_PF0_MAILBOX_MSGBUF_TRN_DW1_BASE_IDX 2
#define mmBIF_BX_PF0_MAILBOX_MSGBUF_TRN_DW2 0x0138
#define mmBIF_BX_PF0_MAILBOX_MSGBUF_TRN_DW2_BASE_IDX 2
#define mmBIF_BX_PF0_MAILBOX_MSGBUF_TRN_DW3 0x0139
#define mmBIF_BX_PF0_MAILBOX_MSGBUF_TRN_DW3_BASE_IDX 2
#define mmBIF_BX_PF0_MAILBOX_MSGBUF_RCV_DW0 0x013a
#define mmBIF_BX_PF0_MAILBOX_MSGBUF_RCV_DW0_BASE_IDX 2
#define mmBIF_BX_PF0_MAILBOX_MSGBUF_RCV_DW2 0x013c
#define mmBIF_BX_PF0_MAILBOX_MSGBUF_RCV_DW2_BASE_IDX 2
#define mmBIF_BX_PF0_MAILBOX_CONTROL 0x013e
#define mmBIF_BX_PF0_MAILBOX_CONTROL_BASE_IDX 2
#define mmBIF_BX_PF0_MAILBOX_INT_CNTL 0x013f
#define mmBIF_BX_PF0_MAILBOX_INT_CNTL_BASE_IDX 2
// addressBlock: nbio_nbif_gdc_GDCDEC[14976..15487]
// base address: 0x3a80
#define mmBIF_SDMA0_DOORBELL_RANGE 0x01d0
#define mmBIF_SDMA0_DOORBELL_RANGE_BASE_IDX 2
#define mmBIF_SDMA1_DOORBELL_RANGE 0x01d1
#define mmBIF_SDMA1_DOORBELL_RANGE_BASE_IDX 2
#define mmBIF_IH_DOORBELL_RANGE 0x01d2
#define mmBIF_IH_DOORBELL_RANGE_BASE_IDX 2
#define mmBIF_MMSCH0_DOORBELL_RANGE 0x01d3
#define mmBIF_MMSCH0_DOORBELL_RANGE_BASE_IDX 2
// addressBlock: nbio_nbif_rcc_dev0_epf0_vf0_BIFPFVFDEC1
// base address: 0x0
// addressBlock: nbio_nbif_bif_bx_dev0_epf0_vf0_BIFPFVFDEC1
// base address: 0x0
#define mmBIF_BX_DEV0_EPF0_VF0_HDP_MEM_COHERENCY_FLUSH_CNTL 0x00f7
#define mmBIF_BX_DEV0_EPF0_VF0_HDP_MEM_COHERENCY_FLUSH_CNTL_BASE_IDX 2
// addressBlock: syshub_mmreg_ind_syshubind
// base address: 0x0
#define ixSYSHUB_MMREG_IND_SYSHUB_MGCG_CTRL_SOCCLK 0x10310
#define ixSYSHUB_MMREG_IND_SYSHUB_MGCG_CTRL_SHUBCLK 0x11040
#endif
