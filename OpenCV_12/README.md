OpenCV Chapter 12

Chapter 12_1

Chapter 12_2

12_2_1
ploygon.bmp 영상 파일에서 객체의 외각선을 그려주는 프로그램 작성

![12_2_1](https://github.com/kCW-tb/OpenCV/assets/71691159/044b4fd5-9d8f-4bc4-be3e-68c252f9b504)


12_2_2
Mat 객체에 저장된 영상에 대하여 외각선을 구성하는 점들을 출력

![12_2_2](https://github.com/kCW-tb/OpenCV/assets/71691159/fca71465-c2f3-4315-a447-a99c44fda3c8)


12_2_3
labelex.png 영상 파일에서 cv::drawContours() 함수를 사용하지 않고 외각선을 그리는 프로그램 작성

![12_2_3](https://github.com/kCW-tb/OpenCV/assets/71691159/5ae0492c-2d32-4db1-bfc9-c8c3fbeaf4d5)


12_2_4
labelex.png 영상 파일에서 외각선의 길이를 출력하고 외각선의 길이가 가장 큰 외각선을 그리는 프로그램 작성

![12_2_4](https://github.com/kCW-tb/OpenCV/assets/71691159/3a1d86b2-dae3-4a27-b71f-ddd86c26130a)


12_2_5
O 의 뚫린 방향이 왼쪽이면 파란색 외각선을 오른쪽이면 붉은색 외각선을 그리는 프로그램 작성

![12_2_5](https://github.com/kCW-tb/OpenCV/assets/71691159/f7c043f6-2639-446b-83ec-06dc09e49531)

Chapter 12_3

12_3_1
기울어진 베타에 대해 바운딩 박스를 그리시오.

![image](https://github.com/kCW-tb/OpenCV/assets/71691159/55b49ce4-afe6-41c3-a9e6-ab0893024916)


12_3_2
기울어진 A에 대해 문자의 기울어진 각도를 찾아 옳바른 형태로 고치시오.

![image](https://github.com/kCW-tb/OpenCV/assets/71691159/9349306b-fef1-4098-9280-4b8f5c9ad940)


12_3_3
영상 파일에 대해서 삼각형, 사각형, 오각형, 육각형, 원의 개수를 각각 구하여 콘솔창에 출력하고 외각선 표현

![image](https://github.com/kCW-tb/OpenCV/assets/71691159/1f6c5cfe-fff7-4548-9373-fb5bd9a285e2)


12_3_4
영상 파일에 대해서 사각형, 원, 삼각형의 면적과 외각선의 길이 출력

![image](https://github.com/kCW-tb/OpenCV/assets/71691159/f8c75f66-4868-4ccd-b26e-d63a7668ed6f)


12_3_5
타원에서 외각선을 검출하고 빨간색으로 그리고 외각선을 근사화한 후 근사화한 외각선을 파란색으로 그리시오.
외각선의 길이, 면적을 출력하시오.
타원에 더 근접하게 근사화하기 위한 조건은?

![image](https://github.com/kCW-tb/OpenCV/assets/71691159/0353fea2-1338-4d1f-9fc2-0237d964a522)


![image](https://github.com/kCW-tb/OpenCV/assets/71691159/b042f7e5-1332-4fd7-840e-f89bc05703b8)

더 근사화하기 위한 조건은 approxPolyDP에서 3번째 매개변수인 epsilon 파라미터를 조정
epsilon의 값이 낮을수록 원형에 근사화된다.
