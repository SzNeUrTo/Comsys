//------------------------------------------------------------------
// Simple 4-bits adder
// 
// SystemC for VHDL engineers
// (c)www.ht-lab.com
//------------------------------------------------------------------
#ifndef OUTPUTCOLLECT_H
#define OUTPUTCOLLECT_H

#include <systemc.h>

SC_MODULE(outputcollect) {
    sc_in<bool> clk;
    sc_in<sc_uint<8> > avg;

    void pc1() {
        int i = 0;
        sc_uint<8> outbuf[256];
        // wait();
        // sc_uint<8> outbuf[256];
        while (true) {
            wait();
            outbuf[i] = avg.read();
            cout << "outputcollect.h --> AVG = " << outbuf[i] << " [index = " << i << "] ";
            i++;
        }
    }

    SC_CTOR(outputcollect) {     
        SC_THREAD(pc1);                     
        sensitive << clk.pos();
        dont_initialize();
    }
};
#endif

