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
           main/simulateurtraffic.cpp \
           ihm/simulationihm.cpp \
           utils/point.cpp \
           utils/utils.cpp \
           utils/ligne.cpp \
           utils/segment.cpp \
           main/plan.cpp \
           utils/vecteur.cpp \
           main/simulation.cpp \
           ihm/routeihm.cpp \
           ihm/images/gestionnaireimages.cpp \
           ihm/images/image.cpp \
           ihm/intersectionihm.cpp \
           ihm/signalisationihm.cpp \
           ihm/images/imagesignalisation.cpp \
           main/signalisation.cpp \
           main/conducteur.cpp \
           main/vehicule.cpp \
           ihm/images/imagevehicule.cpp \
           ihm/vehiculeihm.cpp

HEADERS  += main/simulateurtraffic.h \
            ihm/simulationihm.h \
            utils/point.h \
            utils/utils.h \
            utils/ligne.h \
            utils/segment.h \
            main/plan.h \
            utils/vecteur.h \
            main/simulation.h \
            ihm/routeihm.h \
            ihm/images/gestionnaireimages.h \
            ihm/images/image.h \
            ihm/intersectionihm.h \
            ihm/signalisationihm.h \
            ihm/images/imagesignalisation.h \
            main/signalisation.h \
            main/conducteur.h \
            main/vehicule.h \
            ihm/images/imagevehicule.h \
            ihm/vehiculeihm.h

FORMS    += simulateurtraffic.ui

RESOURCES += ressources/Ressources.qrc











































