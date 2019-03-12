#pragma once
#include "Item.h"
#define maxItens 10
/*INVENTÁRIO
FAZER -> O inventário deverá conter no máximo 10 itens. [10 tipos]
FAZER -> O jogador poderá gerenciar este inventário – jogar item fora e usar o item. 
FAZER -> Quando um item é usado aplica-se o efeito sob o personagem. 
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

