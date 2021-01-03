#include <iostream>
#include "enigma.h"
#include <string>

using namespace std;

int main()
{
    enigma e1;
    cout << e1.cifrado("JAIME") << endl;
    cout << e1.decifrado("JULU");
    return 0;
}
