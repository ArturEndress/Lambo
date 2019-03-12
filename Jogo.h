#pragma once
#include "libUnicornio.h"
#include "Sala.h"
#include "P1.h"
#include "P2.h"
#include "P3.h"
#include <fstream>

enum Tela {tJogo, tSelecaoChar, tInicial};

class Jogo
{
private:
	Personagem **personagens;
	Sala sala;
	Tela telaAtual;

	// Menu
	BotaoSprite bNovo, bContinuar, bVoltar, bSair;

public:
	Jogo();
	~Jogo();

	void inicializar();
	void finalizar();

	void executar();


	void carregarBotoes();
	void telaInicial();
	void telaJogo();
	void telaSelecaoChar();
};

