#ifndef CHECK_H
#define CHECK_H

#include <systemc.h>
#include <iostream>
#include <fstream>

using namespace std;
                                
SC_MODULE(check) {
    sc_in<bool> clk;
    sc_in<sc_uint<8> > avg;

    void p1() { 
        fstream data1024result("data1024.result", std::ios_base::in);
        int number_of_result;
        data1024result >> number_of_result;

        int correct = 0;
        int incorrect = 0;
        while (1) {
            cout << endl;
            wait();
            
            int avgDataResult;
            data1024result >> avgDataResult;
            
            cout << "| checker.h [avg.read() = " << avg.read() << " <--> avgDataResult = " << avgDataResult << "] --> ";
            if (avgDataResult == avg.read()) {
                correct++;
                cout << "Correct" << endl;
            }
            else {
                incorrect++;
                cout << "InCorrect" << endl;
            }

            
            number_of_result--;
            if (number_of_result == 0) {
                break;
            }



        }
        cout << "=================================================================================================================================" << endl;
        cout << "Correct Result = " << correct << endl;
        cout << "In Correct Result = " << incorrect << endl;
    }

    SC_CTOR(check) {  
        SC_THREAD(p1); 
        sensitive << clk.pos();
        dont_initialize();
    }
};
#endif
