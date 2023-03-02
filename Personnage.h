#ifndef PERSONNAGE_H_INCLUDED
#define PERSONNAGE_H_INCLUDED
#include <iostream>
#include <string>
#include "Cell.h"
#include "Map.h"


class Personnage
{
    public:

    Personnage(Map *maps);
    Personnage(Map *maps, irr::scene::IAnimatedMeshSceneNode *modell, irr::video::ITexture *texture);
    void update(irr::core::vector3df pos);
    void updatePlayer(irr::core::vector3df pos);
    void updateSlender(irr::core::vector3df position);
    float getmaxX();
    float getminX();
    float getmaxZ();
    float getminZ();
    int getXCell();
    int getZCell();
    Cell getCell();
    void setRotation(float rotation);

    private:
    Map *map;
    Cell cell;
    int xCell, zCell;
    float minX, minZ, maxX, maxZ;
    irr::scene::IAnimatedMeshSceneNode *model;
    irr::core::vector3df position;



};

#endif // PERSONNAGE_H_INCLUDED
