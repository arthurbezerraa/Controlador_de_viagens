#ifndef CLASSES_CPP
#define CLASSES_CPP

#include <iostream>
#include <string>

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
        Transporte(string nome, char tipo_transporte, int capacidade_passageiros, int velocidade, int distancia_descanso, int tempo_descanso, Cidade* local_atual){
            this->nome = nome;
            this->tipo_transporte = tipo_transporte;
            this->capacidade_passageiros = capacidade_passageiros;
            this->velocidade = velocidade;
            this->distancia_descanso = distancia_descanso;
            this->tempo_descanso = tempo_descanso;
            this->local_atual = local_atual;
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
        Passageiro(string nome, Cidade* local_atual){
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

#endif