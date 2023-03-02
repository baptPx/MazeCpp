#include "Cell.h"

using namespace std;

Cell::Cell()
{
    R=false;
    L=false;
    T=false;
    B=false;
    isVisit = false;
    isSlenderVisit = false;
    containPaper = false;
    isAlgoVisit = false;
}
bool Cell::getR()
{ return R; }
bool Cell::getL()
{ return L; }
bool Cell::getT()
{ return T; }
bool Cell::getB()
{ return B; }
bool Cell::isBroken()
{
    if(R || L || T ||B)
        return true;
    else
        return false;
}
void Cell::brokeR()
{   R = true; }
void Cell::brokeL()
{   L = true; }
void Cell::brokeT()
{   T = true; }
void Cell::brokeB()
{   B = true; }
void Cell::broke(char c)
{
    if(c == 'R' || c == 'r')
        R=true;
    if(c == 'L' || c == 'l')
        L=true;
    if(c == 'B' || c == 'b')
        B=true;
    if(c == 'T' || c == 't')
        T=true;
}
bool Cell::isVisited()
{   return isVisit; }
void Cell::setVisited(bool visit)
{ isVisit=visit;}

bool Cell::isVisitedAlgo()
{   return isAlgoVisit; }
void Cell::setAlgoVisited(bool visit)
{ isAlgoVisit=visit;}
int Cell::getNbWall()   // retourne le nombre de mur
{
    int nb = 0;
    if(!T)
        nb++;
    if(!B)
        nb++;
    if(!R)
        nb++;
    if(!L)
        nb++;
    return nb;
}
void Cell::containObjectif(bool contain)
{   containPaper = contain;}
bool Cell::isObjectif()
{   return containPaper;}
