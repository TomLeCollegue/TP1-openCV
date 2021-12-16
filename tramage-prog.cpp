#include "utils.hpp"
#include "histograms.hpp"
#include "displaywindows.hpp"
#include "tramage.hpp"

int main(int argc, char *argv[])
{

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
  vector<Vec3f> colors;
  colors.push_back(Vec3f({0.0, 0.0, 0.0}));
  colors.push_back(Vec3f({0.0, 1.0, 1.0}));
  colors.push_back(Vec3f({1.0, 1.0, 0.0}));
  colors.push_back(Vec3f({1.0, 0.0, 1.0}));
  colors.push_back(Vec3f({1.0, 1.0, 1.0}));

  // Add Red, Blue, Green to the colors available
  colors.push_back(Vec3f({1.0, 0.0, 0.0}));
  colors.push_back(Vec3f({0.0, 1.0, 0.0}));
  colors.push_back(Vec3f({0.0, 0.0, 1.0}));

  if (!webcam)
  {
    /* code */
    Mat f = imread(imageToRead);

    Mat finalImage;
    finalImage = tramage_floyd_steinberg(f, colors);

    // Display image
    namedWindow(windowImage + " tramage");
    imshow(windowImage + " tramage", finalImage);
    namedWindow("default file");
    imshow("default file", f);
  }
  else
  {
    VideoCapture cap(0);
    Mat f;

    cout << "Le nombre de couleurs choisi pour le tramage générique : "<< colors.size() << endl;
    while (true)
    {
      cap.read(f);
      Mat finalImage;
      finalImage = tramage_floyd_steinberg(f, colors);

      // Display image
      namedWindow(windowImage + " tramage");
      //namedWindow("normal webcam");
      imshow(windowImage + " tramage", finalImage);
      //imshow("normal webcam", f);
      /* code */
      waitKey(1);
    }
  }

  while (waitKey(50) < 0)
  {
  }
}
