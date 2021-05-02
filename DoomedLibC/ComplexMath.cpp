#include "pch.h"

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