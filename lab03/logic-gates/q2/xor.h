#include "systemc.h"
#include "nand.h"
SC_MODULE(XOR)
{
  sc_in<bool> a, b;
  sc_out<bool> o;

  NAND2 n1, n2, n3, n4;

  sc_signal<bool> S1, S2, S3;

  SC_CTOR(XOR) : n1("N1"), n2("N2"), n3("N3"), n4("N4")
  {
    n1.a(a);
    n1.b(b);
    n1.o(S1);

    n2.a(a);
    n2.b(S1);
    n2.o(S2);

    n3.a(S1);
    n3.b(b);
    n3.o(S3);

    n4.a(S2);
    n4.b(S3);
    n4.o(o);

    sensitive << a << b;
  }
};