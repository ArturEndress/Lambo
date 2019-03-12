#pragma once
#include "Personagem.h"
class P1 :
	public Personagem
{
protected:
	Sprite spriteP1;
	Uint64 tick;

public:
	P1();
	~P1();

	void inicializar();
	void desenhar();

	void parado();
	void andarEsq();
	void andarDir();
	void andarCima();
	void andarBaixo();
	void setMorto();

	void atacar();

	Sprite getSprite() { return spriteP1; };
};

