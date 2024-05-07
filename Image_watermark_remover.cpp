
// Image Watermark Remover

// Include necessary libraries
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

// For GUI
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_File_Chooser.H>

using namespace cv;
using namespace std;

// Global variables
bool click1 = false;
Point point1(0, 0);
Mat img;

// Function to handle mouse events
static void click(int event, int x, int y, int flags, void* params)
{
    if (event == EVENT_LBUTTONDOWN)
    {
        // If mousedown, store the x,y position of the mouse
        click1 = true;
        point1 = Point(x, y);
    }
    else if (event == EVENT_MOUSEMOVE && click1)
    {
        // When dragging pressed, draw rectangle in image
        Mat img_copy = img.clone();
        rectangle(img_copy, point1, Point(x, y), Scalar(0, 0, 255), 2);
        imshow("Image", img_copy);
    }
    else if (event == EVENT_LBUTTONUP)
    {
        // On mouseUp, create subimage
        click1 = false;
        Mat sub_img = img(Rect(point1.x, point1.y, x - point1.x, y - point1.y));
        imshow("Snipped Image", sub_img);
    }
}

// Function to open an image and remove watermark
static void open_img(Fl_Widget* widget, void* data)
{
    Fl_File_Chooser chooser(".", "Image Files (*.{png,jpg,jpeg})", Fl_File_Chooser::SINGLE, "Open Image");
    chooser.show();

    while (chooser.visible())
    {
        Fl::wait();
    }

    if (chooser.value() != nullptr)
    {
        string filename = chooser.value();
        img = imread(filename, IMREAD_COLOR);
        namedWindow("Image With Water Mark", WINDOW_AUTOSIZE);
        setMouseCallback("Image With Water Mark", click, nullptr);
        imshow("Image With Water Mark", img);

        Mat img1 = img.clone();
        Mat thresh;
        threshold(img1, thresh, 150, 255, THRESH_BINARY);
        imshow("Image Without Water Mark", thresh);
        waitKey(0);
    }
}

// Main function
int main(int argc, char** argv)
{
    // Create GUI window
    Fl_Window* window = new Fl_Window(1000, 700, "Image Watermark Remover");

    // Create title label
    Fl_Box* title = new Fl_Box(80, 10, 800, 100, "Image Watermark Remover");
    title->labelfont(FL_HELVETICA_BOLD);
    title->labelsize(50);
    title->labelcolor(fl_rgb_color(255, 0, 255));

    // Create "Select" button
    Fl_Button* selectButton = new Fl_Button(150, 550, 150, 50, "SELECT");
    selectButton->labelsize(25);
    selectButton->callback(open_img);

    // Create "Exit" button
    Fl_Button* exitButton = new Fl_Button(700, 550, 150, 50, "EXIT");
    exitButton->labelsize(25);
    exitButton->callback(exit);

    window->end();
    window->show(argc, argv);
    return Fl::run();
}
