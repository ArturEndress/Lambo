#pragma once
#include "libUnicornio.h"

#define MAXCHAR 30




class Item
{
public:
	Item();
	~Item();

	void inicializar(string nome, string path, int nAnim, int nFrames);
	void desenhar();
	void setX(float x) { this->x = x; };
	void setY(float y) { this->y = y; };
	float getX() { return x; };
	float getY() { return y; };
	bool getPegou() { return pegou; };
	void setPegou() { pegou = true; };
	Sprite getSprite() { return item; };
	void setTipo(int tipo) { this->tipo = tipo; };
	int getTipo() { return tipo; };

private:

	Sprite item;
	char nome[MAXCHAR];
	bool pegou;
	int qtd, tipo;
	float x, y;
};

