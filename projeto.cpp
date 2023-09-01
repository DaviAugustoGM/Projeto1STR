#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <time.h>
#include <Windows.h>

using namespace std;

#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>

# include "Item.cpp"

#define TAM_BUFFER 5
#define N_PRODUTORAS 2
#define N_CONSUMIDORAS 1
#define META 10

const string nomeItem[] = {"Resistor 150", "Resistor 1k", "Resistor 1M"};
const float preco[] = {0.50, 1.00, 1.50};

Item buffer[TAM_BUFFER];

int in = 0, out = 0;
//int produtos = 0;
int progresso_producao = 0;
int progresso_consumo = 0;

sem_t empty, full;
pthread_mutex_t mutex;

void producao(){
	
	int n = rand() % 2;
	Qualidade qualidade;
	
	if(n == 0) qualidade = Qualidade::PESSIMA;
	else qualidade = Qualidade::OTIMA;
	
	n = rand() % 3;
	
	Item novoItem(nomeItem[n], preco[n], qualidade, false, ++progresso_producao);
	
    buffer[in] = novoItem;
    in = (in + 1) % TAM_BUFFER;
		
    cout << "Item ( " << novoItem.getId() 
	     << " ) Produzido: Nome: " << novoItem.getNome() 
    	 << " Preco: " << novoItem.getPreco() << setprecision(2) << endl << endl;
}

void consumo(){
	
	Item item;
	
	item = buffer[out];
    out = (out + 1) % TAM_BUFFER;
    
	cout << "Processando Item: " << item.getId() << endl;
    
	if(item.getQualidade() == Qualidade::OTIMA){
		
		item.setFoiEmbalado(true);
		
		cout << "Item de [Otima qualidade]. Embalado e pronto para envio." << endl
			 << "Itens Embalados: " << ++progresso_consumo << endl << endl;
	}
	else
		cout << "Item encaminhado para reciclagem!!!" << endl << endl;
}

void *maquina_produtora(void *arg) {
	
	while (1) {
        
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        
        if(progresso_consumo == META){
        	pthread_mutex_unlock(&mutex);
        	break;
        }
        
        producao();
        
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
    pthread_exit(NULL);
}

void *maquina_consumidora(void *arg) {
    
	while (1) {
		
		if(progresso_consumo == META)
        	break;
        
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        
        if(progresso_consumo == META){
        	pthread_mutex_unlock(&mutex);
        	break;
        }
        consumo();
        
    	pthread_mutex_unlock(&mutex);
    	sem_post(&empty);
    }
    pthread_exit(NULL);
}

int main() {
	
	cout << " ----- Fabrica STR -----" << endl << endl;
	
    srand(time(NULL));
    pthread_t maquinas_produtoras[N_PRODUTORAS];
    pthread_t maquinas_consumidoras[N_CONSUMIDORAS];

    sem_init(&empty, 0, TAM_BUFFER);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < N_PRODUTORAS; i++)
        pthread_create(&maquinas_produtoras[i], NULL, maquina_produtora, NULL);

    for (int i = 0; i < N_CONSUMIDORAS; i++)
        pthread_create(&maquinas_consumidoras[i], NULL, maquina_consumidora, NULL);

    for (int i = 0; i < N_PRODUTORAS; i++)
        pthread_join(maquinas_produtoras[i], NULL);

    for (int i = 0; i < N_CONSUMIDORAS; i++)
        pthread_join(maquinas_consumidoras[i], NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    
    system("pause");

    return 0;
}

