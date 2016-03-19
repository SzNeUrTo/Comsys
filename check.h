#ifndef CHECK_H
#define CHECK_H

#include "setting.h"
#include <systemc.h>

#include <iostream>
using namespace std;       
                                
SC_MODULE(check) {
    sc_in<bool> clk, enable, rw, clr;//, ready;
    sc_in<sc_uint<N_BIT_REG> > din, dout;
    // sc_uint<BIT_ADDR> module__index;
    // sc_in<sc_uint<BIT_ADDR> > _index;
    sc_in<sc_uint<BIT_ADDR> > addr;

    // sc_uint<5> module__index;

    void pc1() {
            if (enable.read() == true) {
                if (rw.read() == 0) {
                  cout << "[";
                // }
                    cout << "ADDR = " << addr.read() << " --> din = " << din.read() << " dout = " << dout.read() << " enable = " << enable.read() << " rw = " << rw.read() << " clr = " << clr.read(); // << " clk = " << clk;
                    

                // if (rw.read() == 0) {
                  cout << "]";
                  cout << endl << endl;
                }
                // cout << endl << endl;
                
            }
    }

    SC_CTOR(check) {     
        SC_METHOD(pc1);                     
        sensitive << enable << rw << clr << din << dout;
    }
};
#endif
