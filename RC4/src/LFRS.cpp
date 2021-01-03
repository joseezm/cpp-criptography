#include "LFRS.h"
#include "RC4.h"
#include <iostream>
#include <NTL/ZZ.h>
#include <string>
#include <sstream>
#include <stdlib.h>

#include <time.h>
#include <bitset>
#include "RC4.h"

using namespace std;
LFRS::LFRS(int n,int p, bool c)
{
    nbits=n;
    npart=p;
    corrimiento=c;  // c=1 <-- --> // c=0 --> <--//
    RC4 semilla(n*(0.1)+1);
    seed=semilla.Generar();
}

int LFRS::modulo(int x, int y){
    x=x-(x/y)*y;
    if(x<0)
        return x+y;
    return x;
}

void LFRS::crecerNum(){
    for (int t=0;seed.size()!=nbits;t++){
        if(seed[t+1]==seed[t])
            seed.append("0");
        else
            seed.append("1");
    }
}

void LFRS::igualar(){
    int cont0=0;
    int cont1=0;
    int dif;
    for (int i=0; i<seed.size(); i++){
        if (seed[i]=='0') cont0++;
        else cont1++;
    }

    dif=cont0-cont1;
    if (dif<0){
            for (int i=seed.size()/rand()%nbits; i>0 && dif!=0; i--){
                if (seed[i]=='1'){
                    seed[i]='0';
                    dif++;
                }
            }
    }
    else{
            for (int i=seed.size()/rand()%nbits; i>0 && dif!=0; i--){
                if (seed[i]=='0'){
                    seed[i]='1';
                    dif--;
                }
            }
    }
}

void LFRS::r_taps(){
    int ntaps = (nbits)*(0.1)+3;
    if(modulo(ntaps,2)==0) ntaps--;

    int taps[ntaps];
    for (int i=0; i<ntaps; i++){
        taps[i]=1+rand()%nbits;
    }

    taps[ntaps-1]=1;

    int sum_taps =0;
    seed = izquierda(seed);

    for(int i=0; i<ntaps; i++){
        if(seed[taps[i]]=='1'){
            sum_taps+=1;
        }

    }
    if (seed[0]=='1') sum_taps++;
    sum_taps=modulo(sum_taps,2);

    if(sum_taps==0)
        seed[nbits-1]='0';
    else
        seed[nbits-1]='1';


}


string LFRS::derecha(string p){
    char aux = p[p.size()-1];
    for(int i=p.size()-1; i>0;i--){
        p[i]=p[i-1];
    }
    p[0]=aux;
    return p;
}

string LFRS::izquierda(string p){
    char aux = p[0];
    for(int i=0; i<p.size()-1;i++){
        p[i]=p[i+1];
    }
    p[p.size()-1]=aux;

    return p;
}

ZZ LFRS::binarytozz(string numero){
    ZZ suma(0);
    ZZ dos(2);
    int contadorbits=numero.size()-1;
    int potencia=numero.size()-2;
    while(contadorbits>=0){
        if(contadorbits==0 && numero[contadorbits]=='1' ) suma+=conv<ZZ>(1);
        else if(numero[contadorbits]=='1') suma+= dos<<potencia;
        contadorbits--;
        potencia--;
    }

    return suma;
}

void LFRS::particion(){
    string partes[npart];
    int tam_partes=nbits/npart;

    partes[0]=seed.substr(0,tam_partes+modulo(seed.size(),npart));
    seed.erase(0,tam_partes+modulo(seed.size(),npart));

    for (int i=0; i<npart-1; i++){
        partes[i+1]=seed.substr(0,tam_partes);
        seed.erase(0,tam_partes);
    }


    if (corrimiento==1){
        for(int i=0; i<npart;i++){
            if(modulo(i,2)==0)
                partes[i]=izquierda(partes[i]);
            else
                partes[i]=derecha(partes[i]);
        }
    }
    else{
        for(int i=0; i<npart;i++){
            if(modulo(i,2)==0)
                partes[i]=derecha(partes[i]);
            else
                partes[i]=izquierda(partes[i]);
        }
    }


    for (int i=0; i<npart;i++){
        seed+=partes[i];
    }
}

ZZ LFRS::Generar(){
    crecerNum();
    igualar();

    for (int i=0; i<16;i++){
        r_taps();
        particion();
    }

    //cout << seed << "   " << seed.size()<< endl;

    return binarytozz(seed);
}

