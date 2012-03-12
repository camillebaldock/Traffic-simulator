#include "imagevehicule.h"

/**
  * Constructeur
  */
ImageVehicule::ImageVehicule(const QString &nom,
                           const QString &nomImage,
                           const Utils::Point &emplacement,
                           qreal direction,
                           const Point &acceleration,
                           const Point &velocite,
                           const Point &forceMoteur,
                           const Point &forceFrottements)
  : m_Nom(nom),
    m_NomImage(nomImage),
    m_Emplacement(emplacement),
    m_Direction(direction),
    m_Acceleration(acceleration),
    m_Velocite(velocite),
    m_ForceMoteur(forceMoteur),
    m_ForceFrottements(forceFrottements)
{
}

QString ImageVehicule::nom() const
{
  return m_Nom;
}

QString ImageVehicule::nomImage() const
{
  return m_NomImage;
}

Utils::Point ImageVehicule::emplacement() const
{
  return m_Emplacement;
}

qreal ImageVehicule::direction() const
{
  return m_Direction;
}

Point ImageVehicule::acceleration() const
{
  return m_Acceleration;
}

Point ImageVehicule::velocite() const
{
  return m_Velocite;
}

void ImageVehicule::forces(Point &moteur, Point &frottements)
{
  moteur = m_ForceMoteur;
  frottements = m_ForceFrottements;
}
