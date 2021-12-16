#include "utils.hpp"

const String mainWindow = "Youpi";
const String windowSlider = "Slider";
const String nameSlider = "alpha (en %)";

Mat filtreM(Mat input)
{
    float kernelValues[] = {1.0, 2.0, 1.0, 2.0, 4.0, 2.0, 1.0, 2.0, 1.0};
    Mat kernel(3, 3, CV_32FC1, kernelValues);
    Mat output;

    cv::filter2D(input, output, -1, kernel / 16.0);
    return output;
}

int main(int argc, char *argv[])
{
    namedWindow(mainWindow);     // crée une fenêtre
    
    //---- SLIDER
    int alpha = 128;
    createTrackbar(nameSlider, mainWindow, nullptr, 255, NULL); // un slider
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
        imshow(mainWindow, input); 
    }


    imwrite("result.png", input); // sauvegarde le résultat
}