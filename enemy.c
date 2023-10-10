#include <stdlib.h>
#include <string.h>
#include "enemy.h"

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
	// IMPLEMENTAR!
	//	Remove os tiros da lista
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
	// IMPLEMENTAR!
	// Os tiros presentes no tabuleiro devem ser atualizados
	//   Se o tiro acertar um alvo, ou sair do tabuleiro, ele deve ser removido da lista
	//   Caso contrário, ele deve "andar" uma casa (sqm) à frente
}

shot *straight_shot(space *board, shot_sentinel *list, enemy *shooter)
{
	// IMPLEMENTAR!
	// Adiciona um novo tiro à lista. Neste momento, todos os tiros se movem apenas para frente
}

int add_enemy(space *board, int position_y, int position_x)
{
	// IMPLEMENTAR!
	// Adiciona um inimigo no tabuleiro. Essa tarefa inclui a alocação do mesmo
	char *enemy_data = (char *)malloc(2 * sizeof(char));
	if (enemy_data == NULL)
	{
		// Verifique se a alocação de memória foi bem-sucedida
		return 0; // Ou qualquer valor de erro apropriado
	}

	// Copiando os dados para enemy_data
	strcpy(enemy_data, "E");
	board->map[position_x][position_y].type = ENEMY;
	board->map[position_x][position_y].entity = enemy_data;
}

int remove_enemy(space *board, int position_y, int position_x)
{
	// IMPLEMENTAR!
	// Remove um inimigo do tabuleiro. Essa tarefa inclui a desalocação do mesmo
}
