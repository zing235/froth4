#include "ImageValue.h"
#include <opencv2/opencv.hpp>
#include"Histogram.h"
#include"WaterShedAlgorithm.h"
#include"WatershedPixel.h"
#include"WatershedStructure.h"
#include <QUrl>
#include <QImage>
#include"AuCamera.h"
#include"SbCamera.h"
#include "connectsql.h"
#include "UniControl.h"
#include "UniTransform.h"
#define UINT8P_CAST(x) reinterpret_cast<UINT8*>(x)
#pragma execution_character_set("utf-8")

double sbGlobleBubbleNumber=0;
double sbGlobleBubbleSize=0;
double sbGlobleGrayMean=0;
double sbsumgrayvalue=0;
int sbGlobleSbGrade=0;

double auGlobleBubbleNumber=0;
double auGlobleBubbleSize=0;
double auGlobleGrayMean=0;
double ausumgrayvalue=0;


ImageValue::ImageValue(QObject *parent):
    QObject(parent),m_sbBubbleNumber("Number"),m_sbBubbleSize("Size"),m_sbGrayMean("Mean"),m_auBubbleNumber("Number"),m_auBubbleSize("Size"),m_auGrayMean("Mean"),m_SbGrade(0),m_ZhidaoYaoji(),m_YaojiList()
{
}
QString ImageValue::getsbBubbleNumber(void) const
{
    return m_sbBubbleNumber;
}
void ImageValue::setsbBubbleNumber(const QString sbBubbleNumber)
{
    m_sbBubbleNumber=sbBubbleNumber;
    emit sbBubbleNumberChanged();
}

QString ImageValue::getsbBubbleSize(void) const
{
    return m_sbBubbleSize;
}
void ImageValue::setsbBubbleSize(const QString sbBubbleSize)
{
    m_sbBubbleSize=sbBubbleSize;
    emit sbBubbleSizeChanged();
}

QString ImageValue::getsbGrayMean(void) const
{
    return m_sbGrayMean;
}
void ImageValue::setsbGrayMean(const QString sbGrayMean)
{
    m_sbGrayMean=sbGrayMean;
    emit sbGrayMeanChanged();
}


QString ImageValue::getauBubbleNumber(void) const
{
    return m_auBubbleNumber;
}
void ImageValue::setauBubbleNumber(const QString auBubbleNumber)
{
    m_auBubbleNumber=auBubbleNumber;
    emit auBubbleNumberChanged();
}

QString ImageValue::getauBubbleSize(void) const
{
    return m_auBubbleSize;
}
void ImageValue::setauBubbleSize(const QString auBubbleSize)
{
    m_auBubbleSize=auBubbleSize;
    emit auBubbleSizeChanged();
}

QString ImageValue::getauGrayMean(void) const
{
    return m_auGrayMean;
}
void ImageValue::setauGrayMean(const QString auGrayMean)
{
    m_auGrayMean=auGrayMean;
    emit auGrayMeanChanged();
}

int ImageValue::getSbGrade(void)const
{
    return m_SbGrade;
}
void ImageValue::setSbGrade(const int SbGrade)
{
    m_SbGrade=SbGrade;
    emit SbGradeChanged();
}


QList<int> ImageValue::getZhidaoYaoji(void) const
{
    return m_ZhidaoYaoji;
}

void ImageValue::setZhidaoYaoji(const QList<int> ZhidaoYaoji)
{
    m_ZhidaoYaoji=ZhidaoYaoji;
    emit ZhidaoYaojiChanged();
}

QList<int> ImageValue::getYaojiList(void) const
{
    return m_YaojiList;
}

void ImageValue::setYaojiList(const QList<int> YaojiList)
{
    m_YaojiList=YaojiList;
    emit YaojiListChanged();
}


cv::Mat ImageValue::qimage2mat(QImage &qimage)//qimage-mat
{
cv::Mat mat = cv::Mat(qimage.height(), qimage.width(), CV_8UC4, (uchar*)qimage.bits(), qimage.bytesPerLine());
cv::Mat mat2 = cv::Mat(mat.rows, mat.cols, CV_8UC3 );
int from_to[] = { 0,0, 1,1, 2,2 };
cv::mixChannels( &mat, 1, &mat2, 1, from_to, 3 );
return mat2;
}


