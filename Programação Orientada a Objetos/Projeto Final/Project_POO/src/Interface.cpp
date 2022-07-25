#include <iostream>
#include <stdlib.h>

#include "Interface.h"

Interface::Interface(){ status = 0; }
Interface::~Interface(){}

void Interface::acesso(void){
	int selection;

	cout << "==========================================" << endl;
	cout << endl;
	cout << "Bem vindo ao sistema de empréstimo online." << endl;
	cout << "Pressione enter para continuar" 			 << endl;
	cout << endl;
	cout << "==========================================" << endl;
	cin.ignore();

	while(1){
		while(status != 1){
			selection = 0;
			while(selection > 3 || selection < 1){
				clrscr();
				cout << "============" << endl;
				cout << "Biblioca 1.0" << endl;
				cout << "============" << endl;
				cout << endl;
				cout << "1. Fazer Login." << endl;
				cout << "2. Registrar nova conta." << endl;
				cout << "3. Sair." << endl;
				cout << endl;

				cout << ">> " << flush;
				cin.clear();
				cin >> selection;
			}

			switch (selection){
				case 1:
					clrscr();
					status = usuarioAtual.logar();
					break;

				case 2:
					clrscr();
					usuarioAtual.registrar();
					break;

				case 3:
					clrscr();
					cout << "=============" << endl;
					cout << "Volte sempre!" << endl;
					cout << "=============" << endl;
					exit(0);
					break;

				default:
					cerr << "Erro na leitura de input." << endl;
					exit(-1);
			}

		}
		menu();
	}
}

void Interface::menu(void)
{
	while(status == 1){
		int selection;
		selection = 0;

		while(selection > 9 || selection < 1){
			clrscr();
			cout << "=============================" << endl;
			cout << "Usuario: " << usuarioAtual.getNome();
			if(usuarioAtual.getPermissao()==1){ cout << " [admin]" << endl;}
			else 							   cout << endl;
			cout << "=============================" << endl;
			cout << endl;

			cout << "Opções:" << endl;
			cout << "1. Mostrar todos os livros." << endl;
			cout << "2. Menu de Emprestimos." << endl;
			cout << "3. Pesquisar por nome." << endl;
			cout << "4. Pesquisar por autor." << endl;
			cout << "5. Pesquisar por ID" << endl;
			cout << "6. Dados do usuário" << endl;
			cout << "7. Deslogar." << endl;
			cout << endl;

			if(usuarioAtual.getPermissao()==1){
				cout << "Opções de administrador:" << endl;
				cout << "8. Adicionar Livro." << endl;
				cout << "9. Devolução de Livro." << endl;
				cout << endl;
			}

			cout << ">> " << flush;
			cin.clear();
			cin >> selection;
			cin.ignore();
		}

		switch(selection){
		case 1:
			clrscr();
			livroSelecionado.listar();
			break;

		case 2:
			clrscr();
			menuEmprestimo();
			break;

		case 3:
			clrscr();
			livroSelecionado.pesquisarNome();
			break;

		case 4:
			clrscr();
			livroSelecionado.pesquisarAutor();
			break;

		case 5:
			clrscr();
			livroSelecionado.pesquisarId();
			break;

		case 6:
			clrscr();
			usuarioAtual.mostrarDados();
			break;

		case 7:
			clrscr();
			usuarioAtual.deslogar();
			status = 0;
			break;

		case 8:
			if(usuarioAtual.getPermissao()==1){
				clrscr();
				livroSelecionado.adicionar();
			}
			break;

		case 9:
			if(usuarioAtual.getPermissao()==1){
				clrscr();
			}
			break;

		default:
			cerr << "Erro na leitura de input." << endl;
			exit(-1);
		}
	}
};

void Interface::menuEmprestimo(void)
{
	int selection;
	while(selection > 4 || selection < 1){
		clrscr();
		cout << "===================" << endl;
		cout << "Menu de Emprestimos" << endl;
		cout << "===================" << endl;
		cout << endl;

		cout << "1. Consultar Emprestimos." << endl;
		cout << "2. Fazer Emprestimos." << endl;
		cout << "3. Devolução." <<endl;
		cout << "4. Voltar para Menu Geral." << endl;
		cout << endl;

		cout << ">> " << flush;
		cin.clear();
		cin >> selection;
		cin.ignore();

		switch(selection){
		case 1:
			clrscr();
			emprestimoAtual.consultarEmprestimos(usuarioAtual);
			break;

		case 2:
			clrscr();
			emprestimoAtual.fazerEmprestimo(usuarioAtual, livroSelecionado);
			break;

		case 3:
			clrscr();
			emprestimoAtual.devolucao(usuarioAtual);

		case 4:
			return;
			break;

		default:
			cerr << "Erro na leitura de Input." << endl;
			break;
		}
	}
};

void clrscr(void){
	cout << string(100, '\n');
}
