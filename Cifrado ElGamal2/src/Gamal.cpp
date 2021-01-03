#include "Gamal.h"
#include <iostream>
#include <NTL/ZZ.h>
#include <string>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;
using namespace NTL;

/*****************************************************************************************************/

Gamal::Gamal(int nBits)
{
    bool Prime=true;

    while(Prime){
        GenPrime(p,nBits);
        if (ProbPrime(p,20)){
            q=(p-1)/2;
            if (ProbPrime(q,20)){
                Prime=false;
            }
        }
    }


    /// ALGORITMO DE RAIZ PRIMITIVA
    srand(time(NULL));
    vector<ZZ> raices;
    ZZ dos(2);
    /*
    for (ZZ g(1); g<p-1; g++){
        if ((expMod(g,dos,p)!= 1) && (expMod(g,q,p)!= 1)){
            raices.push_back(g);
            cout << g << endl;
        }
    }
    */

    for (ZZ g(p/2); g<p-1; g++){
        if ((expMod(g,dos,p)!= 1) && (expMod(g,q,p)!= 1)){
            raices.push_back(g);
            break;
        }
    }

    e_1=raices[RandomBnd(raices.size())];

    d = 2 + RandomBnd(p-2); // PRIVADA
    e_2=expMod(e_1,d,p);

    cout << "CPu:     e1: " <<  e_1 << " e2: " << e_2 << " p: " << p << endl;
    cout << "CPr:     d: " << d << endl;
}

/*****************************************************************************************************/
Gamal::Gamal(ZZ e1, ZZ e2, ZZ p_, ZZ d_){
    e_1=e1;
    e_2=e2;
    p=p_;
    d=d_;
}
/*****************************************************************************************************/

ZZ Gamal::invMod(ZZ a, ZZ b)
{
            ZZ inverso;
            inverso = eucExt(a,b,2);
            while(inverso<0)
                    inverso= inverso+b;
            return inverso;
}

/*****************************************************************************************************/

ZZ Gamal::eucExt(ZZ n1, ZZ n2,int i){
            ZZ res[3],x(0),y(0),x2(1),x1(0),y2(0),y1(1),q(0),r(0);
            ZZ auxn2(n2);

            if(n2==0){
                res[0]=n1;
                res[1]=1;
                res[2]=0;
            }
            else{
                while(n2>0){
                    q=(n1/n2);
                    r= n1-(q*n2);
                    x= x2-(q*x1);
                    y= y2 - (q*y1);
                    n1= n2;
                    n2 = r;
                    x2= x1;
                    x1 = x;
                    y2 = y1;
                    y1 =y;
                }
                res[0]=n1;
                res[1]=x2;
                res[2]=y2;

            }

            if(i==1) return res[0];
            else if (i==2) return res[1];
            else if (i==3) return res[2];

}

/*****************************************************************************************************/

ZZ Gamal::modulo (ZZ x, ZZ y){
        x=x-(x/y)*y;
        if(x<0)
            return x+y;
        return x;
}

/*****************************************************************************************************/

ZZ Gamal::expMod(ZZ a, ZZ e, ZZ m){
            ZZ exp;
            exp=1;
            ZZ x;
            x = modulo(a,m);
            ZZ par(2);
            while(e>0){
                if((modulo(e,par))!=0){
                    exp = exp*x;
                    exp = modulo(exp,m);
                }
                x=x*x;
                x = modulo(x,m);
                e = e/2;
            }
            return exp;
}

/*****************************************************************************************************/

string Gamal::completarzero(string num, int tam){
    for (int i=0; i<tam; i++){
        num.insert(0,"0");
    }
    return num;
}

/*****************************************************************************************************/

string Gamal::zztostring(const ZZ &z){
            stringstream buffer;
            buffer << z;
            return buffer.str();
}

/*****************************************************************************************************/

ZZ Gamal::strtozz(string p){
            char oracion[1000];
            strcpy(oracion,p.c_str());
            return conv<ZZ>(oracion);
}

/*****************************************************************************************************/

string Gamal::cifrado(string texto){

    string textoCifrado;

    ZZ r (2+ RandomBnd(p-2));
    ZZ C_1 (expMod(e_1,r,p));
    ZZ K_m (expMod(e_2,r,p));

    string nDigAlf = to_string(alf.size());
    ZZ tamAlfabeto(nDigAlf.size());

    //cout << "tam    " << tamAlfabeto << endl;

    //cout << "C1 " << C_1 << endl;
    //cout << "Km " << K_m << endl;

    string aux;
    /*
    string P;
    for(int i=0; i<texto.size(); i++){
        aux=to_string(alf.find(texto[i]));
        if (aux.size()< tamAlfabeto)    aux=completarzero(aux,conv<int>(tamAlfabeto)-aux.size());
        P+=aux;
    }
    */

    //cout << P << endl;

    string nDigP=zztostring(p);
    ZZ tamP(nDigP.size());
    string tamC1 =zztostring(C_1);

    textoCifrado=completarzero(tamC1,conv<int>(tamP)- tamC1.size());

    //cout << "c1 " << textoCifrado << endl;

    for(int i=0; i<texto.size();i++){
        aux = zztostring(modulo(conv<ZZ>(alf.find(texto[i]))*K_m,p));
        if(aux.size() < tamP) aux=completarzero(aux,conv<int>(tamP)-aux.size());
        textoCifrado+=aux;
    }

    cout << "TC: " << textoCifrado << endl;

}

/*****************************************************************************************************/

string Gamal::decifrado(string texto){
    string textoDecifrado;

    string nDigAlf = to_string(alf.size());
    ZZ tamAlfabeto(nDigAlf.size());

    string nDigP=zztostring(p);
    ZZ tamP(nDigP.size());

    ZZ C1(strtozz(texto.substr(0,conv<int>(tamP))));
    texto.erase(0,conv<int>(tamP));

    ZZ Km(expMod(C1,d,p));
    ZZ invKm(invMod(Km,p));

    ZZ bloque;
    ZZ aux;

    for (ZZ i(0); i < conv<ZZ>(texto.size()/conv<int>(tamP)); i++){
        aux = (strtozz(texto.substr(conv<int>(i*(tamP)),conv<int>(tamP))))*invKm;
        bloque = modulo(aux,p);
        textoDecifrado += alf[conv<int>(bloque)];
    }

    cout << "TD: " << textoDecifrado;
}

/*****************************************************************************************************/
