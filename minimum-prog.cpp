// minimum-prog.cpp

#include "utils.hpp"
#include "histograms.hpp"
#include "displaywindows.hpp"
#include "tramage.hpp"

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

  // Mat imageGray;
  // imageGray = convertImgToGray(f);

  // Create histograms
  vector<double> hist;
  vector<double> histCumul;
  hist = histogramme(f);
  histCumul = histogrammeCumul(hist);
  DisplayHistograms(f, hist, histCumul, "");

  Mat VPartimage;
  Mat imageEqualized = f.clone();
  equalizeColorImages(imageEqualized, VPartimage);

  vector<double> histE;
  vector<double> histCumulE;
  histE = histogramme(VPartimage);
  histCumulE = histogrammeCumul(histE);
  DisplayHistograms(imageEqualized, histE, histCumulE, " Equalized");

  Mat input = convertImgToGray(imageEqualized);
  Mat outputTramage = input.clone();
  tramage_floyd_steinberg(input, outputTramage);

  // Display image
  namedWindow(windowImage + " tramage");
  imshow(windowImage + " tramage", outputTramage);

  // //---- SLIDER
  // int value = 128;
  // namedWindow(windowSlider);
  // createTrackbar(nameSlider, windowSlider, nullptr, 255, NULL); // un slider
  // setTrackbarPos(nameSlider, windowSlider, value);
  // //----
  // //---- SLIDER POSITION
  while (waitKey(50) < 0) // attend une touche
  {                       // Affiche la valeur du slider
    // int new_value = getTrackbarPos(nameSlider, windowSlider);
    // if (value != new_value)
    // {
    //   value = new_value;
    //   cout << "value=" << value << endl;
    // }
  }
  //----

  return 0;
}
