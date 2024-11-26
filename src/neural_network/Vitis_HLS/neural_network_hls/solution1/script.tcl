############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
############################################################
open_project neural_network_hls
set_top nn_inference
add_files matmul.hpp
add_files matmul.cpp
add_files -tb matmul_tb.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution1" -flow_target vivado
set_part {xczu3eg-sbva484-1-e}
create_clock -period 10 -name default
config_export -format ip_catalog -output /home/peterparker/uni/embeddedsystems/drawing_robot_v2/src/neural_network/Vitis_HLS/nn_inference.zip -rtl vhdl
source "./neural_network_hls/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -rtl vhdl -format ip_catalog -output /home/peterparker/uni/embeddedsystems/drawing_robot_v2/src/neural_network/Vitis_HLS/nn_inference.zip
