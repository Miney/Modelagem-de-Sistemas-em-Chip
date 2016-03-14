/*
Por Yasmin Pimentel - 11/0144341
Em 21/05/2013
*/
#include "systemc.h"

SC_MODULE(BancoRegistradores){
	sc_in<bool> WReg, clock; //variavel de controle. Em 1 o registrador selecionado no banco eh atualizado com o valor de wdata
	sc_in<sc_uint<4> > Reg1, Reg2, WriteReg; // enderecos dos registradores para leitura e o endereco para escrita
	sc_in<sc_uint<16> > WData; //dados de escrita para o registrador
	sc_out<sc_uint<16> > DataA, DataB; //saidas A e B

	sc_out<sc_uint<16> >Banco[16];

	void le_enderecos();
	void escreve();

	SC_CTOR(BancoRegistradores){
		SC_METHOD(le_enderecos);		
		sensitive << Reg1 << Reg2;
		SC_METHOD(escreve);
		sensitive << clock.pos();	
	}
};

