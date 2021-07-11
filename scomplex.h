/**
 * @file complex.h
 * @author
 * @note
 */

#ifndef COMPLEX_H
#define COMPLEX_H

/**
 * @class Complex
 * @brief Represents a complex number in its binomic form
 */

class Complex {
    private:
        double real;
        double imaginaria;
    public:
        /**
         * @brief Basic constructor of the class
         */
        Complex();
        /**
         * @brief Constructor with params
         * @param r The real part
         * @param i The imaginary part
         */
        Complex(double r, double i);
        /**
         * @brief Get the real part
         * @return The real part
         */
        double getReal();
        /**
         * @brief Get the imaginary part
         * @return The imaginary part
         */
        double getImaginary();
        /**
         * @brief Set the real part
         * @param r A real number
         */
        void setReal(double r);
        /**
         * @brief Set the imaginary part
         * @param i A real number
         */
        void setImaginary(double i);
};

/**
 * @brief Overload the addition operator with complex
 * @param c1 A complex
 * @param c2 Other complex
 */
Complex operator+(Complex c1, Complex c2);
/**
 * @brief Overload the addition operator with doubles
 * @param c A complex
 * @param d A double
 */
Complex operator+(Complex c, double d);
/**
 * @brief Overload the addition operator with doubles
 * @param c A complex
 * @param d A double
 */
Complex operator+(double d, Complex c);
/**
 * @brief Overload the multiplication operator with complex
 * @param c1 A complex
 * @param c2 Other complex
 */
Complex operator*(Complex c1, Complex c2);
/**
 * @brief Overload the multiplication operator with doubles
 * @param c A complex
 * @param d A double
 */
Complex operator*(Complex c, double d);

#endif /* COMPLEX_H */