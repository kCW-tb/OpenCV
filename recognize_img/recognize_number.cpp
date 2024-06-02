#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace cv::dnn;
using namespace std;

Mat save_black = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Save_black.jpg");
Mat save_red = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Save_red.jpg");
Mat load_black = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Load_black.jpg");
Mat load_red = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Load_red.jpg");
Mat clear_black = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Clear_black.jpg");
Mat clear_red = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Clear_red.jpg");
Mat run_black = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Run_black.jpg");
Mat run_red = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Run_red.jpg");
Mat exit_black = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Exit_black.jpg");
Mat exit_red = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Exit_red.jpg");

void copyimg(Mat& img, Rect area, Mat& copy);
Mat drawLineImg();
void turn_menu_color(Mat board);
void on_mouse(int event, int x, int y, int flags, void* userdata);

int main(void)
{
    Mat img = drawLineImg();
    char c;
    namedWindow("NUMBER");
    while (true) {
        setMouseCallback("NUMBER", on_mouse, &img);
        imshow("NUMBER", img);
        c = waitKey(1);
        if (c == 27) break;
    }
    return 0;
}

void copyimg(Mat& img, Rect area, Mat& copy) {
    resize(copy, copy, Size(120, 70));
    Point start(area.x, area.y);
    start.x += (area.width - copy.cols) / 2;
    start.y += (area.height - copy.rows) / 2;

    copy.copyTo(img(Rect(start.x, start.y, copy.cols, copy.rows)));
}

Mat drawLineImg() {
    Mat board(500, 650, CV_8UC3, Scalar(255, 255, 255));
    rectangle(board, Rect(0, 0, 500, 650), Scalar(0, 0, 0), 2);
    rectangle(board, Rect(500, 0, 150, 100), Scalar(0, 0, 0), 2);       //Save  Rect(500, 0, 150, 100)
    rectangle(board, Rect(500, 100, 150, 100), Scalar(0, 0, 0), 2);     //Load  Rect(500, 100, 150, 100)
    rectangle(board, Rect(500, 200, 150, 100), Scalar(0, 0, 0), 2);     //Clear Rect(500, 200, 150, 100)
    rectangle(board, Rect(500, 300, 150, 100), Scalar(0, 0, 0), 2);     //Run   Rect(500, 300, 150, 100)
    rectangle(board, Rect(500, 400, 150, 100), Scalar(0, 0, 0), 2);     //Exit  Rect(500, 400, 150, 100)
    
    copyimg(board, Rect(500, 0, 150, 100), save_black);
    copyimg(board, Rect(500, 100, 150, 100), load_black);
    copyimg(board, Rect(500, 200, 150, 100), clear_black);
    copyimg(board, Rect(500, 300, 150, 100), run_black);
    copyimg(board, Rect(500, 400, 150, 100), exit_black);
    
    return board;
}
void turn_menu_color(Mat board) {
    copyimg(board, Rect(500, 0, 150, 100), save_black);
    copyimg(board, Rect(500, 100, 150, 100), load_black);
    copyimg(board, Rect(500, 200, 150, 100), clear_black);
    copyimg(board, Rect(500, 300, 150, 100), run_black);
    copyimg(board, Rect(500, 400, 150, 100), exit_black);
}

void on_mouse(int event, int x, int y, int flags, void* userdata) {
    static Point prePoint = Point(0, 0);
    Rect save(500, 0, 148, 100), load(500, 100, 148, 100), clear(500, 200, 148, 100), run(500, 300, 148, 100), exit_f(500, 400, 148, 100);
    if (Point(x, y).inside(save)) {
        turn_menu_color(*(Mat*)userdata);
        copyimg(*(Mat*)userdata, save, save_red);
    }
    else if (Point(x, y).inside(load)) {
        turn_menu_color(*(Mat*)userdata);
        copyimg(*(Mat*)userdata, load, load_red);
    }
    else if (Point(x, y).inside(clear)) {
        turn_menu_color(*(Mat*)userdata);
        copyimg(*(Mat*)userdata, clear, clear_red);
    }
    else if (Point(x, y).inside(run)) {
        turn_menu_color(*(Mat*)userdata);
        copyimg(*(Mat*)userdata, run, run_red);
    }
    else if (Point(x, y).inside(exit_f)) {
        turn_menu_color(*(Mat*)userdata);
        copyimg(*(Mat*)userdata, exit_f, exit_red);
    }
    else {
        turn_menu_color(*(Mat*)userdata);
    }

    switch (event) {
    case EVENT_LBUTTONDOWN:
        prePoint = Point(x, y);
        if (Point(x, y).inside(Rect(500, 300, 150, 100))) {
            //RUN
        }
        else if (Point(x, y).inside(Rect(500, 0, 150, 100))) {
            //Save
            string fileName = "";
            Mat save = (*(Mat*)userdata)(Rect(1, 1, 498, 498)).clone();
            resize(save, save, Size(500, 500));
            cout << "input fileName : ";
            cin >> fileName;
            fileName += ".jpg";
            imwrite(fileName, save);
            cout << fileName << " saved file" << endl;
        }
        else if (Point(x, y).inside(Rect(500, 100, 150, 100))) {
            //Load
            string fileName = "";
            cout << "input fileName : ";
            cin >> fileName;
            fileName += ".jpg";
            Mat number = imread(fileName);
            rectangle(number, Rect(0, 0, 500, 500), Scalar(0, 0, 0), 2);
            number.copyTo((*(Mat*)userdata)(Rect(0, 0, 500, 500)));
        }
        else if (Point(x, y).inside(Rect(500, 200, 150, 100))) {
            //Clear
            (*(Mat*)userdata)(Rect(1, 1, 498, 498)) = Scalar(255, 255, 255);
        }
        else if (Point(x, y).inside(Rect(500, 400, 150, 100))) {
            //Exit
            exit(1);
        }
        break;
    case EVENT_MOUSEMOVE:
        if (!Rect(1, 1, 498, 498).contains(Point(x, y))) break;
        if (flags == EVENT_FLAG_LBUTTON) {
            line(*(Mat*)userdata, prePoint, Point(x, y), Scalar(0, 0, 0), 3);
            prePoint = Point(x, y);
        }
        else if (flags == EVENT_FLAG_CTRLKEY) {
            line(*(Mat*)userdata, prePoint, Point(x, y), Scalar(255, 255, 255), 10);
            prePoint = Point(x, y);
        }
        break;
    case EVENT_LBUTTONUP:
        prePoint = Point(x, y);
        break;
    default:
        break;
    }
    imshow("NUMBER", *(Mat*)userdata);
}
