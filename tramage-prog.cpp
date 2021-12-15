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

  if (!webcam)
  {
    /* code */
    Mat f = imread(imageToRead);

    Mat input = convertImgToGray(f);
    Mat outputTramage = input.clone();
    tramage_floyd_steinberg(input, outputTramage);

    // Display image
    namedWindow(windowImage + " tramage");
    imshow(windowImage + " tramage", outputTramage);
    namedWindow("truc");
    imshow("truc", input);
  }
  else
  {
    VideoCapture cap(0);
    Mat f;

    while (true)
    {
      cap.read(f);
      Mat input = convertImgToGray(f);
      Mat outputTramage = input.clone();
      tramage_floyd_steinberg(input, outputTramage);

      // Display image
      namedWindow(windowImage + " tramage");
      namedWindow("normal webcam");
      imshow(windowImage + " tramage", outputTramage);
      imshow("normal webcam", input);
      /* code */
      waitKey(1);
    }
  }

  while (waitKey(50) < 0)
  {
  }
}