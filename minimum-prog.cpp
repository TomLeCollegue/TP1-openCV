// minimum-prog.cpp

#include "utils.hpp"
#include "histograms.hpp"
#include "displaywindows.hpp"
#include "tramage.hpp"


int main(int argc, char *argv[])
{
  // Lire le nom du fichier en argument s'il y en a un.
  String imageToRead;
  bool webcam = false;
  if (argc != 1)
  {
    if (std::string(argv[1]) == "webcam")
    {
      webcam = true;
    }
    else
    {
      imageToRead = argv[1];
    }
  }
  else
  {
    imageToRead = imageToReadDefault;
  }

  if (!webcam)
  {
    /* code */
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
  }
  else
  {
    VideoCapture cap(0);
    Mat f;

    vector<double> hist;
    vector<double> histCumul;

    vector<double> histE;
    vector<double> histCumulE;

    Mat VPartimage;
    Mat imageEqualized;

    while (true)
    {
      cap.read(f);
      hist = histogramme(f);
      histCumul = histogrammeCumul(hist);
      DisplayHistograms(f, hist, histCumul, "");

      imageEqualized = f.clone();
      equalizeColorImages(imageEqualized, VPartimage);
      histE = histogramme(VPartimage);
      histCumulE = histogrammeCumul(histE);
      DisplayHistograms(imageEqualized, histE, histCumulE, " Equalized");
      waitKey(1);
    }
  }

  // Mat input = convertImgToGray(imageEqualized);
  // Mat outputTramage = input.clone();
  // tramage_floyd_steinberg_gray(input, outputTramage);

  // // Display image
  // namedWindow(windowImage + " tramage");
  // imshow(windowImage + " tramage", outputTramage);

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
