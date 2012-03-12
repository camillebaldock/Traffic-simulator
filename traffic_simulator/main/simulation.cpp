#include <QFile>
#include <QDomDocument>
#include <QDomNodeList>
#include <QDomElement>
#include <QStringList>
#include "simulation.h"
#include "plan.h"
#include "utils.h"
#include "signalisation.h"

using namespace Utils;

Simulation* Simulation::m_Instance = 0;
qreal Simulation::m_PasSimulation = 0.1f;
QTime Simulation::m_TpsSimulation;

/**
  * Constructeur
  * Mettre à zéro l'horloge et le nombre de pas
  */
Simulation::Simulation()
{
  m_TpsSimulation.setHMS( 0, 0, 0, 0 ) ;
  m_FinSimulation = false;
  m_Plan = 0;
  m_NbTotalPas = 0;
}

Simulation::~Simulation()
{
  m_FinSimulation = true;
  m_TpsSimulation.setHMS(0,0,0);
}

Simulation* Simulation::instance()
{
  if (!m_Instance)
  {
    m_Instance = new Simulation;
  }
  return m_Instance;
}

bool Simulation::supprimerInstance()
{
  if (m_Instance)
  {
    delete m_Instance;
    m_Instance = 0;
    return true;
  }
  return false;
}

/**
  * Parser le fichier XML définissant le plan et en assigner le contenu
  * à la variable m_Plan de cette simulation
  */
void Simulation::ouvrirFichierXMLPlan(const QString &nomFichier)
{
  effacerPlan();
  m_Plan = new Plan(nomFichier);
  m_FichierPlan = nomFichier;
}

void Simulation::effacerPlan()
{
  if (m_Plan)
  {
    delete m_Plan;
    m_FichierPlan = "";
  }
  m_Plan = 0;
}

QString Simulation::ouvrirFichierXMLSignalisation(const QString &nomFichier)
{
    QString nomFichierSimulation;
    QDomDocument doc("Carte");
    QFile fichier(nomFichier);
    if( !fichier.open( QIODevice::ReadOnly ) )
    {return nomFichierSimulation;}
    if( !doc.setContent(&fichier) )
    {
      fichier.close();
    }
    fichier.close();
    m_Signalisations.clear();
    m_FichierSignalisation = nomFichier;

    QDomNodeList elementsPlan = doc.elementsByTagName("Plan");
    if (elementsPlan.isEmpty()) {
        return nomFichierSimulation;
    }
    else
    {
        ouvrirFichierXMLPlan(nomFichier);
    }

    QDomNodeList elementsSimulation = doc.elementsByTagName("Simulation");
    nomFichierSimulation = elementsSimulation.at(0).toElement().text();

  QDomNodeList elementsFeu = doc.elementsByTagName("Feu");
  for (int i=0; i<elementsFeu.size(); i++)
  {
    Signalisation *s = new Signalisation();
    QDomElement elementFeu = elementsFeu.at(i).toElement();
    const Plan::Intersection *inter = NULL;

    QDomNodeList enfantsFeu = elementFeu.childNodes();
    for (int j=0; j<enfantsFeu.size(); j++)
    {
      QDomElement enfantFeu = enfantsFeu.at(j).toElement();
      if (enfantFeu.tagName()=="Intersection")
      {
        inter = m_Plan->getIntersection(enfantFeu.text());
        s->setIntersection(inter);
      }
      else if (enfantFeu.tagName()=="Etat")
      {
        QDomElement elementEtat = enfantFeu.toElement();
        Signalisation::Etat *etat = new Signalisation::Etat(elementEtat.attribute("nom"));

        QDomNodeList enfantsEtat = elementEtat.childNodes();
        for (int k=0; k<enfantsEtat.size(); k++)
        {
          QDomElement enfantEtat = enfantsEtat.at(k).toElement();

          if (enfantEtat.tagName()=="TempsVert")
            etat->setDureeVert(enfantEtat.text().toFloat());
          else if (enfantEtat.tagName()=="TempsOrange")
            etat->setDureeOrange(enfantEtat.text().toFloat());
          else if (enfantEtat.tagName()=="TempsRouge")
            etat->setDureeRouge(enfantEtat.text().toFloat());
          else if (enfantEtat.tagName()=="Connexion")
          {
            QStringList listeSeparee= enfantEtat.text().split(",", QString::SkipEmptyParts);
            const Plan::Route *depart = m_Plan->getRoute(listeSeparee.at(0));
            unsigned int voieDepart = listeSeparee.at(1).toInt();
            const Plan::Route *fin = m_Plan->getRoute(listeSeparee.at(2));
            unsigned int voieFin = listeSeparee.at(3).toInt();
            Signalisation::Connexion *conn = new Signalisation::Connexion(depart, voieDepart, fin, voieFin);
            etat->ajouterConnexion(conn);
          }
        }
        s->ajouterEtat(etat);
      }
    }
    if (inter) {
      m_Signalisations[inter] = s;
    }
  }
  return nomFichierSimulation;
}