void ImageValue::getSbImageValue(void)
{
    Histogram h;//创建图像增强算法实例;
    WatershedAlgorithm myWatershed;	// 创建分水岭算法实例;
    SbCamera sbcamerazz;
    int nr=sbcamerazz.getsbimageheight();
    int nc=sbcamerazz.getsbimagewidth();
    int sbimagesize=nc*nr;
//    QImage sbimageframe=sbcamerazz.getsbimageframe();
//    cv::Mat  sbopencvimage=qimage2mat(sbimageframe);



    cv::Mat  sbopencvimage(nr,nc,CV_8UC3);
    UCC_GetBitmapImage(sbcamerazz.getSbCameraID(),UINT8P_CAST(sbopencvimage.data),1000);



    //3.define image container which will be used later
    cv::Mat  sbopencvimage_gray;
    cv::Mat  sbopencvimage_imadjust;
    cv::Mat  sbelement=getStructuringElement( MORPH_ELLIPSE,cv::Size(7,7), Point(-1,-1));
    cv::Mat  sbopencvimage_imopen;
    cv::Mat  sbopencvimage_imdilated;
    cv::Mat  sbopencvimage_not;
    cv::Mat  sbWSS;


    //4.image processing:image gray-image adjust-image open-image dilate-image not- watershed
    cv::cvtColor(sbopencvimage,sbopencvimage_gray,CV_RGB2GRAY);
   // imshow("Gray image",opencvimage_gray);//only run in debug

    sbopencvimage_imadjust=h.stretch1(sbopencvimage_gray,3000);
  //  imshow("adjust image",opencvimage_imadjust);

    cv::morphologyEx(sbopencvimage_imadjust,sbopencvimage_imopen,MORPH_OPEN,sbelement);
   // imshow("open image",opencvimage_imopen);

    cv::dilate(sbopencvimage_imopen,sbopencvimage_imdilated,sbelement);
   // imshow("dilatedimage",opencvimage_imdilated);

    cv::bitwise_not(sbopencvimage_imdilated,sbopencvimage_not);
   // imshow("notimage",opencvimage_not);

    sbWSS=myWatershed.run(sbopencvimage_not);//return WSS as the result of watershed;
   // imshow("wtershed result1",WSS);
//    imshow("wtershed result2",WSS+opencvimage_gray);//显示分割效果




    //5.caculate the value of image:1>BubbleNumber;2>BubbleSize;3>GrayMean
    //5.1 BubbleNumber
    std::vector<std::vector<cv::Point> >sbcontours;
    cv::findContours(sbWSS,sbcontours,CV_RETR_LIST,CV_CHAIN_APPROX_NONE);
    sbGlobleBubbleNumber=sbcontours.size();

    //5.2 BubbleSize
    sbGlobleBubbleSize=sbimagesize/sbGlobleBubbleNumber;

    //5.3 GrayMean
    if (sbopencvimage_gray.isContinuous())
    {
        nc=nr*nc;
        nr=1;
    }
    for (int j=0;j<nr;j++)
        {
            uchar* data=sbopencvimage_gray.ptr<uchar>(j);
            for (int i=0;i<nc;i++)
            {
                sbsumgrayvalue=sbsumgrayvalue+data[i];
            }
        }
    sbGlobleGrayMean=sbsumgrayvalue/sbimagesize;


    //6. set value and send singnals
    setsbBubbleNumber(QString::number(sbGlobleBubbleNumber));
    setsbBubbleSize(QString::number(sbGlobleBubbleSize));
    setsbGrayMean(QString::number(sbGlobleGrayMean));
}



