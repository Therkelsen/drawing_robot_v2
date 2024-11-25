# This script segment is generated automatically by AutoPilot

set axilite_register_dict [dict create]
set port_AXI_CPU {
out_r { 
	dir O
	width 32
	depth 1
	mode ap_vld
	offset 16
	offset_end 23
}
input_img { 
	dir I
	width 32
	depth 100
	mode ap_memory
	offset 512
	offset_end 1023
}
ap_start { }
ap_done { }
ap_ready { }
ap_idle { }
}
dict set axilite_register_dict AXI_CPU $port_AXI_CPU


