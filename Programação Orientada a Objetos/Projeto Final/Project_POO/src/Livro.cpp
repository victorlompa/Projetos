#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <cctype>
#include <algorithm>

#include <stdio.h>
#include <stdlib.h>

#include "Livro.h"

using namespace std;

void Livro::listar(void){
	string buffer;
	ifstream f;

	f.open(LIVROS, ios_base::in);
	if(!f.is_open()){
		cerr << "Erro ao abrir arquivo " << LIVROS << endl;
		exit(EXIT_FAILURE);
	}

	getline(f,buffer,'\n'); // Ignora cabeçalho

	while(getline(f,buffer,';')){
		cout << buffer << " - ";
		getline(f,buffer,';');
		cout << buffer;
		getline(f,buffer,';');
		cout << " | " << buffer << endl;
		getline(f,buffer,'\n');
	}

	f.close();

	cout << endl << "Pressione enter para retornar ao menu" << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();
	return;
}

void Livro::pesquisarNome(void){
	string::size_type i, j;
	string buffer;
	string procura;
	string titulo;
	string id;
	ifstream f;
	vector<string> livro;
	vector<vector<string>> livros;
	vector<string>::iterator it1;
	vector<string>::iterator it2;

	cout << "Procurar por nome:" << endl;
	cout << ">> "; cin >> procura;
	if(cin.bad()){
		cerr << "Nome inválido para procura." << endl;
		return;
	}
	for(i = 0; i < procura.length(); i++){
		procura[i] = tolower(procura[i]);
	}

	f.open(LIVROS, ios_base::in);
	if(!f.is_open()){
		cerr << "Erro ao abrir arquivo " << LIVROS << endl;
		exit(EXIT_FAILURE);
	}

	getline(f,buffer,'\n'); // Ignora cabeçalho

	while(getline(f,id,';')){
		getline(f,buffer,';');
		titulo = buffer;
		for(i = 0; i < buffer.length(); i++){
			buffer[i] = tolower(buffer[i]);
		}
		if(buffer.find(procura) != buffer.npos){
			livro.push_back(id);							// Id
			livro.push_back(titulo);						// Titulo
			getline(f,buffer,';'); livro.push_back(buffer); // Autor
			getline(f,buffer,';'); livro.push_back(buffer); // Genero
			getline(f,buffer,';'); livro.push_back(buffer); // Sub Genero
			getline(f,buffer,';'); livro.push_back(buffer); // Paginas
			getline(f,buffer,';'); livro.push_back(buffer); // Editora
			getline(f,buffer,';'); livro.push_back(buffer); // Copias
			getline(f,buffer,';'); livro.push_back(buffer); // Disponiveis
			getline(f,buffer,'\n'); livro.push_back(buffer); // Reservadas
			livros.push_back(livro);
			livro.clear();
		}
		else getline(f,buffer,'\n');
	}

	if (livros.size() > 0){
		cout << "==========================" << endl << endl;
		cout << "Livros encontrados: " << livros.size() << endl << endl;
		cout << "--------------------------" << endl;
		for(i = 0; i < livros.size(); i++){
				j = 0;
				cout << "ID: " << livros[i][j] << endl; j++;
				cout << "Titulo: " << livros[i][j] << endl; j++;
				cout << "Autor: " << livros[i][j] << endl; j++;
				cout << "Gênero: " << livros[i][j] << endl; j++;
				cout << "Subgênero: " << livros[i][j] << endl; j++;
				cout << "Paginas: " << livros[i][j] << endl; j++;
				cout << "Editora: " << livros[i][j] << endl; j++;
				cout << endl;
				cout << "Copias: " << livros[i][j] << endl; j++;
				cout << "Disponiveis: " << livros[i][j] << endl; j++;
				cout << "Reservadas: " << livros[i][j] << endl;
				cout << "--------------------------" << endl << endl;
		}
	}
	else{
		cout << "Nenhum livro foi encontrado." << endl;
	}

	f.close();

	cout << "Pressione enter para retornar ao menu" << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();
};

