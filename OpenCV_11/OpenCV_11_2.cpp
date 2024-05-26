//number 1
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(void) {
	Mat rect, cross, ellipes;
	rect = getStructuringElement(MORPH_RECT, Size(3, 3));
	cross = getStructuringElement(MORPH_CROSS, Size(3, 3));
	ellipes = getStructuringElement(MORPH_ELLIPSE, Size(5, 3));

	cout << "MORPH_RECT" << endl;
	cout << rect << endl;
	cout << "MORPH_CROSS" << endl;
	cout << cross << endl;
	cout << "MORPH_ELLIPES" << endl;
	cout << ellipes << endl;

	return 0;
}

//number 2
#include <iostream>
#include <opencv2/opencv.hpp>
#include <random>

using namespace std;
using namespace cv;

int main(void) {
	Mat src = imread("C:\\Users\\AIRLAB\\Downloads\\j.png", IMREAD_GRAYSCALE);
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }
	resize(src, src, Size(src.cols * 2, src.rows * 2));
	threshold(src, src, THRESH_BINARY | THRESH_OTSU, 255, CV_8U);
	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			if (rand() % 10 == 1 && src.at<uchar>(i, j) == 255) src.at<uchar>(i, j) = 0;
			else if (rand() % 10 == 1 && src.at<uchar>(i, j) == 0) src.at<uchar>(i, j) = 255;
		}
	}
	imshow("src", src);
	morphologyEx(src, src, MORPH_OPEN, Mat());
	imshow("src2", src);
	morphologyEx(src, src, MORPH_CLOSE, Mat());
	morphologyEx(src, src, MORPH_CLOSE, Mat(9, 9, CV_8UC1));
	imshow("src3", src);
	waitKey();
	destroyAllWindows();
	return 0;
}

//Number 3
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(void) {
	Mat src = imread("C:\\Users\\AIRLAB\\Downloads\\j.png", IMREAD_GRAYSCALE);
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }
	resize(src, src, Size(src.cols * 2, src.rows * 2));
	threshold(src, src, THRESH_BINARY | THRESH_OTSU, 255, CV_8U);
	morphologyEx(src, src, MORPH_GRADIENT, Mat());
	imshow("src", src);
	waitKey();
	return 0;
}

//Number 4
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(void) {
	Mat src = imread("C:\\Users\\AIRLAB\\Downloads\\car.jpg");
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }
	imshow("src", src);
	waitKey(2000);
	blur(src, src, Size(5, 5));
	cvtColor(src, src, COLOR_BGR2GRAY);
	Sobel(src, src, -1, 1, 0);
	imshow("x축 방향 소벨", src);
	waitKey(2000);
	threshold(src, src, 150, 255, CV_8U);
	imshow("이진화 된 영상", src);
	waitKey(2000);
	Mat M = getStructuringElement(MORPH_RECT, Size(50, 5));
	morphologyEx(src, src, MORPH_CLOSE, M);
	morphologyEx(src, src, MORPH_CLOSE, Mat(9, 3, CV_8U));
	imshow("닫힘 연산", src);
	waitKey();
	return 0;
}
