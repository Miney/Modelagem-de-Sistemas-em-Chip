#include "systemc.h"
#include <iostream>
#include "fand.h"

int sc_main (int argc, char * argv[]) {
    // insert code here...
    /*std::cout << "Hello SystemC!\n";
	
	// elaboracao do circuito
	
	sc_signal<bool> a, b, z;
	
	fand f("f");
	
	f.a(a);
	f.b(b);
	f.z(z);
	
	a = true; b = false;	
    sc_start(1.0, SC_NS);	
	
    cout << sc_time_stamp() << " res = " << z << endl;
	
	a = true; b = true;	
    sc_start(1.0, SC_NS);	
	
    cout << sc_time_stamp() << " res = " << z << endl;
	
	// test01
	//sc_bit flag(SC_LOGIC_1);
	sc_bv<5> positions = "01101";
	cout << positions.range (3,1) << "\n";
	
*/
	//test02
	sc_lv<4> aa, bb; 
	aa = "01zx";
	bb = "1111";
	cout << (aa & bb) << "\n";
	return 0;
}
