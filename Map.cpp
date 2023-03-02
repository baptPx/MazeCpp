#include <iostream>
#include <string>
#include <vector2d.h>
#include "Map.h"


using namespace std;
using namespace irr;
using namespace scene;
using namespace video;
using namespace core;

Map::Map(ISceneManager *sceneManager, IVideoDriver *driverI, int n)
{
    index=0;
    index2=0;
    indexD=0;
    sizeCube=10;
    canBottom=true;
    canLeft=true;
    canRight=true;
    canTop=true;
    hadMove=true;
    width = n;
    scene = sceneManager;
    driver = driverI;
    block = new Cell*[n];
    initBlock(block, n);
    pos = new int*[n*n];
    initPos(pos, n*n);
    pos[index2][0] = n/2;
    pos[index2][1] = n/2;
    makeLaby();             //generation du Labyrinthe
    vector<vector2df> position(0);
    foundEnd(position, width * width);  // creation des 6objectifs
    randomObjectif(position, 0);
    setObjectif(0);

    image = driver->getTexture("carre.png");
    ponyImage = driver->getTexture("pony2.png");
    playerImage = driver->getTexture("player1.png");

}

void Map::setObjectif(int i)
{
    objectif[i] = scene->addAnimatedMeshSceneNode(scene->getMesh("os.obj"));
    objectif[i]->setMaterialFlag(EMF_LIGHTING, true);
    objectif[i]->setMaterialTexture(0,  driver->getTexture("os.png"));
    objectif[i]->setScale(vector3df(0.04f, 0.04f, 0.04f ));
    cout << " +1 p = " << i << endl;
    if(i!=5)
        setObjectif(i+1);
}
void Map::update()
{
    for(int i=0; i<6; i++)
    {
        objectif[i]->setRotation(vector3df(0,objectif[i]->getRotation().Y+2,0));
    }
}
void Map::deleteObjectif(int x, int y, int i)
{
    if(posO[i][0] == x && posO[i][1] == y)
    {
        objectif[i]->setVisible(false);
        i=6;
    }
    if(i!=6)
        deleteObjectif(x, y, i+1);

}
void Map::RAZ(int razIndex)     // remise a zero des cellules visité
{
    block[(int)razIndex/width][(int)razIndex%width].setAlgoVisited(false);
    if(razIndex!=width*width-1)
        RAZ(razIndex+1);
}
void Map::randomObjectif(vector<vector2df> &vecteur, int p)
{
    randomN = p+rand()%(vecteur.size());
    swap(vecteur[p], vecteur[randomN]);
    swap(vecteur[randomN], vecteur[vecteur.size()]);
//    reverseVector(vecteur, p, randomN);
//    reverseVector(vecteur, randomN, vecteur.size());
    int x = (int)vecteur[p].X;
    int y = (int)vecteur[p].Y;
    block[x][y].containObjectif(true);
    if(p!=5)
        randomObjectif(vecteur, p+1);
}
void Map::foundEnd(vector<vector2df> &vecteur, int index)
{
    index--;
    if(block[index/width][index%width].getNbWall() == 3 && index!=width*width-1)
        {vecteur.push_back(vector2df(index/width, index%width));
        }

    if(index!=0)
        foundEnd(vecteur, index);
}
void reverseVector(vector<vector2df> &vecteur, int a, int b)    // inverse 2 valeur dans le tableau
{
    vector2df v1;
    v1 = vecteur[a];
    vecteur[a] = vecteur[b];
    vecteur[b] = v1;
}
void Map::initBlock(Cell **block, int index)
{
    index--;
    block[index] = new Cell[width];
    if(index!=0)
        initBlock(block, index);
}
void Map::initPos(int **pos, int index)
{
    index--;
    pos[index] = new int[2];
    if(index!=0)
        initPos(pos, index);
}
void Map::setVisited(int x, int y)
{
    block[x][y].setVisited(true);
}
int Map::getWidth()
{   return width;  }

float Map::getSizeCube()
{   return sizeCube; }

Cell *Map::gett(int x, int y)
{
        return &block[x][y];
}
Cell Map::get(int x, int y)
{
       return block[x][y];
}

