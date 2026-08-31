/*
 * OSS_3_0_1 Register documentation
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

#ifndef OSS_3_0_1_D_H
#define OSS_3_0_1_D_H

#define mmIH_VMID_0_LUT 0xe00
#define mmIH_RB_CNTL 0xe30
#define mmIH_RB_BASE 0xe31
#define mmIH_RB_RPTR 0xe32
#define mmIH_RB_WPTR 0xe33
#define mmIH_RB_WPTR_ADDR_HI 0xe34
#define mmIH_RB_WPTR_ADDR_LO 0xe35
#define mmIH_CNTL 0xe36
#define mmSRBM_GFX_CNTL 0x391
#define mmSRBM_STATUS2 0x393
#define mmSRBM_STATUS 0x394
#define mmSRBM_STATUS3 0x395
#define mmSRBM_SOFT_RESET 0x398
#define mmSRBM_INT_CNTL 0x3a8
#define mmSRBM_INT_ACK 0x3aa
#define mmSDMA0_UCODE_ADDR 0x3400
#define mmSDMA0_UCODE_DATA 0x3401
#define mmSDMA0_POWER_CNTL 0x3402
#define mmSDMA0_CLK_CTRL 0x3403
#define mmSDMA0_CNTL 0x3404
#define mmSDMA0_CHICKEN_BITS 0x3405
#define mmSDMA0_TILING_CONFIG 0x3406
#define mmSDMA0_SEM_WAIT_FAIL_TIMER_CNTL 0x3409
#define mmSDMA0_RB_RPTR_FETCH 0x340a
#define mmSDMA0_STATUS_REG 0x340d
#define mmSDMA0_STATUS1_REG 0x340e
#define mmSDMA0_RD_BURST_CNTL 0x340f
#define mmSDMA0_F32_CNTL 0x3412
#define mmSDMA0_FREEZE 0x3413
#define mmSDMA0_PHASE0_QUANTUM 0x3414
#define mmSDMA0_PHASE1_QUANTUM 0x3415
#define mmSDMA0_EDC_CONFIG 0x341a
#define mmSDMA0_VM_CNTL 0x3420
#define mmSDMA0_STATUS2_REG 0x3423
#define mmSDMA0_GFX_RB_CNTL 0x3480
#define mmSDMA0_GFX_RB_BASE 0x3481
#define mmSDMA0_GFX_RB_BASE_HI 0x3482
#define mmSDMA0_GFX_RB_RPTR 0x3483
#define mmSDMA0_GFX_RB_WPTR 0x3484
#define mmSDMA0_GFX_RB_WPTR_POLL_CNTL 0x3485
#define mmSDMA0_GFX_RB_WPTR_POLL_ADDR_HI 0x3486
#define mmSDMA0_GFX_RB_WPTR_POLL_ADDR_LO 0x3487
#define mmSDMA0_GFX_RB_RPTR_ADDR_HI 0x3488
#define mmSDMA0_GFX_RB_RPTR_ADDR_LO 0x3489
#define mmSDMA0_GFX_IB_CNTL 0x348a
#define mmSDMA0_GFX_IB_RPTR 0x348b
#define mmSDMA0_GFX_IB_OFFSET 0x348c
#define mmSDMA0_GFX_IB_BASE_LO 0x348d
#define mmSDMA0_GFX_IB_BASE_HI 0x348e
#define mmSDMA0_GFX_DOORBELL 0x3492
#define mmSDMA0_GFX_VIRTUAL_ADDR 0x34a7
#define mmSDMA0_GFX_APE1_CNTL 0x34a8
#define mmSDMA0_GFX_IB_SUB_REMAIN 0x34af
#define mmSDMA0_GFX_PREEMPT 0x34b0
#define mmSDMA0_GFX_DUMMY_REG 0x34b1
#define mmSDMA0_RLC0_RB_CNTL 0x3500
#define mmSDMA0_RLC0_RB_BASE 0x3501
#define mmSDMA0_RLC0_RB_BASE_HI 0x3502
#define mmSDMA0_RLC0_RB_RPTR 0x3503
#define mmSDMA0_RLC0_RB_WPTR 0x3504
#define mmSDMA0_RLC0_RB_WPTR_POLL_CNTL 0x3505
#define mmSDMA0_RLC0_RB_RPTR_ADDR_HI 0x3508
#define mmSDMA0_RLC0_RB_RPTR_ADDR_LO 0x3509
#define mmSDMA0_RLC0_IB_CNTL 0x350a
#define mmSDMA0_RLC0_IB_OFFSET 0x350c
#define mmSDMA0_RLC0_IB_BASE_LO 0x350d
#define mmSDMA0_RLC0_IB_BASE_HI 0x350e
#define mmSDMA0_RLC0_CONTEXT_STATUS 0x3511
#define mmSDMA0_RLC0_DOORBELL 0x3512
#define mmSDMA0_RLC0_VIRTUAL_ADDR 0x3527
#define mmSDMA0_RLC0_WATERMARK 0x352a
#define mmSDMA0_RLC0_CSA_ADDR_LO 0x352c
#define mmSDMA0_RLC0_CSA_ADDR_HI 0x352d
#define mmSDMA0_RLC0_IB_SUB_REMAIN 0x352f
#define mmSDMA0_RLC0_DUMMY_REG 0x3531
#define mmSDMA0_RLC0_MIDCMD_DATA0 0x3541
#define mmSDMA0_RLC0_MIDCMD_CNTL 0x354a
#define mmSDMA0_RLC1_RB_CNTL 0x3580
#define mmSDMA0_RLC1_RB_WPTR_POLL_CNTL 0x3585
#define mmSDMA0_RLC1_RB_RPTR_ADDR_LO 0x3589
#define mmSDMA0_RLC1_IB_CNTL 0x358a
#define mmSDMA1_POWER_CNTL 0x3602
#define mmSDMA1_CLK_CTRL 0x3603
#define mmSDMA1_CHICKEN_BITS 0x3605
#define mmSDMA1_STATUS_REG 0x360d
#define mmSDMA1_RD_BURST_CNTL 0x360f
#define mmSDMA1_GFX_RB_WPTR_POLL_CNTL 0x3685
#define mmSDMA1_GFX_RB_RPTR_ADDR_LO 0x3689
#define mmSDMA1_GFX_IB_CNTL 0x368a
#define mmSDMA1_GFX_PREEMPT 0x36b0
#define mmSDMA1_RLC0_RB_CNTL 0x3700
#define mmSDMA1_RLC0_RB_WPTR_POLL_CNTL 0x3705
#define mmSDMA1_RLC0_RB_RPTR_ADDR_LO 0x3709
#define mmSDMA1_RLC0_IB_CNTL 0x370a
#define mmSDMA1_RLC1_RB_WPTR_POLL_CNTL 0x3785
#define mmSDMA1_RLC1_RB_RPTR_ADDR_LO 0x3789
#define mmSDMA1_RLC1_IB_CNTL 0x378a
#define mmHDP_HOST_PATH_CNTL 0xb00
#define mmHDP_NONSURFACE_BASE 0xb01
#define mmHDP_NONSURFACE_INFO 0xb02
#define mmHDP_NONSURFACE_SIZE 0xb03
#define mmHDP_DEBUG0 0xbcc
#define mmHDP_ADDR_CONFIG 0xbd2
#define mmHDP_MISC_CNTL 0xbd3
#define mmHDP_MEM_POWER_LS 0xbd4
#define mmHDP_XDP_CGTT_BLK_CTRL 0xc33
#endif /* OSS_3_0_1_D_H */
