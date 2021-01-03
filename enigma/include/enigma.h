#ifndef ENIGMA_H
#define ENIGMA_H
#include <string>
#include <iostream>

using namespace std;


class enigma
{
    public:
        string input =      "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        string rotor1 =     "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
        string rotor2 =     "AJDKSIRUXBLHWTMCQGZNPYFVOE";
        string rotor3 =     "BDFHJLCPRTXVZNYEIWGAKMUSQO";
        string reflector =  "YRUHQSLDPXNGOKMIEBFZCWVJAT";

        int clave;
        enigma(){};

        int modulo(int a, int n){
            a=a-(a/n)*n;
            if(a<0) return a+n;
            return a;
        }

        string cifrado(string texto){
            string textoC;
            string aux;
            for(int i=0; i<texto.length(); i++){
                aux = input[modulo(input.find(texto[i])+(i+1),input.length())];
                aux = rotor3[modulo(input.find(aux),input.length())];
                aux = input[modulo(input.find(aux)-(i+1),input.length())];
                aux = rotor2[modulo(input.find(aux),input.length())];
                aux = rotor1[modulo(input.find(aux),input.length())];
                aux= reflector[modulo(input.find(aux),input.length())];

                aux=input[modulo(rotor1.find(aux),input.length())];
                aux=input[modulo(rotor2.find(aux),input.length())];
                aux = input[modulo(input.find(aux)+(i+1),input.length())];
                aux=input[modulo(rotor3.find(aux),input.length())];
                aux = input[modulo(input.find(aux)-(i+1),input.length())];
                aux=input[input.find(aux)];
                textoC+=aux;
            }
            return textoC;
        }

        string decifrado(string texto){
            string textoC;
            string aux;
            for(int i=0; i<texto.length(); i++){
                aux = input[modulo(input.find(texto[i])+(i+1),input.length())];
                aux = rotor3[modulo(input.find(aux),input.length())];
                aux = input[modulo(input.find(aux)-(i+1),input.length())];
                aux = rotor2[modulo(input.find(aux),input.length())];
                aux = rotor1[modulo(input.find(aux),input.length())];
                aux= reflector[modulo(input.find(aux),input.length())];

                aux=input[modulo(rotor1.find(aux),input.length())];
                aux=input[modulo(rotor2.find(aux),input.length())];
                aux = input[modulo(input.find(aux)+(i+1),input.length())];
                aux=input[modulo(rotor3.find(aux),input.length())];
                aux = input[modulo(input.find(aux)-(i+1),input.length())];
                aux=input[input.find(aux)];
                textoC+=aux;
            }
            return textoC;
        }
};
#endif // ENIGMA_H
