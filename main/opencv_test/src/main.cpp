#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;
int main()
{
    std::string image_path = samples::findFile("../../../data/penguin.png");
    Mat img = imread(image_path, IMREAD_COLOR);
    if(img.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }
    imshow("Display window", img);
    int k = waitKey(0); // Wait for a keystroke in the window
    if(k == 's')
    {
        imwrite("starry_night.png", img);
    }
    return 0;
}

// #include<opencv2/opencv.hpp>//OpenCV header to use VideoCapture class//
// #include<iostream>
// using namespace std;
// using namespace cv;
// int main() {
   // Mat myImage;//Declaring a matrix to load the frames//
   // namedWindow("Video Player");//Declaring the video to show the video//
   // VideoCapture cap(0);//Declaring an object to capture stream of frames from default camera//
   // if (!cap.isOpened()){ //This section prompt an error message if no video stream is found//
      // cout << "No video stream detected" << endl;
      // system("pause");
      // return-1;
   // }
   // while (true){ //Taking an everlasting loop to show the video//
      // cap >> myImage;
      // if (myImage.empty()){ //Breaking the loop if no video frame is detected//
         // break;
      // }
      // imshow("Video Player", myImage);//Showing the video//
      // char c = (char)waitKey(25);//Allowing 25 milliseconds frame processing time and initiating break condition//
      // if (c == 27){ //If 'Esc' is entered break the loop//
         // break;
      // }
   // }
   // cap.release();//Releasing the buffer memory//
   // return 0;
// }