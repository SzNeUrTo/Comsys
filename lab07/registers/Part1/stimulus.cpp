// #include "reg4bit.h"
#include "reg16bit.h"
#include "check.h"
#include <systemc.h>
// #include "stimulus.h"

int sc_main(int argc, char* argv[]) {

    sc_signal<sc_uint<16> > din, dout;   // Local signals
    sc_signal<bool> reset, ready;
    sc_signal<bool>  enable, rw, clr;

    sc_clock clk("clk",10,SC_NS);       // Create a 10ns period clock signal

    reg16 DUT("reg16");           // Instantiate Device Under Test
    DUT.clk(clk);                       // Connect ports
    DUT.reset(reset);
    DUT.din(din); 
    DUT.dout(dout);
    DUT.enable(enable);
    DUT.rw(rw);
    DUT.clr(clr);
    DUT.ready(ready);

    check CHECK("check");
    CHECK.clk(clk);
    CHECK.din(din);
    CHECK.dout(dout);
    CHECK.enable(enable);
    CHECK.rw(rw);
    CHECK.clr(clr);
    CHECK.ready(ready);

    // stim STIM("stim");
    // STIM.clk(clk);
    // STIM.din(din);
    // STIM.enable(enable);
    // STIM.rw(rw);
    // STIM.clr(clr);
    // STIM.ready(ready);

    sc_trace_file *fp;                  // VCD filepointer
    fp=sc_create_vcd_trace_file("wave");// Create wave.vcd file
    sc_trace(fp,clk,"clk");             // Add signals to trace file
    sc_trace(fp,dout,"dout");
    sc_trace(fp,rw,"rw");
    sc_trace(fp,clr,"clr");
    sc_trace(fp,din,"din");
    sc_trace(fp,enable,"enable");

    // sc_start();
    // sc_initialize();
    

    sc_start(SC_ZERO_TIME);
    enable = 1, rw = 1, clr = 0;
    sc_start(100 , SC_NS);

    clr=1, enable = 1, rw=1, din = 3;
    sc_start(100 , SC_NS);

    enable =1, rw=0;//, read out // should read 3
    sc_start(100 , SC_NS);

    enable =0, rw=1, din = 1;
    sc_start(100 , SC_NS);
    
    enable =1, rw=0;//, read out  // should read 3
    sc_start(100 , SC_NS);

    enable = 1, rw =1, din = 15; clr = 1;
    sc_start(100 , SC_NS);
    
    enable =1, rw=0;//, read din // read 15
    sc_start(100 , SC_NS);

    // enable=1, clr=0;
    // sc_start(100 , SC_NS);
            
    sc_close_vcd_trace_file(fp);        // close wave.vcd
    return 0;                           // Return OK, no errors.
}                                       // no ;