void ImageValue::updatesqlyaoji()
{
    //7.insert value to sql and get zhidaoyaoji
    if (sqlconnect("frothzz"))
    {
        QSqlQuery qry;

        //1>inset bubble value to sql//?????????????
        QString insertsql="INSERT INTO [frothzz].[dbo].[BubbleValue] ([BubbleNumber],[BubbleSize],[GrayMean]) VALUES(:v1,:v2,:v3)";
        qry.prepare(insertsql);
        qry.bindValue(":v1",QString::number(sbGlobleBubbleNumber));
        qry.bindValue(":v2",QString::number(sbGlobleBubbleSize));
        qry.bindValue(":v3",QString::number(sbGlobleGrayMean));

        //2> select the current guize by graymean value
        QString selectguize="select * FROM [frothzz].[dbo].[专家规则] where 灰度均值=(SELECT Min(Abs(灰度均值-"+QString::number(sbGlobleGrayMean)+"))+"+QString::number(sbGlobleGrayMean)+" FROM [frothzz].[dbo].[专家规则])";
        qry.exec(selectguize);
        qry.next();
        sbGlobleSbGrade=qry.value(0).toInt();
        setSbGrade(sbGlobleSbGrade);

        //3> choose the zhidaoyaoji from current guize
        QList<int> current_ZhidaoYaoji;
        current_ZhidaoYaoji<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0;
        current_ZhidaoYaoji[0]=qry.value(4).toInt();//sb黑药
        current_ZhidaoYaoji[1]=qry.value(5).toInt();//sb硫酸铜
        current_ZhidaoYaoji[2]=qry.value(6).toInt();//sb硝酸铅
        current_ZhidaoYaoji[3]=qry.value(7).toInt();//sb黄药
        current_ZhidaoYaoji[4]=qry.value(8).toInt();//sb二号油

        current_ZhidaoYaoji[5]=qry.value(9).toInt();//au纯碱老
        current_ZhidaoYaoji[6]=qry.value(10).toInt();//au纯碱新
        current_ZhidaoYaoji[7]=qry.value(11).toInt();//au硫酸铜
        current_ZhidaoYaoji[8]=qry.value(12).toInt();//au黄药
        current_ZhidaoYaoji[9]=qry.value(13).toInt();//au二号油
        current_ZhidaoYaoji[10]=qry.value(14).toInt();//au硫化钠
        setZhidaoYaoji(current_ZhidaoYaoji);
    }


    //8.get current yaoji
    if (sqlconnect("YaoJiDBF"))
{
        QSqlQuery qry;
        QList<int> current_YaojiList;

        current_YaojiList<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0;//init, think of another way
        qry.exec("SELECT Top 1 * FROM [YaoJiDBF].[dbo].[调节表] WHERE 药剂种类='碳酸钠' AND 加药点='碳酸钠搅拌桶' order by id desc ");//select last one
        qry.first();
        current_YaojiList[0]=qry.value(6).toInt();
        qry.exec("SELECT Top 1 * FROM [YaoJiDBF].[dbo].[调节表] WHERE 药剂种类='碳酸钠' AND 加药点='碳酸球磨池' order by id desc");
        qry.first();
        current_YaojiList[1]=qry.value(6).toInt();
        qry.exec("SELECT Top 1 * FROM [YaoJiDBF].[dbo].[调节表] WHERE 药剂种类='硫酸铜' AND 加药点='硫酸铜搅拌桶' order by id desc");
        qry.first();
        current_YaojiList[2]=qry.value(6).toInt();
        qry.exec("SELECT Top 1 * FROM [YaoJiDBF].[dbo].[调节表] WHERE 药剂种类='黄药' AND 加药点='黄药搅拌桶' order by id desc");
        qry.first();
        current_YaojiList[3]=qry.value(6).toInt();
        qry.exec("SELECT Top 1 * FROM [YaoJiDBF].[dbo].[调节表] WHERE 药剂种类='2#油' AND 加药点='2#油搅拌桶' order by id desc");
        qry.first();
        current_YaojiList[4]=qry.value(6).toInt();
        qry.exec("SELECT Top 1 * FROM [YaoJiDBF].[dbo].[调节表] WHERE 药剂种类='硫化钠' AND 加药点='硫化钠' order by id desc");
        qry.first();
        current_YaojiList[5]=qry.value(6).toInt();

        qry.exec("SELECT Top 1 * FROM [YaoJiDBF].[dbo].[调节表] WHERE 药剂种类='黑药' AND 加药点='黑药' order by id desc");
        qry.first();
        current_YaojiList[6]=qry.value(6).toInt();
        qry.exec("SELECT Top 1 * FROM [YaoJiDBF].[dbo].[调节表] WHERE 药剂种类='硫酸铜' AND 加药点='硫酸铜锑粗选' order by id desc");
        qry.first();
        current_YaojiList[7]=qry.value(6).toInt();
        qry.exec("SELECT Top 1 * FROM [YaoJiDBF].[dbo].[调节表] WHERE 药剂种类='硝酸铅' AND 加药点='硝酸铅锑粗选' order by id desc");
        qry.first();
        current_YaojiList[8]=qry.value(6).toInt();
        qry.exec("SELECT Top 1 * FROM [YaoJiDBF].[dbo].[调节表] WHERE 药剂种类='黄药' AND 加药点='黄药锑粗选' order by id desc");
        qry.first();
        current_YaojiList[9]=qry.value(6).toInt();
        qry.exec("SELECT Top 1 * FROM [YaoJiDBF].[dbo].[调节表] WHERE 药剂种类='2#油' AND 加药点='2#油锑粗选' order by id desc");
        qry.first();
        current_YaojiList[10]=qry.value(6).toInt();

        setYaojiList(current_YaojiList);

    }

}





