#include "systemc.h"
SC_MODULE(NAND2)          // declare nand2 sc_module
{
  sc_in<bool> a, b;       // input signal ports
  sc_out<bool> o;         // output signal ports

  void do_nand2()         // a C++ function
  {
    o.write( !(a.read() && b.read()) );
  }

  SC_CTOR(NAND2)          // constructor for nand2
  {
    SC_METHOD(do_nand2);  // register do_nand2 with kernel
    sensitive << a << b;  // sensitivity list
  }
};

