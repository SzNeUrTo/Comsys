#include <systemc.h>
#include "FA.h"

SC_MODULE(CON)
{
    sc_in<bool> n0;  
    sc_in<bool> n1;  
    sc_uint<2> t;
    sc_out<sc_uint<2> > o;

    SC_CTOR(CON)
    {
        SC_METHOD(adder_process);
        sensitive << n0 << n1;
    }
    void adder_process() {
        t[0] = n0.read();
        t[1] = n1.read();
        o.write(t);
    }
};

int sc_main(int argc, char *argv[])
{
    sc_uint<2> A;
    sc_uint<2> B;
    sc_signal<sc_uint<2> > S;
    sc_signal<bool> C_OUT;
    sc_signal<bool> F;
    sc_signal<bool> a1,a0,b1,b0,s1,s0;
    sc_signal<bool> c;

    FA1 fa1("fa1"), fa2("fa2");
    fa1.a(a0); fa1.b(b0); fa1.c_in(F); fa1.s(s0); fa1.c_out(c);
    fa2.a(a1); fa2.b(b1); fa2.c_in(c); fa2.s(s1); fa2.c_out(C_OUT);   
    CON con("con");
    con.n0(s0); con.n1(s1); con.o(S);

    sc_initialize();
    sc_trace_file *tf = sc_create_vcd_trace_file("trace");

    sc_trace(tf, A, "A");  
    sc_trace(tf, B, "B");
    sc_trace(tf, S, "SUM");
    sc_trace(tf, C_OUT, "C_OUT");

    A = "00";
    B = "00";
    a0 = A[0]==0?false:true; a1 = A[1]==0?false:true;
    b0 = B[0]==0?false:true; b1 = B[1]==0?false:true;
    F = 0;
    cout << "OK";
    sc_start(10, SC_PS);        
    for ( int i = 0 ; i <= 16 ; i++ )
    {
        A[1] = ((i & 0x8) != 0);
        A[0] = ((i & 0x4) != 0);
        B[1] = ((i & 0x2) != 0);
        B[0] = ((i & 0x1) != 0);
        a0 = A[0]==0?false:true; a1 = A[1]==0?false:true;
        b0 = B[0]==0?false:true; b1 = B[1]==0?false:true;
        sc_start(10, SC_PS);        
    }

    sc_close_vcd_trace_file(tf);    

    return 0;
}