void Livro::pesquisarAutor(void){
	string::size_type i, j;
	string procura;
	string buffer;
	string titulo;
	string autor;
	string id;
	ifstream f;
	vector<string> livro;
	vector<vector<string>> livros;
	vector<string>::iterator it1;
	vector<string>::iterator it2;

	cout << "Procurar por autor:" << endl;
	cout << ">> "; cin >> procura;
	if(cin.bad()){
		cerr << "Autor inválido para procura." << endl;
		return;
	}
	for(i = 0; i < procura.length(); i++){
		procura[i] = tolower(procura[i]);
	}

	f.open(LIVROS, ios_base::in);
	if(!f.is_open()){
		cerr << "Erro ao abrir arquivo " << LIVROS << endl;
		exit(EXIT_FAILURE);
	}

	getline(f,buffer,'\n'); // Ignora cabeçalho

	while(getline(f,id,';')){
		getline(f,titulo,';');
		getline(f,buffer,';');
		autor = buffer;
		for(i = 0; i < buffer.length(); i++){
			buffer[i] = tolower(buffer[i]);
		}
		if(buffer.find(procura) != buffer.npos){
			livro.push_back(id);							// Id
			livro.push_back(titulo);						// Titulo
			livro.push_back(autor);							// Autor
			getline(f,buffer,';'); livro.push_back(buffer); // Genero
			getline(f,buffer,';'); livro.push_back(buffer); // Sub Genero
			getline(f,buffer,';'); livro.push_back(buffer); // Paginas
			getline(f,buffer,';'); livro.push_back(buffer); // Editora
			getline(f,buffer,';'); livro.push_back(buffer); // Copias
			getline(f,buffer,';'); livro.push_back(buffer); // Disponiveis
			getline(f,buffer,'\n'); livro.push_back(buffer); // Reservadas
			livros.push_back(livro);
			livro.clear();
		}
		else getline(f,buffer,'\n');
	}

	if (livros.size() > 0){
		cout << "==========================" << endl << endl;
		cout << "Livros encontrados: " << livros.size() << endl << endl;
		cout << "--------------------------" << endl;
		for(i = 0; i < livros.size(); i++){
				j = 0;
				cout << "ID: " << livros[i][j] << endl; j++;
				cout << "Titulo: " << livros[i][j] << endl; j++;
				cout << "Autor: " << livros[i][j] << endl; j++;
				cout << "Gênero: " << livros[i][j] << endl; j++;
				cout << "Subgênero: " << livros[i][j] << endl; j++;
				cout << "Paginas: " << livros[i][j] << endl; j++;
				cout << "Editora: " << livros[i][j] << endl; j++;
				cout << endl;
				cout << "Copias: " << livros[i][j] << endl; j++;
				cout << "Disponiveis: " << livros[i][j] << endl; j++;
				cout << "Reservadas: " << livros[i][j] << endl;
				cout << "--------------------------" << endl << endl;
		}
	}
	else{
		cout << "Nenhum livro foi encontrado." << endl;
	}

	f.close();

	cout << "Pressione enter para retornar ao menu" << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();
};

