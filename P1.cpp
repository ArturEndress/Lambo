#include "P1.h"

P1::P1()
{
	idPersonagem = Personagem1;
	x = gJanela.getLargura()/2;
}

P1::~P1()
{
}

void P1::inicializar()
{
	if (!gRecursos.carregouSpriteSheet("P1"))
		gRecursos.carregarSpriteSheet("P1", "Sprites/armor.png", 4, 9);
	spriteP1.setSpriteSheet("P1");

	spriteP1.setVelocidadeAnimacao(8);


	efeito = new Efeito[2];
	efeito[0].inicializar("espadaHB", "sprites/hitboxEspd.png", 1, 1);

	efeito[1].inicializar("espada", "sprites/espada.png", 1, 3);

	gTempo.inicializar();
	tick = gTempo.getTicks();

}

void P1::desenhar()
{
		spriteP1.desenhar(x, y);
		

		efeito[1].desenhar();
		if (efeito[1].getAtivo())
		{
			efeito[1].atualizarAnim();
		}
		
}

void P1::parado()
{
	for (int i = 0; i < 2; i++)
	{

		if (pos == pcima)
		{
			spriteP1.setAnimacao(0);

			efeito[i].setX(x);
			efeito[i].setY(y - spriteP1.getAltura() / 2);
			efeito[i].setRot(0);
		}
		else if (pos == pesq) {

			spriteP1.setAnimacao(1);

			efeito[i].setX(x - spriteP1.getLargura() / 2);
			efeito[i].setY(y);
			efeito[i].setRot(270);
		}
		else if (pos == pbaixo) {

			spriteP1.setAnimacao(2);

			efeito[i].setX(x);
			efeito[i].setY(y + spriteP1.getAltura() / 2);
			efeito[i].setRot(180);


		}
		else if (pos == pdir) {

			spriteP1.setAnimacao(3);

			efeito[i].setX(x + spriteP1.getLargura() / 2);
			efeito[i].setY(y);
			efeito[i].setRot(90);


		}
		else
		{
			spriteP1.setAnimacao(2);

			efeito[i].setX(x);
			efeito[i].setY(y + spriteP1.getAltura() / 2);
			efeito[i].setRot(0);
		}
	}
}

void P1::andarEsq()
{
	pos = pesq;
	x -= 2;
	spriteP1.setAnimacao(1);
	spriteP1.avancarAnimacao();
	for (int i = 0; i < 2; i++)
	{

		efeito[i].setX(x - spriteP1.getLargura() / 2);
		efeito[i].setY(y);
		efeito[i].setRot(270);
	}
}

void P1::andarDir()
{
	pos = pdir;

	x += 2;
	spriteP1.setAnimacao(3);
	spriteP1.avancarAnimacao();

	for (int i = 0; i < 2; i++)
	{

		efeito[i].setX(x + spriteP1.getLargura() / 2);
		efeito[i].setY(y);
		efeito[i].setRot(90);
	}
}

void P1::andarCima()
{
	pos = pcima;

	y -= 2;
	spriteP1.setAnimacao(0);
	spriteP1.avancarAnimacao();

	for (int i = 0; i < 2; i++)
	{

		efeito[i].setX(x);
		efeito[i].setY(y - spriteP1.getAltura() / 2);
		efeito[i].setRot(0);
	}
}

void P1::andarBaixo()
{
	pos = pbaixo;

	y += 2;
	spriteP1.setAnimacao(2);
	spriteP1.avancarAnimacao();
	for (int i = 0; i < 2; i++)
	{

		efeito[i].setX(x);
		efeito[i].setY(y + spriteP1.getAltura() / 2);
		efeito[i].setRot(180);
	}
}

void P1::setMorto()
{
	if (pVitais < 0)
	{
		spriteP1.~Sprite();
		vivo = false;
	}
}

void P1::atacar()
{
	if (gTeclado.pressionou[TECLA_ESPACO] && !efeito[0].getAtivo())
	{
		efeito[0].setAtivo(true);
		efeito[1].setAtivo(true);
		tick = gTempo.getTicks();
	}
	if (gTempo.getTempoAteTickAtual(tick) > 0.2)
	{
		efeito[0].setAtivo(false);
	}
}
