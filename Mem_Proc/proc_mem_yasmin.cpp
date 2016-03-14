#include <systemc.h>

class write_if : virtual public sc_interface{
   public:
        virtual void write(int addr, int data) = 0;
};

class read_if : virtual public sc_interface{
   public:
         virtual void read(int &data) = 0;
};

class proc_if : virtual public sc_interface{
    public:
        virtual void transac(int op, int addr, int data);
};

class channel : public sc_channel, public write_if, public read_if
{
   public:
   
   int mem_data[32];
   int reading_address;

    channel(sc_module_name name) : sc_channel(name) {

    }

    void write(int addr, int data) {
       mem_data[addr] = data;
    }

    void read(int &read_data){
       //int data;
       read_data = mem_data[reading_address];
       cout<<"Leu: "<<read_data<<endl;
    }

    void transac(int op, int addr, int data){
        int read_data;
        if(op == 0){
            reading_address = addr;
            read(read_data);
        }
        else if(op == 1){
            write(addr, data);
        }
    }

};

class processor : public sc_module
{
   public:
     sc_port<proc_if> out;

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
            out->transac(0, addr, data);
            
            data = 55;
            addr = 9;
            cout <<"Mandou escrever "<<data<<" em "<<addr<< endl;
            out->transac(0, addr, data);   
            
            addr = 5;
            cout <<"Mandou ler "<<addr<< endl;
            out->transac(1, addr, 0);

            addr = 9;
            cout <<"Mandou ler "<<addr<< endl;
            out->transac(1, addr, 0);

            break;

        }

    }
};

class test : public sc_module
{
   public:
     channel *chan_inst;
     processor *proc_inst;
     //consumer *cons_inst;

     test(sc_module_name name) : sc_module(name){
       
       chan_inst = new channel("Channel1");

       proc_inst = new processor("Processor1");
       proc_inst->out(*chan_inst);

     }
};

int sc_main (int argc , char *argv[]) {
   test test1("Test1");
   sc_start();
   return 0;
}