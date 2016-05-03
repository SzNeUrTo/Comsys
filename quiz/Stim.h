#ifndef STIM_H
#define STIM_H

#include <systemc.h>
#include <iostream>
#include <fstream>
                             
using namespace std;

SC_MODULE(stim) {
    sc_in<bool> clk;
    sc_out<sc_uint<8> > A0, A1, A2, A3;


    void setTestCase(int a0, int a1, int a2, int a3) {
        A0.write(a0);
        A1.write(a1);
        A2.write(a2);
        A3.write(a3);
        wait(); 
    }

    void ps1() {    
        wait();

        fstream data1024("data1024", std::ios_base::in);

        int number_of_lines;
        data1024 >> number_of_lines;

        for (int i = 0; i < number_of_lines / 4; i++) {
            int a0, a1, a2, a3;
            data1024 >> a0;
            data1024 >> a1;
            data1024 >> a2;
            data1024 >> a3;
            setTestCase(a0, a1, a2, a3);
        }

        sc_stop();
    }

    SC_CTOR(stim) {  
        SC_THREAD(ps1);
        sensitive << clk.pos();
    }
};
#endif
