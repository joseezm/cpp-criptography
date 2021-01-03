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
/*  Clave Privada: 859600519,976225717
    Clave Publica: 881550279,976225717   */

    RSA r1(16);

/******************************************************/
/*****   CIFRADO   ************************************/
/******************************************************/
    string _d = "173";
    string _n = "26832";

    d = strtozz(_d);
    n = strtozz(_n);

    RSA r2(d,n,true);
    r2.cifrado("ERNESTOCUADROSVARGAS");

/******************************************************/
/********   DECIFRADO   *******************************/
/******************************************************/

    string _e = "859600519";
           _n = "976225717";
    string _m = "333912434427335930907578514753709589";

    e = strtozz(_e);
    n = strtozz(_n);

    RSA r3(e,n,false);
    r3.decifrado(_m);

    return 0;
}
