/*
 * Empresa.h
 */

#ifndef EMPRESA_H_
#define EMPRESA_H_

#include <vector>
#include <string>
#include <iostream>
#include <set>
#include "Cliente.h"
#include "Servico.h"
#include "Funcionario.h"
#include "Camiao.h"
#include "InsertionSort.h"
#include <tr1/unordered_set>
#include "Oficina.h"
#include "BST.h"

using namespace std;

class OficinaNaoApropriada
{
public:
	OficinaNaoApropriada(){};
};

class OficinaJaExistente
{
public:
	/**
	 * \brief Construtor para lancar a excepcao de uma oficina que ja existe, dai nao poder ser novamente inserida na fila de prioridade oficinas;
	 */
	OficinaJaExistente(){}
};

class OficinaInexistente
{
public:
	/**
	 * \brief Construtor para lancar a excepcao de uma oficina que nao existe por isso nao pode ser removida da fila de prioridade oficinas
	 */
	OficinaInexistente(){}
};

class OficinaOcupada
{
public:
	/**
	 * \brief Construtor para lancar a excepcao de uma oficina que esta ocupada por isso nao pode realizar outro servico
	 */
	OficinaOcupada(){}
};

class CamiaoNaoExistente
{
public:
	/**
	 * \brief Construtor para lancar a excepcao de um camiao que nao existe por isso nao pode ser utilizado para realizar servicos
	 */
	CamiaoNaoExistente(){}
};

class CamiaoJaExistente
{
	/**
	 * Identificacao do Camiao que ja existe
	 */
	string matricula;
public:
	/**
	 * \brief Construtor para lancar a excepcao de um Camiao ja existente
	 * \param matricula Identifica o Camiao que ja existe e que nao pode ser adicionado
	 */
	CamiaoJaExistente(string matricula){this->matricula = matricula;}
	/**
	 * \brief Retorna a identificacao do Camiao ja existente
	 * \return Matricula do Camiao	ja existente
	 */
	string getMatricula(){return matricula;}
};

class ServicoInexistente
{
public:
	/**
	 * \brief Construtor para lancar a excepcao de um Servico que nao existe, portanto impossivel de aceder
	 */
	ServicoInexistente(){}
};


class FicheiroInexistente
{
	/**
	 * Nome do ficheiro que nao e possivel encontrar e aceder
	 */
	string ficheiro;
public:
	/**
	 * \brief Construtor para lancar a excepcao de um Ficheiro que nao existe ou nao consegue aceder
	 */
	FicheiroInexistente(string nome){ficheiro = nome;}
	/**
	 * \brief Retorna o nome do Ficheiro que nao existe
	 * \return Nome do Ficheiro que nao existe
	 */
	string getFicheiro(){return ficheiro;}
};


class ClienteJaExistente
{
	/** Nome do Cliente que ja pertence ao grupo de clientes */
	string nome;
	/** Numero de identificacao do Cliente ja existente */
	unsigned long nif;
public:
	/**
	 * \brief Construtor para lancar a excepcao de um cliente que nao pode ser adicionado porque ja pertence ao grupo de clientes
	 * \param nome Nome do Cliente que ja existe
	 * \param nif Numero de identificacao do Cliente ja existente
	 */
	ClienteJaExistente(string nome,unsigned long nif){this->nome = nome;this->nif = nif;};
	/**
	 * \brief Retorna o nome do Cliente ja existente
	 * \return Nome do Cliente
	 */
	string getNome(){return nome;}
	/**
	 * \brief Retorna o numero de Identificacao do Cliente ja existente
	 * \return Numero de identificacao do cliente
	 */
	unsigned long getNif(){return nif;}
};


class ClienteNaoExistente
{
public:
	/**
	 * \brief Construtor para lancar a excepcao de um cliente que nao existe por isso nao pode ser utilizado para encomendar servicos
	 */
	ClienteNaoExistente(){}
};


class SaldoIndisponivel
{
public:
	/**
	 * \brief Construtor para lancar a excepcao no caso de ocorrer a possibilidade de a empresa nao ter dinheiro para poder pagar os salarios aos funcionarios
	 */
	SaldoIndisponivel(){};
};

struct hCliente {
	int operator()(const Cliente& c1) const{
		return 7;
	}
	bool operator()(const Cliente& c1, const Cliente& c2) const {
		return c1.getNif() == c2.getNif();
	}
};

typedef tr1::unordered_set<Cliente, hCliente, hCliente> hashClientes;

/**
 * \brief Classe que vai comparar os funcionarios, visto estes serem apontadores e nao objetos e por consequente ordena a BST
 */
