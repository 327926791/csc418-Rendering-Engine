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
  assert(
    (num_channels == 3 || num_channels ==1 ) &&
    ".ppm only supports RGB or grayscale images");
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  std::ofstream myfile;
  int color = 255;
  char a = 0x0a;
  myfile.open(filename);

  myfile << "P6" << a << width << " " << height << a << color << a;

  if (num_channels == 3) {

	  for (int i = 0; i < data.size(); i++) {
		  myfile << data[i];
	  }
	  myfile.close();
	  return true;
  }
  else if (num_channels == 1) {
	  
	  return true;
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}
