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
    
    Mat f = imread(imageToRead);

    //Question 2.b
    Mat input = convertImgToGray(f);
    Mat outputTramage = input.clone();
    tramage_floyd_steinberg_gray(input, outputTramage);

    // Display image
    namedWindow(windowImage + " tramage");
    imshow(windowImage + " tramage", outputTramage);
    namedWindow("truc");
    imshow("truc", input);

    //Question 2.c
    //TODO
  }
  else
  {
    VideoCapture cap(0);
    Mat f;

    while (true)
    {
      cap.read(f);
      vector<Mat> splitRGBImages(3);
      split(f, splitRGBImages);

      Mat outputTramageR = splitRGBImages[0].clone();
      Mat outputTramageG = splitRGBImages[1].clone();
      Mat outputTramageB = splitRGBImages[2].clone();

      tramage_floyd_steinberg(splitRGBImages[0], outputTramageR);
      tramage_floyd_steinberg(splitRGBImages[1], outputTramageG);
      tramage_floyd_steinberg(splitRGBImages[2], outputTramageB);

      vector<Mat> channels;
      channels.push_back(outputTramageR);
      channels.push_back(outputTramageG);
      channels.push_back(outputTramageB);
      
      Mat finalImage;
      merge(channels, finalImage);

      // Display image
      namedWindow(windowImage + " tramage");
      namedWindow("normal webcam");
      imshow(windowImage + " tramage", finalImage);
      imshow("normal webcam", f);
      /* code */
      waitKey(1);
    }
  }

  while (waitKey(50) < 0)
  {
  }
}
