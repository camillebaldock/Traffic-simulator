#-------------------------------------------------
#
# Project created by QtCreator 2011-11-21T04:00:00
#
#-------------------------------------------------

QT += core gui xml testlib

TARGET = TestSimulateurIntersections

INCLUDEPATH += utils \
               ihm \
               ihm/images \
               main \
               ../simulateurintersections/main/ \
               ../simulateurintersections/ihm/ \
               ../simulateurintersections/ihm/images \
               ../simulateurintersections/utils/ \

TEMPLATE = app

FORMS    += ../simulateurintersections/simulateurtraffic.ui

RESOURCES += ../simulateurintersections/ressources/Ressources.qrc

SOURCES += main/testmain.cpp \
           ../simulateurintersections/main/simulateurtraffic.cpp \
           ../simulateurintersections/ihm/simulationihm.cpp \
           ../simulateurintersections/utils/point.cpp \
           utils/testpoint.cpp \
           ../simulateurintersections/utils/utils.cpp \
           utils/testutils.cpp \
           ../simulateurintersections/utils/ligne.cpp \
           utils/testligne.cpp \
           ../simulateurintersections/utils/segment.cpp \
           utils/testsegment.cpp \
           ../simulateurintersections/main/plan.cpp \
           main/testplan.cpp \
           ../simulateurintersections/utils/vecteur.cpp \
           utils/testvecteur.cpp \
           ../simulateurintersections/main/simulation.cpp \
           main/testsimulation.cpp \
           ../simulateurintersections/ihm/routeihm.cpp \
           ../simulateurintersections/ihm/images/gestionnaireimages.cpp \
           ../simulateurintersections/ihm/images/image.cpp \
           ../simulateurintersections/ihm/intersectionihm.cpp \
           ../simulateurintersections/ihm/signalisationihm.cpp \
           ../simulateurintersections/ihm/images/imagesignalisation.cpp \
           ../simulateurintersections/main/signalisation.cpp \
           main/testsignalisation.cpp \
           ../simulateurintersections/main/conducteur.cpp \
           main/testconducteur.cpp \
           ../simulateurintersections/main/vehicule.cpp \
           main/testvehicule.cpp \
           ../simulateurintersections/ihm/images/imagevehicule.cpp \
           ../simulateurintersections/ihm/vehiculeihm.cpp

HEADERS  += ../simulateurintersections/main/simulateurtraffic.h \
           ../simulateurintersections/ihm/simulationihm.h \
           ../simulateurintersections/utils/point.h \
           utils/testpoint.h \
           ../simulateurintersections/utils/utils.h \
           utils/testutils.h \
           ../simulateurintersections/utils/ligne.h \
           utils/testligne.h \
           ../simulateurintersections/utils/segment.h \
           utils/testsegment.h \
           ../simulateurintersections/main/plan.h \
           main/testplan.h \
           ../simulateurintersections/utils/vecteur.h \
           utils/testvecteur.h \
           ../simulateurintersections/main/simulation.h \
           main/testsimulation.h \
           ../simulateurintersections/ihm/routeihm.h \
           ../simulateurintersections/ihm/images/gestionnaireimages.h \
           ../simulateurintersections/ihm/images/image.h \
           ../simulateurintersections/ihm/intersectionihm.h \
           ../simulateurintersections/ihm/signalisationihm.h \
           ../simulateurintersections/ihm/images/imagesignalisation.h \
           ../simulateurintersections/main/signalisation.h \
           main/testsignalisation.h \
           ../simulateurintersections/main/conducteur.h \
           main/testconducteur.h \
           ../simulateurintersections/main/vehicule.h \
           main/testvehicule.h \
           ../simulateurintersections/ihm/images/imagevehicule.h \
           ../simulateurintersections/ihm/vehiculeihm.h \








































