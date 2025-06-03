/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-valentin.rueda
** File description:
** init_game.c
*/

#include "wolf.h"

/**
 * @brief Vérifie si une cellule est dans les limites du labyrinthe
 * @param x Coordonnée X
 * @param y Coordonnée Y
 * @return 1 si à l'intérieur, 0 sinon
 */
int is_in_bounds(int x, int y)
{
    return x > 0 && x < MAP_WIDTH - 1 && y > 0 && y < MAP_HEIGHT - 1;
}

/**
 * @brief Initialise une ligne de la map à 0
 * @param map Pointeur vers la map
 * @param line_index Index de la ligne à initialiser
 * @return 0 en cas de succès, -1 en cas d'erreur
 */
int init_map_line(int **map, int line_index)
{
    map[line_index] = malloc(sizeof(int) * MAP_WIDTH);
    if (map[line_index] == NULL) {
        free_map_lines(map, line_index);
        return -1;
    }
    for (int x = 0; x < MAP_WIDTH; x++) {
        map[line_index][x] = 0;
    }
    return 0;
}

/**
 * @brief Initialise la map à 0
 * @return Renvoie la map initialisée à 0
 */
int **init_map(void)
{
    int **map = malloc(sizeof(int *) * MAP_HEIGHT);

    if (map == NULL)
        return NULL;
    for (int i = 0; i < MAP_HEIGHT; i++) {
        if (init_map_line(map, i) == -1)
            return NULL;
    }
    return map;
}

/**
 * @brief Initialise la fenêtre (redimensionnable et fermable)
 * @return Renvoie la fenêtre initialisée
 */
sfRenderWindow *init_window(void)
{
    sfVideoMode v_mode = {SCR_W, SCR_H, 32};
    sfContextSettings settings = {0};
    sfRenderWindow *window = sfRenderWindow_create(
        v_mode, TITLE, sfClose, &settings);

    if (window) {
        sfRenderWindow_setMouseCursorVisible(window, sfFalse);
        sfRenderWindow_setVerticalSyncEnabled(window, sfTrue);
        sfRenderWindow_setFramerateLimit(window, 60);
    }
    return window;
}

static int init_game_variable(app_t *app, game_t *game)
{
    app->g = game;
    app->g->p = NULL;
    app->g->map = NULL;
    app->g->hud = NULL;
    app->g->enemies = NULL;
    app->g->enemy_count = 0;
    app->g->enemies_alive = 0;
    app->g->snd_efct_vol = 50.0f;
    app->g->p = init_player();
    if (!app->g->p)
        return -1;
    app->g->map = init_map();
    if (!app->g->map)
        return -1;
    app->g->hud = init_hud(app);
    if (!app->g->hud)
        return -1;
    return 0;
}

/**
 * @brief Initialise le jeu (player, map et ennemis)
 * @param app L'application à initialiser
 * @return 0 en cas de succès, -1 en cas d'erreur
 */
int init_game(app_t *app)
{
    game_t *game;

    if (!app)
        return -1;
    game = malloc(sizeof(game_t));
    if (game == NULL)
        return -1;
    if (init_game_variable(app, game) == -1)
        return -1;
    update_score(app->g->hud, app->g->p->score);
    generate_procedural_maze(app->g->map, MAZE_DENSITY);
    if (init_enemies(app, ENEMY_COUNT) != 0)
        return -1;
    return 0;
}
