#include <stdlib.h>
#include <string.h>
#include "enemy.h"
#include <stdio.h>

int can_shoot(space *board, int enemy_x, int enemy_y, shot_sentinel *list)
{
	// Verifique se não existem outros inimigos na mesma coluna (à "frente")
	for (int x = enemy_x + 1; x < board->max_x; x++)
	{
		if (board->map[x][enemy_y].type == ENEMY)
		{
			return 0; // Outro inimigo à frente, não pode atirar
		}
	}

	// Verifique se não há tiros ativos na coluna
	shot *current = list->first;
	while (current != NULL)
	{
		if (current->position_x == enemy_x && current->position_y == enemy_y)
		{
			return 0; // Tiro ativo na mesma coluna, não pode atirar
		}
		current = current->next;
	}

	return 1; // Pode atirar
}

shot_sentinel *create_shotlist(void)
{
	shot_sentinel *list = (shot_sentinel *)malloc(sizeof(shot_sentinel));
	if (list == NULL)
		return NULL;
	list->first = NULL;
	list->last = NULL;
	return list;
}

shot *remove_shot(shot *current, shot *previous, shot_sentinel *list)
{
	if (previous != NULL)
	{
		previous->next = current->next;
	}
	else
	{
		list->first = current->next;
	}

	if (current == list->last)
	{
		list->last = previous;
	}

	shot *next = current->next;
	free(current);
	return next;
}

void clean_shots(shot_sentinel *list)
{
	shot *p = (shot *)list->first;
	shot *q = NULL;
	while (p != NULL)
		p = remove_shot(p, q, list);
}

void update_shots(space *board, shot_sentinel *list)
{
	shot *current = list->first;
	shot *previous = NULL;

	while (current != NULL)
	{
		// Atualize a posição vertical do tiro
		current->position_y++;

		// Verifique se o tiro atingiu o solo
		if (current->position_y >= board->max_y)
		{
			// Remova o tiro da lista e libere a memória
			current = remove_shot(current, previous, list);
		}
		else
		{
			previous = current;
			current = current->next;
		}
	}
}

shot_sentinel *straight_shoot(space *board, shot_sentinel *list, enemy *shooter)
{
	printf("oi\n");
	// Verifique se a lista de tiros é nula; se for, crie uma nova
	if (list == NULL)
	{
		list = create_shotlist();
	}

	// Alocar memória para o novo tiro
	shot *new_shot = (shot *)malloc(sizeof(shot));

	if (new_shot == NULL)
	{
		// Tratamento de erro: não foi possível alocar memória
		return list;
	}

	// Configurar os campos do novo tiro
	new_shot->position_x = shooter->position_x; // A posição x do tiro é a mesma do inimigo
	new_shot->position_y = shooter->position_y; // A posição y do tiro é a mesma do inimigo

	// Inserir o novo tiro na lista
	if (list->first == NULL)
	{
		// Se a lista estiver vazia, o novo tiro será o primeiro e o último
		list->first = new_shot;
		list->last = new_shot;
	}
	else
	{
		// Caso contrário, o novo tiro será adicionado ao final da lista
		list->last->next = new_shot;
		list->last = new_shot;
	}

	return list;
}

int add_enemy(space *board, int position_y, int position_x)
{
	// Verificar se as coordenadas são válidas
	if (position_x < 0 || position_x >= board->max_x || position_y < 0 || position_y >= board->max_y)
	{
		return 1; // Código de erro, coordenadas inválidas
	}

	// Aloque memória para o inimigo
	enemy *new_enemy = (enemy *)malloc(sizeof(enemy));

	// Configure os campos do inimigo conforme necessário

	// Atualize o tabuleiro
	board->map[position_x][position_y].type = ENEMY;
	board->map[position_x][position_y].entity = new_enemy;

	return 0; // Sem erros
}

int remove_enemy(space *board, int position_y, int position_x)
{
	// Verificar se as coordenadas são válidas
	if (position_x < 0 || position_x >= board->max_x || position_y < 0 || position_y >= board->max_y)
	{
		return 1; // Código de erro, coordenadas inválidas
	}

	// Desalocar a memória do inimigo
	free(board->map[position_x][position_y].entity);

	// Atualizar o tabuleiro
	board->map[position_x][position_y].type = 0;
	board->map[position_x][position_y].entity = NULL;

	return 0; // Sem erros
}
