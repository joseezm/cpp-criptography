#ifndef DH_H
#define DH_H
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <NTL/ZZ.h>
#include <time.h>
#include <stdlib.h>


using namespace std;
using namespace NTL;

class DH
{
    public:
        ZZ p,q,g,a,b,A,K;
        DH(int nBits);
        DH(ZZ a_, ZZ _g, ZZ _a);
        ZZ obtenerClave(ZZ B);
        ZZ eucExt(ZZ n1, ZZ n2,int i);
        ZZ expMod(ZZ a, ZZ e, ZZ m);
        ZZ modulo (ZZ x, ZZ y);

};

#endif // DH_H
