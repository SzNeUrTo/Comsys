//------------------------------------------------------------------
// Simple 4-bits adder
// 
// SystemC for VHDL engineers
// (c)www.ht-lab.com
//------------------------------------------------------------------
#ifndef ADDER_H
#define ADDER_H

#include <systemc.h>
                                
SC_MODULE(adder) {
    sc_in<sc_int<4> > ain, bin;
    sc_in<bool> ci;
    sc_out<sc_int<4> > sum;
    sc_out<bool> co;

    bool co0, co1, co2, co3;
    sc_int<4> sum_s;

    // sc_out<bool> zflag, oflag;
    bool zflag, oflag;

    // 1-bit ripple carry fulladder, note the cof reference bool&
    bool fulladder(bool a, bool b, bool cif, bool& cof) {
        bool sumr;
        sumr =(a ^ b) ^ cif;
        cof=(a & b) | ((a ^ b) & cif);          
        return sumr;    
    }

    void p1() { 
        sum_s[0]=fulladder(ain.read()[0],bin.read()[0],ci.read(), co0);
        sum_s[1]=fulladder(ain.read()[1],bin.read()[1],co0,co1);
        sum_s[2]=fulladder(ain.read()[2],bin.read()[2],co1,co2);
        sum_s[3]=fulladder(ain.read()[3],bin.read()[3],co2,co3);

        sum.write(sum_s);
        co.write(co3);

        zflag = !(sum_s[0] || sum_s[1] || sum_s[2] || sum_s[3] || co3);
        oflag = co3;

        if (zflag.read()==true) { // something like this.
            cout << " Zero Value" ;//<< endl;
        }
        if (oflag.read()==true) { // something like this.
            cout << " Over Flow" ;//<< endl;
        }
        cout << endl;
    }

    SC_CTOR(adder) {     
        SC_METHOD(p1);  
        sensitive << ain << bin << ci; 
    }
};
#endif
