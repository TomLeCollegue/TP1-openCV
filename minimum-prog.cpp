// minimum-prog.cpp
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <stdlib.h>
#include <iostream>

using namespace cv;
using namespace std;

const String windowImage = "TP1";
const String windowSlider = "Slider";
const String nameSlider = "slider";
const String imageToReadDefault = "lena.jpeg";

vector<double> histogramme(Mat image);
vector<double> histogramme_cumule(const vector<double> &h_I);
Mat convertImgToGray(Mat mat);

vector<double> histogramme(Mat image)
{
  vector<double> res;
  for (int line = 0; line < image.rows; line++)
  {
    for (int column = 0; column < image.cols; column++)
    {
       std::cout << image.at<uint>(line,column) << std::endl;
    }
  }
  return res;
}

Mat convertImgToGray(Mat mat)
{
  Mat matOutGray;
  if (mat.type() != CV_8UC1)
  {
    cvtColor(mat, matOutGray, COLOR_RGB2GRAY);
  }
  else
  {
    cout << "Image déjà en noir et blanc" << endl;
    matOutGray = mat;
  }
  return matOutGray;
}

int main(int argc, char *argv[])
{
  String imageToRead;
  if (argc != 1)
  {
    imageToRead = argv[1];
  }
  else
  {
    imageToRead = imageToReadDefault;
  }
  int value = 128;
  namedWindow(windowImage); // crée une fenêtre
  namedWindow(windowSlider);
  createTrackbar(nameSlider, windowSlider, nullptr, 255, NULL); // un slider
  setTrackbarPos(nameSlider, windowSlider, value);
  Mat f = imread(imageToRead); // lit l'image "lena.png"
                               // Convert to black and white
  f = convertImgToGray(f);

  histogramme(f);

  imshow(windowImage, f); // l'affiche dans la fenêtre
  while (waitKey(50) < 0) // attend une touche
  {                       // Affiche la valeur du slider
    int new_value = getTrackbarPos(nameSlider, windowSlider);
    if (value != new_value)
    {
      value = new_value;
      cout << "value=" << value << endl;
    }
  }
}
