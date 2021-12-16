#include "utils.hpp"
#include "filtres.hpp"

const String mainWindow = "Youpi";
const String windowSlider = "Slider";
const String nameSlider = "alpha (en %)";


int main(int argc, char *argv[])
{
    namedWindow(mainWindow);     // crée une fenêtre
    
    //---- SLIDER
    int alpha = 20;
    createTrackbar(nameSlider, mainWindow, nullptr, 200, NULL); // un slider
    setTrackbarPos(nameSlider, mainWindow, alpha);
    //----

    Mat input = imread(argv[1]); // lit l'image donnée en paramètre
    if (input.channels() == 3)
        cv::cvtColor(input, input, COLOR_BGR2GRAY);
    while (true)
    {
        int new_value = getTrackbarPos(nameSlider, mainWindow);
        if (alpha != new_value)
        {
            alpha = new_value;
            cout << "alpha= " << alpha << endl;
        }

        int keycode = waitKey(50);
        int asciicode = keycode & 0xff;
        if (asciicode == 'q')
        {
            break;
        }
        else if (asciicode == 'a')
        {
            input = filtreM(input);
            imshow(mainWindow, input); // l'affiche dans la fenêtre
        }
        else if (asciicode == 'm')
        {
            cv::medianBlur(input, input, 3);
            imshow(mainWindow, input); // l'affiche dans la fenêtre
        }
        else if (asciicode == 's')
        {
            float alpha1 = (float) alpha / 100.0;
            cout << alpha1 << endl;
            input = laplacienM(input, alpha/100);
            imshow(mainWindow, input); // l'affiche dans la fenêtre
        }
        imshow(mainWindow, input); 
    }


    imwrite("result.png", input); // sauvegarde le résultat
}
