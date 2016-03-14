#include <systemc.h>

class write_if : virtual public sc_interface
{
   public:
     virtual void write(int , int) = 0;
     
};

class read_if : virtual public sc_interface
{
   public:
     virtual void read(int, int &) = 0;
};


class channel : public sc_channel, public write_if, public read_if
{
   public:
     channel(sc_module_name name) : sc_channel(name), ocupado(false) {}

     void write(int data, int addr) {
       if (ocupado)
         wait(transac_ok);

       ocupado = true;
       
       mem[addr] = data;
       cout<<"Escreveu : "<< mem[addr]<<"em  "<< addr <<endl;
       //++ num_elements;
       ocupado = false;
       transac_ok.notify();
     }

     void read(int addr, int &rd_data){
       if (ocupado)
         wait(transac_ok);

       ocupado = true;
       rd_data = mem[addr];
       cout<<"Dado a ser lido  "<<mem[addr]<<endl;
       ocupado = false;
       transac_ok.notify();
     }
   private:
     bool ocupado;
     int mem[32];
     sc_event transac_ok;
};

class processor : public sc_module
{
   public:
     sc_port<write_if> out;
     sc_port<read_if> in;

     SC_HAS_PROCESS(processor);

     processor(sc_module_name name) : sc_module(name)
     {
       SC_THREAD(main);
     }

     void main(){
        int addr, data;
        while(true){
            
            data = 32;
            addr = 5;
            cout <<"Mandou escrever "<<data<<" em "<<addr<< endl;
            out->write(data, addr);
            
            data = 55;
            addr = 9;
            cout <<"Mandou escrever "<<data<<" em "<<addr<< endl;
            out->write(data, addr);   
            
            addr = 5;
            cout <<"Mandou ler "<<addr<< endl;
            in->read(addr, data);
            cout <<"Leu: "<< data<< endl;

            addr = 9;
            in->read(addr, data);
            cout <<"Leu: "<< data<< endl;

            break;

        }

    }
};

class test : public sc_module
{
   public:
     channel *channel_inst;
     processor *proc_inst;

     test(sc_module_name name) : sc_module(name)
     {
       channel_inst = new channel("Channel1");

       proc_inst = new processor("Processor1");
       proc_inst->out(*channel_inst);
       proc_inst->in(*channel_inst);
     }
};

int sc_main (int argc , char *argv[]) {
   test test1("Test1");
   sc_start();
   return 0;
}