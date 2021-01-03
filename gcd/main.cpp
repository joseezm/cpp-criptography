#include <iostream>
#include <NTL/ZZ.h>
#include <string>
#include <sstream>

using namespace NTL;
using namespace std;

ZZ strtozz(string p){
    char oracion[1000];
    strcpy(oracion,p.c_str());
    return conv<ZZ>(oracion);
}

ZZ Min(ZZ a, ZZ b){
    ZZ m;
    m=a;
    if (a>b)
        m=b;

    return m;
}

ZZ modulo (ZZ x, ZZ y){
    x=x-(x/y)*y;
    if(x<0)
       return x+y;
    return x;
}

ZZ lsbgcd (ZZ u, ZZ v){
    ZZ t,aux;
    int s;
    while(v!=0){
        s=0;
        while ((v<<s) <= u){
            s++;
        }
        s=s-1;
        t= Min(u-(v<<s),(v<<(s+1))-u);
        u=v;
        v=t;
        if(u<v){
            aux=u;
            u=v;
            v=aux;
        }
    }
    return u;
    }

ZZ binary_shift(ZZ u,ZZ v){
    ZZ shift;
    if (u == 0) return v;
    if (v == 0) return u;
    for (shift = 0; ((u | v) & 1) == 0; ++shift) {
        u= u >> 1;
        v= v >> 1;
    }
    while ((u & 1) == 0){
        u= u >> 1;
    }
    do{
        while ((v & 1) == 0)
            v= v >> 1;
        if (u > v) {
            ZZ t (v); v = u; u = t;
       }
       v = v - u;
    }
    while (v != 0);

    return u<<conv<int>(shift);
}

ZZ euclides(ZZ a, ZZ b){
    ZZ r;
    while( b != 0){
        r=modulo(a,b);
        a=b;
        b=r;
    }
    return a;
    }

ZZ mcdMenorResto(ZZ a, ZZ b){
    ZZ c, d, r, t;
    if(a == 0){c = b;}
    else{
        c = a;
        d = b;
        while (d != 0){
            t = abs(c - d * (c/d + 1));
            r = abs(c - d * (c/d));
            c = d;
            (r<t)? d = r : d = t;
        }
    }
    return abs(c);
    }




ZZ binarioExt(ZZ x, ZZ y){
    ZZ g(1);
    while(!bit(x,0) && !bit(y,0)){
        x>>=1;
        y>>=1;
        g<<=1;
    }
    ZZ u = x;
    ZZ v = y;
    ZZ A(1), B(0),C(0),D(1);
    while(u.size()){
        while(!bit(u,0)){
            u>>=1;
            if(!bit(A,0) && !bit(B,0)){
                A>>=1;
                B>>=1;
            }
            else{
                (A+=y)>>=1;
                (B-=x)>>=1;
            }
        }
        while(!bit(v,0)){
            v>>=1;
            if(!bit(C,0) && !bit(D,0)){
                C>>=1;
                D>>=1;
            }
            else{
                (C+=y)>>=1;
                (D-=x)>>=1;
            }
        }
        if(u>=v){
            u-=v;
            A-=C;
            B-=D;
        }
        else{
            v-=u;
            C-=A;
            D-=B;
        }
    }
    return modulo(C,y);
}

int main()
{
    ZZ a;
    ZZ b;
    //GenPrime(a ,1024);
    //GenPrime(b ,1024);

    string aS = "124615023188993992885901641809243756333040975311618463254736450399749647038154785576964339109500208811685518518531262092371020508887365047770420179888526564796789241356626902744021662725684196687540800225705170063436443454338109006914545556956980265632655889899934299826218791047745014361386580628524671598583";
    string bS = "132823426805319357026778617541949478719147749274788714878934973089592723384041092427588713736525026882758966766831448155383082347489588419011067866626599802933519318136594251447914698273846560843795974566254270098781030264617111581381739221066929554315678928195234914861740102241217337015155393496054989613929";
    a =strtozz(aS);
    b = strtozz(bS);

    cout << binarioExt(a,b);

    return 0;
}
