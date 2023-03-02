#include "Game.h"

using namespace irr;
using namespace std;
using namespace scene;
using namespace video;
using namespace core;

Game::Game()
{
    i=0;
    indexWay=0;
    posX=50;
    deltaTime=0;
    deltaTime2=0;
    moveSlender=RIGHT;
    poneyTime=-4000;
    totalMove=0;
    distance = 70;
    prosecution = false;
    lose = false;
    poney = true;
    fPressed=false;
    gagner=false;
    posCamera.set(50,-5, 200);
    posSlender.set(50,0,50);

    FMOD_System_Create( &system );
    FMOD_System_Init(system, 32, FMOD_INIT_NORMAL, NULL);

    FMOD_System_CreateSound(system, "bruit1.wav", FMOD_CREATESTREAM, 0, &bruitage1);   // ces bruitages sont en fait les bruits de fond
    FMOD_System_CreateSound(system, "bruit2.wav", FMOD_CREATESTREAM, 0, &bruitage2);  // en fonction du nombre d'objectifs attein, celui ci
    FMOD_System_CreateSound(system, "bruit3.wav", FMOD_CREATESTREAM, 0, &bruitage3);  // gagne en intensité
    FMOD_System_CreateSound(system, "lose.wav", FMOD_CREATESTREAM, 0, &loseBruitage );
    FMOD_System_CreateSound(system, "sonAnim.mp3", FMOD_CREATESTREAM, 0, &sonAnim );
    FMOD_System_CreateSound(system, "bruitageMarche.mp3", FMOD_CREATESTREAM, 0, &sonMarche );


    device = createDevice(    // creation du device
        EDT_OPENGL,
        dimension2d<u32>(1920,1080),
        32,true,true,false,0);

    driver = device->getVideoDriver();                  // creation du driver
    sceneManager = device->getSceneManager ();                // creation du scene manager
    device->getCursorControl()->setVisible(false);
    temps = device->getTimer();
    device->setEventReceiver(&event);

    map = new Map(sceneManager, driver, SIZE);
    joueur = new Personnage(map);
    slender = new Personnage(map, sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh("slender.obj")),
                                    driver->getTexture("slender.png"));

    lumiere =  sceneManager->addLightSceneNode(0, vector3df(200, 2000, 200), SColor(200,125,125,125), 700);
    lumiereFPS =  sceneManager->addLightSceneNode(0, vector3df(0, 0, 0), SColor(100,100,100,100), 20);
    lumiereFPS->getLightData().DiffuseColor = SColor(120,255,170,170);

    keyMap[0].Action = EKA_MOVE_FORWARD;  // avancer
    keyMap[0].KeyCode = KEY_KEY_Z;        // z
    keyMap[1].Action = EKA_MOVE_BACKWARD; // reculer
    keyMap[1].KeyCode = KEY_KEY_S;        // s
    keyMap[2].Action = EKA_STRAFE_LEFT;   // a gauche
    keyMap[2].KeyCode = KEY_KEY_Q;        // q
    keyMap[3].Action = EKA_STRAFE_RIGHT;  // a droite
    keyMap[3].KeyCode = KEY_KEY_D;        // d

    camera = sceneManager->addCameraSceneNodeFPS(0, 100.0f, .1f, -1, keyMap, 4, true);
    camera->setPosition(vector3df(50, 10,150));
    camera->setTarget(vector3df(200, 0,200));

    anims =camera[0].getAnimators().begin();    //vitesse de la camera
    anim =(ISceneNodeAnimatorCameraFPS*)*anims;

    icare = driver->getTexture("icare3.png");
    ariane = driver->getTexture("pelotte.png");
    image = driver->getTexture("carre.png");


    remplirAnimation(0);
    map->draw(0, 0, 100);
    posSlender.set(rand()%SIZE  * map->getSizeCube() + map->getSizeCube()/2, posSlender.Y, rand()%SIZE * map->getSizeCube() + map->getSizeCube()/2);
    nbObjectif = 0;
    deltaTime2 = temps->getTime();
}

void Game::remplirAnimation(int i)
{
    stringw text  = "animFin/anim_000000.jpeg";
    text[17]=48+ i/10;
    text[18]=48+ i%10;
    loseAnimation[i] = driver->getTexture(text);
    if(i!=65)
        remplirAnimation(i+1);
}


