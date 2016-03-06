//------------------------------------------------------------------
// Simple 4-bits adder
// 
// SystemC for VHDL engineers
// (c)www.ht-lab.com
//------------------------------------------------------------------
#ifndef STIM_H
#define STIM_H

#include <systemc.h>
                                
SC_MODULE(stim) {
    sc_in<bool> clk;
    sc_out<sc_int<4> > ain, bin;
    sc_out<bool> ci;

    void ps1() {    
        wait();

        ain.write("0b0000");
        bin.write("0b0000");
        ci.write(false);
        wait();

        ain.write("0b0100");
        bin.write("0b0010");
        ci.write(false);
        wait();             

        ain.write("0b1110");
        bin.write("0b0010");
        ci.write(false);
        wait();         

        ain.write(-1);
        bin.write(-5);
        ci.write(false);
        wait();

        ain.write(-8);
        bin.write(1);
        ci.write(false);
        wait();

        ain.write(-8);
        bin.write(-1);
        ci.write(false);
        wait();

        ain.write(7);
        bin.write(1);
        ci.write(false);
        wait();

        ain.write(5);
        bin.write(1);
        ci.write(true);
        wait();

        ain.write(7);
        bin.write(5);
        ci.write(true);
        wait();  

        ain.write(-5);
        bin.write(3);
        ci.write(true);
        wait(); 

        ain.write(0);
        bin.write(0);
        ci.write(false);
        wait();

        sc_stop();                          // End simulation
    }

    SC_CTOR(stim) {  
        SC_THREAD(ps1);                     // Run ps1 only ones
        sensitive << clk.pos();
    }
};
#endif

