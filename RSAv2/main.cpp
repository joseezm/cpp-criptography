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
/*  Clave Privada: 421411990974233987,549480526021205029
    Clave Publica: 297396892706569259,549480526021205029   */

    RSA r1(8);

/******************************************************/
/*****   CIFRADO   ************************************/
/******************************************************/
    string _d = "229";
    string _n = "3306318923";
    string _m = "751";

    d = strtozz(_d);
    n = strtozz(_n);
    m = strtozz(_m);

    RSA r2(d,n,true);
    r2.cifrado("PERRO");

/******************************************************/
/********   DECIFRADO   *******************************/
/******************************************************/

    string _e = "2857";
           _n = "10363";
           _m = "1787";

    e = strtozz(_e);
    n = strtozz(_n);
    m = strtozz(_m);

    RSA r3(e,n);
    r3.decifrado(m);


    return 0;
}
