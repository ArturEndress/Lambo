#include "P3.h"

P3::P3()
{
	idPersonagem = Personagem3;
	x = gJanela.getLargura()/1.5;
}



P3::~P3()
{
}

void P3::inicializar()
{
	if (!gRecursos.carregouSpriteSheet("P3"))
		gRecursos.carregarSpriteSheet("P3", "Sprites/archer.png", 8, 13);
	gRecursos.getSpriteSheet("P3")->setNumFramesDaAnimacao(0, 9);
	gRecursos.getSpriteSheet("P3")->setNumFramesDaAnimacao(1, 9);
	gRecursos.getSpriteSheet("P3")->setNumFramesDaAnimacao(2, 9);
	gRecursos.getSpriteSheet("P3")->setNumFramesDaAnimacao(3, 9);
	spriteP3.setSpriteSheet("P3");

	spriteP3.setVelocidadeAnimacao(8);
	spriteP3.setAnimacao(2);

	efeito = new Efeito[MAX_FLECHAS];
	
	for (int i = 0; i < MAX_FLECHAS; i++)
	{
		efeito[i].inicializar("flecha", "sprites/flecha.png", 4, 1);
	}

	gTempo.inicializar();
	tempo = gTempo.getTicks();
	
}

void P3::desenhar()
{
	spriteP3.desenhar(x, y);
	for (int i = 0; i < MAX_FLECHAS; i++)
	{
		efeito[i].desenhar();
	}
}

void P3::parado()
{
	
	if (pos == pcima)
	{
		if (gTeclado.segurando[TECLA_ESPACO])
		{
			spriteP3.setAnimacao(4);
			spriteP3.avancarAnimacao();
		}
		
		for (int i = 0; i < MAX_FLECHAS; i++)
		{
			if (!efeito[i].getAtivo())
			{
				efeito[i].setDir(n);
				efeito[i].setRot(0);
			}
		}
	}
	else if (pos == pesq) {
		if (gTeclado.segurando[TECLA_ESPACO])
		{
			spriteP3.setAnimacao(5);
			spriteP3.avancarAnimacao();
		}
		
		for (int i = 0; i < MAX_FLECHAS; i++)
		{
			if (!efeito[i].getAtivo())
			{
				efeito[i].setDir(o);
				efeito[i].setRot(270);
			}
		}
	}
	else if (pos == pbaixo) {
		if (gTeclado.segurando[TECLA_ESPACO])
		{
			spriteP3.setAnimacao(6);
			spriteP3.avancarAnimacao();
		}
		
		for (int i = 0; i < MAX_FLECHAS; i++)
		{
			if (!efeito[i].getAtivo())
			{
				efeito[i].setDir(s);
				efeito[i].setRot(180);
			}
		}
		
	}
	else if (pos == pdir) {
		if (gTeclado.segurando[TECLA_ESPACO])
		{
			spriteP3.setAnimacao(7);
			spriteP3.avancarAnimacao();
		}

		for (int i = 0; i < MAX_FLECHAS; i++)
		{
			if (!efeito[i].getAtivo())
			{
				efeito[i].setDir(l);
				efeito[i].setRot(90);
			}
		}
		
	}
	else
	{
		if (gTeclado.segurando[TECLA_ESPACO])
		{
			spriteP3.setAnimacao(6);
			spriteP3.avancarAnimacao();
		}
		for (int i = 0; i < MAX_FLECHAS; i++)
		{
			if (!efeito[i].getAtivo())
			{
				efeito[i].setDir(s);
				efeito[i].setRot(180);
			}
		}
	}




	for (int i = 0; i < MAX_FLECHAS; i++)
	{
		efeito[i].movimentar();
	}

}

void P3::andarEsq()
{
	x -= 2;
	spriteP3.setAnimacao(1);
	spriteP3.avancarAnimacao();
	pos = pesq;

	for (int i = 0; i < MAX_FLECHAS; i++)
	{
		if (efeito[i].getPegarDir())
			{
				efeito[i].setDir(o);
				efeito[i].setRot(270);

			}
	

			efeito[i].movimentar();
	}
	
	
}

void P3::andarDir()
{
	x += 2;
	spriteP3.setAnimacao(3);
	spriteP3.avancarAnimacao();
	pos = pdir;

	for (int i = 0; i < MAX_FLECHAS; i++)
	{
		if (efeito[i].getPegarDir())
		{
			efeito[i].setDir(l);
			efeito[i].setRot(90);
		}


		efeito[i].movimentar();
	}
}

void P3::andarCima()
{
	y -= 2;
	spriteP3.setAnimacao(0);
	spriteP3.avancarAnimacao();
	pos = pcima;


	for (int i = 0; i < MAX_FLECHAS; i++)
	{
		if (efeito[i].getPegarDir())
		{
			efeito[i].setDir(n);
			efeito[i].setRot(0);

		}


		efeito[i].movimentar();
	}
}

void P3::andarBaixo()
{
	y += 2;
	spriteP3.setAnimacao(2);
	spriteP3.avancarAnimacao();
	pos = pbaixo;

	for (int i = 0; i < MAX_FLECHAS; i++)
	{
		if (efeito[i].getPegarDir())
		{
			efeito[i].setDir(s);
			efeito[i].setRot(180);
		}


		efeito[i].movimentar();
	}
}

void P3::setMorto()
{
	if (pVitais < 0) 
	{ 
		spriteP3.~Sprite();
		vivo = false; 		
	}
}

void P3::atacar()
{

	if (gTeclado.segurando[TECLA_ESPACO]) {
		if(pos==pcima)
		{
			spriteP3.setAnimacao(4);
			spriteP3.avancarAnimacao();
		}
		else if (pos == pesq) {
			spriteP3.setAnimacao(5);
			spriteP3.avancarAnimacao();
		}
		else if (pos == pbaixo){
			spriteP3.setAnimacao(6);
			spriteP3.avancarAnimacao();
		}
		else if (pos == pdir) {
			spriteP3.setAnimacao(7);
			spriteP3.avancarAnimacao();
		}

	}


	if (gTempo.getTempoAteTickAtual(tempo) > 0.5)
	{
		podeAtirar = true;
	}
	if (podeAtirar)
	{
		for (int i = 0; i < MAX_FLECHAS; i++)
		{
			if (!efeito[i].getAtivo())
			{
				if (gTeclado.segurando[TECLA_ESPACO])
				{
					
					efeito[i].setX(x);
					efeito[i].setY(y);
					efeito[i].setAtivo(true);
					efeito[i].setPegarDir(false);
					tempo = gTempo.getTicks();
					podeAtirar = false;
					break;
				}
			}
		}
	}

	

	for (int i = 0; i < MAX_FLECHAS; i++)
	{
		if (efeito[i].getX() > gJanela.getLargura() + efeito[i].getSprite().getLargura() / 2 || 
			efeito[i].getX() < -efeito[i].getSprite().getLargura() / 2)
		{
			efeito[i].setAtivo(false);
			efeito[i].setPegarDir(true);
		}
		if (efeito[i].getY() > gJanela.getAltura() + efeito[i].getSprite().getAltura() / 2 ||
			efeito[i].getY() < -efeito[i].getSprite().getAltura() / 2)
		{
			efeito[i].setAtivo(false);
			efeito[i].setPegarDir(true);
		}
	}
}
