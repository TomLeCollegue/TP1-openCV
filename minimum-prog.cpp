// minimum-prog.cpp

#include "utils.hpp"
#include "histograms.hpp"

const String windowImage = "Image without filter";
const String windowImageEqual = "EqualImage";
const String windowSlider = "Slider";
const String windowHistogram = "Histograms for gray image";
const String nameSlider = "slider";
const String imageToReadDefault = "lena.jpeg";
const String windowsEqualizeHistogram = "HistogrammeEqual";
const String windrowGrayLevel = "Image in gray levels";

void question1b(Mat f)
{
  Mat imageGray = convertImgToGray(f);

  namedWindow(windrowGrayLevel);
  namedWindow(windowImage);
  imshow(windowImage, f);
  imshow(windrowGrayLevel, imageGray);
}

void question1c(Mat imageGray)
{
  //----
  namedWindow(windrowGrayLevel);
  imshow(windrowGrayLevel, imageGray);
  //----

  //---- Pour l'image non égalisée
  vector<double> hist;
  hist = histogramme(imageGray);

  vector<double> histCumul;
  histCumul = histogrammeCumul(hist);

  Mat histMat;
  histMat = afficheHistogrammes(hist, histCumul);
  namedWindow(windowHistogram);
  imshow(windowHistogram, histMat); // l'affiche dans la fenêtre
  //----

  //---- Pour l'image égalisée
  Mat imageEqualize = imageGray.clone();
  equalizeHistogram(imageEqualize, histCumul);
  namedWindow(windowImageEqual);
  imshow(windowImageEqual, imageEqualize);

  vector<double> histEqual;
  histEqual = histogramme(imageEqualize);

  vector<double> histCumulEqual;
  histCumulEqual = histogrammeCumul(histEqual);

  Mat histMatEqual;
  histMatEqual = afficheHistogrammes(histEqual, histCumulEqual);
  namedWindow(windowsEqualizeHistogram);
  imshow(windowsEqualizeHistogram, histMatEqual); // l'affiche dans la fenêtre
  //----
}

int main(int argc, char *argv[])
{
  // Lire le nom du fichier en argument s'il y en a un.
  String imageToRead;
  if (argc != 1)
  {
    imageToRead = argv[1];
  }
  else
  {
    imageToRead = imageToReadDefault;
  }

  Mat f = imread(imageToRead);
  Mat imageGray;

  imageGray = convertImgToGray(f);

  //---- SLIDER
  int value = 128;
  namedWindow(windowSlider);
  createTrackbar(nameSlider, windowSlider, nullptr, 255, NULL); // un slider
  setTrackbarPos(nameSlider, windowSlider, value);
  //----

  // Question1.b
  // question1b(f);

  // Question 1.c
  question1c(imageGray);

  //---- SLIDER POSITION
  while (waitKey(50) < 0) // attend une touche
  {                       // Affiche la valeur du slider
    int new_value = getTrackbarPos(nameSlider, windowSlider);
    if (value != new_value)
    {
      value = new_value;
      cout << "value=" << value << endl;
    }
  }
  //---- 


  return 0;
}
