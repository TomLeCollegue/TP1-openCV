#include "tramage.hpp"

float couleurLaPlusProche(float pixelValue) {
    if (pixelValue < 0.50f) {
        return 0.0f;
    } else {
        return 1.0f;
    }
}

void tramage_floyd_steinberg_gray(Mat &input, Mat &output) {
    Mat calcul;
    input.convertTo(calcul, CV_32FC1, 1 / 255.0);

    for (int line = 1; line < calcul.rows - 1; line++) {
        for (int column = 1; column < calcul.cols - 1; column++) {
            float oldPixel = calcul.at<float>(line, column);
            float newPixel = couleurLaPlusProche(oldPixel);
            calcul.at<float>(line, column) = newPixel;
            float error = oldPixel - newPixel;

            calcul.at<float>(line, column + 1) = saturate_cast<float>(
                    calcul.at<float>(line, column + 1) + (7.0f / 16.0f * error));
            calcul.at<float>(line + 1, column - 1) = saturate_cast<float>(
                    calcul.at<float>(line + 1, column - 1) + (3.0f / 16.0f * error));
            calcul.at<float>(line + 1, column) = saturate_cast<float>(
                    calcul.at<float>(line + 1, column) + (5.0f / 16.0f * error));
            calcul.at<float>(line + 1, column + 1) = saturate_cast<float>(
                    calcul.at<float>(line + 1, column + 1) + (1.0f / 16.0f * error));
        }
    }
    calcul.convertTo(output, CV_8UC1, 255);
}

float distance_color_l2(Vec3f bgr1, Vec3f bgr2) {
    return
            (bgr2[0] - bgr1[0]) * (bgr2[0] - bgr1[0])
            + (bgr2[1] - bgr1[1]) * (bgr2[1] - bgr1[1])
            + (bgr2[2] - bgr1[2]) * (bgr2[2] - bgr1[2]);
}

int best_color(Vec3f bgr, vector<Vec3f> colors) {
    float bestDistance = distance_color_l2(bgr, colors[0]);
    int bestIndex = 0;
    for (int i = 1; i < colors.size(); ++i) {
        float distance = distance_color_l2(bgr, colors[i]);
        if (distance < bestDistance) {
            bestDistance = distance;
            bestIndex = i;
        }
    }
    return bestIndex;
}

Vec3f error_color(Vec3f bgr2, Vec3f bgr1) {
    return Vec3f({bgr2[0] - bgr1[0], bgr2[1] - bgr1[1], bgr2[2] - bgr1[2]});
}

Vec3f applyError(Vec3f value, Vec3f error, float coef) {
    Vec3f errorWithCoef = Vec3f({error[0] * coef, error[1] * coef, error[2] * coef});
    return Vec3f({value[0] + errorWithCoef[0], value[1] + errorWithCoef[1], value[2] + errorWithCoef[2]});
}

Mat tramage_floyd_steinberg(Mat input, vector<Vec3f> colors) {
    Mat calcul;
    input.convertTo(calcul, CV_32FC3, 1 / 255.0);
    for (int line = 1; line < calcul.rows - 1; line++) {
        for (int column = 1; column < calcul.cols - 1; column++) {
            Vec3f oldPixel = calcul.at<Vec3f>(line, column);
            int bestColorIndex = best_color(oldPixel, colors);
            Vec3f errorColor = error_color(oldPixel, colors[bestColorIndex]);
            calcul.at<Vec3f>(line, column) = colors[bestColorIndex];

            calcul.at<Vec3f>(line, column + 1) = applyError(calcul.at<Vec3f>(line, column + 1), errorColor,
                                                            7.0f / 16.0f);
            calcul.at<Vec3f>(line + 1, column - 1) = applyError(calcul.at<Vec3f>(line + 1, column - 1), errorColor,
                                                                3.0f / 16.0f);
            calcul.at<Vec3f>(line + 1, column) = applyError(calcul.at<Vec3f>(line + 1, column), errorColor,
                                                            5.0f / 16.0f);
            calcul.at<Vec3f>(line + 1, column + 1) = applyError(calcul.at<Vec3f>(line + 1, column + 1), errorColor,
                                                                1.0f / 16.0f);
        }
    }

    Mat output;
    calcul.convertTo(output, CV_8UC3, 255.0);

    return output;
}