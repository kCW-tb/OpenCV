#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace cv::dnn;
using namespace std;


Mat drawLineImg();
void wrigt_number(Mat board);
void on_mouse(int event, int x, int y, int flags, void* userdata);

int main(void)
{
    Mat img = drawLineImg();
    namedWindow("NUMBER");
    setMouseCallback("NUMBER", on_mouse, &img);

    imshow("NUMBER", img);
    waitKey();
    return 0;
}


Mat drawLineImg() {
    Mat board(500, 650, CV_8UC3, Scalar(255, 255, 255));
    rectangle(board, Rect(0, 0, 500, 650), Scalar(0, 0, 0), 2);
    rectangle(board, Rect(500, 0, 150, 100), Scalar(0, 0, 0), 2);       //Save  Rect(500, 0, 150, 100)
    rectangle(board, Rect(500, 100, 150, 100), Scalar(0, 0, 0), 2);     //Load  Rect(500, 100, 150, 100)
    rectangle(board, Rect(500, 200, 150, 100), Scalar(0, 0, 0), 2);     //Clear Rect(500, 200, 150, 100)
    rectangle(board, Rect(500, 300, 150, 100), Scalar(0, 0, 0), 2);     //Run   Rect(500, 300, 150, 100)
    rectangle(board, Rect(500, 400, 150, 100), Scalar(0, 0, 0), 2);     //Exit  Rect(500, 400, 150, 100)
    putText(board, "Save", Point(535, 65), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0), 2);
    putText(board, "Load", Point(525, 165), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0), 2);
    putText(board, "Clear", Point(535, 265), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0), 2);
    putText(board, "Run", Point(545, 365), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0), 2);
    putText(board, "Exit", Point(545, 465), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0), 2);
    return board;
}
void wrigt_number(Mat board) {
    board(Rect(501, 1, 148, 98)) = Scalar(255, 255, 255);
    board(Rect(501, 101, 148, 98)) = Scalar(255, 255, 255);
    board(Rect(501, 201, 148, 98)) = Scalar(255, 255, 255);
    board(Rect(501, 301, 148, 98)) = Scalar(255, 255, 255);
    board(Rect(501, 401, 148, 98)) = Scalar(255, 255, 255);
    putText(board, "Save", Point(535, 65), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0), 2);
    putText(board, "Load", Point(525, 165), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0), 2);
    putText(board, "Clear", Point(535, 265), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0), 2);
    putText(board, "Run", Point(545, 365), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0), 2);
    putText(board, "Exit", Point(545, 465), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0), 2);
}

void on_mouse(int event, int x, int y, int flags, void* userdata) {
    static Point prePoint = Point(0, 0);
    
    if (Point(x, y).inside(Rect(500, 0, 148, 100))) {
        wrigt_number(*(Mat*)userdata);
        (*(Mat*)userdata)(Rect(501, 1, 148, 98)) = Scalar(255, 255, 255);
        putText(*(Mat*)userdata, "Save", Point(535, 65), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 3);
    }
    else if (Point(x, y).inside(Rect(500, 100, 148, 100))) {
        wrigt_number(*(Mat*)userdata);
        (*(Mat*)userdata)(Rect(501, 101, 148, 98)) = Scalar(255, 255, 255);
        putText(*(Mat*)userdata, "Load", Point(525, 165), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 3);
    }
    else if (Point(x, y).inside(Rect(500, 200, 148, 100))) {
        wrigt_number(*(Mat*)userdata);
        (*(Mat*)userdata)(Rect(501, 201, 148, 98)) = Scalar(255, 255, 255);
        putText(*(Mat*)userdata, "Clear", Point(535, 265), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 3);
    }
    else if (Point(x, y).inside(Rect(500, 300, 148, 100))) {
        wrigt_number(*(Mat*)userdata);
        (*(Mat*)userdata)(Rect(501, 301, 148, 98)) = Scalar(255, 255, 255);
        putText(*(Mat*)userdata, "Run", Point(545, 365), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 3);
    }
    else if (Point(x, y).inside(Rect(500, 400, 148, 100))) {
        wrigt_number(*(Mat*)userdata);
        (*(Mat*)userdata)(Rect(501, 401, 148, 98)) = Scalar(255, 255, 255);
        putText(*(Mat*)userdata, "Exit", Point(545, 465), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 3);
    }
    else {
        wrigt_number(*(Mat*)userdata);
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
