#include <iostream>
#include <cstdlib>
#include <string>
#include "classes.cpp"
#include <fstream>
#include <limits>
#include <sstream>
#include <vector>
#include <cctype>

using namespace std;

void menu();
void limparTela();
void cadastroCidade();
void cadastroTrajeto();
void cadastroTransporte();
void cadastroPassageiro();

int main(){
    int opcao;
    limparTela();

    while (opcao != 7){
        menu();
        cout << endl << "Escolha uma opcao: ";
        cin >> opcao;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer residual

        switch (opcao)
        {
        case 1:
            cadastroCidade();
            break;
        case 2:
            cadastroTrajeto();
            break;
        case 3:
            cadastroTransporte();
            break;
        case 4:
            cadastroPassageiro();
            break;
        case 5:
            /* code */
            break;
        case 6:
            /* code */
            break;
        case 7:
            cout << endl << "Encerrando o programa." << endl;
            break;
        default:
            limparTela();
            cout << endl << "Opcao invalida! escolha uma opcao disponivel." << endl;
            break;
        }
    }

    return 0;
}

void menu(){
    cout << endl << "------ Contolador de Viagens ------" << endl;
    cout << endl << "1- Cadastro de Cidade" << endl;
    cout << "2- Cadastro de Trajeto" << endl;
    cout << "3- Cadastro de Transporte" << endl;
    cout << "4- Cadastro de Passageiro" << endl;
    cout << "5- Gestao de viagem" << endl;
    cout << "6- Consultas e relatorios" << endl;
    cout << "7- Sair" << endl;
}

void limparTela() {
    system("cls"); // Limpa o terminal no Windows
}

void cadastroCidade(){
    limparTela();

    string nome;
    cout << "Digite o nome da cidade que deseja cadastrar: ";
    getline(cin, nome);

    Cidade cidade(nome); // Atribui o nome da cidade fornecida pelo usuário à variável 'nome' da classe 'Cidade'

    if(cidade.getNome().empty()) // tratamento de erro para verificar se foi possível cadastrar a cidade
    { 
        limparTela();
        cout << "Erro ao adicionar cidade. Tente novamente"<< endl;
    }
    else 
    {
        ofstream arqCidades("cidades.csv", ios::app); // abre o arquivo para escrita - 'ios::app' permite que linhas sejam adicionadas ao invés de sobrescrever o conteúdo do arquivo

        if (!arqCidades.is_open()) { // verificar se o arquivo foi aberto corretamente
            cerr << "Erro ao abrir o arquivo.\n";
            return;
        }

        arqCidades << cidade.getNome() << "\n";

        limparTela();
        cout << "Cidade '"<< nome << "' adicionada com sucesso." << endl;

        arqCidades.close();
    }
}

