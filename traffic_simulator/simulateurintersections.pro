#-------------------------------------------------
#
# Project created by QtCreator 2011-11-19T18:35:49
#
#-------------------------------------------------

QT += core gui xml

TARGET = simulateurintersections
TEMPLATE = app

INCLUDEPATH += utils \
               ihm \
               ihm/images \
               main

SOURCES += main/main.cpp \
           utils/point.cpp \
           utils/utils.cpp \
           utils/ligne.cpp \
           utils/segment.cpp \
           utils/vecteur.cpp \
           main/simulation.cpp \
           ihm/images/gestionnaireimages.cpp \
           ihm/images/image.cpp \
           ihm/images/imagesignalisation.cpp \
           ihm/images/imagevehicule.cpp \
    ihm/road_ui.cpp \
    ihm/car_ui.cpp \
    ihm/intersection_ui.cpp \
    main/driver.cpp \
    main/map.cpp \
    main/car.cpp \
    ihm/simulation_ui.cpp \
    ihm/trafficlights_ui.cpp \
    main/trafficlights.cpp \
    main/trafficsimulator.cpp

HEADERS  += \
            utils/point.h \
            utils/utils.h \
            utils/ligne.h \
            utils/segment.h \
            utils/vecteur.h \
            main/simulation.h \
            ihm/images/gestionnaireimages.h \
            ihm/images/image.h \
            ihm/images/imagesignalisation.h \
            ihm/images/imagevehicule.h \
    ihm/intersection_ui.h \
    ihm/road_ui.h \
    ihm/car_ui.h \
    main/driver.h \
    main/car.h \
    main/trafficsimulator.h \
    main/trafficlights.h \
    main/map.h \
    ihm/trafficlights_ui.h \
    ihm/simulation_ui.h

FORMS    += \
    trafficsimulator.ui

RESOURCES += ressources/Ressources.qrc











































