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
    sc_out<sc_uint<N_BIT_OPERATION> > DD, MM;

    void setTestCase(int a, int b) {
        DD.write(a);
        MM.write(b);
        wait();
    }

    void ps1() {
        wait();
        setTestCase(38, 5);
        setTestCase(35, 3);
        setTestCase(14, 3);
        setTestCase(30, 4);
        setTestCase(12, 5);
        setTestCase(30, 6);

        sc_stop();
    }

    SC_CTOR(stim) {  
        SC_THREAD(ps1);
        sensitive << clk.pos();
    }
};
#endif

