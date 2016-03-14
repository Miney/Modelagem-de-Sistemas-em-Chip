#include "mult.h"
#include <iostream>

void mult::multiplica(){
	int A, B, C;
	while(1){
		wait(5, SC_NS);
		//sleep(1);
		
		if(pode_multiplicar.read() == true){
			//cout<<"Thread multiplicador: "<<A<<" v1: "<<B<<endl;
			A = multiplicando.read();
			B = multiplicador.read();
			C = A * B;
			multiplicado = C;
			multiplicou = true;
			wait(30, SC_NS);
		}
		
		if(morrer.read() == true){
			break;
		}
	}
}

void adder::soma(){
	int A, B, C, D;
	static int i = 0;
	while(1){
		//cout<<"Thread somador"<<endl;
		//sleep(2);
		wait(10, SC_NS);
		//wait(70, SC_NS);
		if(pode_somar.read() == true){
			A = a.read();
			B = b.read();
			C = c.read();
			D = A + B + C;
			resultado[i] = D;
			somou = true;
			i++;
			wait(40, SC_NS);
		}
		
		if(morrer.read() == true){
			break;
			}
	}
}