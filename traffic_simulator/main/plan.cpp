#include <QtGui/QPen>
#include <QDomDocument>
#include <QDomNodeList>
#include <QDomElement>
#include <QFile>
#include <qmath.h>
#include <fstream>
#include <string>
#include "plan.h"
#include "ligne.h"
#include "segment.h"
#include "utils.h"

/*
 *
 * ROUTE
 *
 */
/**
  * Constructeur
  */
Plan::Route::Route()
: m_PremiereIntersection(NULL), m_DeuxiemeIntersection(NULL) {
}

/**
  * Constructeur
  * @param nomRue Nom de la Route
  * @param premiere Intersection Départ
  * @param deuxieme Intersection Fin
  */
Plan::Route::Route(const QString& nomRoute, Plan::Intersection* premiere, Plan::Intersection* deuxieme)
: m_Nom(nomRoute), m_Premier(premiere->emplacement()), m_Deuxieme(deuxieme->emplacement()),
  m_PremiereIntersection(premiere), m_DeuxiemeIntersection(deuxieme) {
}

const QString& Plan::Route::nom() const {
    return m_Nom;
}

qreal Plan::Route::longueur() const {
    return (m_Premier - m_Deuxieme).norme();
}

const Utils::Point& Plan::Route::premier() const {
    return m_Premier;
}

Utils::Point& Plan::Route::premier() {
    return m_Premier;
}

const Utils::Point& Plan::Route::deuxieme() const {
    return m_Deuxieme;
}

Utils::Point& Plan::Route::deuxieme() {
    return m_Deuxieme;
}

const Plan::Intersection *Plan::Route::getPremiereIntersection() const {
    return m_PremiereIntersection;
}

Plan::Intersection *Plan::Route::getPremiereIntersection() {
    return m_PremiereIntersection;
}

const Plan::Intersection *Plan::Route::getDeuxiemeIntersection() const {
    return m_DeuxiemeIntersection;
}

Plan::Intersection *Plan::Route::getDeuxiemeIntersection() {
    return m_DeuxiemeIntersection;
}

unsigned int Plan::Route::largeur() const {
    return (m_VoiesPremVersDeux.count() + m_VoiesDeuxVersPrem.count())*LARGEUR_VOIE;
}

unsigned int Plan::Route::nbVoies(Plan::Route::Voie::Direction d) const {
    return d == Voie::PREM_VERS_DEUX ? m_VoiesPremVersDeux.count() : m_VoiesDeuxVersPrem.count();
}

unsigned int Plan::Route::nbVoies() const {
    return m_VoiesPremVersDeux.count() + m_VoiesDeuxVersPrem.count();
}

/**
  * @param d Direction de la voie voulue
  * @param positionVoie Position de la voie voulue
  * @param resultatOk True si la position voie voulue existe, false sinon
  * @return voie dans la direction d à la position indiquée ou la première voie dans la direction d
  * si la position indiquée ne correspond pas à une voie
  */
const Plan::Route::Voie& Plan::Route::voie(Plan::Route::Voie::Direction d, int positionVoie, bool& resultatOk) const {
    const QList<Voie> &voies = d == Voie::PREM_VERS_DEUX ? m_VoiesPremVersDeux : m_VoiesDeuxVersPrem;
    if (positionVoie < 0 || positionVoie > voies.count()) {
        resultatOk = false;
        return voies.first();
    } else {
        resultatOk = true;
        return voies.at(positionVoie);
    }
}

void Plan::Route::ajouterVoie(int positionVoie, Plan::Route::Voie::Direction dir) {
    QList<Voie>& voies = (dir == Voie::PREM_VERS_DEUX ? m_VoiesPremVersDeux : m_VoiesDeuxVersPrem);
    if (positionVoie >= 0 && voies.count() > positionVoie) {
        Voie voie = {dir};
        voies.replace(positionVoie, voie);
    } else if (positionVoie >= 0) {
        Voie actual = {dir},
        temp = {dir};
        while (voies.count() + 1 < positionVoie)
            voies.push_back(temp);
        voies.push_back(actual);
    }
    recalculerSegmentsVoie();
}

