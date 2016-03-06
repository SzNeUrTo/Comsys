#include <systemc.h>
SC_MODULE(INV)
{
  sc_in<bool> a;  // input pin a
  sc_out<bool> o;  // input pin a
  SC_CTOR(INV)    // the ctor
    {
      SC_METHOD(or_process);
      sensitive << a;
    }
  void or_process() {
    o.write( !a.read() );
  }
};

SC_MODULE(NOR2)
{
  sc_in<bool> a;  // input pin a
  sc_in<bool> b;  // input pin a
  sc_out<bool> o;  // input pin a
  SC_CTOR(NOR2)    // the ctor
    {
      SC_METHOD(or_process);
      sensitive << a << b;
    }
  void or_process() {
    o.write( !(a.read() || b.read()) );
  }
};