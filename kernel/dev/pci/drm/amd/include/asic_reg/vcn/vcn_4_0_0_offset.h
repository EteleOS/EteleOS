/*
 * Copyright 2021 Advanced Micro Devices, Inc.
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
#ifndef _vcn_4_0_0_OFFSET_HEADER
#define _vcn_4_0_0_OFFSET_HEADER

// addressBlock: uvd0_uvddec
// base address: 0x1fb00
#define regUVD_CGC_GATE 0x00c1
#define regUVD_CGC_GATE_BASE_IDX 1
#define regUVD_CGC_CTRL 0x00c2
#define regUVD_CGC_CTRL_BASE_IDX 1
#define regUVD_SUVD_CGC_GATE 0x00c4
#define regUVD_SUVD_CGC_GATE_BASE_IDX 1
#define regUVD_SUVD_CGC_CTRL 0x00c6
#define regUVD_SUVD_CGC_CTRL_BASE_IDX 1
#define regUVD_GPCOM_VCPU_DATA0 0x00d0
#define regUVD_GPCOM_VCPU_DATA0_BASE_IDX 1
#define regUVD_GPCOM_VCPU_DATA1 0x00d1
#define regUVD_GPCOM_VCPU_DATA1_BASE_IDX 1
#define regUVD_MASTINT_EN 0x00e1
#define regUVD_MASTINT_EN_BASE_IDX 1
#define regUVD_SYS_INT_EN 0x00e2
#define regUVD_SYS_INT_EN_BASE_IDX 1
#define regUVD_CONTEXT_ID 0x00e7
#define regUVD_CONTEXT_ID_BASE_IDX 1
#define regUVD_CONTEXT_ID2 0x00e8
#define regUVD_CONTEXT_ID2_BASE_IDX 1
#define regUVD_RB_BASE_LO 0x00ea
#define regUVD_RB_BASE_LO_BASE_IDX 1
#define regUVD_RB_BASE_HI 0x00eb
#define regUVD_RB_BASE_HI_BASE_IDX 1
#define regUVD_RB_SIZE 0x00ec
#define regUVD_RB_SIZE_BASE_IDX 1
#define regUVD_RB_BASE_LO2 0x00ef
#define regUVD_RB_BASE_LO2_BASE_IDX 1
#define regUVD_RB_BASE_HI2 0x00f0
#define regUVD_RB_BASE_HI2_BASE_IDX 1
#define regUVD_RB_SIZE2 0x00f1
#define regUVD_RB_SIZE2_BASE_IDX 1
#define regUVD_RB_BASE_LO3 0x00f4
#define regUVD_RB_BASE_LO3_BASE_IDX 1
#define regUVD_RB_BASE_HI3 0x00f5
#define regUVD_RB_BASE_HI3_BASE_IDX 1
#define regUVD_RB_SIZE3 0x00f6
#define regUVD_RB_SIZE3_BASE_IDX 1
#define regUVD_RB_BASE_LO4 0x00f9
#define regUVD_RB_BASE_LO4_BASE_IDX 1
#define regUVD_RB_BASE_HI4 0x00fa
#define regUVD_RB_BASE_HI4_BASE_IDX 1
#define regUVD_RB_SIZE4 0x00fb
#define regUVD_RB_SIZE4_BASE_IDX 1
#define regUVD_RB_ARB_CTRL 0x0106
#define regUVD_RB_ARB_CTRL_BASE_IDX 1
#define regUVD_VCPU_INT_EN2 0x013d
#define regUVD_VCPU_INT_EN2_BASE_IDX 1
#define regUVD_STATUS 0x0143
#define regUVD_STATUS_BASE_IDX 1
#define regUVD_SOFT_RESET 0x0147
#define regUVD_SOFT_RESET_BASE_IDX 1
#define regUVD_GPCOM_VCPU_CMD 0x0152
#define regUVD_GPCOM_VCPU_CMD_BASE_IDX 1
// addressBlock: uvd0_ecpudec
// base address: 0x1fe00
#define regUVD_VCPU_CACHE_OFFSET0 0x0180
#define regUVD_VCPU_CACHE_OFFSET0_BASE_IDX 1
#define regUVD_VCPU_CACHE_SIZE0 0x0181
#define regUVD_VCPU_CACHE_SIZE0_BASE_IDX 1
#define regUVD_VCPU_CACHE_OFFSET1 0x0182
#define regUVD_VCPU_CACHE_OFFSET1_BASE_IDX 1
#define regUVD_VCPU_CACHE_SIZE1 0x0183
#define regUVD_VCPU_CACHE_SIZE1_BASE_IDX 1
#define regUVD_VCPU_CACHE_OFFSET2 0x0184
#define regUVD_VCPU_CACHE_OFFSET2_BASE_IDX 1
#define regUVD_VCPU_CACHE_SIZE2 0x0185
#define regUVD_VCPU_CACHE_SIZE2_BASE_IDX 1
#define regUVD_VCPU_NONCACHE_OFFSET0 0x0192
#define regUVD_VCPU_NONCACHE_OFFSET0_BASE_IDX 1
#define regUVD_VCPU_NONCACHE_SIZE0 0x0193
#define regUVD_VCPU_NONCACHE_SIZE0_BASE_IDX 1
#define regUVD_VCPU_CNTL 0x0196
#define regUVD_VCPU_CNTL_BASE_IDX 1
// addressBlock: uvd0_uvd_mpcdec
// base address: 0x1ff30
#define regUVD_MPC_CNTL 0x01d4
#define regUVD_MPC_CNTL_BASE_IDX 1
#define regUVD_MPC_SET_MUXA0 0x01d6
#define regUVD_MPC_SET_MUXA0_BASE_IDX 1
#define regUVD_MPC_SET_MUXB0 0x01d8
#define regUVD_MPC_SET_MUXB0_BASE_IDX 1
#define regUVD_MPC_SET_MUX 0x01da
#define regUVD_MPC_SET_MUX_BASE_IDX 1
// addressBlock: uvd0_uvd_rbcdec
// base address: 0x1ff90
#define regUVD_RBC_RB_CNTL 0x01e6
#define regUVD_RBC_RB_CNTL_BASE_IDX 1
// addressBlock: uvd0_lmi_adpdec
// base address: 0x20090
#define regUVD_LMI_VCPU_NC0_64BIT_BAR_LOW 0x0240
#define regUVD_LMI_VCPU_NC0_64BIT_BAR_LOW_BASE_IDX 1
#define regUVD_LMI_VCPU_NC0_64BIT_BAR_HIGH 0x0241
#define regUVD_LMI_VCPU_NC0_64BIT_BAR_HIGH_BASE_IDX 1
#define regUVD_LMI_VCPU_CACHE_64BIT_BAR_LOW 0x0244
#define regUVD_LMI_VCPU_CACHE_64BIT_BAR_LOW_BASE_IDX 1
#define regUVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH 0x0245
#define regUVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH_BASE_IDX 1
#define regUVD_LMI_VCPU_CACHE1_64BIT_BAR_LOW 0x0270
#define regUVD_LMI_VCPU_CACHE1_64BIT_BAR_LOW_BASE_IDX 1
#define regUVD_LMI_VCPU_CACHE1_64BIT_BAR_HIGH 0x0271
#define regUVD_LMI_VCPU_CACHE1_64BIT_BAR_HIGH_BASE_IDX 1
#define regUVD_LMI_VCPU_CACHE2_64BIT_BAR_LOW 0x0274
#define regUVD_LMI_VCPU_CACHE2_64BIT_BAR_LOW_BASE_IDX 1
#define regUVD_LMI_VCPU_CACHE2_64BIT_BAR_HIGH 0x0275
#define regUVD_LMI_VCPU_CACHE2_64BIT_BAR_HIGH_BASE_IDX 1
#define regUVD_LMI_CTRL2 0x02ae
#define regUVD_LMI_CTRL2_BASE_IDX 1
#define regUVD_LMI_CTRL 0x02b0
#define regUVD_LMI_CTRL_BASE_IDX 1
#define regUVD_LMI_STATUS 0x02b1
#define regUVD_LMI_STATUS_BASE_IDX 1
#define regVCN_RAS_CNTL 0x02df
#define regVCN_RAS_CNTL_BASE_IDX 1
// addressBlock: uvd0_jpegnpdec
// base address: 0x20f00
#define regUVD_JPEG_INT_STAT 0x05cb
#define regUVD_JPEG_INT_STAT_BASE_IDX 1
#define regUVD_JPEG_PITCH 0x05df
#define regUVD_JPEG_PITCH_BASE_IDX 1
#define regUVD_JPEG_UV_PITCH 0x05e0
#define regUVD_JPEG_UV_PITCH_BASE_IDX 1
#define regJPEG_DEC_GFX8_ADDR_CONFIG 0x05e3
#define regJPEG_DEC_GFX8_ADDR_CONFIG_BASE_IDX 1
#define regJPEG_DEC_Y_GFX10_TILING_SURFACE 0x05e4
#define regJPEG_DEC_Y_GFX10_TILING_SURFACE_BASE_IDX 1
#define regJPEG_DEC_UV_GFX10_TILING_SURFACE 0x05e5
#define regJPEG_DEC_UV_GFX10_TILING_SURFACE_BASE_IDX 1
#define regJPEG_DEC_GFX10_ADDR_CONFIG 0x05e6
#define regJPEG_DEC_GFX10_ADDR_CONFIG_BASE_IDX 1
#define regJPEG_DEC_ADDR_MODE 0x05e7
#define regJPEG_DEC_ADDR_MODE_BASE_IDX 1
// addressBlock: uvd0_uvd_jrbc_dec
// base address: 0x21100
#define regUVD_JRBC_RB_WPTR 0x0640
#define regUVD_JRBC_RB_WPTR_BASE_IDX 1
#define regUVD_JRBC_RB_CNTL 0x0641
#define regUVD_JRBC_RB_CNTL_BASE_IDX 1
#define regUVD_JRBC_STATUS 0x0649
#define regUVD_JRBC_STATUS_BASE_IDX 1
#define regUVD_JRBC_RB_RPTR 0x064a
#define regUVD_JRBC_RB_RPTR_BASE_IDX 1
#define regUVD_JRBC_RB_SIZE 0x0653
#define regUVD_JRBC_RB_SIZE_BASE_IDX 1
#define regUVD_JRBC_SCRATCH0 0x0654
#define regUVD_JRBC_SCRATCH0_BASE_IDX 1
// addressBlock: uvd0_uvd_jmi_dec
// base address: 0x21200
#define regUVD_LMI_JRBC_RB_VMID 0x0690
#define regUVD_LMI_JRBC_RB_VMID_BASE_IDX 1
#define regUVD_LMI_JRBC_RB_64BIT_BAR_LOW 0x06a6
#define regUVD_LMI_JRBC_RB_64BIT_BAR_LOW_BASE_IDX 1
#define regUVD_LMI_JRBC_RB_64BIT_BAR_HIGH 0x06a7
#define regUVD_LMI_JRBC_RB_64BIT_BAR_HIGH_BASE_IDX 1
#define regUVD_JMI_CNTL 0x06d2
#define regUVD_JMI_CNTL_BASE_IDX 1
// addressBlock: uvd0_uvd_jpeg_common_dec
// base address: 0x21400
#define regJPEG_SYS_INT_EN 0x0701
#define regJPEG_SYS_INT_EN_BASE_IDX 1
#define regJPEG_SYS_INT_STATUS 0x0702
#define regJPEG_SYS_INT_STATUS_BASE_IDX 1
// addressBlock: uvd0_uvd_jpeg_common_sclk_dec
// base address: 0x21480
#define regJPEG_CGC_GATE 0x0720
#define regJPEG_CGC_GATE_BASE_IDX 1
#define regJPEG_CGC_CTRL 0x0721
#define regJPEG_CGC_CTRL_BASE_IDX 1
// addressBlock: uvd0_uvd_pg_dec
// base address: 0x1f800
#define regUVD_PGFSM_CONFIG 0x0000
#define regUVD_PGFSM_CONFIG_BASE_IDX 1
#define regUVD_PGFSM_STATUS 0x0001
#define regUVD_PGFSM_STATUS_BASE_IDX 1
#define regUVD_POWER_STATUS 0x0002
#define regUVD_POWER_STATUS_BASE_IDX 1
#define regUVD_JPEG_POWER_STATUS 0x0003
#define regUVD_JPEG_POWER_STATUS_BASE_IDX 1
#define regUVD_DPG_LMA_CTL 0x0011
#define regUVD_DPG_LMA_CTL_BASE_IDX 1
#define regUVD_DPG_LMA_DATA 0x0012
#define regUVD_DPG_LMA_DATA_BASE_IDX 1
#define regUVD_DPG_LMA_MASK 0x0013
#define regUVD_DPG_LMA_MASK_BASE_IDX 1
#define regUVD_DPG_PAUSE 0x0014
#define regUVD_DPG_PAUSE_BASE_IDX 1
#define regUVD_GFX8_ADDR_CONFIG 0x0041
#define regUVD_GFX8_ADDR_CONFIG_BASE_IDX 1
#define regUVD_GFX10_ADDR_CONFIG 0x0042
#define regUVD_GFX10_ADDR_CONFIG_BASE_IDX 1
#define regUVD_RAS_VCPU_VCODEC_STATUS 0x0057
#define regUVD_RAS_VCPU_VCODEC_STATUS_BASE_IDX 1
#define regUVD_RAS_JPEG0_STATUS 0x0059
#define regUVD_RAS_JPEG0_STATUS_BASE_IDX 1
#define regUVD_RAS_JPEG1_STATUS 0x005a
#define regUVD_RAS_JPEG1_STATUS_BASE_IDX 1
#define regVCN_JPEG_DB_CTRL 0x0071
#define regVCN_JPEG_DB_CTRL_BASE_IDX 1
#define regVCN_RB1_DB_CTRL 0x0072
#define regVCN_RB1_DB_CTRL_BASE_IDX 1
#define regVCN_UMSCH_RB_DB_CTRL 0x0076
#define regVCN_UMSCH_RB_DB_CTRL_BASE_IDX 1
#define regVCN_AGDB_CTRL0 0x0079
#define regVCN_AGDB_CTRL0_BASE_IDX 1
#define regVCN_AGDB_CTRL1 0x007a
#define regVCN_AGDB_CTRL1_BASE_IDX 1
#define regVCN_AGDB_CTRL2 0x007b
#define regVCN_AGDB_CTRL2_BASE_IDX 1
#define regVCN_AGDB_CTRL3 0x007c
#define regVCN_AGDB_CTRL3_BASE_IDX 1
#define regVCN_RB_ENABLE 0x0085
#define regVCN_RB_ENABLE_BASE_IDX 1
#define regUVD_RB_RPTR 0x00ac
#define regUVD_RB_RPTR_BASE_IDX 1
#define regUVD_RB_WPTR 0x00ad
#define regUVD_RB_WPTR_BASE_IDX 1
#define regUVD_RB_RPTR2 0x00ae
#define regUVD_RB_RPTR2_BASE_IDX 1
#define regUVD_RB_WPTR2 0x00af
#define regUVD_RB_WPTR2_BASE_IDX 1
#define regUVD_RB_RPTR3 0x00b0
#define regUVD_RB_RPTR3_BASE_IDX 1
#define regUVD_RB_WPTR3 0x00b1
#define regUVD_RB_WPTR3_BASE_IDX 1
#define regUVD_RB_RPTR4 0x00b2
#define regUVD_RB_RPTR4_BASE_IDX 1
#define regUVD_RB_WPTR4 0x00b3
#define regUVD_RB_WPTR4_BASE_IDX 1
// addressBlock: uvd0_mmsch_dec
// base address: 0x20d00
#define regMMSCH_VF_VMID 0x054b
#define regMMSCH_VF_VMID_BASE_IDX 1
#define regMMSCH_VF_CTX_ADDR_LO 0x054c
#define regMMSCH_VF_CTX_ADDR_LO_BASE_IDX 1
#define regMMSCH_VF_CTX_ADDR_HI 0x054d
#define regMMSCH_VF_CTX_ADDR_HI_BASE_IDX 1
#define regMMSCH_VF_CTX_SIZE 0x054e
#define regMMSCH_VF_CTX_SIZE_BASE_IDX 1
#define regMMSCH_VF_MAILBOX_HOST 0x0552
#define regMMSCH_VF_MAILBOX_HOST_BASE_IDX 1
#define regMMSCH_VF_MAILBOX_RESP 0x0553
#define regMMSCH_VF_MAILBOX_RESP_BASE_IDX 1
#define regVCN_UMSCH_RB_BASE_LO 0x075b
#define regVCN_UMSCH_RB_BASE_LO_BASE_IDX 1
#define regVCN_UMSCH_RB_BASE_HI 0x075c
#define regVCN_UMSCH_RB_BASE_HI_BASE_IDX 1
#define regVCN_UMSCH_RB_SIZE 0x075d
#define regVCN_UMSCH_RB_SIZE_BASE_IDX 1
#define regVCN_UMSCH_RB_RPTR 0x075e
#define regVCN_UMSCH_RB_RPTR_BASE_IDX 1
#define regVCN_UMSCH_RB_WPTR 0x075f
#define regVCN_UMSCH_RB_WPTR_BASE_IDX 1
#define regUVD_UMSCH_FORCE 0x076b
#define regUVD_UMSCH_FORCE_BASE_IDX 1
#define regUMSCH_MES_RESET_CTRL 0x0770
#define regUMSCH_MES_RESET_CTRL_BASE_IDX 1
#define regVCN_MES_PRGRM_CNTR_START 0x0780
#define regVCN_MES_PRGRM_CNTR_START_BASE_IDX 1
#define regVCN_MES_INTR_ROUTINE_START 0x0781
#define regVCN_MES_INTR_ROUTINE_START_BASE_IDX 1
#define regVCN_MES_INTR_ROUTINE_START_HI 0x0782
#define regVCN_MES_INTR_ROUTINE_START_HI_BASE_IDX 1
#define regVCN_MES_CNTL 0x0787
#define regVCN_MES_CNTL_BASE_IDX 1
#define regVCN_MES_MSTATUS_LO 0x0796
#define regVCN_MES_MSTATUS_LO_BASE_IDX 1
#define regVCN_MES_IC_OP_CNTL 0x07a0
#define regVCN_MES_IC_OP_CNTL_BASE_IDX 1
#define regVCN_MES_GP0_LO 0x07c3
#define regVCN_MES_GP0_LO_BASE_IDX 1
#define regVCN_MES_GP0_HI 0x07c4
#define regVCN_MES_GP0_HI_BASE_IDX 1
#define regVCN_MES_GP1_LO 0x07c5
#define regVCN_MES_GP1_LO_BASE_IDX 1
#define regVCN_MES_GP1_HI 0x07c6
#define regVCN_MES_GP1_HI_BASE_IDX 1
#define regVCN_MES_LOCAL_BASE0_LO 0x0803
#define regVCN_MES_LOCAL_BASE0_LO_BASE_IDX 1
#define regVCN_MES_LOCAL_BASE0_HI 0x0804
#define regVCN_MES_LOCAL_BASE0_HI_BASE_IDX 1
#define regVCN_MES_LOCAL_MASK0_LO 0x0805
#define regVCN_MES_LOCAL_MASK0_LO_BASE_IDX 1
#define regVCN_MES_LOCAL_MASK0_HI 0x0806
#define regVCN_MES_LOCAL_MASK0_HI_BASE_IDX 1
#define regVCN_MES_LOCAL_INSTR_BASE_LO 0x0808
#define regVCN_MES_LOCAL_INSTR_BASE_LO_BASE_IDX 1
#define regVCN_MES_LOCAL_INSTR_BASE_HI 0x0809
#define regVCN_MES_LOCAL_INSTR_BASE_HI_BASE_IDX 1
#define regVCN_MES_LOCAL_INSTR_MASK_LO 0x080a
#define regVCN_MES_LOCAL_INSTR_MASK_LO_BASE_IDX 1
#define regVCN_MES_LOCAL_INSTR_MASK_HI 0x080b
#define regVCN_MES_LOCAL_INSTR_MASK_HI_BASE_IDX 1
#define regVCN_MES_PRGRM_CNTR_START_HI 0x081d
#define regVCN_MES_PRGRM_CNTR_START_HI_BASE_IDX 1
#define regVCN_MES_IC_BASE_LO 0x08d0
#define regVCN_MES_IC_BASE_LO_BASE_IDX 1
#define regVCN_MES_IC_BASE_HI 0x08d1
#define regVCN_MES_IC_BASE_HI_BASE_IDX 1
#define regVCN_MES_IC_BASE_CNTL 0x08d2
#define regVCN_MES_IC_BASE_CNTL_BASE_IDX 1
#define regVCN_MES_DC_BASE_LO 0x08d4
#define regVCN_MES_DC_BASE_LO_BASE_IDX 1
#define regVCN_MES_DC_BASE_HI 0x08d5
#define regVCN_MES_DC_BASE_HI_BASE_IDX 1
#define regVCN_MES_MIBOUND_LO 0x08db
#define regVCN_MES_MIBOUND_LO_BASE_IDX 1
#define regVCN_MES_MDBOUND_LO 0x08dd
#define regVCN_MES_MDBOUND_LO_BASE_IDX 1
// addressBlock: uvdctxind
// base address: 0x0
#define ixUVD_CGC_MEM_CTRL 0x0000
#define ixUVD_CGC_CTRL2 0x0001
#endif
