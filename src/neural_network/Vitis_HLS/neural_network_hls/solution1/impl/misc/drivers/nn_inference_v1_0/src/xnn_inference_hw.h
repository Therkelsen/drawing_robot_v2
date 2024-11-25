// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// AXI_CPU
// 0x000 : Control signals
//         bit 0  - ap_start (Read/Write/COH)
//         bit 1  - ap_done (Read/COR)
//         bit 2  - ap_idle (Read)
//         bit 3  - ap_ready (Read)
//         bit 7  - auto_restart (Read/Write)
//         others - reserved
// 0x004 : Global Interrupt Enable Register
//         bit 0  - Global Interrupt Enable (Read/Write)
//         others - reserved
// 0x008 : IP Interrupt Enable Register (Read/Write)
//         bit 0  - enable ap_done interrupt (Read/Write)
//         bit 1  - enable ap_ready interrupt (Read/Write)
//         others - reserved
// 0x00c : IP Interrupt Status Register (Read/TOW)
//         bit 0  - ap_done (COR/TOW)
//         bit 1  - ap_ready (COR/TOW)
//         others - reserved
// 0x010 : Data signal of out_r
//         bit 31~0 - out_r[31:0] (Read)
// 0x014 : Control signal of out_r
//         bit 0  - out_r_ap_vld (Read/COR)
//         others - reserved
// 0x200 ~
// 0x3ff : Memory 'input_img' (100 * 32b)
//         Word n : bit [31:0] - input_img[n]
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XNN_INFERENCE_AXI_CPU_ADDR_AP_CTRL        0x000
#define XNN_INFERENCE_AXI_CPU_ADDR_GIE            0x004
#define XNN_INFERENCE_AXI_CPU_ADDR_IER            0x008
#define XNN_INFERENCE_AXI_CPU_ADDR_ISR            0x00c
#define XNN_INFERENCE_AXI_CPU_ADDR_OUT_R_DATA     0x010
#define XNN_INFERENCE_AXI_CPU_BITS_OUT_R_DATA     32
#define XNN_INFERENCE_AXI_CPU_ADDR_OUT_R_CTRL     0x014
#define XNN_INFERENCE_AXI_CPU_ADDR_INPUT_IMG_BASE 0x200
#define XNN_INFERENCE_AXI_CPU_ADDR_INPUT_IMG_HIGH 0x3ff
#define XNN_INFERENCE_AXI_CPU_WIDTH_INPUT_IMG     32
#define XNN_INFERENCE_AXI_CPU_DEPTH_INPUT_IMG     100