void Plan::Route::ajouterVoie(const Plan::Route::Voie& v) {
    if (v.m_Direction == Voie::PREM_VERS_DEUX) m_VoiesPremVersDeux.push_back(v);
    else if (v.m_Direction == Voie::DEUX_VERS_PREM) m_VoiesDeuxVersPrem.push_back(v);
    recalculerSegmentsVoie();
}

void Plan::Route::recalculerSegmentsVoie() {
    Utils::Segment ligneDirecte(m_Premier, m_Deuxieme);

    Utils::Segment ligneDeCote = ligneDirecte.versDecalage(largeur() / 2);
    int nbVoies = 0;

    for (int i = m_VoiesDeuxVersPrem.size() - 1; i >= 0; i--) {
        m_VoiesDeuxVersPrem[i].m_Segment = ligneDeCote.versDecalage(nbVoies * -LARGEUR_VOIE - (LARGEUR_VOIE / 2));
        nbVoies++;
    }

    for (int i = 0; i < m_VoiesPremVersDeux.size(); i++) {
        m_VoiesPremVersDeux[i].m_Segment = ligneDeCote.versDecalage(nbVoies * -LARGEUR_VOIE - (LARGEUR_VOIE / 2));
        nbVoies++;
    }
}

Plan::Route::Voie::Direction Plan::Route::getDirection(const Intersection *prochaineIntersection) const {
    if (prochaineIntersection != NULL) {
        if (prochaineIntersection == getPremiereIntersection())
            return Voie::PREM_VERS_DEUX;
        else if (prochaineIntersection == getDeuxiemeIntersection())
            return Voie::DEUX_VERS_PREM;
    }
    return Voie::AUCUNE;
}

/*
 *
 * INTERSECTION
 *
 */

Plan::Intersection::Intersection()
: m_Emplacement(0.0, 0.0) {
}

Plan::Intersection::Intersection(const QString& nom, const Utils::Point& emplacement)
: m_Nom(nom), m_Emplacement(emplacement) {
}

const Utils::Point& Plan::Intersection::emplacement() const {
    return m_Emplacement;
}

const QString& Plan::Intersection::nom() const {
    return m_Nom;
}

void Plan::Intersection::ajouterVoisine(Plan::Intersection* voisine) {
    m_Voisines.push_back(voisine);
}


/*
 *
 * PLAN
 *
 */

Plan::Plan() {
}

Plan::Plan(const QString &nomFichier) {
    QDomDocument doc("Plan");
    QFile fichier(nomFichier);
    if (!fichier.open(QIODevice::ReadOnly)) {
        return;
    }
    if (!doc.setContent(&fichier)) {
        fichier.close();
        return;
    }
    fichier.close();

    QDomNodeList intersections = doc.elementsByTagName("Intersection");
    for (int n = 0; n < intersections.size(); ++n) {
        QDomElement intersection = intersections.at(n).toElement();
        qreal x = intersection.attribute("x").toFloat(), y = intersection.attribute("y").toFloat();
        QString nom = intersection.attribute("nom");
        Intersection *i = new Intersection(nom, Utils::Point(x, y));
        if (m_Intersections.contains(nom)) {
            delete m_Intersections[nom];
        }
        m_Intersections[nom] = i;
    }

    QDomNodeList routes = doc.elementsByTagName("Route");
    for (int n = 0; n < routes.count(); ++n) {
        QDomElement route = routes.at(n).toElement();
        Route *r = new Route(route.attribute("nom"),
                             m_Intersections[route.attribute("depart")],
                             m_Intersections[route.attribute("fin")]);
        for (int j = 0; j < route.attribute("pvd").toUInt(); ++j) {
            Route::Voie v;
            v.m_Direction = Route::Voie::PREM_VERS_DEUX;
            r->ajouterVoie(v);
        }
        for (int j = 0; j < route.attribute("dvp").toUInt(); ++j) {
            Route::Voie v;
            v.m_Direction = Route::Voie::DEUX_VERS_PREM;
            r->ajouterVoie(v);
        }
        m_Routes.push_back(r);
    }
    creerTrousIntersection();
}

Plan::~Plan() {
    foreach(Route *r, m_Routes)
            delete r;
    foreach(Intersection *i, m_Intersections)
            delete i;
    m_Routes.clear();
    m_Intersections.clear();
}

