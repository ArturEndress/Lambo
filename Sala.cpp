#include "Sala.h"

Sala::Sala()
{
}

Sala::~Sala()
{
}

void Sala::inicializar()
{
	gTempo.inicializar();
	ticks = ticksPodeMachucar = gTempo.getTicks();

	// * Sala *
	carregarSala(salaAtual);

	
	

	// * Textos *
	// Infos Personagem
	gRecursos.carregarFonte("calibrib", "calibrib.ttf", 20);
	qtdVidas.setFonte("calibrib");
	qtdMoedas.setFonte("calibrib");
	// Inventário
	gRecursos.carregarFonte("fonte1", "fonte_padrao.ttf", 18);
	txt.setFonte("fonte1");
	txt.setCor(0, 0, 0);

	// * Personagem *	
	switch (per)
	{
	case 1:	personagem = new P1;
		break;
	case 2:	personagem = new P2;
		break;
	case 3: personagem = new P3;
	default:
		break;
	}
	personagem->inicializar();

	for (int l = 0; l < nLinhas; l++)
	{
		for (int c = 0; c < nColunas; c++)
		{
			if (mapaSala[c][l] == 31)
			{
				personagem->setX(tiles[0].getLargura() / 2 + tiles[0].getLargura() * c);
				personagem->setY(tiles[0].getAltura() / 2 + tiles[0].getAltura() * l);
				break;
			}
		}
	}
	


	carregarInim();

	inimigos = new Inimigo[nInimigos];
	posXinim = new int[nInimigos];
	posYinim = new int[nInimigos];

	dirInim = new int[nInimigos];

	carregouDir = false;

	for (int i = 0; i < nInimigos; i++)
	{
		sorteioInim = rand() % inimCarreg;
		inimigos[i].inicializar(sprInim[sorteioInim], iniPath[sorteioInim], 4, 8, inimHp[sorteioInim], inimDef[sorteioInim]);
	}

	for (int i = 0; i < nInimigos; i++)
	{
		do
		{
			linhaInim = rand() % 24;
			colunaInim = rand() % 32;


			inimigos[i].setX(tiles[0].getLargura() / 2 + tiles[0].getLargura() * colunaInim);
			inimigos[i].setY(tiles[0].getAltura() / 2 + tiles[0].getAltura() * linhaInim);


		} while (mapaObjetos[colunaInim][linhaInim] != -1);
	}
	//}


	// * Tesouro *
	nBau = rand() % 2 + 1;
	bau = new Bau[nBau];

	if (!gRecursos.carregouSpriteSheet("bau"))
	{
		gRecursos.carregarSpriteSheet("bau", "sprites/chest.png", 1, 2); // depois inverter a imagem pra funcionar animação
	}
	for (int i = 0; i < nBau; i++)
	{
		bau[i].sprBau.setSpriteSheet("bau");
	}

	for (int i = 0; i < nBau; i++)
	{
		do
		{
			linhaInim = rand() % 24;
			colunaInim = rand() % 32;

			
			bau[i].xBau = tiles[0].getLargura() / 2 + tiles[0].getLargura() * colunaInim;
			bau[i].yBau = tiles[0].getAltura() / 2 + tiles[0].getAltura() * linhaInim;


		} while (mapaObjetos[colunaInim][linhaInim] != -1);
	}

	// * Gold *
	nCoin = rand() % 3 + 1;
	
	coin = new Gold[nCoin];

		if (!gRecursos.carregouSpriteSheet("gold"))
			gRecursos.carregarSpriteSheet("gold", "sprites/gold.png", 1, 8);
		
		for (int i = 0; i < nCoin; i++)
		{
			coin[i].sprGold.setSpriteSheet("gold");
			coin[i].sprGold.setVelocidadeAnimacao(7);
		}
		
		for (int i = 0; i < nCoin; i++)
		{
			do
			{
				linhaInim = rand() % 24;
				colunaInim = rand() % 32;


				coin[i].xGold = tiles[0].getLargura() / 2 + tiles[0].getLargura() * colunaInim;
				coin[i].yGold = tiles[0].getAltura() / 2 + tiles[0].getAltura() * linhaInim;


			} while (mapaObjetos[colunaInim][linhaInim] != -1);
		}


	// * Inventário *
	gRecursos.carregarSpriteSheet("canvasInventario", "sprites/fundoInv.png");
	exibirInventario = false;
	canvasI.setSpriteSheet("canvasInventario");

	carregarItens();

	item = new Item[nItens];

	for (int i = 0; i < nItens; i++)
	{
		sorteioItens = rand() % itensCarreg;
		item[i].inicializar(nomeItens[sorteioItens], itensPath[sorteioItens], 1, 1);
		item[i].setTipo(sorteioItens);
	}

	for (int i = 0; i < nItens; i++)
	{
		do
		{
			linhaItem = rand() % 24;
			colunaItem = rand() % 32;

			item[i].setX(tiles[0].getLargura() / 2 + tiles[0].getLargura() * colunaItem);
			item[i].setY(tiles[0].getAltura() / 2 + tiles[0].getAltura() * linhaItem);

		} while (mapaObjetos[colunaItem][linhaItem] != -1);

	}
}

