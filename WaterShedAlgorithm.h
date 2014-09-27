
/*
*  Vincent and Soille 分水岭浸没算法(1991)的实现
*/

#ifndef WATERSHEDALGORITHM_H
#define WATERSHEDALGORITHM_H


#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2\opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <string>
#include <queue>
#include "WatershedStructure.h"
using namespace cv;
using namespace std;

class WatershedAlgorithm {
    static const int HMIN = 0;	// 最小层
    static const int HMAX = 256;	// 最大层;

public:
    Mat run( cv::Mat& image) { 
        
		Mat BW;
        adaptiveThreshold(image,BW,255,CV_ADAPTIVE_THRESH_MEAN_C,CV_THRESH_BINARY,31,0);
		/* 获取图像信息; */
        uchar* pixels = image.data;
        int width = image.cols;
        int height = image.rows;

        /* Vincent and Soille 分水岭算法（1991）第一步: 将像素点存入结构体并排序; */
        WatershedStructure  watershedStructure(pixels, width, height);

		/* Vincent and Soille 分水岭算法（1991）第二步: 泛洪（模拟浸没）; */
        /************************ 泛洪（浸没）开始 ****************************/
        std::queue<WatershedPixel*> pque;	// 存储像素的临时队列;
        int curlab = 0;
        int heightIndex1 = 0;
        int heightIndex2 = 0;

        for (int h = HMIN; h < HMAX; ++h) { // h-1 层的 Geodesic SKIZ;

            for (int pixelIndex = heightIndex1 ; pixelIndex < watershedStructure.size() ; ++pixelIndex) {
                WatershedPixel* p = watershedStructure.at(pixelIndex);

				/* 此像素点位于 h+1 层，暂不处理，跳出循环; */
                if (p->getIntHeight() != h) { heightIndex1 = pixelIndex; break; }

                p->setLabelToMASK(); // 标记此像素将被处理;

                std::vector<WatershedPixel*> neighbours = p->getNeighbours();
                for (unsigned i = 0 ; i < neighbours.size() ; ++i) {
                    WatershedPixel* q =  neighbours.at(i);

					 /* 将处于盆地或分水岭的h层的邻接像素点入队; */
                    if (q->getLabel() >= 0) { p->setDistance(1); pque.push(p); break; }
                }
            }

            int curdist = 1;
            pque.push(new WatershedPixel());

            while (true) { // 扩展聚水盆地;
                WatershedPixel* p = pque.front(); pque.pop();

                if (p->isFICTITIOUS())
                {
                    if (pque.empty()) { delete p; p = NULL; break; }
                    else {
                        pque.push(new WatershedPixel());
                        curdist++;
                        delete p; p = pque.front(); pque.pop();
                    }
                }

                std::vector<WatershedPixel*> neighbours = p->getNeighbours();
                for (unsigned i = 0 ; i < neighbours.size() ; ++i) { // 通过检查邻接像素来标记 p;
                    WatershedPixel* q =  neighbours.at(i);

					/* q属于一个存在的盆地或分水线; */ 
                    if ( (q->getDistance() <= curdist) &&  (q->getLabel() >= 0) ) {             

                        if (q->getLabel() > 0) {
                            if ( p->isLabelMASK() )
                                p->setLabel(q->getLabel());
                            else if (p->getLabel() != q->getLabel())
                                p->setLabelToWSHED();
                        } else if (p->isLabelMASK()) 
							p->setLabelToWSHED();
                    } else if ( q->isLabelMASK() && (q->getDistance() == 0) ) {
                        q->setDistance( curdist + 1 );
                        pque.push(q);
                    }
                } // 处理邻接像素的for循环;
            } // 扩展盆地的while循环;

            /* 搜寻并处理h层中新的最小值; */
            for (int pixelIndex = heightIndex2 ; pixelIndex < watershedStructure.size() ; pixelIndex++) {
                WatershedPixel* p = watershedStructure.at(pixelIndex);

				/* 此像素点位于 h+1 层，暂不处理，跳出循环; */
                if (p->getIntHeight() != h) { heightIndex2 = pixelIndex; break; }

                p->setDistance(0); // 重置距离为0

                if (p->isLabelMASK()) { // 该像素位于新最小值区域;
                    curlab++;
                    p->setLabel(curlab);
                    pque.push(p);

                    while (!pque.empty()) {
                        WatershedPixel* q = pque.front();
                        pque.pop();

                        std::vector<WatershedPixel*> neighbours = q->getNeighbours();

                        for (unsigned i = 0 ; i < neighbours.size() ; i++) { // 检查p2的邻域像素
                            WatershedPixel* r =  neighbours.at(i);

                            if ( r->isLabelMASK() ) { r->setLabel(curlab); pque.push(r); }
                        }
                    } // end while
                } // end if
            } // end for
        }
		/************************ 泛洪（浸没）结束 ****************************/

		/* 生成分水线图像; */
		Mat WS(BW.size(),CV_8U,cv::Scalar(0));

        uchar* wsPixels = WS.data;
        uchar* grayPixels =image.data;
		/*
        for (int y = 0; y < height; ++y)
            for (int x = 0; x < width; ++x)
                wsPixels[x + y * width] = (char)0;
		*/

        for (int pixelIndex = 0 ; pixelIndex < watershedStructure.size() ; pixelIndex++) {
            WatershedPixel* p = watershedStructure.at(pixelIndex);

            if (p->isLabelWSHED() && !p->allNeighboursAreWSHED()) {
                wsPixels[p->getX() + p->getY()*width] = (char)255; // 在黑色背景中绘制白色分水线;
                grayPixels[p->getX() + p->getY()*width] = (char)255;	// 在灰度图中绘制白色分水线;
            }
        }
       
//		imshow("分水岭效果;",WS);
		return WS;
    }
};

#endif