void ImageValue::getAuImageValue(void)
{
    Histogram h;//创建图像增强算法实例;
    WatershedAlgorithm myWatershed;	// 创建分水岭算法实例;
    AuCamera aucamerazz;
    int nr=aucamerazz.getauimageheight();
    int nc=aucamerazz.getauimagewidth();
    int auimagesize=nc*nr;
//    QImage auimageframe=aucamerazz.getauimageframe();
//    cv::Mat  auopencvimage=qimage2mat(auimageframe);



    cv::Mat  auopencvimage(nr,nc,CV_8UC3);
    UCC_GetBitmapImage(aucamerazz.getAuCameraID(),UINT8P_CAST(auopencvimage.data),1000);

//    double auGlobleBubbleNumber=0;
//    double auGlobleBubbleSize=0;
//    double auGlobleGrayMean=0;
//    double ausumgrayvalue=0;



    //3.define image container which will be used later
    cv::Mat  auopencvimage_gray;
    cv::Mat  auopencvimage_imadjust;
    cv::Mat  auelement=getStructuringElement( MORPH_ELLIPSE,cv::Size(7,7), Point(-1,-1));
    cv::Mat  auopencvimage_imopen;
    cv::Mat  auopencvimage_imdilated;
    cv::Mat  auopencvimage_not;
    cv::Mat  auWSS;


    //4.image processing:image gray-image adjust-image open-image dilate-image not- watershed
    cv::cvtColor(auopencvimage,auopencvimage_gray,CV_RGB2GRAY);
   // imshow("Gray image",opencvimage_gray);//only run in debug

    auopencvimage_imadjust=h.stretch1(auopencvimage_gray,3000);
  //  imshow("adjust image",opencvimage_imadjust);

    cv::morphologyEx(auopencvimage_imadjust,auopencvimage_imopen,MORPH_OPEN,auelement);
   // imshow("open image",opencvimage_imopen);

    cv::dilate(auopencvimage_imopen,auopencvimage_imdilated,auelement);
   // imshow("dilatedimage",opencvimage_imdilated);

    cv::bitwise_not(auopencvimage_imdilated,auopencvimage_not);
   // imshow("notimage",opencvimage_not);

    auWSS=myWatershed.run(auopencvimage_not);//return WSS as the result of watershed;
   // imshow("wtershed result1",WSS);
//    imshow("wtershed result2",WSS+opencvimage_gray);//显示分割效果




    //5.caculate the value of image:1>BubbleNumber;2>BubbleSize;3>GrayMean
    //5.1 BubbleNumber
    std::vector<std::vector<cv::Point> >aucontours;
    cv::findContours(auWSS,aucontours,CV_RETR_LIST,CV_CHAIN_APPROX_NONE);
    auGlobleBubbleNumber=aucontours.size();

    //5.2 BubbleSize
    auGlobleBubbleSize=auimagesize/auGlobleBubbleNumber;

    //5.3 GrayMean
    if (auopencvimage_gray.isContinuous())
    {
        nc=nr*nc;
        nr=1;
    }
    for (int j=0;j<nr;j++)
        {
            uchar* data=auopencvimage_gray.ptr<uchar>(j);
            for (int i=0;i<nc;i++)
            {
                ausumgrayvalue=ausumgrayvalue+data[i];
            }
        }
    auGlobleGrayMean=ausumgrayvalue/auimagesize;


    //6. set value and send singnals
    setauBubbleNumber(QString::number(auGlobleBubbleNumber));
    setauBubbleSize(QString::number(auGlobleBubbleSize));
    setauGrayMean(QString::number(auGlobleGrayMean));

    }