void Game::theGoodWay(int xA, int yA, int xB, int yB)   // le chemin resolu automatiquement pour allez d'un point A à un point B
{
    map->RAZ(0);
    map->gett(xA, yA)->setAlgoVisited(true);
    indexWay=0;

    tabGoodWay[indexWay][0] = xA;
    tabGoodWay[indexWay][1] = yA;
    theGoodWayy(xA, yA, xB, yB);
}
void Game::theGoodWayy(int xA, int yA, int xB, int yB)
{
        xA = tabGoodWay[indexWay][0] ;
        yA = tabGoodWay[indexWay][1] ;

        if(map->get(xA, yA).getB() && !map->get(xA, yA+1).isVisitedAlgo())  // bas
        {
            tabGoodWay[indexWay][2] = 2;
            indexWay++;
            tabGoodWay[indexWay][0] = xA;
            tabGoodWay[indexWay][1] = yA+1;
            map->gett(xA, yA+1)->setAlgoVisited(true);

        }
        else if(map->get(xA, yA).getT() && !map->get(xA, yA-1).isVisitedAlgo()) // haut
        {
            tabGoodWay[indexWay][2] = 0;
            indexWay++;
            tabGoodWay[indexWay][0] = xA;
            tabGoodWay[indexWay][1] = yA-1;
            map->gett(xA, yA-1)->setAlgoVisited(true);
        }
        else if(map->get(xA, yA).getR() && !map->get(xA+1, yA).isVisitedAlgo()) // droite
        {
            tabGoodWay[indexWay][2] = 1;
            indexWay++;
            tabGoodWay[indexWay][0] = xA+1;
            tabGoodWay[indexWay][1] = yA;
            map->gett(xA+1, yA)->setAlgoVisited(true);

        }
        else if(map->get(xA, yA).getL() && !map->get(xA-1, yA).isVisitedAlgo()) //gauche
        {
            tabGoodWay[indexWay][2] = 3;
            indexWay++;
            tabGoodWay[indexWay][0] = xA-1;
            tabGoodWay[indexWay][1] = yA;
            map->gett(xA-1, yA)->setAlgoVisited(true);
        }
        else
            indexWay--;

    if(xA != xB || yA!=yB)
        theGoodWayy(xA, yA, xB, yB);
}




 void Game::run()
{

    while(device->run())          // La recursivité n'est pas possible ici, nous avons essayé, le programme plante au bout de 2 à 3 minutes environ (stack overflow)
    {
        driver->beginScene (true, true, SColor(120,120,120,120)); // on demarre la scene
        sceneManager->drawAll ();                  // on calule le rendu
       if(!lose && !gagner)
       {
            joueur->updatePlayer(camera->getPosition());

           if(camera->getPosition().Z > joueur->getminZ() && camera->getPosition().Z < joueur->getmaxZ() && camera->getPosition().X < joueur->getmaxX()  && camera->getPosition().X > joueur->getminX())
               posCamera=camera->getPosition();  // si le joueur veut se déplacer la ou il n'y a pas de mur alors la camera se déplace, sinon, elle revient en arrière.
           else
               camera->setPosition(posCamera);

          lumiereFPS->setPosition(camera->getPosition()); // position de la lumière


          if(joueur->getCell().isObjectif())       // lorsqu'un objectif est trouvé
          {
              nbObjectif++;
              map->gett(joueur->getXCell(), joueur->getZCell())->containObjectif(false);
              map->deleteObjectif(joueur->getXCell(), joueur->getZCell(), 0);
              deltaTime = - 30470;
              if(nbObjectif==6)
                gagner=true;
          }
           if(event.getF() && !fPressed)
           {
               poneyTime = temps->getTime();
               fPressed=true;
           }
           if(event.getF() && temps->getTime() - poneyTime < 70000) //temps des ailes d'icare
           {
               map->poneyWings(joueur->getXCell(), joueur->getZCell());
               poney = false;
           }
           if(nbObjectif == 1 || nbObjectif==2)
           {
               if(temps->getTime() - deltaTime>1950 )
               {
                   deltaTime = temps->getTime();
                   FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, bruitage1, 0, NULL);

               }
           }
           else if(nbObjectif == 3 || nbObjectif == 4)
           {
               if(temps->getTime() - deltaTime>6700 )
               {
                   deltaTime = temps->getTime();
                   FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, bruitage2, 0, NULL);
               }
           }
           else if( nbObjectif == 5 && temps->getTime() - deltaTime>30470 )
           {
               deltaTime = temps->getTime();
               FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, bruitage3, 0, NULL);

           }
           if(i==0)
                driver->draw2DImage( ariane, position2d<s32>(1920-400, 1080-190), rect<s32>(0,0,195,190), 0, SColor(255,255,255,255), true);
            if(fPressed == false)
                driver->draw2DImage( icare, position2d<s32>(1920-126, 900), rect<s32>(0,0,126,92), 0, SColor(255,255,255,255), true);
            if(prosecution)
                driver->draw2DImage(image, position2d<s32>(0, 0), rect<s32>(0,0,1920,1080),
                             0, SColor(70,255,0,0), true);
           if((event.getG() || i>0) && i < 200)
               particle();
          slenderUpdate();
           map->update();

       }
       else if(lose)
       {
           if(temps->getTime() - deltaTime2<=1000)
            {
                camera->setTarget(vector3df(posSlender.X*(temps->getTime()-deltaTime2)/1000, focus.Y + (posSlender.Y-focus.Y)*(temps->getTime()-deltaTime2)/1000, focus.Z + (posSlender.Z-focus.Z)*(temps->getTime()-deltaTime2)/1000));
            }
            else if(temps->getTime() - deltaTime2<=2000)    {                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sonAnim, 0, NULL);    }
            else if(temps->getTime()  - deltaTime2 < 4400)
            {
                driver->draw2DImage( loseAnimation[(int)((temps->getTime()-(float)deltaTime2 - 2000)/2400*65)], position2d<s32>(0, 0), rect<s32>(0,0,1920,1080),           0, SColor(255,255,255,255), true);
            }
            else
            {
                device->closeDevice();
                cout << endl << " you lose ! " << endl ;
                getchar();
            }

       }
       else if(gagner)
       {
            device->closeDevice();
            cout << "You win !!! " << endl;
            getchar();
       }
           driver->endScene ();                       // on affiche le rendu

    }

}



