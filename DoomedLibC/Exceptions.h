#ifndef DOOMED_EXCEPT_HGUARD

#define DOOMED_EXCEPT_HGUARD

#include <exception>
#include "DoomedHeader.h"

namespace dlc {
	class not_yet_implemented : std::exception {
	private:
		const STR func;
	public:
		const char* what() { return func.c_str(); }
		not_yet_implemented(STR funcname) : std::exception(), func("This function has not yet been implemented!: " + funcname) {};
	};

	class incompatible_dimensions : std::exception {
	private:
		const STR func;
	public:
		const char* what() { return func.c_str(); }
		incompatible_dimensions() : std::exception(), func("Matrix dimensions don't match.") {};
	};

}

#endif