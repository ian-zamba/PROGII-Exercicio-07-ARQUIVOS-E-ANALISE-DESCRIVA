#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <cmath>
#include <ctype.h>
#include <fstream> //nomearq
using namespace std;

int main(void) {
    
    char nomearq[200];
    fstream arq;
    int num;
    int vet[5];
    string s;
    
    cout << "Informe o nome do arquivo .txt: ";
    cin >> nomearq;
    strcat(nomearq, ".txt");

    arq.open(nomearq, ios::out | ios::trunc);

        for (int i = 1; i <= 5; i++){
            cout << "Informe o " << i << " Numero: ";
            cin >> num;
            arq << num << "\n";
        }
    
    arq.close();

    arq.open(nomearq, ios::in);

        for (int i = 0; i < 5; i++){
            getline(arq, s);
            vet[i] = stoi(s);
        }

    arq.close();

    for (int i = 0; i < 5; i++){
        cout << vet[i] << " ";
    }
    






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