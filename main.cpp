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

void menu(); // imprime na tela o menu de funcionalidades do programa
void limparTela(); // limpar a tela do terminal
void cadastroCidade();
void cadastroTrajeto();
void cadastroTransporte();
void cadastroPassageiro();

int main(){
    int opcao;
    limparTela();

    while (opcao != 7){ // rodar as opções infinitamente até que a opção de sair (7) seja escolhida
        menu();
        cout << endl << "Escolha uma opcao: ";
        cin >> opcao;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer residual

        // Switch para realizar a fuincionalidade escolhida pelo usuário
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
    getline(cin, nome); // armazena o nome da cidade cadastrada

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

        // realiza o cadastro do nome da cidade no arquivo CSV
        arqCidades << cidade.getNome() << "\n";

        limparTela();
        cout << "Cidade '"<< nome << "' adicionada com sucesso." << endl;

        //fecha o acesso ao arquivo
        arqCidades.close();
    }
}

void cadastroTrajeto(){
    limparTela();

    string origem, destino;
    char tipoTrajeto;
    int distancia;

    cout << "Digite o nome da cidade de origem do trajeto: ";
    getline(cin, origem); // captura a cidade de origem do trajeto
    cout << "Digite o nome da cidade de destino do trajeto: ";
    getline(cin, destino); // captura a cidade de destino do trajeto

    ifstream arqCidades("cidades.csv"); // abertura para leitura do arquivo de cidades
    if (!arqCidades.is_open()) { // tratamento de erro para verificar se o arquivo conseguiu ser aberto
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

        if(verificaOrigem == true && verificaDestino == true){ // se ambas as cidades foram encontradas, encerra-se o loop while
            break;
        }
    }

    if(verificaOrigem == false){ // informa se foi possivel encontrar a cidade de origem
        limparTela();
        cout << "A cidade de origem '" << origem << "' nao foi cadastrada. Escolha outra cidade ou cadastre-a." << endl;

        return;
    }

    if(verificaDestino == false){ // informa se foi possivel encontrar a cidade de destino
        limparTela();
        cout << "A cidade de destino '" << destino << "' nao foi cadastrada. Escolha outra cidade ou cadastre-a." << endl;

        return;
    }

    // armazena o tipo do trajeto
    cout << endl << "Digite o tipo do trajeto ('A' para aquatico e 'T' para terrestre): ";
    cin >> tipoTrajeto;
    tipoTrajeto = toupper(tipoTrajeto); // passa o char para maiúsculo
    
    // tratamento de erro para ver se o tipo do trajeto foi informado corretamente
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
    
    // armazena a distancia
    do
    {   
        if(distancia<= 0){ // tratamento de erro para ver se a distancia foi informada corretamente
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

    // tratamento de erro para verificar se foi possível cadastrar o trajeto
    if(trajeto.getOrigem()->getNome().empty() || trajeto.getDestino()->getNome().empty()) 
    { 
        limparTela();
        cout << "Erro ao Cadastrar trajeto. Tente novamente"<< endl;
        return;
    }
    else 
    {
        // abre o arquivo para escrita - 'ios::app' permite que linhas sejam adicionadas ao invés de sobrescrever o conteúdo do arquivo
        ofstream arqTrajeto("trajetos.csv", ios::app); 

        if (!arqTrajeto.is_open()) { // verificar se o arquivo foi aberto corretamente
            cerr << "Erro ao abrir o arquivo.\n";
            return;
        }

        // Adiciona trajeto para linha do arquivo "trajeto.csv"
        arqTrajeto << trajeto.getOrigem()->getNome() << "," << trajeto.getDestino()->getNome() << "," << trajeto.getTipoTrajeto() << "," << trajeto.getDistancia() << "\n";

        limparTela();
        cout << "Trajeto de '"<< trajeto.getOrigem()->getNome() << "' para '" << trajeto.getDestino()->getNome() << "' adicionado com sucesso." << endl;

        //fecha o acesso ao arquivo
        arqTrajeto.close();
        arqCidades.close();
    }
}
void cadastroTransporte(){
    string nome, localAtual;
    char tipoTransporte;
    int capacidade, velocidade, distancia_descanso, tempo_descanso, tempo_descanso_atual;
    limparTela();

    cout << "Digite o nome do transporte: ";
    getline(cin, nome); // armazena o nome do transporte

    cout << "Digite o tipo do transporte ('A' para aquatico e 'T' para terrestre): ";
    cin >> tipoTransporte; // armazena o tipo do transporte
    tipoTransporte = toupper(tipoTransporte); // passa o char para maiúsculo
    
    // tratamento de erro para ver se o tipo do transporte foi informado corretamente
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
    cin >> capacidade; // armazena a capacidade do transporte

    //tratamento de erro caso a capacidade seja informada de forma incorreta
    while (capacidade <= 0){   
        cout << endl << "Capacidade invalida" << endl;
        cout << "Digite a capacidade do transporte: ";
        cin >> capacidade;
    }

    cout << "Digite a velocidade do transporte (em km/h): ";
    cin >> velocidade; // armazena a velocidade

    //tratamento de erro caso a velocidade seja informada de forma incorreta
    while (velocidade <= 0){   
        cout << endl << "Velocidade invalida" << endl;
        cout << "Digite a velocidade do transporte (em km/h): ";
        cin >> velocidade;
    } 

    cout << "Digite a distancia de descanso do transporte (em km): ";
    cin >> distancia_descanso; // armazena a distancia de descanso

    //tratamento de erro caso a distancia de descanso seja informada de forma incorreta
    while (distancia_descanso <= 0){   
        cout << endl << "Distancia invalida" << endl;
        cout << "Digite a distancia de descanso do transporte (em km): ";
        cin >> distancia_descanso;
    }

    cout << "Digite o tempo de descanso do transporte (em h): ";
    cin >> tempo_descanso; // armazena o tempo de descanso

    //tratamento de erro caso o tempo de descanso seja informada de forma incorreta
    while (tempo_descanso <= 0){   
        cout << endl << "Tempo de descanso invalido" << endl;
        cout << "Digite o tempo de descanso do transporte (em h): ";
        cin >> tempo_descanso;
    }

    cout << "Digite o tempo de descanso atual do transporte (em h): ";
    cin >> tempo_descanso_atual; // armazena o tempo de descanso atual

    //tratamento de erro caso o tempo de descanso atual seja informada de forma incorreta
    while (tempo_descanso_atual <= 0){   
        cout << endl << "Tempo de descanso invalido" << endl;
        cout << "Digite o tempo de descanso atual do transporte (em h): ";
        cin >> tempo_descanso_atual;
    }
    
    cout << "Digite o local atual do transporte: ";
    getline(cin, localAtual); //armazena o local atual

    // abertura para leitura do arquivo 'cidades' para verificar se a cidade 'local atual' foi cadastrada
    ifstream arqCidades("cidades.csv");
    if (!arqCidades.is_open()) {
        limparTela();
        cerr << "Erro ao abrir o arquivo 'cidades.csv'" << endl;
        return;
    }

    string linha;

    while (getline(arqCidades, linha)) { // percorrer linha por linha no arquivo
        
        if (linha == localAtual) { // Verificar se a linha contém o local atual
            break;
        }else{
            limparTela();
            cout << "Local atual '" << localAtual << "' do transporte '" << nome << "' nao esta cadastrado. Cadastre-o ou escolha outra cidade." << endl;
            return;
        }
    }

    Cidade localAtual_obj(localAtual); // Cria a instância da cidade de local atual
    Cidade* local_atual = &localAtual_obj; // Ponteiro para a cidade de local atual
    
    // Cria o Transporte
    Transporte transporte(nome, tipoTransporte, capacidade, velocidade, distancia_descanso, tempo_descanso, tempo_descanso_atual, local_atual);
    
    // Tratamento de erro para erificar se foi possível criar o transporte
    if(transporte.getNome().empty()){
        cout << "Erro ao Cadastrar transporte. Tente novamente"<< endl;
    }else{

        // abre o arquivo para escrita - 'ios::app' permite que linhas sejam adicionadas ao invés de sobrescrever o conteúdo do arquivo
        ofstream arqTransporte("transportes.csv", ios::app); 

        if (!arqTransporte.is_open()) { // verificar se o arquivo foi aberto corretamente
            cerr << "Erro ao abrir o arquivo.\n";
            return;
        }

        // passagem dos parametros de Transporte para o arquivo CSV
        arqTransporte << transporte.getNome() << "," << transporte.getTipoTransporte() << "," << transporte.getCapacidadePassageiros() << "," << transporte.getVelocidade() << "," << transporte.getDistanciaDescanso() << "," << transporte.getTempoDescanso() << "," << transporte.getTempoDescansoAtual() << "," << transporte.getLocalAtual() << "\n";

        limparTela();
        cout << "Transporte '" << transporte.getNome() << "' adicionado com sucesso. " << endl;

        //fecha o acesso ao arquivo
        arqTransporte.close();
        arqCidades.close();
    }
}

void cadastroPassageiro(){
    limparTela();

    string nome, localAtual;
    cout << "Digite o nome do passageiro: ";
    getline(cin, nome); // Armazena o nome do passageiro
    
    cout << "Digite o local atual do passageiro: ";
    getline(cin, localAtual);
    
    // abertura do arquivo 'cidades' para verificar se o 'local atual' informado ja foi cadastrado
    ifstream arqCidades("cidades.csv");

    // tratamento de erro para ver se foi possivel abrir o arquivo
    if (!arqCidades.is_open()) {
        cerr << "Erro ao abrir o arquivo 'cidades.csv'" << endl;
        return;
    }

    string linha;    

    while (getline(arqCidades, linha)) { // percorrer linha por linha no arquivo
        
        if (linha == localAtual) { // Verificar se a linha contém o local atual
            break;
        }else{
            limparTela();
            cout << "Local atual '" << localAtual << "' do passageiro '" << nome << "' nao esta cadastrado. Cadastre-o ou escolha outra cidade." << endl;
            return;
        }
    }

    Cidade localAtual_obj(localAtual); // Cria a instância da cidade de local atual
    Cidade* local_atual = &localAtual_obj; // Ponteiro para a cidade de local atual

    // cria Passageiro
    Passageiro passageiro(nome, local_atual);

    // verifica se foi possivel cadastrar o passageiro
    if(passageiro.getNome().empty() || passageiro.getLocalAtual() == nullptr)
    {
        limparTela();
        cout << "Erro ao adicionar passageiro. Tente novamente"<< endl;
    }else
    {
        // abertura do arquivo 'passageiros' para escrita - 'ios::app' permite que linhas sejam adicionadas ao invés de sobrescrever o conteúdo do arquivo
        ofstream arqPassageiros("passageiros.csv", ios::app);

        // passagem dos parâmetros de Passageiro para o arquivo CSV
        arqPassageiros << passageiro.getNome() << "," << passageiro.getLocalAtual() << "\n";

        limparTela();
        cout << "Passageiro '"<< passageiro.getNome() << "' localizado em '" << passageiro.getLocalAtual()<< "' cadastrado com sucesso." << endl;

        //fecha o acesso ao arquivo
        arqPassageiros.close();
        arqCidades.close();
    }
}