//------------------------------------------------------------------
// 4-bits adder checker module
// 
// SystemC for VHDL engineers
// (c)www.ht-lab.com
//------------------------------------------------------------------
#ifndef CHECK_H
#define CHECK_H

#include <systemc.h>

#include <iostream>
using namespace std;       
                                
SC_MODULE(check) {
    sc_in<bool> clk;
    sc_in<sc_int<32> > ain, bin;
    sc_in<bool> ci;
    sc_in<sc_int<32> > sum;
    sc_in<bool> co;

    sc_int<33> sumc;

    void pc1() {    
        if (ci == false) {
            sumc=ain.read() + bin.read() + ci.read();
            cout << "fulladder " << ain.read() << " + " << bin.read() << " = " << sum.read();//+co.read()*16; 
        }
        else {
            sumc=ain.read() - bin.read();
            cout << "fulladder " << ain.read() << " - " << bin.read() << " = " << sum.read();//+co.read()*16; 
        } 
        if (sumc==sum.read()) {
            cout << " Passed" ;//<< endl;
        } else {
            cout << " Failed, expected sum=" << sumc << " co=" << sumc[32];//<< endl;
        }
    }

    SC_CTOR(check) {     
        SC_METHOD(pc1);                     
        sensitive << clk.pos();
        dont_initialize();
    }
};
#endif
