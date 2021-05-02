#ifndef DOOMED_COMPLEX_HGUARD

	#define DOOMED_COMPLEX_HGUARD

	#include "DoomedHeader.h"
	#include <cmath>

	namespace dlc {

		using std::abs;
		using std::atan;

		const F80 PI = atan(F80(1)) * 4;

		class complex;

		F80 abs(complex c);
		F80 abs2(complex c);
		complex pow(complex base, F80 exponent);
		complex pow(complex base, complex exponent);
		complex exp(complex exponent);
		complex sin(complex c);
		complex cos(complex c);

		class complex {
		public:
			complex() : real(0), imag(0) {};
			complex(F80 r) : real(r), imag(0) {};
			complex(F80 r, F80 i) : real(r), imag(i) {};
			F80 real;
			F80 imag;
			complex operator+(complex);
			complex operator-(complex);
			complex& operator+=(complex);
			complex& operator-=(complex);
			complex operator*(complex);
			complex operator/(complex);
			complex& operator*=(complex);
			complex& operator/=(complex);
		private:
			friend std::ostream& operator<<(std::ostream&, const complex&);
		};

		class complex_polar {
		public:
			complex_polar(complex c) : r(abs(c)), theta(c.real == 0 ? 0 : (atan(c.imag / c.real) + (c.real < 0 ? PI : 0))) {}
			F80 r;
			F80 theta;
			operator complex() { return complex(r * std::cos(theta), r * std::sin(theta)); }
		private:
			friend std::ostream& operator<<(std::ostream&, const complex_polar&);
		};

	}

	#define DOOMED_COMPLEX_DONE

#endif

	