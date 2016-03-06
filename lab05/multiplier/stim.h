//------------------------------------------------------------------
// Simple 4-bits adder
// 
// SystemC for VHDL engineers
// (c)www.ht-lab.com
//------------------------------------------------------------------
#ifndef STIM_H
#define STIM_H

#include <systemc.h>
#include "setting.h"
                                
SC_MODULE(stim) {
    sc_in<bool> clk;
    sc_out<sc_uint<N_BIT_OPERATION> > RA, RB;
    sc_in<bool> ready;
    sc_out<bool> start;

    void setTestCase(int a, int b) {
        RA.write(a);
        RB.write(b);
        wait();
    }

    void ps1() {

        setTestCase(13, 11); // 1101 x 1011
        setTestCase(15, 13); 
        setTestCase(13, 12); 
        setTestCase(5, 7); 
        setTestCase(3, 1);
        setTestCase(65535, 65535);


        sc_stop();                          // End simulation
    }

    SC_CTOR(stim) {  
        SC_THREAD(ps1);                     // Run ps1 only ones
        sensitive << ready.neg();
    }
};
#endif

