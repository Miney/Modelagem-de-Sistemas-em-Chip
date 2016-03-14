#include "systemc.h"
#include <iostream>

using namespace std;

SC_MODULE (ulamips) {
	sc_in<sc_uint<3> > opcode;
	sc_in<int> A, B;
	sc_out<int> Z;
	sc_out<bool> zero;
	
	void exec();

	SC_CTOR(ulamips) {
		SC_METHOD (exec);
		sensitive << A << B << opcode;
	}
};

void ulamips::exec() {
	sc_uint<SIZE> x0, x1;
	x0 = A.read();
	x1 = B.read();

	switch(opcode){
		case adicao:
			Z = x0 + x1; 
			break;
		case subtracao:
			Z = x0 - x1; 
			break; 
		case multiplicacao:
			Z = x0 * x1; 
			break;
		case divisao:
			Z = x0 / x1; 
			break;
		case notA:
			Z = ~x0; 
			break;
		case xor_AB:
			 
			break;		
		case bypassA::
			Z = x0; 
			break;
		case slt:
			if(A<B){
				Z = 1;			
			}
			else{
				Z = 0;
			}			 
			break;

	}
}
 
int sc_main (int argc, char * argv[]) {
	sc_signal<sc_uint<SIZE> x, y, z;
	sc_signal<OpType> operacao;
	Ula ULA("Ula");
	ULA.X(x);
	ULA.Y(y);
	ULA.Z(z);

	///fazer os blocos de teste aqui 
}
