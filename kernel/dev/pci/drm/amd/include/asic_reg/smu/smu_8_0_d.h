/*
 * SMU_8_0 Register documentation
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

#ifndef SMU_8_0_D_H
#define SMU_8_0_D_H

#define ixTHM_TCON_CUR_TMP 0xd8200ca4
#define mmMP0PUB_IND_INDEX 0x180
#define mmMP0PUB_IND_DATA 0x181
#define mmMP0PUB_IND_INDEX_0 0x180
#define mmMP0PUB_IND_DATA_0 0x181
#define mmSMU_MP1_SRBM2P_MSG_0 0x1c0
#define mmSMU_MP1_SRBM2P_RESP_0 0x1d0
#define mmSMU_MP1_SRBM2P_ARG_0 0x1e0
#define ixGENERAL_PWRMGT 0xd0200000
#define ixCNB_PWRMGT_CNTL 0xd0200004
#define ixSCLK_PWRMGT_CNTL 0xd0200008
#define ixTARGET_AND_CURRENT_PROFILE_INDEX 0xd0200014
#define ixTARGET_AND_CURRENT_PROFILE_INDEX_2 0xd02000f4
#define ixCG_FREQ_TRAN_VOTING_0 0xd02001a8
#define ixSMU_VOLTAGE_STATUS 0xd0200094
#define ixCG_ULV_PARAMETER 0xd020015c
#define ixLCAC_MC0_CNTL 0xd0208130
#define ixLCAC_MC0_OVR_SEL 0xd0208134
#define ixLCAC_MC0_OVR_VAL 0xd0208138
#define ixLCAC_MC1_CNTL 0xd020813c
#define ixLCAC_MC1_OVR_SEL 0xd0208140
#define ixLCAC_MC1_OVR_VAL 0xd0208144
#define ixLCAC_MC2_OVR_SEL 0xd020814c
#define ixLCAC_MC2_OVR_VAL 0xd0208150
#define ixLCAC_MC3_OVR_SEL 0xd0208158
#define ixLCAC_MC3_OVR_VAL 0xd020815c
#define ixLCAC_CPL_CNTL 0xd0208160
#define ixLCAC_CPL_OVR_SEL 0xd0208164
#define ixLCAC_CPL_OVR_VAL 0xd0208168
#endif /* SMU_8_0_D_H */
