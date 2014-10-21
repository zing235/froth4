INCLUDEPATH+="d:/Program Files/Allied Vision Technologies/UniversalPackage/UniAPI/include"
LIBS+="d:/Program Files/Allied Vision Technologies/UniversalPackage/UniAPI/lib/Secure/UniControl.lib"
LIBS+="d:/Program Files/Allied Vision Technologies/UniversalPackage/UniAPI/lib/Secure/UniTransform.lib"

INCLUDEPATH += "D:/Program Files/opencv/build/include"


win32:CONFIG(debug, debug|release): {
LIBS += "D:/Program Files/opencv/build/x86/vc10/lib/opencv_core249d.lib"
LIBS += "D:/Program Files/opencv/build/x86/vc10/lib/opencv_imgproc249d.lib"
LIBS += "D:/Program Files/opencv/build/x86/vc10/lib/opencv_highgui249d.lib"
LIBS += "D:/Program Files/opencv/build/x86/vc10/lib/opencv_ml249d.lib"
LIBS += "D:/Program Files/opencv/build/x86/vc10/lib/opencv_video249d.lib"
LIBS += "D:/Program Files/opencv/build/x86/vc10/lib/opencv_features2d249d.lib"
LIBS += "D:/Program Files/opencv/build/x86/vc10/lib/opencv_calib3d249d.lib"
LIBS += "D:/Program Files/opencv/build/x86/vc10/lib/opencv_objdetect249d.lib"
LIBS += "D:/Program Files/opencv/build/x86/vc10/lib/opencv_contrib249d.lib"
LIBS += "D:/Program Files/opencv/build/x86/vc10/lib/opencv_legacy249d.lib"
LIBS += "D:/Program Files/opencv/build/x86/vc10/lib/opencv_flann249d.lib"

} else:win32:CONFIG(release, debug|release): {
LIBS += "D:/Program Files/opencv/build/x86/vc10/lib/opencv_core249.lib"
LIBS += "D:/Program Files/opencv/build/x86/vc10/lib/opencv_imgproc249.lib"
LIBS += "D:/Program Files/opencv/build/x86/vc10/lib/opencv_highgui249.lib"
LIBS += "D:/Program Files/opencv/build/x86/vc10/lib/opencv_ml249.lib"
LIBS += "D:/Program Files/opencv/build/x86/vc10/lib/opencv_video249.lib"
LIBS += "D:/Program Files/opencv/build/x86/vc10/lib/opencv_features2d249.lib"
LIBS += "D:/Program Files/opencv/build/x86/vc10/lib/opencv_calib3d249.lib"
LIBS += "D:/Program Files/opencv/build/x86/vc10/lib/opencv_objdetect249.lib"
LIBS += "D:/Program Files/opencv/build/x86/vc10/lib/opencv_contrib249.lib"
LIBS += "D:/Program Files/opencv/build/x86/vc10/lib/opencv_legacy249.lib"
LIBS += "D:/Program Files/opencv/build/x86/vc10/lib/opencv_flann249.lib"
}
# Add more folders to ship with the application, here
folder_01.source = qml/forth2
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =
QT+= sql
# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    Histogram.cpp \
    ImageValue.cpp \
    SbCamera.cpp \
    AuCamera.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    Histogram.h \
    ImageValue.h \
    WaterShedAlgorithm.h \
    WatershedPixel.h \
    WatershedStructure.h \
    connectsql.h \
    SbCamera.h \
    AuCamera.h