void Sala::atualizar()
{
	utilizarItens();

	// * Sala *
	tiles[31].avancarAnimacao();
	for (int l = 0; l < nLinhas; l++)
		for (int c = 0; c < nColunas; c++)
			tiles[mapaSala[c][l]].desenhar(tiles[0].getLargura() / 2 + tiles[0].getLargura() * c, tiles[0].getAltura() / 2 + tiles[0].getAltura() * l);

		for (int l = 0; l < nLinhas; l++)
			for (int c = 0; c < nColunas; c++)
				if (mapaObjetos[c][l] >= 0)
					tiles[mapaObjetos[c][l]].desenhar(tiles[0].getLargura() / 2 + tiles[0].getLargura() * c, tiles[0].getAltura() / 2 + tiles[0].getAltura() * l);

	// * Tesouro *
		for (int i = 0; i < nBau; i++)
		{
			bau[i].sprBau.desenhar(bau[i].xBau, bau[i].yBau);
		}

	// * Gold *	
		for (int i = 0; i < nCoin; i++)
		{
			if (coin[i].goldDisponivel) {
				coin[i].sprGold.desenhar(coin[i].xGold, coin[i].yGold);
				coin[i].sprGold.avancarAnimacao();
			}
		}
	
	
	// * Desenhar Itens *
	for (int i = 0; i < nItens; i++)
	{
		item[i].desenhar();
	}
	
	// * Inimigo *
	
	for (int i = 0; i < nInimigos; i++)
	{
		posXinim[i] = inimigos[i].getX() / tiles[0].getLargura();
		posYinim[i] = inimigos[i].getY() / tiles[0].getAltura();

	}
	
	movimentarInimigo();


	for (int i = 0; i < nInimigos; i++)
	{
		if (inimigos[i].getVivo())
		{
			if (inimigos[i].getPodeMachucar())
			{
				inimigos[i].desenhar();
			}
			else
			{
				int random = rand() % 2;
				if (random)
				{
					inimigos[i].desenhar();
				}
			}
		}
	}


	// * Personagem *
	if (personagem->getVivo()) {
		posX = personagem->getX() / tiles[0].getLargura();
		posY = personagem->getY() / tiles[0].getAltura();
		if (personagem->getPodeMachucar())
		{
			personagem->desenhar();
		}
		else
		{
			int random = rand() % 2;

			if (random)
			{
				personagem->desenhar();
			}
		}
		movimentarPlayer();

		personagem->atacar();
	}



	// * Inventário *
	
	if (exibirInventario)
		desenharInventario();
	if (gTeclado.pressionou[TECLA_I])
		exibirInventario = !exibirInventario;

	

	// * Textos *
	escreverInfos();

	// * Colisão *
	testarColisao();
}

void Sala::movimentarPlayer()
{	
		// condições de movimentação
		if (mapaObjetos[posX + 1][posY] < 0)
			personagem->setPodeAndar(dir, true);
		else
			personagem->setPodeAndar(dir, false);
		if (mapaObjetos[posX - 1][posY] < 0)
			personagem->setPodeAndar(esq, true);
		else
			personagem->setPodeAndar(esq, false);
		if (mapaObjetos[posX][posY + 1] < 0)
			personagem->setPodeAndar(baixo, true);
		else
			personagem->setPodeAndar(baixo, false);
		if (mapaObjetos[posX][posY - 1] < 0)
			personagem->setPodeAndar(cima, true);
		else
			personagem->setPodeAndar(cima, false);
		personagem->andar();
	
}


