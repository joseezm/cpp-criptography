#ifndef RSA_H
#define RSA_H
#include <iostream>
#include <NTL/ZZ.h>
#include <string>
#include <sstream>

using namespace std;
using namespace NTL;

class RSA
{
    public:
        //string alf ={"ABCDEFGHIJKLMNOPQRSTUVWXYZ.,-_()abcdefghijklmnopqrstuvwxyz 0123456789"};
        string alf ={"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
        ZZ p,q,n,fi_n,e,d,p_Inv,q_Inv;

        RSA(int nBits);
        RSA(ZZ _e,ZZ _n, bool a);
        ZZ invMod(ZZ a, ZZ b);
        ZZ eucExt(ZZ n1, ZZ n2,int i);
        ZZ modulo (ZZ x, ZZ y);
        ZZ expMod(ZZ a, ZZ e, ZZ m);
        ZZ restochino(ZZ x1, ZZ x2);
        string zztostring(const ZZ &z);
        ZZ strtozz(string p);
        void cifrado (string texto);
        void decifrado (string texto);

};

#endif // RSA_H
