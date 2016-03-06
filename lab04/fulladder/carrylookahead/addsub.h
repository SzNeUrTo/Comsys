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
    int nBitOperation = 4;
    sc_in<sc_int<nBitOperation> > ain, bin;
    sc_in<bool> ci;
    sc_out<sc_int<nBitOperation> > sum;
    sc_out<bool> co;

    bool co_[nBitOperation];
    sc_int<nBitOperation> sum_s;

    sc_out<bool> zflag, oflag;

    // 1-bit ripple carry fulladder, note the cof reference bool&

    bool fulladder(bool a, bool b, bool cif, bool& cof) { //
        bool sumr;
        sumr =(a ^ b) ^ cif;
        cof=(a & b) | ((a ^ b) & cif);          
        return sumr;    
    }


    void p1() { 
        sum_s[0]=fulladder(ain.read()[0],bin.read()[0]^ci.read(), ci.read(), co_[0]);
        for (int i = 1; i <= nBitOperation-1; i++) {
            sum_s[i]=fulladder(ain.read()[i],bin.read()[i]^ci.read(),co_[i-1],co_[i]);
        }

        sum.write(sum_s);
        co.write(co_[nBitOperation-1]);

        bool zz;
        zz = false;
        for (int i = 0; i < nBitOperation; i++) {
            zz = zz || (sum_s[i]);
        }
        zz = !(zz);
        zflag.write(zz);

        if (zflag.read()==true) { // something like this.
            cout << " [Zero Value]" ;//<< endl;
        }

        bool aa, bb, ss;
        aa = ain.read()[nBitOperation-1];
        bb = bin.read()[nBitOperation-1];
        ss = sum_s[nBitOperation-1];
        oflag.write((!aa && !bb && ss) | (aa && bb && !ss));

        if (oflag.read()==true) { // something like this.
            cout << " [Over Flow]" ;//<< endl;
        }
        cout << endl;
    }

    SC_CTOR(adder) {     
        SC_METHOD(p1);  
        sensitive << ain << bin << ci; 
    }
};
#endif
