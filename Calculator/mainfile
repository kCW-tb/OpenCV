#include "FileName.hpp"

extern Mat img_c;
extern vector<Rect> area;
extern Mat calculate_img;

int main(void) {
	char c = 'n';
	while (true) {
		CV_Assert(img_c.data);
		cw::makeCalculatorFrame(img_c);
		namedWindow("Calculator");
		setMouseCallback("Calculator", cw::on_mouse, &img_c);
		imshow("Calculator", img_c);
		c = waitKey();
		if (c != 'n') return 0;
	}

	return 0;
}