void Livro::pesquisarId(void){
	int qtt;
	string::size_type i, j;
	string buffer;
	string procura;
	ifstream f;
	vector<string> livro;
	vector<vector<string>> livros;
	vector<string>::iterator it1;
	vector<string>::iterator it2;

	qtt = quantidade();

	cout << "Procurar por ID:" << endl;
	cout << ">> "; cin >> procura;
	if(cin.bad() || stoi(procura) > qtt || stoi(procura) < 1){
		cerr << "ID inválido para procura." << endl;
		return;
	}

	f.open(LIVROS, ios_base::in);
	if(!f.is_open()){
		cerr << "Erro ao abrir arquivo " << LIVROS << endl;
		exit(EXIT_FAILURE);
	}

	getline(f,buffer,'\n'); // Ignora cabeçalho

	while(getline(f,buffer,';')){
		if(stoi(buffer) == stoi(procura)){
			livro.push_back(buffer); 						// ID
			getline(f,buffer,';'); livro.push_back(buffer); // Titulo
			getline(f,buffer,';'); livro.push_back(buffer); // Autor
			getline(f,buffer,';'); livro.push_back(buffer); // Genero
			getline(f,buffer,';'); livro.push_back(buffer); // Sub Genero
			getline(f,buffer,';'); livro.push_back(buffer); // Paginas
			getline(f,buffer,';'); livro.push_back(buffer); // Editora
			getline(f,buffer,';'); livro.push_back(buffer); // Copias
			getline(f,buffer,';'); livro.push_back(buffer); // Disponiveis
			getline(f,buffer,'\n'); livro.push_back(buffer); // Reservadas
			livros.push_back(livro);
			livro.clear();
			break;
		}
		else getline(f,buffer,'\n');
	}

	if (livros.size() > 0){
		for(i = 0; i < livros.size(); i++){
			j = 0;
			cout << endl << "------------------" << endl;
			cout << "ID: " << livros[i][j] << endl; j++;
			cout << "Titulo: " << livros[i][j] << endl; j++;
			cout << "Autor: " << livros[i][j] << endl; j++;
			cout << "Gênero: " << livros[i][j] << endl; j++;
			cout << "Subgênero: " << livros[i][j] << endl; j++;
			cout << "Paginas: " << livros[i][j] << endl; j++;
			cout << "Editora: " << livros[i][j] << endl; j++;
			cout << endl;
			cout << "Copias: " << livros[i][j] << endl; j++;
			cout << "Disponiveis: " << livros[i][j] << endl; j++;
			cout << "Reservadas: " << livros[i][j] << endl;
			cout << "--------------------------" << endl << endl;
		}
	}
	else{
		cout << "Nenhum livro foi encontrado." << endl;
	}

	f.close();

	cout << "Pressione enter para retornar ao menu" << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();
};

int Livro::selecionar(void){
	int qtt;
	string buffer;
	string procura;
	ifstream f;

	qtt = quantidade();

	cout << "Selecionar ID:" << endl;
	cout << ">> "; cin >> procura;
	if(cin.fail() || stoi(procura) > qtt || stoi(procura) < 1){
		cerr << "ID inválido." << endl;
		return 0;
	}

	f.open(LIVROS, ios_base::in);
	if(!f.is_open()){
		cerr << "Erro ao abrir arquivo " << LIVROS << endl;
		exit(EXIT_FAILURE);
	}

	getline(f,buffer,'\n'); // Ignora cabeçalho

	while(getline(f,buffer,';')){
		if(stoi(buffer) == stoi(procura)){
			id = buffer;				// ID
			getline(f,titulo,';'); 		// Titulo
			getline(f,autor,';'); 		// Autor
			getline(f,genero,';'); 		// Genero
			getline(f,sub_genero,';'); 	// Sub Genero
			getline(f,buffer,';'); 	paginas = stoi(buffer);		// Paginas
			getline(f,editora,';'); 	// Editora
			getline(f,buffer,';'); 	copias = stoi(buffer);		// Copias
			getline(f,buffer,';'); 	disponiveis = stoi(buffer); // Disponiveis
			getline(f,buffer,'\n'); reservados = stoi(buffer);	// Reservadas
			break;
		}
		else getline(f,buffer,'\n');
	}
	f.close();
	return 1;
}

