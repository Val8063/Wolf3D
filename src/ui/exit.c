/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-valentin.rueda
** File description:
** menu_exit.c
*/

#include "wolf.h"

/**
 * @brief Dessine le bouton EXIT sur le menu principal
 * @param app Structure contenant les données de l'application
 */
void draw_exit_button(app_t *app)
{
    sfRectangleShape *exit_button = NULL;
    sfText *exit_text = NULL;
    sfVector2f button_pos = {SCR_W - 200, SCR_H - 110};
    sfVector2f button_size = {150, 60};
    sfFloatRect bounds;
    sfVector2f text_pos;

    if (!app->font)
        app->font = sfFont_createFromFile(ARIAL_FONT);
    create_button(&exit_button, button_pos,
    sfColor_fromRGB(200, 0, 0), button_size);
    create_text(&exit_text, app->font, "EXIT", (sfVector2f){0, 0});
    bounds = sfText_getGlobalBounds(exit_text);
    text_pos.x = button_pos.x + (button_size.x - bounds.width) / 2;
    text_pos.y = button_pos.y + (button_size.y - bounds.height) / 2 - 5;
    sfText_setPosition(exit_text, text_pos);
    sfRenderWindow_drawRectangleShape(app->window, exit_button, NULL);
    sfRenderWindow_drawText(app->window, exit_text, NULL);
    sfRectangleShape_destroy(exit_button);
    sfText_destroy(exit_text);
}

/**
 * @brief Vérifie si l'utilisateur clique sur le bouton EXIT
 * @param app Structure contenant les données de l'application
 */
void is_clicking_on_exit(app_t *app)
{
    sfVector2f mouse_pos = get_normalized_mouse_pos(app);
    sfVector2f button_pos = {SCR_W - 200, SCR_H - 110};
    sfVector2f button_size = {150, 60};

    if (!app->menu || !app->menu->show_menu)
        return;
    if (mouse_pos.x >= button_pos.x && mouse_pos.x <= button_pos.x
        + button_size.x && mouse_pos.y >= button_pos.y &&
        mouse_pos.y <= button_pos.y + button_size.y) {
        sfRenderWindow_close(app->window);
    }
}
