#include "P2.h"

P2::P2()
{
	idPersonagem = Personagem2;
	x = gJanela.getLargura() / 3;
}


P2::~P2()
{
}

void P2::inicializar()
{
	if (!gRecursos.carregouSpriteSheet("P2"))
		gRecursos.carregarSpriteSheet("P2", "Sprites/skel.png", 8, 9);
	gRecursos.getSpriteSheet("P2")->setNumFramesDaAnimacao(4, 6);
	gRecursos.getSpriteSheet("P2")->setNumFramesDaAnimacao(5, 6);
	gRecursos.getSpriteSheet("P2")->setNumFramesDaAnimacao(6, 6);
	gRecursos.getSpriteSheet("P2")->setNumFramesDaAnimacao(7, 6);
	spriteP2.setSpriteSheet("P2");

	spriteP2.setVelocidadeAnimacao(8);


	efeito = new Efeito[1];
	
		efeito[0].inicializar("explosao", "sprites/explosao.png", 1, 12);

		efeito[0].getSprite().setAnimacao(0, false);
		

	gTempo.inicializar();
	cooldown = gTempo.getTicks();
	podeAtacar = true;
}

void P2::desenhar()
{
		spriteP2.desenhar(x, y);
		if (!podeAtacar)
		{
			if (efeito[0].getAtivo())
			{
				efeito[0].desenhar();

				efeito[0].atualizarAnim();
			}
		}
		
}

void P2::parado()
{
	spriteP2.setAnimacao(2);
}

void P2::andarEsq()
{
	x -= 2;
	spriteP2.setAnimacao(1);
	spriteP2.avancarAnimacao();
	pos = pesq;
	
}

void P2::andarDir()
{
	x += 2;
	spriteP2.setAnimacao(3);
	spriteP2.avancarAnimacao();

}

void P2::andarCima()
{
	y -= 2;
	spriteP2.setAnimacao(0);
	spriteP2.avancarAnimacao();

}

void P2::andarBaixo()
{
	y += 2;
	spriteP2.setAnimacao(2);
	spriteP2.avancarAnimacao();

}

void P2::setMorto()
{
	if (pVitais < 0)
	{
		spriteP2.~Sprite();
		vivo = false;		
	}
}

void P2::atacar()
{
	
	if (podeAtacar)
	{
		if (gMouse.pressionou[BOTAO_MOUSE_ESQ])
		{
			efeito[0].setAtivo(true);
			efeito[0].setX(gMouse.x);
			efeito[0].setY(gMouse.y);

			podeAtacar = false;

			cooldown = gTempo.getTicks();
		}
	}

	if (gTempo.getTempoAteTickAtual(cooldown) > 5)
	{
		podeAtacar = true;
	}
}