void Livro::adicionar(void){
	int i;
	ifstream f;
	string buffer;
	vector<string> novosDados;

	i = quantidade() + 1;
	stringstream ss; ss << i; ss >> buffer;
	novosDados.push_back(buffer); // ID

	cout << "Título:" << endl;
	cout << ">> " << flush; getline(cin>>ws, buffer);
	if(cin.fail()){
		cerr << "Título inválido" << endl;
		cin.clear();
		return;
	}
	novosDados.push_back(buffer); // Títulos

	cout << "Autor:" << endl;
	cout << ">> " << flush; getline(cin>>ws, buffer);
	if(cin.fail()){
		cerr << "Autor inválida" << endl;
		cin.clear();
		return;
	}
	novosDados.push_back(buffer); // Autor

	cout << "Genêro:" << endl;
	cout << ">> " << flush; getline(cin>>ws, buffer);
	if(cin.fail()){
		cerr << "Genero inválido" << endl;
		cin.clear();
		return;
	}
	novosDados.push_back(buffer); // Gênero

	cout << "Subgênero:" << endl;
	cout << ">> " << flush; getline(cin>>ws, buffer);
	if(cin.fail()){
		cerr << "Subgênero inválido" << endl;
		cin.clear();
		return;
	}
	novosDados.push_back(buffer); // Subgênero

	cout << "Páginas:" << endl;
	cout << ">> " << flush; getline(cin>>ws, buffer);
	if(cin.fail()){
		cerr << "Páginas inválido" << endl;
		cin.clear();
		return;
	}
	novosDados.push_back(buffer); // Páginas

	cout << "Editora:" << endl;
	cout << ">> " << flush; getline(cin>>ws, buffer);
	if(cin.fail()){
		cerr << "Editora inválida" << endl;
		cin.clear();
		return;
	}
	novosDados.push_back(buffer); // Editora

	cout << "Cópias:" << endl;
	cout << ">> " << flush; getline(cin>>ws, buffer);
	if(cin.fail()){
		cerr << "Cópias inválido" << endl;
		cin.clear();
		return;
	}
	novosDados.push_back(buffer);  // Cópias
	novosDados.push_back(buffer); // Disponíveis
	novosDados.push_back("0"); // Reservados

	cout << endl;
	cout << "Prosseguir com a criação de um novo livro com estes dados? [Y/N]" << endl;
	cin >> buffer;

	if(buffer == "y" || buffer == "Y"){
		ofstream f;

		f.open(LIVROS, ios_base::app);
		if(!f.is_open()){
			cerr << "Erro ao abrir arquivo " << LIVROS << endl;
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

int Livro::quantidade(void){
	string buffer;
	ifstream f;
	int i = 0;

	f.open(LIVROS, ios_base::in);
	if(!f.is_open()){
		cerr << "Erro ao abrir arquivo " << LIVROS << endl;
		exit(EXIT_FAILURE);
	}

	getline(f,buffer,'\n'); // Ignora cabeçalho
	while(getline(f, buffer, '\n')){i++;}

	f.close();
	return i;
}

// Livro::atualizar altera o valor de livros disponíveis
// String s: Nome do livro a ser atualizado
// int op:  0 - diminui um livro disponível
//			1 - aumenta um livro disponível
void Livro::atualizar(string s, int op){
	fstream fin, fout;
	string buffer;
	string titulo;
	int i;

	if(op != 0 && op != 1){
		cerr << "Operação inválida." << endl;
		return;
	}

	fin.open(LIVROS, ios::in);
	if(!fin.is_open()){
		cerr << "Erro ao abrir arquivo " << LIVROS << endl;
		exit(EXIT_FAILURE);
	}

	fout.open("temp.csv", ios::out);
	if(!fout.is_open()){
		cerr << "Erro ao abrir arquivo " << "temp.csv" << endl;
		exit(EXIT_FAILURE);
	}

	while(getline(fin,buffer,';')){
		getline(fin,titulo,';');
		fout << buffer << ';'; 		// ID
		fout << titulo << ';';		// Titulo
		getline(fin,buffer,';');
		getline(fin,titulo,';');
		fout << buffer << ';';		// Autor
		fout << titulo << ';';		// Genero
		getline(fin,buffer,';');
		getline(fin,titulo,';');
		fout << buffer << ';';		// subgênero
		fout << titulo << ';';		// paginas
		getline(fin,buffer,';');
		getline(fin,titulo,';');
		fout << buffer << ';';		// editora
		fout << titulo << ';';		// copias
		getline(fin,buffer,';');
		getline(fin,titulo,'\n');

		// Disponiveis
		if(titulo != s) fout << buffer << ';';
		else {
			i = stoi(buffer);
			if(op == 1) i++;
			else i--;
			stringstream ss;
			ss << i; ss >> buffer;
			fout << buffer << ';';
		}
		fout << titulo << '\n';		// reservados
	}

	fout.close();
	fin.close();

	remove(LIVROS);
	rename("temp.csv", LIVROS);

	return;
}
