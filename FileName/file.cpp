#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

void getZeroPaddedImage(Mat& img, Mat& dst);
Mat getshuppling(Mat img);
void getLogMag(Mat planes[], Mat& magI, Mat& angI);
void addNoise(Mat& img, int nNoise);
void addLine_h(Mat& img, int nLine);
void addLine_w(Mat& img, int nLine);
int main(void) {
	Mat img = imread("C:/Users/AIRLAB/Desktop/img/sky.jpg", 0);
	
	CV_Assert(img.data);
	Mat lineImg = img.clone();
	addLine_w(lineImg, 20);
	imshow("lineImg", lineImg);
	Mat padded;
	getZeroPaddedImage(img, padded);
	getZeroPaddedImage(lineImg, lineImg);
	
	//dft를 위한 2채널 매트릭스 생성 - 실수부 허수부 구별을 해주기 위한 단계(실수는 고정값.)
	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
	Mat complexI;	//complexI에 2채널을 합친 Mat객체 생성. CV_32FC2일것으로 예상.
	merge(planes, 2, complexI);

	Mat planes_line[] = { Mat_<float>(lineImg), Mat::zeros(lineImg.size(), CV_32F) };
	Mat complexI_line;	//complexI에 2채널을 합친 Mat객체 생성. CV_32FC2일것으로 예상.
	merge(planes_line, 2, complexI_line);
	dft(complexI_line, complexI_line);
	split(complexI_line, planes_line);

	Mat magI_line, angI_line;
	getLogMag(planes_line, magI_line, angI_line);
	//log계산까지 마친 각도와 크기에 대해서 정규화 실행.
	normalize(magI_line, magI_line, 0, 1, NORM_MINMAX);	//float형이므로 0부터 1로 정규화 진행
	normalize(angI_line, angI_line, 0, 1, NORM_MINMAX);

	magI_line = getshuppling(magI_line);
	imshow("magI_line", magI_line);

	//dft 수행하고 채널 분리 planes[0] : 실수부, planes[1] : 허수부
	dft(complexI, complexI);
	split(complexI, planes);

	Mat magI, angI;
	getLogMag(planes, magI, angI);
	//log계산까지 마친 각도와 크기에 대해서 정규화 실행.
	normalize(magI, magI, 0, 1, NORM_MINMAX);	//float형이므로 0부터 1로 정규화 진행
	normalize(angI, angI, 0, 1, NORM_MINMAX);
	magI = getshuppling(magI);	//1-3, 2-4사분면 교체
	imshow("img", img);
	imshow("pd_img", padded);
	
	imshow("real_실수", planes[0]);
	planes[0] = getshuppling(planes[0]);
	imshow("real_실수", planes[0]);
	imshow("imaginary_허수", planes[1]);
	imshow("크기", magI);
	imshow("각도", angI);
	//역 푸리에 변환 dft(입력영상, 입력영상, 옵션상수);
	//split으로 분할해주고 정규화 진행
	waitKey();
	return 0;
}

//조금더 세밀하게 DFT를 이행하기 위한 준비단계 이미지의 여유부분이 생기고 0으로 초기화
void getZeroPaddedImage(Mat& img, Mat& dst) {	
	int m = getOptimalDFTSize(img.rows);
	int n = getOptimalDFTSize(img.cols);
	copyMakeBorder(img, dst, 0, m - img.rows, 0, n - img.cols, BORDER_CONSTANT, Scalar::all(0));
}
//실수부와 허수부로부터 크기와 각도를 계산하고 크기에 log를 취해서 돌려줌 이후 정규화 단계가 필요.
void getLogMag(Mat planes[], Mat& magI, Mat& angI) {
	//직교좌표를 극좌표계로 X라라라 하는 함수 cartToPolar
	cartToPolar(planes[0], planes[1], magI, angI, true);
	magI += Scalar::all(1);
	log(magI, magI);

	magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));
}
Mat getshuppling(Mat img) {
	int cx = img.cols / 2;
	int cy = img.rows / 2;
	Mat shuffling(img.size(), img.type());
	Rect rec1(Point(cx, 0), Point(cx * 2, cy));
	Rect rec2(Point(0, 0), Point(cx, cy));
	Rect rec3(Point(0, cy), Point(cx, 2 * cy));
	Rect rec4(Point(cx, cy), Point(cx * 2, 2 * cy));
	img(rec1).copyTo(shuffling(rec3));
	img(rec2).copyTo(shuffling(rec4));
	img(rec3).copyTo(shuffling(rec1));
	img(rec4).copyTo(shuffling(rec2));
	return shuffling;
}

void addNoise(Mat& img, int nNoise) {
	int nGenPoint = 0;
	while (nGenPoint < nNoise) {
		int x = (int)(((float)rand() / RAND_MAX) * img.cols);
		int y = (int)(((float)rand() / RAND_MAX) * img.rows);
		if (x >= img.cols || y >= img.rows) continue;
		if ((float)rand() / RAND_MAX > 0.5) img.at<uchar>(y, x) = 0;
		else img.at<uchar>(y, x) = 255;
		nGenPoint++;
	}
}
//잡음 추가
void addLine_h(Mat& img, int nLine) {
	int height = img.rows / nLine;
	for (int i = 0; i < nLine; i++) {
		int sy = i * height;
		int ey = (i + 1) * height - 1;
		if (ey >= img.rows) ey = img.rows - 1;
		Mat tmp(img, Rect(0, sy, img.cols, (ey - sy + 1)/4));

		if (i % 2 == 0) tmp += Scalar::all(100);
		else tmp += Scalar::all(100);
	}
}
void addLine_w(Mat& img, int nLine) {
	int width = img.cols / nLine;
	for (int i = 0; i < nLine -1; i++) {
		int sx = i * width;
		int ex = (i + 1) * width - 1;
		if (ex >= img.cols) ex = img.cols - 1;
		Mat tmp(img, Rect(sx, 0, 1, img.rows));

		if (i % 2 == 0) tmp = 255;
		else tmp = 255;
	}
}
