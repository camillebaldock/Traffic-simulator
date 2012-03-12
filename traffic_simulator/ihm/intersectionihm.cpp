#include "intersectionihm.h"
#include <QFont>
#include <QPen>
#include <qmath.h>
#include "utils.h"

/**
  * Constructeur, fond noir pour l'intersection
  */
IntersectionIHM::IntersectionIHM(QGraphicsItem *parent)
  : QGraphicsPathItem(parent)
{
  setZValue(Utils::COUCHE_INTERSECTION);
  setPen(QPen(Qt::black));
  setBrush(Qt::black);
}

/**
  * Remplir les variables m_Points et m_Segments avec le contenu de routes, normaliser
  * la position des points par rapport au centre de l'intersection, puis dessiner l'intersection
  * @param routes ListeRoutes dont les données seront utilisées pour dessiner l'intersection
  */
void IntersectionIHM::ajouterRoutes(const Plan::ListeRoutes &routes)
{
  //Remplir les variables m_Points et m_Segments avec le contenu de routes
  foreach(Plan::Route* r, routes)
  {
    if (r->getPremiereIntersection() && r->getDeuxiemeIntersection())
    {
      Utils::Segment segment;
      segment.depart() = r->premier();
      segment.fin() = r->deuxieme();
      if (r->getPremiereIntersection()->nom() == m_Nom)
      {
        Utils::Segment segmentP(segment.versPerpendiculaireDepuisDepart(0, r->largeur()));
        m_Segments.push_back(segmentP);
        m_Points.push_back(segmentP.depart());
        m_Points.push_back(segmentP.fin());
      }
      else
      {
        Utils::Segment segmentP(segment.versPerpendiculaireDepuisFin(0, r->largeur()));
        m_Segments.push_back(segmentP);
        m_Points.push_back(segmentP.depart());
        m_Points.push_back(segmentP.fin());
      }
    }
  }

  //Déterminer le centre de l'intersection
  Utils::Point centre(0.0f,0.0f), dir(0.0f, -1.0f);
  foreach(Utils::Point p, m_Points)
    centre += p;
  centre /= m_Points.count();

  //Trouver la position des points par rapport au centre de l'intersection
  for (int i=0; i<m_Points.count(); ++i)
  {
    for (int j=0; j<m_Points.count(); ++j)
    {
      Utils::Point pointI = m_Points.at(i), pointJ = m_Points.at(j);
      pointI -= centre;
      pointI.normaliser();
      pointJ -= centre;
      pointJ.normaliser();
      qreal angleI = Utils::Point::angleSigne(pointI, dir) * 180.0/M_PI,
            angleJ = Utils::Point::angleSigne(pointJ, dir) * 180.0/M_PI;
      if (angleI > 0) angleI -= 360;
      if (angleJ > 0) angleJ -= 360;
      if (angleI < angleJ)
      {
        Utils::Point temp(m_Points.at(j));
        m_Points.replace(j, m_Points.at(i));
        m_Points.replace(i, temp);
      }
    }
  }
  dessinerIntersection();
}

/**
  * Dessine les bordures et le nom de l'intersection
  * @param afficherNom Afficher ou non le nom de l'intersection
  */
void IntersectionIHM::dessinerIntersection()
{
  if (m_Segments.count() > 1)
  {
    //Trouver le centre de l'intersection
    Utils::Point centre(0,0);
    foreach(Utils::Point p, m_Points)
      centre += p;
    centre /= m_Points.count();

    //Déterminer la wone QPainterPath dans laquel les dessins suivants vont être faits
    QPainterPath path;
    path.moveTo(m_Points.front().x(), m_Points.front().y());
    path.lineTo(m_Points.front().x(), m_Points.front().y());
    for(int i=1; i<m_Points.count(); ++i)
    {
      path.lineTo(m_Points.at(i).x(), m_Points.at(i).y());
    }
    path.closeSubpath();
    path.setFillRule(Qt::WindingFill);
    setPath(path);

    //Dessiner les bordures de l'intersection
    QPen blanc(Qt::white);
    foreach(Utils::Segment segment, m_Segments)
    {
      QGraphicsLineItem* ligne(new QGraphicsLineItem(this));
      ligne->setPen(blanc);
      ligne->setLine(segment.toQLineF());
    }
  }
}

void IntersectionIHM::setNomIntersection(const QString &nom)
{
  m_Nom = nom;
}

void IntersectionIHM::setCentreIntersection(const Utils::Point &centre)
{
  m_Centre = centre;
}
