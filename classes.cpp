#ifndef CLASSES_CPP
#define CLASSES_CPP

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Cidade{
    private: 
        string nome;

    public: 
        Cidade(string nome){
            this->nome = nome;
        }

        string getNome(){
            return this->nome;
        }
};

class Trajeto{
    private: 
        Cidade* origem;
        Cidade* destino;
        char tipo_trajeto; // A (aquático) ou T (terrestre)
        int distancia_trajeto; // em km

    public:
        Trajeto(Cidade* origem, Cidade* destino, char tipo_trajeto, int distancia_trajeto){
            this->origem = origem;
            this->destino = destino;
            this->tipo_trajeto = tipo_trajeto;
            this->distancia_trajeto = distancia_trajeto;
        }

        Cidade* getOrigem(){
            return this->origem;
        }

        Cidade* getDestino(){
            return this->destino;
        }

        char getTipoTrajeto(){
            return this->tipo_trajeto;
        }

        int getDistancia(){
            return this->distancia_trajeto;
        }
};

class Transporte{
    private: 
        string nome;
        char tipo_transporte; // A (aquático) ou T (terrestre)
        int capacidade_passageiros;
        int velocidade; // km/h
        int distancia_descanso; // km
        int tempo_descanso; // h
        Cidade* local_atual;

    public: 
        Transporte(string nome, char tipo_transporte, int capacidade_passageiros, int velocidade, int distancia_descanso, int tempo_descanso, Cidade* local_atual = nullptr){
            this->nome = nome;
            this->tipo_transporte = tipo_transporte;
            this->capacidade_passageiros = capacidade_passageiros;
            this->velocidade = velocidade;
            this->distancia_descanso = distancia_descanso;
            this->tempo_descanso = tempo_descanso;
            this->local_atual = local_atual;
        }

        string getNome(){
            return this->nome;
        }

        char getTipoTransporte(){
            return tipo_transporte;
        }

        int getCapacidadePassageiros(){
            return capacidade_passageiros;
        }
        
        int getVelocidade(){
            return velocidade;
        }

        int getDistanciaDescanso(){
            return distancia_descanso;
        }

        int getTempoDescanso(){
            return tempo_descanso;
        }

        /*int getTempoDescansoAtual(){

        } */

        Cidade* getLocalAtual(){
            return local_atual;
        }

        void setLocalAtual(Cidade* local){
            this->local_atual = local;
        }

};

class Passageiro{
    private:
        string nome;
        Cidade* local_atual;

    public:
        Passageiro(string nome, Cidade* local_atual = nullptr){
            this->nome = nome;
            this->local_atual = local_atual;
        }

        string getNome(){
            return nome;
        }

        Cidade* getLocalAtual(){
            return local_atual;
        }

        void setLocalAtual(Cidade* local){
            this->local_atual = local;
        }
};

class Viagem{
    private: 
        Transporte* transporte;
        vector <Passageiro*> passageiros;
        Cidade* origem;
        Cidade* destino;
        Viagem* proxima;
        int horasEmTransito;
        bool emAndamento;

    public:
        Viagem(Transporte* transporte, vector <Passageiro*> passageiros, Cidade* origem, Cidade* destino);

        void iniciarViagem(){
            if (transporte == nullptr || origem == nullptr || destino == nullptr) {
                cout << "Erro: Informações insuficientes para iniciar a viagem." << endl;
                return;
            }
            
            this->emAndamento = true;
            this->horasEmTransito = 0;
            this->transporte->setLocalAtual(this->origem);

            for (Passageiro* passageiro : this->passageiros) {
                passageiro->setLocalAtual(this->origem);
            }

            cout << "Viagem iniciada de " << this->origem->getNome() << " para " << this->destino->getNome() << endl;
        }

        void avancarHoras(int horas){
            if (!this->emAndamento) {
                cout << "Erro: A viagem não está em andamento." << endl;
                return;
            }

            int distanciaRestante = this->destino->getNome() != this->transporte->getLocalAtual()->getNome() ? (this->transporte->getDistanciaDescanso() - this->horasEmTransito) : 0; // Aqui supondo trajeto.

            int distanciaPercorrida = this->transporte->getVelocidade() * horas;
            this->horasEmTransito += horas;

            if (distanciaPercorrida >= distanciaRestante) {
                this->transporte->setLocalAtual(this->destino);
                
                for (Passageiro* passageiro : this->passageiros) {
                    passageiro->setLocalAtual(this->destino);
                }

                this->emAndamento = false;
                cout << "Viagem concluída! Chegamos ao destino: " << this->destino->getNome() << endl;

            } else {
                // Atualize a posição intermediária aqui (opcional, baseado no contexto do trajeto).
                cout << "Viagem em progresso. " << distanciaRestante - distanciaPercorrida << " km restantes." << endl;
            }
        }
        
        void relatarEstado(){
            cout << "Status da Viagem:" << endl;
            cout << "Origem: " << this->origem->getNome() << endl;
            cout << "Destino: " << this->destino->getNome() << endl;
            cout << "Local Atual do Transporte: " << this->transporte->getLocalAtual()->getNome() << endl;
            cout << "Horas em trânsito: " << this->horasEmTransito << endl;
            cout << "Status: " << (this->emAndamento ? "Em andamento" : "Concluída") << endl;
        }
        
        bool isEmAndamento(){
            return this->emAndamento;
        }
};

#endif
