/*Todo personagem possui cinco atributos:
1. Nome
Os personagens podem mover, atacar e dar um especial.
Além de usar itens no inventário.*/

#include"libUnicornio.h"
#include "Efeito.h"
#include <ctime>
#pragma once
using namespace std;

#define qtdPer 3 
enum idPer { Personagem1, Personagem2, Personagem3 };
enum dir { esq, dir, cima, baixo };
enum Pos {pcima, pesq, pbaixo, pdir};

class Personagem
{
protected:
	//* Atributos *
	Efeito *efeito;
	string nome;
	int idPersonagem, pos;
	int pAtaque, pDefesa, pVitais, moedas;
	float x = 400, y = 400;
	bool vivo, podeAndar[4], podeMachucar;

public:
	Personagem();
	~Personagem();

	//**** Métodos ****
	// Gets e Sets
	inline int getId() { return idPersonagem; };
	bool getPodeMachucar() { return podeMachucar; };
	void setPodeMachucar(bool podeMachucar) { this->podeMachucar = podeMachucar; };
	Sprite getSpriteEfeito(int i) { return efeito[i].getSprite(); };
	float getEfeitoX(int i) { return efeito[i].getX(); };
	float getEfeitoY(int i) { return efeito[i].getY(); };
	bool getEfeitoAtivo(int i) { return efeito[i].getAtivo(); };
	void setEfeitoAtivo(int i, bool ativo) { efeito[i].setAtivo(ativo); };


	// * Vida *
	inline int getVidas() { return pVitais; };
	bool getVivo() { return vivo; };
	//void setMorto() { if (pVitais <= 0) vivo = false; };
	void atualizarVidas(int pVitais);
	
	// * Ataque e Defesa *
	int getPAtaque() { return pAtaque; };
	void setpAtaque(int pAtaque) { this->pAtaque = pAtaque; };
	int getPDefesa() { return pDefesa; };
	void setPDefesa(int pDefesa) { this->pDefesa = pDefesa; };


	// * Moedas *
	int getMoedas() { return moedas; };
	void setMoedas() { moedas++; };

	// * Posição *
	float getX() { return x; };
	void setX(float newX) { x = newX; };
	float getY() { return y; };
	void setY(float newY) { y = newY; };
	void setPodeAndar(int dir, bool andar) { podeAndar[dir] = andar; };
	bool getPodeAndar(int dir) { return podeAndar[dir]; };
	int getPos() { return pos; };


	// Abstratos
	void andar();

	// Virtuais

	virtual void inicializar() = 0; // carrega e seta sprites
	virtual void desenhar() = 0;

	virtual void parado() = 0;
	virtual void andarEsq() = 0;
	virtual void andarDir() = 0;
	virtual void andarCima() = 0;
	virtual void andarBaixo() = 0;
	virtual void setMorto() = 0;
	virtual void atacar() = 0;

	virtual Sprite getSprite() = 0;


};

