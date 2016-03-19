#ifndef MIPS_REG
#define MIPS_REG

#include "reg16bit.h"
#include "setting.h"
#include <systemc.h>

#include <iostream>
using namespace std;       

                                
SC_MODULE(mips_reg) {
    sc_in<bool> clk, enable, rw, clr, reset;
    sc_in<sc_uint<N_BIT_REG> > din;
    sc_out<sc_uint<N_BIT_REG> > dout;
    
    sc_signal<sc_uint<5> > _index[N_MODULE];
    sc_in<sc_uint<5> > addr;
    sc_signal<sc_uint<N_BIT_REG> > _din[N_MODULE], _dout[N_MODULE];

    reg16* R[N_MODULE];

    void pc1() {
        // cout << _dout[addr.read()] << endl;
        dout.write(_dout[addr.read()]);
    }

    SC_CTOR(mips_reg) {     
        SC_METHOD(pc1);                     
        sensitive << enable << rw << clr << din << addr << reset;

        for (int i = 0; i < N_MODULE; i++) {
            char name_reg[100] = "reg_";
            name_reg[4] = (char)(i/10 + '0');
            name_reg[5] = (char)(i%10 + '0') ;

            R[i] = new reg16(name_reg);
            R[i] -> clk(clk);
            R[i] -> reset(reset);
            R[i] -> din(_din[i]);
            R[i] -> dout(_dout[i]);
            R[i] -> enable(enable);
            R[i] -> rw(rw);
            R[i] -> clr(clr);

            R[i] -> _index(_index[i]);
            R[i] -> addr(addr);
        }

        for (int i = 0; i < N_MODULE; i++) {
            _index[i] = i;
        }
    }


    
};
#endif
