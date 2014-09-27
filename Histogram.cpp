//////////////////////////////////////////////////////////////////////////
//初始化成员变量，定义成员函数的功能，构造函数？;
//////////////////////////////////////////////////////////////////////////

#include "Histogram.h"

Histogram::Histogram() {
	histSize[0] = 256;
	hrangee[0] = 0.0;
	hrangee[1] = 255.0;
	ranges[0] = hrangee;
	channels[0] = 0;
}


cv::Mat Histogram::getHistogram(const cv::Mat& image){
	cv::MatND hist;
	cv::calcHist(&image, 1, channels, cv::Mat(), hist, 1, histSize, ranges);
	return hist;
}


cv::Mat Histogram::getHistogramImage(const cv::Mat& image, int channel){
	std::vector<cv::Mat> planes;
	cv::split(image,planes);
	cv::Scalar color;
	if(planes.size() == 1){
		channel = 0;
		color = cv::Scalar(0,0,0);
	}else{
		color = cv::Scalar(channel==0?255:0, channel==1?255:0, channel==2?255:0);
	}
	cv::MatND hist = getHistogram(planes[channel]);
	double maxVal = 0;
	double minVal = 0;
	cv::minMaxLoc(hist, &minVal, &maxVal, 0, 0);
	cv::Mat histImg(histSize[0], histSize[0], CV_8UC3, cv::Scalar(255,255,255));
	int hpt = static_cast<int>(0.9*histSize[0]);
	for(int h=0; h<histSize[0]-1; h++){
		float binVal = hist.at<float>(h);
		float binVal2 = hist.at<float>(h+1);
		int intensity = static_cast<int>(binVal*hpt/maxVal);
		int intensity2 = static_cast<int>(binVal2*hpt/maxVal);
		cv::line(histImg, cv::Point(h,histSize[0]-intensity),
			cv::Point(h,histSize[0]-intensity2), color);
	}
	return histImg;
}

cv::Mat Histogram::stretch1(const cv::Mat& image, int minValue) {
	cv::MatND hist = getHistogram(image);
	int imin =0;
	for (; imin < histSize[0]; imin++) {
		if (hist.at<float>(imin) > minValue) {
			break;
		}
	}
	int imax = histSize[0] -1;
	for (; imax >=0; imax--) {
		if (hist.at<float>(imax) > minValue) {
			break;
		}
	}
	cv::Mat lookup(cv::Size(1, 256), CV_8U);
	for (int i =0; i <256; i++) {
		if (i < imin) {
			lookup.at<uchar>(i) =0;
		} else if (i > imax) {
			lookup.at<uchar>(i) =255;
		} else {
			lookup.at<uchar>(i) = static_cast<uchar>(255.0* (i - imin)
				/ (imax - imin) +0.5);}
	}
	cv::Mat result;
	cv::LUT(image, lookup, result);
	return result;
}

cv::Mat Histogram::stretch3(const cv::Mat& image) {
	cv::Mat result;
	cv::equalizeHist(image, result);
	return result;
}