void Map::draw(int i, int j, float size)      // construit le Labyrinthe dans la scene
{
    sizeCube=size;


            if(i==0)
            {
                cube = scene->addCubeSceneNode( size/2, 0, -1,
                vector3df(
                        size*j,
                        0.0f,
                        size*width));

            cube->setMaterialTexture(0, driver->getTexture("mur.jpg"));
            cube = scene->addCubeSceneNode( size/2, 0, -1,
                vector3df(
                        size*width,
                        0.0f,
                        size*j));
            cube->setMaterialTexture(0, driver->getTexture("mur.jpg"));
                cube = scene->addCubeSceneNode( size/2, 0, -1,
                vector3df(
                        size*j+size/2,
                        0.0f,
                        size*width));

            cube->setMaterialTexture(0, driver->getTexture("mur.jpg"));
            cube = scene->addCubeSceneNode( size/2, 0, -1,
                vector3df(
                        size*width,
                        0.0f,
                        size*j+size/2));
            cube->setMaterialTexture(0, driver->getTexture("mur.jpg"));

            }
            cube = scene->addCubeSceneNode( size/2, 0, -1,
                vector3df(
                        size*i,
                        0.0f,
                        size*j));

            cube->setMaterialTexture(0, driver->getTexture("mur.jpg"));

                cube = scene->addCubeSceneNode( size/2, 0, -1,
                vector3df(
                        size*i+size/2,
                        -size/2,
                        size*j+size/2));

            cube->setMaterialTexture(0, driver->getTexture("terre.jpg"));

                 cube = scene->addCubeSceneNode( size/2, 0, -1,
                vector3df(
                        size*i+size/2,
                        size/2,
                        size*j+size/2));
            cube->setMaterialTexture(0, driver->getTexture("mur.jpg"));

            if(!block[i][j].getL())
            {
                cube = scene->addCubeSceneNode( size/2, 0, -1,
                vector3df(
                        size*i,
                        0.0f,
                        size*j+size/2));
                cube->setMaterialTexture(0, driver->getTexture("mur.jpg"));

            }
            else
            {
                cube = scene->addCubeSceneNode( size/2, 0, -1,
                vector3df(
                        size*i,
                        -size/2,
                        size*j+size/2));
                cube->setMaterialTexture(0, driver->getTexture("terre.jpg"));

                 cube = scene->addCubeSceneNode( size/2, 0, -1,
                vector3df(
                        size*i,
                        size/2,
                        size*j+size/2));
                cube->setMaterialTexture(0, driver->getTexture("mur.jpg"));

            }
            if(!block[i][j].getT())
            {
                cube = scene->addCubeSceneNode( size/2, 0, -1,
                vector3df(
                        size*i+size/2,
                        0.0f,
                        size*j));
                cube->setMaterialTexture(0, driver->getTexture("mur.jpg"));
            }
             else
            {
                cube = scene->addCubeSceneNode( size/2, 0, -1,
                vector3df(
                        size*i+size/2,
                        -size/2,
                        size*j));
                cube->setMaterialTexture(0, driver->getTexture("terre.jpg"));
                 cube = scene->addCubeSceneNode( size/2, 0, -1,
                vector3df(
                        size*i+size/2,
                        size/2,
                        size*j));
                cube->setMaterialTexture(0, driver->getTexture("mur.jpg"));
            }
            if(block[i][j].isObjectif())
            {
                objectif[indexD]->setPosition(vector3df( size*i+size/2,
                        0,
                        size*j +size/2));
                objectif[indexD]->setRotation(vector3df( 0,0,0));
                posO[indexD][0] = i;
                posO[indexD][1] = j;
                indexD++;
    }

       cube->setMaterialTexture(0, driver->getTexture("mur.jpg"));
       j++;
       if(j==width)
       {    j=0; i++;       }
        if(i!=width)
            draw(i, j, size);
}

