#include "simulateurtraffic.h"
#include "ui_simulateurtraffic.h"
#include <QTimer>
#include <QFileDialog>
#include "plan.h"
#include "utils.h"

SimulateurTraffic::SimulateurTraffic(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::SimulateurTraffic)
{
  ui->setupUi(this);
  m_Simulation = Simulation::instance();
  m_EnCoursDeLecture = false;

  if (m_Simulation)
  {
    m_SimTpsReel = true;

    m_Horloge = new QTimer(this);
    connect(m_Horloge, SIGNAL(timeout()), this, SLOT(OnHorloge()));
    m_Horloge->setInterval(50);
    if (m_SimTpsReel)
      m_Horloge->start();
    m_Simulation->ouvrirFichierXMLTypes(":/types.xml");
    m_Simulation->ouvrirFichierXMLSignalisation(":/sim1_plan.xml");
    m_Simulation->ouvrirFichierXMLSimulation(":/sim1_simulation.xml");
    ui->simulationView->redessinerPlan();
    m_Simulation->m_GestionnaireImages.ajouterImages();
    ui->simulationView->rafraichirImages();
    ui->simulationView->centrer();
    ui->simulationView->afficherVelocite(false);
    ui->simulationView->afficherFrottements(false);
    ui->simulationView->afficherForceMoteur(false);
    if (!m_SimTpsReel)
      m_Simulation->start();
  }
}

SimulateurTraffic::~SimulateurTraffic()
{
  delete ui;
  if (m_Simulation)
  {
    m_Simulation->setFinSimulation(true);
    m_Simulation->m_TpsSimulation.setHMS(0,0,0);
    if (m_Simulation->wait())
      m_Simulation->supprimerInstance();
  }
}

void SimulateurTraffic::OnHorloge()
{
  if (!m_Simulation)
    m_Simulation = Simulation::instance();

  if (!m_EnCoursDeLecture)
  {
    ui->boutonLectureArret->setIcon(QIcon(":/play.png"));
    return;
  }

  ui->boutonLectureArret->setIcon(QIcon(":/stop.png"));
  if (m_SimTpsReel)
    m_Simulation->avancer();

  m_Simulation->m_GestionnaireImages.imageSuivante();
  ui->simulationView->rafraichirImages();
}

void SimulateurTraffic::OnOuvertureSimulation()
{
  QString nomFichier = QFileDialog::getOpenFileName(this,
      tr("Ouvrir Fichier Simulation"), "", tr("Fichiers Simulation (*.xml)"));
  if (!nomFichier.isEmpty())
  {
    m_Simulation = Simulation::instance();
    m_Simulation->effacerPlan();
    m_Simulation->m_Vehicules.clear();
    m_Simulation->m_TpsSimulation.setHMS(0,0,0);
    ui->simulationView->effacerImages(true);
    m_Simulation->m_GestionnaireImages.effacerImages();
    QString nomFichierSimulation = m_Simulation->ouvrirFichierXMLSignalisation(nomFichier);
    QStringList splitFileName = nomFichier.split("/");
    splitFileName.removeLast();
    m_Simulation->ouvrirFichierXMLSimulation(splitFileName.join("/") + "/" + nomFichierSimulation);
    ui->simulationView->redessinerPlan();
    m_Simulation->m_GestionnaireImages.ajouterImages();
    ui->simulationView->rafraichirImages();
    ui->simulationView->afficherVelocite(false);
    ui->simulationView->afficherFrottements(false);
    ui->simulationView->afficherForceMoteur(false);
    ui->simulationView->centrer();
    if (!m_SimTpsReel)
      m_Simulation->start();
  }
}

void SimulateurTraffic::OnLectureArretSimulation()
{
  if (!m_Simulation)
    m_Simulation = Simulation::instance();

  if (m_SimTpsReel)
    m_Simulation->m_GestionnaireImages.derniereImage();
  m_EnCoursDeLecture = !m_EnCoursDeLecture;
}

void SimulateurTraffic::OnZoomAvant()
{
  ui->simulationView->zoom(1);
}

void SimulateurTraffic::OnZoomArriere()
{
  ui->simulationView->zoom(0);
}

void SimulateurTraffic::OnReglageVitesseSim(int vitesse)
{
  if (!m_Simulation)
    m_Simulation = Simulation::instance();

  m_Horloge->stop();
  switch (vitesse)
  {
  case 5: m_Horloge->setInterval(10); break;
  case 4: m_Horloge->setInterval(20); break;
  case 3: m_Horloge->setInterval(50); break;
  case 2: m_Horloge->setInterval(100); break;
  case 1: m_Horloge->setInterval(1000); break;
  }
  m_Horloge->start();
}

void SimulateurTraffic::OnAfficherVelocite(bool valeur)
{
  ui->simulationView->afficherVelocite(valeur);
  ui->simulationView->hide();
  ui->simulationView->show();
}

void SimulateurTraffic::OnAfficherForceMoteur(bool valeur)
{
  ui->simulationView->afficherForceMoteur(valeur);
  ui->simulationView->hide();
  ui->simulationView->show();
}

void SimulateurTraffic::OnAfficherFrottements(bool valeur)
{
  ui->simulationView->afficherFrottements(valeur);
  ui->simulationView->hide();
  ui->simulationView->show();
}
