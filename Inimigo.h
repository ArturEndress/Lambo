#include<iostream>
#include"libUnicornio.h"
#include "Personagem.h"
#pragma once

/*INIMIGOS
Sempre que encontrar um inimigo, o jogador deve combater. 

Todos os inimigos têm os mesmos atributos do jogador. 

Todo monstro no mínimo os seguintes atributos: 
nome, poder de defesa e pontos vitais. 

Possivelmente outras informações deverão ser armazenadas 
considerando a representação visual do monstro.
*/

enum idInim { morcego, grue, aranha};
enum dirInim {Left, Right, Up, Down};


class Inimigo
	{
	protected:
		Sprite sprIni;

		Uint64 tick, tKnB;
	
		int qtdIni, pDefesa, pVitais, pAtaque, dir, dirKnb;
		float x, y;
		bool vivo, podeAndar[4], podeMachucar, knb;

	public:
		Inimigo();
		~Inimigo();

		void inicializar(string nome, string path, int nAnim, int nFrames, int pVid, int pDef);
		void desenhar();
				
		bool getPodeAndar() { return podeAndar; };
		void setPodeAndar(int dir, bool podeAndar) { this->podeAndar[dir] = podeAndar; };
		void setDir(int dir) { this->dir = dir; };
		int getDir() { return dir; };
		
		// * Vida *
		inline int getVidas() { return pVitais; };
		bool getVivo() { return vivo; };
		void setMorto() { vivo = false; };
		
		void atualizarVidas(int pVitais);
		void setPodeMachucar();
		bool getPodeMachucar() { return podeMachucar; };
		void atualizarTick(Uint64 tick) { this->tick = tick; };

		// * Ataque e Defesa *
		int getPAtaque() { return pAtaque; };
		void setpAtaque(int pAtaque) { this->pAtaque = pAtaque; };
		int getPDefesa() { return pDefesa; };
		void setPDefesa(int pDefesa) { this->pDefesa = pDefesa; };
		
		// Posição
		void parado();
		void andarEsq();
		void andarDir();
		void andarCima();
		void andarBaixo();
		float getX() { return x; };
		float getY() { return y; };
		void setX(float x) { this->x = x; };
		void setY(float y) { this->y = y; };
		void knockBack();
		void setKnockBack();
		void setDirKnockBack(int dirKnb) { this->dirKnb = dirKnb; };
		void ativouKnockBack(bool knb) { this->dirKnb = knb; };

		// Sprite
		Sprite getSprite() { return sprIni; };
	};

