#include "simulation_ui.h"
#include "road_ui.h"
#include "simulation.h"
#include "image.h"
#include "intersection_ui.h"
#include <QWheelEvent>

/**
  * Constructeur, mettre le zoom au niveau 1 et afficher la scène
  */
SimulationUI::SimulationUI(QWidget *parent)
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
void SimulationUI::afficherVelocite(bool afficher)
{
  m_AfficherVelocite = afficher;
  foreach(CarUI* vi, m_IHMsVehicule)
  {
    if (vi)
    {
        vi->displayVelocity(m_AfficherVelocite);
    }
  }
}

/**
  * Afficher les vecteurs frottements pour tous les véhicules de
  * de la simulation
  * @param afficher Afficher ou non les vecteurs
  */
void SimulationUI::afficherFrottements(bool afficher)
{
  m_AfficherFrottements = afficher;
  foreach(CarUI* vi, m_IHMsVehicule)
  {
    if (vi)
    {
        vi->displayFriction(m_AfficherFrottements);
    }
  }
}

/**
  * Afficher les vecteurs force moteur pour tous les véhicules de
  * de la simulation
  * @param afficher Afficher ou non les vecteurs
  */
void SimulationUI::afficherForceMoteur(bool afficher)
{
  m_AfficherForceMoteur = afficher;
  foreach(CarUI* vi, m_IHMsVehicule)
  {
    if (vi)
    {
        vi->displayMotorForce(m_AfficherForceMoteur);
    }
  }
}

/**
  * Ajouter une marge sur les quatre côtés de l'IHM Simulation
  * @param marge nombre de pixels de marge
  */
void SimulationUI::ajouterMarges(const float marge)
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
void SimulationUI::centrer()
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
QGraphicsPathItem* SimulationUI::drawIntersection(Map::Intersection *i,
                                                    const Map::ListeRoutes& routes)
{
  IntersectionUI* inter(new IntersectionUI());

  if (i)
  {
    inter->setCentreIntersection(i->emplacement());
    inter->setNameIntersection(i->nom());
    inter->addRoads(routes);
  }

  return inter;
}

/**
  * Obtenir une IHM route à partir d'un objet route
  * @param route 0bjet route
  * @return IHM Route créée à partir de route
  */
QGraphicsPathItem* SimulationUI::drawRoad(Map::Road *route)
{
  RoadUI* r(new RoadUI());
  r->setFirst(route->premier());
  r->setSecond(route->deuxieme());
  r->setLanesFirstToSecond(route->nbVoies(Map::Road::Voie::PREM_VERS_DEUX));
  r->setLanesSecondToFirst(route->nbVoies(Map::Road::Voie::DEUX_VERS_PREM));
  r->setRoadWidth(route->largeur());
  return r;
}

/**
  * Supprimer toutes les images de signalisation et de véhicule
  * de la simulation
  * @param effacerImage Effacer tous les éléments de la scène
  */
void SimulationUI::effacerImages(const bool effacerImage)
{
  foreach(CarUI *vi, m_IHMsVehicule)
      m_Scene.removeItem(vi);
    m_IHMsVehicule.clear();
  foreach(TrafficLightsUI *sIHM, m_IHMsSignalisation)
    m_Scene.removeItem(sIHM);
  m_IHMsSignalisation.clear();
  if (effacerImage)
    m_Scene.clear();
}

/**
  * Rafraichit le contenu de toutes les images de véhicules
  * et de signalisations de la simulation
  */
void SimulationUI::rafraichirImages()
{
  Simulation* simu(Simulation::instance());
  if (simu)
  {
    Image* image(simu->m_GestionnaireImages.imageActuelle());
    if (image)
    {
        foreach(ImageVehicule* imageV, image->imagesVehicule())
        {
          CarUI *vi(m_IHMsVehicule.value(imageV->nom(), 0));
          if (!vi)
          {
            vi = new CarUI(QPixmap(imageV->nomImage()));
            vi->setToolTip(imageV->nom());
            m_IHMsVehicule[imageV->nom()] = vi;
            m_Scene.addItem(vi);
          }
          vi->setCarImage(imageV);
        }

      foreach(ImageSignalisation *is, image->imagesSignalisation())
      {
        TrafficLightsUI *sIHM(m_IHMsSignalisation.value(is->nom(), 0));
        if (!sIHM)
        {
          sIHM = new TrafficLightsUI();
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
void SimulationUI::redessinerPlan()
{
  effacerImages();
  Simulation* simu(Simulation::instance());
  if (simu && simu->m_Plan)
  {
    foreach(Map::Road* r, simu->m_Plan->getRoutes())
    {
      QGraphicsPathItem* route(drawRoad(r));
      m_Scene.addItem(route);
    }

    foreach(Map::Intersection* i, simu->m_Plan->getIntersections())
    {
      Map::ListeRoutes listeroutes(simu->m_Plan->getRoutes(i));
      QGraphicsPathItem* intersection(drawIntersection(i, listeroutes));
      m_Scene.addItem(intersection);
    }
  }
}

/**
  * Gérer les "wheelEvent" sur la simulation, en particulier
  * limiter la vitesse à laquelle l'utilisateur peut se déplacer
  * sur la fenêtre
  */
void SimulationUI::wheelEvent(QWheelEvent *wheel)
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
void SimulationUI::zoom(bool zoomAvant)
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
