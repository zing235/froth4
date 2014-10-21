#ifndef IMAGEVALUE_H
#define IMAGEVALUE_H
#include <QObject>
#include <opencv2/opencv.hpp>
#pragma execution_character_set("utf-8")
class ImageValue : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString sbBubbleNumber READ getsbBubbleNumber WRITE setsbBubbleNumber NOTIFY sbBubbleNumberChanged)
    Q_PROPERTY(QString sbBubbleSize READ getsbBubbleSize WRITE setsbBubbleSize NOTIFY sbBubbleSizeChanged)
    Q_PROPERTY(QString sbGrayMean READ getsbGrayMean WRITE setsbGrayMean NOTIFY sbGrayMeanChanged)

    Q_PROPERTY(QString auBubbleNumber READ getauBubbleNumber WRITE setauBubbleNumber NOTIFY auBubbleNumberChanged)
    Q_PROPERTY(QString auBubbleSize READ getauBubbleSize WRITE setauBubbleSize NOTIFY auBubbleSizeChanged)
    Q_PROPERTY(QString auGrayMean READ getauGrayMean WRITE setauGrayMean NOTIFY auGrayMeanChanged)

    Q_PROPERTY(int SbGrade READ getSbGrade WRITE setSbGrade NOTIFY SbGradeChanged)
    Q_PROPERTY(QList<int> ZhidaoYaoji READ getZhidaoYaoji WRITE setZhidaoYaoji NOTIFY ZhidaoYaojiChanged)
    Q_PROPERTY(QList<int> YaojiList READ getYaojiList WRITE setYaojiList NOTIFY YaojiListChanged)
public:
    explicit ImageValue(QObject *parent=0);

    QString getsbBubbleNumber(void) const;
    void setsbBubbleNumber(const QString sbBubbleNumber);

    QString getsbBubbleSize(void) const;
    void setsbBubbleSize(const QString sbBubbleSize);

    QString getsbGrayMean(void) const;
    void setsbGrayMean(const QString sbGrayMean);


    QString getauBubbleNumber(void) const;
    void setauBubbleNumber(const QString auBubbleNumber);

    QString getauBubbleSize(void) const;
    void setauBubbleSize(const QString auBubbleSize);

    QString getauGrayMean(void) const;
    void setauGrayMean(const QString auGrayMean);

    int getSbGrade(void) const;
    void setSbGrade(const int SbGrade);

    QList<int> getZhidaoYaoji(void) const;
    void setZhidaoYaoji(const QList<int> ZhidaoYaoji);

    QList<int> getYaojiList(void) const;
    void setYaojiList(const QList<int> YaojiList);

    cv::Mat qimage2mat(QImage &qimage);


    Q_INVOKABLE void getSbImageValue(void);
    Q_INVOKABLE void getAuImageValue(void);
    Q_INVOKABLE void updatesqlyaoji(void);



signals:
    void sbBubbleNumberChanged(void);
    void sbBubbleSizeChanged(void);
    void sbGrayMeanChanged(void);

    void auBubbleNumberChanged(void);
    void auBubbleSizeChanged(void);
    void auGrayMeanChanged(void);

    void SbGradeChanged(void);
    void ZhidaoYaojiChanged();
    void YaojiListChanged();



private:
    QString m_sbBubbleNumber;
    QString m_sbBubbleSize;
    QString m_sbGrayMean;

    QString m_auBubbleNumber;
    QString m_auBubbleSize;
    QString m_auGrayMean;
    int m_SbGrade;
    QList<int> m_ZhidaoYaoji;
    QList<int>  m_YaojiList;
};
#endif // IMAGEVALUE_H
