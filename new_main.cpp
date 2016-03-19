#include <systemc.h>

#include "setting.h"
#include "check.h"
#include "mips_reg.h"




int sc_main(int argc, char* argv[]) {

    sc_signal<sc_uint<N_BIT_REG> > din, dout;
    sc_signal<bool> reset, ready;
    sc_signal<bool>  enable, rw, clr;
    sc_signal<sc_uint<BIT_ADDR> > addr;

    sc_clock clk("clk",10,SC_NS,0.5);
    
    check CHECK("checker");
    CHECK.clk(clk);
    CHECK.enable(enable);
    CHECK.rw(rw);
    CHECK.clr(clr);
    CHECK.din(din);
    CHECK.dout(dout);
    CHECK.addr(addr);

    mips_reg MIPSREG("mips");
    MIPSREG.clk(clk);
    MIPSREG.enable(enable);
    MIPSREG.rw(rw);
    MIPSREG.clr(clr);
    MIPSREG.addr(addr);
    MIPSREG.din(din);
    MIPSREG.dout(dout);
    MIPSREG.reset(reset);

    
    

    sc_start(SC_ZERO_TIME);

    enable =0, rw=1, addr = 1, din = 27, clr=1;
    sc_start(100 , SC_NS);
    enable =1;
    sc_start(100 , SC_NS);
    rw=0, addr = 1, din = 27;
    sc_start(100 , SC_NS);


    enable =0, rw=1;
    sc_start(100 , SC_NS);
    enable=1 , addr = 7, din = 25;
    sc_start(100 , SC_NS);
    rw=0;
    sc_start(100 , SC_NS);


    enable =0, rw=1;
    sc_start(100 , SC_NS);
    enable=1 , addr = 5, din = 3;
    sc_start(100 , SC_NS);
    rw=0;
    sc_start(100 , SC_NS);

    return 0;                           // Return OK, no errors.
}                                       // no ;
