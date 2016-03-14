#include "systemc.h"

SC_MODULE(BancoRegistradores){
	///variaveis

	//addreg1: endereco do reg para ser lido em data1, addreg2 em data2
	//wadd : entrada de endereco para escrita	
	sc_in<sc_uint<5> > addreg1, addreg2, wadd;

	//entrada para indormacao a ser escrita em wadd	
	sc_in<unsigned> wdata;	

	//wreg e o sinal de escrita. Se acionado, wadd recebe wdata na subida do relogio.	
	sc_in<bool> wreg, clk;

	//saidas com os registradores lidos em addreg1 e addreg2
	sc_out<unsigned> data1, data2;

	//array de registradores de 32 posicoes
	sc_uint<32> registradores[32];
	
	//criar um booleano para startar o metodo de mostrar o registrador

	///metodos
	
	void proc();
	//void show_reg(sc_uint<5>);

	///construtor
	
	SC_CTOR(BancoRegistradores){
		SC_METHOD (proc);
		//sensivel so ao wreg ou ao clk tb?
		sensitive << wreg << clk;	
	}
};

