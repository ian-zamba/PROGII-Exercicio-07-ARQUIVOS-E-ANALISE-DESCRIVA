#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <cmath>
#include <ctype.h>
#include <iomanip>
#include <fstream> //arquivo
using namespace std;

struct aluno{
    char nome[30];
    float nota;
};

int EscolhaOpcao();
void AddAluno(char* arquivo);
void MostrarNotas(char* arquivo);
void Media(char* arquivo);


int main(void){

    int opcao;
    char* arquivo = "boletim.dat";
    

    opcao = EscolhaOpcao();

    while(opcao != 4){
        
        switch (opcao){

        case 1:
            AddAluno(arquivo);    
            break;

        case 2:
            MostrarNotas(arquivo);
            break;
        
        case 3:
            Media(arquivo);
            break;
        
        default:
            cout << "Opcao invalida.\n\n";
            break;
        }
        opcao = EscolhaOpcao();
    }

    return 0;
}


int EscolhaOpcao (){

    int op;

    cout << "Opcoes: \n"
         << "1. Adicionar mais um aluno\n"
         << "2. Exibir todas as notas\n"
         << "3. Calcular a media\n"
         << "4. Sair\n";
    
    cin >> op;

    return op;
}

void AddAluno(char* arquivo){

    aluno a;
    fstream boletim(arquivo, ios :: app);

        cout << "Informe o nome do novo aluno: ";
        cin >> a.nome;
        cout << "Informe a nota do novo aluno: ";
        do{
            cin >> a.nota;
            if(a.nota > 10 || a.nota < 0){
                cout << "Nota invalida, informe novamente: ";
            }
        }while(a.nota > 10 || a.nota < 0);
        
        boletim.write((const char*) (&a) ,sizeof (aluno));
        cout << "\n";
        
    boletim.close();

}

void MostrarNotas(char* arquivo){

    aluno a;
    ifstream boletim(arquivo, ios :: in);

        if(boletim){
            cout <<  setiosflags(ios :: left)
                <<  setw(30) << "\nNome"
                <<  setw(8) << "Nota\n";

            boletim.read ((char*)(&a), sizeof(aluno));
            while (!boletim.eof()){
                cout << setiosflags (ios :: left)
                << setw(30) << a.nome
                << setw(8) << setprecision(1) 
                << setiosflags ( ios :: fixed | ios :: showpoint ) << a.nota 
                << "\n";        
                boletim.read((char*)(&a), sizeof(aluno));
            }
        }else{
            cout << "Arquivo nao encontrado :(\n";
        }
            cout << "\n";

    boletim.close();

}

void Media(char* arquivo){

    aluno a;
    float soma, media = 0;
    ifstream boletim(arquivo, ios :: in);

        if(boletim){
            
            boletim.read ((char*)(&a), sizeof(aluno));
            while (!boletim.eof()){
                soma += a.nota;
                media ++;      
                boletim.read((char*)(&a), sizeof(aluno));
            }

            media = soma / media;

            cout << "Media geral: " << setprecision(1) 
            << setiosflags ( ios :: fixed | ios :: showpoint ) 
            << media << "\n";

        }else{
            cout << "Arquivo nao encontrado :(\n";
        }
            cout << "\n";

    boletim.close();



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