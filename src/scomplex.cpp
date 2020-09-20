#include "scomplex.h"

using namespace std;

Complex::Complex() {
    real = 0;
    imaginaria = 0;
}

Complex::Complex(double r, double i) {
    real = r;
    imaginaria = i;
}

double Complex::getReal() {
    return real;
}

double Complex::getImaginary() {
    return imaginaria;
}

void Complex::setReal(double r) {
    real = r;
}

void Complex::setImaginary(double i) {
    imaginaria = i;
}

Complex operator+(Complex c1, Complex c2) {
    Complex c;  //No valgo pa los nombres xd

    c.setReal(c1.getReal() + c2.getReal());
    c.setImaginary(c1.getImaginary() + c2.getImaginary());

    return c;
}

Complex operator+(Complex c, double d) {
    Complex c2;     //De verdad ayuda

    c2.setReal(c.getReal() + d);
    c2.setImaginary(c.getImaginary());

    return c2;
}

Complex operator*(Complex c1, Complex c2) {
    Complex c;

    c.setReal(c1.getReal()*c2.getReal() - c1.getImaginary()*c2.getImaginary());
    c.setImaginary(c1.getReal()*c2.getImaginary() + c2.getReal()*c1.getImaginary());

    return c;
}