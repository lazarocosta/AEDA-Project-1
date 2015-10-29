/*
 * Servico.h
 *
 *  Created on: 13/10/2015
 *      Author: POS
 */

#ifndef SERVICO_H_
#define SERVICO_H_

#include "Camiao.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Servico
{
public:
	Servico(string origem, string destino,float distancia, string tipo_produto, float quantidade);
	string getOrigem()const;
	string getDestino()const;
	int getDistancia()const;
	string getTipo_produto()const;
	bool getIniciado()const;
	bool getTerminado()const;
	int getCapacidade()const;
	void setInicia();
	void setTermina();
	vector<int> inicia_servico();//retorna o vetor com o indice dos camioes ocupados, se n�o inicia retorna um vetor nulo
	void termina_servico();//atualiza todo o vetor de camioes, pondo desocupado os camioes que estao em veiculos ocupados
	bool operator < (const Servico &Ser)const;

private:
	static int globalID;
	int ID;
	vector<int> veiculos_ocupados;
	vector<Camiao*> Camioes;
	string origem;
	string destino;
	int distancia;
	int capacidade;
	string tipo_produto;
	bool iniciado;
	bool terminado;

};

#endif /* SERVICO_H_ */