const Plan::Intersection* Plan::getIntersection(const Utils::Point& point) const {
    Intersection *inter = NULL;

    foreach(Intersection *i, m_Intersections) {
        if (inter == NULL) {
            inter = i;
        } else if ((i->emplacement() - point).norme() < (inter->emplacement() - point).norme()) {
            inter = i;
        }
    }
    return inter;
}

const Plan::Intersection* Plan::getIntersection(const Plan::Intersection *previousIntersection,
        const Plan::Route *routeActuelle) const {
    if (routeActuelle->getPremiereIntersection() == previousIntersection) {
        return routeActuelle->getDeuxiemeIntersection();
    } else {
        return routeActuelle->getPremiereIntersection();
    }
}

Plan::Intersection* Plan::getIntersection(const Utils::Point& point) {
    Intersection *inter = NULL;

    foreach(Intersection *i, m_Intersections) {
        if (inter == NULL) {
            inter = i;
        } else if ((i->emplacement() - point).norme() < (inter->emplacement() - point).norme()) {
            inter = i;
        }
    }
    return inter;
}

const Plan::Intersection* Plan::getIntersection(const QString& nom) const {
    if (m_Intersections.contains(nom)) return m_Intersections[nom];
    else return NULL;
}

Plan::ListeIntersections Plan::getIntersections() const {
    return m_Intersections.values();
}

/**
  *@param point Point du plan
  *@return Route du plan la plus proche de point
  */
const Plan::Route* Plan::getRoute(const Utils::Point &point) const {
    Route *route = NULL;

    foreach(Route* r, m_Routes) {
        if (route == NULL) {
            route = r;
        } else {
            Utils::Point p1 = (r->deuxieme() + r->premier()) / 2.0,
                         p2 = (route->deuxieme() + route->premier()) / 2.0;
            if ((p1 - point).norme() < (p2 - point).norme())
                route = r;
        }
    }
    return route;
}

const Plan::Route* Plan::getRoute(const QString &nomRoute) const {

    foreach(Route* r, m_Routes) {
        if (r && r->nom() == nomRoute)
            return r;
    }
    return NULL;
}

const Plan::Route* Plan::getRoute(
        const Plan::Intersection* intersection1,
        const Plan::Intersection* intersection2) const {
    if (!intersection1 || !intersection2)
        return NULL;

    foreach(Route* r, m_Routes) {
        if (
                ((r->getPremiereIntersection() && r->getPremiereIntersection()->nom() == intersection1->nom())
                && (r->getDeuxiemeIntersection() && r->getDeuxiemeIntersection()->nom() == intersection2->nom()))
                ||
                ((r->getPremiereIntersection() && r->getPremiereIntersection()->nom() == intersection2->nom())
                && (r->getDeuxiemeIntersection() && r->getDeuxiemeIntersection()->nom() == intersection1->nom()))
                )
            return r;
    }
    return NULL;
}

/**
  *@param intersection Objet intersection
  *@return Liste des routes du plan reliées à l'intersection
  */
Plan::ListeRoutes Plan::getRoutes(const Plan::Intersection *intersection) const {
    ListeRoutes routes;
    if (intersection) {
        foreach(Route* r, m_Routes) {
            if (r->getPremiereIntersection() && r->getPremiereIntersection()->nom() == intersection->nom()) {
                routes.append(r);
            }
            if (r->getDeuxiemeIntersection() && r->getDeuxiemeIntersection()->nom() == intersection->nom()) {
                routes.append(r);
            }
        }
    }
    return routes;
}

/**
  * @return Liste des objets Route du plan
  */
Plan::ListeRoutes Plan::getRoutes() const {
    return m_Routes;
}

