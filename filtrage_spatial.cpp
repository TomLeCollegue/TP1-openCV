#include "utils.hpp"
#include "filtres.hpp"

const String mainWindow = "Youpi";
const String sliderSeuil = "Seuil T";
const String nameSlider = "alpha (en %)";
const String imageToReadDefault = "lena.jpeg";

int main(int argc, char *argv[]) {
    namedWindow(mainWindow); // crée une fenêtre

    //---- SLIDER
    int alpha = 60;
    createTrackbar(nameSlider, mainWindow, nullptr, 200, NULL); // un slider
    setTrackbarPos(nameSlider, mainWindow, alpha);
    //----

    //---- SLIDER
    int seuil = 60;
    createTrackbar(sliderSeuil, mainWindow, nullptr, 200, NULL); // un slider
    setTrackbarPos(sliderSeuil, mainWindow, seuil);
    //----

    String imageToReadName;
    if (argc != 1) {
        imageToReadName = argv[1];
    } else {
        imageToReadName = imageToReadDefault;
    }
    Mat input = imread(imageToReadName); // lit l'image donnée en paramètre

    if (input.channels() == 3)
        cv::cvtColor(input, input, COLOR_BGR2GRAY);
    while (true) {
        int new_value = getTrackbarPos(nameSlider, mainWindow);
        if (alpha != new_value) {
            alpha = new_value;
            cout << "alpha= " << alpha << " %" << endl;
        }

        int keycode = waitKey(50);
        int asciicode = keycode & 0xff;
        if (asciicode == 'q') {
            break;
        } else if (asciicode == 'a') {
            // Q2
            input = filtreM(input);
            imshow(mainWindow, input); // l'affiche dans la fenêtre
        } else if (asciicode == 'm') {
            // Q3
            cv::medianBlur(input, input, 3);
            imshow(mainWindow, input); // l'affiche dans la fenêtre
        } else if (asciicode == 's') {
            // Q4
            float alpha1 = (float) alpha / 100.0;
            cout << "alpha : " << alpha1 << endl;
            input = contrasteM(input, alpha1);
            imshow(mainWindow, input); // l'affiche dans la fenêtre
        } else if (asciicode == 'x') {
            input = sobelX(input);
            imshow(mainWindow, input); // l'affiche dans la fenêtre
        } else if (asciicode == 'y') {
            input = sobelY(input);
            imshow(mainWindow, input); // l'affiche dans la fenêtre
        } else if (asciicode == 'g') {
            input = gradient(input);
            imshow(mainWindow, input); // l'affiche dans la fenêtre
        }
        imshow(mainWindow, input);
    }

    imwrite("result.png", input); // sauvegarde le résultat
}
