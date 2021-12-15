#pragma once

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

void DisplayHistograms(Mat& image, vector<double>& hist, vector<double>& histCumul, String windowArgName);

void equalizeColorImages(Mat& image, Mat& Vimage);
