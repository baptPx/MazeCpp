#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED
#include <time.h>
#include <irrlicht.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <vector2d.h>
#include "Cell.h"
#define size2D 40


void reverseVector(std::vector<irr::core::vector2df> &vecteur, int a, int b);

class Map
{
    public:

    Map(irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *driverI, int N);

    void initBlock(Cell **block, int index);
    void initPos(int **pos, int index);
    void makeLaby();
    int getWidth();
    void draw(int i, int j, float size);
    float getSizeCube();
    Cell *gett(int x, int y);
    Cell get(int x, int y);
    void poneyWings(int x, int y); // ailes d'Icares
    void drawWings(int indexP, int x, int y);
    void setVisited(int x, int y);
    void foundEnd(std::vector<irr::core::vector2df> &vecteur, int index);
    void randomObjectif(std::vector<irr::core::vector2df> &vecteur, int index);
    void RAZ(int razIndex);
    void deleteObjectif(int x, int y, int i);
    void update();
    void setObjectif(int i);



    private:
    Cell** block;
    int **pos;
    int index, index2, indexD, randomN, width, posO[6][2];
    float sizeCube;
    bool hadMove, canRight, canLeft, canBottom, canTop;
    irr::scene::ISceneManager *scene;
    irr::video::IVideoDriver *driver;
    irr::scene::IMeshSceneNode *cube;
    irr::video::ITexture *image, *ponyImage, *playerImage;
    irr::scene::IAnimatedMeshSceneNode *objectif[6];


};

#endif // MAP_H_INCLUDED
