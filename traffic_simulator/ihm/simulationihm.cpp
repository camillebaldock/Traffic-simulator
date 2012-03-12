#include "simulationihm.h"
#include "routeihm.h"
#include "simulation.h"
#include "image.h"
#include "intersectionihm.h"
#include <QWheelEvent>

/**
  * Constructeur, mettre le zoom au niveau 1 et afficher la scène
  */
SimulationIHM::SimulationIHM(QWidget *parent)
  : QGraphicsView(parent)
{
  setScene(&m_Scene);
  m_Zoom = 1.0f;
  show();
}

/**
  * Afficher les vecteurs vélocité pour tous les véhicules de
  * de la simulation
  * @param afficher afficher ou non les vecteurs
  */
void SimulationIHM::afficherVelocite(bool afficher)
{
  m_AfficherVelocite = afficher;
  foreach(VehiculeIHM* vi, m_IHMsVehicule)
  {
    if (vi)
    {
        vi->afficherVelocite(m_AfficherVelocite);
    }
  }
}

/**
  * Afficher les vecteurs frottements pour tous les véhicules de
  * de la simulation
  * @param afficher Afficher ou non les vecteurs
  */
void SimulationIHM::afficherFrottements(bool afficher)
{
  m_AfficherFrottements = afficher;
  foreach(VehiculeIHM* vi, m_IHMsVehicule)
  {
    if (vi)
    {
        vi->afficherFrottements(m_AfficherFrottements);
    }
  }
}

/**
  * Afficher les vecteurs force moteur pour tous les véhicules de
  * de la simulation
  * @param afficher Afficher ou non les vecteurs
  */
void SimulationIHM::afficherForceMoteur(bool afficher)
{
  m_AfficherForceMoteur = afficher;
  foreach(VehiculeIHM* vi, m_IHMsVehicule)
  {
    if (vi)
    {
        vi->afficherForceMoteur(m_AfficherForceMoteur);
    }
  }
}

/**
  * Ajouter une marge sur les quatre côtés de l'IHM Simulation
  * @param marge nombre de pixels de marge
  */
void SimulationIHM::ajouterMarges(const float marge)
{
  QRectF rectangle = m_Scene.itemsBoundingRect();
  rectangle.setLeft(rectangle.left()-marge);
  rectangle.setTop(rectangle.top()-marge);
  rectangle.setBottom(rectangle.bottom()+marge);
  rectangle.setRight(rectangle.right()+marge);
  setSceneRect(rectangle);
}

/**
  * Centrer la fenêtre sur le milieu de la simulation et
  * mettre au niveau moyen de zoom
  */
void SimulationIHM::centrer()
{
  ajouterMarges();
  centerOn(sceneRect().center());
  resetTransform();
  m_Zoom = 1.0f;
}

/**
  * Obtenir une IHM intersection à partir d'un objet intersection et d'une liste d'objets routes
  * @param i Objet intersection
  * @param routes Liste d'objets routes
  * @return IHM Intersection créée à partir de i et routes
  */
QGraphicsPathItem* SimulationIHM::dessinerIntersection(Plan::Intersection *i,
                                                    const Plan::ListeRoutes& routes)
{
  IntersectionIHM* inter(new IntersectionIHM());

  if (i)
  {
    inter->setCentreIntersection(i->emplacement());
    inter->setNomIntersection(i->nom());
    inter->ajouterRoutes(routes);
  }

  return inter;
}

/**
  * Obtenir une IHM route à partir d'un objet route
  * @param route 0bjet route
  * @return IHM Route créée à partir de route
  */
QGraphicsPathItem* SimulationIHM::dessinerRoute(Plan::Route *route)
{
  RouteIHM* r(new RouteIHM());
  r->setPremier(route->premier());
  r->setDeuxieme(route->deuxieme());
  r->setVoiesPremVersDeux(route->nbVoies(Plan::Route::Voie::PREM_VERS_DEUX));
  r->setVoiesDeuxVersPrem(route->nbVoies(Plan::Route::Voie::DEUX_VERS_PREM));
  r->setLargeurRoute(route->largeur());
  return r;
}

/**
  * Supprimer toutes les images de signalisation et de véhicule
  * de la simulation
  * @param effacerImage Effacer tous les éléments de la scène
  */
void SimulationIHM::effacerImages(const bool effacerImage)
{
  foreach(VehiculeIHM *vi, m_IHMsVehicule)
      m_Scene.removeItem(vi);
    m_IHMsVehicule.clear();
  foreach(SignalisationIHM *sIHM, m_IHMsSignalisation)
    m_Scene.removeItem(sIHM);
  m_IHMsSignalisation.clear();
  if (effacerImage)
    m_Scene.clear();
}

