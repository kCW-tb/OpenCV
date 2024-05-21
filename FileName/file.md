# 주제
## 주제
### 주제

  Mat img = imread("C:/Users/AIRLAB/Desktop/img/sky.jpg", 0);
	
	  CV_Assert(img.data);
	  Mat lineImg = img.clone();
	  addLine_w(lineImg, 20);
	  imshow("lineImg", lineImg);
	  Mat padded;
	  getZeroPaddedImage(img, padded);
	  getZeroPaddedImage(lineImg, lineImg);
