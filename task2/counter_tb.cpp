#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"
#include<iostream>

const char* PROG_NAME = "Lab1: Counter"; // could put all params in a namespace if i end up with a lot of them

int main(int argc, char **argv, char **env){
    int i; 
    int clk;
    int pause = -1;

    Verilated::commandArgs(argc, argv);
    // init verilog instance
    Vcounter* top = new Vcounter();
    //init trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp, 99);
    tfp->open ("counter.vcd");

    // init vbuddy

    if (vbdOpen()!=1) return (-1);
    vbdHeader(PROG_NAME);

    // init simulation inputs
    top->clk = 1;
    top->rst = 1;
    top->en = 0;

    // run simulation 
    for (i = 0; i < 500; i++){
        for (clk = 0; clk < 2; clk++){
            tfp->dump (2*i+clk);   //unit is in ps
            top->clk = !top->clk;
            top->eval ();
        }

        // send count to vbuddy 
        /*
        vbdHex(4, (int(top->count) >> 16) & 0xF);
        vbdHex(3, (int(top->count) >> 8) & 0xF);
        vbdHex(2, (int(top->count) >> 4) & 0xF);
        vbdHex(1, (int(top->count)) & 0xF);
        */
        //  current cycle
        vbdPlot(int(top->count), 0, 255);
        vbdCycle(i+1);

        // change signals during
        top->rst = (i<2) | (i == 15);
        top->en = vbdFlag(); // set allow enable to be set by button

        // exit on finish or stop
        if (Verilated::gotFinish()) exit(0);
    }

    vbdClose();
    tfp -> close();
    exit(0);
};