/*
 * BIF_5_0 Register documentation
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

#ifndef BIF_5_0_D_H
#define BIF_5_0_D_H

#define mmMM_INDEX 0x0
#define mmMM_INDEX_HI 0x6
#define mmMM_DATA 0x1
#define mmCC_BIF_BX_FUSESTRAP0 0x14D7
#define mmBIF_DOORBELL_APER_EN 0x1501
#define mmBUS_CNTL 0x1508
#define mmCONFIG_CNTL 0x1509
#define mmCONFIG_MEMSIZE 0x150a
#define mmBIF_IOV_FUNC_IDENTIFIER 0x1503
#define mmINTERRUPT_CNTL 0x151a
#define mmINTERRUPT_CNTL2 0x151b
#define mmHDP_REG_COHERENCY_FLUSH_CNTL 0x1528
#define mmHDP_MEM_COHERENCY_FLUSH_CNTL 0x1520
#define mmBIF_DOORBELL_CNTL 0x14c3
#define mmBIF_CLK_CTRL 0x14c5
#define mmBIF_FB_EN 0x1524
#define mmGPU_HDP_FLUSH_REQ 0x1537
#define mmGPU_HDP_FLUSH_DONE 0x1538
#define mmBACO_CNTL 0x14e5
#define mmREMAP_HDP_MEM_FLUSH_CNTL 0x1426
#define mmREMAP_HDP_REG_FLUSH_CNTL 0x1427
#define mmBIOS_SCRATCH_0 0x5c9
#define mmBIOS_SCRATCH_1 0x5ca
#define mmBIOS_SCRATCH_2 0x5cb
#define mmBIOS_SCRATCH_3 0x5cc
#define mmBIOS_SCRATCH_4 0x5cd
#define mmBIOS_SCRATCH_5 0x5ce
#define mmBIOS_SCRATCH_6 0x5cf
#define mmBIOS_SCRATCH_7 0x5d0
#define mmBIOS_SCRATCH_8 0x5d1
#define mmBIOS_SCRATCH_9 0x5d2
#define mmBIOS_SCRATCH_10 0x5d3
#define mmBIOS_SCRATCH_11 0x5d4
#define mmBIOS_SCRATCH_12 0x5d5
#define mmBIOS_SCRATCH_13 0x5d6
#define mmBIOS_SCRATCH_14 0x5d7
#define mmBIOS_SCRATCH_15 0x5d8
#define mmBIF_RB_CNTL 0x1530
#define mmMAILBOX_MSGBUF_TRN_DW0 0x14c8
#define mmMAILBOX_MSGBUF_TRN_DW1 0x14c9
#define mmMAILBOX_MSGBUF_TRN_DW2 0x14ca
#define mmMAILBOX_MSGBUF_TRN_DW3 0x14cb
#define mmMAILBOX_MSGBUF_RCV_DW0 0x14cc
#define mmMAILBOX_MSGBUF_RCV_DW1 0x14cd
#define mmMAILBOX_MSGBUF_RCV_DW2 0x14ce
#define mmMAILBOX_MSGBUF_RCV_DW3 0x14cf
#define mmMAILBOX_CONTROL 0x14d0
#define mmMAILBOX_INT_CNTL 0x14d1
#define mmPCIE_INDEX 0xe
#define mmPCIE_DATA 0xf
#define mmPCIE_EFUSE4 0xfc3
#define ixPCIE_HW_DEBUG 0x1400002
#define ixPCIE_RX_NUM_NAK 0x140000e
#define ixPCIE_RX_NUM_NAK_GENERATED 0x140000f
#define ixPCIE_CONFIG_CNTL 0x1400011
#define ixPCIE_CNTL2 0x140001c
#define ixPCIE_LC_STATUS1 0x1400028
#define ixPCIE_P_CNTL 0x1400040
#define ixPCIE_PERF_COUNT_CNTL 0x1400080
#define ixPCIE_PERF_CNTL_TXCLK 0x1400081
#define ixPCIE_PERF_COUNT0_TXCLK 0x1400082
#define ixPCIE_PERF_COUNT1_TXCLK 0x1400083
#define ixPCIE_LC_CNTL 0x100100a0
#define ixPCIE_LC_CNTL2 0x100100b1
#define ixPCIE_LC_CNTL3 0x100100b5
#define ixPCIE_LC_CNTL4 0x100100b6
#define ixPCIE_LC_CNTL6 0x100100bb
#define ixPCIE_LC_TRAINING_CNTL 0x100100a1
#define ixPCIE_LC_LINK_WIDTH_CNTL 0x100100a2
#define ixPCIE_LC_N_FTS_CNTL 0x100100a3
#define ixPCIE_LC_SPEED_CNTL 0x100100a4
#endif /* BIF_5_0_D_H */