/**
  * Rafraichit le contenu de toutes les images de véhicules
  * et de signalisations de la simulation
  */
void SimulationIHM::rafraichirImages()
{
  Simulation* simu(Simulation::instance());
  if (simu)
  {
    Image* image(simu->m_GestionnaireImages.imageActuelle());
    if (image)
    {
        foreach(ImageVehicule* imageV, image->imagesVehicule())
        {
          VehiculeIHM *vi(m_IHMsVehicule.value(imageV->nom(), 0));
          if (!vi)
          {
            vi = new VehiculeIHM(QPixmap(imageV->nomImage()));
            vi->setToolTip(imageV->nom());
            m_IHMsVehicule[imageV->nom()] = vi;
            m_Scene.addItem(vi);
          }
          vi->setImageVehicule(imageV);
        }

      foreach(ImageSignalisation *is, image->imagesSignalisation())
      {
        SignalisationIHM *sIHM(m_IHMsSignalisation.value(is->nom(), 0));
        if (!sIHM)
        {
          sIHM = new SignalisationIHM();
          m_IHMsSignalisation[is->nom()] = sIHM;
          m_Scene.addItem(sIHM);
        }
        sIHM->setImage(is);
      }
      ajouterMarges();
    }
  }
  else
  {
    effacerImages();
  }
}

/**
  * Redessine toutes les routes et intersections de la simulation
  */
void SimulationIHM::redessinerPlan()
{
  effacerImages();
  Simulation* simu(Simulation::instance());
  if (simu && simu->m_Plan)
  {
    foreach(Plan::Route* r, simu->m_Plan->getRoutes())
    {
      QGraphicsPathItem* route(dessinerRoute(r));
      m_Scene.addItem(route);
    }

    foreach(Plan::Intersection* i, simu->m_Plan->getIntersections())
    {
      Plan::ListeRoutes listeroutes(simu->m_Plan->getRoutes(i));
      QGraphicsPathItem* intersection(dessinerIntersection(i, listeroutes));
      m_Scene.addItem(intersection);
    }
  }
}

/**
  * Gérer les "wheelEvent" sur la simulation, en particulier
  * limiter la vitesse à laquelle l'utilisateur peut se déplacer
  * sur la fenêtre
  */
void SimulationIHM::wheelEvent(QWheelEvent *wheel)
{
  qreal vitesseLimite = width()*0.14;
  QPointF centreScene = mapToScene(rect().center());
  QPointF positionSceneWheel = mapToScene(wheel->pos());
  QPointF sceneCenterWindowG = mapToGlobal(rect().center());
  QPointF positionGlobaleWheel = mapToGlobal(wheel->pos());
  QPointF diffCentreFenetre = positionGlobaleWheel - sceneCenterWindowG;
  if (diffCentreFenetre.x() > vitesseLimite)
    diffCentreFenetre.setX(vitesseLimite);
  else if (diffCentreFenetre.x() < -vitesseLimite)
    diffCentreFenetre.setX(-vitesseLimite);
  if (diffCentreFenetre.y() > vitesseLimite)
    diffCentreFenetre.setY(vitesseLimite);
  else if (diffCentreFenetre.y() < -vitesseLimite)
    diffCentreFenetre.setY(-vitesseLimite);

  qreal echelleHorizontale = diffCentreFenetre.x() / (width()/2) * m_Zoom;
  qreal echelleVerticale = diffCentreFenetre.y() / (height()/2) * m_Zoom;
  qreal newX = (positionSceneWheel.x() - centreScene.x()) * qAbs(echelleHorizontale);
  qreal newY = (positionSceneWheel.y() - centreScene.y()) * qAbs(echelleVerticale);

  QPointF nouveauCentre((positionSceneWheel.x() + newX), (positionSceneWheel.y() + newY));

  if (wheel->delta() > 0)
    zoom(1);
  else
    zoom(0);
  centerOn(nouveauCentre);
  wheel->accept();
}

/**
  * Augmenter ou diminuer le zoom sur la fenêtre simulation
  * par un facteur de 1.2
  * @param zoomAvant zoom avant ou arrière
  */
void SimulationIHM::zoom(bool zoomAvant)
{
  if (zoomAvant)
  {
    scale(1.2, 1.2);
    m_Zoom*=0.97;
  }
  else
  {
    scale(1/1.2, 1/1.2);
    m_Zoom=1.03;
  }
}
