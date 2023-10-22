# what i did:
- setup vbuddy.cfg
- setup initialised and ended the serial communication
```
    // init vbuddy

    if (vbdOpen()!=1) return (-1);
    vbdHeader(PROG_NAME);
```
```
    vbdClose();
    tfp -> close();
    exit(0);
```
getting this to work appears to be slightly tempramental. I needed to flick a few switches on the vbuddy to get it to ack() properly.
- plotted the output of the counter to a 7seg display simulated on the vbuddy's screen
```
    // send count to vbuddy 
    
    vbdHex(4, (int(top->count) >> 16) & 0xF);
    vbdHex(3, (int(top->count) >> 8) & 0xF);
    vbdHex(2, (int(top->count) >> 4) & 0xF);
    vbdHex(1, (int(top->count)) & 0xF);
    
    //  current cycle
    vbdCycle(i+1);
```
- ploted the output of the counter with the vbdPlot function
```
    // output to vbuddy
    vbdPlot(int(top->count), 0, 255);
    vbdCycle(i+1);
```
- made en read from the vbdFlag
```
    top->en = vbdFlag(); // set allow enable to be set by button
```
# CHALLENGE:
I changed the function of en to set the direction of counting
```
module counter #(
    parameter WIDTH = 8
)(
    input logic                 clk,    // clock (duh)
    input logic                 rst,    // reset
    input logic                 en,     // count direction
    output logic[WIDTH-1:0]     count   // count output
);

always_ff @(posedge clk, posedge rst) // CHALLENGE asynchronous reset
    if (rst) count <= {WIDTH{1'b0}};
    else count <= count + ((-1)**(en+1))*{{WIDTH-1{1'b0}}, 1}; // could be rewrittn with a mux? also why the brackets around the first arg

endmodule
```