void Sala::movimentarInimigo()
{
	

	if (!carregouDir)
	{
		for (int i = 0; i < nInimigos; i++)
		{
			dirInim[i] = rand() % 4;
			inimigos[i].setDir(dirInim[i]);
		}
		carregouDir = true;
	}
	for (int i = 0; i < nInimigos; i++)
	{
		if (inimigos[i].getVivo())
		{
			int random = rand() % 2 + 2;

			if (gTempo.getTempoAteTickAtual(ticks) > random)
			{
				dirInim[i] = rand() % 4;

				inimigos[i].setDir(dirInim[i]);

				ticks = gTempo.getTicks();
			}
		}
	}


	for (int i = 0; i < nInimigos; i++)
	{
		/*	if (inimigos[i].getVivo())
		{

			if (!mapaObjetos[posXinim[i] - 1][posYinim[i]] < 0)
			{
				if (!mapaObjetos[posXinim[i] + 1][posYinim[i]] < 0)
				{
					if (!mapaObjetos[posXinim[i]][posYinim[i] - 1] < 0)
					{
						if (!mapaObjetos[posXinim[i] + 1][posYinim[i] - 1] < 0)
						{
							inimigos[i].setMorto();
						}
					}
				}
			}
			inimigos[i].knockBack();
		}
*/
		if (inimigos[i].getVivo())
		{

			switch (inimigos[i].getDir())
			{
			case Left:
				if (mapaObjetos[posXinim[i] - 1][posYinim[i]] < 0)
				{
					inimigos[i].andarEsq();
				}
				else
				{
					dirInim[i] = rand() % 4;
					inimigos[i].setDir(dirInim[i]);
				}

				break;
			case Right:
				if (mapaObjetos[posXinim[i] + 1][posYinim[i]] < 0)
				{
					inimigos[i].andarDir();
				}
				else
				{
					dirInim[i] = rand() % 4;
					inimigos[i].setDir(dirInim[i]);
				}
				break;
			case Up:
				if (mapaObjetos[posXinim[i]][posYinim[i] - 1] < 0)
				{
					inimigos[i].andarCima();
				}
				else
				{
					dirInim[i] = rand() % 4;
					inimigos[i].setDir(dirInim[i]);
				}
				break;
			case Down:
				if (mapaObjetos[posXinim[i]][posYinim[i] + 1] < 0)
				{
					inimigos[i].andarBaixo();
				}
				else
				{
					dirInim[i] = rand() % 4;
					inimigos[i].setDir(dirInim[i]);
				}
				break;
			default:
				inimigos[i].parado();
				break;
			}
		}
	}


}

