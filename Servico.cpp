/*
 * Servico.cpp
 *
 *  Created on: 13/10/2015
 *      Author: POS
 */

#include "Servico.h"

int Servico::globalID = 0;


Servico::Servico()
{

}


Servico::Servico(string origem, string destino, int distancia, string tipo_produto, int capacidade, unsigned long Nif, vector<Camiao *> &c)
{
	unsigned int i = 0;

	while(capacidade > 0 && i < c.size())
	{
		if (c[i]->getTipo() == tipo_produto && c[i]->getDisponivel())
		{
			capacidade = capacidade - c[i]->getCapacidade();
			Camioes.push_back(c[i]);
			if (origem != "abcd") // para pedir o orcamento arbitra-se um a origem "abcd"
				c[i]->setDisponivel(false);
		}
		i++;
	}

	if (capacidade > 0)
		throw camioesIndisponiveis();

	if (origem != "abcd")
		for(unsigned int i = 0; i < Camioes.size(); i++)
			Camioes[i]->setDisponivel(false);

	this->origem = origem;
	this->destino = destino;
	this->distancia = distancia;
	this->tipo_produto = tipo_produto;
	this->capacidade = capacidade;
	iniciado = false;
	terminado = false;
	ID = globalID++;
	this->Nif=Nif;
	preco = 0;
	for (unsigned int i = 0; i < Camioes.size(); i++)
		preco = preco + Camioes[i]->getPreco(distancia);

}

Servico::Servico(string origem, string destino, int distancia, string tipo_produto, int capacidade, unsigned long Nif, vector<Camiao *> &c, int temp)
{
	unsigned int i = 0;

	while(capacidade > 0 && i < c.size())
	{
		if (c[i]->getTipo() == tipo_produto && c[i]->getDisponivel())
		{
			capacidade = capacidade - c[i]->getCapacidade();
			Camioes.push_back(c[i]);
			if (origem != "abcd") // para pedir o orcamento arbitra-se um a origem "abcd"
				c[i]->setDisponivel(false);
		}
		i++;
	}

	if (capacidade > 0)
		throw camioesIndisponiveis();

	if (origem != "abcd")
		for(unsigned int i = 0; i < Camioes.size(); i++)
			Camioes[i]->setDisponivel(false);

	this->origem = origem;
	this->destino = destino;
	this->distancia = distancia;
	this->tipo_produto = tipo_produto;
	this->capacidade = capacidade;
	iniciado = false;
	terminado = false;
	ID = globalID++;
	this->Nif=Nif;
	preco = 0;
	for (unsigned int i = 0; i < Camioes.size(); i++)
	{
		double dif = 20 - temp;
		dif = dif / 10;
		preco += (6 + dif) * distancia;
	}
}

Servico::Servico(string origem, string destino, int distancia, string tipo_produto, int capacidade, unsigned long Nif, vector<Camiao *> &c, string nivel_p)
{
	unsigned int i = 0;

	while(capacidade > 0 && i < c.size())
	{
		if (c[i]->getTipo() == tipo_produto && c[i]->getDisponivel())
		{
			capacidade = capacidade - c[i]->getCapacidade();
			Camioes.push_back(c[i]);
			if (origem != "abcd") // para pedir o orcamento arbitra-se um a origem "abcd"
				c[i]->setDisponivel(false);
		}
		i++;
	}

	if (capacidade > 0)
		throw camioesIndisponiveis();

	if (origem != "abcd")
		for(unsigned int i = 0; i < Camioes.size(); i++)
			Camioes[i]->setDisponivel(false);

	this->origem = origem;
	this->destino = destino;
	this->distancia = distancia;
	this->tipo_produto = tipo_produto;
	this->capacidade = capacidade;
	iniciado = false;
	terminado = false;
	ID = globalID++;
	this->Nif=Nif;
	preco = 0;
	for (unsigned int i = 0; i < Camioes.size(); i++)
	{
		if (nivel_p == "inflamavel")
			preco += 7 * distancia;
		else if (nivel_p == "toxica")
			preco += 8 * distancia;
		else if (nivel_p == "corrosiva")
			preco += 7.5 * distancia;
		else if (nivel_p == "radioactiva")
			preco += 9 * distancia;
	}
}

string Servico::getOrigem()const
{
	return origem;
}

vector<Camiao*> Servico::getCamioes()
{
	return Camioes;
}

string Servico::getDestino()const
{
	return destino;
}


int Servico::getDistancia()const
{
	return distancia;
}

string Servico::getTipo_produto()const
{
	return tipo_produto;
}

bool Servico::getIniciado()const
{
	return iniciado;
}

bool Servico::getTerminado()const
{
	return terminado;
}

int Servico::getCapacidade()const
{
	return capacidade;
}

unsigned long Servico::getNif()const
{
	return Nif;
}

void Servico::setInicia()
{
	iniciado = true;
}

void Servico::setTermina()
{
	terminado = true;
}

vector<int> Servico::inicia_servico()
{
	int quantia = capacidade;
	vector<int> v;


	for(unsigned int i=0; i < Camioes.size(); i++)
	{
		if (Camioes[i]->getDisponivel()&& Camioes[i]->getTipo()==tipo_produto)
		{
			quantia = quantia - Camioes[i]->getCapacidade();
			v.push_back(i);
		}
	}

	if (quantia <= 0 )
	{
		for(unsigned int i=0; i <v.size(); i++)
		{
			Camioes[i]->setDisponivel( false);
			veiculos_ocupados.push_back(v[i]);
		}

		setInicia();
	}
	else
		throw ServicoNaoIniciado();


	return veiculos_ocupados;
}

void Servico::termina_servico()
{
	for(unsigned int i=0; i <veiculos_ocupados.size(); i++)
		Camioes[i]->setDisponivel(true);

	setTermina();

}

bool Servico::operator < (const Servico &Ser)const
{
	if (distancia < Ser.getDistancia())
		return true;

	if(distancia == Ser.getDistancia())
	{
		if(capacidade < Ser.getCapacidade())
			return true;
		else
			return false;
	}
	else return false;
}


int Servico::getPreco() const
{
	return preco;
}


