#include "Personagem.h"



Personagem::Personagem()
{
	srand(time(0));

	pDefesa = 7;
	pVitais = uniRandEntre(2, 12);
	moedas = 0;
	podeMachucar = true;
	pos = pbaixo;
	vivo = true;
}


Personagem::~Personagem()
{
}

void Personagem::atualizarVidas(int pVitais)
{
	this->pVitais += pVitais;
	if (this->pVitais <= 0)
		vivo=false;

}


void Personagem::andar()
{
	if (gTeclado.segurando[TECLA_W])
	{
		pos = pcima;
		if (podeAndar[cima])
			andarCima();
	}
	else if (gTeclado.segurando[TECLA_A])
	{
		pos = pesq;
		if (podeAndar[esq])
			andarEsq();
	}
	else if (gTeclado.segurando[TECLA_D])
	{
		pos = pdir;
		if (podeAndar[dir])
			andarDir();
	}
	else if (gTeclado.segurando[TECLA_S])
	{
		pos = pbaixo;
		if (podeAndar[baixo])
			andarBaixo();
	}
	else
		parado();
}


