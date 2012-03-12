#ifndef IMAGESIGNALISATION_H
#define IMAGESIGNALISATION_H
#include "point.h"
#include "plan.h"
#include "signalisation.h"

class ImageSignalisation
{
    public:
      ImageSignalisation(const QString& nom,
                          const Plan::Intersection *intersection,
                          const Signalisation::Etat &etat);
      QString nom() const;
      Signalisation::Etat etat() const;
      const Plan::Intersection* intersection() const;

    protected:
      QString m_Nom;
      Signalisation::Etat m_Etat;
      const Plan::Intersection *m_Intersection;
    };

#endif
