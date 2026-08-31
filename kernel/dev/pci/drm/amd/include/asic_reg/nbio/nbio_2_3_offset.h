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
#ifndef _nbio_2_3_OFFSET_HEADER
#define _nbio_2_3_OFFSET_HEADER

// addressBlock: nbio_nbif0_bif_bx_SYSDEC
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
// addressBlock: nbio_nbif0_syshub_mmreg_syshubdec
// base address: 0x0
#define mmSYSHUB_INDEX 0x0008
#define mmSYSHUB_INDEX_BASE_IDX 0
#define mmSYSHUB_DATA 0x0009
#define mmSYSHUB_DATA_BASE_IDX 0
// addressBlock: nbio_nbif0_rcc_strap_BIFDEC1
// base address: 0x0
#define mmRCC_BIF_STRAP0 0x0000
#define mmRCC_BIF_STRAP0_BASE_IDX 2
#define mmRCC_BIF_STRAP2 0x0002
#define mmRCC_BIF_STRAP2_BASE_IDX 2
#define mmRCC_BIF_STRAP3 0x0003
#define mmRCC_BIF_STRAP3_BASE_IDX 2
#define mmRCC_BIF_STRAP5 0x0005
#define mmRCC_BIF_STRAP5_BASE_IDX 2
#define mmRCC_DEV0_EPF0_STRAP0 0x0011
#define mmRCC_DEV0_EPF0_STRAP0_BASE_IDX 2
// addressBlock: nbio_nbif0_rcc_dev0_epf0_BIFPFVFDEC1[13440..14975]
// base address: 0x3480
#define mmRCC_DEV0_EPF0_RCC_DOORBELL_APER_EN 0x00c0
#define mmRCC_DEV0_EPF0_RCC_DOORBELL_APER_EN_BASE_IDX 2
#define mmRCC_DEV0_EPF0_RCC_CONFIG_MEMSIZE 0x00c3
#define mmRCC_DEV0_EPF0_RCC_CONFIG_MEMSIZE_BASE_IDX 2
// addressBlock: nbio_nbif0_rcc_dev0_BIFDEC1
// base address: 0x0
#define mmRCC_BACO_CNTL_MISC_BASE_IDX 2
// addressBlock: nbio_nbif0_bif_bx_BIFDEC1
// base address: 0x0
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
#define mmBIF_INTR_CNTL 0x0100
#define mmBIF_INTR_CNTL_BASE_IDX 2
#define mmBACO_CNTL 0x010b
#define mmBACO_CNTL_BASE_IDX 2
#define mmREMAP_HDP_MEM_FLUSH_CNTL 0x012d
#define mmREMAP_HDP_MEM_FLUSH_CNTL_BASE_IDX 2
#define mmREMAP_HDP_REG_FLUSH_CNTL 0x012e
#define mmREMAP_HDP_REG_FLUSH_CNTL_BASE_IDX 2
#define mmBIF_RB_CNTL 0x012f
#define mmBIF_RB_CNTL_BASE_IDX 2
// addressBlock: nbio_nbif0_bif_bx_pf_BIFPFVFDEC1
// base address: 0x0
#define mmBIF_BX_PF_DOORBELL_SELFRING_GPA_APER_BASE_HIGH 0x00f3
#define mmBIF_BX_PF_DOORBELL_SELFRING_GPA_APER_BASE_HIGH_BASE_IDX 2
#define mmBIF_BX_PF_DOORBELL_SELFRING_GPA_APER_BASE_LOW 0x00f4
#define mmBIF_BX_PF_DOORBELL_SELFRING_GPA_APER_BASE_LOW_BASE_IDX 2
#define mmBIF_BX_PF_DOORBELL_SELFRING_GPA_APER_CNTL 0x00f5
#define mmBIF_BX_PF_DOORBELL_SELFRING_GPA_APER_CNTL_BASE_IDX 2
#define mmBIF_BX_PF_GPU_HDP_FLUSH_REQ 0x0106
#define mmBIF_BX_PF_GPU_HDP_FLUSH_REQ_BASE_IDX 2
#define mmBIF_BX_PF_GPU_HDP_FLUSH_DONE 0x0107
#define mmBIF_BX_PF_GPU_HDP_FLUSH_DONE_BASE_IDX 2
// addressBlock: nbio_nbif0_gdc_GDCDEC
// base address: 0x0
#define mmBIF_SDMA0_DOORBELL_RANGE 0x01d0
#define mmBIF_SDMA0_DOORBELL_RANGE_BASE_IDX 2
#define mmBIF_SDMA1_DOORBELL_RANGE 0x01d1
#define mmBIF_SDMA1_DOORBELL_RANGE_BASE_IDX 2
#define mmBIF_IH_DOORBELL_RANGE 0x01d2
#define mmBIF_IH_DOORBELL_RANGE_BASE_IDX 2
#define mmBIF_MMSCH0_DOORBELL_RANGE 0x01d3
#define mmBIF_MMSCH0_DOORBELL_RANGE_BASE_IDX 2
// addressBlock: nbio_nbif0_bif_bx_dev0_epf0_vf0_BIFPFVFDEC1
// base address: 0x0
#define mmBIF_BX_DEV0_EPF0_VF0_HDP_MEM_COHERENCY_FLUSH_CNTL 0x00f7
#define mmBIF_BX_DEV0_EPF0_VF0_HDP_MEM_COHERENCY_FLUSH_CNTL_BASE_IDX 2
#endif
