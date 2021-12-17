#include "utils.hpp"
#include "filtres.hpp"

const String mainWindow = "Youpi";
const String sliderSeuil = "Seuil T";
const String nameSlider = "alpha (en %)";
const String sliderPropor = "Proportion trait (%)";
const String sliderLongueur = "Longueur trait (%)";
const String imageToReadDefault = "lena.jpeg";

int main(int argc, char *argv[])
{
    namedWindow(mainWindow); // crée une fenêtre

    //---- SLIDER
    int alpha = 60;
    createTrackbar(nameSlider, mainWindow, nullptr, 200, nullptr);
    setTrackbarPos(nameSlider, mainWindow, alpha);
    //----

    //---- SLIDER
    int seuil = 40;
    createTrackbar(sliderSeuil, mainWindow, nullptr, 100, nullptr);
    setTrackbarPos(sliderSeuil, mainWindow, seuil);
    //----

    //---- SLIDER
    int proportionTrait = 40;
    createTrackbar(sliderPropor, mainWindow, nullptr, 100, nullptr);
    setTrackbarPos(sliderPropor, mainWindow, proportionTrait);
    //----

    //---- SLIDER
    int longueur = 40;
    createTrackbar(sliderLongueur, mainWindow, nullptr, 3000, nullptr);
    setTrackbarPos(sliderLongueur, mainWindow, proportionTrait);
    //----

    String imageToRead;
    bool webcam = false;

    if (argc != 1)
    {
        if (std::string(argv[1]) == "webcam")
        {
            webcam = true;
        }
        else
        {
            imageToRead = argv[1];
        }
    }
    else
    {
        imageToRead = imageToReadDefault;
    }

    int function = 'i';
    VideoCapture cap(0);
    Mat input;
    if (!webcam)
    {
        input = imread(imageToRead);
        if (input.channels() == 3)
        {
            cv::cvtColor(input, input, COLOR_BGR2GRAY);
        }
    }

    while (true)
    {
        if (webcam)
        {
            cap.read(input);
            cvtColor(input, input, COLOR_BGR2GRAY);
        }
        else
        {
            function = 'i';
        }

        int new_value = getTrackbarPos(nameSlider, mainWindow);
        if (alpha != new_value)
        {
            alpha = new_value;
            cout << "alpha= " << alpha << " %" << endl;
        }

        int newSeuil = getTrackbarPos(sliderSeuil, mainWindow);
        if (seuil != newSeuil)
        {
            seuil = newSeuil;
            cout << "Seuil= " << seuil << endl;
        }

        int newLongueur = getTrackbarPos(sliderLongueur, mainWindow);
        if (longueur != newLongueur) {
            longueur = newLongueur;
            cout << "Longueur= " << longueur << endl;
        }

        int newProp = getTrackbarPos(sliderPropor, mainWindow);
        if (proportionTrait != newProp) {
            proportionTrait = newProp;
            cout << "proportion trait= " << proportionTrait << endl;
        }

        int keycode = waitKey(50);
        int asciicode = keycode & 0xff;
        if (asciicode == 'q')
        {
            break;
        }
        else if (asciicode == 'a' || asciicode == 'm' || asciicode == 's' || asciicode == 'x' || asciicode == 'y' || asciicode == 'g' || asciicode == 'c' || asciicode == 'r')
        {
            function = asciicode;
        }

        if (function == 'a')
        {
            // Q2
            input = filtreM(input);
            imshow(mainWindow, input); // l'affiche dans la fenêtre
        }
        else if (function == 'm')
        {
            // Q3
            medianBlur(input, input, 9);
            imshow(mainWindow, input); // l'affiche dans la fenêtre
        }
        else if (function == 's')
        {
            // Q4
            float alpha1 = (float)alpha / 100.0;
            input = contrasteM(input, alpha1);
            imshow(mainWindow, input); // l'affiche dans la fenêtre
        }
        else if (function == 'x')
        {
            input = sobelX(input, 128.0);
            imshow(mainWindow, input); // l'affiche dans la fenêtre
        }
        else if (function == 'y')
        {
            input = sobelY(input, 128.0);
            imshow(mainWindow, input); // l'affiche dans la fenêtre
        }
        else if (function == 'g')
        {
            input = gradient(input);
            imshow(mainWindow, input); // l'affiche dans la fenêtre
        }
        else if (function == 'c')
        {
            medianBlur(input, input, 9);
            input = contour(input, seuil);
            imshow(mainWindow, input); // l'affiche dans la fenêtre
        }
        else if (function == 'e')
        {

            imshow(mainWindow, input); // l'affiche dans la fenêtre
        }
        else if (function == 'r')
        {
            if (!webcam)
            {
                input = imread(imageToRead);
                if (input.channels() == 3)
                {
                    cv::cvtColor(input, input, COLOR_BGR2GRAY);
                }
                imshow(mainWindow, input);
            }
            else
            {
                cap.read(input);
                cvtColor(input, input, COLOR_BGR2GRAY);
            }
            
        }

        imshow(mainWindow, input);
    }
    imwrite("result.png", input); // sauvegarde le résultat
}
