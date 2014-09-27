INCLUDEPATH+="D:/Program Files/mingopencv/include"
INCLUDEPATH+="d:/Program Files/UniversalPackage/UniAPI/include"


LIBS+="D:/Program Files/mingopencv/lib/libopencv_calib3d249.dll.a"
LIBS+="D:/Program Files/mingopencv/lib/libopencv_contrib249.dll.a"
LIBS+="D:/Program Files/mingopencv/lib/libopencv_core249.dll.a"
LIBS+="D:/Program Files/mingopencv/lib/libopencv_features2d249.dll.a"
LIBS+="D:/Program Files/mingopencv/lib/libopencv_flann249.dll.a"
LIBS+="D:/Program Files/mingopencv/lib/libopencv_gpu249.dll.a"
LIBS+="D:/Program Files/mingopencv/lib/libopencv_highgui249.dll.a"
LIBS+="D:/Program Files/mingopencv/lib/libopencv_imgproc249.dll.a"
LIBS+="D:/Program Files/mingopencv/lib/libopencv_legacy249.dll.a"
LIBS+="D:/Program Files/mingopencv/lib/libopencv_ml249.dll.a"
LIBS+="D:/Program Files/mingopencv/lib/libopencv_objdetect249.dll.a"
LIBS+="D:/Program Files/mingopencv/lib/libopencv_video249.dll.a"

LIBS+="d:/Program Files/UniversalPackage/UniAPI/lib/Secure/UniControl.lib"
LIBS+="d:/Program Files/UniversalPackage/UniAPI/lib/Secure/UniTransform.lib"
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
