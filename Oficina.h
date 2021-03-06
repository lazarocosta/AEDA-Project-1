/*
 * Oficina.h
 */

#ifndef OFICINA_H_
#define OFICINA_H_

#include <string>
#include <iostream>
#include "Camiao.h"
#include <vector>

using namespace std;

class Oficina
{
public:
	/** \brief Criacao de uma Oficina por definicao
	    \param Nao possui parametros

		\return Nao possui retorno
	 */
	Oficina();

	/**
	 * \brief Construtor de uma Oficina
	 * \param nome Nome da Oficina
	 * \param marca Marca da Oficina criada
	 * \param disp tempo que a Oficina demora a ficar disponivel
	 * \param camioes veiculos que estao na oficina
	 *
	 * \return Nao possui retorno
	 *
	 */
	Oficina(string nome, string marca, int disp, vector<Camiao*> camioes);
	/**
	 * \brief Retorna o nome da Oficina
	 * \param Nao possui parametros
	 *
	 * \return nome Nome da Oficina
	 */
	string getNome()const;

	/*
	 * \brief Retorna a marca da Oficina
	 * \param Nao possui parametros
	 *
	 * \return marca Marca da Oficina
	 */
	string getMarca()const;

	/*
	 * \brief Retorna os veiculos da oficina
	 * \param Nao possui parametros
	 *
	 * \return cami os veiculos da oficina
	 */
	vector<Camiao*> getVeiculos()const;
	/*
	 * \brief Retorna a disponibilidade da Oficina
	 * \param Nao possui parametros
	 *
	 * \return disp Disponibilidade da Oficina
	 */
	int getDisp()const;
	/*
	 * \brief Overload do operador < entre oficinas para a comparacao das mesmas
	 * \param F Oficina com o qual vais fazer a comparacao
	 *
	 * \return Retorna em forma de booleano se a oficina e ou nao menor que a Oficina F
	 */
	bool operator <(const Oficina F)const;

	/*
	 * \brief realiza o servico ao camiao C, deixando-o indisponivel, adiciona a disponibilidade de 5 unidades e guarda esse camiao na oficina
	 * \param C Veiculo a que vai fazer o servi�o
	 *
	 * \return Nao possui retorno
	 */
	void fazServico(Camiao* C);

	/*
	 * \brief termina o servico da oficina ficando a disponibilidade reduzida de 5unidades e sem esse veiculo na oficina e este fica disponivel
	 * \param C, apontador para o camiao que vai terminar o servico
	 *
	 * \return Nao possui retorno
	 */
	void termServico(Camiao* C);
	/**
		 * \brief verifica se o apontador de Camiao ja se encontra na oficina
		 * \param C, apontador de camiao a procurar na oficina
		 *
		 * \return Retorna em forma de bool caso encontre ou nao
		 */
	bool camiaoNaOficina(Camiao* C);
	/**
	 * \brief Overload do operador << para fazer o cout de uma oficina
	 * \param s, ostream onde vamos guardar a informacao da oficina que vamos fazer cout
	 * \param F, oficina a que vamos fazer o cout
	 *
	 * \return Retorna em forma de ostream a informacao da oficina a imprimir
	 */
	friend ostream & operator<<(ostream & s, const Oficina  &F);
	/**
	 * \brief Altera a marca da oficina
	 * \param mar Nova marca da oficina
	 */
	void setMarca(string mar);

private:
	/** Nome da Oficina */
	string nome;
	/** Marca da Oficina */
	string marca;
	/** Disponibilidade da Oficina */
	int disp;
	/** Apontadores de camioes da oficina*/
	vector<Camiao*> Cami;

};
#endif /* OFICINA_H_ */
