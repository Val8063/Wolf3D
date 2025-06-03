/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-valentin.rueda
** File description:
** enemy.c
*/

#include "wolf.h"

/**
 * @brief Place un ennemi à une position aléatoire valide dans le labyrinthe
 * @param app L'application contenant le jeu
 * @param enemy_index L'index de l'ennemi à placer
 */
static void place_enemy_randomly(app_t *app, int enemy_index)
{
    int x = 0;
    int y = 0;
    int attempts = 0;
    const int max_attempts = 100;

    while (attempts < max_attempts) {
        x = 1 + rand() % (MAP_WIDTH - 2);
        y = 1 + rand() % (MAP_HEIGHT - 2);
        attempts++;
        if (set_pos_if_valid(x, y, enemy_index, app))
            return;
    }
    app->g->enemies[enemy_index].x = 3.0f;
    app->g->enemies[enemy_index].y = 3.0f;
}

/**
 * @brief Initialise les ennemis dans le jeu
 * @param app L'application contenant le jeu
 * @param count Le nombre d'ennemis à initialiser
 * @return 0 en cas de succès, -1 en cas d'erreur
 */
int init_enemies(app_t *app, int count)
{
    sfTexture *texture = sfTexture_createFromFile(ENNEMY_ASSET, NULL);

    if (!texture)
        return -1;
    app->g->enemy_count = count;
    app->g->enemies_alive = count;
    app->g->enemies = malloc(sizeof(enemy_t) * count);
    if (app->g->enemies == NULL)
        return -1;
    srand(time(NULL));
    for (int i = 0; i < count; i++) {
        place_enemy_randomly(app, i);
        app->g->enemies[i].texture = texture;
        app->g->enemies[i].sprite = sfSprite_create();
        if (!app->g->enemies[i].sprite)
            return -1;
        sfSprite_setTexture(app->g->enemies[i].sprite, texture, sfTrue);
        app->g->enemies[i].alive = 1;
    }
    return 0;
}

static int calculate_enemy_transform(player_t *p, enemy_t *enemy,
    float *transformX, float *transformY)
{
    float dx = enemy->x - p->x;
    float dy = enemy->y - p->y;
    float determinant = p->planeX * p->dy - p->dx * p->planeY;
    float invDet = 0.0f;

    if (fabsf(determinant) < 0.001f)
        return 0;
    invDet = 1.0f / determinant;
    *transformX = invDet * (p->dy * dx - p->dx * dy);
    *transformY = invDet * (-p->planeY * dx + p->planeX * dy);
    if (*transformY <= 0.001f)
        return 0;
    return 1;
}

static void calculate_sprite_dimensions(float dx, float dy,
    int *spriteHeight, int *spriteWidth)
{
    float euclidDistance = sqrtf(dx * dx + dy * dy);

    if (euclidDistance < 0.5f)
        *spriteHeight = (int)(SCR_H * 0.95f);
    else
        *spriteHeight = (int)(SCR_H / (euclidDistance * 1.1f) + 50);
    *spriteWidth = *spriteHeight;
}

static void calculate_vertical_bounds(int spriteHeight,
    int *drawStartY, int *drawEndY)
{
    *drawStartY = (int)(SCR_H * 0.5) - spriteHeight / 2;
    if (*drawStartY < 0)
        *drawStartY = 0;
    *drawEndY = spriteHeight + *drawStartY;
    if (*drawEndY >= SCR_H)
        *drawEndY = SCR_H - 1;
}

static void set_up_sprite(enemy_t *enemy)
{
    if (ENEMY_TEXTURE_SIZE > 0) {
        sfSprite_setScale(enemy->sprite, (sfVector2f) {
            enemy->width / (float)ENEMY_TEXTURE_SIZE,
            enemy->height / (float)ENEMY_TEXTURE_SIZE
        });
        sfSprite_setPosition(enemy->sprite, (sfVector2f) {
            enemy->screenX - enemy->width / 2,
            enemy->screenY
        });
    }
}

static void setup_enemy_rendering(app_t *app, enemy_t *enemy,
    float *transformX, float *transformY)
{
    float dx = enemy->x - app->g->p->x;
    float dy = enemy->y - app->g->p->y;
    int spriteHeight = 0;
    int spriteWidth = 0;
    int drawStartY = 0;
    int drawEndY = 0;
    int spriteX = 0;

    if (!calculate_enemy_transform(app->g->p, enemy, transformX, transformY))
        return;
    spriteX = (int)((SCR_W / 2) * (1 + *transformX / *transformY));
    calculate_sprite_dimensions(dx, dy, &spriteHeight, &spriteWidth);
    calculate_vertical_bounds(spriteHeight, &drawStartY, &drawEndY);
    enemy->screenX = spriteX;
    enemy->screenY = drawStartY;
    enemy->width = spriteWidth;
    enemy->height = spriteHeight;
}

static void process_single_enemy(app_t *app, int index)
{
    enemy_t *enemy = &app->g->enemies[index];
    float transformX = 0.0f;
    float transformY = 0.0f;

    if (!enemy->alive || !enemy->sprite)
        return;
    if (!is_enemy_visible(app, enemy)) {
        enemy->render = 0;
        return;
    }
    setup_enemy_rendering(app, enemy, &transformX, &transformY);
    if (transformY <= 0.001f)
        return;
    enemy->transformX = transformX;
    enemy->transformY = transformY;
    enemy->render = 1;
    set_up_sprite(enemy);
}

int process_enemy(app_t *app)
{
    if (!app->g || !app->g->p || !app->g->enemies || app->g->enemy_count <= 0)
        return 84;
    for (int i = 0; i < app->g->enemy_count; i++) {
        process_single_enemy(app, i);
    }
    return 1;
}

void draw_enemies(app_t *app)
{
    if (!app->g || !app->g->enemies || app->g->enemy_count <= 0)
        return;
    for (int i = 0; i < app->g->enemy_count; i++) {
        if (!app->g->enemies[i].alive || !app->g->enemies[i].sprite
        || !app->g->enemies[i].render)
            continue;
        sfRenderWindow_drawSprite(app->window,
            app->g->enemies[i].sprite, NULL);
        app->g->enemies[i].render = 0;
    }
}
