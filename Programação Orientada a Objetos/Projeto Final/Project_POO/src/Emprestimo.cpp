#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <cctype>
#include <algorithm>

#include "Emprestimo.h"

#define SEMANA 604800

using namespace std;

void Emprestimo::fazerEmprestimo(Usuario u, Livro l){
	string buffer;
	string id;

	usuarioAtual = u;

	if(usuarioAtual.getEmprestimos() >= 5){
		cerr << "Você possui o número máximo de emprestimos permitido." << endl;
		return;
	}

	if(!livroAtual.selecionar()){
		cerr << "Erro na selação de livro." << endl;
		return;
	}

	if(livroAtual.getDisponiveis() < 1){
		cerr << "Livro selecionado não possui cópias disponíveis." << endl;
		return;
	}

	saida = time(0);
	estimada = saida + SEMANA;

	cout << endl << "=======================" << endl << endl;
	cout << "Usuário: " << usuarioAtual.getNome() << endl;
 	cout << "Empréstimos: " << usuarioAtual.getEmprestimos() << "/5" << endl;
	cout << "-----------------------" << endl;
	cout << "ID: " << livroAtual.getId() << endl;
	cout << "Titulo: " << livroAtual.getTitulo() << endl;
	cout << "Autor: " << livroAtual.getAutor() << endl;
	cout << "Gênero: " << livroAtual.getGenero() << endl;
	cout << "Subgênero: " << livroAtual.getSubgenero() << endl;
	cout << "Páginas: " << livroAtual.getPaginas() << endl;
	cout << "Editora: " << livroAtual.getEditora() << endl;
	cout << "Cópias: " << livroAtual.getCopias() << endl;
	cout << "Disponíveis: " << livroAtual.getDisponiveis() << endl;
	cout << "Reservadas: " << livroAtual.getReservados() << endl;
	cout << "-----------------------" << endl;
	cout << "Data de saída: " << ctime(&saida);
	cout << "Data prevista: " << ctime(&estimada);
	cout << endl << "Confirmar empréstimo do livro selecionado? [Y/N]" << endl;
	cin >> buffer;

	if(buffer == "y" || buffer == "Y"){
		if(!confirmarEmprestimo()){
			cerr << "Impossível completar a operação.";
			return;
		}
		usuarioAtual.addEmprestimo(); // Adiciona 1 no contador de empréstimos do usuário.
		livroAtual.atualizar(livroAtual.getTitulo(), 0);
	}
	return;
};

int Emprestimo::confirmarEmprestimo(){
	ofstream f;
	string buffer;

	f.open(EMPRESTIMO, ios_base::app);
	if(!f.is_open()){
		cerr << "Erro ao abrir arquivo " << EMPRESTIMO << endl;
		return 0;
	}

	f << usuarioAtual.getNome() << ";";
	f << livroAtual.getTitulo() << ";";
	f << saida << ";";
	f << estimada << "\n";
	f.close();

	return 1;
};

void Emprestimo::consultarEmprestimos(Usuario u){
	string::size_type i;
	string buffer;
	string nome;
	ifstream f;
	vector<string> livro;
	vector<vector<string>> livros;
	vector<string>::iterator it;

	usuarioAtual = u;

	f.open(EMPRESTIMO, ios_base::in);
	if(!f.is_open()){
		cerr << "Erro ao abrir arquivo " << EMPRESTIMO << endl;
		exit(EXIT_FAILURE);
	}

	nome = usuarioAtual.getNome();

	getline(f,buffer,'\n'); // Ignora cabeçalho

	while(getline(f,buffer,';')){
		if(buffer == nome){
			getline(f,buffer,';'); livro.push_back(buffer); // Livro
			getline(f,buffer,';'); livro.push_back(buffer); // Data de Saída
			getline(f,buffer,'\n'); livro.push_back(buffer); // Data estimada
			livros.push_back(livro);
		}
		else getline(f,buffer,'\n');
	}

	if (livros.size() > 0){
			cout << "==========================" << endl << endl;
			cout << "Livros emprestados: " << livros.size() << endl << endl;
			cout << "--------------------------" << endl;
			for(i = 0; i < livros.size(); i++){
					cout << "Título: " << livros[i][0] << endl;
					cout << "Status: ";
					if(stoi(livros[i][2])-stoi(livros[i][1]) > 0){
						cout << "Em dia."   << endl;}
					else{
						cout << "Atrasado." << endl;}
					cout << "Data de saída: " << livros[i][1] << endl;
					cout << "Data prevista: " << livros[i][2] << endl;
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
	return;
};

void Emprestimo::devolucao(Usuario u){
	string::size_type i;
	fstream fin;
	string buffer;
	string nome;
	vector<string> livros;
	int selection;

	usuarioAtual = u;
	nome = usuarioAtual.getNome();

	fin.open(EMPRESTIMO, ios::in);
	if(!fin.is_open()){
		cerr << "Erro ao abrir arquivo " << EMPRESTIMO << endl;
		exit(EXIT_FAILURE);
	}

	getline(fin, buffer, '\n');

	while(getline(fin, buffer,';')){
		if(buffer == nome){
			getline(fin,buffer,';');
			livros.push_back(buffer);
			getline(fin, buffer, '\n');
		}
		else getline(fin, buffer, '\n');
	}

	fin.close();

	if (livros.size() > 0){
		while(selection > livros.size()+1 || selection < 0){
			cout << "Livros: " << livros.size() << endl;
			cout << "--------------------------" << endl;
			for(i = 0; i < livros.size(); i++){
				cout << i+1 << " - " << livros[i];
			}
			cout << endl << endl;
			cout << "Livro a devolver [0 para cancelar]" << endl;
			cout << ">> ";
			cin.clear(); cin >> selection;
			if(selection == 0){return;}
		}
		buffer = livros[selection-1];
		if(!confirmaDevolucao(buffer)){
			cerr << "Não foi possível completar operação." << endl;
			return;
		}
		usuarioAtual.subEmprestimo();
		livroAtual.atualizar(buffer, 1);
	} else cout << "Nenhum livro foi encontrado." << endl;
	return;

};

int Emprestimo::confirmaDevolucao(string s){
	fstream fin, fout;
	string nome;
	string titulo;

	fin.open(EMPRESTIMO, ios::in);
	if(!fin.is_open()){
		cerr << "Erro ao abrir arquivo " << EMPRESTIMO << endl;
		exit(EXIT_FAILURE);
	}

	fout.open("temp.csv", ios::out);
	if(!fout.is_open()){
		cerr << "Erro ao abrir arquivo " << "temp.csv" << endl;
		exit(EXIT_FAILURE);
	}

	while(getline(fin,nome,';')){
		getline(fin,titulo,';');
		if(nome != usuarioAtual.getNome() || titulo != s){
			fout << nome << ';';
			fout << titulo << ';';
			getline(fin,nome,';');
			getline(fin,titulo,'\n');
			fout << nome << ';';
			fout << titulo << '\n';
		}
		else getline(fin,nome,'\n');
	}

	fout.close();
	fin.close();

	remove(EMPRESTIMO);
	rename("temp.csv", EMPRESTIMO);

	return 1;
}
