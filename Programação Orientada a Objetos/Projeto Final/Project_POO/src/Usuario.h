/*
 * Usuario.h
 *
 *  Created on: Jul 24, 2022
 *      Author: Victor
 */

#ifndef USUARIO_H_
#define USUARIO_H_

#include <string>

#define USUARIO "usuarios.csv"

using namespace std;

class Usuario{
private:
	string login;
	string password;
	string nome;
	string cep;
	string celular;
	string email;
	int permissao;
	int emprestimos;

public:
	Usuario();
	virtual ~Usuario();

	int  logar(void);
	void deslogar(void);
	void registrar(void);
	void atualizar(void);
	void mostrarDados(void);

	string getNome(void)	{return nome;};
	string getCep(void)		{return cep;};
	string getCelular(void)	{return celular;};
	string getEmail(void)	{return email;};
	int getPermissao(void)	{return permissao;}
	int getEmprestimos(void){return emprestimos;};

	void addEmprestimo(void){emprestimos += 1;};
	void subEmprestimo(void){emprestimos -= 1;};
};


#endif /* USUARIO_H_ */
