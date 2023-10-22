# converting to bcd
I belive verilator automatically links in all required sv modules, so minimal work was needed to get the new top.sv to work properly:
- change name of module in doit.sh
- change top_tb.cpp to use correct inputs and module names
- ensure i was using the correct version of counter - top.sv appears to have v included as a input, but dosnt use the version of the counter that takes v as an input, so i decide to use the version of counter without v.