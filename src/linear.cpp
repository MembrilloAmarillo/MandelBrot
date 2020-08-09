#include <complex.h>
#include <iostream>

using namespace::std;

// Clase para las propiedades basicas

class mandel_properties {
	public:
		long double z_param (long double, long double, long double);
		long double x_param (long double, long double, long double);
		long double c_param (long double, long double, long double);
	/* No las hago privadas porque no puedo acceder desde la herencia a las variables */
		long double z;
		long double x;
		long double c;
		long double r;
};

// Herencia para x_sub n+1
class mandel_next:public mandel_properties {
	public:
	long double next_x (long double, long double);
	
	private:
	long double x_plus1;
};

long double mandel_properties::z_param(long double z, long double r, long double x) {
	long double theta = 0;
	z = this->z;
	r = this->r;
	x = this->x;

	theta = r * (1/2 - x);
	return theta;
}

long double mandel_next::next_x(long double x, long double r) {
	
	mandel_properties *op;

	x = op->z_param(this->z, this->r, this->x);
	r = this->r;
	this->x_plus1 = 0;

	x_plus1 = r * x * (1 - x);

	return x_plus1;
}
