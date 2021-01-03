#include "DH.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <NTL/ZZ.h>
#include <time.h>
#include <stdlib.h>


using namespace std;
using namespace NTL;

DH::DH(int nBits){
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

    srand(time(NULL));
    ZZ dos(2);

    for (ZZ i(p/2); i<p-1; i++){
        if ((expMod(i,dos,p)!= 1) && (expMod(i,q,p)!= 1) && eucExt(i,p,1)==1 ){
            g=i;
            break;
        }
    }

    a=1+RandomBnd(p-1);
    A=expMod(g,a,p);

    cout << endl <<  "p: " << p << endl;
    cout << "g: " << g << endl;
    cout << "A: " << A << endl << endl;

}


DH::DH(ZZ _p, ZZ _g, ZZ _a){
    p=_p;
    g=_g;
    a=_a;

    A=expMod(g,a,p);

    cout << endl <<  "p: " << p << endl;
    cout << "g: " << g << endl;
    cout << "A: " << A << endl << endl;
}
/*****************************************************************************************************/

ZZ DH::modulo (ZZ x, ZZ y){
        x=x-(x/y)*y;
        if(x<0)
            return x+y;
        return x;
}

/*****************************************************************************************************/

ZZ DH::expMod(ZZ a, ZZ e, ZZ m){
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

ZZ DH::eucExt(ZZ n1, ZZ n2,int i){
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


ZZ DH::obtenerClave(ZZ B){

    K=expMod(B,a,p);
    cout << "----> K: " << K << endl;

    return K;

}
