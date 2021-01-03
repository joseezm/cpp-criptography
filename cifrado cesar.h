#ifndef CESAR_H
#define CESAR_H
#include <string>
#include <iostream>

using namespace std;

class cesar
{
    public:
        string alf = "abcdefghijklmnopqrstuvwxyz";
        int clave;
        cesar(int c){
        clave=c;
        };

        string cifrado(string texto){
            string textoC;
            for(int i=0; i<texto.length(); i++){
                int aux = alf.find(texto[i]);
                aux+=clave;
                while(aux>alf.length())
                    aux-=alf.length();

                textoC+=alf[aux];
            }
            return textoC;
        }

        string decifrado(string texto){
            string textoD;
            for(int i=0; i<texto.length(); i++){
                int aux = alf.find(texto[i]);
                aux-=clave;
                while(aux<0)
                    aux+=alf.length();

                textoD+=alf[aux];
            }
            return textoD;
        }
};

#endif // CESAR_H
