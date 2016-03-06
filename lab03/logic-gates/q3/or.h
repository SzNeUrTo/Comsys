#include <systemc.h>
#include "inv.h"
SC_MODULE(OR2)
{
    sc_in<bool> a;  // input pin a
    sc_in<bool> b;  // input pin b
    sc_out<bool> o; // output pin o
    SC_CTOR(OR2)    // the ctor
    {
        SC_METHOD(or_process);
        sensitive << a << b;
    }
    void or_process() {
        o.write( a.read() || b.read() );
    }
};

SC_MODULE(OR3)
{
    sc_in<bool> a;  // input pin a
    sc_in<bool> b;  // input pin b
    sc_in<bool> c;
    sc_out<bool> o; // output pin o
    SC_CTOR(OR3)    // the ctor
    {
        SC_METHOD(or_process);
        sensitive << a << b << c;
    }
    void or_process() {
        o.write( a.read() || b.read() || c.read() );
    }
};

SC_MODULE(NOR2)
{
    sc_in<bool> a;  // input pin a
    sc_in<bool> b;  // input pin b
    sc_out<bool> o; // output pin o

    sc_signal<bool> or_v;

    OR2 orr;
    INV invv;

    SC_CTOR(NOR2) : orr("orr"), invv("invv")
    {
        SC_METHOD(nor_process);
        sensitive << a << b;
        orr.a(a); orr.b(b); orr.o(or_v);
        invv.a(or_v); invv.o(o);
    }
    void nor_process() {
    }
};
