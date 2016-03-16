#ifndef CHECK_H
#define CHECK_H

#include <systemc.h>

#include <iostream>
using namespace std;       
                                
SC_MODULE(check) {
    sc_in<bool> clk, enable, rw, clr;//, ready;
    sc_in<sc_uint<32> > din, dout;
    // sc_in<sc_uint<5> > _index;

    // sc_in<sc_uint<5> > addr;
    sc_uint<5> module__index;
    sc_in<sc_uint<5> > _index;
    sc_in<sc_uint<5> > addr;

    // sc_uint<5> module__index;

    void pc1() {
        // while (true) {

            if (addr.read() == module__index) {


            // if (ready.read() == true) {
                if (enable.read() == true) {
                    if (rw.read() == 0) {
                      cout << "[";
                    // }
                        
                        cout << "module_index = " << module__index << " --> din = " << din.read() << " dout = " << dout.read() << " enable = " << enable.read() << " rw = " << rw.read() << " clr = " << clr.read(); // << " clk = " << clk;

                    // if (rw.read() == 0) {
                      cout << "]";
                      cout << endl << endl;
                    }
                    // cout << endl << endl;
                    
                }
                else {
                    // cout << "================= Disable (enable = 0) =================" << endl << endl;   
                }
            // }

            }

            // wait();
        // }
    }

    void set_index() {
        module__index = _index.read();
    }

    SC_CTOR(check) {     
        SC_METHOD(pc1);                     
        sensitive << enable << rw << clr << din << dout;
        SC_METHOD(set_index);                     
        sensitive << _index;
        // SC_METHOD(pc1);
        // sensitive << ready;
        // SC_CTHREAD(pc1, ready);
    }
};
#endif
