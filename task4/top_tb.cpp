#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"
const char* PROG_NAME = "Lab1: Counter"; // could put all params in a namespace if i end up with a lot of them

int main(int argc, char **argv, char **env){
    int i; 
    int clk;
    int pause = -1;
    int step = 0;

    Verilated::commandArgs(argc, argv);
    // init verilog instance
    Vcounter* top = new Vcounter();
    //init trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp, 99);
    tfp->open ("top.vcd");

    // init vbuddy
    if (vbdOpen()!=1) return (-1);
    vbdHeader(PROG_NAME);
    vbdSetMode(1);

    // init simulation inputs
    top->clk = 1;
    top->rst = 0;
    top->ld = 1;
    top->v = vbdValue();

    // run simulation 
    for (i = 0; i < 500; i++){

        step = 0;
        while(step == 0){ // this is cringe - infinite loops W/O timeout are a bad idea - plus there is defo a cleaner way to implement this
            step = vbdFlag();
        }

        for (clk = 0; clk < 2; clk++){
            tfp->dump (2*i+clk);   //unit is in ps
            top->clk = !top->clk;
            top->eval ();
        }

        // send bcd to vbuddy 
        
        vbdHex(4, (int(top->bcd) >> 16) & 0xF);
        vbdHex(3, (int(top->bcd) >> 8) & 0xF);
        vbdHex(2, (int(top->bcd) >> 4) & 0xF);
        vbdHex(1, (int(top->bcd)) & 0xF);
        
        //  current cycle
        // vbdPlot(int(top->bcd), 0, 255);
        vbdCycle(i+1);

        // change signals during
        top->ld = 0;

        // exit on finish or stop
        if (Verilated::gotFinish()) exit(0);
    }

    vbdClose();
    tfp -> close();
    exit(0);
};