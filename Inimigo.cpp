#include "Inimigo.h"

Inimigo::Inimigo()
{
	pAtaque = rand() % 11 + 2;
}


Inimigo::~Inimigo()
{
}

void Inimigo::inicializar(string nome, string path, int nAnim, int nFrames, int pVid, int pDef)
{
	x = 0;
	y = 0;

	pDefesa = pDef;
	pVitais = pVid;

	vivo = true;
	podeMachucar = true;
	dirKnb = 0;

	gTempo.inicializar();

	tick = gTempo.getTicks();
	tKnB = gTempo.getTicks();
	knb = false;

	if (!gRecursos.carregouSpriteSheet(nome))
	{
		gRecursos.carregarSpriteSheet(nome, path, nAnim, nFrames);
	}
	sprIni.setSpriteSheet(nome);
}

void Inimigo::desenhar()
{
	sprIni.desenhar(x, y);

	if (gTempo.getTempoAteTickAtual(tick) > 1)
	{
		podeMachucar = true;
	}

}

void Inimigo::atualizarVidas(int pVitais)
{
	this->pVitais += pVitais;
	if (this->pVitais > 0)
		vivo=true;
	else 
	{
		vivo = false; 
	}
}

void Inimigo::setPodeMachucar()
{
	if (podeMachucar)
	{
		podeMachucar = false;
		tick = gTempo.getTicks();

	}
	
}

void Inimigo::parado()
{
	sprIni.setAnimacao(2);
}

void Inimigo::andarEsq()
{
	x -= 2;
	sprIni.setAnimacao(1);
	sprIni.avancarAnimacao();
}

void Inimigo::andarDir()
{
	x += 2;
	sprIni.setAnimacao(3);
	sprIni.avancarAnimacao();
}

void Inimigo::andarCima()
{
	y -= 2;
	sprIni.setAnimacao(0);
	sprIni.avancarAnimacao();
}

void Inimigo::andarBaixo()
{
	y += 2;
	sprIni.setAnimacao(2);
	sprIni.avancarAnimacao();	
}

void Inimigo::knockBack()
{
	if (gTempo.getTempoAteTickAtual(tKnB) > 0.2)
	{
		knb = false;
	}

	if (knb)
	{
		if (dirKnb == Left)
		{
			x -= 10;
		}
		else if (dirKnb == Right)
		{
			x += 10;
		}
		else if (dirKnb == Up)
		{
			y -= 10;
		}
		else if (dirKnb == Down)
		{
			y += 10;
		}
	}
}

void Inimigo::setKnockBack()
{
	tKnB = gTempo.getTicks();
	knb = true;
}
