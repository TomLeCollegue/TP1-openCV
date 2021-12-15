#include "histograms.hpp"

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

Mat convertImgToHSV(Mat& mat)
{
  Mat matOutGray;
  if (mat.type() != CV_8UC1)
  {
    cvtColor(mat, matOutGray, COLOR_BGR2HSV);
  }
  else
  {
    cout << "Image déjà en noir et blanc" << endl;
    matOutGray = mat;
  }
  return matOutGray;
}

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

vector<double> histogrammeCumul(const vector<double> &histogramme)
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

void equalizeHistogram(Mat image, vector<double>& histCumul) {
  vector<double> L_1CDFs(256);
  for (int i = 0; i < 256; i++)
  { 
    L_1CDFs[i] = round((histCumul[i] / histCumul[255]) * 255);
  }

  for (int line = 0; line < image.rows; line++)
  {
    for (int column = 0; column < image.cols; column++)
    {
      int pixelValue = (int)image.at<uchar>(line, column);
      image.at<uchar>(line, column) = L_1CDFs[pixelValue];
    }
  }

}