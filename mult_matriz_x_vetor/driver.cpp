#include "driver.h"
#include <iostream>

using namespace std;

void driver::drive(){
	static int i = 0;
	int matriz[3][3];
	int vetor[3];
	
	morrer = false;
	pode_somar = false;
	pode_multiplicar = false;
	
	cout<<"Matriz : "<<endl;
	for(int x = 0; x < 3; x++){
		for(int y = 0; y < 3; y++){
			matriz[x][y] = 2;	
			cout<<"\t"<<matriz[x][y];
		
		}
		cout<<endl;
		vetor[x] = 1;
	}
	
	cout<<"Vetor: "<< vetor[0] << vetor[1] << vetor[2]<<endl;
	
	
	while(1){
		//cout<<"Thread driver"<<endl;	
		a = matriz[i][0];
		b = matriz[i][1];
		c = matriz[i][2];
		v1 = vetor[0];
		v2 = vetor[1];
		v3 = vetor[2];
		pode_multiplicar = true;
		
		if(multiplicou[0].read() == true && multiplicou[1].read() == true && multiplicou[2].read() == true){
			//cout<<"Entrou no if 1"<<endl;
			//sleep(1);
			pode_multiplicar = false;
			pode_somar = true;
			wait(20, SC_NS);
		}
		if(somou.read() == true){
			//cout<<"Entrou no if 2"<<endl;
			//sleep(1);
			pode_somar = false;
			i++;
			//wait(20, SC_NS);
		}
		
		if(i>3){
			morrer = true;
			//wait(30, SC_NS);
			break;
		}
		//wait(10, SC_NS);
		//sleep(1);
		wait(30, SC_NS);
	}
}

void monitor::monitorar(){
	while(1){
		//cout<<"Thread monitor"<<endl;
		if(morrer.read() == true){
			cout<<"Linha multiplicada: "<< a.read()<< b.read() << c.read() <<endl;
			break;
		}
		wait(60, SC_NS);
	}
}
