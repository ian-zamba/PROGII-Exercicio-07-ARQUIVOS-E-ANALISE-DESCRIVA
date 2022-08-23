#include <locale.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
using namespace std;
#include "cliente.h" 
enum Escolhas{CRIAR = 1, TELA, ARQUIVOTEXTO, ATUALIZAR, NOVO, APAGAR, FIM};
// ------------------------------------------------------------------------

Escolhas enterChoice(){
    /*essa função serve para o usuario escolher oque ele vai fazer no programa,
    ela escreve na tela as opções que ele pode escolher e pede um numero que será
    transformado em um enum declarado acima e retornara esse enum;
    */

    int menuChoice;
    cout << "Menu:" << endl 
         << "1 - Cria registros vazios no arquivo \n" 
         << "2 - Lista os dados na tela \n" 
         << "3 - Armazena os dados no arquivo texto print.txt \n" 
         << "4 - Atualiza uma conta que ja contenha informacoes \n" 
         << "5 - Insere informacoes em uma nova conta \n" 
         << "6 - Apaga informacoes de uma conta \n" 
         << "7 - Fim do programa \n" 
         << "Opcao: ";
    cin >> menuChoice;
    return (Escolhas)menuChoice;
    
}
// ------------------------------------------------------------------------
void create(fstream &f){
    /*essa função serve para iniciar o arquivo com 100 usuarios "vazios", 
    onde seria o numero do usuario, ele inicia com 0, o nome com um espaço vazio
    e o saldo com 0.0
    */

    cliente clienteVazio = {0, "", 0.0};
    f.seekp(0);
    for (int i = 0; i < 100; i++) 
    f.write((const char *)(&clienteVazio), sizeof(cliente));

}
// ------------------------------------------------------------------------
void outputLine(ostream &output, const cliente &c){
    /*essa função serve para imprimir os dados do cliente(que é uma struct)
    em algum lugar. Esse lugar sera definido atravez da variavel output, onde
    cada chamada dessa função sera diferente.
    ex: se a chamada da função vier com o parametro "cout", ele imprimira na tela
    as informações, ou se vier como parametro "outPrintFile" ele imprimira no 
    arquivo outPrintFile.
    */

    output << setiosflags(ios ::left)  << setw(10) << c.numero  
           << setw(30) << c.nome  << setw(10) 
           << setprecision(2) << resetiosflags(ios ::left) 
           << setiosflags(ios ::fixed | ios ::showpoint) << c.saldo << "\n";

}
// ------------------------------------------------------------------------
void screen(fstream &f){
    /*essa função serve para imprimir os dados do arquivo na tela, ele primeiro
    imprime conta, nome e saldo como se fosse uma tabela, definindo quantos 
    espaços cada informação ocupara. Depois disso ele chama a função outputLine
    (explicado a cima) com o parametro "cout", onde ele vai imprimir na tela de
    um jeito organizado como a tabela conta, nome, saldo. Ele imprime até o 
    arquivo chegar ao final e se o numero da conta não for 0(cliente vazio).
    */

    cliente c;
    cout << setiosflags(ios ::left) 
         << setw(10) << "Conta" 
         << setw(30) << "Nome" 
         << resetiosflags(ios ::left) << setw(10) << " Saldo " << endl;

    f.seekp(0);
    f.read((char *)(&c), sizeof(cliente));

    while (!f.eof())
    {
        if (c.numero != 0) 
        outputLine(cout, c);
        f.read((char *)(&c), sizeof(cliente));        
    }

}
// ------------------------------------------------------------------------
void textFile(fstream &f){
    /*essa função serve para imprimir os dados do arquivo em outro 
    arquivo(outPrintFile), ele primeiro imprime conta, nome e saldo como se fosse 
    uma tabela, definindo quantos espaços cada informação ocupara. Depois disso 
    ele chama a função outputLine (explicado a cima) com o parametro 
    "outPrintFile", onde ele vai imprimir no arquivo de um jeito organizado 
    como a tabela conta, nome, saldo. Ele imprime até o arquivo chegar ao 
    final e se o numero da conta não for 0(cliente vazio).
    */

    cliente c;
    ofstream outPrintFile("print.txt", ios ::out);
    if (!outPrintFile){
        cerr << "Arquivo print.txt nao pode ser aberto." << endl;
        exit(1);
    }
    outPrintFile << setiosflags(ios ::left) 
                 << setw(10) << "Conta" 
                 << setw(30) << "Nome" 
                 << resetiosflags(ios ::left) << setw(10) << "Saldo" << endl;
    f.seekp(0);
    f.read((char *)(&c), sizeof(cliente));

    while (!f.eof()){
        if (c.numero != 0) 
        outputLine(outPrintFile, c);
        f.read((char *)(&c), sizeof(cliente));        
    }
    outPrintFile.close();

}
// ------------------------------------------------------------------------
int getAccount(string msg){
    /*essa função serve para o usuario escolher um numero de 1 até 100
    onde ele checa se o numero escolhido esta entre esses dois numeros,se 
    não for ele pede para escrever de novo até estar e retorna o valor escolhido.
    */

    int conta;
    do{
        cout << msg << "(1 - 100): ";
        cin >> conta;
    }while (conta < 1 || conta > 100);
    return conta;

}
// ------------------------------------------------------------------------
void updateRecord(fstream &f){
    /*essa função serve para atulizar o saldo de um cliente. ela chama a função 
    getAccount(explicada acima) para saber qual cliente deve ser atualizado, ele 
    checa se o cliente não é vazio (conta não é 0), e pede para informar o valor
    do deposito ou retirada e soma ou subtrai do saldo do cliente escolhido e
    atualiza esse valor no arquivo.
    */

    int conta;
    cliente c;
    float transacao;

    conta = getAccount("Conta a ser atualizada");
    f.seekp((conta - 1) * sizeof(cliente)); // posicionar na conta desejada
    f.read((char *)(&c), sizeof(cliente));  // ler dados da conta
    if (c.numero != 0){// conta contem informacao ?
        outputLine(cout, c);
        cout << "\nEntre deposito (+) ou retirada (-): ";
        cin >> transacao;
        c.saldo += transacao;
        outputLine(cout, c);
        f.seekp((conta - 1) * sizeof(cliente));       // posicionar na conta desejada
        f.write((const char *)(&c), sizeof(cliente)); // atualizar
    }else 
    cerr << "Conta #" << conta << " nao possui informacao." << endl;

}
// ------------------------------------------------------------------------
void newRecord(fstream &f){
    /*essa função serve para cadastrar um novo cliente. ela chama a função 
    getAccount(explicada acima) para saber qual cliente deve ser cadastrado, 
    checa se a conta é vazia (conta = 0) e cadastra o novo cliente no arquivo, 
    se a a conta não for vazia, ele aviza que ja tem alguma informação naquela 
    conta.
    */

    int conta;
    cliente c;
    
    conta = getAccount("Numero da nova conta");
    f.seekp((conta - 1) * sizeof(cliente)); // posicionar na conta desejada
    f.read((char*)(&c), sizeof(cliente));  // ler dados da conta
    if (c.numero == 0){
        cout << "Entre nome, saldo \n? ";
        cin >> c.nome >> c.saldo;
        c.numero = conta;
        f.seekp((conta - 1) * sizeof(cliente));       // posicionar na conta desejada
        f.write((const char *)(&c), sizeof(cliente)); // atualizar
    }else 
    cerr << "Conta #" << conta << " ja possui informacao." << endl;

}
// ------------------------------------------------------------------------
void deleteRecord(fstream &f){
    /*essa função serve paraapagar os dados de um cliente. ela chama a função 
    getAccount(explicada acima) para saber qual cliente deve ser pagado, checa se
    o cliente solicitado não é vazio(conta = 0), se não for vazio, ele subescreve 
    os dados desse cliente com os dados de um cliente vazio, se for vazio, ele
    informa que o cliente ja foi apagado.
    */

    int conta;
    cliente c, clienteVazio = {0, "", 0.0};
    
    conta = getAccount("Conta a ser apagada");
    f.seekp((conta - 1) * sizeof(cliente));
    f.read((char *)(&c), sizeof(cliente));
    if (c.numero != 0){
        f.seekp((conta - 1) * sizeof(cliente));
        f.write((const char *)(&clienteVazio), sizeof(cliente));
        cout << "Conta #" << conta << "apagada." << endl;
    }else 
    cerr << "Conta #" << conta << "ja esta apagada." << endl;

}
// ------------------------------------------------------------------------
int main(){
    /*função principal(main), ela serve para abrir o arquivo para ser cadastrado
    os clientes e para checar qual foi a escolha do usuario para poder chamar as
    respectivas funções.
    */

    setlocale(LC_ALL, "portuguese");
    
    Escolhas opcao;
    fstream inOutCredito("credito.dat", ios ::in | ios ::out);
    
    if (!inOutCredito){
        cerr << "Arquivo credito.dat nao pode ser aberto." << endl;
        exit(1);
    }

    while ((opcao = enterChoice()) != FIM){
        switch (opcao){
            case CRIAR : 
                create(inOutCredito);
                break;
            case TELA : 
                screen(inOutCredito);
                break;
            case ARQUIVOTEXTO : 
                textFile(inOutCredito);
                break;
            case ATUALIZAR : 
                updateRecord(inOutCredito);
                break;
            case NOVO : 
                newRecord(inOutCredito);
                break;
            case APAGAR : 
                deleteRecord(inOutCredito);
                break;
            default : 
                cerr << "Opcao incorreta \n";
                break;
        }
        inOutCredito.clear();

    }

    return 0;
}