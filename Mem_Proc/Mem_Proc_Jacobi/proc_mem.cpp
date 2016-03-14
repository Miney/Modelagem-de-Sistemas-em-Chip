#include "systemc.h"

class write_if : virtual public sc_interface{
   public:
     virtual void write(unsigned int addr, int data) = 0;
};

class read_if : virtual public sc_interface{
public:
	virtual void read(unsigned int addr, int &) = 0;
};

class channel : public sc_channel, public write_if, public read_if{
	void write(unsigned int addr, int data);
	virtual void read(unsigned int addr, int &);
	sc_event wr_event, rd_event;
};
