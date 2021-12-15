#include "utils.hpp"
#include "histograms.hpp"

float couleurLaPlusProche(float pixelValue)
{
    if (pixelValue < 0.50)
    {
        return 0.0;
    }
    else
    {
        return 1.0;
    }
}

void tramage_floyd_steinberg(Mat &input, Mat &output)
{

    Mat calcul;
    input.convertTo(calcul, CV_32FC1, 1 / 255.0);

    Mat outputFloat;
    output.convertTo(outputFloat, CV_32FC1, 1 / 255.0);

    for (int line = 1; line < calcul.rows - 1; line++)
    {
        for (int column = 1; column < calcul.cols - 1; column++)
        {
            float oldPixel = input.at<float>(line, column);
            float newPixel = couleurLaPlusProche(oldPixel);
            output.at<float>(line, column) = newPixel;
            float error = oldPixel - newPixel;

            outputFloat.at<float>(line, column + 1) = input.at<float>(line, column + 1) + (7.0 / 16.0 * error);
            outputFloat.at<float>(line + 1, column - 1) = input.at<float>(line + 1, column - 1) + (3.0 / 16.0 * error);
            outputFloat.at<float>(line + 1, column) = input.at<float>(line + 1, column) + (5.0 / 16.0 * error);
            outputFloat.at<float>(line + 1, column + 1) =  input.at<float>(line + 1, column + 1) + (1.0 / 16.0 * error);
        }
    }

    outputFloat.convertTo(output, CV_8UC1, 255);
}