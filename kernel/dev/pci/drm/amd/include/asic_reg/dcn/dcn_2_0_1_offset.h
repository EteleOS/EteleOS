/*
 * Copyright (C) 2021 Advanced Micro Devices, Inc.
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

#ifndef _dcn_2_0_1_OFFSET_HEADER
#define _dcn_2_0_1_OFFSET_HEADER

// addressBlock: dce_dc_dccg_dccg_dispdec
// base address: 0x0
#define mmREFCLK_CNTL 0x0049
#define mmREFCLK_CNTL_BASE_IDX 1
#define mmDPREFCLK_CNTL 0x0058
#define mmDPREFCLK_CNTL_BASE_IDX 1
#define mmDSCCLK0_DTO_PARAM 0x006c
#define mmDSCCLK0_DTO_PARAM_BASE_IDX 1
#define mmMILLISECOND_TIME_BASE_DIV 0x0070
#define mmMILLISECOND_TIME_BASE_DIV_BASE_IDX 1
#define mmDISPCLK_FREQ_CHANGE_CNTL 0x0071
#define mmDISPCLK_FREQ_CHANGE_CNTL_BASE_IDX 1
#define mmDC_MEM_GLOBAL_PWR_REQ_CNTL 0x0072
#define mmDC_MEM_GLOBAL_PWR_REQ_CNTL_BASE_IDX 1
#define mmDCCG_GATE_DISABLE_CNTL 0x0074
#define mmDCCG_GATE_DISABLE_CNTL_BASE_IDX 1
#define mmMICROSECOND_TIME_BASE_DIV 0x007b
#define mmMICROSECOND_TIME_BASE_DIV_BASE_IDX 1
#define mmDCCG_GATE_DISABLE_CNTL2 0x007c
#define mmDCCG_GATE_DISABLE_CNTL2_BASE_IDX 1
#define mmSYMCLKA_CLOCK_ENABLE 0x00a0
#define mmSYMCLKA_CLOCK_ENABLE_BASE_IDX 1
#define mmSYMCLKB_CLOCK_ENABLE 0x00a1
#define mmSYMCLKB_CLOCK_ENABLE_BASE_IDX 1
#define mmDSCCLK_DTO_CTRL 0x00a7
#define mmDSCCLK_DTO_CTRL_BASE_IDX 1
#define mmDCCG_AUDIO_DTO_SOURCE 0x00ab
#define mmDCCG_AUDIO_DTO_SOURCE_BASE_IDX 1
#define mmDCCG_AUDIO_DTO0_PHASE 0x00ac
#define mmDCCG_AUDIO_DTO0_PHASE_BASE_IDX 1
#define mmDCCG_AUDIO_DTO0_MODULE 0x00ad
#define mmDCCG_AUDIO_DTO0_MODULE_BASE_IDX 1
#define mmDCCG_AUDIO_DTO1_PHASE 0x00ae
#define mmDCCG_AUDIO_DTO1_PHASE_BASE_IDX 1
#define mmDCCG_AUDIO_DTO1_MODULE 0x00af
#define mmDCCG_AUDIO_DTO1_MODULE_BASE_IDX 1
#define mmDPPCLK_DTO_CTRL 0x00b6
#define mmDPPCLK_DTO_CTRL_BASE_IDX 1
// addressBlock: dce_dc_dccg_dccg_dfs_dispdec
// base address: 0x0
#define mmDENTIST_DISPCLK_CNTL 0x0064
#define mmDENTIST_DISPCLK_CNTL_BASE_IDX 1
// addressBlock: dce_dc_dmu_rbbmif_dispdec
// base address: 0x0
#define mmRBBMIF_TIMEOUT_DIS 0x005f
#define mmRBBMIF_TIMEOUT_DIS_BASE_IDX 2
#define mmRBBMIF_TIMEOUT_DIS_2 0x0060
#define mmRBBMIF_TIMEOUT_DIS_2_BASE_IDX 2
// addressBlock: dce_dc_hda_azf0controller_dispdec
// base address: 0x0
#define mmAZALIA_CONTROLLER_CLOCK_GATING 0x03c2
#define mmAZALIA_CONTROLLER_CLOCK_GATING_BASE_IDX 2
#define mmAZALIA_AUDIO_DTO 0x03c3
#define mmAZALIA_AUDIO_DTO_BASE_IDX 2
// addressBlock: dce_dc_hda_azf0root_dispdec
// base address: 0x0
#define mmAZALIA_F0_CODEC_FUNCTION_PARAMETER_SUPPORTED_SIZE_RATES 0x040b
#define mmAZALIA_F0_CODEC_FUNCTION_PARAMETER_SUPPORTED_SIZE_RATES_BASE_IDX 2
#define mmAZALIA_F0_CODEC_FUNCTION_PARAMETER_STREAM_FORMATS 0x040c
#define mmAZALIA_F0_CODEC_FUNCTION_PARAMETER_STREAM_FORMATS_BASE_IDX 2
#define mmAZALIA_F0_CODEC_FUNCTION_PARAMETER_POWER_STATES 0x040d
#define mmAZALIA_F0_CODEC_FUNCTION_PARAMETER_POWER_STATES_BASE_IDX 2
// addressBlock: dce_dc_dchubbub_hubbub_ret_path_dispdec
// base address: 0x0
#define mmDCHUBBUB_CRC_CTRL 0x04f1
#define mmDCHUBBUB_CRC_CTRL_BASE_IDX 2
// addressBlock: dce_dc_dchubbub_hubbub_dispdec
// base address: 0x0
#define mmDCHUBBUB_ARB_DF_REQ_OUTSTAND 0x0505
#define mmDCHUBBUB_ARB_DF_REQ_OUTSTAND_BASE_IDX 2
#define mmDCHUBBUB_ARB_SAT_LEVEL 0x0506
#define mmDCHUBBUB_ARB_SAT_LEVEL_BASE_IDX 2
#define mmDCHUBBUB_ARB_QOS_FORCE 0x0507
#define mmDCHUBBUB_ARB_QOS_FORCE_BASE_IDX 2
#define mmDCHUBBUB_ARB_DRAM_STATE_CNTL 0x0508
#define mmDCHUBBUB_ARB_DRAM_STATE_CNTL_BASE_IDX 2
#define mmDCHUBBUB_ARB_DATA_URGENCY_WATERMARK_A 0x0509
#define mmDCHUBBUB_ARB_DATA_URGENCY_WATERMARK_A_BASE_IDX 2
#define mmDCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_A 0x050a
#define mmDCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_A_BASE_IDX 2
#define mmDCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_A 0x050d
#define mmDCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_A_BASE_IDX 2
#define mmDCHUBBUB_ARB_DATA_URGENCY_WATERMARK_B 0x050e
#define mmDCHUBBUB_ARB_DATA_URGENCY_WATERMARK_B_BASE_IDX 2
#define mmDCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_B 0x050f
#define mmDCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_B_BASE_IDX 2
#define mmDCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_B 0x0512
#define mmDCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_B_BASE_IDX 2
#define mmDCHUBBUB_ARB_DATA_URGENCY_WATERMARK_C 0x0513
#define mmDCHUBBUB_ARB_DATA_URGENCY_WATERMARK_C_BASE_IDX 2
#define mmDCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_C 0x0514
#define mmDCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_C_BASE_IDX 2
#define mmDCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_C 0x0517
#define mmDCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_C_BASE_IDX 2
#define mmDCHUBBUB_ARB_DATA_URGENCY_WATERMARK_D 0x0518
#define mmDCHUBBUB_ARB_DATA_URGENCY_WATERMARK_D_BASE_IDX 2
#define mmDCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_D 0x0519
#define mmDCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_D_BASE_IDX 2
#define mmDCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_D 0x051c
#define mmDCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_D_BASE_IDX 2
#define mmDCHUBBUB_ARB_WATERMARK_CHANGE_CNTL 0x051d
#define mmDCHUBBUB_ARB_WATERMARK_CHANGE_CNTL_BASE_IDX 2
#define mmDCHUBBUB_GLOBAL_TIMER_CNTL 0x051f
#define mmDCHUBBUB_GLOBAL_TIMER_CNTL_BASE_IDX 2
#define mmDCHUBBUB_SOFT_RESET 0x052e
#define mmDCHUBBUB_SOFT_RESET_BASE_IDX 2
#define mmDCHUBBUB_CLOCK_CNTL 0x052f
#define mmDCHUBBUB_CLOCK_CNTL_BASE_IDX 2
#define mmDCFCLK_CNTL 0x0530
#define mmDCFCLK_CNTL_BASE_IDX 2
#define mmDCHUBBUB_CTRL_STATUS 0x0534
#define mmDCHUBBUB_CTRL_STATUS_BASE_IDX 2
#define mmDCHUBBUB_TIMEOUT_DETECTION_CTRL1 0x053a
#define mmDCHUBBUB_TIMEOUT_DETECTION_CTRL1_BASE_IDX 2
#define mmDCHUBBUB_TIMEOUT_DETECTION_CTRL2 0x053b
#define mmDCHUBBUB_TIMEOUT_DETECTION_CTRL2_BASE_IDX 2
#define mmDCHUBBUB_TEST_DEBUG_INDEX 0x053d
#define mmDCHUBBUB_TEST_DEBUG_INDEX_BASE_IDX 2
#define mmDCHUBBUB_TEST_DEBUG_DATA 0x053e
#define mmDCHUBBUB_TEST_DEBUG_DATA_BASE_IDX 2
// addressBlock: dce_dc_dcbubp0_dispdec_hubp_dispdec
// base address: 0x0
#define mmHUBP0_DCSURF_PRI_VIEWPORT_DIMENSION 0x05ea
#define mmHUBP0_DCSURF_PRI_VIEWPORT_DIMENSION_BASE_IDX 2
// addressBlock: dce_dc_dcbubp0_dispdec_hubpreq_dispdec
// base address: 0x0
#define mmHUBPREQ0_DCSURF_SURFACE_PITCH 0x0607
#define mmHUBPREQ0_DCSURF_SURFACE_PITCH_BASE_IDX 2
// addressBlock: dce_dc_dpp0_dispdec_dpp_top_dispdec
// base address: 0x0
#define mmDPP_TOP0_DPP_CRC_VAL_R_G 0x0cc7
#define mmDPP_TOP0_DPP_CRC_VAL_R_G_BASE_IDX 2
#define mmDPP_TOP0_DPP_CRC_VAL_B_A 0x0cc8
#define mmDPP_TOP0_DPP_CRC_VAL_B_A_BASE_IDX 2
#define mmDPP_TOP0_DPP_CRC_CTRL 0x0cc9
#define mmDPP_TOP0_DPP_CRC_CTRL_BASE_IDX 2
// addressBlock: dce_dc_mpc_mpc_cfg_dispdec
// base address: 0x0
#define mmMPC_CRC_CTRL 0x134b
#define mmMPC_CRC_CTRL_BASE_IDX 2
#define mmMPC_CRC_RESULT_AR 0x134d
#define mmMPC_CRC_RESULT_AR_BASE_IDX 2
#define mmMPC_CRC_RESULT_GB 0x134e
#define mmMPC_CRC_RESULT_GB_BASE_IDX 2
#define mmMPC_CRC_RESULT_C 0x134f
#define mmMPC_CRC_RESULT_C_BASE_IDX 2
// addressBlock: dce_dc_mpc_mpc_ocsc_dispdec
// base address: 0x0
#define mmMPC_OUT_CSC_COEF_FORMAT 0x15b6
#define mmMPC_OUT_CSC_COEF_FORMAT_BASE_IDX 2
// addressBlock: dce_dc_optc_optc_misc_dispdec
// base address: 0x0
#define mmDWB_SOURCE_SELECT 0x1e2a
#define mmDWB_SOURCE_SELECT_BASE_IDX 2
#define mmGSL_SOURCE_SELECT 0x1e2b
#define mmGSL_SOURCE_SELECT_BASE_IDX 2
// addressBlock: dce_dc_dio_dout_i2c_dispdec
// base address: 0x0
#define mmDC_I2C_CONTROL 0x1e98
#define mmDC_I2C_CONTROL_BASE_IDX 2
#define mmDC_I2C_ARBITRATION 0x1e99
#define mmDC_I2C_ARBITRATION_BASE_IDX 2
#define mmDC_I2C_SW_STATUS 0x1e9b
#define mmDC_I2C_SW_STATUS_BASE_IDX 2
#define mmDC_I2C_TRANSACTION0 0x1eae
#define mmDC_I2C_TRANSACTION0_BASE_IDX 2
#define mmDC_I2C_TRANSACTION1 0x1eaf
#define mmDC_I2C_TRANSACTION1_BASE_IDX 2
#define mmDC_I2C_TRANSACTION2 0x1eb0
#define mmDC_I2C_TRANSACTION2_BASE_IDX 2
#define mmDC_I2C_TRANSACTION3 0x1eb1
#define mmDC_I2C_TRANSACTION3_BASE_IDX 2
#define mmDC_I2C_DATA 0x1eb2
#define mmDC_I2C_DATA_BASE_IDX 2
// addressBlock: dce_dc_dio_dio_misc_dispdec
// base address: 0x0
#define mmDIO_MEM_PWR_STATUS 0x1edd
#define mmDIO_MEM_PWR_STATUS_BASE_IDX 2
#define mmDIO_MEM_PWR_CTRL 0x1ede
#define mmDIO_MEM_PWR_CTRL_BASE_IDX 2
// addressBlock: dce_dc_dio_hpd0_dispdec
// base address: 0x0
#define mmHPD0_DC_HPD_CONTROL 0x1f16
#define mmHPD0_DC_HPD_CONTROL_BASE_IDX 2
// addressBlock: dce_dc_dio_hpd1_dispdec
// base address: 0x20
#define mmHPD1_DC_HPD_CONTROL 0x1f1e
#define mmHPD1_DC_HPD_CONTROL_BASE_IDX 2
// addressBlock: dce_dc_dio_dig0_dispdec
// base address: 0x0
#define mmDIG0_HDMI_CONTROL 0x2071
#define mmDIG0_HDMI_CONTROL_BASE_IDX 2
// addressBlock: dce_dc_dio_dp0_dispdec
// base address: 0x0
#define mmDP0_DP_DPHY_FAST_TRAINING 0x2124
#define mmDP0_DP_DPHY_FAST_TRAINING_BASE_IDX 2
#define mmDP0_DP_DPHY_BS_SR_SWAP_CNTL 0x2144
#define mmDP0_DP_DPHY_BS_SR_SWAP_CNTL_BASE_IDX 2
// addressBlock: dce_dc_dio_dp1_dispdec
// base address: 0x400
#define mmDP1_DP_DPHY_FAST_TRAINING 0x2224
#define mmDP1_DP_DPHY_FAST_TRAINING_BASE_IDX 2
#define mmDP1_DP_DPHY_BS_SR_SWAP_CNTL 0x2244
#define mmDP1_DP_DPHY_BS_SR_SWAP_CNTL_BASE_IDX 2
// addressBlock: dce_dc_dcio_dcio_dispdec
// base address: 0x0
#define mmDC_PINSTRAPS 0x2880
#define mmDC_PINSTRAPS_BASE_IDX 2
#define mmDCIO_SOFT_RESET 0x289e
#define mmDCIO_SOFT_RESET_BASE_IDX 2
// addressBlock: dce_dc_dcio_dcio_chip_dispdec
// base address: 0x0
#define mmDC_GPIO_DDC1_A 0x28d1
#define mmDC_GPIO_DDC1_A_BASE_IDX 2
#define mmDC_GPIO_DDC2_A 0x28d5
#define mmDC_GPIO_DDC2_A_BASE_IDX 2
#define mmDC_GPIO_HPD_A 0x28f5
#define mmDC_GPIO_HPD_A_BASE_IDX 2
#define mmDC_GPIO_PAD_STRENGTH_1 0x28fc
#define mmDC_GPIO_PAD_STRENGTH_1_BASE_IDX 2
#endif
