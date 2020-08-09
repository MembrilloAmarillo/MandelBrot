#include <complex.h>
#include <iostream>

using namespace::std;

// Clase para las propiedades basicas

class mandel_properties {
	public:
		long double z_param (long double, long double, long double);
		long double x_param (long double, long double, long double);
		long double c_param (long double);
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
		/* Debemos que calcular la derivada de next_y para encontrar valores criticos */
		long double next_y (long double);
	private:
		long double x_plus1;
};

long double mandel_properties::z_param(long double z, long double r, long double x) {
	long double theta = 0;
	/* No creo que haga falta esto, pero por si acaso :) */
	z = this->z;
	r = this->r;
	x = this->x;
	/* ################################################ */

	theta = r * (1/2 - x);
	return theta;
}

/* Podemos meter algun valor loco de r y al carajo */
long double mandel_properties::c_param(long double r) {
	r = this->r;

	/* r = 4 es un valor seguro para calcular */
	this->c = -(r/2) * ((r-2)/2);

	return this->c;
}

long double mandel_next::next_x(long double x, long double r) {
	
	/* Lo mismo de antes, por si acaso xD */
	x = this->x;
	r = this->r;
	/* ################################## */
	this->x_plus1 = 0;

	x_plus1 = r * x * (1 - x);

	return x_plus1;
}
