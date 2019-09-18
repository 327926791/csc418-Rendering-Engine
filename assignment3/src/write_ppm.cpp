#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code from computer-graphics-raster-images or email
  // jacobson@cs.toronto.edu for correct code.
    std::ofstream myfile;
    int color = 255;
    myfile.open(filename,std::ofstream::binary);   
	//FILE *myfile = fopen(filename.c_str(), "wb");

    if (num_channels == 3) {
        myfile << "P6\n" << width << " " << height << "\n" << color << "\n";
        for (int i = 0; i < data.size(); i++) {
            myfile << data[i];
        }
        myfile.close();
        //std::cout << "output filename: " << filename << std::endl;
        return true;
    } else if (num_channels == 1) {
        myfile << "P5\n" << width << " " << height << "\n" << color << "\n";
        for (int i = 0; i < data.size(); i++) {
            myfile << data[i];
        }
        myfile.close();
        return true;
    }
    return false;
  ////////////////////////////////////////////////////////////////////////////
}
