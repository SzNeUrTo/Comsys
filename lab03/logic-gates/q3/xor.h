#include <systemc.h>
#include "or.h"
#include "and.h"

SC_MODULE(XOR2)
{
    sc_in<bool> a;  // input pin a
    sc_in<bool> b;  // input pin b
    sc_out<bool> o; // output pin o

    sc_signal<bool> na, nb, t1, t2;

    INV inva, invb;
    AND2 and1, and2;
    OR2 or3;

    SC_CTOR(XOR2) : inva("inva"), invb("invb"), and1("and1"), and2("and2"), or3("or3")
    {
        SC_METHOD(xor_process);
        sensitive << a << b;
        inva.a(a); inva.o(na);
        invb.a(b); invb.o(nb);
        and1.a(a); and1.b(nb); and1.o(t1);
        and2.a(na); and2.b(b); and2.o(t2);
        or3.a(t1); or3.b(t2); or3.o(o);
    }  
    void xor_process() {
    }
};
