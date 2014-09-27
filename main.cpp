#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#include "SbCamera.h"
#include "AuCamera.h"
#include "ImageValue.h"
#include <QtQml>
#include <QtQuick/QQuickView>
#include "yaoji.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<SbCamera>("SbCamera", 1, 0, "SbCamera");
    qmlRegisterType<AuCamera>("AuCamera", 1, 0, "AuCamera");
    QtQuick2ApplicationViewer viewer;
    viewer.rootContext()->setContextProperty("imagevalue",new ImageValue);
    viewer.setMainQmlFile(QStringLiteral("qml/forth2/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
