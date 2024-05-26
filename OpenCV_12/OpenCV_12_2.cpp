//Number 1
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;
int main(void)
{
    Mat src = imread("D:/Users/AIRLAB/source/repos/polygon.bmp");
    Mat dst = src.clone();
    if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }
    cvtColor(src, src, COLOR_BGR2GRAY);
    threshold(src, src, 150, 255, THRESH_BINARY_INV);
    vector<vector<Point>> contours;
    findContours(src, contours, RETR_LIST, CHAIN_APPROX_NONE);
    for (int i = 0; i < contours.size(); i++) {
        Scalar c(rand() & 255, rand() & 255, rand() & 255);
        drawContours(dst, contours, i, c, 2);
    }
    imshow("src", src);
    imshow("dst", dst);
    waitKey(0);
    return 0;
}

//Number 2
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;
int main() {
    uchar data[] = {
    0, 0, 1, 1, 0, 0, 0, 0,
    1, 1, 1, 1, 0, 0, 1, 0,
    1, 1, 1, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 1, 0,
    0, 0, 0, 1, 1, 1, 1, 0,
    0, 0, 0, 1, 0, 0, 1, 0,
    0, 0, 1, 1, 1, 1, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    };
    Mat src = Mat(8, 8, CV_8UC1, data) * 255;
    Mat labels;
    vector<vector<Point>> contours;
    findContours(src, contours, RETR_LIST, CHAIN_APPROX_NONE);
    cout << "외각선의 갯수: " << contours.size() << endl;
    for (int i = 0; i < contours.size(); i++) {
        cout << i << "번째 외각선의 점의 좌표 : " << endl;
        for (int j = 0; j < contours[i].size(); j++) {
            cout << contours[i][j];
            if (j != contours[i].size() - 1) cout << ",";
            else cout << endl;
        }
    }
    return 0;
}

//Number 3
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;
int main(void)
{
    Mat src = imread("D:/Users/AIRLAB/source/repos/labelex.png");
    Mat dst = src.clone();
    if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }
    cvtColor(src, src, COLOR_BGR2GRAY);
    threshold(src, src, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
    vector<vector<Point>> contours;
    findContours(src, contours, RETR_LIST, CHAIN_APPROX_NONE);
    for (int i = 0; i < contours.size(); i++) {
        Scalar c(rand() & 255, rand() & 255, rand() & 255);
        for (int j = 0; j < contours[i].size(); j++) {
            line(dst, contours[i][j], contours[i][(j + 1) % contours[i].size()], c, 2);
        }
    }
    imshow("src", src);
    imshow("dst", dst);
    waitKey(0);
    return 0;
}

//Number 4
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;
int main(void)
{
    Mat src = imread("D:/Users/AIRLAB/source/repos/labelex.png");
    Mat dst = src.clone();
    if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }
    cvtColor(src, src, COLOR_BGR2GRAY);
    threshold(src, src, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
    vector<vector<Point>> contours;
    findContours(src, contours, RETR_LIST, CHAIN_APPROX_NONE);
    int maxindex = 0;
    for (int i = 0; i < contours.size(); i++) {
        cout << i << "번째 외각선 길이 : " << contours[i].size() << endl;
        if (contours[i].size() >= contours[maxindex].size()) maxindex = i;
    }
    drawContours(dst, contours, maxindex, Scalar(0, 0, 255), 2);
    imshow("src", src);
    imshow("dst", dst);
    waitKey(0);
    return 0;
}

//Number 5
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;
int main() {
    Mat src = imread("D:/Users/AIRLAB/source/repos/char_c.png", IMREAD_GRAYSCALE);
    Mat dst = src.clone();
    threshold(src, src, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
    cvtColor(dst, dst, COLOR_GRAY2BGR);

    Mat labels, stats, centroids;
    int c = connectedComponentsWithStats(src, labels, stats, centroids);

    int* c11 = stats.ptr<int>(1);
    int* c12 = stats.ptr<int>(2);

    //C1과 C2에 대한 Rect영역
    Rect c1(c11[0] - 1, c11[1] - 1, c11[2] + 3, c11[3] + 3), c2(c12[0] - 1, c12[1] - 1, c12[2] + 3, c12[3] + 3);

    //C1에 대해서 왼쪽 오른쪽 박스 영역
    Rect c1r(c11[0] + c11[2] / 2 - 1, c11[1] - 1, c11[2] / 2 + 3, c11[3] + 3),
        c1l(c11[0] - 1, c11[1] - 1, c11[2] / 2 + 3, c11[3] + 3);

        //C2에 대해서 왼쪽 오른쪽 박스 영역
    Rect c2r(c12[0] + c12[2] / 2 - 1, c12[1] - 1, c12[2] / 2 + 3, c12[3] + 3),
        c2l(c12[0] - 1, c12[1] - 1, c12[2] / 2 + 3, c12[3] + 3);

    int c1ll, c1rr, c2ll, c2rr;

    c1ll = connectedComponents(src(c1l), labels);    //왼쪽
    c1rr = connectedComponents(src(c1r), labels);    //오른쪽
    c2ll = connectedComponents(src(c2l), labels);    //왼쪽
    c2rr = connectedComponents(src(c2r), labels);    //오른쪽

    if (c1ll == 3) {
        vector<vector<Point>> object_left;
        findContours(src(c1), object_left, RETR_LIST, CHAIN_APPROX_NONE);
        drawContours(dst(c1), object_left, 0, Scalar(255, 0, 0), 2);
    }
    if (c1rr == 3) {
        vector<vector<Point>> object_right;
        findContours(src(c1), object_right, RETR_LIST, CHAIN_APPROX_NONE);
        drawContours(dst(c1), object_right, 0, Scalar(0, 0, 255), 2);
    }
    if (c2ll == 3) {
        vector<vector<Point>> object_left;
        findContours(src(c2), object_left, RETR_LIST, CHAIN_APPROX_NONE);
        drawContours(dst(c2), object_left, 0, Scalar(255, 0, 0), 2);
    }
    if (c2rr == 3) {
        vector<vector<Point>> object_right;
        findContours(src(c2), object_right, RETR_LIST, CHAIN_APPROX_NONE);
        drawContours(dst(c2), object_right, 0, Scalar(0, 0, 255), 2);
    }

    imshow("src", src);
    imshow("dst", dst);
    waitKey();

    return 0;
}

