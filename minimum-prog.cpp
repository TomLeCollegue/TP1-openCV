// minimum-prog.cpp
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <stdlib.h>
#include <iostream>

using namespace cv;
using namespace std;

const String windowImage = "TP1";
const String windowSlider = "Slider";
const String windowHistogram = "Histogram";
const String nameSlider = "slider";
const String imageToReadDefault = "lena.jpeg";

vector<double> histogramme(Mat image);
vector<double> histogramme_cumule(const vector<double> &h_I);
Mat afficheHistogrammes(const std::vector<double>& histogramme);

Mat convertImgToGray(Mat mat);

vector<double> histogramme(Mat image)
{
  vector<double> res(256);
  for (int line = 0; line < image.rows; line++)
  {
    for (int column = 0; column < image.cols; column++)
    {
      int pixelValue = (int)image.at<uchar>(line, column);
      res[pixelValue] = res[pixelValue] + 1;
    }
  }
  return res;
}


Mat afficheHistogrammes(const vector<double>& histogramme) 
{
  Mat imageHist( 256, 256, CV_8UC1);
  double max = *max_element(histogramme.begin(), histogramme.end());
  cout<<"Max value: " << max << endl ;

  for (int line = 0; line < imageHist.rows; line++)
  {
    for (int column = 0; column < imageHist.cols; column++)
    {
      int newValueHistogram = ( histogramme[column] / max ) * 255;

      int pixelValue;
      if(newValueHistogram >= imageHist.rows - line) {
        pixelValue = 0;
      } else {
        pixelValue = 255;
      }
      imageHist.at<uchar>(line,column) = pixelValue;
    }
  }
  return imageHist;
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
  namedWindow(windowHistogram);

  createTrackbar(nameSlider, windowSlider, nullptr, 255, NULL); // un slider
  setTrackbarPos(nameSlider, windowSlider, value);
  Mat f = imread(imageToRead); // lit l'image "lena.png"
                               // Convert to black and white
  f = convertImgToGray(f);

  vector<double> hist;
  hist = histogramme(f);

  Mat histMat;
  histMat = afficheHistogrammes(hist);
  imshow(windowHistogram, histMat); // l'affiche dans la fenêtre

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
