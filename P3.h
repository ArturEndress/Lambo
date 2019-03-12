#pragma once
#include "Personagem.h"

#define MAX_FLECHAS 10
class P3 :
	public Personagem
{
protected:
	Sprite spriteP3;
	bool podeAtirar;
	Uint64 tempo;

public:
	P3();
	~P3();

	void inicializar();
	void desenhar();

	void parado();
	void andarEsq();
	void andarDir();
	void andarCima();
	void andarBaixo();
	void setMorto();

	void atacar();

	Sprite getSprite() { return spriteP3; };
};