struct classcomp
{
	bool operator()(const Funcionario * f1, Funcionario * f2)
	{
		if (f1->getHoras() == f2->getHoras())
		{
			return (f1->getNome() < f2->getNome());
		}

		return (f1->getHoras() < f2->getHoras());
	}
};

class Empresa
{
private:
	/** Nome da empresa */
	string nomeEmpresa;
	/** Endereco da posicao do ficheiro de Camioes */
	string ficca;
	/** Endereco da posicao do ficheiro de Clientes */
	string ficcli;
	/** Endereco da posicao do ficheiro de Funcionarios */
	string ficfun;
	/** Endereco da posicao do ficheiro de Sercvicos */
	string ficser;
	/** Endereco da posicao do ficheiro de Oficinas */
	string ficofi;
	/** Saldo atual da empresa */
	long saldo;
	/** Vector de Camioes pertencentes a empresa */
	vector<Camiao *> camioes;
	/** Vector de Servicos da empresa, em exucucao e ja terminados */
	vector<Servico> servicos;
	/** Vector de Clientes que tem conta na empresa */
	vector<Cliente> clientes;
	/** Vector de Funcionarios que trabalham na empresa */
	set<Funcionario *, classcomp> funcionarios;
	/** Fila de prioridade de Oficinas da empresa */
	priority_queue<Oficina> oficinas;
	/** Tabela de dispersao de clientes inactivos */
	hashClientes clInact;


public:
	/**
	\brief Construtor sem parametros
	 */
	Empresa();
	/**
	\brief Inicializa os dados da empresa
	\param doc Directorio dos ficheiros que contem os dados da empresa
	 */
	Empresa(string doc);
	/**
	\brief Devolve o vector de camioes da empresa
	\return vector de camioes da empresa */
	vector<Camiao *> getCamioes();
	/**
	\brief Devolve o vector de funcionarios da empresa
	\return vector de funcionarios da empresa */
	set<Funcionario *, classcomp> getFuncionarios();
	/**
	\brief Permite adicionarum novo cliente a empresa
	\return Nao possui retorno */
	void adicionaCliente();
	/**
	\brief Adiciona um novo servico do tipo Normal ou Animais
	\param origem origem do servico
	\param destino destino do servico
	\param distancia distancia do transporte
	\param tipo_produto tipo do produto a ser transportado
	\param capacidade carga a ser transportada
	\param Nif NIF do cliente que pretende adicionar o servico
	\return Nao possui retorno */
	void novoServico(string origem, string destino, int distancia, string tipo_produto, int capacidade, unsigned long Nif);
	/**
	\brief Adiciona um novo servico do tipo Congelacao
	\param origem origem do servico
	\param destino destino do servico
	\param distancia distancia do transporte
	\param tipo_produto tipo do produto a ser transportado
	\param capacidade carga a ser transportada
	\param Nif NIF do cliente que pretende adicionar o servico
	\param temp temperatura do servico desejado
	\return Nao possui retorno */
	void novoServico(string origem, string destino, int distancia, string tipo_produto, int capacidade, unsigned long Nif, int temp);
	/**
	\brief Adiciona um novo servico do tipo Perigosos
	\param origem origem do servico
	\param destino destino do servico
	\param distancia distancia do transporte
	\param tipo_produto tipo do produto a ser transportado
	\param capacidade carga a ser transportada
	\param Nif NIF do cliente que pretende adicionar o servico
	\param nivel_p nivel de perigosidade do servico desejado
	\return Nao possui retorno */
	void novoServico(string origem, string destino, int distancia, string tipo_produto, int capacidade, unsigned long Nif, string nivel_p);
	/**
	\brief Le do ficheiro um servico do tipo Normal ou Animais
	\param origem origem do servico
	\param destino destino do servico
	\param distancia distancia do transporte
	\param tipo_produto tipo do produto a ser transportado
	\param capacidade carga a ser transportada
	\param Nif NIF do cliente que pretende adicionar o servico
	\param ter estado do servico (terminado ou nao)
	\return Nao possui retorno */
	void leNovoServico(string origem, string destino, int distancia, string tipo_produto, int capacidade, unsigned long Nif, vector<string> mat, vector<unsigned long> funcs, bool ter);
	/**
	\brief Le do ficheiro um servico do tipo Congelacao
	\param origem origem do servico
	\param destino destino do servico
	\param distancia distancia do transporte
	\param tipo_produto tipo do produto a ser transportado
	\param capacidade carga a ser transportada
	\param Nif NIF do cliente que pretende adicionar o servico
	\param temperatura do servico desejado
	\param ter estado do servico (terminado ou nao)
	\return Nao possui retorno */
	void leNovoServico(string origem, string destino, int distancia, string tipo_produto, int capacidade, unsigned long Nif, int temp, vector<string> mat, vector<unsigned long> funcs, bool ter);
	/**
	\brief Le do ficheiro um servico do tipo Perigosos
	\param origem origem do servico
	\param destino destino do servico
	\param distancia distancia do transporte
	\param tipo_produto tipo do produto a ser transportado
	\param capacidade carga a ser transportada
	\param Nif NIF do cliente que pretende adicionar o servico
	\param nivel_p nivel de perigosidade do servico desejado
	\param ter estado do servico (terminado ou nao)
	\return Nao possui retorno */
	void leNovoServico(string origem, string destino, int distancia, string tipo_produto, int capacidade, unsigned long Nif, string nivel_p, vector<string> mat, vector<unsigned long> funcs, bool ter);
	/**
	\brief Permite a contratacao de um funcionario para a empresa
	\return Nao possui retorno */
	void contrataFuncionario();
	/**
	\brief Permite pagar os salarios a todos os funcionarios da empresa
	\return Nao possui retorno */
	void pagaSalario();
	/**
	\brief Devolve o nome da empresa
	\return Devolve o nome da empresa */
	string getNome() const;
	/**
	\brief Imprime o saldo actual da empresa
	\return Nao possui retorno */
	void imprimeSaldo() const;
	/**
	\brief Mostra no ecra a informacao de todos os servicos
	\return Nao possui retorno */
	void imprimeServicos();
	/**
	\brief Mostra no ecra a informacao acerca de um servico
	\return Nao possui retorno */
	void imprimeServico(Servico s) ;
	/**
	\brief Mostra no ecra a informacao acerca de todos os servicos em execucao
	\return Nao possui retorno */
	void ListaServicosExecucao();
	/**
	\brief Mostra no ecra a informacao acerca de todos os servicos de um cliente
	\return Nao possui retorno */
	void ListaServicosCliente();
	/**
	\brief Mostra no ecra a informacao acerca de todos os servicos de um camiao
	\return Nao possui retorno */
	void ListaServicosCamiao();
	/**
	\brief Mostra no ecra a informacao ordenada acerca de todos os camioes
	\return Nao possui retorno */
	void ListaCamioesOrdenados()const;
	/**
	\brief Mostra no ecra a informacao acerca de todos os clientes
	\return Nao possui retorno */
	void listaClientes() const;
	/**
	\brief Mostra no ecra a informacao ordenada acerca de todos os clientes
	\return Nao possui retorno */
	void listaClientesOrdenados();
	/**
	\brief Verifica se o cliente ja esta registado
	\return Devolve o indice do vector onde o cliente se encontra ou lanca uma exepcao caso nao encontre */
	int posCliente(unsigned long nif) const;
	/**
	\brief Actualiza o saldo da empresa, os camioes da empresa e os funcionarios nos ficheiros correspondentes
	\return Nao possui retorno */
	void actualizaFicheiro();
	/**
	\brief Termina um servico e actualiza o estado dos camioes e dos funcionarios associados ao servico e actualiza os ficheiros necessarios
	\param ID ID do servico que se pretende terminar
	\return Nao possui retorno */
	void terminaServico(int ID);
	/**
	\brief Actualiza o ficheiro de servicos com o novo estado do servico
	\param ID ID do servico que foi terminado
	\param tipo do servico que foi terminado
	\return Nao possui retorno */
	void EscreveServicoTerminado(int ID, string tipo);
	/**
	\brief Mostra no ecra a informacao acerca de todos os camioes
	\return Nao possui retorno */
	void ImprimeListaCamioes();
	/**
	\brief Mostra no ecra a informacao ordenada acerca de todos os camioes
	\return Nao possui retorno */
	void ImprimeListaCamioesDisponiveis();
	/**
	\brief Permite adicionar um novo camiao a frota da empresa
	\return Nao possui retorno */
	void AdicionaCamiao();
	/**
	\brief Mostra no ecra a informacao acerca de todos os funcionarios
	\return Nao possui retorno
	 */
	void listaFuncionarios() const;
	/**
	\brief Mostra no ecra a informacao ordenada por nome acerca de todos os funcionarios
	\return Nao possui retorno
	 */
	void listaFuncionariosOrdenada();
	/**
	\brief Mostra no ecra a informacao acerca de todos os funcionarios disponiveis
	\return Nao possui retorno
	 */
	void listaFuncionariosDisponiveis() const;
	/**
	\brief Permite despedir um funcionario
	\return Nao possui retorno
	 */
	void despedeFuncionario();
	/**
	\brief Permite remover um camiao
	\return Nao possui retorno
	 */
	void retiraCamiao(string matricula);
	/**
	\brief Permite remover um cliente
	\return Nao possui retorno
	 */
	void retiraCliente(unsigned long Nif);
	/**
	\brief Permite editar um cliente
	\return Nao possui retorno
	 */
	void editaCliente();

