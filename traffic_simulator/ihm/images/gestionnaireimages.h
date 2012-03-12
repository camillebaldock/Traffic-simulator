#ifndef GESTIONNAIREIMAGES_H
#define GESTIONNAIREIMAGES_H
#include "image.h"

class GestionnaireImages
{
    public:
      typedef QList<Image*> ListeImages;

      GestionnaireImages();
      virtual ~GestionnaireImages();
      void ajouterImages();
      void effacerImages();
      Image* imageActuelle();
      void setIdImageActuelle(const unsigned int id);
      void imageSuivante(unsigned int nbImages=1);
      void derniereImage();

    protected:
      ListeImages m_Images;
      unsigned int m_IdImageActuelle;
};

#endif
