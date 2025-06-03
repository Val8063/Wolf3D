/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-valentin.rueda
** File description:
** functions_settings.c - Fonctions pour l'écran des paramètres
*/

#include "wolf.h"

/**
 * @brief Affiche l'écran des paramètres
 * @param app Structure contenant les données de l'application
 */
void display_settings(app_t *app)
{
    sfRenderWindow_drawRectangleShape(app->window,
        app->menu->settings_bg, NULL);
    sfRenderWindow_setMouseCursorVisible(app->window, sfTrue);
    for (int i = 0; i < 4; i++) {
        sfRenderWindow_drawRectangleShape(app->window,
        app->menu->settings_btn[i], NULL);
        sfRenderWindow_drawText(app->window,
        app->menu->settings_txt[i], NULL);
    }
}
