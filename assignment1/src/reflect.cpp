#include "reflect.h"

void reflect(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & reflected)
{
  reflected.resize(width*height*num_channels);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////
  
  if (num_channels == 3){
	for (int i = 0; i < height; i++) {
		 for (int j = 0; j < width; j++){
			reflected[width*i + j * 3] = input[width*i + (width - j - 1) * 3];
			reflected[width*i + j * 3 + 1] = input[width*i + (width - j - 1) * 3 + 1];
			reflected[width*i + j * 3 + 2] = input[width*i + (width - j - 1) * 3 + 2];

		}
	}
  }
}
