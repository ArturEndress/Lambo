#include "Item.h"



Item::Item()
{
}


Item::~Item()
{
}

void Item::inicializar(string nome, string path, int nAnim, int nFrames)
{
	x = 0;
	y = 0;

	qtd = 0;
	tipo = 0;

	pegou = false;

	if (!gRecursos.carregouSpriteSheet(nome))
	{
		gRecursos.carregarSpriteSheet(nome, path, nAnim, nFrames);
	}
	item.setSpriteSheet(nome);

}


void Item::desenhar()
{
	if (!pegou)
		item.desenhar(x, y);
}
