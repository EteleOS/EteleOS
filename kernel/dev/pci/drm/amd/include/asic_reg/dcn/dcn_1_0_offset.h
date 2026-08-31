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
#ifndef _dcn_1_0_OFFSET_HEADER
#define _dcn_1_0_OFFSET_HEADER

// addressBlock: dce_dc_mmhubbub_vga_dispdec[72..76]
// base address: 0x48
//#define mmVGA_VGA_MEM_WRITE_PAGE_ADDR                                                                  0x0000
//#define mmVGA_VGA_MEM_READ_PAGE_ADDR                                                                   0x0001
// addressBlock: dce_dc_mmhubbub_vga_dispdec
// base address: 0x0
//#define mmVGA_VGA_MEM_WRITE_PAGE_ADDR                                                                  0x0000
//#define mmVGA_VGA_MEM_READ_PAGE_ADDR                                                                   0x0001
#define mmVGA_RENDER_CONTROL 0x0000
#define mmVGA_RENDER_CONTROL_BASE_IDX 1
#define mmVGA_HDP_CONTROL 0x000a
#define mmVGA_HDP_CONTROL_BASE_IDX 1
#define mmD1VGA_CONTROL 0x000c
#define mmD1VGA_CONTROL_BASE_IDX 1
#define mmD2VGA_CONTROL 0x000e
#define mmD2VGA_CONTROL_BASE_IDX 1
#define mmVGA_TEST_CONTROL 0x0015
#define mmVGA_TEST_CONTROL_BASE_IDX 1
//#define mmVGA_CRTC8_IDX                                                                                0x002d
//#define mmVGA_CRTC8_DATA                                                                               0x002d
//#define mmVGA_GENFC_WT                                                                                 0x002e
//#define mmVGA_GENS1                                                                                    0x002e
//#define mmVGA_ATTRDW                                                                                   0x0030
//#define mmVGA_ATTRX                                                                                    0x0030
//#define mmVGA_ATTRDR                                                                                   0x0030
//#define mmVGA_GENMO_WT                                                                                 0x0030
//#define mmVGA_GENS0                                                                                    0x0030
//#define mmVGA_GENENB                                                                                   0x0030
//#define mmVGA_SEQ8_IDX                                                                                 0x0031
//#define mmVGA_SEQ8_DATA                                                                                0x0031
//#define mmVGA_DAC_MASK                                                                                 0x0031
//#define mmVGA_DAC_R_INDEX                                                                              0x0031
//#define mmVGA_DAC_W_INDEX                                                                              0x0032
//#define mmVGA_DAC_DATA                                                                                 0x0032
//#define mmVGA_GENFC_RD                                                                                 0x0032
//#define mmVGA_GENMO_RD                                                                                 0x0033
//#define mmVGA_GRPH8_IDX                                                                                0x0033
//#define mmVGA_GRPH8_DATA                                                                               0x0033
//#define mmVGA_CRTC8_IDX_1                                                                              0x0035
//#define mmVGA_CRTC8_DATA_1                                                                             0x0035
//#define mmVGA_GENFC_WT_1                                                                               0x0036
//#define mmVGA_GENS1_1                                                                                  0x0036
#define mmD3VGA_CONTROL 0x0038
#define mmD3VGA_CONTROL_BASE_IDX 1
#define mmD4VGA_CONTROL 0x0039
#define mmD4VGA_CONTROL_BASE_IDX 1
#define mmD5VGA_CONTROL 0x003a
#define mmD5VGA_CONTROL_BASE_IDX 1
#define mmD6VGA_CONTROL 0x003b
#define mmD6VGA_CONTROL_BASE_IDX 1
// addressBlock: dce_dc_dccg_dccg_dispdec
// base address: 0x0
#define mmREFCLK_CNTL 0x0049
#define mmREFCLK_CNTL_BASE_IDX 1
#define mmDPREFCLK_CNTL 0x0058
#define mmDPREFCLK_CNTL_BASE_IDX 1
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
#define mmSYMCLKC_CLOCK_ENABLE 0x00a2
#define mmSYMCLKC_CLOCK_ENABLE_BASE_IDX 1
#define mmSYMCLKD_CLOCK_ENABLE 0x00a3
#define mmSYMCLKD_CLOCK_ENABLE_BASE_IDX 1
#define mmSYMCLKE_CLOCK_ENABLE 0x00a4
#define mmSYMCLKE_CLOCK_ENABLE_BASE_IDX 1
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
// addressBlock: dce_dc_dccg_dccg_dfs_dispdec
// base address: 0x0
#define mmDENTIST_DISPCLK_CNTL 0x0064
#define mmDENTIST_DISPCLK_CNTL_BASE_IDX 1
// addressBlock: dce_dc_dmu_rbbmif_dispdec
// base address: 0x0
#define mmRBBMIF_TIMEOUT_DIS 0x0058
#define mmRBBMIF_TIMEOUT_DIS_BASE_IDX 2
// addressBlock: dce_dc_dmu_dc_pg_dispdec
// base address: 0x0
#define mmDOMAIN0_PG_CONFIG 0x008a
#define mmDOMAIN0_PG_CONFIG_BASE_IDX 2
#define mmDOMAIN0_PG_STATUS 0x008b
#define mmDOMAIN0_PG_STATUS_BASE_IDX 2
#define mmDOMAIN1_PG_CONFIG 0x008c
#define mmDOMAIN1_PG_CONFIG_BASE_IDX 2
#define mmDOMAIN1_PG_STATUS 0x008d
#define mmDOMAIN1_PG_STATUS_BASE_IDX 2
#define mmDOMAIN2_PG_CONFIG 0x008e
#define mmDOMAIN2_PG_CONFIG_BASE_IDX 2
#define mmDOMAIN2_PG_STATUS 0x008f
#define mmDOMAIN2_PG_STATUS_BASE_IDX 2
#define mmDOMAIN3_PG_CONFIG 0x0090
#define mmDOMAIN3_PG_CONFIG_BASE_IDX 2
#define mmDOMAIN3_PG_STATUS 0x0091
#define mmDOMAIN3_PG_STATUS_BASE_IDX 2
#define mmDOMAIN4_PG_CONFIG 0x0092
#define mmDOMAIN4_PG_CONFIG_BASE_IDX 2
#define mmDOMAIN4_PG_STATUS 0x0093
#define mmDOMAIN4_PG_STATUS_BASE_IDX 2
#define mmDOMAIN5_PG_CONFIG 0x0094
#define mmDOMAIN5_PG_CONFIG_BASE_IDX 2
#define mmDOMAIN5_PG_STATUS 0x0095
#define mmDOMAIN5_PG_STATUS_BASE_IDX 2
#define mmDOMAIN6_PG_CONFIG 0x0096
#define mmDOMAIN6_PG_CONFIG_BASE_IDX 2
#define mmDOMAIN6_PG_STATUS 0x0097
#define mmDOMAIN6_PG_STATUS_BASE_IDX 2
#define mmDOMAIN7_PG_CONFIG 0x0098
#define mmDOMAIN7_PG_CONFIG_BASE_IDX 2
#define mmDOMAIN7_PG_STATUS 0x0099
#define mmDOMAIN7_PG_STATUS_BASE_IDX 2
#define mmDOMAIN8_PG_CONFIG 0x009a
#define mmDOMAIN8_PG_CONFIG_BASE_IDX 2
#define mmDOMAIN8_PG_STATUS 0x009b
#define mmDOMAIN8_PG_STATUS_BASE_IDX 2
#define mmDOMAIN9_PG_CONFIG 0x009c
#define mmDOMAIN9_PG_CONFIG_BASE_IDX 2
#define mmDOMAIN9_PG_STATUS 0x009d
#define mmDOMAIN9_PG_STATUS_BASE_IDX 2
#define mmDOMAIN10_PG_STATUS 0x009f
#define mmDOMAIN10_PG_STATUS_BASE_IDX 2
#define mmDOMAIN11_PG_STATUS 0x00a1
#define mmDOMAIN11_PG_STATUS_BASE_IDX 2
#define mmDC_IP_REQUEST_CNTL 0x00ad
#define mmDC_IP_REQUEST_CNTL_BASE_IDX 2
// addressBlock: dce_dc_dmu_dmu_misc_dispdec
// base address: 0x0
#define mmCC_DC_PIPE_DIS 0x00ca
#define mmCC_DC_PIPE_DIS_BASE_IDX 2
#define mmDMU_CLK_CNTL 0x00cb
#define mmDMU_CLK_CNTL_BASE_IDX 2
#define mmDMU_MEM_PWR_CNTL 0x00cc
#define mmDMU_MEM_PWR_CNTL_BASE_IDX 2
#define mmSMU_INTERRUPT_CONTROL 0x00ce
#define mmSMU_INTERRUPT_CONTROL_BASE_IDX 2
// addressBlock: dce_dc_dmu_dmcu_dispdec
// base address: 0x0
#define mmDMCU_CTRL 0x00da
#define mmDMCU_CTRL_BASE_IDX 2
#define mmDMCU_STATUS 0x00db
#define mmDMCU_STATUS_BASE_IDX 2
#define mmDMCU_RAM_ACCESS_CTRL 0x00e2
#define mmDMCU_RAM_ACCESS_CTRL_BASE_IDX 2
#define mmDMCU_IRAM_WR_CTRL 0x00e7
#define mmDMCU_IRAM_WR_CTRL_BASE_IDX 2
#define mmDMCU_IRAM_WR_DATA 0x00e8
#define mmDMCU_IRAM_WR_DATA_BASE_IDX 2
#define mmDMCU_IRAM_RD_CTRL 0x00e9
#define mmDMCU_IRAM_RD_CTRL_BASE_IDX 2
#define mmDMCU_IRAM_RD_DATA 0x00ea
#define mmDMCU_IRAM_RD_DATA_BASE_IDX 2
#define mmDMCU_INTERRUPT_TO_UC_EN_MASK 0x00f1
#define mmDMCU_INTERRUPT_TO_UC_EN_MASK_BASE_IDX 2
#define mmDC_DMCU_SCRATCH 0x00f5
#define mmDC_DMCU_SCRATCH_BASE_IDX 2
#define mmMASTER_COMM_DATA_REG1 0x00f9
#define mmMASTER_COMM_DATA_REG1_BASE_IDX 2
#define mmMASTER_COMM_DATA_REG2 0x00fa
#define mmMASTER_COMM_DATA_REG2_BASE_IDX 2
#define mmMASTER_COMM_DATA_REG3 0x00fb
#define mmMASTER_COMM_DATA_REG3_BASE_IDX 2
#define mmMASTER_COMM_CMD_REG 0x00fc
#define mmMASTER_COMM_CMD_REG_BASE_IDX 2
#define mmMASTER_COMM_CNTL_REG 0x00fd
#define mmMASTER_COMM_CNTL_REG_BASE_IDX 2
#define mmSLAVE_COMM_DATA_REG1 0x00fe
#define mmSLAVE_COMM_DATA_REG1_BASE_IDX 2
#define mmSLAVE_COMM_DATA_REG2 0x00ff
#define mmSLAVE_COMM_DATA_REG2_BASE_IDX 2
#define mmSLAVE_COMM_DATA_REG3 0x0100
#define mmSLAVE_COMM_DATA_REG3_BASE_IDX 2
#define mmSLAVE_COMM_CMD_REG 0x0101
#define mmSLAVE_COMM_CMD_REG_BASE_IDX 2
// addressBlock: dce_dc_dmu_ihc_dispdec
// base address: 0x0
#define mmDISP_INTERRUPT_STATUS 0x012a
#define mmDISP_INTERRUPT_STATUS_BASE_IDX 2
#define mmDISP_INTERRUPT_STATUS_CONTINUE 0x012b
#define mmDISP_INTERRUPT_STATUS_CONTINUE_BASE_IDX 2
#define mmDISP_INTERRUPT_STATUS_CONTINUE2 0x012c
#define mmDISP_INTERRUPT_STATUS_CONTINUE2_BASE_IDX 2
#define mmDISP_INTERRUPT_STATUS_CONTINUE3 0x012d
#define mmDISP_INTERRUPT_STATUS_CONTINUE3_BASE_IDX 2
#define mmDISP_INTERRUPT_STATUS_CONTINUE4 0x012e
#define mmDISP_INTERRUPT_STATUS_CONTINUE4_BASE_IDX 2
#define mmDISP_INTERRUPT_STATUS_CONTINUE5 0x012f
#define mmDISP_INTERRUPT_STATUS_CONTINUE5_BASE_IDX 2
// addressBlock: dce_dc_mmhubbub_mmhubbub_dispdec
// base address: 0x0
#define mmMMHUBBUB_MEM_PWR_CNTL 0x033d
#define mmMMHUBBUB_MEM_PWR_CNTL_BASE_IDX 2
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
// addressBlock: dce_dc_dchubbub_hubbub_sdpif_dispdec
// base address: 0x0
#define mmDCHUBBUB_SDPIF_CFG0 0x048f
#define mmDCHUBBUB_SDPIF_CFG0_BASE_IDX 2
#define mmDCHUBBUB_SDPIF_CFG1 0x0490
#define mmDCHUBBUB_SDPIF_CFG1_BASE_IDX 2
#define mmDCHUBBUB_SDPIF_FB_BASE 0x0493
#define mmDCHUBBUB_SDPIF_FB_BASE_BASE_IDX 2
#define mmDCHUBBUB_SDPIF_FB_TOP 0x0494
#define mmDCHUBBUB_SDPIF_FB_TOP_BASE_IDX 2
#define mmDCHUBBUB_SDPIF_FB_OFFSET 0x0495
#define mmDCHUBBUB_SDPIF_FB_OFFSET_BASE_IDX 2
#define mmDCHUBBUB_SDPIF_AGP_BOT 0x0496
#define mmDCHUBBUB_SDPIF_AGP_BOT_BASE_IDX 2
#define mmDCHUBBUB_SDPIF_AGP_TOP 0x0497
#define mmDCHUBBUB_SDPIF_AGP_TOP_BASE_IDX 2
#define mmDCHUBBUB_SDPIF_AGP_BASE 0x0498
#define mmDCHUBBUB_SDPIF_AGP_BASE_BASE_IDX 2
#define mmDCHUBBUB_SDPIF_MMIO_CNTRL_0 0x049d
#define mmDCHUBBUB_SDPIF_MMIO_CNTRL_0_BASE_IDX 2
// addressBlock: dce_dc_dchubbub_hubbub_ret_path_dispdec
// base address: 0x0
#define mmDCHUBBUB_CRC_CTRL 0x04e2
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
#define mmDCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_A 0x050b
#define mmDCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_A_BASE_IDX 2
#define mmDCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_A 0x050c
#define mmDCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_A_BASE_IDX 2
#define mmDCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_A 0x050d
#define mmDCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_A_BASE_IDX 2
#define mmDCHUBBUB_ARB_DATA_URGENCY_WATERMARK_B 0x050e
#define mmDCHUBBUB_ARB_DATA_URGENCY_WATERMARK_B_BASE_IDX 2
#define mmDCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_B 0x050f
#define mmDCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_B_BASE_IDX 2
#define mmDCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_B 0x0510
#define mmDCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_B_BASE_IDX 2
#define mmDCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_B 0x0511
#define mmDCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_B_BASE_IDX 2
#define mmDCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_B 0x0512
#define mmDCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_B_BASE_IDX 2
#define mmDCHUBBUB_ARB_DATA_URGENCY_WATERMARK_C 0x0513
#define mmDCHUBBUB_ARB_DATA_URGENCY_WATERMARK_C_BASE_IDX 2
#define mmDCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_C 0x0514
#define mmDCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_C_BASE_IDX 2
#define mmDCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_C 0x0515
#define mmDCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_C_BASE_IDX 2
#define mmDCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_C 0x0516
#define mmDCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_C_BASE_IDX 2
#define mmDCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_C 0x0517
#define mmDCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_C_BASE_IDX 2
#define mmDCHUBBUB_ARB_DATA_URGENCY_WATERMARK_D 0x0518
#define mmDCHUBBUB_ARB_DATA_URGENCY_WATERMARK_D_BASE_IDX 2
#define mmDCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_D 0x0519
#define mmDCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_D_BASE_IDX 2
#define mmDCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_D 0x051a
#define mmDCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_D_BASE_IDX 2
#define mmDCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_D 0x051b
#define mmDCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_D_BASE_IDX 2
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
#define mmDCHUBBUB_TEST_DEBUG_INDEX 0x053a
#define mmDCHUBBUB_TEST_DEBUG_INDEX_BASE_IDX 2
#define mmDCHUBBUB_TEST_DEBUG_DATA 0x053b
#define mmDCHUBBUB_TEST_DEBUG_DATA_BASE_IDX 2
// addressBlock: dce_dc_dcbubp0_dispdec_hubp_dispdec
// base address: 0x0
#define mmHUBP0_DCSURF_PRI_VIEWPORT_DIMENSION 0x055d
#define mmHUBP0_DCSURF_PRI_VIEWPORT_DIMENSION_BASE_IDX 2
// addressBlock: dce_dc_dcbubp0_dispdec_hubpreq_dispdec
// base address: 0x0
#define mmHUBPREQ0_DCSURF_SURFACE_PITCH 0x057b
#define mmHUBPREQ0_DCSURF_SURFACE_PITCH_BASE_IDX 2
// addressBlock: dce_dc_dpp0_dispdec_dpp_top_dispdec
// base address: 0x0
#define mmDPP_TOP0_DPP_CRC_VAL_R_G 0x0c3f
#define mmDPP_TOP0_DPP_CRC_VAL_R_G_BASE_IDX 2
#define mmDPP_TOP0_DPP_CRC_VAL_B_A 0x0c40
#define mmDPP_TOP0_DPP_CRC_VAL_B_A_BASE_IDX 2
#define mmDPP_TOP0_DPP_CRC_CTRL 0x0c41
#define mmDPP_TOP0_DPP_CRC_CTRL_BASE_IDX 2
// addressBlock: dce_dc_mpc_mpc_cfg_dispdec
// base address: 0x0
#define mmMPC_CRC_CTRL 0x1725
#define mmMPC_CRC_CTRL_BASE_IDX 2
#define mmMPC_CRC_RESULT_AR 0x1727
#define mmMPC_CRC_RESULT_AR_BASE_IDX 2
#define mmMPC_CRC_RESULT_GB 0x1728
#define mmMPC_CRC_RESULT_GB_BASE_IDX 2
#define mmMPC_CRC_RESULT_C 0x1729
#define mmMPC_CRC_RESULT_C_BASE_IDX 2
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
#define mmDC_I2C_DDCVGA_SETUP 0x1eb5
#define mmDC_I2C_DDCVGA_SETUP_BASE_IDX 2
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
// addressBlock: dce_dc_dio_hpd2_dispdec
// base address: 0x40
#define mmHPD2_DC_HPD_CONTROL 0x1f26
#define mmHPD2_DC_HPD_CONTROL_BASE_IDX 2
// addressBlock: dce_dc_dio_hpd3_dispdec
// base address: 0x60
#define mmHPD3_DC_HPD_CONTROL 0x1f2e
#define mmHPD3_DC_HPD_CONTROL_BASE_IDX 2
// addressBlock: dce_dc_dio_hpd4_dispdec
// base address: 0x80
#define mmHPD4_DC_HPD_CONTROL 0x1f36
#define mmHPD4_DC_HPD_CONTROL_BASE_IDX 2
// addressBlock: dce_dc_dio_hpd5_dispdec
// base address: 0xa0
#define mmHPD5_DC_HPD_CONTROL 0x1f3e
#define mmHPD5_DC_HPD_CONTROL_BASE_IDX 2
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
// addressBlock: dce_dc_dio_dp2_dispdec
// base address: 0x800
#define mmDP2_DP_DPHY_FAST_TRAINING 0x2324
#define mmDP2_DP_DPHY_FAST_TRAINING_BASE_IDX 2
#define mmDP2_DP_DPHY_BS_SR_SWAP_CNTL 0x2344
#define mmDP2_DP_DPHY_BS_SR_SWAP_CNTL_BASE_IDX 2
// addressBlock: dce_dc_dio_dp3_dispdec
// base address: 0xc00
#define mmDP3_DP_DPHY_FAST_TRAINING 0x2424
#define mmDP3_DP_DPHY_FAST_TRAINING_BASE_IDX 2
#define mmDP3_DP_DPHY_BS_SR_SWAP_CNTL 0x2444
#define mmDP3_DP_DPHY_BS_SR_SWAP_CNTL_BASE_IDX 2
// addressBlock: dce_dc_dio_dp4_dispdec
// base address: 0x1000
#define mmDP4_DP_DPHY_FAST_TRAINING 0x2524
#define mmDP4_DP_DPHY_FAST_TRAINING_BASE_IDX 2
#define mmDP4_DP_DPHY_BS_SR_SWAP_CNTL 0x2544
#define mmDP4_DP_DPHY_BS_SR_SWAP_CNTL_BASE_IDX 2
// addressBlock: dce_dc_dio_dp5_dispdec
// base address: 0x1400
#define mmDP5_DP_DPHY_FAST_TRAINING 0x2624
#define mmDP5_DP_DPHY_FAST_TRAINING_BASE_IDX 2
#define mmDP5_DP_DPHY_BS_SR_SWAP_CNTL 0x2644
#define mmDP5_DP_DPHY_BS_SR_SWAP_CNTL_BASE_IDX 2
// addressBlock: dce_dc_dio_dp6_dispdec
// base address: 0x1800
#define mmDP6_DP_DPHY_FAST_TRAINING 0x2724
#define mmDP6_DP_DPHY_FAST_TRAINING_BASE_IDX 2
#define mmDP6_DP_DPHY_BS_SR_SWAP_CNTL 0x2744
#define mmDP6_DP_DPHY_BS_SR_SWAP_CNTL_BASE_IDX 2
// addressBlock: dce_dc_dcio_dcio_dispdec
// base address: 0x0
#define mmDC_GPIO_DEBUG 0x286c
#define mmDC_GPIO_DEBUG_BASE_IDX 2
#define mmDC_PINSTRAPS 0x2880
#define mmDC_PINSTRAPS_BASE_IDX 2
#define mmBL_PWM_CNTL 0x2888
#define mmBL_PWM_CNTL_BASE_IDX 2
#define mmBL_PWM_CNTL2 0x2889
#define mmBL_PWM_CNTL2_BASE_IDX 2
#define mmBL_PWM_PERIOD_CNTL 0x288a
#define mmBL_PWM_PERIOD_CNTL_BASE_IDX 2
#define mmBL_PWM_GRP1_REG_LOCK 0x288b
#define mmBL_PWM_GRP1_REG_LOCK_BASE_IDX 2
#define mmDCIO_SOFT_RESET 0x289e
#define mmDCIO_SOFT_RESET_BASE_IDX 2
#define mmAUXP_IMPCAL 0x28a3
#define mmAUXP_IMPCAL_BASE_IDX 2
#define mmAUXN_IMPCAL 0x28a4
#define mmAUXN_IMPCAL_BASE_IDX 2
// addressBlock: dce_dc_dcio_dcio_chip_dispdec
// base address: 0x0
#define mmDC_GPIO_GENERIC_MASK 0x28c8
#define mmDC_GPIO_GENERIC_MASK_BASE_IDX 2
#define mmDC_GPIO_GENERIC_A 0x28c9
#define mmDC_GPIO_GENERIC_A_BASE_IDX 2
#define mmDC_GPIO_GENERIC_EN 0x28ca
#define mmDC_GPIO_GENERIC_EN_BASE_IDX 2
#define mmDC_GPIO_DVODATA_MASK 0x28cc
#define mmDC_GPIO_DVODATA_MASK_BASE_IDX 2
#define mmDC_GPIO_DVODATA_EN 0x28ce
#define mmDC_GPIO_DVODATA_EN_BASE_IDX 2
#define mmDC_GPIO_DDC1_A 0x28d1
#define mmDC_GPIO_DDC1_A_BASE_IDX 2
#define mmDC_GPIO_DDC2_A 0x28d5
#define mmDC_GPIO_DDC2_A_BASE_IDX 2
#define mmDC_GPIO_DDC3_A 0x28d9
#define mmDC_GPIO_DDC3_A_BASE_IDX 2
#define mmDC_GPIO_DDC4_A 0x28dd
#define mmDC_GPIO_DDC4_A_BASE_IDX 2
#define mmDC_GPIO_DDC5_A 0x28e1
#define mmDC_GPIO_DDC5_A_BASE_IDX 2
#define mmDC_GPIO_DDC6_A 0x28e5
#define mmDC_GPIO_DDC6_A_BASE_IDX 2
#define mmDC_GPIO_DDCVGA_A 0x28e9
#define mmDC_GPIO_DDCVGA_A_BASE_IDX 2
#define mmDC_GPIO_SYNCA_MASK 0x28ec
#define mmDC_GPIO_SYNCA_MASK_BASE_IDX 2
#define mmDC_GPIO_SYNCA_A 0x28ed
#define mmDC_GPIO_SYNCA_A_BASE_IDX 2
#define mmDC_GPIO_SYNCA_EN 0x28ee
#define mmDC_GPIO_SYNCA_EN_BASE_IDX 2
#define mmDC_GPIO_GENLK_A 0x28f1
#define mmDC_GPIO_GENLK_A_BASE_IDX 2
#define mmDC_GPIO_HPD_A 0x28f5
#define mmDC_GPIO_HPD_A_BASE_IDX 2
#define mmDC_GPIO_PWRSEQ_A 0x28f9
#define mmDC_GPIO_PWRSEQ_A_BASE_IDX 2
#define mmDC_GPIO_PAD_STRENGTH_1 0x28fc
#define mmDC_GPIO_PAD_STRENGTH_1_BASE_IDX 2
#define mmDC_GPIO_PAD_STRENGTH_2 0x28fd
#define mmDC_GPIO_PAD_STRENGTH_2_BASE_IDX 2
#define mmDC_GPIO_I2CPAD_A 0x2901
#define mmDC_GPIO_I2CPAD_A_BASE_IDX 2
#endif
