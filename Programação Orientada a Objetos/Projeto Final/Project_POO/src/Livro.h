/*
 * Livro.h
 *
 *  Created on: Jul 24, 2022
 *      Author: Victor
 */

#ifndef LIVRO_H_
#define LIVRO_H_

#include <string>

#define LIVROS   "livraria.csv"

using namespace std;

class Livro{
private:
	string id;
	string titulo;
	string autor;
	string genero;
	string sub_genero;
	string editora;
	int paginas = 0;
	int copias = 0;
	int disponiveis = 0;
	int reservados = 0;

public:
	Livro(){}
	virtual ~Livro(){}

	void listar(void);
	void pesquisarNome(void);
	void pesquisarAutor(void);
	void pesquisarId(void);
	void adicionar(void);
	void atualizar(string s, int op);
	int  selecionar(void);
	int  quantidade(void);

	string getId(void)			{return id;};
	string getTitulo(void)		{return titulo;};
	string getAutor(void)		{return autor;};
	string getGenero(void)		{return genero;};
	string getSubgenero(void)	{return sub_genero;};
	string getEditora(void)		{return editora;};
	int getPaginas(void)		{return paginas;};
	int getCopias(void)			{return copias;};
	int getDisponiveis(void)	{return disponiveis;};
	int getReservados(void)		{return reservados;};

};

#endif /* LIVRO_H_ */
