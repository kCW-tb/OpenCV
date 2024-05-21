//number1
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
void draw_histo(Mat hist, Mat& hist_img, Size size = Size(256, 100));
void calc_Histo(const Mat& image, Mat& hist, int bins, int range_max);

int main(void) {
    Mat dst, src = imread("D:\\Users\\Admin\\opencv\\camera.bmp");
    Mat hist, hist_img;
    calc_Histo(src, hist, 64, 255);
    draw_histo(hist, hist_img);
    imshow("src", src);
    imshow("hist", hist_img);
    threshold(src, dst, 100, 255, THRESH_BINARY);
    imshow("dst", dst);
    waitKey();
    return 0;
}

void draw_histo(Mat hist, Mat& hist_img, Size size) {
    hist_img = Mat(size, CV_8U, Scalar(255));
    float bin = (float)hist_img.cols / hist.rows;
    normalize(hist, hist, 0, hist_img.rows, NORM_MINMAX);

    for (int i = 0; i < hist.rows; i++) {
	float start_x = i * bin;
	float end_x = (i + 1) * bin;
	Point2f pt1(start_x, 0);
	Point2f pt2(end_x, hist.at<float>(i));

	if (pt2.y > 0)
	    rectangle(hist_img, pt1, pt2, Scalar(0), -1);
    }
    flip(hist_img, hist_img, 0);
}
void calc_Histo(const Mat& image, Mat& hist, int bins, int range_max) {
    int histSize[] = { bins };
    float range[] = { 0, (float)range_max };
    int channels[] = { 0 };
    const float* ranges[] = { range };

    calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges);
    hist.at<int>(0) = 0;
}


//number2
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void draw_histo(Mat hist, Mat& hist_img, Size size = Size(256, 100));
void calc_Histo(const Mat& image, Mat& hist, int bins, int range_max);

int main(void) {
    Mat dst, src = imread("D:\\Users\\Admin\\opencv\\camera.bmp", IMREAD_GRAYSCALE);
    Mat hist, hist_img;
    calc_Histo(src, hist, 64, 255);
    draw_histo(hist, hist_img);
    imshow("src", src);
    imshow("hist", hist_img);
    threshold(src, dst, 0, 255, THRESH_BINARY | THRESH_OTSU);
    imshow("dst", dst);
    waitKey();
    return 0;
}

void draw_histo(Mat hist, Mat& hist_img, Size size) {
    hist_img = Mat(size, CV_8U, Scalar(255));
    float bin = (float)hist_img.cols / hist.rows;
    normalize(hist, hist, 0, hist_img.rows, NORM_MINMAX);

    for (int i = 0; i < hist.rows; i++) {
	float start_x = i * bin;
	float end_x = (i + 1) * bin;
	Point2f pt1(start_x, 0);
	Point2f pt2(end_x, hist.at<float>(i));

	if (pt2.y > 0)
	    rectangle(hist_img, pt1, pt2, Scalar(0), -1);
    }
    flip(hist_img, hist_img, 0);
}
void calc_Histo(const Mat& image, Mat& hist, int bins, int range_max) {
    int histSize[] = { bins };
    float range[] = { 0, (float)range_max };
    int channels[] = { 0 };
    const float* ranges[] = { range };

    calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges);
    hist.at<int>(0) = 0;
}

//number 3
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void draw_histo(Mat hist, Mat& hist_img, Size size = Size(256, 100));
void calc_Histo(const Mat& image, Mat& hist, int bins, int range_max);

int main(void) {
    Mat dst, src = imread("D:\\Users\\Admin\\opencv\\camera.bmp", IMREAD_GRAYSCALE);
    Mat hist, hist_img;
    calc_Histo(src, hist, 64, 255);
    draw_histo(hist, hist_img);
    imshow("src", src);
    imshow("hist", hist_img);
    adaptiveThreshold(src, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 9, 2);
    imshow("dst", dst);
    waitKey();
    return 0;
}

void draw_histo(Mat hist, Mat& hist_img, Size size) {
    hist_img = Mat(size, CV_8U, Scalar(255));
    float bin = (float)hist_img.cols / hist.rows;
    normalize(hist, hist, 0, hist_img.rows, NORM_MINMAX);

    for (int i = 0; i < hist.rows; i++) {
	float start_x = i * bin;
	float end_x = (i + 1) * bin;
	Point2f pt1(start_x, 0);
	Point2f pt2(end_x, hist.at<float>(i));

	if (pt2.y > 0)
	    rectangle(hist_img, pt1, pt2, Scalar(0), -1);
    }
    flip(hist_img, hist_img, 0);
}
void calc_Histo(const Mat& image, Mat& hist, int bins, int range_max) {
    int histSize[] = { bins };
    float range[] = { 0, (float)range_max };
    int channels[] = { 0 };
    const float* ranges[] = { range };

    calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges);
    hist.at<int>(0) = 0;
}

//number 4
#include <iostream> 
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
void draw_histo(Mat hist, Mat& hist_img, Size size = Size(256, 100));
void calc_Histo(const Mat& image, Mat& hist, int bins, int range_max);

int main(void) {
    Mat dst;
    VideoCapture cap("D:\\Users\\AIRLAB\\source\\repos\\line.mp4");
    if (!cap.isOpened()) { cerr << "mp4 loaded failed"; return -1; }
    Mat hist, hist_img;
    while (true) {
	Mat src, frame;
	cap >> frame;
	src = frame(Rect(160, 260, 200, 90));
	resize(src, src, Size(400, 180));
	cvtColor(src, src, COLOR_BGR2GRAY);
	calc_Histo(src, hist, 64, 255);
	draw_histo(hist, hist_img);
	imshow("src", src);
	imshow("hist", hist_img);
	threshold(src, dst, 190, 255, THRESH_BINARY);
	cvtColor(dst, dst, COLOR_GRAY2BGR);
	imshow("dst", dst);
	waitKey(30);
    }
    return 0;
}

void draw_histo(Mat hist, Mat& hist_img, Size size) {
    hist_img = Mat(size, CV_8U, Scalar(255));
    float bin = (float)hist_img.cols / hist.rows;
    normalize(hist, hist, 0, hist_img.rows, NORM_MINMAX);

    for (int i = 0; i < hist.rows; i++) {
	float start_x = i * bin;
	float end_x = (i + 1) * bin;
	Point2f pt1(start_x, 0);
	Point2f pt2(end_x, hist.at<float>(i));

	if (pt2.y > 0)
	    rectangle(hist_img, pt1, pt2, Scalar(0), -1);
    }
    flip(hist_img, hist_img, 0);
}

void calc_Histo(const Mat& image, Mat& hist, int bins, int range_max) {
    int histSize[] = { bins };
    float range[] = { 0, (float)range_max };
    int channels[] = { 0 };
    const float* ranges[] = { range };

    calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges);
    hist.at<int>(0) = 0;
}
