#ifndef PRINT_H
#define PRINT_H

#include <systemc.h>
SC_MODULE(print) {
    sc_in<bool> clk;
    sc_in<sc_uint<N_BIT_OPERATION> > DD, MM, QQ, AA;

    void ps1() {
    	cout << DD.read() << " = " << MM.read() << " (" << QQ.read() << ") " << " + " << AA.read() << endl;
    }

    SC_CTOR(print) {  
        SC_METHOD(ps1);
        sensitive << clk.neg();
        dont_initialize();
    }
};


#endif