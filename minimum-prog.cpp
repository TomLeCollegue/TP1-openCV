// minimum-prog.cpp
#include <opencv2/highgui.hpp>
#include <stdlib.h>
#include <iostream>

using namespace cv;
 
const String windowImage = "TP1";
const String windowSlider = "Slider"; 
const String nameSlider = "slider";
const String imageToReadDefault = "lena.jpeg";

int main(int argc,char *argv[])
{
  String imageToRead;
  if(argc != 1) {
    imageToRead = argv[1];
  } else {
    imageToRead = imageToReadDefault;
  }
  int value = 128;
  namedWindow(windowImage);             // crée une fenêtre
  namedWindow(windowSlider);
  createTrackbar( nameSlider, windowSlider, nullptr, 255,  NULL); // un slider
  setTrackbarPos( nameSlider, windowSlider, value );
  Mat f = imread(imageToRead);          // lit l'image "lena.png"
  imshow( windowImage, f );                // l'affiche dans la fenêtre
  while ( waitKey(50) < 0 )            // attend une touche
  { // Affiche la valeur du slider
    int new_value = getTrackbarPos( nameSlider, windowSlider);
    if ( value != new_value )
    {
      value = new_value;
      std::cout << "value=" << value << std::endl;
    }
  }
}               
