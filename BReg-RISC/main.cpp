#include <iostream>
#include "BReg-RISC.h"

using namespace std;

SC_MODULE (driver){
	sc_out<bool> WReg, clock;
	sc_out<sc_uint<4> > Reg1, Reg2, WriteReg;
	sc_out< sc_uint<16> > WData;
	sc_in<sc_uint<16> >DataA, DataB;
	void drive();
	
	SC_CTOR(driver){
		SC_THREAD(drive);
	}
};

void driver::drive(){
	int count_ciclos = 0;	
	
	WReg = true;	
	WData = 37;
	WriteReg = 2;

	while(1){
		clock = 0;
		wait(10, SC_NS);
		clock = 1;
		wait(10, SC_NS);
		count_ciclos++;
		if(count_ciclos == 2){
			WData = 22;		
			WriteReg = 8;
		}
		if(count_ciclos == 3){
			WReg = true;
		}
		if(count_ciclos == 4){
			WData = 37;
			WriteReg = 2;
		}
		if(count_ciclos == 5){
			Reg1 = 2;
			Reg2 = 8;		
		}
		if(count_ciclos == 6){
			break;		
		}		
	}
	
	Reg1 = 2;
	Reg2 = 8;
}

SC_MODULE(monitor){
	sc_in<sc_uint<4> > Reg1, Reg2, WriteReg;
	sc_in< sc_uint<16> > WData;
	sc_in<bool> WReg, clock;

	sc_in<sc_uint<16> > DataA, DataB;

	sc_in<sc_uint<16> >Banco[16];

	void monitorar();

	SC_CTOR(monitor){
		SC_METHOD(monitorar);
		sensitive << WReg << clock << Reg1 << Reg2;
	}
};

void monitor::monitorar(){
	sc_uint<4> aux;	

	cout<<"Em: "<< sc_time_stamp()<< "\tClk: "<< clock << endl;
	aux = Reg1.read();
	cout<<"registrador Reg1 [" << Reg1 << "]:" << Banco[aux] << " Saida A : " << DataA.read() << endl;
	aux = Reg2.read();
	cout<<"registrador Reg2 [" << Reg2 << "]:" << Banco[aux] << " Saida B : " << DataB.read() << endl;
	aux = WriteReg.read();
	cout<<"registrador destino [" << WriteReg << "]:" << Banco[aux] << " Valor a ser escrito :" << WData << endl;
	cout<<"registrador 0: "<< Banco[0] << endl;
}


int sc_main (int argc, char* argv[]){
	int i;	
	
	sc_signal<bool> WReg, clock;
	sc_signal<sc_uint<4> > Reg1, Reg2, WriteReg;     
	sc_signal<sc_uint<16> > WData;
	sc_signal<sc_uint<16> > DataA, DataB;    
	sc_signal<sc_uint<16> > Banco[16];    

	BancoRegistradores BREG("BREG");
	BREG.WReg(WReg);
	BREG.clock(clock);
	BREG.Reg1(Reg1);
	BREG.Reg2(Reg2);
	BREG.WData(WData);
	BREG.DataA(DataA);
	BREG.DataB(DataB);
	BREG.WriteReg(WriteReg);
	
	for(i=0; i<16; i++){
		BREG.Banco[i](Banco[i]);
	} 	

	driver DRIVER("DRIVER");
	DRIVER.WReg(WReg);
	DRIVER.clock(clock);
	DRIVER.Reg1(Reg1);
	DRIVER.Reg2(Reg2);
	DRIVER.WriteReg(WriteReg);
	DRIVER.WData(WData);
	DRIVER.DataA(DataA);
	DRIVER.DataB(DataB);


	monitor MONITOR("MONITOR");
	MONITOR.WReg(WReg);
	MONITOR.clock(clock);
	MONITOR.Reg1(Reg1);
	MONITOR.Reg2(Reg2);
	MONITOR.WData(WData);
	MONITOR.DataA(DataA);
	MONITOR.DataB(DataB);
	MONITOR.WriteReg(WriteReg);
	for(i=0;i<16;i++){
		MONITOR.Banco[i](Banco[i]);
	}
	
	sc_start();
	return 0;

}