	/*
	\brief insere  uma nova oficina na fila de prioridade oficinas

	\return Nao possui retorno
	 */
	void adicionaOficina();

	/*
	\brief procura, retira da fila de prioridade a oficina que vai ficar com o servico
	\return retorna a oficina que vai ficar com o servico usual
	 */
	Oficina serUsual(Camiao* C);

	/*
	\brief procura, retira da fila de prioridade a oficina que vai ficar com o servico especifico daquele camiao
	\param C veiculo que vai precisar do servico especifico

	\return retorna a oficina que vai ficar com o servico especifico
	 */
	Oficina serEspeci(Camiao* C);

	/*
	 * \brief insere na fila de prioridade oficinas a oficina atualizada com o novo servico especial do camiao C
	 *
	 * \return  Nao possui retorno
	 */
	void fazSerEspeci();

	/*
	 * \brief insere na fila de prioridade oficinas a oficina atualizada com o novo servico usual do camiao C
	 *
	 * \return  Nao possui retorno
	 */
	void fazSerUsual();

	/*
	 * \brief procura na fila de prioridade(oficinas) uma oficina que esteja a realizar o servico ao camiao C, retirando-a e retornando-a na funcao
	 * \param C camiao que vai ser procurado na fila de prioridade oficinas
	 *
	 * \return retorna a oficina que estava a realizar o servico do camiao C
	 */
	vector<Oficina> procuraCamiaoNaFila(Camiao* C);

