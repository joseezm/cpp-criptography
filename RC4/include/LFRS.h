#ifndef LFRS_H
#define LFRS_H

#include <iostream>
#include <NTL/ZZ.h>
#include <string>
#include <sstream>
#include <bitset>
#include "RC4.h"

using namespace std;
using namespace NTL;

class LFRS
{
    public:
        int modulo(int x, int y);
        int nbits;
        int npart;
        bool corrimiento;
        string seed;

        LFRS(int n,int p, bool c);
        void crecerNum();
        void igualar();
        void r_taps();
        void particion();
        string derecha(string p);
        string izquierda(string p);
        ZZ binarytozz(string numero);
        ZZ Generar();

};

#endif // LFRS_H
