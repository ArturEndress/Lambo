#pragma once

#include "libUnicornio.h"
#include "P1.h"
#include "P2.h"
#include "P3.h"
#include "Inimigo.h"
#include "Inventario.h"

struct Bau
{
	Sprite sprBau;
	float xBau = 0, yBau = 0;
	bool abriu = false;
};

struct Gold
{

	Sprite sprGold;
	int xGold = 0, yGold = 0;
	bool goldDisponivel = true;
};

class Sala
{


public:
	Sala();
	~Sala();

	void inicializar();
	void atualizar();

	// Personagem
	void setPersonagem(int per) { this->per = per; };
	void movimentarPlayer();
	void movimentarInimigo();
	// Inventário
	void desenharInventario();
	// Colisão
	void testarColisao();
	// Gold
	
	void carregarItens();
	void carregarInim();
	void carregarSala(int s);
	void utilizarItens();
	
protected:

	Uint64 ticks, ticksPodeMachucar;
	// Sala
	Sprite *tiles = 0;
	int nColunas = 0, nLinhas = 0, **mapaSala, **mapaObjetos, salaAtual = 1;
	
	// Personagens
	Personagem *personagem;
	Inimigo *inimigos;
	string *nomeInim, *iniPath, *sprInim;
	int posX, posY, per, sorteioInim, linhaInim, colunaInim, *dirInim, *posXinim, *posYinim, inimCarreg, nInimigos, *inimHp, *inimDef;
	bool carregouDir;
	Texto qtdVidas, qtdMoedas;
	void escreverInfos();

	// Inventário
	Inventario inventario;
	string *nomeItens, *itensPath;
	Item *item;
	int sorteioItens, linhaItem, colunaItem, itensCarreg, *tipoItem, nItens;
	bool exibirInventario;
	Sprite canvasI;
	Texto txt;

	// Gold
	Gold *coin;
	int nCoin;
	

	// Baú
	Bau *bau;
	int nBau;
	
	
};

