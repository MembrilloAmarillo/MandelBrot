#include <iostream>
#include <fstream>
#include <complex>

const float width   = 600;
const float height  = 600;

int value (int, int);

int main() {
    std::ofstream my_Image ("assets/mandelbrot.ppm");
    if (my_Image.is_open()) {
        my_Image << "P3\n" << width << " " << height << "255\n";
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                int val = value(i, j);
                my_Image << val << ' ' << 0 << ' ' << 0 << "\n";
            }
        }
        my_Image.close();
    }
    else std::cout << "Could not open the file";
    return 0;
}

int value (int x, int y) {
    std::complex<float> point((float)x/width-1.5, (float)y/height-0.5);
    //Divide the image dimension to get values smaller than 1
    //Then apply a translation

    std::complex<float> z(0, 0);
    unsigned int nb_iter = 0;
    while (abs(z) < 2 && nb_iter <= 34) {
        z = z * z + point;
        nb_iter++;
    }
    if (nb_iter < 34) return (255*nb_iter)/33;
    else return 0;
}

