/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-valentin.rueda
** File description:
** save.c
*/

#include "wolf.h"

static void save_player_info(app_t *app, FILE *file)
{
    fprintf(file, "player_x %f\n", app->g->p->x);
    fprintf(file, "player_y %f\n", app->g->p->y);
    fprintf(file, "player_dx %f\n", app->g->p->dx);
    fprintf(file, "player_dy %f\n", app->g->p->dy);
    fprintf(file, "player_planeX %f\n", app->g->p->planeX);
    fprintf(file, "player_planeY %f\n", app->g->p->planeY);
    fprintf(file, "player_score %d\n", app->g->p->score);
    fprintf(file, "player_life %d\n", app->g->p->life);
}

/**
 * @brief Sauvegarde les données du jeu dans un fichier
 * @param app Structure contenant les données de l'application
 * @param filename Nom du fichier de sauvegarde
 */
void save_game(app_t *app, const char *filename)
{
    FILE *file = fopen(filename, "w");

    if (!file)
        return perror("Erreur lors de l'ouverture du fichier de sauvegarde");
    save_player_info(app, file);
    fprintf(file, "map_width %d\n", MAP_WIDTH);
    fprintf(file, "map_height %d\n", MAP_HEIGHT);
    fprintf(file, "map_data\n");
    for (int y = 0; y < MAP_HEIGHT; y++)
        for (int x = 0; x < MAP_WIDTH; x++) {
            fprintf(file, "%d ", app->g->map[y][x]);
    }
    fprintf(file, "\nenemy_count %d\n", app->g->enemy_count);
    fprintf(file, "enemies_alive %d\n", app->g->enemies_alive);
    for (int i = 0; i < app->g->enemy_count; i++)
        fprintf(file, "enemy %d %f %f %d\n", i, app->g->enemies[i].x,
        app->g->enemies[i].y, app->g->enemies[i].alive);
    fclose(file);
}

static void parse_enemies(FILE *file, app_t *app)
{
    int enemy_count = 0;
    int enemy_id = 0;
    int enemy_alive = 0;
    float enemy_x = 0.0f;
    float enemy_y = 0.0f;

    fscanf(file, "enemy_count %d\n", &enemy_count);
    fscanf(file, "enemies_alive %d\n", &app->g->enemies_alive);
    for (int i = 0; i < enemy_count; i++) {
        fscanf(file, "enemy %d %f %f %d\n",
        &enemy_id, &enemy_x, &enemy_y, &enemy_alive);
        if (enemy_id >= 0 && enemy_id < app->g->enemy_count) {
            app->g->enemies[enemy_id].x = enemy_x;
            app->g->enemies[enemy_id].y = enemy_y;
            app->g->enemies[enemy_id].alive = enemy_alive;
        }
    }
}

static void parse_map(FILE *file, app_t *app)
{
    int map_width = 0;
    int map_height = 0;

    fscanf(file, "map_width %d\n", &map_width);
    fscanf(file, "map_height %d\n", &map_height);
    fscanf(file, "map_data\n");
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++)
            fscanf(file, "%d ", &app->g->map[y][x]);
        fscanf(file, "\n");
    }
}

static void parse_player_info(FILE *file, app_t *app)
{
    fscanf(file, "player_x %f\n", &app->g->p->x);
    fscanf(file, "player_y %f\n", &app->g->p->y);
    fscanf(file, "player_dx %f\n", &app->g->p->dx);
    fscanf(file, "player_dy %f\n", &app->g->p->dy);
    fscanf(file, "player_planeX %f\n", &app->g->p->planeX);
    fscanf(file, "player_planeY %f\n", &app->g->p->planeY);
    fscanf(file, "player_score %d\n", &app->g->p->score);
    fscanf(file, "player_life %d\n", &app->g->p->life);
}

/**
 * @brief Charge les données du jeu depuis un fichier
 * @param app Structure contenant les données de l'application
 * @param filename Nom du fichier de sauvegarde
 */
void load_game(app_t *app, const char *filename)
{
    FILE *file = fopen(filename, "r");

    if (!file) {
        perror("Erreur lors de l'ouverture du fichier de sauvegarde");
        return;
    }
    parse_player_info(file, app);
    parse_map(file, app);
    parse_enemies(file, app);
    if (app->g->hud) {
        update_score(app->g->hud, app->g->p->score);
        update_e_left(app->g->hud, app->g->enemies_alive);
        update_life(app->g->hud, app->g->p->life);
    }
    fclose(file);
}
