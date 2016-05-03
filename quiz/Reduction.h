#ifndef REDUCTION_H
#define REDUCTION_H

#include <systemc.h>
                                
SC_MODULE(reduction) {
    sc_in<bool> clk;
    sc_in<sc_uint<8> > A0, A1, A2, A3;
    sc_out<sc_uint<8> > avg;

    void pc1() {    
        avg.write((A0.read() + A1.read() + A2.read() + A3.read()) / 4);
    }

    SC_CTOR(reduction) {     
        SC_METHOD(pc1);                     
        sensitive << A0 << A1 << A2 << A3;
        dont_initialize();
    }
};
#endif

