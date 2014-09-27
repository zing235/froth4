#include "AuCamera.h"
#include <QPainter>
#include <stdio.h>
#include <vector>

#include "UniControl.h"
#include "UniTransform.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
UINT32_TYPE                 aucnt(64);
std::vector<UINT32_TYPE>    auCamIds(aucnt);
UINT32_TYPE          auimagewidth,auimageheight;
QImage aucameraframe;

#define UINT8P_CAST(x) reinterpret_cast<UINT8*>(x)
//![0]
AuCamera::AuCamera(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
}
//![0]

void AuCamera::startaucamera(void)
{

    UINT32_TYPE Result;
    UINT32_TYPE depth,Code;

    //1.initial the camera
    Result=UCC_Init();
    if(S_OK!=Result)
        {
            std::cout<<"Can not initial aucamera or aucamera has already initialed "<<endl;
        }
    else
         std::cout<<"aucamera has already initialed"<<endl;

    // 2.get list of cameras found on the bus;
    Result = UCC_GetCameras(&aucnt,&*auCamIds.begin());
    if( S_OK!= Result && UNI_RESULT_MORE_DATA != Result)
    {
        std::cout<<"Get Cameras failed"<<endl;
    }
//    setCameraID(quint32::CamIds[0]);


    //3.OpenCamera(CamIds[0]);
    Result=UCC_OpenCamera(auCamIds[0]);
    if(S_OK!=Result)
    {
        std::cout<<"Could not openCamera"<<endl;
    }


    //4.GetCurrentImageFormat;
    Result=UCC_GetCurrentImageFormat(auCamIds[0],&auimagewidth,&auimageheight,&Code,&depth);
    if(S_OK!=Result)
    {
        std::cout<<"Could not get image format"<<endl;
    }


    //5.start the image stream
    Result= UCC_GrabStart(auCamIds[0],1000);
    if(S_OK!=Result)
    {
        std::cout<<"Could not start Grab image"<<endl;
    }


    //6.creat image conventor
    aucameraframe=QImage(auimagewidth,auimageheight,QImage::Format_RGB888);//注意颜色rgb-bgr
}

void AuCamera::getauimage(void)
{
    UCC_GetBitmapImage(auCamIds[0],UINT8P_CAST(aucameraframe.bits()),10);
}


void AuCamera::updateaucamera(void)
{

    update();
}


void AuCamera::paint(QPainter *painter)
{

    painter->drawImage(boundingRect().adjusted(1, 1, -1, -1),aucameraframe);
}

quint32 AuCamera::getAuCameraID(void) const
{
    return auCamIds[0];
}
quint32 AuCamera::getauimagewidth(void) const
{
    return auimagewidth;
}
quint32 AuCamera::getauimageheight(void) const
{
    return auimageheight;
}

QImage AuCamera::getauimageframe(void) const
{
    return aucameraframe;
}

