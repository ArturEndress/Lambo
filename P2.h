#pragma once
#include "Personagem.h"
class P2 :
	public Personagem
{
protected:
	Sprite spriteP2;
	Uint64 cooldown;
	bool podeAtacar;

public:
	P2();
	~P2();

	void inicializar();
	void desenhar();

	void parado();
	void andarEsq();
	void andarDir();
	void andarCima();
	void andarBaixo();
	void setMorto();

	void atacar();

	Sprite getSprite() { return spriteP2; };
};

