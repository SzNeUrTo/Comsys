//------------------------------------------------------------------
// Simple Testbench for 4-bits adder file
// 
// SystemC for VHDL engineers
// (c)www.ht-lab.com
//------------------------------------------------------------------

#include <systemc.h>

#include "adder.h"
#include "stim.h"
#include "check.h"

int sc_main(int argc, char* argv[])
{
    sc_signal<sc_uint<4> > ain, bin, sum;
    sc_signal<bool> ci,co;
    sc_signal<bool> oflag,zflag;

    sc_clock clk("clk",10,SC_NS,0.5);   // Create a clock signal

    adder DUT("adder");                 // Instantiate Device Under Test
    DUT.ain(ain);                       // Connect ports
    DUT.bin(bin);
    DUT.ci(ci); 
    DUT.sum(sum);
    DUT.co(co);
    DUT.oflag(oflag);
    DUT.zflag(zflag);

    stim STIM("stimulus");              // Instantiate stimulus generator
    STIM.clk(clk);  
    STIM.ain(ain);
    STIM.bin(bin);
    STIM.ci(ci);

    check CHECK("checker");             // Instantiate checker
    CHECK.clk(clk); 
    CHECK.ain(ain);
    CHECK.bin(bin);
    CHECK.ci(ci);
    CHECK.sum(sum);
    CHECK.co(co);

    sc_start(SC_ZERO_TIME);
    sc_trace_file *tf = sc_create_vcd_trace_file("trace");
    sc_trace(tf, ain, "A");
    sc_trace(tf, bin, "B");
    sc_trace(tf, sum, "SUM");
    sc_trace(tf, ci, "CIN");
    sc_trace(tf, co, "COUT");
    sc_trace(tf, oflag, "OFlag");
    sc_trace(tf, zflag, "ZFlag");
    sc_trace(tf, clk, "CLOCK");

    sc_start(100, SC_NS);
    sc_close_vcd_trace_file(tf);

    return 0;                           // Return OK, no errors.
}
