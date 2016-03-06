#include <systemc.h>
#include "xor.h"

SC_MODULE(FA1)
{
    sc_in<bool> a;  
    sc_in<bool> b;  
    sc_in<bool> c_in;
    sc_out<bool> s;
    sc_out<bool> c_out; 

    sc_signal<bool> t1, t2, t3;

    XOR2 xor1, xor2;
    AND2 and3, and4;
    OR2 or5;

    SC_CTOR(FA1)
    : xor1("xor1"), xor2("xor2"), and3("and3"), and4("and4"), or5("or5")
    {
        SC_METHOD(adder_process);
        sensitive << a << b << c_in;
        xor1.a(a); xor1.b(b); xor1.o(t1);
        xor2.a(t1); xor2.b(c_in); xor2.o(s);
        and3.a(a); and3.b(b); and3.o(t2);
        and4.a(c_in); and4.b(t1); and4.o(t3);
        or5.a(t2); or5.b(t3); or5.o(c_out);
    }
    void adder_process() {
    }
};
