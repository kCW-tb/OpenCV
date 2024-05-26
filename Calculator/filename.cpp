#include "FileName.hpp"

Mat img_c(Size(1200, 500), CV_8UC3, Scalar(0, 0, 0));
Mat calculate_img;
vector<Rect> area;
int area_num;
static string Ans = "";

namespace cw {
    //계산기 그리기
    void makeCalculatorFrame(Mat &img) {
        line(img, Point(0, 70), Point(img.cols, 70), Scalar(255, 255, 255), 3);
        line(img, Point(0, 400), Point(img.cols, 400), Scalar(255, 255, 255), 3);
        line(img, Point(900, 70), Point(900, img.rows), Scalar(255, 255, 255), 3);
        line(img, Point(900, 290), Point(img.cols, 290), Scalar(255, 255, 255), 3);
        line(img, Point(900, 170), Point(img.cols, 170), Scalar(255, 255, 255), 3);
        line(img, Point(img.cols, 0), Point(img.cols, img.rows), Scalar(255, 255, 255), 3);
        line(img, Point(0, img.rows), Point(img.cols, img.rows), Scalar(255, 255, 255), 3);
        line(img, Point(0, 0), Point(0, img.rows), Scalar(255, 255, 255), 3);
        putText(img, "Culculator_CV", Point(10, 60), 
            FONT_HERSHEY_COMPLEX, 2, Scalar(255, 255, 255), 2);
        putText(img, "All Clear", Point(940, 140), 
            FONT_HERSHEY_COMPLEX, 1.5, Scalar(255, 255, 255), 2);
        putText(img, "Ans", Point(1000, 360),
            FONT_HERSHEY_COMPLEX, 1.5, Scalar(255, 255, 255), 2);
        putText(img, "Clear", Point(980, 245), 
            FONT_HERSHEY_COMPLEX, 1.5, Scalar(255, 255, 255), 2);
        putText(img, "=", Point(1020, 470), 
            FONT_HERSHEY_COMPLEX, 1.8, Scalar(255, 255, 255), 2);
        putText(img, "Answer : ", Point(10, 460), 
            FONT_HERSHEY_COMPLEX, 1.2, Scalar(255, 255, 255), 2);
        area.push_back(Rect(Point(901, 169), Point(img.cols - 1, 71)));   //AC <-> 0
        area.push_back(Rect(Point(901, 289), Point(img.cols - 1, 171)));  //Clear <-> 1
        area.push_back(Rect(Point(901, 399), Point(img.cols - 1, 291)));  //Ans <-> 2
        area.push_back(Rect(Point(901, 499), Point(img.cols - 1, 401)));  //= <-> 3
    }
    //마우스 이벤트 처리 함수
    void on_mouse(int event, int x, int y, int flags, void* userdata) {
        Mat clone = (*(Mat*)userdata).clone();
        static Point pt1;
        static Point pt2;
        static double result = 0;
        Mat mouseInsideAC = img_c(area[0]).clone() + Scalar(150, 150, 150);
        Mat mouseInsideC = img_c(area[1]).clone() + Scalar(150, 150, 150);
        Mat mouseInsideAns = img_c(area[2]).clone() + Scalar(150, 150, 150);
        Mat equalsSign = img_c(area[3]).clone() + Scalar(150, 150, 150);

        const static Mat mouseInsideCOrigin = img_c(area[1]).clone();
        const static Mat mouseInsideACOrigin = img_c(area[0]).clone();
        const static Mat mouseInsideAnsOrigin = img_c(area[2]).clone();
        const static Mat equalsSignOrigin = img_c(area[3]).clone();

        if (area[0].contains(Point(x, y)) && !area[0].contains(pt1)) {
            mouseInsideAC.copyTo(img_c(area[0]));
            cout << "ALLCLEAR" << endl;
            imshow("Calculator", img_c);
        }
        else if (!area[0].contains(Point(x, y)) && area[0].contains(pt1)) {
            mouseInsideACOrigin.copyTo(img_c(area[0]));
            cout << "ALLCLEAR END" << endl;
            imshow("Calculator", img_c);
        }
        if (area[1].contains(Point(x, y)) && !area[1].contains(pt1)) {
            cout << "CLEAR" << endl;
            mouseInsideC.copyTo(img_c(area[1]));
            imshow("Calculator", img_c);
        }
        else if (!area[1].contains(Point(x, y)) && area[1].contains(pt1)) {
            mouseInsideCOrigin.copyTo(img_c(area[1]));
            cout << "CLEAR END" << endl;
            imshow("Calculator", img_c);
        }
        if (area[2].contains(Point(x, y)) && !area[2].contains(pt1)) {
            cout << "ANS" << endl;
            mouseInsideAns.copyTo(img_c(area[2]));
            imshow("Calculator", img_c);
        }
        else if (!area[2].contains(Point(x, y)) && area[2].contains(pt1)) {
            cout << "ANS END" << endl;
            mouseInsideAnsOrigin.copyTo(img_c(area[2]));
            imshow("Calculator", img_c);
        }
        if (area[3].contains(Point(x, y)) && !area[3].contains(pt1)) {
            cout << "equalsSign" << endl;
            equalsSign.copyTo(img_c(area[3]));
            imshow("Calculator", img_c);
        }
        else if (!area[3].contains(Point(x, y)) && area[3].contains(pt1)) {
            cout << "equalsSign END" << endl;
            equalsSignOrigin.copyTo(img_c(area[3]));
            imshow("Calculator", img_c);
        }
        switch (event)
        {
        case EVENT_LBUTTONDOWN:
            pt1 = Point(x, y);
            //ALLCLEAR
            if (pt1.inside(area[0])) {
                Ans = "";
                Mat allClear(Size(1200, 500), CV_8UC3, Scalar(0, 0, 0));
                makeCalculatorFrame(allClear);
                allClear.copyTo(img_c);
                imshow("Calculator", img_c); 
                break;
            }
            //CLEAR
            if (pt1.inside(area[1])) {
                Mat img = img_c(Rect(Point(5, 75), Point(898, 398)));
                imwrite("Clear_img.jpg", img);
                cout << "이미지 저장 완료" << endl;
                Mat clear_img = imread("Clear_img.jpg");
                prepare_img(clear_img);
                Mat labels, stats, centroids;
                connectedComponentsWithStats(clear_img, labels, stats, centroids);
                bubble_sort_stats(stats);
                bubble_sort_centroids(centroids);
                cvtColor(clear_img, clear_img, COLOR_GRAY2BGR);
                int* p = stats.ptr<int>(stats.rows - 1);
                Rect a(p[0], p[1], p[2], p[3]);
                clear_img(a) = Scalar(0, 0, 0);
                clear_img.copyTo(img_c(Rect(Point(5, 75), Point(898, 398))));
                cout << clear_img.size() << endl;
                imshow("Calculator", img_c);
                break;
            }
            //Ans
            if (pt1.inside(area[2])) {
                pt2 = Point(x, y);
                break;
            }
            //equalsSign
            if (pt1.inside(area[3])) {
                Mat img = img_c(Rect(Point(5, 75), Point(898, 398)));
                imwrite("Calculator_img.jpg", img);
                cout << "이미지 저장 완료" << endl;
                calculate_img = imread("Calculator_img.jpg");
                prepare_img(calculate_img);
                Mat labels, stats, centroids;
                connectedComponentsWithStats(calculate_img, labels, stats, centroids);
                bubble_sort_stats(stats);
                bubble_sort_centroids(centroids);
                cout << endl;
                vector<char> vec;
                push_char(calculate_img, stats, vec);
                cout_char(vec);
                cout << "vec.size : " << vec.size() << endl;
                string str = makeString(vec);
                cout << "후위연산으로 변경되기 전 string객체 : " << str << endl;
                str = infixToPostfix(str);
                cout << "후위연산으로 변경된 string객체 : " << str << endl;
                result = calculatePostfix(str);
                Ans = result;
                cout << "result 값 : " << result << endl;
                img_c(Rect(210, 410, 250, 65)) = Scalar(0, 0, 0);
                putText(img_c, to_string((int)result), Point(210, 470), 
                    FONT_HERSHEY_SCRIPT_SIMPLEX, 2, Scalar(255, 255, 255), 2);
                img = Scalar(0, 0, 0);
                break;
            }
            break;
        case EVENT_MOUSEMOVE:
            if (flags & EVENT_FLAG_LBUTTON) {
                if (pt2.inside(area[2])) {
                    putText(clone, "Ans", Point(x, y), 
                        FONT_HERSHEY_SIMPLEX, 3, Scalar(255, 255, 255), 3);
                    imshow("Calculator", clone);
                    break;
                }
                line(img_c, pt1, Point(x, y), Scalar(255, 255, 255), 4);
                pt1 = Point(x, y);
                imshow("Calculator", img_c);
            }
        case EVENT_LBUTTONUP:
            if (pt2.inside(area[2])) {
                putText(img_c, "Ans", Point(x, y), 
                    FONT_HERSHEY_SIMPLEX, 2, Scalar(255, 255, 255), 2);
                rectangle(img_c, Rect(x-5, y-50, 115, 60), 
                    Scalar(255, 255, 255),2);
                pt2 = Point(0, 0);
                imshow("Calculator", img_c);
            }
        default:
            pt1 = Point(x, y);
            break;
        }
    }
    //이미지 자체에 대한 전처리 과정
    void prepare_img(Mat& img) {
        cvtColor(img, img, COLOR_BGR2GRAY);
        threshold(img, img, 0, 255, THRESH_BINARY | THRESH_OTSU);
        Mat kernel = getStructuringElement(MORPH_RECT, Size(2, 2));
        morphologyEx(img, img, MORPH_CLOSE, kernel);
    }
    //stats의 객체들을 x좌표에 대해서 순서대로 정렬시키는 함수
    void swapRows(Mat& mat, int row1, int row2) {
        Mat temp = mat.row(row1).clone();
        cout << "row1 : " << mat.row(row1) << "을 ";
        mat.row(row2).copyTo(mat.row(row1));
        cout << "row2 : " << mat.row(row2) << "로 서로 위치 변경" << endl;
        temp.copyTo(mat.row(row2));
        cout << "변경된 row1 : " << mat.row(row1) << endl;
        cout << "변경된 row2 : " << mat.row(row2) << endl << endl;
    }
    void bubble_sort_stats(Mat& stats) {
        int i, j;
        for (i = stats.rows - 1; i > 0; i--) {
            for (j = 1; j < i; j++) {   //배경은 정렬 제외하기 위해 j = 1부터 정렬
                if (stats.at<int>(j, 0) > stats.at<int>(j + 1, 0)) {
                    cout << stats.at<int>(j, 0) << " > " 
                        << stats.at<int>(j + 1, 0)<< endl;
                    swapRows(stats, j, j + 1);
                }
            }
        }
    }
    //centroids의 객체들을 무게중심 x축에 따라서 순서 재정렬 무게중심에 따라변경함
    void bubble_sort_centroids(Mat& centroids) {
        int i, j;
        for (i = centroids.rows - 1; i > 0; i--) {
            for (j = 1; j < i; j++) {   //배경은 정렬 제외하기 위해 j = 1부터 정렬
                if (centroids.at<double>(j, 0) > centroids.at<double>(j + 1, 0)) {
                    swapRows(centroids, j, j + 1);
                }
            }
        }
    }
    //객체 하나의 영역에 있는 외각선의 개수를 구한다.
    int findContour(Mat img, Rect area) {
        Mat fContour = img(area).clone();
        vector<vector<Point>> contours;
        findContours(fContour, contours, RETR_LIST, CHAIN_APPROX_NONE);
        return contours.size();
    }
    int findContourF(Mat img) {
        Mat fContour = img.clone();
        vector<vector<Point>> contours;
        findContours(fContour, contours, RETR_LIST, CHAIN_APPROX_NONE);
        return contours.size();
    }
    //{1, /, -} 3개를 구별하는 함수 외각선이 하나이고 
    //무게중심을 기준으로 제거했을 때 외각선이 2개 이하일 때 시행
    char find_ODM(Mat img) {
        vector<vector<Point>> contours;
        findContours(img, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
        RotatedRect rectRo = minAreaRect(contours[0]); //이거 왜 안되누?
        Size2f rectSize = rectRo.size;
        cout << "회전 사각형의 사이즈 크기 : " << rectSize << endl;
        if (rectSize.width > 20 && rectSize.height > 20) return 'l';
        double get_sc = img.cols / (double)img.rows;    //가로 세로 비율 stats
        if (get_sc < 0.4) return '1';
        else if (get_sc >= 0.4 && get_sc < 1.5) {
            return '/';
        }
        else return '-';
    }
    //+, * 구별 함수
    char find_PM(Mat img) {
        Mat dst, labels, stats, centroids;
        dst = img.clone();
        int num = 1;
        if (dst.cols / (float)dst.rows < 0.4 || 
            dst.cols / (float)dst.rows > 1.5) return 'l';
        Rect remove(Point((dst.cols / 2 - 15), (dst.rows / 2 - 15)),
            Point((dst.cols / 2 + 15), (dst.rows / 2 + 15)));
        cout << "size : " << dst.size << endl;
        cout << "remove area : " << remove << endl;
        dst(remove) = 0;
        num = connectedComponentsWithStats(dst, labels, stats, centroids) - 1;
        if (num == 4) return '+';
        else if (num == 5 || num == 6) return '*';
        else 'l';
    }
    char findOneContourNumber(Mat img) {
        Point centorPoint(img.cols/2, img.rows/2);
        Rect area(centorPoint, Point(img.cols, img.rows));
        int num;
        Mat src = img(area).clone(), labels;
        num = connectedComponents(src, labels) - 1;
        if (num == 2) return '2';
        centorPoint += Point(-10, 0);//센터포인트 수정
        Rect areaLeft(Point(0, 0), Point(centorPoint.x, img.rows));
        src = img.clone();
        Mat empty;  //쓰레기 데이터 입력
        num = connectedComponents(src(areaLeft), empty) - 1;

        if (num == 1) return '7';
        else if (num == 2) return '5';
        else if (num == 3 || num == 4) return '3';
        else return '?';
    }
    //내부 외각선의 무게중심을 반환하는 함수
    Point getChildContourCenter(Mat img) {  
        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;
        findContours(img, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
        Point weightPoint(0, 0);
        for (int i = 0; i < contours[1].size(); i++) {
            weightPoint += contours[1][i];
        }
        weightPoint = Point(weightPoint.x / (float)contours[1].size(),
            weightPoint.y / (float)contours[1].size());
        return weightPoint;
    }
    char findTwoContourNumber(Mat img) { //4,6,9,0판별하는 함수
        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;
        findContours(img, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
        //내부 외각선의 무게중심 좌표
        Point weightPoint(0, 0);
        for (int i = 0; i < contours[1].size(); i++) {
            weightPoint += contours[1][i];
        }
        weightPoint = Point(weightPoint.x / (float)contours[1].size(),
            weightPoint.y / (float)contours[1].size());
        Point weightPointUp = weightPoint + Point(0, -20), 
            weightPointDown = weightPoint - Point(0, -20);
        Rect up(0, weightPointUp.y, img.cols, 2);
        Rect down(0, weightPointDown.y, img.cols, 2);
        Rect right(img.cols / 7 * 5, 0, 2, img.rows);
        Mat scr = img.clone();
        Mat empty;
        cout << "up: " << up << endl;
        cout << "down: " << down << endl;
        cout << "right: " << right << endl;
        int numUp, numDown, numRight;
        numUp = connectedComponents(scr(up), empty) - 1;
        numDown = connectedComponents(scr(down), empty) - 1;
        numRight = connectedComponents(scr(right), empty) - 1;

        if (numUp == 2 && numDown == 2) return '0';
        else if (numUp == 1 && numDown == 2) return '6';
        else {
            if (numRight == 1) return '4';
            else return '9';
        }
    }
    //객체 하나의 대해서 객체를 파악하는 함수 ******* 중요 ********
    char find_char(Mat img) {    //img는 객체 영역을 사각형으로 둘러싼 영역
        //숫자 1, 2, 3, 5, 7 문자 +, -, /, *
        if (findContourF(img) == 1) {
            //1, +, /, *, - 구별 완료
            char PM;
            PM = find_PM(img);
            if (PM == '+') return '+';
            else if (PM == '*') return '*';
            else {
                PM = find_ODM(img);
                if (PM == 'l') PM = 'l';    //아무것도 안하기
                else return PM;
            }
            //2,3,5,7 구별해야함
            char num = findOneContourNumber(img);
            if (num != 'l') return num;
        }
        // 숫자 4, 6, 9, 0
        else if (findContourF(img) == 2) {
            return findTwoContourNumber(img);
        }
        // 숫자 8 완료
        else if (findContourF(img) == 3) {
            return '8';
        }
        // Ans 취급
        else {
            return 'A';
        }
        return 'E';        
    }
    //정렬된 stats 행렬에 대해서 반복하여 char형 vector에 저장할 함수
   void push_char(Mat img, Mat stats, vector<char>& vec) {
        for (int i = 1; i < stats.rows; i++) {
            int* p = stats.ptr<int>(i);
            vec.push_back(find_char(img(Rect(p[0], p[1], p[2], p[3]))));
            cout << "실행 횟수 : " << i << endl;
        }
    }
    void cout_char(vector<char> vec) {
        for (int i = 0; i < vec.size(); i++) {
            cout << i + 1 << "번째 char 객체 : " << vec[i] << endl;
        }
    }

    //띄어쓰기로 구별된 String객체 생성
    string makeString(vector<char> vec) {
        for (int i = 0; i < vec.size(); i++) {
            cout << vec[i] << "\t";
        }
        cout << endl;
        stack<char> st;
        cout << "스택 총 사이즈 : " << st.size() << endl;
        for (int i = 0; i < vec.size(); i++) {
            st.push(vec[i]);
        }
        cout << "수식의 마지막 숫자 : " << st.top() << endl;
        cout << vec.size() << " : 벡터 사이즈" << endl;
        string calcString = "";
        for (int i = 0; i < vec.size(); i++) {
            cout << "st스택 상단의 값 : " << st.top() << endl;
            if (vec[i] == 'A') {
                for (int j = Ans.size() - 1; j >= 0; j--) {
                    calcString.insert(0, string(1, Ans[j]));
                }
                st.pop();
                continue;
            }
            if (st.top() == '+' || st.top() == '-' || 
                st.top() == '/' || st.top() == '*') {
                calcString.insert(0, " ");
                calcString.insert(0, string(1, st.top())); st.pop();
                calcString.insert(0, " ");
            }
            calcString.insert(0, string(1, st.top())); st.pop();
            cout << calcString << " calcString : String으로 객체 변환" << endl;
            if (st.empty()) break;
        }
        cout << calcString << " : makeString function to result" << endl;
        return calcString;
    }
    inline int getCalcChar(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return -1;
    }

    bool isOperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }

    string infixToPostfix(const string& infix) {
        stack<char> s;
        string postfix;
        string currentNum;

        for (char c : infix) {
            if (c == ' ') {
                continue;
            }
            if (isdigit(c)) {
                currentNum += c;
            }
            else {
                if (!currentNum.empty()) {
                    postfix += currentNum + " ";
                    currentNum.clear();
                }

                if (isOperator(c)) {
                    while (!s.empty() && getCalcChar(s.top())
                        >= getCalcChar(c)) {
                        postfix += s.top();
                        postfix += " ";
                        s.pop();
                    }
                    s.push(c);
                }
            }
        }
        if (!currentNum.empty()) {
            postfix += currentNum + " ";
        }
        while (!s.empty()) {
            postfix += s.top();
            postfix += " ";
            s.pop();
        }
        return postfix;
    }



    //후위연산으로 진행하면
    double calculatePostfix(string str) {
        stringstream iss(str);
        string token = "";
        static stack<double> stack;

        while (iss >> token) {
            if ((token != "+") && (token != "-") && 
                (token != "*") && (token != "/")) {
                stack.push(stod(token));
            }
            else if (token == "+") {
                double operand2 = stack.top(); stack.pop();
                double operand1 = stack.top(); stack.pop();
                double result = operand1 + operand2;
                stack.push(result);
            }
            else if (token == "-") {
                double operand2 = stack.top(); stack.pop();
                double operand1 = stack.top(); stack.pop();
                double result = operand1 - operand2;
                stack.push(result);
            }
            else if (token == "*") {
                double operand2 = stack.top(); stack.pop();
                double operand1 = stack.top(); stack.pop();
                double result = operand1 * operand2;
                stack.push(result);
            }
            else if (token == "/") {
                double operand2 = stack.top(); stack.pop();
                double operand1 = stack.top(); stack.pop();
                double result = operand1 / operand2;
                stack.push(result);
            }
            else { }
        }
        return stack.top();
    }
    
}
