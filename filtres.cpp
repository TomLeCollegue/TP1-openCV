#include "filtres.hpp"

Mat filtreM(Mat input) 
{
    float kernelValues[] = {1.0, 2.0, 1.0, 2.0, 4.0, 2.0, 1.0, 2.0, 1.0};
    Mat kernel(3,3, CV_32FC1, kernelValues);
    Mat output;

    cv::filter2D(input, output, -1, kernel / 16.0);
    return output;
}