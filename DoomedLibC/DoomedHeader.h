#ifndef DOOMED_HGUARD
	
	#define DOOMED_HGUARD

	#include <iostream>
	#include <string>

	#define DLCDEF(a,b) typedef a b;
	#define DLCTDEF(a,b,c,d) using DLC_ ## a = a<d>; DLCDEF(DLC_ ## a ## b, c)


	using std::cout;
	using std::cin;
	using std::endl;
	using std::to_string;

	DLCDEF(std::string, STR)

	DLCDEF(signed int, INT32)
	DLCDEF(signed long long, INT64)
	DLCDEF(unsigned int, UINT32)
	DLCDEF(unsigned long long, UINT64)

	DLCDEF(float, F32)
	DLCDEF(double, F64)
	DLCDEF(long double, F80)

	DLCDEF(INT32*, P_INT32)
	DLCDEF(INT64*, P_INT64)
	DLCDEF(UINT32*, P_UINT32)
	DLCDEF(UINT64*, P_UINT64)
	DLCDEF(F32*, P_F32)
	DLCDEF(F64*, P_F64)
	DLCDEF(F80*, P_F80)

	#include "Exceptions.h"
	#define NYI(a) throw dlc::not_yet_implemented(a);


	#include "ComplexMath.h"
	#ifdef DOOMED_COMPLEX_DONE
		DLCDEF(dlc::complex, C80)
		DLCDEF(C80*, P_C80)
	#endif

	

#endif