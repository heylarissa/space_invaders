#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#include "display.h"
#include "player.h"
#include "game.h"
#include "enemies.h"
#include "shots.h"


bool shot_in_this_column(SHOT *shots, PLAYER p)
{
    SHOT *aux;
    aux = shots;

    while (aux != NULL)
    {
        if (aux->x == p.x + SIZE_PLAYER + 5)
        {
            return TRUE;
        }
        aux = aux->next;
    }

    return FALSE;
}

/* SHOTS */
void delete_shot(int position, SHOT **head)
{
    SHOT *temp = *head;

    if (position == 0)
    {
        *head = (*head)->next;
        temp->next = NULL;
        free(temp);
    }
    else
    {
        for (int i = 0; i < position - 1; i++)
        {
            temp = temp->next;
        }

        SHOT *del = temp->next;
        temp->next = temp->next->next;
        del->next = NULL;
        free(del);
    }
}


void update_player_shots(PLAYER *p)
{
    if (p->shots == NULL)
        return; // se não houver tiros, ignorar
    SHOT *aux;
    int i = -1;
    aux = p->shots;
    while (aux != NULL)
    {
        i++;
        aux->y -= SIZE_PLAYER / 2;

        if (aux->y <= 0)
        {
            delete_shot(i, &p->shots);
        }
        aux = aux->next;
    }
}

void create_player_shot(PLAYER *p)
{
    if (!shot_in_this_column(p->shots, *p))
    {
        SHOT *new;
        new = malloc(sizeof(SHOT));
        new->direction = UP;
        new->x = p->x + p->w / 2;
        new->y = p->y;
        new->next = p->shots;
        p->shots = new;
    }
}
