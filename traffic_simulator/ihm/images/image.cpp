#include "image.h"

/**
 * Constructeur
 */
Image::Image()
{}

/**
 * Ajoute une ImageSignalisation à l'image
 */
void Image::ajouterImageSignalisation(ImageSignalisation* image)
{
  m_ImagesSignalisation.append(image);
}

/**
 * @return Images signalisation de l'image
 */
Image::ListeImagesSignalisation Image::imagesSignalisation() const
{
  return m_ImagesSignalisation;
}

/**
 * Ajoute une ImageVehicule à l'image
 */
void Image::ajouterImageVehicule(ImageVehicule* image)
{
  m_Vehicules.append(image);
}

/**
 * @return Images vehicule de l'image
 */
Image::ListeVehicules Image::imagesVehicule() const
{
  return m_Vehicules;
}