void Map::poneyWings(int x, int y)  { drawWings(0, x, y)  ;}
void Map::drawWings(int indexP, int x, int y) // ailes d'Icares
{

           if(block[indexP/width][indexP%width].isVisited())
                  driver->draw2DImage(image, position2d<s32>(size2D + 4 + size2D*(indexP/width),size2D + 4 + indexP%width*size2D), rect<s32>(0,0,size2D-8,size2D-8),
                             0, SColor(255,62,148,255), true);
            if(!block[indexP/width][indexP%width].getT())
                  driver->draw2DImage(image, position2d<s32>(size2D + size2D*(indexP/width),size2D + indexP%width*size2D), rect<s32>(0,0,size2D,2),
                             0, SColor(255,255,255,255), true);
            if(!block[indexP/width][indexP%width].getB())
                  driver->draw2DImage(image, position2d<s32>(size2D + size2D*(indexP/width),size2D*2 + indexP%width*size2D), rect<s32>(0,0,size2D,2),
                             0, SColor(255,255,255,255), true);
            if(!block[indexP/width][indexP%width].getR())
                  driver->draw2DImage(image, position2d<s32>(size2D*2 + size2D*(indexP/width),size2D + indexP%width*size2D), rect<s32>(0,0,2,size2D),
                             0, SColor(255,255,255,255), true);
            if(!block[indexP/width][indexP%width].getL())
                  driver->draw2DImage(image, position2d<s32>(size2D + size2D*(indexP/width),size2D + indexP%width*size2D), rect<s32>(0,0,2,size2D),
                             0, SColor(255,255,255,255), true);
            if(block[indexP/width][indexP%width].isObjectif())
                 driver->draw2DImage(ponyImage, position2d<s32>(size2D + 4 + size2D*(indexP/width),size2D + 4 + indexP%width*size2D), rect<s32>(0,0,size2D-8,size2D-8),
                             0, SColor(255,62,255,255), true);


            if(indexP != width*width -1)
                drawWings(indexP+1, x, y);
            else
                driver->draw2DImage(playerImage, position2d<s32>(size2D + 4 + size2D*x,size2D + 4 + y*size2D), rect<s32>(0,0,size2D-8,size2D-8),
                             0, SColor(255,255,255,255), true);

}

void Map::makeLaby()
{
     if(hadMove)
            index2++;
        hadMove=false;
        randomN = rand()%4;
        if(randomN == 0 &&  pos[index][0]!=width-1)
        {
            if(!block[pos[index][0] +1]   [pos[index][1]].isBroken() )
            {
            pos[index2][0] = pos[index][0] +1;
            pos[index2][1] = pos[index][1];
            block[pos[index][0]]   [pos[index][1]].brokeR();
            block[pos[index2][0]]   [pos[index2][1]].brokeL();
            index=index2;
            hadMove=true;
//            cout << "a droite " << endl;

            }

        }

        if(randomN == 1 && pos[index][0]!=0)
        {
            if(!block[pos[index][0] -1]   [pos[index][1]].isBroken() )
            {
            pos[index2][0] = pos[index][0] -1;
            pos[index2][1] = pos[index][1];
            block[pos[index][0]]   [pos[index][1]].brokeL();
            block[pos[index2][0]]   [pos[index2][1]].brokeR();
            index=index2;
            hadMove=true;
//                                cout << " en gauche" << endl;

            }

        }

        if(randomN == 2 && pos[index][1]!=width-1)
        {
            if(!block[pos[index][0] ]   [pos[index][1] +1].isBroken() )
            {
            pos[index2][0] = pos[index][0];
            pos[index2][1] = pos[index][1] + 1 ;

            block[pos[index][0]]   [pos[index][1]].brokeB();
            block[pos[index2][0]]   [pos[index2][1]].brokeT();
            index=index2;
            hadMove=true;
            }

        }

        if(randomN == 3 && pos[index][1]!=0)
        {
            if(!block[pos[index][0] ]   [pos[index][1] -1].isBroken())
            {
                pos[index2][0] = pos[index][0];
                pos[index2][1] = pos[index][1] - 1 ;
                block[pos[index][0]]   [pos[index][1]].brokeT();
                block[pos[index2][0]]   [pos[index2][1]].brokeB();
                index = index2;
                hadMove=true;
            }
        }

        if( pos[index][1] == 0)
            canBottom=false;
        else if(block[pos[index][0] ]   [pos[index][1] -1].isBroken() )
            canBottom = false;

         if( pos[index][1] == width-1)
            canTop = false;
         else if(block[pos[index][0] ]   [pos[index][1] +1].isBroken() )
            canTop = false;

         if( pos[index][0] == width-1)
            canRight=false;
         else if(block[pos[index][0] +1 ]   [pos[index][1]].isBroken() )
            canRight = false;

         if( pos[index][0] == 0)
            canLeft = false;
         else if(block[pos[index][0] -1]   [pos[index][1]].isBroken() )
            canLeft = false;

        if(!canBottom && !canTop && !canRight && !canLeft )
            index--;


        canRight=true;
        canLeft=true;
        canBottom=true;
        canTop=true;

        if(index2 != width*width)
            makeLaby();
}
