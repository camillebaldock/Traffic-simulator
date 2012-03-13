#ifndef SimulationUI_H
#define SimulationUI_H

#include <QGraphicsView>
#include "map.h"
#include "trafficlights_ui.h"
#include "car_ui.h"

class SimulationUI : public QGraphicsView
{
    public:
      SimulationUI(QWidget* parent = 0);
      void rafraichirImages();
      void redessinerPlan();
      void effacerImages(const bool effacerScene=false);
      void zoom(bool zoomAvant);
      void afficherVelocite(bool afficher=true);
      void afficherFrottements(bool afficher=true);
      void afficherForceMoteur(bool afficher=true);
      void centrer();
      void ajouterMarges(const float marge=100.0f);

    protected:
      virtual void wheelEvent(QWheelEvent *event);
      QGraphicsScene m_Scene;
      QMap<QString, CarUI*> m_IHMsVehicule;
      QMap<QString, TrafficLightsUI*> m_IHMsSignalisation;

    private:
      QGraphicsPathItem* drawRoad(Map::Road* r);
      QGraphicsPathItem* drawIntersection(Map::Intersection* i,
                                           const Map::ListeRoutes& routes);
      bool m_AfficherVelocite;
      bool m_AfficherAcceleration;
      bool m_AfficherNomsIntersections;
      bool m_AfficherFrottements;
      bool m_AfficherForceMoteur;
      float m_Zoom;
};

#endif
