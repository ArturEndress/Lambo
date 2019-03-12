#pragma once
#include "Item.h"
#define maxItens 10
/*INVENT�RIO
FAZER -> O invent�rio dever� conter no m�ximo 10 itens. [10 tipos]
FAZER -> O jogador poder� gerenciar este invent�rio � jogar item fora e usar o item. 
FAZER -> Quando um item � usado aplica-se o efeito sob o personagem. 
*/

const string nomes_pocoes[3] = { "potHP", "potMP", "veneno" };

struct NodoItem
{
	int ID;
	int qtd;
	Item item;
	NodoItem *ant, *prox;

}; class Inventario

{
public:
	Inventario();
	~Inventario();

	void add(int tipo);
	void remover(int tipo);
	
	NodoItem *getIni() { return ini; }
	NodoItem *getFim() { return fim; }

	bool estaVazio();
	NodoItem* getNodo(int tipo);

protected:
	NodoItem * ini, *fim;

};

