#include "Jogo.h"

Jogo::Jogo()
{
}

Jogo::~Jogo()
{
}

void Jogo::inicializar()
{
	uniInicializar(1024, 768, false);

	carregarBotoes();

	telaAtual = tInicial;

	personagens = new Personagem*[3];
	personagens[0] = new P1;
	personagens[1] = new P2;
	personagens[2] = new P3;

	for (int i = 0; i < 3; i++)
		personagens[i]->inicializar();		
}

void Jogo::finalizar()
{
	uniFinalizar();
}

void Jogo::executar()
{
	while (!gTeclado.soltou[TECLA_ESC] && !gEventos.sair)
	{
		uniIniciarFrame();

		//		MENU		//
		switch (telaAtual)
		{
		case tInicial: telaInicial();
			break;
		case tSelecaoChar: telaSelecaoChar();
			break;
		case tJogo: telaJogo();
			break;
		}

		uniTerminarFrame();
	}
}

void Jogo::carregarBotoes()
{
	// Novo
	//if (!gRecursos.carregouSpriteSheet("bNovo"))	
	gRecursos.carregarSpriteSheet("bNovo", "sprites/menu/novo.png", 3, 1);
	bNovo.setSpriteSheet("bNovo");


	// Continuar
	//if (!gRecursos.carregouSpriteSheet("bContinuar"))
	gRecursos.carregarSpriteSheet("bContinuar", "sprites/menu/cont.png", 3, 1);

	bContinuar.setSpriteSheet("bContinuar");


	// Sair
	if (!gRecursos.carregouSpriteSheet("bSair"))
		gRecursos.carregarSpriteSheet("bSair", "sprites/menu/sair.png", 3, 1);
	bSair.setSpriteSheet("bSair");


	// Voltar
	if (!gRecursos.carregouSpriteSheet("bVoltar"))
		gRecursos.carregarSpriteSheet("bVoltar", "sprites/menu/volta.png", 3, 1);
	bVoltar.setSpriteSheet("bVoltar");

}

void Jogo::telaInicial()
{
	// Botoes

	bNovo.setPos(gJanela.getLargura() / 2, 300);
	bNovo.desenhar();
	bNovo.atualizar();

	bContinuar.setPos(gJanela.getLargura() / 2, gJanela.getAltura() / 2);
	bContinuar.desenhar();
	bContinuar.atualizar();

	bSair.setPos(gJanela.getLargura() / 2, 468);
	bSair.desenhar();
	bSair.atualizar();

	//////////////////

	if (bNovo.estaClicado())
		telaAtual = tSelecaoChar;

	else if (bSair.estaClicado())
		gEventos.sair = true;

}

void Jogo::telaJogo()
{
	// * Sala *
	sala.atualizar();


	/* TESTE SAVE

	if (gTeclado.pressionou[TECLA_1])
	{
		// abrir arq e salvar

		ofstream arqSaida;


		arqSaida.open("save.txt", ios::binary);
		if (!arqSaida.is_open())
		{
			cout << "Erro " << endl;
		}
		else
		{
			arqSaida.write(reinterpret_cast<const char*>(&sala), sizeof(sala));
		}
		arqSaida.close();
	}
	if (gTeclado.pressionou[TECLA_2])
	{
		ifstream arqEntrada;


		arqEntrada.open("save.txt", ios::binary);
		if (arqEntrada.is_open())
		{
			arqEntrada.read(reinterpret_cast<char *>(&sala), sizeof(Sala));


			//LOAD 


		}
		arqEntrada.close();

	}
	*/
}

void Jogo::telaSelecaoChar()
{
	for (int p = 0; p < 3; p++)
	{
		personagens[p]->parado();
		personagens[p]->desenhar();
	}
	
	// Escolher 
	for (int p = 0; p < 3; p++)
		if (uniTestarColisaoPontoComSprite(gMouse.x, gMouse.y, personagens[p]->getSprite(), personagens[p]->getX(), personagens[p]->getY(), 0))
			if (gMouse.pressionou[BOTAO_MOUSE_ESQ])
			{
				sala.setPersonagem(p+1);
				telaAtual = tJogo;
				sala.inicializar();
			}
}
