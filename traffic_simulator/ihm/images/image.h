#ifndef IMAGE_H
#define IMAGE_H
#include <QTime>
#include "imagesignalisation.h"
#include "imagevehicule.h"

class Image
{
    public:
      typedef QList<ImageSignalisation*> ListeImagesSignalisation;
      typedef QList<ImageVehicule*> ListeVehicules;
      Image();
      void ajouterImageSignalisation(ImageSignalisation* image);
      ListeImagesSignalisation imagesSignalisation() const;
      void ajouterImageVehicule(ImageVehicule* image);
      ListeVehicules imagesVehicule() const;
      QTime m_Tps;

    protected:
      ListeImagesSignalisation m_ImagesSignalisation;
      ListeVehicules m_Vehicules;
    };

#endif
