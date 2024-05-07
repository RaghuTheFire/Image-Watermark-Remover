# FLTK Installation
To build an FLTK project on UBUNTU 20.04.

Install FLTK and two additional packages:
$ sudo apt install fltk1.3-dev
$ sudo apt install libxft-dev
$ sudo apt install libxinerama-dev
After this, you can define an FLTK project, and build it without problems.
If you do not install the libxft-dev and libXinerama-dev packages, you will indeed get these error messages listed in question about missing libraries (-lXft, -lfontconfig, -lXinerama).

# Image_watermark_remover.cpp
This C++ code uses the OpenCV library for image processing and the FLTK library for creating a graphical user interface (GUI). The code provides functionality to open an image, remove watermarks, and display the original and processed images.

Here's a breakdown of the code:

1. The necessary libraries are included, including `opencv2/opencv.hpp` for image processing and `FL/Fl.H` for the FLTK GUI library.
2. Global variables `click1` and `point1` are declared to handle mouse events for selecting a region of interest in the image.
3. The `click` function is defined to handle mouse events. It allows the user to select a region of interest by clicking and dragging the mouse on the image.
4. The `open_img` function is defined to open a file dialog for selecting an image file. Once an image is selected, it is loaded using `cv::imread`, and the original image is displayed in a window named "Image With Water Mark". The user can then select a region of interest by clicking and dragging on the image. The selected region is displayed in a separate window named "Snipped Image". Additionally, a thresholding operation is applied to the image to remove the watermark, and the result is displayed in a window named "Image Without Water Mark".
5. In the `main` function, a GUI window is created using FLTK. The window contains a title label, a "Select" button to open the file dialog, and an "Exit" button to close the application.
6. The `Fl::run()` function is called to start the GUI event loop and display the window.

To compile and run this code, you'll need to have OpenCV and FLTK libraries installed on your system. The compilation command will depend on your specific setup and compiler, but it should be similar to:
g++ -o image_watermark_remover Image_watermark_remover.cpp `fltk-config --cxxflags --ldflags` -lopencv_core -lopencv_highgui -lopencv_imgproc
