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
    int seuil = 40;
    createTrackbar(sliderSeuil, mainWindow, nullptr, 200, NULL); // un slider
    setTrackbarPos(sliderSeuil, mainWindow, seuil);
    //----

    String imageToRead;
    bool webcam = false;
    if (argc != 1) {
        if (std::string(argv[1]) == "webcam") {
            webcam = true;
        } else {
            imageToRead = argv[1];
        }
    } else {
        imageToRead = imageToReadDefault;
    }

    int function = 'i';

    //if (input.channels() == 3)
    //    cv::cvtColor(input, input, COLOR_BGR2GRAY);

    VideoCapture cap(0);
    Mat input;
    while (true) {
        cap.read(input);
        cvtColor(input, input, COLOR_BGR2GRAY);

        int new_value = getTrackbarPos(nameSlider, mainWindow);
        if (alpha != new_value) {
            alpha = new_value;
            cout << "alpha= " << alpha << " %" << endl;
        }

        int newSeuil = getTrackbarPos(sliderSeuil, mainWindow);
        if (seuil != newSeuil) {
            seuil = newSeuil;
            cout << "Seuil= " << seuil << endl;
        }

        int keycode = waitKey(50);
        int asciicode = keycode & 0xff;
        if (asciicode == 'q') {
            break;
        } else if (asciicode == 'a'
                   || asciicode == 'm'
                   || asciicode == 's'
                   || asciicode == 'x'
                   || asciicode == 'y'
                   || asciicode == 'g'
                   || asciicode == 'c'
                   ) {
            function = asciicode;
        }

        if (function == 'a') {
            // Q2
            input = filtreM(input);
            imshow(mainWindow, input); // l'affiche dans la fenêtre
        } else if (function == 'm') {
            // Q3
            cv::medianBlur(input, input, 3);
            imshow(mainWindow, input); // l'affiche dans la fenêtre
        } else if (function == 's') {
            // Q4
            float alpha1 = (float) alpha / 100.0;
            input = contrasteM(input, alpha1);
            imshow(mainWindow, input); // l'affiche dans la fenêtre
        } else if (function == 'x') {
            input = sobelX(input);
            imshow(mainWindow, input); // l'affiche dans la fenêtre
        } else if (function == 'y') {
            input = sobelY(input);
            imshow(mainWindow, input); // l'affiche dans la fenêtre
        } else if (function == 'g') {
            input = gradient(input);
            imshow(mainWindow, input); // l'affiche dans la fenêtre
        } else if (function == 'c') {
            input = contour(input, seuil);
            imshow(mainWindow, input); // l'affiche dans la fenêtre
        }

        imshow(mainWindow, input);
    }

    imwrite("result.png", input); // sauvegarde le résultat
}
