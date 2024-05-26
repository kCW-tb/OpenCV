#ifndef _MYLIB_HPP_
#define _MYLIB_HPP_

#include <iostream>
#include <opencv2/opencv.hpp>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <stack>
#include <fstream>
#include <sstream>

using namespace std;
using namespace cv;

const int MAX_STACK_SIZE = 20;

namespace cw {
	void makeCalculatorFrame(Mat& img);
	void on_mouse(int event, int x, int y, int flags, void* userdata);
	void prepare_img(Mat& img);
	void swapRows(Mat& mat, int row1, int row2);
	void bubble_sort_stats(Mat& stats);
	void bubble_sort_centroids(Mat& centroids);
	int findContour(Mat img, Rect area);

	Point getChildContourCenter(Mat img);
	char findOneContourNumber(Mat img);
	char findTwoContourNumber(Mat img);
	char find_PM(Mat img);
	char find_ODM(Mat stats);
	char find_char(Mat img);
	void push_char(Mat img, Mat stats, vector<char>& vec);
	void cout_char(vector<char> vec);

	string makeString(vector<char> vec);
	inline int getCalcChar(char op);
	bool isOperator(char c);
	string infixToPostfix(const string& infix);
	double calculatePostfix(string str);
}

#endif
