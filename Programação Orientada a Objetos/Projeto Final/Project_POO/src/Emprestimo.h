#ifndef EMPRESTIMO_H_
#define EMPRESTIMO_H_

#include <iostream>
#include <ctime>

#include "Usuario.h"
#include "Livro.h"

#define EMPRESTIMO "emprestimos.csv"

using namespace std;

class Emprestimo{
private:
	Usuario usuarioAtual;
	Livro   livroAtual;
	time_t  saida;
	time_t  estimada;

public:
	Emprestimo(){}; // @suppress("Class members should be properly initialized")
	virtual ~Emprestimo(){};
	void fazerEmprestimo(Usuario u, Livro l);
	void consultarEmprestimos(Usuario u);
	int confirmarEmprestimo();
	void devolucao(Usuario u);
	int confirmaDevolucao(string s);
};


#endif /* EMPRESTIMO_H_ */