void Simulation::rafraichirSimulation()
{
  m_TpsSimulation.setHMS(0,0,0);
  if (!m_FichierSignalisation.isEmpty())
    ouvrirFichierXMLSignalisation(m_FichierSignalisation);
}

void Simulation::setFinSimulation(bool fin)
{
  m_FinSimulation=fin;
}

bool Simulation::finSimulation()
{
  return m_FinSimulation;
}

void Simulation::avancer()
{
  foreach(Signalisation *s, m_Signalisations) s->avancer();
  foreach(Conducteur *c, m_Conducteurs) c->avancer();
  foreach(Vehicule *v, m_Vehicules) v->avancer();
  m_GestionnaireImages.ajouterImages();
  m_TpsSimulation = m_TpsSimulation.addMSecs(1000*m_PasSimulation);
}



void Simulation::executer()
{
  QTime tpsMax(0,10); //10 minutes de temps maximum pour une simulation
  while (!m_FinSimulation && (m_TpsSimulation < tpsMax))
  {
    avancer();
  }
}

void Simulation::ajouterVehicule(Vehicule *v)
{
  m_Vehicules.push_back(v);
}

Vehicule* Simulation::ajouterVehicule(const QString &nom, const QString &nomType)
{
  int nbVehicules = m_Vehicules.size();
  QString nomDepart = nom;
  QString nomFin = nomDepart;
  if (nom.isEmpty())
  {
    nomDepart = "Vehicule";
    nomFin = nomDepart+QString::number(nbVehicules);
  }
  Vehicule *vehiculeExiste = trouverVehicule(nomFin);
  int n = nbVehicules+1;
  while (vehiculeExiste != NULL)
  {
    vehiculeExiste = trouverVehicule(nomDepart+QString::number(n));
    n++;
  }

  int index = -1;
  for (int i=0; i<m_TypesVehicule.size(); i++)
  {
    if (m_TypesVehicule.at(i)->m_Nom == nomType)
    {
      index = i;
      break;
    }
  }
  if (index < 0)
  {
    return 0;
  }

  TypeVehicule *tv = m_TypesVehicule.at(index);
  Vehicule *v = new Vehicule(nomFin, tv);
  v->setMasse(tv->m_Masse);
  v->setEmpattement(tv->m_Empattement);
  v->setForceMoteur(tv->m_ForceMoteur);
  ajouterVehicule(v);
  return v;
}

Vehicule* Simulation::trouverVehicule(const QString &nom)
{
  foreach(Vehicule *v, m_Vehicules)
  {
    if (v && v->nom() == nom)
      return v;
  }
  return NULL;
}

void Simulation::ajouterConducteur(Conducteur *c)
{
  m_Conducteurs.push_back(c);
}

Conducteur* Simulation::ajouterConducteur(const QString &nom, const QString &nomType)
{
  int nbConducteurs = m_Conducteurs.size();
  QString nomDepart = nom;
  QString nomFinal = nomDepart;
  if (nom.isEmpty())
  {
    nomDepart = "Conducteur";
    nomFinal = nomDepart+QString::number(nbConducteurs);
  }
  Conducteur *conducteur = trouverConducteur(nomFinal);
  int n = nbConducteurs+1;
  while (conducteur != NULL)
  {
    conducteur = trouverConducteur(nomDepart+QString::number(n));
    n++;
  }

  int index = -1;
  for (int i=0; i<m_TypesConducteur.size(); i++)
  {
    if (m_TypesConducteur.at(i)->m_Nom == nomType)
    {
      index = i;
      break;
    }
  }

  if (index < 0)
  {
    return 0;
  }

  TypeConducteur *tc = m_TypesConducteur.at(index);
  Conducteur *c = new Conducteur(nomFinal);
  c->m_ObjectifVitesseVirage = tc->m_VitesseVirage;
  c->m_VitesseParDefaut = tc->m_VitesseToutDroit;
  ajouterConducteur(c);
  return c;
}

Conducteur* Simulation::trouverConducteur(const QString &nom)
{
  foreach(Conducteur *c, m_Conducteurs)
  {
    if (c && c->nom() == nom)
      return c;
  }
  return NULL;
}


