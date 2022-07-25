/*
 * Interface.h
 *
 *  Created on: Jul 24, 2022
 *      Author: Victor
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_

#include "Usuario.h"
#include "Livro.h"
#include "Emprestimo.h"

using namespace std;

void clrscr(void);

class Interface{
private:
	int status;
	Usuario usuarioAtual;
	Livro 	livroSelecionado;
	Emprestimo emprestimoAtual;

public:
	Interface();
	virtual ~Interface();
	void acesso(void);
	void menu(void);
	void menuEmprestimo(void);
};

#endif /* INTERFACE_H_ */
