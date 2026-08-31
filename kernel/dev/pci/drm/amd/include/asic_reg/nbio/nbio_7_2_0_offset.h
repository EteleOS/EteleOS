/*
 * Copyright (C) 2020  Advanced Micro Devices, Inc.
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
#ifndef _nbio_7_2_0_OFFSET_HEADER
#define _nbio_7_2_0_OFFSET_HEADER

// addressBlock: nbio_nbif0_bif_bx_pf_SYSPFVFDEC:1
// base address: 0x0
#define regBIF_BX_PF0_RSMU_INDEX 0x0000
#define regBIF_BX_PF0_RSMU_INDEX_BASE_IDX 1
#define regBIF_BX_PF0_RSMU_DATA 0x0001
#define regBIF_BX_PF0_RSMU_DATA_BASE_IDX 1
// addressBlock: nbio_nbif0_bif_bx_SYSDEC:1
// base address: 0x0
#define regBIF_BX0_PCIE_INDEX2 0x000e
#define regBIF_BX0_PCIE_INDEX2_BASE_IDX 0
#define regBIF_BX0_PCIE_DATA2 0x000f
#define regBIF_BX0_PCIE_DATA2_BASE_IDX 0
// addressBlock: nbio_nbif0_rcc_strap_BIFDEC1
// base address: 0x0
#define regRCC_STRAP0_RCC_BIF_STRAP2 0x0002
#define regRCC_STRAP0_RCC_BIF_STRAP2_BASE_IDX 2
#define regRCC_STRAP0_RCC_BIF_STRAP3 0x0003
#define regRCC_STRAP0_RCC_BIF_STRAP3_BASE_IDX 2
#define regRCC_STRAP0_RCC_BIF_STRAP5 0x0005
#define regRCC_STRAP0_RCC_BIF_STRAP5_BASE_IDX 2
#define regRCC_STRAP0_RCC_DEV0_EPF0_STRAP0 0x0011
#define regRCC_STRAP0_RCC_DEV0_EPF0_STRAP0_BASE_IDX 2
// addressBlock: nbio_nbif0_rcc_ep_dev0_BIFDEC1:1
// base address: 0x0
#define regRCC_EP_DEV0_0_EP_PCIE_TX_LTR_CNTL 0x0030
#define regRCC_EP_DEV0_0_EP_PCIE_TX_LTR_CNTL_BASE_IDX 2
// addressBlock: nbio_nbif0_rcc_dev0_epf0_BIFPFVFDEC1
// base address: 0x0
#define regRCC_DEV0_EPF0_0_RCC_DOORBELL_APER_EN 0x00c0
#define regRCC_DEV0_EPF0_0_RCC_DOORBELL_APER_EN_BASE_IDX 2
#define regRCC_DEV0_EPF0_0_RCC_CONFIG_MEMSIZE 0x00c3
#define regRCC_DEV0_EPF0_0_RCC_CONFIG_MEMSIZE_BASE_IDX 2
// addressBlock: nbio_nbif0_bif_bx_BIFDEC1:1
// base address: 0x0
#define regBIF_BX0_INTERRUPT_CNTL 0x00f1
#define regBIF_BX0_INTERRUPT_CNTL_BASE_IDX 2
#define regBIF_BX0_INTERRUPT_CNTL2 0x00f2
#define regBIF_BX0_INTERRUPT_CNTL2_BASE_IDX 2
#define regBIF_BX0_BIF_DOORBELL_INT_CNTL 0x00fd
#define regBIF_BX0_BIF_DOORBELL_INT_CNTL_BASE_IDX 2
#define regBIF_BX0_BIF_FB_EN 0x00ff
#define regBIF_BX0_BIF_FB_EN_BASE_IDX 2
#define regBIF_BX0_REMAP_HDP_MEM_FLUSH_CNTL 0x012d
#define regBIF_BX0_REMAP_HDP_MEM_FLUSH_CNTL_BASE_IDX 2
#define regBIF_BX0_REMAP_HDP_REG_FLUSH_CNTL 0x012e
#define regBIF_BX0_REMAP_HDP_REG_FLUSH_CNTL_BASE_IDX 2
// addressBlock: nbio_nbif0_bif_bx_pf_BIFPFVFDEC1:1
// base address: 0x0
#define regBIF_BX_PF0_DOORBELL_SELFRING_GPA_APER_BASE_HIGH 0x00f3
#define regBIF_BX_PF0_DOORBELL_SELFRING_GPA_APER_BASE_HIGH_BASE_IDX 2
#define regBIF_BX_PF0_DOORBELL_SELFRING_GPA_APER_BASE_LOW 0x00f4
#define regBIF_BX_PF0_DOORBELL_SELFRING_GPA_APER_BASE_LOW_BASE_IDX 2
#define regBIF_BX_PF0_DOORBELL_SELFRING_GPA_APER_CNTL 0x00f5
#define regBIF_BX_PF0_DOORBELL_SELFRING_GPA_APER_CNTL_BASE_IDX 2
#define regBIF_BX_PF0_HDP_MEM_COHERENCY_FLUSH_CNTL 0x00f7
#define regBIF_BX_PF0_HDP_MEM_COHERENCY_FLUSH_CNTL_BASE_IDX 2
#define regBIF_BX_PF0_GPU_HDP_FLUSH_REQ 0x0106
#define regBIF_BX_PF0_GPU_HDP_FLUSH_REQ_BASE_IDX 2
#define regBIF_BX_PF0_GPU_HDP_FLUSH_DONE 0x0107
#define regBIF_BX_PF0_GPU_HDP_FLUSH_DONE_BASE_IDX 2
// addressBlock: nbio_nbif0_gdc_GDCDEC
// base address: 0x1400000
#define regGDC0_BIF_SDMA0_DOORBELL_RANGE 0x4f0af0
#define regGDC0_BIF_SDMA0_DOORBELL_RANGE_BASE_IDX 3
#define regGDC0_BIF_IH_DOORBELL_RANGE 0x4f0af2
#define regGDC0_BIF_IH_DOORBELL_RANGE_BASE_IDX 3
#define regGDC0_BIF_VCN0_DOORBELL_RANGE 0x4f0af3
#define regGDC0_BIF_VCN0_DOORBELL_RANGE_BASE_IDX 3
// addressBlock: nbio_nbif0_bif_bx_SYSDEC
// base address: 0x10120000
#define regBIF_BX1_PCIE_INDEX2 0x800e
#define regBIF_BX1_PCIE_INDEX2_BASE_IDX 5
#define regBIF_BX1_PCIE_DATA2 0x800f
#define regBIF_BX1_PCIE_DATA2_BASE_IDX 5
#define regBIF_BX1_BIOS_SCRATCH_2 0x804e
#define regBIF_BX1_BIOS_SCRATCH_2_BASE_IDX 5
#define regBIF_BX1_BIOS_SCRATCH_3 0x804f
#define regBIF_BX1_BIOS_SCRATCH_3_BASE_IDX 5
#define regBIF_BX1_BIOS_SCRATCH_6 0x8052
#define regBIF_BX1_BIOS_SCRATCH_6_BASE_IDX 5
// addressBlock: nbio_nbif0_rcc_strap_BIFDEC1:1
// base address: 0x10120000
#define regRCC_STRAP1_RCC_DEV0_EPF0_STRAP0 0x8d31
#define regRCC_STRAP1_RCC_DEV0_EPF0_STRAP0_BASE_IDX 5
// addressBlock: nbio_nbif0_bif_bx_BIFDEC1
// base address: 0x10120000
#define regBIF_BX1_INTERRUPT_CNTL 0x8e11
#define regBIF_BX1_INTERRUPT_CNTL_BASE_IDX 5
#define regBIF_BX1_INTERRUPT_CNTL2 0x8e12
#define regBIF_BX1_INTERRUPT_CNTL2_BASE_IDX 5
#define regBIF_BX1_BIF_FB_EN 0x8e1f
#define regBIF_BX1_BIF_FB_EN_BASE_IDX 5
// addressBlock: nbio_nbif0_bif_bx_pf_BIFPFVFDEC1
// base address: 0x10120000
#define regBIF_BX_PF1_DOORBELL_SELFRING_GPA_APER_BASE_HIGH 0x8e13
#define regBIF_BX_PF1_DOORBELL_SELFRING_GPA_APER_BASE_HIGH_BASE_IDX 5
#define regBIF_BX_PF1_DOORBELL_SELFRING_GPA_APER_BASE_LOW 0x8e14
#define regBIF_BX_PF1_DOORBELL_SELFRING_GPA_APER_BASE_LOW_BASE_IDX 5
#define regBIF_BX_PF1_DOORBELL_SELFRING_GPA_APER_CNTL 0x8e15
#define regBIF_BX_PF1_DOORBELL_SELFRING_GPA_APER_CNTL_BASE_IDX 5
#define regBIF_BX_PF1_HDP_MEM_COHERENCY_FLUSH_CNTL 0x8e17
#define regBIF_BX_PF1_HDP_MEM_COHERENCY_FLUSH_CNTL_BASE_IDX 5
#define regBIF_BX_PF1_GPU_HDP_FLUSH_REQ 0x8e26
#define regBIF_BX_PF1_GPU_HDP_FLUSH_REQ_BASE_IDX 5
#define regBIF_BX_PF1_GPU_HDP_FLUSH_DONE 0x8e27
#define regBIF_BX_PF1_GPU_HDP_FLUSH_DONE_BASE_IDX 5
// addressBlock: nbio_nbif0_rcc_strap_rcc_strap_internal
// base address: 0x10100000
#define regRCC_DEV0_EPF2_STRAP2 0xd102
#define regRCC_DEV0_EPF2_STRAP2_BASE_IDX 5
#define regRCC_DEV0_EPF5_STRAP4 0xd284
#define regRCC_DEV0_EPF5_STRAP4_BASE_IDX 5
#define regRCC_DEV0_EPF6_STRAP4 0xd304
#define regRCC_DEV0_EPF6_STRAP4_BASE_IDX 5
#define regRCC_DEV2_EPF0_STRAP2 0xd802
#define regRCC_DEV2_EPF0_STRAP2_BASE_IDX 5
// addressBlock: nbio_pcie0_pciedir
// base address: 0x11180000
#define regPCIE_CONFIG_CNTL 0x420011
#define regPCIE_CONFIG_CNTL_BASE_IDX 5
#define regPCIE_CNTL2 0x42001c
#define regPCIE_CNTL2_BASE_IDX 5
#define regCPM_CONTROL 0x420118
#define regCPM_CONTROL_BASE_IDX 5
// addressBlock: nbio_nbif0_bif_bx_SYSDEC
// base address: 0xd0000000
#define regBIF_BX2_BIOS_SCRATCH_2 0x2ffc004e
#define regBIF_BX2_BIOS_SCRATCH_2_BASE_IDX 5
#define regBIF_BX2_BIOS_SCRATCH_3 0x2ffc004f
#define regBIF_BX2_BIOS_SCRATCH_3_BASE_IDX 5
#define regBIF_BX2_BIOS_SCRATCH_6 0x2ffc0052
#define regBIF_BX2_BIOS_SCRATCH_6_BASE_IDX 5
#endif
