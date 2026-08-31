/*
 * Copyright 2020 Advanced Micro Devices, Inc.
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
#ifndef _vcn_2_6_0_OFFSET_HEADER
#define _vcn_2_6_0_OFFSET_HEADER

// addressBlock: uvd0_ecpudec
// base address: 0x1fd00
#define regUVD_VCPU_CACHE_OFFSET0 0x0140
#define regUVD_VCPU_CACHE_OFFSET0_BASE_IDX 1
#define regUVD_VCPU_CACHE_SIZE0 0x0141
#define regUVD_VCPU_CACHE_SIZE0_BASE_IDX 1
#define regUVD_VCPU_CACHE_OFFSET1 0x0142
#define regUVD_VCPU_CACHE_OFFSET1_BASE_IDX 1
#define regUVD_VCPU_CACHE_SIZE1 0x0143
#define regUVD_VCPU_CACHE_SIZE1_BASE_IDX 1
#define regUVD_VCPU_CACHE_OFFSET2 0x0144
#define regUVD_VCPU_CACHE_OFFSET2_BASE_IDX 1
#define regUVD_VCPU_CACHE_SIZE2 0x0145
#define regUVD_VCPU_CACHE_SIZE2_BASE_IDX 1
#define regUVD_VCPU_NONCACHE_OFFSET0 0x0152
#define regUVD_VCPU_NONCACHE_OFFSET0_BASE_IDX 1
#define regUVD_VCPU_NONCACHE_SIZE0 0x0153
#define regUVD_VCPU_NONCACHE_SIZE0_BASE_IDX 1
#define regUVD_VCPU_CNTL 0x0156
#define regUVD_VCPU_CNTL_BASE_IDX 1
// addressBlock: uvd0_jpegnpdec
// base address: 0x1e200
#define regUVD_JPEG_INT_STAT 0x008b
#define regUVD_JPEG_INT_STAT_BASE_IDX 0
#define regUVD_JPEG_PITCH 0x009f
#define regUVD_JPEG_PITCH_BASE_IDX 0
#define regUVD_JPEG_UV_PITCH 0x00a0
#define regUVD_JPEG_UV_PITCH_BASE_IDX 0
#define regJPEG_DEC_GFX8_ADDR_CONFIG 0x00a3
#define regJPEG_DEC_GFX8_ADDR_CONFIG_BASE_IDX 0
#define regJPEG_DEC_Y_GFX10_TILING_SURFACE 0x00a4
#define regJPEG_DEC_Y_GFX10_TILING_SURFACE_BASE_IDX 0
#define regJPEG_DEC_UV_GFX10_TILING_SURFACE 0x00a5
#define regJPEG_DEC_UV_GFX10_TILING_SURFACE_BASE_IDX 0
#define regJPEG_DEC_GFX10_ADDR_CONFIG 0x00a6
#define regJPEG_DEC_GFX10_ADDR_CONFIG_BASE_IDX 0
#define regJPEG_DEC_ADDR_MODE 0x00a7
#define regJPEG_DEC_ADDR_MODE_BASE_IDX 0
// addressBlock: uvd0_lmi_adpdec
// base address: 0x20870
#define regUVD_LMI_VCPU_NC0_64BIT_BAR_LOW 0x0438
#define regUVD_LMI_VCPU_NC0_64BIT_BAR_LOW_BASE_IDX 1
#define regUVD_LMI_VCPU_NC0_64BIT_BAR_HIGH 0x0439
#define regUVD_LMI_VCPU_NC0_64BIT_BAR_HIGH_BASE_IDX 1
#define regUVD_LMI_VCPU_CACHE_64BIT_BAR_LOW 0x043c
#define regUVD_LMI_VCPU_CACHE_64BIT_BAR_LOW_BASE_IDX 1
#define regUVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH 0x043d
#define regUVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH_BASE_IDX 1
#define regUVD_LMI_VCPU_CACHE1_64BIT_BAR_LOW 0x0468
#define regUVD_LMI_VCPU_CACHE1_64BIT_BAR_LOW_BASE_IDX 1
#define regUVD_LMI_VCPU_CACHE1_64BIT_BAR_HIGH 0x0469
#define regUVD_LMI_VCPU_CACHE1_64BIT_BAR_HIGH_BASE_IDX 1
#define regUVD_LMI_VCPU_CACHE2_64BIT_BAR_LOW 0x046c
#define regUVD_LMI_VCPU_CACHE2_64BIT_BAR_LOW_BASE_IDX 1
#define regUVD_LMI_VCPU_CACHE2_64BIT_BAR_HIGH 0x046d
#define regUVD_LMI_VCPU_CACHE2_64BIT_BAR_HIGH_BASE_IDX 1
#define regUVD_LMI_CTRL2 0x04a6
#define regUVD_LMI_CTRL2_BASE_IDX 1
#define regUVD_LMI_CTRL 0x04a8
#define regUVD_LMI_CTRL_BASE_IDX 1
#define regUVD_LMI_STATUS 0x04a9
#define regUVD_LMI_STATUS_BASE_IDX 1
#define regVCN_RAS_CNTL 0x04b9
#define regVCN_RAS_CNTL_BASE_IDX 1
// addressBlock: uvd0_mmsch_dec
// base address: 0x1e000
#define regMMSCH_VF_VMID 0x000b
#define regMMSCH_VF_VMID_BASE_IDX 0
#define regMMSCH_VF_CTX_ADDR_LO 0x000c
#define regMMSCH_VF_CTX_ADDR_LO_BASE_IDX 0
#define regMMSCH_VF_CTX_ADDR_HI 0x000d
#define regMMSCH_VF_CTX_ADDR_HI_BASE_IDX 0
#define regMMSCH_VF_CTX_SIZE 0x000e
#define regMMSCH_VF_CTX_SIZE_BASE_IDX 0
#define regMMSCH_VF_MAILBOX_HOST 0x0012
#define regMMSCH_VF_MAILBOX_HOST_BASE_IDX 0
#define regMMSCH_VF_MAILBOX_RESP 0x0013
#define regMMSCH_VF_MAILBOX_RESP_BASE_IDX 0
// addressBlock: uvd0_uvd_jmi_dec
// base address: 0x1e500
#define regUVD_LMI_JRBC_RB_VMID 0x0150
#define regUVD_LMI_JRBC_RB_VMID_BASE_IDX 0
#define regUVD_LMI_JRBC_RB_64BIT_BAR_LOW 0x0166
#define regUVD_LMI_JRBC_RB_64BIT_BAR_LOW_BASE_IDX 0
#define regUVD_LMI_JRBC_RB_64BIT_BAR_HIGH 0x0167
#define regUVD_LMI_JRBC_RB_64BIT_BAR_HIGH_BASE_IDX 0
#define regUVD_JMI_CNTL 0x0192
#define regUVD_JMI_CNTL_BASE_IDX 0
// addressBlock: uvd0_uvd_jpeg_common_dec
// base address: 0x1e700
#define regJPEG_SYS_INT_EN 0x01c1
#define regJPEG_SYS_INT_EN_BASE_IDX 0
#define regJPEG_SYS_INT_STATUS 0x01c2
#define regJPEG_SYS_INT_STATUS_BASE_IDX 0
// addressBlock: uvd0_uvd_jpeg_common_sclk_dec
// base address: 0x1e780
#define regJPEG_CGC_GATE 0x01e0
#define regJPEG_CGC_GATE_BASE_IDX 0
#define regJPEG_CGC_CTRL 0x01e1
#define regJPEG_CGC_CTRL_BASE_IDX 0
// addressBlock: uvd0_uvd_jrbc_dec
// base address: 0x1e400
#define regUVD_JRBC_RB_WPTR 0x0100
#define regUVD_JRBC_RB_WPTR_BASE_IDX 0
#define regUVD_JRBC_RB_CNTL 0x0101
#define regUVD_JRBC_RB_CNTL_BASE_IDX 0
#define regUVD_JRBC_STATUS 0x0109
#define regUVD_JRBC_STATUS_BASE_IDX 0
#define regUVD_JRBC_RB_RPTR 0x010a
#define regUVD_JRBC_RB_RPTR_BASE_IDX 0
#define regUVD_JRBC_RB_SIZE 0x0113
#define regUVD_JRBC_RB_SIZE_BASE_IDX 0
#define regUVD_JRBC_SCRATCH0 0x0114
#define regUVD_JRBC_SCRATCH0_BASE_IDX 0
// addressBlock: uvd0_uvd_mpcdec
// base address: 0x20310
#define regUVD_MPC_CNTL 0x02cc
#define regUVD_MPC_CNTL_BASE_IDX 1
#define regUVD_MPC_SET_MUXA0 0x02ce
#define regUVD_MPC_SET_MUXA0_BASE_IDX 1
#define regUVD_MPC_SET_MUXB0 0x02d0
#define regUVD_MPC_SET_MUXB0_BASE_IDX 1
#define regUVD_MPC_SET_MUX 0x02d2
#define regUVD_MPC_SET_MUX_BASE_IDX 1
// addressBlock: uvd0_uvd_pg_dec
// base address: 0x1f800
#define regUVD_PGFSM_CONFIG 0x0000
#define regUVD_PGFSM_CONFIG_BASE_IDX 1
#define regUVD_PGFSM_STATUS 0x0001
#define regUVD_PGFSM_STATUS_BASE_IDX 1
#define regUVD_POWER_STATUS 0x0004
#define regUVD_POWER_STATUS_BASE_IDX 1
#define regUVD_JPEG_POWER_STATUS 0x000a
#define regUVD_JPEG_POWER_STATUS_BASE_IDX 1
#define regUVD_DPG_LMA_CTL 0x0011
#define regUVD_DPG_LMA_CTL_BASE_IDX 1
#define regUVD_DPG_LMA_DATA 0x0012
#define regUVD_DPG_LMA_DATA_BASE_IDX 1
#define regUVD_DPG_LMA_MASK 0x0013
#define regUVD_DPG_LMA_MASK_BASE_IDX 1
#define regUVD_DPG_PAUSE 0x0014
#define regUVD_DPG_PAUSE_BASE_IDX 1
#define regUVD_GFX8_ADDR_CONFIG 0x0049
#define regUVD_GFX8_ADDR_CONFIG_BASE_IDX 1
#define regUVD_GFX10_ADDR_CONFIG 0x004a
#define regUVD_GFX10_ADDR_CONFIG_BASE_IDX 1
#define regUVD_RAS_VCPU_VCODEC_STATUS 0x0057
#define regUVD_RAS_VCPU_VCODEC_STATUS_BASE_IDX 1
#define regUVD_RAS_JPEG0_STATUS 0x0059
#define regUVD_RAS_JPEG0_STATUS_BASE_IDX 1
#define regUVD_RAS_JPEG1_STATUS 0x005a
#define regUVD_RAS_JPEG1_STATUS_BASE_IDX 1
// addressBlock: uvd0_uvd_rbcdec
// base address: 0x20370
#define regUVD_RBC_RB_CNTL 0x02de
#define regUVD_RBC_RB_CNTL_BASE_IDX 1
// addressBlock: uvd0_uvddec
// base address: 0x1fa00
#define regUVD_STATUS 0x0080
#define regUVD_STATUS_BASE_IDX 1
#define regUVD_SOFT_RESET 0x0084
#define regUVD_SOFT_RESET_BASE_IDX 1
#define regUVD_CGC_GATE 0x0088
#define regUVD_CGC_GATE_BASE_IDX 1
#define regUVD_CGC_CTRL 0x008a
#define regUVD_CGC_CTRL_BASE_IDX 1
#define regUVD_SUVD_CGC_GATE 0x008c
#define regUVD_SUVD_CGC_GATE_BASE_IDX 1
#define regUVD_SUVD_CGC_CTRL 0x008e
#define regUVD_SUVD_CGC_CTRL_BASE_IDX 1
#define regUVD_GPCOM_VCPU_CMD 0x008f
#define regUVD_GPCOM_VCPU_CMD_BASE_IDX 1
#define regUVD_GPCOM_VCPU_DATA0 0x0090
#define regUVD_GPCOM_VCPU_DATA0_BASE_IDX 1
#define regUVD_GPCOM_VCPU_DATA1 0x0091
#define regUVD_GPCOM_VCPU_DATA1_BASE_IDX 1
#define regUVD_MASTINT_EN 0x00a1
#define regUVD_MASTINT_EN_BASE_IDX 1
#define regUVD_SYS_INT_EN 0x00a2
#define regUVD_SYS_INT_EN_BASE_IDX 1
#define regUVD_CONTEXT_ID 0x00a7
#define regUVD_CONTEXT_ID_BASE_IDX 1
#define regUVD_CONTEXT_ID2 0x00a8
#define regUVD_CONTEXT_ID2_BASE_IDX 1
#define regUVD_RB_BASE_LO 0x00aa
#define regUVD_RB_BASE_LO_BASE_IDX 1
#define regUVD_RB_BASE_HI 0x00ab
#define regUVD_RB_BASE_HI_BASE_IDX 1
#define regUVD_RB_SIZE 0x00ac
#define regUVD_RB_SIZE_BASE_IDX 1
#define regUVD_RB_RPTR 0x00ad
#define regUVD_RB_RPTR_BASE_IDX 1
#define regUVD_RB_WPTR 0x00ae
#define regUVD_RB_WPTR_BASE_IDX 1
#define regUVD_RB_BASE_LO2 0x00af
#define regUVD_RB_BASE_LO2_BASE_IDX 1
#define regUVD_RB_BASE_HI2 0x00b0
#define regUVD_RB_BASE_HI2_BASE_IDX 1
#define regUVD_RB_SIZE2 0x00b1
#define regUVD_RB_SIZE2_BASE_IDX 1
#define regUVD_RB_RPTR2 0x00b2
#define regUVD_RB_RPTR2_BASE_IDX 1
#define regUVD_RB_WPTR2 0x00b3
#define regUVD_RB_WPTR2_BASE_IDX 1
#define regUVD_RB_BASE_LO3 0x00b4
#define regUVD_RB_BASE_LO3_BASE_IDX 1
#define regUVD_RB_BASE_HI3 0x00b5
#define regUVD_RB_BASE_HI3_BASE_IDX 1
#define regUVD_RB_SIZE3 0x00b6
#define regUVD_RB_SIZE3_BASE_IDX 1
#define regUVD_RB_RPTR3 0x00b7
#define regUVD_RB_RPTR3_BASE_IDX 1
#define regUVD_RB_WPTR3 0x00b8
#define regUVD_RB_WPTR3_BASE_IDX 1
#define regUVD_RB_BASE_LO4 0x00b9
#define regUVD_RB_BASE_LO4_BASE_IDX 1
#define regUVD_RB_BASE_HI4 0x00ba
#define regUVD_RB_BASE_HI4_BASE_IDX 1
#define regUVD_RB_SIZE4 0x00bb
#define regUVD_RB_SIZE4_BASE_IDX 1
#define regUVD_RB_RPTR4 0x00bc
#define regUVD_RB_RPTR4_BASE_IDX 1
#define regUVD_RB_WPTR4 0x00bd
#define regUVD_RB_WPTR4_BASE_IDX 1
#define regUVD_RB_ARB_CTRL 0x00c6
#define regUVD_RB_ARB_CTRL_BASE_IDX 1
#endif
