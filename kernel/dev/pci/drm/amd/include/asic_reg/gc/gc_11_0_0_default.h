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
#ifndef _gc_11_0_0_DEFAULT_HEADER
#define _gc_11_0_0_DEFAULT_HEADER

// addressBlock: gc_sdma0_sdma0dec
#define regSDMA0_QUEUE0_DUMMY_REG_DEFAULT 0x0000000f
#define regSDMA0_QUEUE0_RB_AQL_CNTL_DEFAULT 0x00004000
// addressBlock: gc_gcvml2pfdec
#define regGCVM_L2_CNTL3_DEFAULT 0x80120007
#define regGCVM_L2_CNTL4_DEFAULT 0x000000c1
#define regGCVM_L2_CNTL5_DEFAULT 0x00003fe0
// addressBlock: gc_cppdec
#define regCP_GFX_HQD_VMID_DEFAULT 0x00000000
#define regCP_GFX_HQD_QUEUE_PRIORITY_DEFAULT 0x00000000
#define regCP_GFX_HQD_QUANTUM_DEFAULT 0x00000a01
#define regCP_GFX_HQD_RPTR_DEFAULT 0x00000000
#define regCP_RB_DOORBELL_CONTROL_DEFAULT 0x00000000
#define regCP_GFX_HQD_CNTL_DEFAULT 0x00a00000
#define regCP_GFX_MQD_CONTROL_DEFAULT 0x00000100
// addressBlock: gc_cpphqddec
#define regCP_HQD_PERSISTENT_STATE_DEFAULT 0x0be05501
#define regCP_HQD_QUANTUM_DEFAULT 0x00000000
#define regCP_HQD_PQ_RPTR_DEFAULT 0x00000000
#define regCP_HQD_PQ_DOORBELL_CONTROL_DEFAULT 0x00000000
#define regCP_HQD_PQ_CONTROL_DEFAULT 0x00308509
#define regCP_HQD_IB_CONTROL_DEFAULT 0x00300000
#define regCP_HQD_IQ_TIMER_DEFAULT 0x00000000
#define regCP_MQD_CONTROL_DEFAULT 0x00000100
#define regCP_HQD_EOP_CONTROL_DEFAULT 0x00000006
// addressBlock: gc_gfxudec
#define regGRBM_GFX_INDEX_DEFAULT 0xe0000000
#endif