void Game::newWay(int percentageGoodWay)    //Trouver un nouveau chemin pour Slender
{
    random = rand()%4;

        theGoodWay(slender->getXCell(), slender->getZCell(), joueur->getXCell(), joueur->getZCell());
        if(indexWay <=5 )
        {
            prosecution = true;
            anim->setMoveSpeed(0.15f);
        }
        if(indexWay >=7 )
        {
            if(prosecution)
            {
                posSlender.set(rand()%SIZE  * map->getSizeCube() + map->getSizeCube()/2, posSlender.Y, rand()%SIZE * map->getSizeCube() + map->getSizeCube()/2);
            }
            prosecution = false;
            anim->setMoveSpeed(0.10);
        }
    if(rand()%100 < percentageGoodWay)      //Mouvements de Slender
    {
        if(tabGoodWay[0][2] == 0 )
        {
            moveSlender = TOP;
            slender->setRotation(90);
        }
        else if(tabGoodWay[0][2] == 1 )
        {
            moveSlender = RIGHT;
            slender->setRotation(180);
        }
        else if(tabGoodWay[0][2] == 2 )
        {
            moveSlender = BACK;
            slender->setRotation(0);
        }
        else if(tabGoodWay[0][2] == 3 )
        {
            moveSlender = LEFT;
            slender->setRotation(-90);
        }
    }
    else if(random == 0 && slender->getCell().getR())
    {
        moveSlender = RIGHT;
        slender->setRotation(90);
    }
    else if(random == 1 && slender->getCell().getT())
    {
    moveSlender = TOP;
           slender->setRotation(180);
    }
    else if(random == 2 && slender->getCell().getB())
    {
        moveSlender = BACK;
        slender->setRotation(0);
    }
    else if(random == 3 && slender->getCell().getL())
    {
        moveSlender = LEFT;
        slender->setRotation(-90);
    }
    else
        newWay(-1);
}
void Game::slenderUpdate()
{
    if(nbObjectif >= 1)
    {
        if(!prosecution)        //vitesse et intelligence de slender en fonction des objectifs atteints
        {
            if(nbObjectif == 1 )
            { pourcentage = 20; speedSlender = 0.2f;        }
            if(nbObjectif == 2 )
            { pourcentage = 30; speedSlender = 0.3f;        }
            if(nbObjectif == 3 )
            { pourcentage = 50; speedSlender = 0.4f;        }
            if(nbObjectif == 4 )
            { pourcentage = 75; speedSlender = 0.5f;        }
            if(nbObjectif == 5 )
            { pourcentage = 100; speedSlender = 0.6f;        }
        }
        else
        {   pourcentage=100;    speedSlender = 0.3f;    }

       if(moveSlender == RIGHT)     // droite
       {
            posSlender.set(posSlender.X+speedSlender, posSlender.Y, posSlender.Z);
            slender->updateSlender(posSlender);
            totalMove+=speedSlender;
            if(totalMove>=map->getSizeCube())
            {
                totalMove=0;
                if(slender->getCell().getNbWall() == 1 || !slender->getCell().getR())
                        newWay(80);
            }
       }
       if(moveSlender == BACK)         // haut
       {
            posSlender.set(posSlender.X, posSlender.Y, posSlender.Z+speedSlender);
            slender->updateSlender(posSlender);
            totalMove+=speedSlender;
            if(totalMove>=map->getSizeCube())
            {
                totalMove=0;
                if(slender->getCell().getNbWall() == 1 || !slender->getCell().getB())
                    newWay(80);
            }
       }

        if(moveSlender == TOP)    //bas
       {
            posSlender.set(posSlender.X, posSlender.Y, posSlender.Z-speedSlender);
            slender->updateSlender(posSlender);
            totalMove+=speedSlender;
            if(totalMove>=map->getSizeCube())
             {
                 totalMove=0;
                if(slender->getCell().getNbWall() == 1 || !slender->getCell().getT())
                        newWay(80);
             }

       }
        if(moveSlender == LEFT)        // gauche
       {
            posSlender.set(posSlender.X-speedSlender, posSlender.Y, posSlender.Z);
            slender->updateSlender(posSlender);
            totalMove+=speedSlender;
            if(totalMove>=map->getSizeCube())
            {
                totalMove=0;
                if(slender->getCell().getNbWall() == 1 || !slender->getCell().getL())
                       newWay(80);
            }
       }
    }

    if(slender->getXCell() == joueur->getXCell() && slender->getZCell() == joueur->getZCell())
    {

        camera->remove();
        focus=camera->getTarget();
        deltaTime2=temps->getTime();
        lose=true;
        FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, loseBruitage, 0, NULL);
    }
}



