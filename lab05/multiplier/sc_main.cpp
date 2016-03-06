//------------------------------------------------------------------
// Simple Testbench for 4-bits adder file
// 
// SystemC for VHDL engineers
// (c)www.ht-lab.com
//------------------------------------------------------------------

#include <systemc.h>

#include "multiplier.h"
#include "stim.h"
#include "setting.h"
// #include "controller.h"

int sc_main(int argc, char* argv[])
{
    sc_signal<sc_uint<N_BIT_OPERATION> > RA, RB;
    sc_signal<sc_uint<N_BIT_OPERATION*2> > RC;

    sc_signal<sc_uint<N_BIT_OPERATION> > OutA, OutB;


    // ready = 1 ok ready = 0 don't use don't finish
    sc_signal<bool> ready, start;

    sc_clock clk("clk", 10, SC_NS, 0.5);


    multiplier DUT("multiplier");
    DUT.A(RA);                       
    DUT.B(RB);

    DUT.C(RC);
    DUT.ready(ready);
    DUT.start(start);
    DUT.clk(clk);
    DUT.OutA(OutA);                       
    DUT.OutB(OutB);


    stim STIM("stimulus");
    STIM.start(start);
    STIM.ready(ready); 
    STIM.RA(RA);
    STIM.RB(RB);
    STIM.clk(clk);

    sc_start(SC_ZERO_TIME);
    sc_trace_file *tf = sc_create_vcd_trace_file("trace");
    sc_trace(tf, OutA, "RA");
    sc_trace(tf, OutB, "RB");
    sc_trace(tf, RC, "RC");
    sc_trace(tf, ready, "READY");
    sc_trace(tf, clk, "CLOCK");

    sc_start(10000, SC_NS);
    sc_close_vcd_trace_file(tf);

    return 0;                           // Return OK, no errors.
}
