/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-valentin.rueda
** File description:
** victory.c - Gestion de l'écran de victoire
*/

#include "wolf.h"

/**
 * @brief Initialise les éléments de l'écran de victoire
 * @param app Structure contenant les données de l'application
 */
void init_victory_screen(app_t *app)
{
    sfVector2f position = {SCR_W / 2 - 200, SCR_H / 2 - 100};

    app->victory->show_victory = 0;
    app->victory->victory_text = NULL;
    if (app->victory->bg) {
        sfRectangleShape_setSize(app->victory->bg,
            (sfVector2f){SCR_W, SCR_H});
        sfRectangleShape_setFillColor(app->victory->bg,
            sfColor_fromRGBA(0, 0, 0, 200));
    }
    app->victory->victory_text = sfText_create();
    if (app->victory->victory_text && app->font) {
        sfText_setFont(app->victory->victory_text, app->font);
        sfText_setString(app->victory->victory_text,
            "VICTORY!\nAll enemies defeated!");
        sfText_setCharacterSize(app->victory->victory_text, 72);
        sfText_setColor(app->victory->victory_text, sfYellow);
        sfText_setPosition(app->victory->victory_text, position);
    }
}

/**
 * @brief Vérifie si tous les ennemis sont morts
 * @param app Structure contenant les données de l'application
 */
void check_all_enemies_dead(app_t *app)
{
    int all_dead = 1;

    if (!app->victory || app->menu->show_menu || app->menu->show_settings ||
    app->victory->show_victory)
        return;
    if (!app->g->enemies || app->g->enemy_count <= 0)
        return;
    for (int i = 0; i < app->g->enemy_count; i++) {
        if (app->g->enemies[i].alive) {
            all_dead = 0;
            break;
        }
    }
    if (all_dead) {
        app->menu->show_menu = 0;
        app->menu->show_settings = 0;
        app->victory->show_victory = 1;
    }
}

/**
 * @brief Affiche l'écran de victoire
 * @param app Structure contenant les données de l'application
 */
void display_victory_screen(app_t *app)
{
    if (!app->victory || !app->victory->show_victory)
        return;
    sfRenderWindow_setMouseCursorVisible(app->window, sfTrue);
    if (app->victory->bg)
        sfRenderWindow_drawRectangleShape(app->window,
            app->victory->bg, NULL);
    if (app->victory->victory_text)
        sfRenderWindow_drawText(app->window, app->victory->victory_text, NULL);
}
