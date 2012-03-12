#ifndef ROUTEIHM_H
#define ROUTEIHM_H
#include <QGraphicsPathItem>
#include "point.h"

class RouteIHM : public QGraphicsPathItem
{
    public:
      RouteIHM(QGraphicsItem* parent = 0);
      void setPremier(const Utils::Point& premier);
      void setDeuxieme(const Utils::Point& deuxieme);
      void setVoiesPremVersDeux(unsigned int nb);
      void setVoiesDeuxVersPrem(unsigned int nb);
      void setLargeurRoute(unsigned int largeur);

    protected:
      void dessinerRoute();
      Utils::Point m_Premier, m_Deuxieme;
      unsigned int m_VoiesPremVersDeux, m_VoiesDeuxVersPrem;
      int m_LargeurRoute;
};

#endif
