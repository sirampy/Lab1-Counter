#!/bin/bash

# setup params
MODULE_NAME="top"
MODULE_NAME_V="V${MODULE_NAME}"
TB="${MODULE_NAME}_tb.cpp"
SV="${MODULE_NAME}.sv"
MK="${MODULE_NAME_V}.mk"
VCD="${MODULE_NAME}.vcd"

#clean
rm -r obj_dir
rm -f counter.vcd

# run verilator on counter_tb.cpp
verilator -Wall --cc --trace $SV --exe $TB

# build cpp file
make -j -C obj_dir/ -f $MK $MODULE_NAME_V

# run executable to make vcd
obj_dir/$MODULE_NAME_V

# open in gtkwave
# gtkwave $VCD
