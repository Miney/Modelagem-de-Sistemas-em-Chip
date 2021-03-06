#include "systemc.h"
#include <iostream>

using namespace std;


///Declaracao dos 3 modulos : driver, monitor e multiplicador

SC_MODULE (driver) {
    sc_out<sc_uint<8> > a, b;
    sc_out<bool> clock, start;
    
    void drive();
    SC_CTOR(driver) {
        SC_THREAD(drive);
    }
};

SC_MODULE (monitor) {
    sc_in<sc_uint<16> > res;
    sc_in<bool> done, clock;
    
    void monitorar ();

    SC_CTOR(monitor) {
        SC_METHOD (monitorar);
        sensitive << res << done << clock;
    }
};

SC_MODULE (multiplicador) {
	sc_in<sc_uint<8> > a, b;
	sc_in<bool> clock, start;
	sc_out<sc_uint<16> > res;
	sc_out<bool> done;

	sc_uint<8> aux_b;
	int contador_ciclos;

	
	
	void exec();

	SC_CTOR(multiplicador) {
		SC_METHOD (exec);
		sensitive << a << b << start << clock.pos();
	}
};

///especificacao das funcoes de cada um
void driver::drive(){
	int	max_ciclos = 8, count_ciclos = 0;
	a = 1;
	b = 1;
	start = true;

	while(1){
		clock = 0;
		wait(10, SC_NS);
		clock = 1;
		wait(10, SC_NS);
		count_ciclos++;
		if( count_ciclos >= max_ciclos ){
			break;		
		}	
	}
}

void monitor::monitorar(){
    cout << "Em: " << sc_time_stamp()<< "\tres: " << res << "\tdone: " << 		done << "\tclock: " << clock << endl;
}

void multiplicador::exec() {
	sc_uint<8> A, B;
	sc_uint<16> RES;
	
	sc_uint<8> aux;	
	
	A = a.read();
	RES = res.read();

	if(contador_ciclos != 1){
		B = aux_b;
	}
	
	else{
		B= b.read();
		RES = (RES.range(15,8), B);
	}

	if(contador_ciclos <= 8){
		done = false;
		if(B[0] == 1){
			aux = RES.range(15,8) + A;
			RES = (aux, RES(7,0));
		}
		
		RES = RES >>1;
		aux_b = B >> 1;
		contador_ciclos++;
	}
	
	else{
		contador_ciclos = 0;
		done = true;
	}

	res = RES;
}

///funcao main

int sc_main (int argc, char * argv[]) {
	sc_signal<sc_uint <8> > a, b;
	sc_signal<bool> clock, start;
	sc_signal<sc_uint <16> > res;
	sc_signal<bool> done;

	multiplicador MULT("MULT");
	MULT.a(a);
	MULT.b(b);
	MULT.clock(clock);
	MULT.start(start);
	MULT.res(res);
	MULT.done(done);
	
	driver DRIVER("DRIVER");
    
	DRIVER.a(a);
	DRIVER.b(b);
	DRIVER.clock(clock);
	DRIVER.start(start);

	monitor MONITOR("MONITOR");
	MONITOR.clock(clock);
	MONITOR.res(res);
	MONITOR.done(done);
    
	sc_start();

	return 0;
}
