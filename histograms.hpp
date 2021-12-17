#pragma once

#include "utils.hpp"

/**
 * @brief Question 1.b : 
 * Convertit l'image en entrée en niveaux de gris.
 * Si l'image est déjà en niveau de gris alors elle est simplement renvoyée telle quelle.
 * 
 * @param mat 
 * @return Mat 
 */
Mat convertImgToGray(Mat mat);

/**
 * @brief Question 1.D
 * Convertit l'image en entrée en HSV
 * @param mat 
 * @return Mat 
 */
Mat convertImgToHSV(Mat &mat);


/**
 * @brief Question 1.D
 * Convertit l'image en entrée HSV en BGR
 * @param mat 
 * @return Mat 
 */
Mat convertHSVToBGR(Mat &mat);

/**
 * @brief Question 1.c : 
 * Calcule d'un histogramme simple mesurant la proportion de pixel ayant la même valeur.
 * 
 * @param image Il s'agit d'une image en niveaux de gris.
 * @return vector<double> 
 */
vector<double> histogramme(Mat image);

/**
 * @brief Question 1.c : 
 * Histogramme cumulant les valeurs de l'histogramme précédent.
 * 
 * @param h_I histogramme généré par la fonction histogramme(Mat)
 * @return vector<double> 
 */
vector<double> histogrammeCumul(const vector<double> &h_I);

/**
 * @brief Question 1.c : 
 * Retourne une image contenant les 2 histogrammes,
 * l'histogramme simple et l'histogramme cumulé.
 * 
 * @param histogramme 
 * @param histogrammeCumule 
 * @return Mat 
 */
Mat afficheHistogrammes(const std::vector<double> &histogramme, const vector<double> &histogrammeCumule);

/**
 * @brief Question 1.c :
 * Retourne une image egalisée
 * @param image 
 * @param histCumul 
 */
void equalizeHistogram(Mat image, vector<double> &histCumul);