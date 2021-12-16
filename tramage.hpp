#pragma once

#include "utils.hpp"
#include "histograms.hpp"

/**
 * @brief renvoie la couleur la plus proche de pixel Value entre 2 possibilités, noir ou blanc.
 * 
 * 
 * @param pixelValue 
 * @return float 0.0f pour noir ou 1.0f pour blanc.
 */
float couleurLaPlusProche(float pixelValue);

/**
 * @brief Question 1.a : 
 * Effectue le tramage pour une image en noir et blanc
 * 
 * @param input 
 * @param output 
 */
void tramage_floyd_steinberg_gray(Mat &input, Mat &output);

float distance_color_l2(Vec3f bgr1, Vec3f bgr2 );
int best_color(Vec3f bgr, vector<Vec3f> colors );
Vec3f error_color( Vec3f bgr1, Vec3f bgr2 );
Vec3f applyError(Vec3f value, Vec3f error, float coef);

/**
 * @brief Question 2.b et 2.c : 
 * Fonction de tramage générique
 * 
 * @param input 
 * @param colors 
 * @return Mat 
 */
Mat tramage_floyd_steinberg(Mat input, vector<Vec3f> colors);

