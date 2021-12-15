#pragma once

#include "utils.hpp"
#include "histograms.hpp"

float couleurLaPlusProche(float pixelValue);

/**
 * @brief question 2.b : 
 * tramage pour une image en noir et blanc
 * 
 * @param input 
 * @param output 
 */
void tramage_floyd_steinberg_gray(Mat &input, Mat &output);

/**
 * @brief Question 2.d : 
 * fonction de tramage générique
 * 
 * @param input 
 * @param colors 
 * @return Mat 
 */
Mat tramage_floyd_steinberg(Mat input, vector<Vec3f> colors);
