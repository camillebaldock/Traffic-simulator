#ifndef SIMULATIONIHM_H
#define SIMULATIONIHM_H

#include <QGraphicsView>
#include "plan.h"
#include "signalisationihm.h"
#include "vehiculeihm.h"

class SimulationIHM : public QGraphicsView
{
    public:
      SimulationIHM(QWidget* parent = 0);
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
      QMap<QString, VehiculeIHM*> m_IHMsVehicule;
      QMap<QString, SignalisationIHM*> m_IHMsSignalisation;

    private:
      QGraphicsPathItem* dessinerRoute(Plan::Route* r);
      QGraphicsPathItem* dessinerIntersection(Plan::Intersection* i,
                                           const Plan::ListeRoutes& routes);
      bool m_AfficherVelocite;
      bool m_AfficherAcceleration;
      bool m_AfficherNomsIntersections;
      bool m_AfficherFrottements;
      bool m_AfficherForceMoteur;
      float m_Zoom;
};

#endif
