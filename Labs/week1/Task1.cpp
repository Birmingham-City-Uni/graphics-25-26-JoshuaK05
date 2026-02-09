#include <iostream>
#include <lodepng.h>
#include <cmath>


void setPixel(std::vector<uint8_t>& imgBuffer, int x, int y , int r, int g, int b, int a, int width, int height) {
	int pixelIdx = (x + y * width) * 4;
	imgBuffer[pixelIdx + 0] = r;
	imgBuffer[pixelIdx + 1] = g;
	imgBuffer[pixelIdx + 2] = b; 
	imgBuffer[pixelIdx + 3] = a;
}


int main()
{
	std::string outputFilename = "output.png";

	const int width = 1920, height = 1080;
	const int nChannels = 4;

	// Setting up an image buffer
	// This std::vector has one 8-bit value for each pixel in each row and column of the image, and
	// for each of the 4 channels (red, green, blue and alpha).
	// Remember 8-bit unsigned values can range from 0 to 255.
	std::vector<uint8_t> imageBuffer(height*width*nChannels);



	// This for loop sets all the pixels of the image to a cyan colour. 
	for(int y = 0; y < height/2; ++y) 
		for (int x = 0; x < width; ++x) {
			setPixel(imageBuffer, x, y, 0, 255, 255, 255, width, height);
		}
	for (int y = 0; y < height; ++y)
		for (int x = 0; x < width; ++x) {
			if (std::sqrtf((x - width/2)*(x - width / 2) + (y - height / 2)*(y - height / 2)) < 275)
			setPixel(imageBuffer, x, y, 255, 0, 255, 255, width, height);
		}
	for (int y = height/2; y < height; ++y)
		for (int x = 0; x < width; ++x) {
			setPixel(imageBuffer, x, y, 0, 255, 0, 255, width, height);
		}


	// * Optional Task 4: Work out how good the compression ratio of the saved PNG image is. PNG images
	//           use *lossless* compression, where all the pixel values of the original image are preserved.
	//           To work out the compression ratio, compare the size of the saved image to the memory
	//           occupied by the image buffer (this is based on the width, height and number of channels).
	//           Try setting the pixels to random values (use rand() and the % operator). What is the 
	//           compression ratio now, and why do you think this is?


	// *** Encoding image data ***
	// PNG files are compressed to save storage space. 
	// The lodepng::encode function applies this compression to the image buffer and saves the result 
	// to the filename given.
	int errorCode;
	errorCode = lodepng::encode(outputFilename, imageBuffer, width, height);
	if (errorCode) { // check the error code, in case an error occurred.
		std::cout << "lodepng error encoding image: " << lodepng_error_text(errorCode) << std::endl;
		return errorCode;
	}

	return 0;
}
