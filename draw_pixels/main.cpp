//
//  main.cpp
//  myfirstopencvpro
//
//  Created by mac on 17/3/7.
//  Copyright © 2017年 mac. All rights reserved.
//

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <cv.h>
#include <cxcore.h>
#include <stack>
#include <cmath>
#include <math.h>
using namespace std;
using namespace cv;


int main(int argc, char* argv[])
{
    namedWindow("Test");     //创建一个名为Test窗口
    
    cv::Mat image = cv::imread("/Users/mac/Desktop/university/CST/1718Autumn/4_计原/pic1.png");
    cv::Mat output;
    
    cv::resize(image, image, Size(32,32));
    
    for (int i = 0; i < 32; i++)
        for (int j = 0; j < 32; j++)
        {
            cout << int((int(image.at<cv::Vec3b>(i,j)[0]) / 32)) * 64 + int((int(image.at<cv::Vec3b>(i,j)[1]) / 32)) * 8 + int((int(image.at<cv::Vec3b>(i,j)[2]) / 32)) << endl;
//            cout << int(image.at<cv::Vec3b>(i,j)[0]) << endl;
//            cout << int(image.at<cv::Vec3b>(i,j)[1]) << endl;
//            cout << int(image.at<cv::Vec3b>(i,j)[2]) << endl;
        }

    
    imshow("Test",image);   //窗口中显示图像
    waitKey(); //等待
    
    return 0;
}



