#pragma once

#include "utils.hpp"
#include "histograms.hpp"

float couleurLaPlusProche(float pixelValue);
void tramage_floyd_steinberg_gray(Mat &input, Mat &output);

float distance_color_l2(Vec3f bgr1, Vec3f bgr2 );
int best_color(Vec3f bgr, vector<Vec3f> colors );
Vec3f error_color( Vec3f bgr1, Vec3f bgr2 );

Mat tramage_floyd_steinberg(Mat input, vector<Vec3f> colors);

