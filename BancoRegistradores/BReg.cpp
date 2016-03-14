#include "BReg.h"
#include "iostream"

using namespace std;

void BancoRegistradores::proc(){
	sc_uint<5> m_addreg1, m_addreg2, m_wadd;
	unsigned m_wdata;
	
	m_addreg1 = addreg1.read();
	m_addreg2 = addreg2.read();
	m_wadd = wadd.read();
	
	if( m_addreg1 < 32 && m_addreg1 >= 0 &&
		m_addreg2 < 32 && m_addreg2 >= 0 &&
		m_wadd < 32 && m_wadd >= 0){

			m_wdata = wdata.read();

			data1 << registradores[m_addreg1];
			data2 << registradores[m_addreg2];

			registradores[0] = 0;
	
			if(m_wadd != 0 && clk == 1){
				registradores[m_wadd] = m_wdata;
			}
	}
}

/*void BancoRegistradores::show_reg(sc_uint<5> registrador){
    	cout<<"Registrador ["<< registrador <<"]" <<":\t" << registradores[registrador] << endl;
	
	//cout<<"addreg2: "<< registradores[addreg2] <<"\tdata2: "<< data2 << endl;

}*/



