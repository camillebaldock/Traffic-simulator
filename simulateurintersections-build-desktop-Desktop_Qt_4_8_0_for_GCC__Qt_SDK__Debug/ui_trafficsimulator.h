/********************************************************************************
** Form generated from reading UI file 'trafficsimulator.ui'
**
** Created: Tue Mar 13 01:19:21 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRAFFICSIMULATOR_H
#define UI_TRAFFICSIMULATOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QWidget>
#include "simulationihm.h"

QT_BEGIN_NAMESPACE

class Ui_TrafficSimulator
{
public:
    QAction *actionOuvrir_Fichier_Simulation;
    QWidget *widget;
    QPushButton *boutonLectureArret;
    Simulation_UI *simulationView;
    QPushButton *boutonZoomArriere;
    QPushButton *boutonZoomAvant;
    QLabel *label;
    QSlider *reglageVitesse;
    QLabel *label_2;
    QCheckBox *checkBoxAfficherVelocite;
    QCheckBox *checkBoxAfficherForceMoteur;
    QCheckBox *checkBoxAfficherFrottements;
    QLabel *label_3;
    QMenuBar *menuBar;
    QMenu *menuFichier;

    void setupUi(QMainWindow *SimulateurTraffic)
    {
        if (SimulateurTraffic->objectName().isEmpty())
            SimulateurTraffic->setObjectName(QString::fromUtf8("SimulateurTraffic"));
        SimulateurTraffic->resize(1064, 721);
        actionOuvrir_Fichier_Simulation = new QAction(SimulateurTraffic);
        actionOuvrir_Fichier_Simulation->setObjectName(QString::fromUtf8("actionOuvrir_Fichier_Simulation"));
        widget = new QWidget(SimulateurTraffic);
        widget->setObjectName(QString::fromUtf8("widget"));
        boutonLectureArret = new QPushButton(widget);
        boutonLectureArret->setObjectName(QString::fromUtf8("boutonLectureArret"));
        boutonLectureArret->setGeometry(QRect(40, 110, 41, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        boutonLectureArret->setIcon(icon);
        boutonLectureArret->setAutoRepeat(false);
        boutonLectureArret->setAutoExclusive(false);
        boutonLectureArret->setAutoDefault(false);
        boutonLectureArret->setDefault(false);
        boutonLectureArret->setFlat(false);
        simulationView = new Simulation_UI(widget);
        simulationView->setObjectName(QString::fromUtf8("simulationView"));
        simulationView->setGeometry(QRect(160, 10, 801, 661));
        QBrush brush(QColor(0, 0, 0, 66));
        brush.setStyle(Qt::SolidPattern);
        simulationView->setProperty("backgroundBrush", QVariant(brush));
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::NoBrush);
        simulationView->setProperty("foregroundBrush", QVariant(brush1));
        simulationView->setProperty("sceneRect", QVariant(QRectF(0, 0, 0, 300000)));
        boutonZoomArriere = new QPushButton(widget);
        boutonZoomArriere->setObjectName(QString::fromUtf8("boutonZoomArriere"));
        boutonZoomArriere->setGeometry(QRect(30, 220, 21, 21));
        boutonZoomAvant = new QPushButton(widget);
        boutonZoomAvant->setObjectName(QString::fromUtf8("boutonZoomAvant"));
        boutonZoomAvant->setGeometry(QRect(70, 220, 21, 21));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 240, 41, 21));
        reglageVitesse = new QSlider(widget);
        reglageVitesse->setObjectName(QString::fromUtf8("reglageVitesse"));
        reglageVitesse->setGeometry(QRect(20, 170, 81, 21));
        reglageVitesse->setMinimum(1);
        reglageVitesse->setMaximum(5);
        reglageVitesse->setPageStep(1);
        reglageVitesse->setValue(3);
        reglageVitesse->setSliderPosition(3);
        reglageVitesse->setOrientation(Qt::Horizontal);
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 190, 51, 16));
        checkBoxAfficherVelocite = new QCheckBox(widget);
        checkBoxAfficherVelocite->setObjectName(QString::fromUtf8("checkBoxAfficherVelocite"));
        checkBoxAfficherVelocite->setGeometry(QRect(0, 350, 121, 31));
        checkBoxAfficherVelocite->setChecked(false);
        checkBoxAfficherForceMoteur = new QCheckBox(widget);
        checkBoxAfficherForceMoteur->setObjectName(QString::fromUtf8("checkBoxAfficherForceMoteur"));
        checkBoxAfficherForceMoteur->setGeometry(QRect(0, 380, 141, 31));
        checkBoxAfficherForceMoteur->setChecked(false);
        checkBoxAfficherFrottements = new QCheckBox(widget);
        checkBoxAfficherFrottements->setObjectName(QString::fromUtf8("checkBoxAfficherFrottements"));
        checkBoxAfficherFrottements->setGeometry(QRect(0, 410, 151, 31));
        checkBoxAfficherFrottements->setChecked(false);
        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 320, 62, 16));
        SimulateurTraffic->setCentralWidget(widget);
        boutonLectureArret->raise();
        boutonZoomArriere->raise();
        boutonZoomAvant->raise();
        label->raise();
        reglageVitesse->raise();
        label_2->raise();
        simulationView->raise();
        checkBoxAfficherVelocite->raise();
        checkBoxAfficherForceMoteur->raise();
        checkBoxAfficherFrottements->raise();
        label_3->raise();
        menuBar = new QMenuBar(SimulateurTraffic);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1064, 22));
        menuFichier = new QMenu(menuBar);
        menuFichier->setObjectName(QString::fromUtf8("menuFichier"));
        SimulateurTraffic->setMenuBar(menuBar);

        menuBar->addAction(menuFichier->menuAction());
        menuFichier->addAction(actionOuvrir_Fichier_Simulation);

        retranslateUi(SimulateurTraffic);
        QObject::connect(checkBoxAfficherFrottements, SIGNAL(toggled(bool)), SimulateurTraffic, SLOT(OnAfficherFrottements(bool)));

        QMetaObject::connectSlotsByName(SimulateurTraffic);
    } // setupUi

    void retranslateUi(QMainWindow *SimulateurTraffic)
    {
        SimulateurTraffic->setWindowTitle(QApplication::translate("TrafficSimulator", "TrafficSimulator", 0, QApplication::UnicodeUTF8));
        actionOuvrir_Fichier_Simulation->setText(QApplication::translate("TrafficSimulator", "Ouvrir Fichier Plan", 0, QApplication::UnicodeUTF8));
        boutonLectureArret->setText(QString());
        boutonZoomArriere->setText(QApplication::translate("TrafficSimulator", "-", 0, QApplication::UnicodeUTF8));
        boutonZoomAvant->setText(QApplication::translate("TrafficSimulator", "+", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("TrafficSimulator", "Zoom", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("TrafficSimulator", "Vitesse", 0, QApplication::UnicodeUTF8));
        checkBoxAfficherVelocite->setText(QApplication::translate("TrafficSimulator", "V\303\251locit\303\251 (jaune)", 0, QApplication::UnicodeUTF8));
        checkBoxAfficherForceMoteur->setText(QApplication::translate("TrafficSimulator", "Force Moteur (vert)", 0, QApplication::UnicodeUTF8));
        checkBoxAfficherFrottements->setText(QApplication::translate("TrafficSimulator", "Frottements (bleu)", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("TrafficSimulator", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Lucida Grande'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600; text-decoration: underline;\">Afficher</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        menuFichier->setTitle(QApplication::translate("TrafficSimulator", "Fichier", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TrafficSimulator: public Ui_TrafficSimulator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRAFFICSIMULATOR_H
