#include <iostream>
#include <NTL/ZZ.h>
#include <string>

using namespace std;
using namespace NTL;


ZZ modulo (ZZ x, ZZ y){
        x=x-(x/y)*y;
        if(x<0)
            return x+y;
        return x;
        }

ZZ PowMod(ZZ a, ZZ n, ZZ m){
            ZZ exp;
            exp=1;
            ZZ x;
            x = modulo(a,m);
            ZZ par(2);
            while(n>0){
                if((modulo(n,par))!=0){
                    exp = exp*x;
                    exp = modulo((exp),m);
                }

                x=x*x;
                x = modulo(x,m);
                n = n/2;
            }
            return exp;
        }

bool Fermat(ZZ p, int iterations){
    if (p == 1) return false;
    for (int i = 0; i < iterations; i++){
        ZZ a ;
        a= RandomBnd(p);
        if (PowMod(a, p - 1, p) != 1) return false;
    }
    return true;
}

ZZ strtozz(string p){
            char oracion[1000];
            strcpy(oracion,p.c_str());
            return conv<ZZ>(oracion);
        }

int main()
{
    //PRIMO
    string n = {"130113293464585753548631829500459392680801641319400199570568161233975322936142681549444412195131969949338096611592050502994326929763464049517689769582491531292029273434962878569998128660688531894161805525193484376030504745351075074192221039951125687586545407564400363588540840552969281812490730526778205630547"};
    //COMPUESTO
    //string n = {"130113293464585753548631829500459392680801641319400199570568161233975322936142681549444412195131969949338096611592050502994326929763464049517689769582491531292029273434962878569998128660688531894161805525193484376030504745351075074192221039951125687586545407564400363588540840552969281812490730526778205630548"};

    ZZ a;
    a= strtozz(n);
    cout<<Fermat(a, 100)<<endl;



    return 0;
}
