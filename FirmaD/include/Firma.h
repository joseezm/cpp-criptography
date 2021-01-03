#ifndef FIRMA_H
#define FIRMA_H
#include <iostream>
#include <NTL/ZZ.h>
#include <string>
#include <sstream>

using namespace std;
using namespace NTL;

class Firma
{
    public:
        //string alf ={"ABCDEFGHIJKLMNOPQRSTUVWXYZ.,-_()abcdefghijklmnopqrstuvwxyz 0123456789"};
        string alf ={"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
        ZZ p,q,n,fi_n,e,d,p_Inv,q_Inv,claveE,claveN;

        Firma(int nBits);
        Firma(ZZ _e,ZZ _d,ZZ _n, ZZ _E, ZZ _N);
        ZZ invMod(ZZ a, ZZ b);
        ZZ eucExt(ZZ n1, ZZ n2,int i);
        ZZ modulo (ZZ x, ZZ y);
        ZZ expMod(ZZ a, ZZ e, ZZ m);
        ZZ restochino(ZZ x1, ZZ x2);
        string zztostring(const ZZ &z);
        ZZ strtozz(string p);
        string cifradoRSA (ZZ e, ZZ n, string texto);
        string decifradoRSA (ZZ d, ZZ n, ZZ _p, ZZ _q, string texto);
        void cifrado (string texto);
        void decifrado (string texto);

};

#endif // FIRMA_H
