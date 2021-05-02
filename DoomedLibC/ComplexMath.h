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

	namespace dlc {

		std::ostream& operator<<(std::ostream& stream, const complex& cmplx) {
			return stream << cmplx.real << ((cmplx.imag >= 0) ? " + " : " - ") << abs(cmplx.imag) << "i";
		}

		std::ostream& operator<<(std::ostream& stream, const complex_polar& cmplx) {
			return stream << cmplx.r << "*e^(" << cmplx.theta << "i)";
		}

		complex complex::operator+(complex cmplx) {
			return { this->real + cmplx.real, this->imag + cmplx.imag };
		}

		complex complex::operator-(complex cmplx) {
			return { this->real - cmplx.real, this->imag - cmplx.imag };
		}

		complex& complex::operator+=(complex cmplx) {
			this->real += cmplx.real;
			this->imag += cmplx.imag;
			return *this;
		}

		complex& complex::operator-=(complex cmplx) {
			this->real -= cmplx.real;
			this->imag -= cmplx.imag;
			return *this;
		}

		complex complex::operator*(complex cmplx) {
			return { this->real * cmplx.real - this->imag * cmplx.imag, this->imag * cmplx.real + this->real * cmplx.imag };
		}

		complex complex::operator/(complex cmplx) {
			F80 abs = abs2(cmplx);
			return { ((this->real * cmplx.real) + (this->imag * cmplx.imag)) / abs, ((this->imag * cmplx.real) - (this->real * cmplx.imag)) / abs };
		}

		complex& complex::operator*=(complex cmplx) {
			F80 temp = this->real;
			this->real = (temp * cmplx.real) - (this->imag * cmplx.imag); //ac - bd
			this->imag = (this->imag * cmplx.real) + (temp * cmplx.imag); //bc + ad
			return *this;
		}

		complex& complex::operator/=(complex cmplx) {
			F80 temp = this->real;
			F80 f = abs2(cmplx);
			this->real = ((temp * cmplx.real) + (this->imag * cmplx.imag)) / f;
			this->imag = ((this->imag * cmplx.real) - (temp * cmplx.imag)) / f;
			return *this;
		}

		F80 abs(complex c) {
			return sqrt(abs2(c));
		}

		F80 abs2(complex c) {
			return c.real * c.real + c.imag * c.imag;
		}

		complex pow(complex base, F80 exponent) {
			complex_polar c = base;
			c.r = std::pow(c.r, exponent);
			c.theta *= exponent;
			return c;
		}

		complex pow(complex base, complex exponent) {
			complex_polar c = base;
			return exp(complex(exponent.real * std::log(c.r) - exponent.imag * c.theta, exponent.imag * std::log(c.r) + exponent.real * c.theta));
		}

		complex exp(complex exponent) {
			complex c = complex(std::cos(exponent.imag), std::sin(exponent.imag));
			return c * std::exp(exponent.real);
		}


		complex sin(complex c) {
			F80 a = std::sin(c.real) + std::cosh(c.imag);
			F80 b = std::cos(c.real) + std::sinh(c.imag);
			return complex(a, b);
		}
		complex cos(complex c) {
			F80 a = std::cos(c.real) + std::cosh(c.imag);
			F80 b = std::sin(c.real) + std::sinh(c.imag);
			return complex(a, b);
		}

	}

	#define DOOMED_COMPLEX_DONE

#endif

	