	/**
	 *
	 * \brief insere na fila de prioridade oficinas a oficina devidamente atualizada que estava a realizar o servico do camiao C
	 * \param C camiao que recebeu o servico
	 *
	 * \return Nao possui retorno
	 */
	void termiServico();
	/**
	 * \brief Funcao que procura no vetor de camioes o camiao pretendido
	 * \param Matri Matricula do camiao que se pretende encontrar
	 * \return Apontador para o camiao pretendido
	 */
	Camiao* procuraCamiao(string Matri);
	/**
	 * \brief Lista das oficinas existentes
	 */
	void listaOficinas();
	/**
	 * \brief Remove uma determinada oficina posteriormente identificada
	 */
	void removeOficina();
	/**
	 * \brief Funcao que procura na fila de prioridade a oficina determinada
	 * \param F Oficina que se pretende encontrar
	 * \return Retorna a oficina pretendida
	 */
	Oficina procuraOficina(Oficina F);
	/**
	 * \brief Funcao que verifica se uma determinada oficina existe
	 * \param F Oficina que se pretende encontrar
	 * \return Retorna verdadeiro ou falso mediante exista ou nao a oficina pretendida
	 */
	bool existeOficina(Oficina F);
	/**
	 * \brief Funcao que imprime os clienes inativos
	 */
	void imprimeClientesIn() const;
	/**
	 * \brief Funcao que
	 */
	void actualizaClientes();
	/**
	 * \brief Funcao que define um cliente como inativo
	 * \param nif Nif do cliente que se pretende tornar inativo
	 */
	void defineClienteInactivo(unsigned long nif);
	/**
	 * \brief Funcao que define um cliente como ativo
	 * \param nif Nif do cliente que se pretende tornar ativo
	 */
	void defineClienteActivo(unsigned long nif);
	/**
	 * \brief Funcao que transforma a BST de Funcionarios num vetor de Funcionarios
	 * \return Vetor de funcionarios
	 */
	vector<Funcionario *> getFuncionariosvetor();
	/**
	 * \brief Funcao que pesquisa um cliente quer no vetor de clientes ativos quer na tabela de expressao de clientes inativos
	 * \param nif Nif do cliente que pretendemos encontrar
	 * \param show Variavel que define se ha impressao de informacao ou nao
	 * \return Retorna 0 se o cliente for ativo, 1 se for inativo e -1 se nao existir
	 */
	int pesquisaCliente(unsigned long nif, int show);

	/**
	 * \brief Funcao que edita o funcionario, ou seja lhe altera o salario
	 */
	void editaFuncionario();
	/**
	 * \brief Funcao que edita a oficina, ou seja lhe modifica a marca
	 */
	void editaOficina();

};



#endif /* EMPRESA_H_ */