void Sala::testarColisao()
{
	// Itens
	for (int i = 0; i < nItens; i++)
	{
		if (uniTestarColisaoSpriteComSprite(personagem->getSprite(), personagem->getX(), personagem->getY(), 0,
			item[i].getSprite(), item[i].getX(), item[i].getY(), 0, true))
		{
			if (!item[i].getPegou())
			{
				item[i].setPegou();

				inventario.add(item[i].getTipo());
			}

		}
	}

	// * Bau *

	for (int i = 0; i < nBau; i++)
	{
		if (uniTestarColisaoSpriteComSprite(personagem->getSprite(), personagem->getX(), personagem->getY(), 0,
			bau[i].sprBau, bau[i].xBau, bau[i].yBau, 0, true))
		{
			if (!bau[i].abriu)
			{
				bau[i].abriu = true;

				bau[i].sprBau.setFrame(1);

				int random = rand() % 100;

				if (random < 20)
				{
					int randItem = rand() % itensCarreg;

					inventario.add(randItem);
				}
				else
				{
					personagem->setMoedas();
				}
			}

		}
	}

	// Pegar moeda
	for (int i = 0; i < nCoin; i++)
	{
		if (coin[i].goldDisponivel)
			if (uniTestarColisaoSpriteComSprite(personagem->getSprite(), personagem->getX(), personagem->getY(), 0, 
				coin[i].sprGold, coin[i].xGold, coin[i].yGold, 0))
			{
				personagem->setMoedas();
				coin[i].goldDisponivel = false;
			}
	}

	// Colidir com Inimigos
	for (int i = 0; i < nInimigos; i++)
	{
		if (personagem->getVivo() && inimigos[i].getVivo())
			if (personagem->getPodeMachucar()) {
				if (uniTestarColisaoSpriteComSprite(personagem->getSprite(), personagem->getX(), personagem->getY(), 0,
					inimigos[i].getSprite(), inimigos[i].getX(), inimigos[i].getY(), 0, true))
				{
					if (inimigos[i].getPAtaque() - personagem->getPDefesa() > 0)
						personagem->atualizarVidas(-(inimigos[i].getPAtaque() - personagem->getPDefesa()));
					else
						personagem->atualizarVidas(-1);

					personagem->setPodeMachucar(false);
					ticksPodeMachucar = gTempo.getTicks();
				}
			}
		if (personagem->getVidas() < 0)
		{
			personagem->atualizarVidas(1);
		}
	}


	if (personagem->getId() == Personagem1)
	{
		for (int i = 0; i < nInimigos; i++)
		{
			if (inimigos[i].getVivo() && personagem->getVivo())
			{
				if (personagem->getEfeitoAtivo(0))
				{
					if (uniTestarColisaoSpriteComSprite(personagem->getSpriteEfeito(0), personagem->getEfeitoX(0), personagem->getEfeitoY(0), 0,
						inimigos[i].getSprite(), inimigos[i].getX(), inimigos[i].getY(), 0, true) && inimigos[i].getPodeMachucar())
					{
						switch (personagem->getPos())
						{
						case pcima: inimigos[i].setDirKnockBack(Up);
							break;
						case pbaixo: inimigos[i].setDirKnockBack(Down);
							break;
						case pesq: inimigos[i].setDirKnockBack(Left);
							break;
						case pdir: inimigos[i].setDirKnockBack(Right);
							break;
						default:
							break;
						}
						if (personagem->getPAtaque() - inimigos[i].getPDefesa() > 0)
							inimigos[i].atualizarVidas(-(personagem->getPAtaque() - inimigos[i].getPDefesa()));
						else
							inimigos[i].atualizarVidas(-1);
					
					inimigos[i].setPodeMachucar();
					inimigos[i].setKnockBack();
					}

				}
				
			}
		}
	}

	if (personagem->getId() == Personagem2)
	{
		for (int i = 0; i < nInimigos; i++)
		{
			if (inimigos[i].getVivo())
			{
				if (personagem->getEfeitoAtivo(0))
				{
					if (uniTestarColisaoSpriteComSprite(personagem->getSpriteEfeito(0), personagem->getEfeitoX(0), personagem->getEfeitoY(0), 0,
						inimigos[i].getSprite(), inimigos[i].getX(), inimigos[i].getY(), 0, true) && inimigos[i].getPodeMachucar())
					{
						if (personagem->getPAtaque() - inimigos[i].getPDefesa() > 0)
							inimigos[i].atualizarVidas(-(personagem->getPAtaque() - inimigos[i].getPDefesa()));
						else
							inimigos[i].atualizarVidas(-1);

						inimigos[i].setPodeMachucar();
					}

				}

			}
		}
	}

	if (personagem->getId() == Personagem3)
	{
		for (int i = 0; i < nInimigos; i++)
		{
			if (inimigos[i].getVivo())
			{
				for (int t = 0; t < MAX_FLECHAS; t++)
				{
					if (uniTestarColisaoSpriteComSprite(personagem->getSpriteEfeito(t), personagem->getEfeitoX(t), personagem->getEfeitoY(t), 0,
						inimigos[i].getSprite(), inimigos[i].getX(), inimigos[i].getY(), 0, true) && inimigos[i].getPodeMachucar())
					{
						if (personagem->getEfeitoAtivo(t))
						{

							if (personagem->getPAtaque() - inimigos[i].getPDefesa() > 0)
								inimigos[i].atualizarVidas(-(personagem->getPAtaque() - inimigos[i].getPDefesa()));
							else
								inimigos[i].atualizarVidas(-1);

							inimigos[i].setPodeMachucar();
							personagem->setEfeitoAtivo(t, false);
						}
					}

				}
			}
		}
	}
	
	

	if (gTempo.getTempoAteTickAtual(ticksPodeMachucar) > 1)
	{
		personagem->setPodeMachucar(true);
	}
}

void Sala::desenharInventario()
{
	canvasI.desenhar(200, 100);
	txt.setAlinhamento(TEXTO_CENTRALIZADO);
	txt.setString("Inventário");
	txt.desenhar(200, 50);
	NodoItem *aux = inventario.getIni();
	Sprite sprAux;
	float x = 70.0, y = 100.0;
	while (aux != NULL)
	{
		sprAux.setSpriteSheet(nomes_pocoes[aux->ID]);
		sprAux.desenhar(x, y);
		txt.setString(to_string(aux->qtd));
		txt.desenhar(x, y + 50);
		x += sprAux.getLargura();
		aux = aux->prox;
	}
}

