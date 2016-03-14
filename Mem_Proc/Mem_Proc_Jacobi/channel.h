/*
 *  channel.h
 *  procmem
 *
 *  Created by RJ on 27/06/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

enum cmd_enum {
	READ, WRITE
};

struct token_st {
	cmd_enum cmd;
	unsigned int addr;
	int data;
};
	
class write_if : virtual public sc_interface
{
public:
	virtual void write(unsigned int addr, int data) = 0;
};

class read_if : virtual public sc_interface
{
public:
	virtual void read(unsigned int addr, int &) = 0;
};

class mem_if : virtual public sc_interface {
	public:
	virtual void transac(token_st &) = 0;
}


class channel : public sc_channel, public write_if, public read_if, public mem_if
{
	void write(unsigned int addr, int data);
	virtual void read(unsigned int addr, int &);
	virtual void transac(token_st &);

	sc_event wr_evt, rd_evt, trans_ok_evt;
};


