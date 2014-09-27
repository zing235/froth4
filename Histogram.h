//////////////////////////////////////////////////////////////////////////
//定义类来进行直方图处理，这个头文件用来定义这个类，并声明类的成员变量，和成员函数;
//////////////////////////////////////////////////////////////////////////
#ifndef HISTOGRAM_H_
#define HISTOGRAM_H_
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>

class Histogram {
private:
	int histSize[1];
	float hrangee[2];
	const float* ranges[1];
	int channels[1];

protected:
	cv::Mat getHistogram(const cv::Mat&);

public:
	Histogram();
	cv::Mat getHistogramImage(const cv::Mat&, int channel = 0);
	cv::Mat stretch1(const cv::Mat& image, int minValue);//对比度增强1，类似于matlab的imadjust
    cv::Mat stretch3(const cv::Mat& image);//直方图均衡化;
};

#endif /* HISTOGRAM_H_ */
