#include "utils.hpp"
#include "filtres.hpp"

const String mainWindow = "Youpi";


int main(int argc, char *argv[])
{
    namedWindow(mainWindow);        // crée une fenêtre
    Mat input = imread(argv[1]); // lit l'image donnée en paramètre
    if (input.channels() == 3)
        cv::cvtColor(input, input, COLOR_BGR2GRAY);
    while (true)
    {
        int keycode = waitKey(50);
        int asciicode = keycode & 0xff;
        if (asciicode == 'q') {
            break;
        }
        else if ( asciicode == 'a') {
            input = filtreM(input);
            imshow(mainWindow, input); // l'affiche dans la fenêtre
        }
    }
    imwrite("result.png", input); // sauvegarde le résultat
}