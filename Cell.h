#ifndef CELL_H_INCLUDED
#define CELL_H_INCLUDED
#include <iostream>
#include <string>

class Cell
{
    public:

    Cell();
    bool getR();
    bool getL();
    bool getT();
    bool getB();
    bool isBroken();
    void brokeR();
    void brokeL();
    void brokeT();
    void brokeB();
    void broke(char c);
    bool isVisited();
    void setVisited(bool visit);
    int getNbWall();
    void containObjectif(bool contain);
    bool isObjectif();
    void setAlgoVisited(bool visit);
    bool isVisitedAlgo();



    private:
    bool R; // Right
    bool L; // Left
    bool T; // Top
    bool B; // Bottom
    bool isVisit;
    bool containPaper;
    bool isSlenderVisit;
    bool isAlgoVisit;

};

#endif // CELL_H_INCLUDED
