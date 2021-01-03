#ifndef ENIGMA_H
#define ENIGMA_H


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

        string cifrado(string texto){
            string textoC;
            for(int i=0; i<texto.length(); i++){
                string aux;
                aux = rotor3[input.find(texto[i])];
                aux = rotor2[input.find(aux)];
                aux = rotor1[input.find(aux)];
                aux= reflector[input.find(aux)];

                aux=input[rotor1.find(aux)];
                aux=input[rotor2.find(aux)];
                aux=input[rotor3.find(aux)];

                aux=input[input.find(aux)];


                textoC+=aux;
            }
            return textoC;
        }

        string decifrado(string texto){
            string textoC;
            for(int i=0; i<texto.length(); i++){
                string aux;
                aux=input[rotor1.find(texto[i])];
                cout << aux << endl;
                aux=input[rotor2.find(aux)];
                aux=input[rotor3.find(aux)];
                aux= input[reflector.find(aux)];

                aux = rotor3[input.find(aux)];
                aux = rotor2[input.find(aux)];
                aux = rotor1[input.find(aux)];


                aux=input[input.find(aux)];


                textoC+=aux;
            }
            return textoC;
        }
};
#endif // ENIGMA_H
