#ifndef IMAGESIGNALISATION_H
#define IMAGESIGNALISATION_H
#include "point.h"
#include "map.h"
#include "trafficlights.h"

class ImageSignalisation
{
    public:
      ImageSignalisation(const QString& nom,
                          const Map::Intersection *intersection,
                          const TrafficLights::State &etat);
      QString nom() const;
      TrafficLights::State etat() const;
      const Map::Intersection* intersection() const;

    protected:
      QString m_Nom;
      TrafficLights::State m_Etat;
      const Map::Intersection *m_Intersection;
    };

#endif
