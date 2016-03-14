#include <iostream>
#include "BReg.h"

using namespace std;

SC_MODULE (driver){

	sc_out<bool> wreg, clk;

	void drive();

	SC_CTOR(driver){
		SC_THREAD(drive);
	}	
};

void driver::drive(){
	int count_ciclos = 0;	
	
	wreg = true;	

	while(1){
		clk = 0;
		wait(10, SC_NS);
		clk = 1;
		wait(10, SC_NS);
		count_ciclos++;
		if(count_ciclos == 4){
			break;		
		}		
	}
}

SC_MODULE (monitor){
	sc_in< sc_uint<5> > addreg1, addreg2, wadd;
	sc_in<unsigned> wdata, data1, data2;	

	sc_in<bool> wreg, clk;
	
	void monitorar();

	SC_CTOR(monitor){
		SC_METHOD(monitorar);
		sensitive << wreg << clk;
	}
};

void monitor::monitorar(){
	cout<<"Em: "<< sc_time_stamp()<< "\tClk: "<< clk << endl;
	
	//cout<<"registrador " << wadd << ":" << registradores[wadd] << "\twdata: "<< wdata<< endl;
	
	///starta a variavel do metodo do banco pra 
	
	//cout<<"addreg1: "<< registradores[addreg1] <<"\tdata1: "<< data1 << endl;	
	//cout<<"addreg2: "<< registradores[addreg2] <<"\tdata2: "<< data2 << endl;
	
	//cout<<"registrador 0: "<< registradores[0] << endl;
	
}


///funcao main

int sc_main (int argc, char* argv[]){
	sc_signal<sc_uint <5> > addreg1, addreg2, wadd;
	sc_signal<unsigned> wdata;
	sc_signal<bool> wreg, clk;
	sc_signal<unsigned> data1, data2;

	BancoRegistradores BREG("BREG");
	
	BREG.addreg1(addreg1);
	BREG.addreg2(addreg2);
	BREG.wadd(wadd);
	BREG.wdata(wdata);
	BREG.wreg(wreg);
	BREG.clk(clk);
	BREG.data1(data1);
	BREG.data2(data2);

	driver DRIVER("DRIVER");
	
	DRIVER.wreg(wreg);
	DRIVER.clk(clk);
	
	monitor MONITOR("MONITOR");
	
	MONITOR.addreg1(addreg1);
	MONITOR.addreg2(addreg2);
	MONITOR.wadd(wadd);
	MONITOR.wdata(wdata);
	MONITOR.data1(data1);
	MONITOR.data2(data2);	
	MONITOR.wreg(wreg);
	MONITOR.clk(clk);
	

	sc_start();

	return 0;
}
