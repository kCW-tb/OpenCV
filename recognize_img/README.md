black imgs

![Clear_black](https://github.com/kCW-tb/OpenCV/assets/71691159/b8e28a49-328b-4b33-9fc6-6b7ecf8ec6de)

![Exit_black](https://github.com/kCW-tb/OpenCV/assets/71691159/ebc62b26-dfc6-4c2f-988b-13df278c967b)

![Load_black](https://github.com/kCW-tb/OpenCV/assets/71691159/7e2b4183-b0e5-4230-8b6e-aa19c5d7d85b)

![Run_black](https://github.com/kCW-tb/OpenCV/assets/71691159/fc3bf236-d2b1-468a-91b4-1fca3e1c91e3)

![Save_black](https://github.com/kCW-tb/OpenCV/assets/71691159/9d2b9a85-e75c-4bf4-ac62-35cc745ab93b)


red imgs

![Clear_red](https://github.com/kCW-tb/OpenCV/assets/71691159/5c776354-f094-4d51-bd90-75a7280e242d)

![Exit_red](https://github.com/kCW-tb/OpenCV/assets/71691159/2a30bf2e-d84b-4f06-9d93-8844590278fb)

![Load_red](https://github.com/kCW-tb/OpenCV/assets/71691159/d05e0427-97b6-4835-a55d-ba95944c6580)

![Run_red](https://github.com/kCW-tb/OpenCV/assets/71691159/aeca7b30-80da-4c1c-90a8-ced76305fa2f)

![Save_red](https://github.com/kCW-tb/OpenCV/assets/71691159/0fddf149-2770-476c-816e-b8ccc746c6d9)


코드 설명
```
Mat save_black = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Save_black.jpg");
Mat save_red = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Save_red.jpg");
Mat load_black = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Load_black.jpg");
Mat load_red = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Load_red.jpg");
Mat clear_black = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Clear_black.jpg");
Mat clear_red = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Clear_red.jpg");
Mat run_black = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Run_black.jpg");
Mat run_red = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Run_red.jpg");
Mat exit_black = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Exit_black.jpg");
Mat exit_red = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Exit_red.jpg");
```

위 이미지들을 저장하는 전역 Mat 객체


```
void copyimg(Mat& img, Rect area, Mat& copy) {
    resize(copy, copy, Size(120, 70));
    Point start(area.x, area.y);
    start.x += (area.width - copy.cols) / 2;
    start.y += (area.height - copy.rows) / 2;

    copy.copyTo(img(Rect(start.x, start.y, copy.cols, copy.rows)));
}
```

이미지들을 변경시키기 위한 코드로 img의 일정 영역 area에 copy Mat객체를 중앙에 위치하게 하여 적용시킨다.
이미지들에 대해 일일이 크기를 조정하는 것을 보완하기 위해 resize로 크기를 통일시켜 주었다.


```
Mat drawLineImg();
void turn_menu_color(Mat board);
```

위 두 함수는 기본 틀을 그리는 함수와 menu에 대해서 Rect영역을 나갔을 때 초기화 시켜주기 위한 코드이다.


```
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
```

왼쪽 마우스가 내려가는 이벤트가 발생했을 시 코드로 Save는 이름을 작성하면 string객체에서 .jpg를 붙혀 imwrite를 통해 해당 디렉토리에 이미지가 적용되게 하였고 호출 역시 동일한 방식으로 호출하였다. Rect영역을 조정해주어 숫자영역에 대해서만 저장 및 호출이 되도록 하였다.

Clear의 영역이 눌렸을 때에는 해당 영역의 픽셀을 모두 Scalar(255, 255, 255)로 초기화시켜주었다.
Exit의 영역이 눌렸을 때에는 exit(1)을 통해 프로그램을 종료시키도록 하였다.


[기본 틀 작동 영상](https://youtu.be/yHq14nihd5s)
