#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <irrlicht.h>
#include <iostream>
#include <cstdlib>
#define SIZE 10
#include "Map.h"
#include "Personnage.h"
#include "Cell.h"
#include "include/eventType.h"
#include <string>
#include <fmodex/fmod.h>
#include <math.h>

enum side { TOP=0, BACK=2, RIGHT=1, LEFT=3};

class Game
{
    public :

    Game();
    void run();
    bool canParticle(int n);
    void particle();
    void slenderUpdate();
    void newWay(int pourcentage);
    void remplirAnimation(int i);
    void theGoodWay(int xA, int yA, int xB, int yB);
    void theGoodWayy(int xA, int yA, int xB, int yB);




  private :
    int i, random, indexWay;
    int posX;
    int deltaTime, deltaTime2, updateTime;
    eventType event;
    irr::core::vector3df posCamera, posSlender;
    irr::IrrlichtDevice *device ;
    irr::video::IVideoDriver* driver;
    irr::scene::ISceneManager *sceneManager;
    Map *map;
    Personnage *joueur, *slender;
    irr::ITimer *temps ;
    irr::scene::IParticleSystemSceneNode *particleSystem[200];
    irr::scene::IParticleEmitter *emitter;
    irr::scene::ILightSceneNode *lumiere;
    irr::scene::ILightSceneNode *lumiereFPS;
    irr::SKeyMap keyMap[4];
    irr::scene::ICameraSceneNode* camera;
    irr::core::list<irr::scene::ISceneNodeAnimator*>::ConstIterator anims;
    irr::scene::ISceneNodeAnimatorCameraFPS *anim;
    irr::video::ITexture *icare, *ariane, *loseAnimation[65], *image;
    FMOD_SOUND *bruitage1, *bruitage2, *bruitage3, *loseBruitage, *sonAnim, *sonMarche;
    FMOD_SYSTEM *system;
    FMOD_CHANNEL *channel;


    side moveSlender ;

    int tabGoodWay[20*20][3],  poneyTime;
    int nbObjectif;
    float speedSlender, totalMove, oppose, adjacent, distance;
    int pourcentage;
    bool prosecution , lose , poney , fPressed, gagner;
    irr::core::vector3df focus;
};

#endif // GAME_H_INCLUDED
