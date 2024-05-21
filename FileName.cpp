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
	
	//dft�� ���� 2ä�� ��Ʈ���� ���� - �Ǽ��� ����� ������ ���ֱ� ���� �ܰ�(�Ǽ��� ������.)
	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
	Mat complexI;	//complexI�� 2ä���� ��ģ Mat��ü ����. CV_32FC2�ϰ����� ����.
	merge(planes, 2, complexI);

	Mat planes_line[] = { Mat_<float>(lineImg), Mat::zeros(lineImg.size(), CV_32F) };
	Mat complexI_line;	//complexI�� 2ä���� ��ģ Mat��ü ����. CV_32FC2�ϰ����� ����.
	merge(planes_line, 2, complexI_line);
	dft(complexI_line, complexI_line);
	split(complexI_line, planes_line);

	Mat magI_line, angI_line;
	getLogMag(planes_line, magI_line, angI_line);
	//log������ ��ģ ������ ũ�⿡ ���ؼ� ����ȭ ����.
	normalize(magI_line, magI_line, 0, 1, NORM_MINMAX);	//float���̹Ƿ� 0���� 1�� ����ȭ ����
	normalize(angI_line, angI_line, 0, 1, NORM_MINMAX);

	magI_line = getshuppling(magI_line);
	imshow("magI_line", magI_line);

	//dft �����ϰ� ä�� �и� planes[0] : �Ǽ���, planes[1] : �����
	dft(complexI, complexI);
	split(complexI, planes);

	Mat magI, angI;
	getLogMag(planes, magI, angI);
	//log������ ��ģ ������ ũ�⿡ ���ؼ� ����ȭ ����.
	normalize(magI, magI, 0, 1, NORM_MINMAX);	//float���̹Ƿ� 0���� 1�� ����ȭ ����
	normalize(angI, angI, 0, 1, NORM_MINMAX);
	magI = getshuppling(magI);	//1-3, 2-4��и� ��ü
	imshow("img", img);
	imshow("pd_img", padded);
	
	imshow("real_�Ǽ�", planes[0]);
	planes[0] = getshuppling(planes[0]);
	imshow("real_�Ǽ�", planes[0]);
	imshow("imaginary_���", planes[1]);
	imshow("ũ��", magI);
	imshow("����", angI);
	//�� Ǫ���� ��ȯ dft(�Է¿���, �Է¿���, �ɼǻ��);
	//split���� �������ְ� ����ȭ ����
	waitKey();
	return 0;
}

//���ݴ� �����ϰ� DFT�� �����ϱ� ���� �غ�ܰ� �̹����� �����κ��� ����� 0���� �ʱ�ȭ
void getZeroPaddedImage(Mat& img, Mat& dst) {	
	int m = getOptimalDFTSize(img.rows);
	int n = getOptimalDFTSize(img.cols);
	copyMakeBorder(img, dst, 0, m - img.rows, 0, n - img.cols, BORDER_CONSTANT, Scalar::all(0));
}
//�Ǽ��ο� ����ηκ��� ũ��� ������ ����ϰ� ũ�⿡ log�� ���ؼ� ������ ���� ����ȭ �ܰ谡 �ʿ�.
void getLogMag(Mat planes[], Mat& magI, Mat& angI) {
	//������ǥ�� ����ǥ��� �X���� �ϴ� �Լ� cartToPolar
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
//���� �߰�
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