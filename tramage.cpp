#include "tramage.hpp"

float couleurLaPlusProche(float pixelValue)
{
    if (pixelValue < 0.50f)
    {
        return 0.0f;
    }
    else
    {
        return 1.0f;
    }
}

void tramage_floyd_steinberg_gray(Mat &input, Mat &output)
{
    Mat calcul;
    input.convertTo(calcul, CV_32FC1, 1 / 255.0);

    for (int line = 1; line < calcul.rows - 1; line++)
    {
        for (int column = 1; column < calcul.cols - 1; column++)
        {
            float oldPixel = calcul.at<float>(line, column);
            float newPixel = couleurLaPlusProche(oldPixel);
            calcul.at<float>(line, column) = newPixel;
            float error = oldPixel - newPixel;

            calcul.at<float>(line, column + 1) = saturate_cast<float>(calcul.at<float>(line, column + 1) + (7.0f / 16.0f * error));
            calcul.at<float>(line + 1, column - 1) = saturate_cast<float>(calcul.at<float>(line + 1, column - 1) + (3.0f / 16.0f * error));
            calcul.at<float>(line + 1, column) = saturate_cast<float>(calcul.at<float>(line + 1, column) + (5.0f / 16.0f * error));
            calcul.at<float>(line + 1, column + 1) = saturate_cast<float>(calcul.at<float>(line + 1, column + 1) + (1.0f / 16.0f * error));
        }
    }
    calcul.convertTo(output, CV_8UC1, 255);
}

Mat tramage_floyd_steinberg(Mat input, vector<Vec3f> colors){
  //TODO
}