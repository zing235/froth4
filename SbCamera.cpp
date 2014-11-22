#include "SbCamera.h"
#include <QPainter>
#include <stdio.h>
#include <vector>

#include "UniControl.h"
#include "UniTransform.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

UINT32_TYPE                 sbcnt(64);
std::vector<UINT32_TYPE>    sbCamIds(sbcnt);
UINT32_TYPE          sbimagewidth,sbimageheight;
QImage sbcameraframe;

#define UINT8P_CAST(x) reinterpret_cast<UINT8*>(x)
//![0]
SbCamera::SbCamera(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
}
//![0]

void SbCamera::startsbcamera(void)
{

    UINT32_TYPE Result;
    UINT32_TYPE depth,Code;

    //1.initial the camera
    Result=UCC_Init();
    if(S_OK!=Result)
        {
            std::cout<<"Can not initial aucamera or aucamera has already initialed"<<endl;
        }
    else
         std::cout<<"sbcamera has already initialed"<<endl;


    // 2.get list of cameras found on the bus;
    Result = UCC_GetCameras(&sbcnt,&*sbCamIds.begin());
    if( S_OK!= Result && UNI_RESULT_MORE_DATA != Result)
    {
        std::cout<<"Get Cameras failed"<<endl;
    }
//    setCameraID(quint32::CamIds[0]);


    //3.OpenCamera(CamIds[0]);
    Result=UCC_OpenCamera(sbCamIds[1]);
    if(S_OK!=Result)
    {
        std::cout<<"Could not openCamera"<<endl;
    }


    //4.GetCurrentImageFormat;
    Result=UCC_GetCurrentImageFormat(sbCamIds[1],&sbimagewidth,&sbimageheight,&Code,&depth);
    if(S_OK!=Result)
    {
        std::cout<<"Could not get image format"<<endl;
    }


    //5.start the image stream
    Result= UCC_GrabStart(sbCamIds[1],1000);
    if(S_OK!=Result)
    {
        std::cout<<"Could not start Grab image"<<endl;
    }


    //6.creat image conventor
    sbcameraframe=QImage(sbimagewidth,sbimageheight,QImage::Format_RGB888);
}

//void SbCamera::getsbimage(void)
//{
//    UCC_GetBitmapImage(sbCamIds[1],UINT8P_CAST(sbcameraframe.bits()),10);
//}

void SbCamera::updatesbcamera(void)
{
    update();
}


void SbCamera::paint(QPainter *painter)
{
    cv::Mat mSbimage(1088, 1388,CV_8UC3);
    UCC_GetBitmapImage(sbCamIds[0],UINT8P_CAST(mSbimage.data),10);
    cv::cvtColor(mSbimage,mSbimage,CV_BGR2RGB);
    sbcameraframe= QImage((const unsigned char*)mSbimage.data,mSbimage.cols,mSbimage.rows,QImage::Format_RGB888);
    painter->drawImage(boundingRect().adjusted(1, 1, -1, -1),sbcameraframe);
 }

quint32 SbCamera::getSbCameraID(void) const
{
    return sbCamIds[1];
}
quint32 SbCamera::getsbimagewidth(void) const
{
    return sbimagewidth;
}
quint32 SbCamera::getsbimageheight(void) const
{
    return sbimageheight;
}

QImage SbCamera::getsbimageframe(void) const
{
    return sbcameraframe;
}

