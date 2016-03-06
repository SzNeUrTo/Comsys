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
    int nBitOperation=4;
    sc_in<sc_int<4> > ain, bin;
    sc_in<bool> ci;
    sc_out<sc_int<4> > sum;
    sc_out<bool> co;

    // bool co0, co1, co2, co3;
    bool c0/*ci*/, c1, c2, c3, c4;
    bool g[4];
    bool p[4];
    sc_int<4> sum_s;

    sc_out<bool> zflag, oflag;

    // 1-bit ripple carry fulladder, note the cof reference bool&
    bool fulladder(bool a, bool b, bool cif, bool& cof, bool& gof, bool& pof) {
        // bool sumr;
        gof = a & b;
        pof = a | b;
        cof = gof | (pof & cif);
        bool sumr = a ^ b ^ cif;
        return sumr;    
    }

    void p1() { 
        c0 = ci.read();
        sum_s[0]=fulladder (ain.read()[0], bin.read()[0] ^ c0, c0, c1, g[0], p[0]);
        sum_s[1]=fulladder (ain.read()[1], bin.read()[1] ^ c0, c1, c2, g[1], p[1]);
        sum_s[2]=fulladder (ain.read()[2], bin.read()[2] ^ c0, c2, c3, g[2], p[2]);
        sum_s[3]=fulladder (ain.read()[3], bin.read()[3] ^ c0, c3, c4, g[3], p[3]);


        sum.write(sum_s);
        co.write(c4);

        
        zflag.write(!(sum_s[0] || sum_s[1] || sum_s[2] || sum_s[3] || c4));


        bool aa, bb, ss;
        aa = ain.read()[nBitOperation-1];
        bb = bin.read()[nBitOperation-1];
        ss = sum_s[nBitOperation-1];
        oflag.write((!aa && !bb && ss) | (aa && bb && !ss));


        if (zflag.read()==true) {
            cout << " Zero Value" ;
        }
        if (oflag.read()==true) {
            cout << " Over Flow" ;
        }
        cout << endl;
    }

    SC_CTOR(adder) {     
        SC_METHOD(p1);  
        sensitive << ain << bin << ci; 
    }
};
#endif