void Game::particle()       // Il s'agit en fait du fil d'ariane, seulment, au lieu que se soit un fil, le joueur laisse derrière lui des gouttes de sang qui tombent du plafond
{
     if(canParticle(i))
        {
            particleSystem[i] = sceneManager-> addParticleSystemSceneNode(true);
            particleSystem[i]->setPosition(posCamera);
                emitter = particleSystem[i]->createBoxEmitter(aabbox3d<f32>(-25, 20, -25, 25, -20, 25), vector3df(0,-0.025f,0), 16, 20,
                                                            SColor(255,255,255,255), SColor(255,255,255,255), 700, 900, 0,
                                                            dimension2df(2,2), dimension2df(3,3));
            particleSystem[i]->setEmitter(emitter);
            particleSystem[i]->setMaterialFlag(irr::video::EMF_LIGHTING, false); // insensible a la lumiere
            particleSystem[i]->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);     // desactive zbuffer pour surfaces derriere

            particleSystem[i]->setMaterialTexture(0, driver->getTexture("sang.png"));     // on colle une texture
            particleSystem[i]->setMaterialType(EMT_TRANSPARENT_ADD_COLOR); // application transparence
                        i++;

        }
}
bool Game::canParticle(int n )        // possibilité de particules
{
    n--;
    if(n>=0)
        distance =   sqrt((particleSystem[n]->getPosition().X - posCamera.X) * (particleSystem[n]->getPosition().X - posCamera.X) +
            (particleSystem[n]->getPosition().Z - posCamera.Z) * (particleSystem[n]->getPosition().Z - posCamera.Z) ) ;
    if( distance < 70)
            return false;
    if(n>=0)
        return canParticle(n);
    else
        return true;
}
