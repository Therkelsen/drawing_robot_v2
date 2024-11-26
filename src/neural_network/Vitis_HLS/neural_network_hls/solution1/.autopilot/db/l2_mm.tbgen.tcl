set moduleName l2_mm
set isTopModule 0
set isCombinational 0
set isDatapathOnly 0
set isPipelined 0
set pipeline_type none
set FunctionProtocol ap_ctrl_hs
set isOneStateSeq 0
set ProfileFlag 0
set StallSigGenFlag 0
set isEnableWaveformDebug 1
set C_modelName {l2_mm}
set C_modelType { void 0 }
set C_modelArgList {
	{ input_0 float 32 regular {array 32 { 1 1 } 1 1 }  }
	{ output_0 float 32 regular {array 16 { 0 0 } 0 1 }  }
}
set C_modelArgMapList {[ 
	{ "Name" : "input_0", "interface" : "memory", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "output_0", "interface" : "memory", "bitwidth" : 32, "direction" : "WRITEONLY"} ]}
# RTL Port declarations: 
set portNum 164
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ input_0_address0 sc_out sc_lv 5 signal 0 } 
	{ input_0_ce0 sc_out sc_logic 1 signal 0 } 
	{ input_0_q0 sc_in sc_lv 32 signal 0 } 
	{ input_0_address1 sc_out sc_lv 5 signal 0 } 
	{ input_0_ce1 sc_out sc_logic 1 signal 0 } 
	{ input_0_q1 sc_in sc_lv 32 signal 0 } 
	{ output_0_address0 sc_out sc_lv 4 signal 1 } 
	{ output_0_ce0 sc_out sc_logic 1 signal 1 } 
	{ output_0_we0 sc_out sc_logic 1 signal 1 } 
	{ output_0_d0 sc_out sc_lv 32 signal 1 } 
	{ output_0_address1 sc_out sc_lv 4 signal 1 } 
	{ output_0_ce1 sc_out sc_logic 1 signal 1 } 
	{ output_0_we1 sc_out sc_logic 1 signal 1 } 
	{ output_0_d1 sc_out sc_lv 32 signal 1 } 
	{ grp_fu_2574_p_din0 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2574_p_din1 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2574_p_opcode sc_out sc_lv 2 signal -1 } 
	{ grp_fu_2574_p_dout0 sc_in sc_lv 32 signal -1 } 
	{ grp_fu_2574_p_ce sc_out sc_logic 1 signal -1 } 
	{ grp_fu_2578_p_din0 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2578_p_din1 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2578_p_opcode sc_out sc_lv 2 signal -1 } 
	{ grp_fu_2578_p_dout0 sc_in sc_lv 32 signal -1 } 
	{ grp_fu_2578_p_ce sc_out sc_logic 1 signal -1 } 
	{ grp_fu_2582_p_din0 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2582_p_din1 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2582_p_opcode sc_out sc_lv 2 signal -1 } 
	{ grp_fu_2582_p_dout0 sc_in sc_lv 32 signal -1 } 
	{ grp_fu_2582_p_ce sc_out sc_logic 1 signal -1 } 
	{ grp_fu_2586_p_din0 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2586_p_din1 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2586_p_opcode sc_out sc_lv 2 signal -1 } 
	{ grp_fu_2586_p_dout0 sc_in sc_lv 32 signal -1 } 
	{ grp_fu_2586_p_ce sc_out sc_logic 1 signal -1 } 
	{ grp_fu_2590_p_din0 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2590_p_din1 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2590_p_opcode sc_out sc_lv 2 signal -1 } 
	{ grp_fu_2590_p_dout0 sc_in sc_lv 32 signal -1 } 
	{ grp_fu_2590_p_ce sc_out sc_logic 1 signal -1 } 
	{ grp_fu_2594_p_din0 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2594_p_din1 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2594_p_opcode sc_out sc_lv 2 signal -1 } 
	{ grp_fu_2594_p_dout0 sc_in sc_lv 32 signal -1 } 
	{ grp_fu_2594_p_ce sc_out sc_logic 1 signal -1 } 
	{ grp_fu_2598_p_din0 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2598_p_din1 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2598_p_opcode sc_out sc_lv 2 signal -1 } 
	{ grp_fu_2598_p_dout0 sc_in sc_lv 32 signal -1 } 
	{ grp_fu_2598_p_ce sc_out sc_logic 1 signal -1 } 
	{ grp_fu_2602_p_din0 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2602_p_din1 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2602_p_opcode sc_out sc_lv 2 signal -1 } 
	{ grp_fu_2602_p_dout0 sc_in sc_lv 32 signal -1 } 
	{ grp_fu_2602_p_ce sc_out sc_logic 1 signal -1 } 
	{ grp_fu_2638_p_din0 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2638_p_din1 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2638_p_opcode sc_out sc_lv 2 signal -1 } 
	{ grp_fu_2638_p_dout0 sc_in sc_lv 32 signal -1 } 
	{ grp_fu_2638_p_ce sc_out sc_logic 1 signal -1 } 
	{ grp_fu_2642_p_din0 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2642_p_din1 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2642_p_opcode sc_out sc_lv 2 signal -1 } 
	{ grp_fu_2642_p_dout0 sc_in sc_lv 32 signal -1 } 
	{ grp_fu_2642_p_ce sc_out sc_logic 1 signal -1 } 
	{ grp_fu_2646_p_din0 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2646_p_din1 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2646_p_opcode sc_out sc_lv 2 signal -1 } 
	{ grp_fu_2646_p_dout0 sc_in sc_lv 32 signal -1 } 
	{ grp_fu_2646_p_ce sc_out sc_logic 1 signal -1 } 
	{ grp_fu_2650_p_din0 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2650_p_din1 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2650_p_opcode sc_out sc_lv 2 signal -1 } 
	{ grp_fu_2650_p_dout0 sc_in sc_lv 32 signal -1 } 
	{ grp_fu_2650_p_ce sc_out sc_logic 1 signal -1 } 
	{ grp_fu_2654_p_din0 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2654_p_din1 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2654_p_opcode sc_out sc_lv 2 signal -1 } 
	{ grp_fu_2654_p_dout0 sc_in sc_lv 32 signal -1 } 
	{ grp_fu_2654_p_ce sc_out sc_logic 1 signal -1 } 
	{ grp_fu_2658_p_din0 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2658_p_din1 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2658_p_opcode sc_out sc_lv 2 signal -1 } 
	{ grp_fu_2658_p_dout0 sc_in sc_lv 32 signal -1 } 
	{ grp_fu_2658_p_ce sc_out sc_logic 1 signal -1 } 
	{ grp_fu_2662_p_din0 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2662_p_din1 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2662_p_opcode sc_out sc_lv 2 signal -1 } 
	{ grp_fu_2662_p_dout0 sc_in sc_lv 32 signal -1 } 
	{ grp_fu_2662_p_ce sc_out sc_logic 1 signal -1 } 
	{ grp_fu_2666_p_din0 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2666_p_din1 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2666_p_opcode sc_out sc_lv 2 signal -1 } 
	{ grp_fu_2666_p_dout0 sc_in sc_lv 32 signal -1 } 
	{ grp_fu_2666_p_ce sc_out sc_logic 1 signal -1 } 
	{ grp_fu_2606_p_din0 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2606_p_din1 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2606_p_dout0 sc_in sc_lv 32 signal -1 } 
	{ grp_fu_2606_p_ce sc_out sc_logic 1 signal -1 } 
	{ grp_fu_2610_p_din0 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2610_p_din1 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2610_p_dout0 sc_in sc_lv 32 signal -1 } 
	{ grp_fu_2610_p_ce sc_out sc_logic 1 signal -1 } 
	{ grp_fu_2614_p_din0 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2614_p_din1 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2614_p_dout0 sc_in sc_lv 32 signal -1 } 
	{ grp_fu_2614_p_ce sc_out sc_logic 1 signal -1 } 
	{ grp_fu_2618_p_din0 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2618_p_din1 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2618_p_dout0 sc_in sc_lv 32 signal -1 } 
	{ grp_fu_2618_p_ce sc_out sc_logic 1 signal -1 } 
	{ grp_fu_2622_p_din0 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2622_p_din1 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2622_p_dout0 sc_in sc_lv 32 signal -1 } 
	{ grp_fu_2622_p_ce sc_out sc_logic 1 signal -1 } 
	{ grp_fu_2626_p_din0 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2626_p_din1 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2626_p_dout0 sc_in sc_lv 32 signal -1 } 
	{ grp_fu_2626_p_ce sc_out sc_logic 1 signal -1 } 
	{ grp_fu_2630_p_din0 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2630_p_din1 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2630_p_dout0 sc_in sc_lv 32 signal -1 } 
	{ grp_fu_2630_p_ce sc_out sc_logic 1 signal -1 } 
	{ grp_fu_2634_p_din0 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2634_p_din1 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2634_p_dout0 sc_in sc_lv 32 signal -1 } 
	{ grp_fu_2634_p_ce sc_out sc_logic 1 signal -1 } 
	{ grp_fu_2670_p_din0 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2670_p_din1 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2670_p_dout0 sc_in sc_lv 32 signal -1 } 
	{ grp_fu_2670_p_ce sc_out sc_logic 1 signal -1 } 
	{ grp_fu_2674_p_din0 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2674_p_din1 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2674_p_dout0 sc_in sc_lv 32 signal -1 } 
	{ grp_fu_2674_p_ce sc_out sc_logic 1 signal -1 } 
	{ grp_fu_2678_p_din0 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2678_p_din1 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2678_p_dout0 sc_in sc_lv 32 signal -1 } 
	{ grp_fu_2678_p_ce sc_out sc_logic 1 signal -1 } 
	{ grp_fu_2682_p_din0 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2682_p_din1 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2682_p_dout0 sc_in sc_lv 32 signal -1 } 
	{ grp_fu_2682_p_ce sc_out sc_logic 1 signal -1 } 
	{ grp_fu_2686_p_din0 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2686_p_din1 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2686_p_dout0 sc_in sc_lv 32 signal -1 } 
	{ grp_fu_2686_p_ce sc_out sc_logic 1 signal -1 } 
	{ grp_fu_2690_p_din0 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2690_p_din1 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2690_p_dout0 sc_in sc_lv 32 signal -1 } 
	{ grp_fu_2690_p_ce sc_out sc_logic 1 signal -1 } 
	{ grp_fu_2694_p_din0 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2694_p_din1 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2694_p_dout0 sc_in sc_lv 32 signal -1 } 
	{ grp_fu_2694_p_ce sc_out sc_logic 1 signal -1 } 
	{ grp_fu_2698_p_din0 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2698_p_din1 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_2698_p_dout0 sc_in sc_lv 32 signal -1 } 
	{ grp_fu_2698_p_ce sc_out sc_logic 1 signal -1 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "input_0_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":5, "type": "signal", "bundle":{"name": "input_0", "role": "address0" }} , 
 	{ "name": "input_0_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "input_0", "role": "ce0" }} , 
 	{ "name": "input_0_q0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "input_0", "role": "q0" }} , 
 	{ "name": "input_0_address1", "direction": "out", "datatype": "sc_lv", "bitwidth":5, "type": "signal", "bundle":{"name": "input_0", "role": "address1" }} , 
 	{ "name": "input_0_ce1", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "input_0", "role": "ce1" }} , 
 	{ "name": "input_0_q1", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "input_0", "role": "q1" }} , 
 	{ "name": "output_0_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "output_0", "role": "address0" }} , 
 	{ "name": "output_0_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "output_0", "role": "ce0" }} , 
 	{ "name": "output_0_we0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "output_0", "role": "we0" }} , 
 	{ "name": "output_0_d0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "output_0", "role": "d0" }} , 
 	{ "name": "output_0_address1", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "output_0", "role": "address1" }} , 
 	{ "name": "output_0_ce1", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "output_0", "role": "ce1" }} , 
 	{ "name": "output_0_we1", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "output_0", "role": "we1" }} , 
 	{ "name": "output_0_d1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "output_0", "role": "d1" }} , 
 	{ "name": "grp_fu_2574_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2574_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_2574_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2574_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_2574_p_opcode", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "grp_fu_2574_p_opcode", "role": "default" }} , 
 	{ "name": "grp_fu_2574_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2574_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_2574_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_2574_p_ce", "role": "default" }} , 
 	{ "name": "grp_fu_2578_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2578_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_2578_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2578_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_2578_p_opcode", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "grp_fu_2578_p_opcode", "role": "default" }} , 
 	{ "name": "grp_fu_2578_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2578_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_2578_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_2578_p_ce", "role": "default" }} , 
 	{ "name": "grp_fu_2582_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2582_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_2582_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2582_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_2582_p_opcode", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "grp_fu_2582_p_opcode", "role": "default" }} , 
 	{ "name": "grp_fu_2582_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2582_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_2582_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_2582_p_ce", "role": "default" }} , 
 	{ "name": "grp_fu_2586_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2586_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_2586_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2586_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_2586_p_opcode", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "grp_fu_2586_p_opcode", "role": "default" }} , 
 	{ "name": "grp_fu_2586_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2586_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_2586_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_2586_p_ce", "role": "default" }} , 
 	{ "name": "grp_fu_2590_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2590_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_2590_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2590_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_2590_p_opcode", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "grp_fu_2590_p_opcode", "role": "default" }} , 
 	{ "name": "grp_fu_2590_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2590_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_2590_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_2590_p_ce", "role": "default" }} , 
 	{ "name": "grp_fu_2594_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2594_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_2594_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2594_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_2594_p_opcode", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "grp_fu_2594_p_opcode", "role": "default" }} , 
 	{ "name": "grp_fu_2594_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2594_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_2594_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_2594_p_ce", "role": "default" }} , 
 	{ "name": "grp_fu_2598_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2598_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_2598_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2598_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_2598_p_opcode", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "grp_fu_2598_p_opcode", "role": "default" }} , 
 	{ "name": "grp_fu_2598_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2598_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_2598_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_2598_p_ce", "role": "default" }} , 
 	{ "name": "grp_fu_2602_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2602_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_2602_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2602_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_2602_p_opcode", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "grp_fu_2602_p_opcode", "role": "default" }} , 
 	{ "name": "grp_fu_2602_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2602_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_2602_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_2602_p_ce", "role": "default" }} , 
 	{ "name": "grp_fu_2638_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2638_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_2638_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2638_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_2638_p_opcode", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "grp_fu_2638_p_opcode", "role": "default" }} , 
 	{ "name": "grp_fu_2638_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2638_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_2638_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_2638_p_ce", "role": "default" }} , 
 	{ "name": "grp_fu_2642_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2642_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_2642_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2642_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_2642_p_opcode", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "grp_fu_2642_p_opcode", "role": "default" }} , 
 	{ "name": "grp_fu_2642_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2642_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_2642_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_2642_p_ce", "role": "default" }} , 
 	{ "name": "grp_fu_2646_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2646_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_2646_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2646_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_2646_p_opcode", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "grp_fu_2646_p_opcode", "role": "default" }} , 
 	{ "name": "grp_fu_2646_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2646_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_2646_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_2646_p_ce", "role": "default" }} , 
 	{ "name": "grp_fu_2650_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2650_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_2650_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2650_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_2650_p_opcode", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "grp_fu_2650_p_opcode", "role": "default" }} , 
 	{ "name": "grp_fu_2650_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2650_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_2650_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_2650_p_ce", "role": "default" }} , 
 	{ "name": "grp_fu_2654_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2654_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_2654_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2654_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_2654_p_opcode", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "grp_fu_2654_p_opcode", "role": "default" }} , 
 	{ "name": "grp_fu_2654_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2654_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_2654_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_2654_p_ce", "role": "default" }} , 
 	{ "name": "grp_fu_2658_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2658_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_2658_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2658_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_2658_p_opcode", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "grp_fu_2658_p_opcode", "role": "default" }} , 
 	{ "name": "grp_fu_2658_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2658_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_2658_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_2658_p_ce", "role": "default" }} , 
 	{ "name": "grp_fu_2662_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2662_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_2662_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2662_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_2662_p_opcode", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "grp_fu_2662_p_opcode", "role": "default" }} , 
 	{ "name": "grp_fu_2662_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2662_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_2662_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_2662_p_ce", "role": "default" }} , 
 	{ "name": "grp_fu_2666_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2666_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_2666_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2666_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_2666_p_opcode", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "grp_fu_2666_p_opcode", "role": "default" }} , 
 	{ "name": "grp_fu_2666_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2666_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_2666_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_2666_p_ce", "role": "default" }} , 
 	{ "name": "grp_fu_2606_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2606_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_2606_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2606_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_2606_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2606_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_2606_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_2606_p_ce", "role": "default" }} , 
 	{ "name": "grp_fu_2610_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2610_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_2610_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2610_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_2610_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2610_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_2610_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_2610_p_ce", "role": "default" }} , 
 	{ "name": "grp_fu_2614_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2614_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_2614_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2614_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_2614_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2614_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_2614_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_2614_p_ce", "role": "default" }} , 
 	{ "name": "grp_fu_2618_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2618_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_2618_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2618_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_2618_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2618_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_2618_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_2618_p_ce", "role": "default" }} , 
 	{ "name": "grp_fu_2622_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2622_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_2622_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2622_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_2622_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2622_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_2622_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_2622_p_ce", "role": "default" }} , 
 	{ "name": "grp_fu_2626_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2626_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_2626_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2626_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_2626_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2626_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_2626_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_2626_p_ce", "role": "default" }} , 
 	{ "name": "grp_fu_2630_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2630_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_2630_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2630_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_2630_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2630_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_2630_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_2630_p_ce", "role": "default" }} , 
 	{ "name": "grp_fu_2634_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2634_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_2634_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2634_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_2634_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2634_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_2634_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_2634_p_ce", "role": "default" }} , 
 	{ "name": "grp_fu_2670_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2670_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_2670_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2670_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_2670_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2670_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_2670_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_2670_p_ce", "role": "default" }} , 
 	{ "name": "grp_fu_2674_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2674_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_2674_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2674_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_2674_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2674_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_2674_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_2674_p_ce", "role": "default" }} , 
 	{ "name": "grp_fu_2678_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2678_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_2678_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2678_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_2678_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2678_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_2678_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_2678_p_ce", "role": "default" }} , 
 	{ "name": "grp_fu_2682_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2682_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_2682_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2682_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_2682_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2682_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_2682_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_2682_p_ce", "role": "default" }} , 
 	{ "name": "grp_fu_2686_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2686_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_2686_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2686_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_2686_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2686_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_2686_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_2686_p_ce", "role": "default" }} , 
 	{ "name": "grp_fu_2690_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2690_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_2690_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2690_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_2690_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2690_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_2690_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_2690_p_ce", "role": "default" }} , 
 	{ "name": "grp_fu_2694_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2694_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_2694_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2694_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_2694_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2694_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_2694_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_2694_p_ce", "role": "default" }} , 
 	{ "name": "grp_fu_2698_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2698_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_2698_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2698_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_2698_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_2698_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_2698_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_2698_p_ce", "role": "default" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "",
		"CDFG" : "l2_mm",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "171", "EstimateLatencyMax" : "171",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "input_0", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "output_0", "Type" : "Memory", "Direction" : "O"}]}]}


set ArgLastReadFirstWriteLatency {
	l2_mm {
		input_0 {Type I LastRead 155 FirstWrite -1}
		output_0 {Type O LastRead -1 FirstWrite 164}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "171", "Max" : "171"}
	, {"Name" : "Interval", "Min" : "171", "Max" : "171"}
]}

set PipelineEnableSignalInfo {[
]}

set Spec2ImplPortList { 
	input_0 { ap_memory {  { input_0_address0 mem_address 1 5 }  { input_0_ce0 mem_ce 1 1 }  { input_0_q0 mem_dout 0 32 }  { input_0_address1 MemPortADDR2 1 5 }  { input_0_ce1 MemPortCE2 1 1 }  { input_0_q1 MemPortDOUT2 0 32 } } }
	output_0 { ap_memory {  { output_0_address0 mem_address 1 4 }  { output_0_ce0 mem_ce 1 1 }  { output_0_we0 mem_we 1 1 }  { output_0_d0 mem_din 1 32 }  { output_0_address1 MemPortADDR2 1 4 }  { output_0_ce1 MemPortCE2 1 1 }  { output_0_we1 MemPortWE2 1 1 }  { output_0_d1 MemPortDIN2 1 32 } } }
}