void Simulation::ouvrirFichierXMLTypes(const QString &nomFichier)
{
  QDomDocument doc("Configuration");
  QFile fichier( nomFichier );
  if( !fichier.open( QIODevice::ReadOnly ) )
  {
    return;
  }
  if( !doc.setContent(&fichier))
  {
    fichier.close();
    return;
  }
  fichier.close();
  m_TypesVehicule.clear();
  m_TypesConducteur.clear();

  QDomNodeList vTypes = doc.elementsByTagName("TypeVehicule");
  for (int n1=0; n1<vTypes.size(); ++n1)
  {
    QDomElement elem1 = vTypes.at(n1).toElement();
    TypeVehicule *vt = new TypeVehicule();
    vt->m_Nom = elem1.attribute("nom");

    QDomNodeList children = elem1.childNodes();
    for (int i=0; i<children.size(); ++i)
    {
      QDomElement elem2 = children.at(i).toElement();
      if (elem2.tagName() == "Image")
          vt->m_NomImage = elem2.text();
      else if (elem2.tagName() == "Empattement")
        vt->m_Empattement = (elem2.text().toFloat());
      else if (elem2.tagName() == "Masse")
        vt->m_Masse = (elem2.text().toFloat());
      else if (elem2.tagName() == "ForceMoteur")
        vt->m_ForceMoteur = (elem2.text().toFloat());
    }
    m_TypesVehicule.push_back(vt);
  }

  QDomNodeList cTypes = doc.elementsByTagName("TypeConducteur");
  for (int n2=0; n2<cTypes.size(); ++n2)
  {
    QDomElement elem1 = cTypes.at(n2).toElement();
    TypeConducteur *dt = new TypeConducteur();
    dt->m_Nom = elem1.attribute("nom");

    QDomNodeList children = elem1.childNodes();
    for (int i=0; i<children.size(); ++i)
    {
      QDomElement elem2 = children.at(i).toElement();
      if (elem2.tagName() == "VitesseVirage")
        dt->m_VitesseVirage = elem2.text().toFloat();
      else if (elem2.tagName() == "VitesseToutDroit")
        dt->m_VitesseToutDroit = elem2.text().toFloat();
    }
    m_TypesConducteur.push_back(dt);
  }

  return;
}

void Simulation::ouvrirFichierXMLSimulation(const QString &nomFichier)
{
  m_TpsSimulation.setHMS(0,0,0);

  QDomDocument doc("Simulation");
  QFile fichier(nomFichier);
  if( !fichier.open( QIODevice::ReadOnly ) )
  {return;}

  if( !doc.setContent( &fichier  ) )
  {
    fichier.close();
    return;
  }
  fichier.close();

  QDomNodeList vehicules = doc.elementsByTagName("Vehicule");
  for (int i=0; i<vehicules.size(); ++i)
  {
    QDomElement elementVehicule = vehicules.at(i).toElement();
    QString nom_Vehicule = elementVehicule.attribute("nom");
    QString typeVehicule = elementVehicule.attribute("type");

    Vehicule *nouveauVehicule = ajouterVehicule(nom_Vehicule, typeVehicule);
    if (!nouveauVehicule)
      return;

    QDomNodeList children = elementVehicule.childNodes();
    for (int i=0; i<children.size(); ++i)
    {
      QDomElement elem2 = children.at(i).toElement();
      if (elem2.tagName() == "Emplacement")
      {
        QString valStr = elem2.text();
        qreal x = valStr.section(" ", 0, 0).toFloat();
        qreal y = valStr.section(" ", 1, 1).toFloat();
        nouveauVehicule->setEmplacement(Point(x,y));
      }
      else if (elem2.tagName() == "Direction")
      {
        nouveauVehicule->setDirection(elem2.text().toFloat());
      }
    }

    QDomNodeList conducteurs = elementVehicule.elementsByTagName("Conducteur");
    for (int n4=0; n4<conducteurs.size(); ++n4)
    {
      QDomElement elem2 = conducteurs.at(n4).toElement();
      QString typeConducteur = elem2.attribute("type");

      Conducteur *nouveauConducteur = ajouterConducteur("Conducteur" + n4, typeConducteur);
      if (!nouveauConducteur)
        return;
      nouveauConducteur->utiliser(nouveauVehicule);

      QDomNodeList children = elem2.childNodes();
      for (int i=0; i<children.size(); ++i)
      {
        QDomElement elem3 = children.at(i).toElement();
        if (elem3.tagName() == "Voie")
        {
          QDomNodeList children2 = elem3.childNodes();
          for (int j=0; j<children2.size(); ++j)
          {
            QDomElement elem4= children2.at(j).toElement();
            if (elem4.tagName().compare("Intersections",Qt::CaseInsensitive) == 0)
            {
              QString valStr = elem4.text();
              QStringList strList = valStr.split(" ", QString::SkipEmptyParts);
              for (int si=0; si<strList.size(); si++)
                nouveauConducteur->ajouterCoordonnees(strList.at(si));
            }
            else
            {
              QString valStr = elem4.text();
              qreal x = valStr.section(" ", 0, 0).toFloat();
              qreal y = valStr.section(" ", 1, 1).toFloat();
              nouveauConducteur->ajouterCoordonnees(Point(x,y));
            }
          }
        }
      }
    }
  }
  m_FichierSimulation = nomFichier;
}