void cadastroTrajeto(){
    limparTela();

    string origem, destino;
    char tipoTrajeto;
    int distancia;

    cout << "Digite o nome da cidade de origem do trajeto: ";
    getline(cin, origem);
    cout << "Digite o nome da cidade de destino do trajeto: ";
    getline(cin, destino);

    ifstream arqCidades("cidades.csv");
    if (!arqCidades.is_open()) {
        cerr << "Erro ao abrir o arquivo 'cidades.csv'" << endl;
        return;
    }

    string linha;
    bool verificaOrigem = false;
    bool verificaDestino = false;

    while (getline(arqCidades, linha)) { // percorrer linha por linha no arquivo
        
        if (linha == origem) { // Verificar se a linha contém a cidade de origem
            verificaOrigem = true;
        }

        if (linha == destino) { // Verificar se a linha contém a cidade de destino
            verificaDestino = true;
        }

        if(verificaOrigem == true && verificaDestino == true){
            break;
        }
    }

    if(verificaOrigem == false){
        limparTela();
        cout << "A cidade de origem '" << origem << "' nao foi cadastrada. Escolha outra cidade ou cadastre-a." << endl;

        return;
    }

    if(verificaDestino == false){
        limparTela();
        cout << "A cidade de destino '" << destino << "' nao foi cadastrada. Escolha outra cidade ou cadastre-a." << endl;

        return;
    }

    cout << endl << "Digite o tipo do trajeto ('A' para aquatico e 'T' para terrestre): ";
    cin >> tipoTrajeto;
    tipoTrajeto = toupper(tipoTrajeto);
    
    while(true){
        if(tipoTrajeto == 'A' || tipoTrajeto == 'T'){
            break;
        }else{
            cout << endl << "Tipo invalido" << endl;
            cout << "Digite o tipo do trajeto ('A' para aquatico e 'T' para terrestre): ";
            cin >> tipoTrajeto;
            tipoTrajeto = toupper(tipoTrajeto);
        }
    }
    
    do
    {   
        if(distancia<= 0){
            cout << endl << "Distancia invalida" << endl;
        }
        cout << "Digite a distancia do trajeto (em km): ";
        cin >> distancia;
    } while (distancia <= 0);

    Cidade origemA_obj(origem); // Cria a instância da cidade de origem
    Cidade destinoA_obj(destino); // Cria a instância da cidade de destino
    Cidade* origemA = &origemA_obj; // Ponteiro para a cidade de origem
    Cidade* destinoA = &destinoA_obj; // Ponteiro para a cidade de destino
    Trajeto trajeto(origemA, destinoA, tipoTrajeto, distancia); // Criação do trajeto

    if(trajeto.getOrigem()->getNome().empty() || trajeto.getDestino()->getNome().empty()) // tratamento de erro para verificar se foi possível cadastrar o trajeto
    { 
        limparTela();
        cout << "Erro ao Cadastrar trajeto. Tente novamente"<< endl;
        return;
    }
    else 
    {
        ofstream arqTrajeto("trajetos.csv", ios::app); // abre o arquivo para escrita - 'ios::app' permite que linhas sejam adicionadas ao invés de sobrescrever o conteúdo do arquivo

        if (!arqTrajeto.is_open()) { // verificar se o arquivo foi aberto corretamente
            cerr << "Erro ao abrir o arquivo.\n";
            return;
        }

        // Adiciona trajeto para linha do arquivo "trajeto.csv"
        arqTrajeto << trajeto.getOrigem()->getNome() << "," << trajeto.getDestino()->getNome() << "," << trajeto.getTipoTrajeto() << "," << trajeto.getDistancia() << "\n";

        limparTela();
        cout << "Trajeto de '"<< trajeto.getOrigem()->getNome() << "' para '" << trajeto.getDestino()->getNome() << "' adicionado com sucesso." << endl;

        arqTrajeto.close();
    }
}
void cadastroTransporte(){
    string nome, localAtual;
    char tipoTransporte;
    int capacidade, velocidade, distancia_descanso, tempo_descanso;
    limparTela();

    cout << "Digite o nome do transporte: ";
    getline(cin, nome);

    cout << "Digite o tipo do transporte ('A' para aquatico e 'T' para terrestre): ";
    cin >> tipoTransporte;
    tipoTransporte = toupper(tipoTransporte);
    
    while(true){
        if(tipoTransporte == 'A' || tipoTransporte == 'T'){
            break;
        }else{
            cout << endl << "Tipo invalido" << endl;
            cout << "Digite o tipo do transporte ('A' para aquatico e 'T' para terrestre): ";
            cin >> tipoTransporte;
            tipoTransporte = toupper(tipoTransporte);
        }
    }

    cout << "Digite a capacidade do transporte: ";
    cin >> capacidade;

    while (capacidade <= 0){   
        cout << endl << "Capacidade invalida" << endl;
        cout << "Digite a capacidade do transporte: ";
        cin >> capacidade;
    }

    cout << "Digite a velocidade do transporte (em km/h): ";
    cin >> velocidade;

    while (velocidade <= 0){   
        cout << endl << "Velocidade invalida" << endl;
        cout << "Digite a velocidade do transporte (em km/h): ";
        cin >> velocidade;
    } 

    cout << "Digite a distancia de descanso do transporte (em km): ";
    cin >> distancia_descanso;

    while (distancia_descanso <= 0){   
        cout << endl << "Distancia invalida" << endl;
        cout << "Digite a distancia de descanso do transporte (em km): ";
        cin >> distancia_descanso;
    }

    cout << "Digite o tempo de descanso do transporte (em h): ";
    cin >> tempo_descanso;

    while (tempo_descanso <= 0){   
        cout << endl << "Tempo invalido" << endl;
        cout << "Digite o tempo de descanso do transporte (em h): ";
        cin >> tempo_descanso;
    }

    /*
    cout << "Digite o local atual do transporte: ";
    getline(cin, localAtual);

    ifstream arqCidades("cidades.csv");
    if (!arqCidades.is_open()) {
        limparTela();
        cerr << "Erro ao abrir o arquivo 'cidades.csv'" << endl;
        return;
    }

    string linha;
    bool verificaLocalAtual = false;

    while(getline(arqCidades, linha)){
        if(localAtual == linha){
            verificaLocalAtual = true;
            break;
        }
    }

    if(verificaLocalAtual == false){
        limparTela();
        cout << "Cidade '" << localAtual << "' nao foi cadastrada" << endl;
        return;
    }
    */

    Transporte transporte(nome, tipoTransporte, capacidade, velocidade, distancia_descanso, tempo_descanso);
    if(transporte.getNome().empty()){
        cout << "Erro ao Cadastrar transporte. Tente novamente"<< endl;
    }else{
        ofstream arqTransporte("transportes.csv", ios::app); // abre o arquivo para escrita - 'ios::app' permite que linhas sejam adicionadas ao invés de sobrescrever o conteúdo do arquivo

        if (!arqTransporte.is_open()) { // verificar se o arquivo foi aberto corretamente
            cerr << "Erro ao abrir o arquivo.\n";
            return;
        }

        arqTransporte << transporte.getNome() << "," << transporte.getTipoTransporte() << "," << transporte.getCapacidadePassageiros() << "," << transporte.getVelocidade() << "," << transporte.getDistanciaDescanso() << "," << transporte.getTempoDescanso() << "," << transporte.getLocalAtual() << "\n";

        limparTela();
        cout << "transporte '" << transporte.getNome() << "' adicionado com sucesso. " << endl;
        arqTransporte.close();
    }
}

void cadastroPassageiro(){
    limparTela();

    string nome;
    cout << "Digite o nome do passageiro: ";
    getline(cin, nome);

    Passageiro passageiro(nome);

    if(passageiro.getNome().empty())
    {
        limparTela();
        cout << "Erro ao adicionar passageiro. Tente novamente"<< endl;
    }else
    {
        ofstream arqPassageiros("passageiros.csv", ios::app);

        arqPassageiros << passageiro.getNome() << "," << passageiro.getLocalAtual() << "\n";

        limparTela();
        cout << "Passageiro '"<< passageiro.getNome() << "' cadastrado com sucesso." << endl;

        arqPassageiros.close();
    }
}
