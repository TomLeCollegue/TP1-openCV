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

Mat sobelX(Mat input, float delta) {
    float kernelValues[] = {-0.25, 0.0, 0.25, -0.5, 0.0, 0.5, -0.25, 0.0, 0.25};
    Mat kernel(3, 3, CV_32FC1, kernelValues);
    Mat output;
    cv::filter2D(input, output, -1, kernel, Point(-1, -1), delta);
    return output;
}

Mat sobelY(Mat input, float delta) {
    float kernelValues[] = {-0.25, -0.5, -0.25, 0.0, 0.0, 0.0, 0.25, 0.5, 0.25};
    Mat kernel(3, 3, CV_32FC1, kernelValues);
    Mat output;
    cv::filter2D(input, output, -1, kernel, Point(-1, -1), delta);
    return output;
}

Mat gradient(const Mat &input) {
    Mat inputX = sobelX(input, 0.0);
    Mat inputY = sobelY(input, 0.0);

    inputX.convertTo(inputX, CV_32FC1, 1.0);
    inputY.convertTo(inputY, CV_32FC1, 1.0);

    Mat output = inputX.clone();

    for (int line = 0; line < input.rows; line++) {
        for (int column = 0; column < input.cols; column++) {
            float valueX = inputX.at<float>(line, column) - 128.0;
            float valueY = inputY.at<float>(line, column) - 128.0;
            output.at<float>(line, column) = sqrt(valueX * valueX + valueY * valueY);
        }
    }
    output.convertTo(output, CV_8UC1, 1.0);
    return output;
}

Mat contour(Mat input, float seuil) {
    Mat inputFloat = input.clone();
    input.convertTo(inputFloat, CV_32FC1);

    Mat Mlaplac;
    Mat Mgradient = gradient(input);
    Mgradient.convertTo(Mgradient, CV_32FC1);
    Mat output = Mgradient.clone();

    float kernelValues[] = {0.0, 1.0, 0.0, 1.0, -4.0, 1.0, 0.0, 1.0, 0.0};
    Mat kernel(3, 3, CV_32FC1, kernelValues);
    cv::filter2D(inputFloat, Mlaplac, -1, kernel);
    Mlaplac.convertTo(Mlaplac, CV_32FC1);

    for (int line = 1; line < input.rows - 1; line++) {
        for (int column = 1; column < input.cols - 1; column++) {
            if (Mgradient.at<float>(line, column) > seuil) {
                if (Mlaplac.at<float>(line, column) * Mlaplac.at<float>(line - 1, column) < 0
                    || Mlaplac.at<float>(line, column) * Mlaplac.at<float>(line + 1, column) < 0
                    || Mlaplac.at<float>(line, column) * Mlaplac.at<float>(line, column + 1) < 0
                    || Mlaplac.at<float>(line, column) * Mlaplac.at<float>(line, column - 1) < 0) {
                    output.at<float>(line, column) = 0.0;
                } else {
                    output.at<float>(line, column) = 255.0;
                }
            } else {
                output.at<float>(line, column) = 255.0;
            }
        }
    }

    output.convertTo(output, CV_8UC1);
    return output;
}

float randO1() {
    return rand() / (double) RAND_MAX;
}

Mat esquisse(Mat input, float seuil, float l, float t) {
    Mat contourMFinal(input.rows, input.cols, CV_32FC1, Scalar(255));

    Mat contourM = contour(input, seuil);
    contourM.convertTo(contourM, CV_32FC1, 1.0);

    Mat gradientM = gradient(input);
    gradientM.convertTo(gradientM, CV_32FC1, 1.0);

    Mat inputX = sobelX(input);
    inputX.convertTo(inputX, CV_32FC1, 1.0);

    Mat inputY = sobelY(input);
    inputY.convertTo(inputY, CV_32FC1, 1.0);

    for (int line = 1; line < input.rows - 1; line++) {
        for (int column = 1; column < input.cols - 1; column++) {
            if (contourM.at<float>(line, column) < 128) {
                if (randO1() < t / 100.0) {
                    float valueY = inputY.at<float>(line, column);
                    float valueX = inputX.at<float>(line, column);
                    float theta = atan2(valueY - 128, valueX - 128) + (M_PI / 2) + (0.02 * (randO1() - 0.5));
                    float g = gradientM.at<float>(line, column);
                    float lprime = (g/255.0) * (l/100.0);


                    Point point1 = Point(column + lprime * cos(theta), line + lprime * sin(theta));
                    Point point2 = Point(column - lprime * cos(theta), line - lprime * sin(theta));
                    cv::line(contourMFinal, point1, point2, Scalar(0));
                }
            }
        }
    }

    contourMFinal.convertTo(contourMFinal, CV_8UC1);
    return contourMFinal;
}
