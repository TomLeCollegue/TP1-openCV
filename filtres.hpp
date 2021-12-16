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
Mat laplacienM(Mat input, float alpha);