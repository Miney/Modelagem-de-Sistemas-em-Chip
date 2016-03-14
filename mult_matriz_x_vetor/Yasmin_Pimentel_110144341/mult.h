#include "systemc.h"

SC_MODULE(mult){
	sc_in<bool> pode_multiplicar, morrer;
	sc_in<int> multiplicando;
	sc_in<int> multiplicador;
	sc_out<int> multiplicado;
	sc_out<bool> multiplicou;

	void multiplica();
	
	SC_CTOR(mult){
		SC_THREAD(multiplica);
		
	}
	
};

SC_MODULE(adder){
	sc_in<bool> pode_somar, morrer;
	sc_in<int> a, b, c;
	sc_out<int> resultado[3];
	sc_out<bool> somou;
	
	void soma();
	
	SC_CTOR(adder){
		SC_THREAD(soma);
	}
	
};
	