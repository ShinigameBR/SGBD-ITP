Esse programa é um projeto para a disciplina de ITP (Introdução as técnicas de programação), trata-se de um Sistema de Gerenciamento de Banco de Dados (SGBD) simplificado, feito na linguagem C.
A seguir a documentação exigida.

Funcionalidades solicitas que foram implementas:
	- Criar tabela
	- Listar tabelas
	- Criar nova linha na tabela
	- Listar todos os dados de uma tabela
	- Apagar tupla de uma tabela
	- Apagar tabela
Funcionalidades solicitadas que não foram implementadas:
	- Pesquisar valor em uma tabela

Oque faria de forma diferente:
	- Implementar as funcionalidades que faltaram
	- Deixar mais organizado desde início
	- Determinar o funcionamento do código desde início (planejar como vai funcionar)

Como compilar e rodar o projeto:
	No windows:
		> Em um terminal, com o MinGW instalado na máquina, estando dentro da pasta "CODIGO" (caminho: */SGBD-ITP/CODIGO), executar o comando: 'gcc -o Main main.c file.c funcs.c table.c definitions.h -g -w' para compilar. Em seguida executar o comando '.\Main.exe' para rodar o programa.
	No Linux:
		> No terminal, estando dentro do diretorio ../SGBD-ITP/CODIGO, executar o comando 'gcc -o Main main.c table.c file.c funcs.c definitions.h -w' para compilar. Em seguida executar o comando './Main' para rodar o programa.

Autores:
	~ Expedito Hebert Firmino da Rocha
		-> Implementou as funcionalidades de criar nova linha, apagar tupla e apagar tabela.
	~ Pedro Lucas de Souza Bezerra
		-> Implementou as funcionalidades de listar tabelas e mostrar todos os dados de uma tabela.
	* A funcionalidade de criar tabela foi implementada coletivamente.