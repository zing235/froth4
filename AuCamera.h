#ifndef AUCAMERA_H
#define AUCAMERA_H

#include <QtQuick/QQuickPaintedItem>
#include <QImage>

class AuCamera : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(quint32 AuCameraID READ getAuCameraID )
    Q_PROPERTY(quint32 auimagewidth READ getauimagewidth)
    Q_PROPERTY(quint32 auimageheight READ getauimageheight)

    Q_PROPERTY(QImage auimageframe READ getauimageframe)
public:
    AuCamera(QQuickItem *parent = 0);

    quint32 getAuCameraID(void) const;
    quint32 getauimagewidth(void) const;
    quint32 getauimageheight(void) const;

    QImage getauimageframe(void) const;

    Q_INVOKABLE void startaucamera();
    Q_INVOKABLE void updateaucamera();
    Q_INVOKABLE  void getauimage();


   void paint(QPainter *painter);
private:
//   quint32 m_cameraID;

};
#endif // AUCAMERA_H
