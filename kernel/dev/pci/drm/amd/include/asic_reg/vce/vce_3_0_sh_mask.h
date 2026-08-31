/*
 * VCE_3_0 Register documentation
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

#ifndef VCE_3_0_SH_MASK_H
#define VCE_3_0_SH_MASK_H

#define VCE_STATUS__JOB_BUSY_MASK 0x1
#define VCE_STATUS__JOB_BUSY__SHIFT 0x0
#define VCE_VCPU_CNTL__CLK_EN_MASK 0x1
#define VCE_VCPU_CNTL__CLK_EN__SHIFT 0x0
#define VCE_SOFT_RESET__ECPU_SOFT_RESET_MASK 0x1
#define VCE_SOFT_RESET__ECPU_SOFT_RESET__SHIFT 0x0
#define VCE_RB_ARB_CTRL__VCE_CGTT_OVERRIDE_MASK 0x10000
#define VCE_RB_ARB_CTRL__VCE_CGTT_OVERRIDE__SHIFT 0x10
#define VCE_UENC_DMA_DCLK_CTRL__WRDMCLK_FORCEON_MASK 0x1
#define VCE_UENC_DMA_DCLK_CTRL__WRDMCLK_FORCEON__SHIFT 0x0
#define VCE_UENC_DMA_DCLK_CTRL__RDDMCLK_FORCEON_MASK 0x2
#define VCE_UENC_DMA_DCLK_CTRL__RDDMCLK_FORCEON__SHIFT 0x1
#define VCE_UENC_DMA_DCLK_CTRL__REGCLK_FORCEON_MASK 0x4
#define VCE_UENC_DMA_DCLK_CTRL__REGCLK_FORCEON__SHIFT 0x2
#define VCE_SYS_INT_EN__VCE_SYS_INT_TRAP_INTERRUPT_EN_MASK 0x8
#define VCE_SYS_INT_EN__VCE_SYS_INT_TRAP_INTERRUPT_EN__SHIFT 0x3
#define VCE_SYS_INT_STATUS__VCE_SYS_INT_TRAP_INTERRUPT_INT_MASK 0x8
#define VCE_SYS_INT_STATUS__VCE_SYS_INT_TRAP_INTERRUPT_INT__SHIFT 0x3
#endif /* VCE_3_0_SH_MASK_H */
