#pragma once

#include "utils.hpp"

/**
 * @brief TP2 Question 2 : 
 * Filtre moyenneur
 * 
 * @param input 
 * @return Mat 
 */
Mat filtreM(Mat input);

/**
 * @brief TP2 Question 4 : 
 * Rehaussement de contraste en utilisant le masque de Laplacien
 * 
 * @param input 
 * @param alpha 
 * @return Mat 
 */
Mat contrasteM(Mat input, float alpha);

/**
 * @brief TP2 Question 5
 * 
 * @param input 
 * @return Mat 
 */
Mat sobelX(Mat input);

/**
 * @brief TP2 Question 5
 * 
 * @param input 
 * @return Mat 
 */
Mat sobelY(Mat input);

/**
 * @brief TP2 Question 6
 * 
 * @param input 
 * @return Mat 
 */
Mat gradient(const Mat& input);

/**
 * @brief TP 2 Question 7
 * 
 * @param input 
 * @param seuil 
 * @return Mat 
 */
Mat contour(Mat input, float seuil);

/**
 * @brief TP2 Question 8 : En cours
 * 
 * @param input 
 * @param seuil 
 * @param longueur 
 * @param proportion 
 * @return Mat 
 */
Mat esquisse(Mat input, float seuil, float longueur, float proportion);