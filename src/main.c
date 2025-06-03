/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-valentin.rueda
** File description:
** main.c
*/

#include "wolf.h"

static void refresh_window(sfRenderWindow *window)
{
    sfRenderWindow_display(window);
}

/**
 * @brief Exécute la boucle principale du jeu
 * @param app Structure contenant les données de l'application
 * @return int Code d'erreur (0 en cas de succès)
 */
static int game_loop(app_t *app)
{
    sfClock *clock = sfClock_create();

    if (!clock)
        return 84;
    while (sfRenderWindow_isOpen(app->window)) {
        while (sfRenderWindow_pollEvent(app->window, &app->evt)) {
            process_event(app);
        }
        if ((!app->menu || !app->menu->show_menu) &&
            (!app->menu || !app->menu->show_settings) &&
            (!app->victory || !app->victory->show_victory)) {
            sfRenderWindow_setMouseCursorVisible(app->window, sfFalse);
            update_player_rotation(app);
        } else
            sfRenderWindow_setMouseCursorVisible(app->window, sfTrue);
        display(app);
        refresh_window(app->window);
    }
    sfClock_destroy(clock);
    return 0;
}

int main(int argc, char **argv)
{
    app_t *app = init_application();
    int return_code = 0;

    if (!app)
        return 84;
    if (argc > 1 && strcmp(argv[1], "") != 0) {
        load_game(app, argv[1]);
    }
    return_code = game_loop(app);
    save_game(app, "save.txt");
    free_app(app);
    return return_code;
}
