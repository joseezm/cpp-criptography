#include "Firma.h"
#include <iostream>
#include <NTL/ZZ.h>
#include <string>
#include <sstream>

using namespace std;
using namespace NTL;

/*****************************************************************************************************/

Firma::Firma(int nBits)
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

Firma::Firma(ZZ _e, ZZ _d, ZZ _n, ZZ _E, ZZ _N)
{
            e=_e;
            d=_d;
            n=_n;
            claveE=_E;
            claveN=_N;

    p=62311;
    q=16339;
    fi_n = (p-1)*(q-1);
    p_Inv = expMod(n / p, p - 2 , p);
    q_Inv= expMod(n / q, q - 2, q);



}

/*****************************************************************************************************/

ZZ Firma::invMod(ZZ a, ZZ b)
{
            ZZ inverso;
            inverso = eucExt(a,b,2);
            while(inverso<0)
                    inverso= inverso+b;
            return inverso;
}

/*****************************************************************************************************/

ZZ Firma::eucExt(ZZ n1, ZZ n2,int i){
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

ZZ Firma::modulo (ZZ x, ZZ y){
        x=x-(x/y)*y;
        if(x<0)
            return x+y;
        return x;
}

/*****************************************************************************************************/

ZZ Firma::expMod(ZZ a, ZZ e, ZZ m){
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

ZZ Firma::restochino(ZZ x1, ZZ x2){
	ZZ x;
	x = ((q*p_Inv*x1) + (p*q_Inv*x2));
	x = modulo(x,n);
	return x;
}

/*****************************************************************************************************/

string Firma::zztostring(const ZZ &z){
            stringstream buffer;
            buffer << z;
            return buffer.str();
}

/*****************************************************************************************************/

ZZ Firma::strtozz(string p){
            char oracion[1000];
            strcpy(oracion,p.c_str());
            return conv<ZZ>(oracion);
}

/*****************************************************************************************************/

string Firma::cifradoRSA (ZZ _e, ZZ _n, string texto)
{
            //cout << "D: " << _e << "N" << _n << endl;
            string textoCifrado;
            string texTamAlf = texto;
            string texTamN;
            string aux;

            ZZ tamAlf (alf.size());
            int tamN = zztostring(_n).size();

            tamN = tamN-1;

            while (modulo(conv<ZZ>(texTamAlf.size()),conv<ZZ>(tamN))!=0){
                texTamAlf+= to_string(alf.find("W"));
            }

            //cout << " CON W  " << texTamAlf << endl;
            for (int i=0; i< texTamAlf.size()/tamN ; i++){
                aux = texTamAlf.substr(i*tamN,tamN);

                aux= zztostring(expMod(strtozz(aux),_e,_n));
                //cout << "--> " << aux << endl;
                while (aux.size() < zztostring(_n).size())
                    aux.insert(0,"0");

                textoCifrado+= aux;
                //cout << "C " << i << " : " << textoCifrado << endl;
            }

            return textoCifrado;

}

/*****************************************************************************************************/

string Firma::decifradoRSA (ZZ _d, ZZ _n, ZZ _p, ZZ _q, string texto)
{           //cout << "D: " << _d << "N" << _n << endl;
            string textoDecifrado;
            string texTamAlf;
            string texTamN;
            string aux;

            ZZ tamAlf (alf.size());
            int tamN = zztostring(_n).size();

            ZZ x1,x2;
            //cout << texto.size()/tamN << endl;
            for (int i=0; i<texto.size()/tamN; i++){
                aux = texto.substr(i*tamN,tamN);

                //if (_p== 0 && _q == 0)
                if(1)
                    aux = zztostring(expMod(strtozz(aux),_d,_n));
                else{
                    x1=expMod(strtozz(aux),modulo(_d,_p-1),_p);
                    x2=expMod(strtozz(aux),modulo(_d,_q-1),_q);
                    aux=zztostring(restochino(x1,x2));
                }

                while (aux.size() < (zztostring(_n).size()-1))
                    aux.insert(0,"0");

                texTamAlf += aux;
                //cout << "C " << i << " : " << aux << endl;
            }

            //cout << "TD: " << textoDecifrado << endl << endl;
            //cout << "Clave Usada: " <<_d << "," << _n<< endl;
            return texTamAlf;
}


void Firma::cifrado(string texto){
    string texTamAlf;
            for (int i=0; i< texto.size(); i++){
                if (alf.find(texto[i])<10){
                    texTamAlf+= "0" + zztostring(conv<ZZ>(alf.find(texto[i])));
                }
                else
                    texTamAlf+= zztostring(conv<ZZ>(alf.find(texto[i])));
            }
    string aux;

    //cout << "TEXTO CON ALF: " << texTamAlf << endl;
    aux = cifradoRSA(claveE,claveN,texTamAlf);
    //cout << "CIFRADO 1 : " << texTamAlf << endl;
    aux= cifradoRSA (d,n,aux);
    //cout << "CIFRADO 2: " << texTamAlf << endl;
    aux = cifradoRSA(claveE,claveN,aux);

    cout << "TC: " << aux << endl << endl;
}

void Firma::decifrado(string texto){
    ZZ zero(0);

    string aux;
    string textoDecifrado;

    aux = decifradoRSA(d,n,p,q,texto);
    aux= decifradoRSA (claveE,claveN,zero,zero,aux);
    aux = decifradoRSA(d,n,p,q,aux);

    for (int j=0; j<aux.size()/2; j++){
        textoDecifrado += alf[stoi(aux.substr(2*j,2))];
    }

    cout << "TD: " << textoDecifrado << endl;
}
