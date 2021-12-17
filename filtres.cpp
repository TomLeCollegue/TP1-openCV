#include "filtres.hpp"

Mat filtreM(Mat input) {
    float kernelValues[] = {1.0, 2.0, 1.0, 2.0, 4.0, 2.0, 1.0, 2.0, 1.0};
    Mat kernel(3, 3, CV_32FC1, kernelValues);
    Mat output;

    cv::filter2D(input, output, -1, kernel / 16.0);
    return output;
}

Mat contrasteM(Mat input, float alpha) {
    // kernel identité - alpha * Masque Laplacien
    float kernelToFilter[] = {0.0, -alpha, 0.0, -alpha, float(1.0 + 4.0 * alpha), -alpha, 0.0, -alpha, 0.0};

    Mat kernel(3, 3, CV_32FC1, kernelToFilter);
    Mat output;

    cv::filter2D(input, output, -1, kernel);

    return output;
}

Mat sobelX(Mat input) {
    float kernelValues[] = {-0.25, 0.0, 0.25, -0.5, 0.0, 0.5, -0.25, 0.0, 0.25};
    Mat kernel(3, 3, CV_32FC1, kernelValues);
    Mat output;
    cv::filter2D(input, output, -1, kernel, Point(-1,-1), 128);
    return output;
}

Mat sobelY(Mat input) {
    float kernelValues[] = {0.25, 0.5, 0.25, 0.0, 0.0, 0.0, -0.25, -0.5, -0.25};
    Mat kernel(3, 3, CV_32FC1, kernelValues);
    Mat output;
    cv::filter2D(input, output, -1, kernel, Point(-1,-1), 128);
    return output;
}