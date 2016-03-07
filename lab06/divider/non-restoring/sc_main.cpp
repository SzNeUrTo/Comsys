//------------------------------------------------------------------
// Simple Testbench for 4-bits adder file
// 
// SystemC for VHDL engineers
// (c)www.ht-lab.com
//------------------------------------------------------------------

#include <systemc.h>

#include "non-restoring.h"
#include "print.h"
#include "stim.h"
#include "setting.h"

int sc_main(int argc, char* argv[])
{
    sc_signal<sc_uint<N_BIT_OPERATION> > QQ, DD, MM, AA;

    sc_clock clk("clk", 10, SC_NS, 0.5);

    devider DUT("devider");
    DUT.QQ(QQ);
    DUT.DD(DD);
    DUT.MM(MM);
    DUT.AA(AA);

    stim STIM("stimulus");
    STIM.DD(DD);
    STIM.MM(MM);
    STIM.clk(clk);

    print PRINT("print");
    PRINT.clk(clk);
    PRINT.QQ(QQ);
    PRINT.DD(DD);
    PRINT.MM(MM);
    PRINT.AA(AA);

    sc_start(SC_ZERO_TIME);
    sc_trace_file *tf = sc_create_vcd_trace_file("trace");
    sc_trace(tf, QQ, "Q");
    sc_trace(tf, DD, "D");
    sc_trace(tf, MM, "M");
    sc_trace(tf, AA, "A");
    sc_trace(tf, clk, "CLOCK");

    sc_start(10000, SC_NS);
    sc_close_vcd_trace_file(tf);

    return 0;
}
