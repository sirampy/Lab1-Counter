# WTF is goint on?
The easiest way to tell what is going on is to look at the doit.sh script as it automoates the build process.

## sources:
**counter.sv** = SystemVerilog module for our counter

**counter_tb.cpp** = testbench used by Verilatore

**doit.sh** = build script -> changing MODULE_NAME should be enough to get it to work for similar modules with the same naming scheme

## Intermediate steps:
### obj_dir:
files produced by verilator, including the makefile to create the executable:

* **Vcounter.mk** = make file to create the excecutable

* **Vcounter** = excecutable to create the wavefrom

## outputs:
**counter.vcd** = waveform genereated

## others

viewing the output in GTKwiewer should look something like:

![wavefrom](images/waveform)

#challenge:
* Added a variable to track how manny cycles to pause for to the test bench:
```
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
```
* Added 
