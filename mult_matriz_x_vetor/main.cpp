#include "driver.h"
#include "mult.h"

int sc_main (int argc, char * argv[]) {
	sc_signal<int> a, b, c, v1, v2, v3, a_adder, b_adder, c_adder;
	sc_signal<int> a_final, b_final, c_final;
	sc_signal<bool>pode_somar, pode_multiplicar, somou, multiplicou[3], morrer;
	
	driver DRIVER("DRIVER");
	DRIVER.a(a);
	DRIVER.b(b);
	DRIVER.c(c);	
	DRIVER.v1(v1);
	DRIVER.v2(v2);
	DRIVER.v3(v3);
	DRIVER.multiplicou[0](multiplicou[0]);
	DRIVER.multiplicou[1](multiplicou[1]);
	DRIVER.multiplicou[2](multiplicou[2]);
	DRIVER.somou(somou);
	DRIVER.pode_somar(pode_somar);
	DRIVER.pode_multiplicar(pode_multiplicar);
	DRIVER.morrer(morrer);
	
	monitor MONITOR("MONITOR");
	MONITOR.a(a_final);
	MONITOR.b(b_final);
	MONITOR.c(c_final);
	MONITOR.morrer(morrer);
	//MONITOR.
	
	mult MULT_1("MULT_1");
	MULT_1.multiplicando(a);
	MULT_1.multiplicador(v1);
	MULT_1.multiplicado(a_adder);
	MULT_1.multiplicou(multiplicou[0]);
	MULT_1.pode_multiplicar(pode_multiplicar);
	MULT_1.morrer(morrer);
	
	mult MULT_2("MULT_2");
	MULT_2.multiplicando(b);
	MULT_2.multiplicador(v2);
	MULT_2.multiplicado(b_adder);
	MULT_2.multiplicou(multiplicou[1]);
	MULT_2.pode_multiplicar(pode_multiplicar);
	MULT_2.morrer(morrer);
	
	mult MULT_3("MULT_3");
	MULT_3.multiplicando(c);
	MULT_3.multiplicador(v3);
	MULT_3.multiplicado(c_adder);
	MULT_3.multiplicou(multiplicou[2]);
	MULT_3.pode_multiplicar(pode_multiplicar);
	MULT_3.morrer(morrer);
	
	adder ADDER("ADDER");
	ADDER.a(a_adder);
	ADDER.b(b_adder);
	ADDER.c(c_adder);
	ADDER.resultado[0](a_final);
	ADDER.resultado[1](b_final);
	ADDER.resultado[2](c_final);
	ADDER.pode_somar(pode_somar);
	ADDER.somou(somou);
	ADDER.morrer(morrer);
	
	sc_start();
}