void Plan::creerTrousIntersection() {

    foreach(Intersection *i, m_Intersections) {
        ListeRoutes routes = getRoutes(i);
        ListeRoutes::iterator compteurRouteExt;
        for (compteurRouteExt = routes.begin(); compteurRouteExt != routes.end(); ++compteurRouteExt) {
            ListeRoutes::iterator compteurRouteInt;
            for (compteurRouteInt = routes.begin(); compteurRouteInt != routes.end(); ++compteurRouteInt) {
                Route *routeExterieure = *compteurRouteExt, *routeInterieure = *compteurRouteInt;
                qreal largeurExt = routeExterieure->largeur(), largeurInt = routeInterieure->largeur();
                Utils::Segment segmentExt(routeExterieure->premier(), routeExterieure->deuxieme()),
                               segmentInt(routeInterieure->premier(), routeInterieure->deuxieme());
                Utils::Segment segmentExtPos(segmentExt.versDecalage((largeurExt / 2))), segmentExtNeg(segmentExt.versDecalage(-(largeurExt / 2))),
                               segmentIntPos(segmentInt.versDecalage((largeurInt / 2))), segmentIntNeg(segmentInt.versDecalage(-(largeurInt / 2)));
                Utils::InfoIntersection infsepsip, infsepsin, infsensip, infsensin;
                Utils::Point sepsip(Utils::InterSegmentSegment(segmentExtPos, segmentIntPos, infsepsip)),
                             sepsin(Utils::InterSegmentSegment(segmentExtPos, segmentIntNeg, infsepsin)),
                             sensip(Utils::InterSegmentSegment(segmentExtNeg, segmentIntPos, infsensip)),
                             sensin(Utils::InterSegmentSegment(segmentExtNeg, segmentIntNeg, infsensin));
                if (infsepsip == Utils::INTERSECTION)
                {
                  bool eb=routeExterieure->getPremiereIntersection()->nom() == i->nom(),
                       ib=routeInterieure->getPremiereIntersection()->nom() == i->nom();
                  Utils::Point eoff(eb?segmentExtPos.depart()-sepsip:segmentExtPos.fin()-sepsip),
                               ioff(ib?segmentIntPos.depart()-sepsip:segmentIntPos.fin()-sepsip);
                  (eb?routeExterieure->premier():routeExterieure->deuxieme()) -= eoff;
                  (ib?routeInterieure->premier():routeInterieure->deuxieme()) -= ioff;
                }
                if (infsepsin == Utils::INTERSECTION)
                {
                  bool eb=routeExterieure->getPremiereIntersection()->nom() == i->nom(),
                       ib=routeInterieure->getPremiereIntersection()->nom() == i->nom();
                  Utils::Point eoff(eb?segmentExtPos.depart()-sepsin:segmentExtPos.fin()-sepsin),
                               ioff(ib?segmentIntNeg.depart()-sepsin:segmentIntNeg.fin()-sepsin);
                  (eb?routeExterieure->premier():routeExterieure->deuxieme()) -= eoff;
                  (ib?routeInterieure->premier():routeInterieure->deuxieme()) -= ioff;
                }
                if (infsensip == Utils::INTERSECTION)
                {
                  bool eb=routeExterieure->getPremiereIntersection()->nom() == i->nom(),
                       ib=routeInterieure->getPremiereIntersection()->nom() == i->nom();
                  Utils::Point eoff(eb?segmentExtNeg.depart()-sensip:segmentExtNeg.fin()-sensip),
                               ioff(ib?segmentIntPos.depart()-sensip:segmentIntPos.fin()-sensip);
                  (eb?routeExterieure->premier():routeExterieure->deuxieme()) -= eoff;
                  (ib?routeInterieure->premier():routeInterieure->deuxieme()) -= ioff;
                }
                if (infsensin == Utils::INTERSECTION)
                {
                  bool eb=routeExterieure->getPremiereIntersection()->nom() == i->nom(),
                       ib=routeInterieure->getPremiereIntersection()->nom() == i->nom();
                  Utils::Point eoff(eb?segmentExtNeg.depart()-sensin:segmentExtNeg.fin()-sensin),
                               ioff(ib?segmentIntNeg.depart()-sensin:segmentIntNeg.fin()-sensin);
                  (eb?routeExterieure->premier():routeExterieure->deuxieme()) -= eoff;
                  (ib?routeInterieure->premier():routeInterieure->deuxieme()) -= ioff;
                }
                routeInterieure->recalculerSegmentsVoie();
                routeExterieure->recalculerSegmentsVoie();
            }
        }
    }
}
