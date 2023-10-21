#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

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

    // init simulation inputs
    top->clk = 1;
    top->rst = 1;
    top->en = 0;

    // run simulation 
    for (i = 0; i < 300; i++){
        for (clk = 0; clk < 2; clk++){
            tfp->dump (2*i+clk);   //unit is in ps
            top->clk = !top->clk;
            top->eval ();
        }
    
        // change signals during
        top->rst = (i<2) | (i == 15);
        top->en = !(i<=4);

        // CHALLENGE: set pause enable for 3 cycles counter reaches 9 (i feel like this is a janky way of doint it)
        
        if(pause > 0){
            top->en = 0;
            pause -= 1;
        }else if(pause == 0){
            pause -= 1;
        }else if((top->count == 8) & (pause != 0)){ // needs to set pause at 8 as this line if code is before the model is evaluated
            pause = 3;
        }
        if(top->rst == 1){
            pause = 0;
        }

        // exit on finish or stop
        if (Verilated::gotFinish()) exit(0);
    }

    tfp -> close();
    exit(0);
};