// minimum-prog.cpp
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <stdlib.h>
#include <iostream>
#include <numeric>

using namespace cv;
using namespace std;

const String windowImage = "TP1";
const String windowImageEqual = "EqualImage";
const String windowSlider = "Slider";
const String windowHistogram = "Histogram";
const String nameSlider = "slider";
const String imageToReadDefault = "lena.jpeg";
const String windowsHistogrammeCumul = "HistogrammeEqual";

vector<double> histogramme(Mat image);
vector<double> histogramme_cumule(const vector<double> &h_I);
Mat afficheHistogrammes(const std::vector<double> &histogramme);

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

vector<double> histogramme_cumule(const vector<double> &histogramme)
{
  vector<double> res(256);
  double numberPixels = accumulate(histogramme.begin(), histogramme.end(), 0.0);

  double currentValue = 0;

  for (int i = 0; i < 256; i++)
  {
    double newValueHistogram = (histogramme[i] / numberPixels) * 256;
    currentValue += newValueHistogram;
    res[i] = currentValue;
  }

  return res;
}

Mat afficheHistogrammes(const vector<double> &histogramme, const vector<double> &histogrammeCumule)
{
  Mat imageHist(256, 512, CV_8UC1);
  
  // Display Histogramme gauche
  double max = *max_element(histogramme.begin(), histogramme.end());
  cout << "Max value: " << max << endl;

  for (int line = 0; line < 256; line++)
  {
    for (int column = 0; column < 256; column++)
    {
      int newValueHistogram = (histogramme[column] / max) * 256;
      int pixelValue;
      if (newValueHistogram >= 256 - line)
      {
        pixelValue = 0;
      }
      else
      {
        pixelValue = 255;
      }
      imageHist.at<uchar>(line, column) = pixelValue;
    }
  }

// Display histogramme droit
  for (int line = 0; line < 256; line++)
  {
    for (int column = 256; column < 512; column++)
    {
      int newValueHistogram = histogrammeCumule[column - 256];
      int pixelValue;
      if (newValueHistogram >= 255 - line)
      {
        pixelValue = 0;
      }
      else
      {
        pixelValue = 255;
      }
      imageHist.at<uchar>(line, column) = pixelValue;
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
  namedWindow(windowImageEqual);

  createTrackbar(nameSlider, windowSlider, nullptr, 255, NULL); // un slider
  setTrackbarPos(nameSlider, windowSlider, value);
  Mat f = imread(imageToRead); // lit l'image "lena.png"
                               // Convert to black and white
  f = convertImgToGray(f);
  
  Mat imageEqualize;
  equalizeHist(f, imageEqualize);
  
  vector<double> hist;
  hist = histogramme(f);

  vector<double> histCumul;
  histCumul = histogramme_cumule(hist);

  Mat histMat;
  histMat = afficheHistogrammes(hist, histCumul);
  imshow(windowHistogram, histMat); // l'affiche dans la fenêtre
  imshow(windowImageEqual, f);
  
  vector<double> histEqual;
  histEqual = histogramme(imageEqualize);

  vector<double> histCumulEqual;
  histCumulEqual = histogramme_cumule(histEqual);

  Mat histMatEqual;
  histMatEqual = afficheHistogrammes(histEqual, histCumulEqual);
  imshow(windowsHistogrammeCumul, histMatEqual); // l'affiche dans la fenêtre

  imshow(windowImage, imageEqualize); // l'affiche dans la fenêtre
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
