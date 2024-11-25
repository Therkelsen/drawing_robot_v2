set moduleName hw_act_layer1
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
set C_modelName {hw_act_layer1}
set C_modelType { void 0 }
set C_modelArgList {
	{ output_0 float 32 regular {array 32 { 2 2 } 1 1 }  }
}
set C_modelArgMapList {[ 
	{ "Name" : "output_0", "interface" : "memory", "bitwidth" : 32, "direction" : "READWRITE"} ]}
# RTL Port declarations: 
set portNum 26
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ output_0_address0 sc_out sc_lv 5 signal 0 } 
	{ output_0_ce0 sc_out sc_logic 1 signal 0 } 
	{ output_0_we0 sc_out sc_logic 1 signal 0 } 
	{ output_0_d0 sc_out sc_lv 32 signal 0 } 
	{ output_0_q0 sc_in sc_lv 32 signal 0 } 
	{ output_0_address1 sc_out sc_lv 5 signal 0 } 
	{ output_0_ce1 sc_out sc_logic 1 signal 0 } 
	{ output_0_we1 sc_out sc_logic 1 signal 0 } 
	{ output_0_d1 sc_out sc_lv 32 signal 0 } 
	{ output_0_q1 sc_in sc_lv 32 signal 0 } 
	{ grp_fu_362_p_din0 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_362_p_din1 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_362_p_opcode sc_out sc_lv 5 signal -1 } 
	{ grp_fu_362_p_dout0 sc_in sc_lv 1 signal -1 } 
	{ grp_fu_362_p_ce sc_out sc_logic 1 signal -1 } 
	{ grp_fu_367_p_din0 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_367_p_din1 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_367_p_opcode sc_out sc_lv 5 signal -1 } 
	{ grp_fu_367_p_dout0 sc_in sc_lv 1 signal -1 } 
	{ grp_fu_367_p_ce sc_out sc_logic 1 signal -1 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "output_0_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":5, "type": "signal", "bundle":{"name": "output_0", "role": "address0" }} , 
 	{ "name": "output_0_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "output_0", "role": "ce0" }} , 
 	{ "name": "output_0_we0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "output_0", "role": "we0" }} , 
 	{ "name": "output_0_d0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "output_0", "role": "d0" }} , 
 	{ "name": "output_0_q0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "output_0", "role": "q0" }} , 
 	{ "name": "output_0_address1", "direction": "out", "datatype": "sc_lv", "bitwidth":5, "type": "signal", "bundle":{"name": "output_0", "role": "address1" }} , 
 	{ "name": "output_0_ce1", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "output_0", "role": "ce1" }} , 
 	{ "name": "output_0_we1", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "output_0", "role": "we1" }} , 
 	{ "name": "output_0_d1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "output_0", "role": "d1" }} , 
 	{ "name": "output_0_q1", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "output_0", "role": "q1" }} , 
 	{ "name": "grp_fu_362_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_362_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_362_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_362_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_362_p_opcode", "direction": "out", "datatype": "sc_lv", "bitwidth":5, "type": "signal", "bundle":{"name": "grp_fu_362_p_opcode", "role": "default" }} , 
 	{ "name": "grp_fu_362_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_362_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_362_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_362_p_ce", "role": "default" }} , 
 	{ "name": "grp_fu_367_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_367_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_367_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_367_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_367_p_opcode", "direction": "out", "datatype": "sc_lv", "bitwidth":5, "type": "signal", "bundle":{"name": "grp_fu_367_p_opcode", "role": "default" }} , 
 	{ "name": "grp_fu_367_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_367_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_367_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_367_p_ce", "role": "default" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "",
		"CDFG" : "hw_act_layer1",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "31", "EstimateLatencyMax" : "31",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "output_0", "Type" : "Memory", "Direction" : "IO"}]}]}


set ArgLastReadFirstWriteLatency {
	hw_act_layer1 {
		output_0 {Type IO LastRead 16 FirstWrite 16}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "31", "Max" : "31"}
	, {"Name" : "Interval", "Min" : "31", "Max" : "31"}
]}

set PipelineEnableSignalInfo {[
]}

set Spec2ImplPortList { 
	output_0 { ap_memory {  { output_0_address0 mem_address 1 5 }  { output_0_ce0 mem_ce 1 1 }  { output_0_we0 mem_we 1 1 }  { output_0_d0 mem_din 1 32 }  { output_0_q0 mem_dout 0 32 }  { output_0_address1 MemPortADDR2 1 5 }  { output_0_ce1 MemPortCE2 1 1 }  { output_0_we1 MemPortWE2 1 1 }  { output_0_d1 MemPortDIN2 1 32 }  { output_0_q1 MemPortDOUT2 0 32 } } }
}
