#ifndef IMAGEVEHICULE_H
#define IMAGEVEHICULE_H
#include "point.h"
using namespace Utils;

class ImageVehicule
{
    public:
      ImageVehicule(const QString& nom, const QString& nomImage,
                   const Utils::Point& emplacement, qreal direction,
                   const Point &acceleration, const Point &velocite,
                   const Point &forceMoteur, const Point &forceFrottements);

      QString nom() const;
      QString nomImage() const;
      Utils::Point emplacement() const;
      qreal direction() const;
      Point acceleration() const;
      Point velocite() const;
      void forces(Point &forceMoteur, Point &forceFrottements);

    protected:
      QString m_Nom, m_NomImage;
      Utils::Point m_Emplacement;
      qreal m_Direction;
      Point m_Acceleration, m_Velocite;
      Point m_ForceMoteur, m_ForceFrottements;
};

#endif
