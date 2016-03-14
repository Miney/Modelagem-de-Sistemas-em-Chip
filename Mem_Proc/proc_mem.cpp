#include "systemc.h"

enum cmd_enum {
	READ, WRITE
};

struct token_st {
	cmd_enum cmd;
	unsigned int addr;
	int data;
};

/*	Interfaces	*/

class write_if : virtual public sc_interface{
   public:
     virtual void write(unsigned int addr, int data) = 0;
};

class read_if : virtual public sc_interface{
public:
	virtual void read(int &) = 0;
};

class proc_if : virtual public sc_interface{
public:
	virtual void transac(int op, unsigned int addr, int data) = 0;
};

/*	Memoria	*/
SC_MODULE(memory){
public:
	sc_in<int> op;
	
	sc_port<write_if> wr_p;
	sc_port<read_if> rd_p;
	int mem_data[32];
	

	void read(){
		unsigned int addr;

		if(op == 0){
			wr_p->read(addr);
			
			if(addr >= 0 && addr <= sizeof(mem_data)){
				wr_p->write(mem_data[addr]);
				trans_ok_event.notify();
			else{
				cout << "Invalid memory address"<< endl;
				wr_p->write(0);
				trans_ok_event.notify();
			}
		}
	}

	void write(){
		if(op == 1){
			in->read(addr);
			in->read(data);

			if(addr >= 0 && addr <= sizeof(mem_data)){
				mem_data[addr] = data;
				trans_ok_event.notify();
			}
			else{
				cout << "Invalid memory address"<< endl;
				trans_ok_event.notify();
			}
		}
	}


	SC_CTOR(memory){
		SC_METHOD(read);
		sensitive<<op;
		SC_METHOD(write);
		sensitive<<op;
	}

};

/*	Processador	  */

SC_MODULE(processor){
public:
	sc_port<proc_if> p_if;

	

	void main(){
		int add, data;
		while(true){
			
			data = 32;
			addr = 5;
			cout <<"Mandou escrever "<<data<<" em "<<addr<< endl;
			p_if->transac(0, addr, data);
			
			data = 55;
			addr = 9;
			cout <<"Mandou escrever "<<data<<" em "<<addr<< endl;
			p_if->transac(0, addr, data);	
			
			addr = 5;
			cout <<"Mandou ler "<<addr<< endl;
			p_if->transac(1, addr);

			addr = 9;
			cout <<"Mandou ler "<<addr<< endl;
			p_if->transac(1, addr);

			break;

		}

	}

	SC_CTOR(processor){
		SC_THREAD(main);
	}
};

/* Channel */

class channel : public sc_channel, public write_if, public read_if, public proc_if{
	bool busy;
	public:
		sc_event wr_event, rd_event, trans_ok_event;
		unsigned int addr;

	void transac(int op, unsigned int addr, int data){
		if(busy){
			wait(trans_ok_event);
		}
		else{
			if(op == 0){
				busy = true;
				read(addr);
			}
			else if(op == 1){
				busy = true;
				write(addr, data);
			}
		}
	}

	void write(unsigned int addr, int data){
		wr_event.notify();
		cout<"Info inserida na memoria"<<endl;	
		wait(trans_ok_event);
		busy = false;		
	}
	
	void read(int addr){
		rd_event.notify();
		wait(trans_ok_event);
		busy = false;
	}

};

class test : public sc_module{
public:
		channel *channel_inst;
		processor *proc_inst;
		memory *mem_inst;

		test(sc_module_name name) : sc_module(name){
			channel_inst = new channel("channel_1");
			
			proc_inst = new processor("processor_1");
			proc_inst->p_if(*channel_inst);

			mem_inst = new memory("memory_1");
			mem_inst->wr_p(*channel_inst);
			mem_inst->rd_p(*channel_inst);


		}


};

int sc_main (int argc, char *argv[]){
	test test1("test");
	sc_start();
	return 0;
}