void Sala::carregarSala(int s)
{
	string name, path, arqName;
	int nID, nAnim, nFrames, nTiles;
	ifstream arquivoSala;

	arqName = "salas/sala" + to_string(s) + ".txt";

	arquivoSala.open(arqName);
	if (arquivoSala.is_open())
	{		
		arquivoSala >> nInimigos;

		arquivoSala >> nItens;

		arquivoSala >> nTiles;
		
		tiles = new Sprite[nTiles];

		for (int t = 0; t < nTiles; t++)
		{
			arquivoSala >> nID >> name >> path >> nAnim >> nFrames;
			if (!gRecursos.carregouSpriteSheet(name))
				gRecursos.carregarSpriteSheet(name, path, nAnim, nFrames);
			tiles[nID].setSpriteSheet(name);
		}
		
		arquivoSala >> nColunas >> nLinhas;
		
		mapaSala = new int*[nColunas];
		mapaObjetos = new int*[nColunas];

		for (int c = 0; c < nColunas; c++)
		{
			mapaSala[c] = new int[nLinhas];
			mapaObjetos[c] = new int[nLinhas];
		}

		for (int l = 0; l < nLinhas; l++)
			for (int c = 0; c < nColunas; c++)
				arquivoSala >> mapaSala[c][l];
		
		for (int l = 0; l < nLinhas; l++)
			for (int c = 0; c < nColunas; c++)
				arquivoSala >> mapaObjetos[c][l];
		
		arquivoSala.close();
	}
	else
	{
		exit(0);
	}
}

void Sala::escreverInfos()
{
	// Moedas
	qtdMoedas.setString("Gold: " + to_string(personagem->getMoedas()));
	qtdMoedas.desenhar(200, 20, 0);

	// Vidas
	qtdVidas.setString("HP: " + to_string(personagem->getVidas()));
	qtdVidas.desenhar(100, 20, 0);
}

void Sala::carregarItens()
{
	string path, arqName, nome;
	int nAnim, nFrames, nID;
	ifstream arquivoItens;
	Item *carregarItens;

	arqName = "itens.txt";

	arquivoItens.open(arqName);
	if (arquivoItens.is_open())
	{


		arquivoItens >> itensCarreg;


		carregarItens = new Item[itensCarreg];
		nomeItens = new string[itensCarreg];
		itensPath = new string[itensCarreg];
		tipoItem = new int[itensCarreg];

		for (int t = 0; t < nItens; t++)
		{
			arquivoItens >> nID >> nome >> path >> nAnim >> nFrames;
			if (!gRecursos.carregouSpriteSheet(nome))
				gRecursos.carregarSpriteSheet(nome, path, nAnim, nFrames);
			nomeItens[nID] = nome;
			itensPath[nID] = path;
			tipoItem[nID] = nID;
		}



		arquivoItens.close();
	}
	else
	{
		exit(0);
	}
}

void Sala::carregarInim()
{
	int nID, nAnim, nFrames, hp, def;
	string nome, path, spr;

	ifstream arqInimigos;
	arqInimigos.open("Inimigos.txt");

	if (arqInimigos.is_open())
	{

		arqInimigos >> inimCarreg;

		sprInim = new string[inimCarreg];
		iniPath = new string[inimCarreg];
		nomeInim = new string[inimCarreg];
		inimHp = new int[inimCarreg];
		inimDef = new int[inimCarreg];



		for (int i = 0; i < inimCarreg; i++)
		{
			// 0 sprMorcego sprites/bat.png 4 8

			arqInimigos >> nID >> spr >> path >> nAnim >> nFrames >> nome >> hp >> def;

			sprInim[nID] = spr;
			iniPath[nID] = path;
			nomeInim[nID] = nome;
			inimHp[nID] = hp;
			inimDef[nID] = def;
		}
	}
	arqInimigos.close();

}
void Sala::utilizarItens()
{

	if (personagem->getVivo())
	{
		if (gTeclado.pressionou[TECLA_KP_1])
		{
			inventario.remover(0);

			if (personagem->getVidas() + 10 <= 20)
			{
				personagem->atualizarVidas(10);
			}
			else
			{
				for (int i = 0; i < 20; i++)
				{
					if (personagem->getVidas() < 20)
					{
						personagem->atualizarVidas(1);
					}
					else
					{
						break;
					}
				}
			}
		}
		else if (gTeclado.pressionou[TECLA_KP_2])
		{
			inventario.remover(1);

			personagem->setpAtaque(personagem->getPAtaque() + 1);
		}
		else if (gTeclado.pressionou[TECLA_KP_3])
		{
			inventario.remover(2);

			for (int i = 0; i < nInimigos; i++)
			{
				inimigos[i].setpAtaque(inimigos[i].getPAtaque() - 1);
			}
		}
	}

}