#include <iostream>
#include <NTL/ZZ.h>
#include <string>
#include "RSA.h"

using namespace std;
using namespace NTL;

/******************************************************************************************************/
        string zztostring(const ZZ &z){
            stringstream buffer;
            buffer << z;
            return buffer.str();
        }
/******************************************************************************************************/
        ZZ strtozz(string p){
            char oracion[1000];
            strcpy(oracion,p.c_str());
            return conv<ZZ>(oracion);
        }
/******************************************************************************************************/


int main()
{
    ZZ d,e,n,m;

/*****   GENERAR CLAVES   *****************************/
/*  P: 12923  Q:7867
    Clave Privada: 95856301,101665241
    Clave Publica: 81906661,101665241
*/

    RSA r1(16);

/******************************************************/
/*****   CIFRADO   ************************************/
/******************************************************/
    string _d = "81906661";
    string _n = "101665241";

    d = strtozz(_d);
    n = strtozz(_n);

    RSA r2(d,n,true);
    r2.cifrado("ERNESTOCUADROSVARGAS");

/******************************************************/
/********   DECIFRADO   *******************************/
/******************************************************/

    string _e = "95856301";
           _n = "101665241";
    string _m = "038408582094182986061083340095673469079173376";

    e = strtozz(_e);
    n = strtozz(_n);

    RSA r3(e,n,false);
    r3.decifrado(_m);

    return 0;
}
