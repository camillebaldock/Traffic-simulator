#include "gestionnaireimages.h"
#include "simulation.h"
#include "signalisation.h"

/**
  * Constructeur, initialise l'identifiant de l'image actuelle à 0
  */
GestionnaireImages::GestionnaireImages()
  : m_IdImageActuelle(0)
{}


/**
  * Destructeur, efface les images
  */
GestionnaireImages::~GestionnaireImages()
{effacerImages();}


/**
  * Récupère l'instance de la simulation en cours, et tous les éléments
  * listés dans m_Vehicules et m_Signalisations et rajoute les images correspondantes
  * à la variable m_Images de la simulation
  */
void GestionnaireImages::ajouterImages()
{
  Simulation* simu(Simulation::instance());
  if (simu)
  {
    Image* image(new Image());
    image->m_Tps = simu->m_TpsSimulation;
    foreach(Vehicule* v, simu->m_Vehicules)
    {
      Point moteur, frottement, objectif;
      v->forces(moteur, frottement);
      if (v->conducteur())
        objectif = v->conducteur()->m_ObjectifActuel;
      image->ajouterImageVehicule(new ImageVehicule(v->nom(),
                                                    v->type()->m_NomImage,
                                     v->emplacement(),
                                     v->direction().angle(),
                                     v->acceleration(),
                                     v->velocite(),
                                     moteur, frottement));
    }
    foreach(Signalisation *s, simu->m_Signalisations)
    {
      image->ajouterImageSignalisation(new ImageSignalisation(s->intersection()->nom(),
                                                              s->intersection(),
                                                              *s->etatActuel()));
    }
    m_Images.append(image);
  }
}

/**
  * Efface les images et remet à zéro l'identifiant de l'image actuelle
  */
void GestionnaireImages::effacerImages()
{
  m_IdImageActuelle = 0;
  m_Images.clear();
}

/**
  * Règle l'identifiant image actuelle sur le plus haut identifiant des images disponibles
  * Si aucune image n'est disponible, remise à zéro de l'identifiant de l'image actuelle
  */
void GestionnaireImages::derniereImage()
{
  if (m_Images.empty())
    m_IdImageActuelle = 0;
  else
  {
    unsigned int nbImages = static_cast<unsigned int>(m_Images.size());
    m_IdImageActuelle = nbImages-1;
  }
}

/**
  * @return Image correspondant à l'identifiant image actuelle
  */
Image* GestionnaireImages::imageActuelle()
{
  if (!m_Images.empty() && m_IdImageActuelle < (unsigned int)m_Images.size())
    return m_Images.at(m_IdImageActuelle);
  return NULL;
}


/**
  * Incrémente l'identifiant image actuelle
  */
void GestionnaireImages::imageSuivante(unsigned int nbImages)
{
  setIdImageActuelle(m_IdImageActuelle+nbImages);
}

void GestionnaireImages::setIdImageActuelle(unsigned int nb)
{
  unsigned int nbImages = static_cast<unsigned int>(m_Images.size());
  if (nb >= nbImages)
    m_IdImageActuelle = nbImages-1;
  else
    m_IdImageActuelle =  nb;
}
