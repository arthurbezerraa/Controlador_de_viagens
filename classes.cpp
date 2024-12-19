#ifndef CLASSES_CPP
#define CLASSES_CPP

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Cidade{
    private: 
        string nome; // nome da cidade

    public: 

        // funcao construtora para passar os parametros
        Cidade(string nome){
            this->nome = nome;
        }

        // retorna o nome da cidade
        string getNome(){
            return this->nome;
        }
};

class Trajeto{
    private: 
        Cidade* origem; // ponteiro para a cidade de origem do trajeto
        Cidade* destino; // ponteiro para a cidade de destino do trajeto
        char tipo_trajeto; // A (aquático) ou T (terrestre)
        int distancia_trajeto; // em km

    public:

        // funcao construtora para passar os parametros
        Trajeto(Cidade* origem, Cidade* destino, char tipo_trajeto, int distancia_trajeto){
            this->origem = origem;
            this->destino = destino;
            this->tipo_trajeto = tipo_trajeto;
            this->distancia_trajeto = distancia_trajeto;
        }

        // retorna a cidade de origem que o ponteiro aponta
        Cidade* getOrigem(){
            return this->origem;
        }

        // retorna a cidade de destino que o ponteiro aponta
        Cidade* getDestino(){
            return this->destino;
        }

        // retorna o tipo do trajeto
        char getTipoTrajeto(){
            return this->tipo_trajeto;
        }

        // retorna a distância do trajeto
        int getDistancia(){
            return this->distancia_trajeto;
        }
};

class Transporte{
    private: 
        string nome; // nome do transporte
        char tipo_transporte; // A (aquático) ou T (terrestre)
        int capacidade_passageiros;
        int velocidade; // km/h
        int distancia_descanso; // km
        int tempo_descanso; // h
        int tempo_de_descanso_atual; // h
        Cidade* local_atual; // ponteiro que aponta para a cidade atual do transporte

    public: 

        // funcao construtora para passar os parametros
        Transporte(string nome, char tipo_transporte, int capacidade_passageiros, int velocidade, int distancia_descanso, int tempo_descanso, int tempo_de_descanso_atual, Cidade* local_atual){
            this->nome = nome;
            this->tipo_transporte = tipo_transporte;
            this->capacidade_passageiros = capacidade_passageiros;
            this->velocidade = velocidade;
            this->distancia_descanso = distancia_descanso;
            this->tempo_descanso = tempo_descanso;
            this->local_atual = local_atual;
        }

        // retorna o nome do transporte
        string getNome(){
            return this->nome;
        }

        // retorna o tipo do transporte
        char getTipoTransporte(){
            return tipo_transporte;
        }

        // retorna a capacidade do transporte
        int getCapacidadePassageiros(){
            return capacidade_passageiros;
        }
        
        // retorna a velocidade do transporte
        int getVelocidade(){
            return velocidade;
        }

        // retorna a distância de descanso do transporte
        int getDistanciaDescanso(){
            return distancia_descanso;
        }

        // retorna o tempo de descanso do transporte
        int getTempoDescanso(){
            return tempo_descanso;
        }

        // retorna o tempo de descanso atual do transporte
        int getTempoDescansoAtual(){
            return tempo_de_descanso_atual;
        } 

        // retorna a cidade onde o ponteiro aponta para indicar o local atual que o transporte está
        Cidade* getLocalAtual(){
            return local_atual;
        }

        // atualiza a cidade onde o ponteiro aponta para indicar o local atual que o transporte está
        void setLocalAtual(Cidade* local){
            this->local_atual = local;
        }

};

class Passageiro{
    private:
        string nome; // nome do passageiro
        Cidade* local_atual; // ponteiro que aponta para a cidade atual do passageiro

    public:

        // funcao construtora para passar os parametros
        Passageiro(string nome, Cidade* local_atual){
            this->nome = nome;
            this->local_atual = local_atual;
        }

        // retorna o nome do passageiro
        string getNome(){
            return nome;
        }

        // retorna a cidade onde o ponteiro aponta para indicar o local atual que o passageiro está
        Cidade* getLocalAtual(){
            return local_atual;
        }

