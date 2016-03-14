/*
Yasmin Pimentel 11/0144341
Em 28/05/2013
*/

#include "BReg-RISC.h"
#include <iostream>

using namespace std;

void BancoRegistradores::le_enderecos(){
	if(Reg1.read() == 0){
		DataA.write(0);
	}
	else{		
		DataA.write(Banco[Reg1.read()]);		
	}
	
	if(Reg2.read() == 0){
		DataB.write(0);	
	}	
	else{				
		DataB.write(Banco[Reg2.read()]);
	}	
}

void BancoRegistradores::escreve(){	
	if(WReg == 1){	
		Banco[WriteReg.read()].write(WData.read());	
		Banco[0].write(0);				
	}	
}

