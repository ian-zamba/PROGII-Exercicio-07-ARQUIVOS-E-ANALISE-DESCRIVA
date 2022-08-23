#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <cmath>
#include <ctype.h>
#include <fstream>
using namespace std;


int main(void) {
    
    fstream texto;
    char escrevertexto[1000];
    char s;

    texto.open("texto.txt", ios::out | ios::trunc);
        
        cout << "Escreva o Texto:\n";
        fgets(escrevertexto, 1000, stdin);
        texto << escrevertexto;

    texto.close();

    texto.open("texto.txt", ios::in);

        int i = 0;

        while(texto.get(s)) {

            s = toupper(s);
            escrevertexto[i] = s;
            i++;
            
        }
    texto.close();

    texto.open("texto.txt", ios::out | ios::trunc);

        texto << escrevertexto;

    texto.close();

    cout << "Texto convertido para maiusculo e salvo em texto.txt";

    return 0;
}


/*
                 .eeeeeeeee
                .$$$$$$$$P"
               .$$$$$$$$P
              z$$$$$$$$P
             z$$$$$$$$"
            z$$$$$$$$"
           d$$$$$$$$"
          d$$$$$$$$"
        .d$$$$$$$P
       .$$$$$$$$P
      .$$$$$$$$$.........
     .$$$$$$$$$$$$$$$$$$"
    z$$$$$$$$$$$$$$$$$P"
   -**********$$$$$$$P
             d$$$$$$"
           .d$$$$$$"
          .$$$$$$P"
         z$$$$$$P
        d$$$$$$"
      .d$$$$$$"
     .$$$$$$$"
    z$$$$$$$beeeeee
   d$$$$$$$$$$$$$*
  ^""""""""$$$$$"
          d$$$*
         d$$$"
        d$$*
       d$P"
     .$$"
    .$P"
   .$"
  .P"
 ."
/"

ZAMBA
*/