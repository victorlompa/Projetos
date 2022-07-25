/*
 * Usuario.cpp
 *
 *  Created on: Jul 24, 2022
 *      Author: Victor
 */

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <cctype>
#include <algorithm>

#include <stdio.h>
#include <stdlib.h>

#include "Usuario.h"

using namespace std;


Usuario::Usuario(){
	permissao = 0;
	emprestimos = 0;
}

Usuario::~Usuario(){}

int Usuario::logar(){
	string buffLoging;
	string buffPassword;
	string buffer;
	ifstream f;

	cout << "Usuario: " << endl;
	cout << ">> " << flush; cin >> buffLoging;
	cout << endl << "Senha: " << endl;
	cout << ">> " << flush; cin >> buffPassword;

	f.open(USUARIO, ios_base::in);
	if(!f.is_open()){
		cerr << "Erro ao abrir arquivo " << USUARIO << endl;
		exit(EXIT_FAILURE);
	}

	getline(f,buffer,'\n'); // Ignora cabeçalho

	while(getline(f,login,';')){
		getline(f,password,';');
		if(login == buffLoging){
			if(password == buffPassword){
				getline(f,buffer,';'); permissao = stoi(buffer);
				getline(f,nome,';');
				getline(f,cep,';');
				getline(f,celular,';');
				getline(f,email,'\n');
				f.close();
				return 1;
			}
		}
		getline(f,buffer,'\n');
	}
	cerr << "Usuário ou senha inválidos." << endl;
	f.close();
	return 0;
};

void Usuario::deslogar(){
	login = "";
	password = "";
	nome = "";
	cep = "";
	celular = "";
	email = "";
	permissao = 0;
	emprestimos = 0;

	return;
}

void Usuario::registrar(){
	string buffer;
	vector<string> novosDados;

	cout << "Escolha um login:" << endl;
	cout << ">> " << flush; cin >> buffer;
	if(cin.bad()){
		cerr << "Login inválido" << endl;
		cin.clear();
		return;
	}
	novosDados.push_back(buffer);

	cout << "Escolha uma senha:" << endl;
	cout << ">> " << flush; cin >> buffer;
	if(cin.bad()){
		cerr << "Senha inválida" << endl;
		cin.clear();
		return;
	}
	novosDados.push_back(buffer);

	novosDados.push_back("0");

	cout << "Insira seu nome:" << endl;
	cout << ">> " << flush; getline(cin>>ws, buffer);
	if(cin.bad()){
		cerr << "Nome inválido" << endl;
		cin.clear();
		return;
	}
	novosDados.push_back(buffer);

	cout << "Insira seu CEP:" << endl;
	cout << ">> " << flush; cin >> buffer;
	if(cin.bad()){
		cerr << "CEP inválido" << endl;
		cin.clear();
		return;
	}
	novosDados.push_back(buffer);

	cout << "Insira seu telefone:" << endl;
	cout << ">> " << flush; cin >> buffer;
	if(cin.bad()){
		cerr << "Telefone inválido" << endl;
		cin.clear();
		return;
	}
	novosDados.push_back(buffer);

	cout << "Insira seu E-mail:" << endl;
	cout << ">> " << flush; cin >> buffer;
	if(cin.bad()){
		cerr << "E-mail inválido" << endl;
		cin.clear();
		return;
	}
	novosDados.push_back(buffer);

	cout << endl;
	cout << "Prosseguir com a criação de um novo usuário com estes dados? [Y/N]" << endl;
	cin >> buffer;

	if(buffer == "y" || buffer == "Y"){
		ofstream f;

		f.open(USUARIO, ios_base::app);
		if(!f.is_open()){
			cerr << "Erro ao abrir arquivo " << USUARIO << endl;
			exit(EXIT_FAILURE);
		}

		for(vector<string>::iterator it = novosDados.begin(); it != novosDados.end(); it++){
			f << *it;
			if(it != novosDados.end()-1) f << ";";
			else f << "\n";
		}

		f.close();
	}
	return;
}

void Usuario::mostrarDados(){
	cout << "Nome: " << nome << endl;
	cout << "CEP: " << cep << endl;
	cout << "Celular: " << celular << endl;
	cout << "E-mail: " << email << endl;
	cout << "Emprestimos: " << emprestimos << "/5" << endl;
	cout << endl << "Pressione enter para retornar ao menu" << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();
	return;
}
