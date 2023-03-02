#include "Personnage.h"

using namespace std;
using namespace irr;
using namespace core;
using namespace video;
using namespace scene;

Personnage::Personnage(Map *maps)
{
    map = maps;
}
 Personnage::Personnage(Map *maps, IAnimatedMeshSceneNode *modell, ITexture *texture)
{
    map = maps;
    model = modell;
    model->setMaterialFlag(EMF_LIGHTING, true);
    model->setMaterialTexture(0,texture);
    model->setPosition(vector3df(50, 0, 50));
    model->setRotation(vector3df(0,0,0));
    model->setScale(vector3df(0.08f, 0.08f, 0.08f));
}
void Personnage::update(vector3df pos)
{
    /*
    * pour les collsions :
    * ce ne sont pas de "vrai collisions"
    * selon la position X et Z du joueur, nous connaissons sa position dans la "MAP"
    * selon le block dans lequel le personnage se situe et si il y a un mur en haut par exemple, alors il ne pourra pas se déplacer plus loin
    * si il n'y a pas de mur, il pourra se déplacer bien plus loin, jusqu'a changer de block.
    */
    xCell = pos.X/map->getSizeCube();
    zCell = pos.Z/map->getSizeCube();
    cell = map->get(xCell, zCell);

//    cout << " x / y " << xCell << " / " << zCell;
    if(!cell.getT())
        minZ = map->getSizeCube()/3 + pos.Z - (int)pos.Z%(int)map->getSizeCube();
    else
        minZ = pos.Z -200 ;
    if(!cell.getB())
        maxZ = map->getSizeCube()*0.70f + pos.Z - (int)pos.Z%(int)map->getSizeCube();
    else
        maxZ = pos.Z +200 ;
    if(!cell.getR())
        maxX =   map->getSizeCube() *0.70f + pos.X - (int)pos.X%(int)map->getSizeCube();
    else
        maxX = pos.X +200 ;
    if(!cell.getL())
        minX =   map->getSizeCube()/3 +  pos.X - (int)pos.X%(int)map->getSizeCube();
    else
        minX = pos.X -200 ;
}
void Personnage::updatePlayer(vector3df pos)
{
    update(pos);
    map->setVisited(xCell, zCell);

}
void Personnage::updateSlender(vector3df position)  // au lieu de faire plusieurs classe héritant de Personnage, nous avons créer 2 fonctions update
{
    update(position);
    model->setPosition(position);
}
void Personnage::setRotation(float rotation)
{
    model->setRotation(vector3df(0,rotation,0));
}
float Personnage::getmaxX()
{   return maxX; }
float Personnage::getminX()
{   return minX; }
float Personnage::getmaxZ()
{   return maxZ; }
float Personnage::getminZ()
{   return minZ; }
int Personnage::getXCell()
{   return xCell; }
int Personnage::getZCell()
{   return zCell;  }
Cell Personnage::getCell()
{   return map->get(xCell, zCell); }