        // atualiza a cidade onde o ponteiro aponta para indicar o local atual que o passageiro está
        void setLocalAtual(Cidade* local){
            this->local_atual = local;
        }
};

class Viagem {
    private: 
        Transporte* transporte; // Ponteiro para o transporte utilizado na viagem
        vector<Passageiro*> passageiros; // Vetor de ponteiros para os passageiros da viagem
        Cidade* origem; // Ponteiro para a cidade de origem da viagem
        Cidade* destino; // Ponteiro para a cidade de destino da viagem
        Viagem* proxima; // Ponteiro para a próxima viagem 
        int horasEmTransito; // Quantidade de horas que a viagem está em andamento
        bool emAndamento; // Indica se a viagem está em progresso ou foi concluída

    public:
        // Construtor da classe, inicializa os atributos principais da viagem
        Viagem(Transporte* transporte, vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino);

        // Método para iniciar a viagem, verifica condições iniciais e ajusta o estado
        void iniciarViagem() {
            if (transporte == nullptr || origem == nullptr || destino == nullptr) {
                // Verifica se as informações essenciais estão presentes
                cout << "Erro: Informações insuficientes para iniciar a viagem." << endl;
                return;
            }
            
            this->emAndamento = true; // Define que a viagem está em andamento
            this->horasEmTransito = 0; // Reseta as horas em trânsito
            this->transporte->setLocalAtual(this->origem); // Define o transporte na origem

            // Atualiza a localização inicial de todos os passageiros para a origem
            for (Passageiro* passageiro : this->passageiros) {
                passageiro->setLocalAtual(this->origem);
            }

            // Exibe mensagem indicando o início da viagem
            cout << "Viagem iniciada de " << this->origem->getNome() << " para " << this->destino->getNome() << endl;
        }

        // Método para avançar o tempo em horas e calcular o progresso da viagem
        void avancarHoras(int horas) {
            if (!this->emAndamento) {
                // Impede avanço de horas se a viagem não estiver em andamento
                cout << "Erro: A viagem não está em andamento." << endl;
                return;
            }

            // Calcula a distância restante para o destino
            int distanciaRestante = this->destino->getNome() != this->transporte->getLocalAtual()->getNome() ? (this->transporte->getDistanciaDescanso() - this->horasEmTransito) : 0;

            // Calcula a distância percorrida no tempo informado
            int distanciaPercorrida = this->transporte->getVelocidade() * horas;
            this->horasEmTransito += horas; // Incrementa as horas em trânsito

            if (distanciaPercorrida >= distanciaRestante) {
                // Caso a viagem alcance ou exceda o destino
                this->transporte->setLocalAtual(this->destino); // Atualiza a posição do transporte para o destino
                
                // Atualiza a localização de todos os passageiros para o destino
                for (Passageiro* passageiro : this->passageiros) {
                    passageiro->setLocalAtual(this->destino);
                }

                this->emAndamento = false; // Marca a viagem como concluída
                cout << "Viagem concluída! Chegamos ao destino: " << this->destino->getNome() << endl;

            } else {
                // Caso ainda reste distância para o destino
                cout << "Viagem em progresso. " << distanciaRestante - distanciaPercorrida << " km restantes." << endl;
            }
        }
        
        // Método para relatar o estado atual da viagem
        void relatarEstado() {
            cout << "Status da Viagem:" << endl;
            cout << "Origem: " << this->origem->getNome() << endl; // Exibe a origem da viagem
            cout << "Destino: " << this->destino->getNome() << endl; // Exibe o destino da viagem
            cout << "Local Atual do Transporte: " << this->transporte->getLocalAtual()->getNome() << endl; // Local atual do transporte
            cout << "Horas em trânsito: " << this->horasEmTransito << endl; // Horas de viagem já realizadas
            cout << "Status: " << (this->emAndamento ? "Em andamento" : "Concluída") << endl; // Status da viagem
        }
        
        // Método para verificar se a viagem está em andamento
        bool isEmAndamento() {
            return this->emAndamento; // Retorna o status da viagem
        }
};


#endif