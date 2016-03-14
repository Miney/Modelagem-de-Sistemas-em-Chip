#include "systemc.h"

SC_MODULE(driver){
	sc_out<int> a, b, c;
	sc_in<bool> multiplicou[3], somou;
	sc_out<int> v1, v2, v3;
	sc_out<bool> pode_somar, pode_multiplicar, morrer;
	
	void drive();
	
	SC_CTOR(driver){
		SC_THREAD(drive);
	}	
};
	
SC_MODULE(monitor){
	sc_in<int> a, b, c;
	sc_in<bool> morrer;
	
	void monitorar();
	
	SC_CTOR(monitor){
		SC_THREAD(monitorar);
		}
		
};
	
	