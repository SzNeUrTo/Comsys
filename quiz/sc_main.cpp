#include <systemc.h>

#include "Reduction.h"
#include "Stim.h"
#include "Outputcollect.h"
#include "Checker.h"

int sc_main(int argc, char* argv[]) {

    sc_signal<sc_uint<8> > A0, A1, A2, A3;
    sc_signal<sc_uint<8> > outbuf;
    sc_signal<sc_uint<8> > avg;

    sc_clock clk("clk", 10, SC_NS, 0.5);

    reduction DUT("reduction");
    DUT.clk(clk);
    DUT.A0(A0);
    DUT.A1(A1);
    DUT.A2(A2);
    DUT.A3(A3);
    DUT.avg(avg);
    
    stim STIM("stimulus");
    STIM.clk(clk);  
    STIM.A0(A0);
    STIM.A1(A1);
    STIM.A2(A2);
    STIM.A3(A3);

    outputcollect OUTCL("outputcollect");
    OUTCL.clk(clk);
    OUTCL.avg(avg);

    check CHECK("checker");
    CHECK.clk(clk);
    CHECK.avg(avg);

    sc_start(SC_ZERO_TIME);
    sc_trace_file *tf = sc_create_vcd_trace_file("trace");
    sc_trace(tf, A0, "A0");
    sc_trace(tf, A1, "A1");
    sc_trace(tf, A2, "A2");
    sc_trace(tf, A3, "A3");
    sc_trace(tf, avg, "AVG");
    sc_trace(tf, clk, "CLOCK");

    sc_start(10000000, SC_NS);
    sc_close_vcd_trace_file(tf);

    return 0;
}
