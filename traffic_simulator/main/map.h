#ifndef PLAN_H
#define PLAN_H
#include <QString>
#include <QSize>
#include <QList>
#include <QMap>
#include "point.h"
#include "segment.h"

#define LARGEUR_VOIE 25

class Map {
public:
    class Road;
    class Intersection;
    typedef QList<Road*> ListeRoutes;
    typedef QList<Intersection*> ListeIntersections;
    typedef QMap<QString, Intersection*> DictionnaireIntersections;

    Map();
    Map(const QString& nomFichier);
    ~Map();

    const Intersection* getIntersection(const Utils::Point& point) const;
    Intersection* getIntersection(const Utils::Point& point);
    const Intersection* getIntersection(const Intersection* intersectionPrecedente, const Road* routeActuelle) const;
    const Intersection* getIntersection(const QString& nom) const;
    ListeIntersections getIntersections() const;
    void creerTrousIntersection();

    const Road* getRoute(const Intersection* intersection1, const Intersection* intersection2) const;
    const Road* getRoute(const Utils::Point& point) const;
    const Road* getRoute(const QString &nom) const;
    ListeRoutes getRoutes() const;
    ListeRoutes getRoutes(const Intersection* intersection) const;

protected:
    ListeRoutes m_Routes;
    DictionnaireIntersections m_Intersections;

};

class Map::Road {
public:

    class Voie {
    public:
        enum Direction {AUCUNE, PREM_VERS_DEUX, DEUX_VERS_PREM};
        Direction m_Direction;
        Utils::Segment m_Segment;
    };
    typedef QList<Voie> VoieList;

    Road();
    Road(const QString& nom, Intersection* premiere, Intersection* deuxieme);

    const QString& nom() const;
    qreal longueur() const;
    unsigned int largeur() const;
    const Utils::Point& premier() const;
    Utils::Point& premier();
    const Utils::Point& deuxieme() const;
    Utils::Point& deuxieme();
    const Intersection *getPremiereIntersection() const;
    Intersection *getPremiereIntersection();
    const Intersection *getDeuxiemeIntersection() const;
    Intersection *getDeuxiemeIntersection();
    Voie::Direction getDirection(const Intersection *prochaineIntersection) const;

    // Le resultat n'est acceptable que si resultatOk est true
    const Voie& voie(Voie::Direction d, int positionVoie, bool& resultatOk) const;
    unsigned int nbVoies(Voie::Direction d) const;
    unsigned int nbVoies() const;
    void ajouterVoie(int positionVoie, Voie::Direction dir);
    void ajouterVoie(const Voie& v);
    void recalculerSegmentsVoie();

protected:
    QString m_Nom;
    QList<Voie> m_VoiesPremVersDeux, m_VoiesDeuxVersPrem;
    Utils::Point m_Premier, m_Deuxieme;
    Intersection *m_PremiereIntersection, *m_DeuxiemeIntersection;
};

class Map::Intersection {
public:
    Intersection();
    Intersection(const QString& nom, const Utils::Point& emplacement);
    const QString& nom() const;
    const Utils::Point& emplacement() const;
    void ajouterVoisine(Intersection* voisine);

protected:
    QString m_Nom;
    QList<Intersection*> m_Voisines;
    Utils::Point m_Position;
};

#endif // PLAN_H
