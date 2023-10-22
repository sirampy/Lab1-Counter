# Making the counter load value from vbuddy:
jus as a note, it says modify counter.sv in the instructions when it perhaps should say counter_tb.cpp
- switch into oneshot mode
- read value from vbuddy into the v and trigger ld when required:
```cpp
    // change signals during
    shoot = vbdFlag();
    top->ld = shoot;
    if(shoot){ // this conditional is kinda unnecesary
        top->v = vbdValue();
    }
    top->rst = 0;
```
- turns out i failed at following lab instructions :() and i only need to preset it:
```cpp
    // init simulation inputs
    top->clk = 1;
    top->rst = 0;
    top->ld = 1;
    top->v = vbdValue();
```
```cpp
    // change signals during
    top->ld = 0;
```
# implementing steping only when button is pressed:
at the top of main loop:
```cpp
    step = 0;
    while(step == 0){ // this is cringe - infinite loops W/O timeout are a bad idea - plus there is defo a cleaner way to implement this
        step = vbdFlag();
    }
```