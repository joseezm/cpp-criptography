#include "RSA.h"
#include <iostream>
#include <NTL/ZZ.h>
#include <string>
#include <sstream>

using namespace std;
using namespace NTL;

/*****************************************************************************************************/

RSA::RSA(int nBits)
{
        while(1){
            RandomBits(p,nBits);
            if (ProbPrime(p,20)) break;
        }
        while(1){
            RandomBits(q,nBits);

            if (ProbPrime(q,20)) break;
        }

        n=p*q;
        fi_n = (p-1)*(q-1);

        while(1){
            e = RandomBnd(fi_n);
            if (eucExt(e,fi_n,1)==1) break;
        }

        d=invMod(e,fi_n);

        p_Inv = expMod(n / p, p - 2 , p);
        q_Inv= expMod(n / q, q - 2, q);

        cout << "P: " <<p << "  Q:" << q<< endl;
        cout << "Clave Privada: " <<d << "," << n<< endl;
        cout << "Clave Publica: " <<e << "," << n << endl << endl;
}

/*****************************************************************************************************/

RSA::RSA(ZZ _e, ZZ _n, bool a)
{
            if(a)
                e=_e;
            else
                d=_e;
            n=_n;

            /******** P y Q *****/
            p=12923;
            q=7867;
            fi_n = (p-1)*(q-1);
            /******** P y Q *****/
            p_Inv = expMod(n / p, p - 2 , p);
            q_Inv= expMod(n / q, q - 2, q);
}

/*****************************************************************************************************/

ZZ RSA::invMod(ZZ a, ZZ b)
{
            ZZ inverso;
            inverso = eucExt(a,b,2);
            while(inverso<0)
                    inverso= inverso+b;
            return inverso;
}

/*****************************************************************************************************/

ZZ RSA::eucExt(ZZ n1, ZZ n2,int i){
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

ZZ RSA::modulo (ZZ x, ZZ y){
        x=x-(x/y)*y;
        if(x<0)
            return x+y;
        return x;
}

/*****************************************************************************************************/

ZZ RSA::expMod(ZZ a, ZZ e, ZZ m){
            if (modulo (fi_n,e-1) == 0 && a<n ){
                return a;
            }
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

ZZ RSA::restochino(ZZ x1, ZZ x2){
	ZZ x;
	x = ((q*p_Inv*x1) + (p*q_Inv*x2));
	x = modulo(x,n);
	return x;
}

/*****************************************************************************************************/

string RSA::zztostring(const ZZ &z){
            stringstream buffer;
            buffer << z;
            return buffer.str();
}

/*****************************************************************************************************/

ZZ RSA::strtozz(string p){
            char oracion[1000];
            strcpy(oracion,p.c_str());
            return conv<ZZ>(oracion);
}

/*****************************************************************************************************/

void RSA::cifrado (string texto)
{
            string textoCifrado;
            string texTamAlf;
            string texTamN;
            string aux;

            ZZ tamAlf (alf.size());
            int tamN = zztostring(n).size();

            tamN = tamN-1;

            /******** PONER TODOS LOS DIGITOS DEL MISMO TAMAÑO *****/
            for (int i=0; i< texto.size(); i++){
                if (alf.find(texto[i])<10){
                    texTamAlf+= "0" + zztostring(conv<ZZ>(alf.find(texto[i])));
                }
                else
                    texTamAlf+= zztostring(conv<ZZ>(alf.find(texto[i])));
            }

            /******** AUMENTAR LETRAS PARA PODER DIVIDIR *****/
            while (modulo(conv<ZZ>(texTamAlf.size()),conv<ZZ>(tamN))!=0){
                texTamAlf+= to_string(alf.find("W"));
            }

            /******** CIFRADO *****/
            for (int i=0; i< texTamAlf.size()/tamN ; i++){
                aux = texTamAlf.substr(i*tamN,tamN);

                aux= zztostring(expMod(strtozz(aux),e,n));

                while (aux.size() < zztostring(n).size())
                    aux.insert(0,"0");

                textoCifrado+= aux;
            }

            cout << "TC: " << textoCifrado << endl << endl;
            cout << "Clave Privada: " <<d << "," << n<< endl;
            cout << "Clave Publica: " <<e << "," << n << endl << endl;
}

/*****************************************************************************************************/

void RSA::decifrado (string texto)
{
            string textoDecifrado;
            string texTamAlf;
            string texTamN;
            string aux;

            ZZ tamAlf (alf.size());
            int tamN = zztostring(n).size();

            ZZ x1,x2;
            /******** DECIFRADO *****/
            for (int i=0; i<texto.size()/tamN; i++){
                aux = texto.substr(i*tamN,tamN);
                //aux = zztostring(expMod(strtozz(aux),d,n));

                x1=expMod(strtozz(aux),modulo(d,p-1),p);
                x2=expMod(strtozz(aux),modulo(d,q-1),q);
                aux=zztostring(restochino(x1,x2));

                while (aux.size() < (zztostring(n).size()-1))
                    aux.insert(0,"0");

                texTamAlf += aux;
            }

            /******** DIVIDIR EN TAMAÑO DEL ALFABETO *****/
            for (int j=0; j<texTamAlf.size()/2; j++){
                textoDecifrado += alf[stoi(texTamAlf.substr(2*j,2))];
            }

            cout << "TD: " << textoDecifrado << endl << endl;
            cout << "Clave Privada: " <<d << "," << n<< endl;
            cout << "Clave Publica: " <<e << "," << n << endl << endl;
}
