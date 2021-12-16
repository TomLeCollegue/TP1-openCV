#include "filtres.hpp"

Mat filtreM(Mat input)
{
    float kernelValues[] = {1.0, 2.0, 1.0, 2.0, 4.0, 2.0, 1.0, 2.0, 1.0};
    Mat kernel(3, 3, CV_32FC1, kernelValues);
    Mat output;

    cv::filter2D(input, output, -1, kernel / 16.0);
    return output;
}

Mat laplacienM(Mat input, float alpha)
{
    // float kernelIdentity[] = {0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0};
    // float kernelValues[] = {0.0, 1.0, 0.0, 1.0, -4.0, 1.0, 0.0, 1.0, 0.0};

    // kernel identité - alpha * Masque Laplacien
    float kernelToFilter[] = {0.0, -alpha, 0.0, -alpha, float(1.0 + 4.0 * alpha), -alpha, 0.0, -alpha, 0.0};

    // Mat kernel(3, 3, CV_32FC1, kernelValues);
    Mat kernel(3, 3, CV_32FC1, kernelToFilter);
    Mat output;

    cv::filter2D(input, output, -1, kernel);

    return output;
}