//------------------------------------------------------------------
// Simple 4-bits adder
// 
// SystemC for VHDL engineers
// (c)www.ht-lab.com
//------------------------------------------------------------------
#ifndef MUL_H
#define MUL_H

#include <systemc.h>
#include "setting.h"
                                
SC_MODULE(multiplier) {
    // int nBitOperation=4;
    // sc_in<bool> clk;
    sc_in<sc_uint<N_BIT_OPERATION> > A, B;
    sc_out<sc_uint<N_BIT_OPERATION*2> > C;
    sc_out<sc_uint<N_BIT_OPERATION> > OutA, OutB;
    sc_in<bool> start;
    sc_in<bool> clk;
    sc_out<bool> ready;
    unsigned int RA, RB, RC;
    int AA, BB;
    
    bool odd(int v) {
        return v % 2 == 1;
    }

    void p1() { 
        
        while (1) {
            wait();
            RA=A.read(), RB=B.read(), RC=0;
            AA=RA; BB=RB;
            cout << endl;
            while(RA>0)
            {
                if (odd(RA)) {
                    RC=RC+RB;
                }
                RA = RA >> 1;
                RB = RB << 1;
                OutA.write(RA);
                OutB.write(RB);
                C.write(RC);
                wait();
            }
            ready.write(1);
            wait();
            ready.write(0);
            cout << "[RA = " << AA << " RB = " << BB << " RC = " << RC << "]" << endl;
        }
    }

    SC_CTOR(multiplier) {  
        SC_THREAD(p1); 
        sensitive << clk.pos();
    }
};
#endif

