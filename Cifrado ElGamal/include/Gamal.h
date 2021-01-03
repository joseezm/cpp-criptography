#ifndef GAMAL_H
#define GAMAL_H

#include <iostream>
#include <NTL/ZZ.h>
#include <string>
#include <sstream>

using namespace std;
using namespace NTL;

class Gamal
{
    public:
        //string alf ={"ABCDEFGHIJKLMNOPQRSTUVWXYZ.,-_()abcdefghijklmnopqrstuvwxyz 0123456789"};
        string alf ={"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
        ZZ p,q,e_1,d,e_2;
        int nBits;

        Gamal(int n);
        Gamal(ZZ e1, ZZ e2, ZZ p_, ZZ d_);
        ZZ invMod(ZZ a, ZZ b);
        ZZ eucExt(ZZ n1, ZZ n2,int i);
        ZZ modulo (ZZ x, ZZ y);
        ZZ expMod(ZZ a, ZZ e, ZZ m);
        string completarzero(string num, int tam);
        string zztostring(const ZZ &z);
        ZZ strtozz(string p);
        string cifrado(string texto);
        string decifrado(string texto);



};

#endif // GAMAL_H
