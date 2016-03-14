/*
 *  fand.h
 *  fand
 *
 *  Created by Ricardo Jacobi on 27/10/09.
 *  Copyright 2009 Universidade de Brasilia. All rights reserved.
 *
 */

#include "systemc.h"

using namespace std;

SC_MODULE (fand) {
	sc_in<bool> a, b;
	sc_out<bool> z;
	
	void exec();

	SC_CTOR(fand) {
		SC_METHOD (exec);
		 sensitive << a << b;
	}
};
		
		
	