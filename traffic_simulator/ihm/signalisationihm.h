#ifndef SIGNALISATIONIHM_H
#define SIGNALISATIONIHM_H
#include <QGraphicsPixmapItem>
#include "plan.h"
#include "imagesignalisation.h"

class SignalisationIHM : public QGraphicsPixmapItem
{
    public:
      SignalisationIHM();
      void setImage(ImageSignalisation* image);
      void setIntersection(const Plan::Intersection *intersection);

    private:
      QString m_Nom;
      QMap<QString, QGraphicsPixmapItem*> m_ImagesFeu;
      const Plan::Intersection *m_Intersection;
};


#endif
