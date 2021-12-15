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

void DisplayHistograms(Mat& image, vector<double>& hist, vector<double>& histCumul, String windowArgName)
{
    // Display Histograms
    Mat histMat;
    histMat = afficheHistogrammes(hist, histCumul);
    namedWindow(windowHistogram + windowArgName);
    imshow(windowHistogram + windowArgName, histMat); // l'affiche dans la fenêtre

    // Display image
    namedWindow(windowImage + windowArgName);
    imshow(windowImage + windowArgName, image);
}

void equalizeColorImages(Mat& image, Mat& Vimage)
{
    Mat imageHSV = convertImgToHSV(image);
    vector<Mat> splitHSVImages(3);
    split(imageHSV, splitHSVImages);

    Vimage = splitHSVImages[2];

    vector<double> hist = histogramme(Vimage);
    vector<double> histCumul = histogrammeCumul(hist);

    equalizeHistogram(Vimage, histCumul);

    vector<Mat> channels;
    channels.push_back(splitHSVImages[0]);
    channels.push_back(splitHSVImages[1]);
    channels.push_back(Vimage);

    Mat finalImage;
    merge(channels, finalImage);
    image = convertHSVToBGR(finalImage);  
}