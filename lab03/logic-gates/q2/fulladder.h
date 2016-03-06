#include <systemc.h>
#include "xor.h"
#include "and.h"
#include "or.h"



SC_MODULE(FULLADDER)
{
  sc_in<bool> cin;  // input pin a
  sc_in<bool> a;  // input pin a
  sc_in<bool> b;  // input pin b

  sc_out<bool> sum; // output pin o
  sc_out<bool> cout; // output pin o
  
  XOR xor1, xor2;
  AND2 and3, and4;
  OR2 or5;
  sc_signal<bool> s1, s2, s3;

  SC_CTOR(FULLADDER) : xor1("n1"), xor2("n2"), and3("n3"), and4("n4"), or5("n5")
  {
      // SC_METHOD(fulladder_process);
      xor1.a(a);
      xor1.b(b);
      xor1.o(s1);

      xor2.a(s1);
      xor2.b(cin);
      xor2.o(sum);

      and3.a(s1);
      and3.b(cin);
      and3.o(s2);

      and4.a(a);
      and4.b(b);
      and4.o(s3);

      or5.a(s2);
      or5.b(s3);
      or5.o(cout);

      sensitive << a << b << cin;

  }
};
