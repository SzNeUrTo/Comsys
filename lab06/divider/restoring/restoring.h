//------------------------------------------------------------------
// Simple 4-bits adder
// 
// SystemC for VHDL engineers
// (c)www.ht-lab.com
//------------------------------------------------------------------
#ifndef DEV_H
#define DEV_H

#include <systemc.h>
#include "setting.h"
                                
SC_MODULE(devider) {
    sc_uint<N_BIT_OPERATION> Q, A, M;
    sc_uint<1> S;
    sc_in<sc_uint<N_BIT_OPERATION> > DD, MM;
    sc_out<sc_uint<N_BIT_OPERATION> > QQ, AA;

    void p1() { 
        Q = DD.read();
        M = MM.read();
        A = 0;
        S = 0;
        
        for (int count = 0; count < N_BIT_OPERATION; count++) {
            (A, Q) = (A, Q) << 1;
            (S, A) = (S, A) - M;
            if (A[N_BIT_OPERATION-1]) {
                (S, A) = (S, A) + M;
                Q[0] = 0;
            }
            else {
                Q[0] = 1;
            }
        }

        QQ.write(Q);
        AA.write(A);
    }

    SC_CTOR(devider) {  
        SC_METHOD(p1); 
        sensitive << DD << AA;
    }
};
#endif

