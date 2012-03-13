#include "imagesignalisation.h"

/**
  * Constructeur
  * @param nom Nom de l'intersection
  * @param intersection Object intersection
  * @param etat Etat de la signalisation
  */
ImageSignalisation::ImageSignalisation(
    const QString &nom,
    const Map::Intersection *intersection,
    const TrafficLights::State &etat)
  : m_Nom(nom),
  m_Intersection(intersection),
  m_Etat(etat)
{}

QString ImageSignalisation::nom() const
{
  return m_Nom;
}

TrafficLights::State ImageSignalisation::etat() const
{
  return m_Etat;
}

const Map::Intersection* ImageSignalisation::intersection() const
{
  return m_Intersection;
}
