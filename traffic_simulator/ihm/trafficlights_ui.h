#ifndef TRAFFICLIGHTSUI_H
#define TRAFFICLIGHTSUI_H
#include <QGraphicsPixmapItem>
#include "map.h"
#include "imagesignalisation.h"

class TrafficLightsUI : public QGraphicsPixmapItem
{
    public:
      TrafficLightsUI();
      void setImage(ImageSignalisation* image);
      void setIntersection(const Map::Intersection *intersection);

    private:
      QString m_Name;
      QMap<QString, QGraphicsPixmapItem*> m_ImagesFeu;
      const Map::Intersection *m_Intersection;
};


#endif
