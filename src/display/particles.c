/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-valentin.rueda
** File description:
** particles.c
*/

#include "wolf.h"

/**
 * @brief Crée des particules de sang à la position d'un ennemi touché
 * @param app Structure contenant les données de l'application
 * @param enemyScreenX Position X de l'ennemi sur l'écran
 * @param enemyScreenY Position Y de l'ennemi sur l'écran
 */
void create_blood_particles(app_t *app, int enemyScreenX, int enemyScreenY)
{
    float angle = 0.0f;
    float speed = 0.0f;
    int i = 0;

    if (!app->particles->particle_clock)
        app->particles->particle_clock = sfClock_create();
    for (int j = 0; i < 20 && j < 100; j++) {
        if (app->particles->blood_particles[j].active)
            continue;
        app->particles->blood_particles[j].x = enemyScreenX;
        app->particles->blood_particles[j].y = enemyScreenY + 250;
        angle = ((float)rand() / RAND_MAX) * 2.0f * 3.14159f;
        speed = ((float)rand() / RAND_MAX) * 5.0f + 2.0f;
        app->particles->blood_particles[j].vx = cosf(angle) * speed;
        app->particles->blood_particles[j].vy = sinf(angle) * speed;
        app->particles->blood_particles[j].lifespan = 1.0f;
        app->particles->blood_particles[j].active = 1;
        i++;
    }
    app->particles->active_particles += i;
}

static void update_particles_pos(app_t *app, int i)
{
    app->particles->blood_particles[i].x +=
    app->particles->blood_particles[i].vx;
    app->particles->blood_particles[i].y +=
    app->particles->blood_particles[i].vy;
    app->particles->blood_particles[i].vx *= 0.95f;
    app->particles->blood_particles[i].vy *= 0.95f;
    app->particles->blood_particles[i].vy += 0.1f;
}

/**
 * @brief Met à jour les particules de sang (position, durée de vie)
 * @param app Structure contenant les données de l'application
 */
void update_blood_particles(app_t *app)
{
    float dt;

    if (!app->particles || !app->particles->particle_clock)
        return;
    dt = sfTime_asSeconds(sfClock_restart(app->particles->particle_clock));
    for (int i = 0; i < 100; i++) {
        if (!app->particles->blood_particles[i].active)
            continue;
        app->particles->blood_particles[i].lifespan -= dt;
        if (app->particles->blood_particles[i].lifespan <= 0) {
            app->particles->blood_particles[i].active = 0;
            app->particles->active_particles--;
        } else {
            update_particles_pos(app, i);
        }
    }
}

static void render_particles(app_t *app, sfCircleShape *circle, int i)
{
    float opacity = 255.0f;

    sfCircleShape_setRadius(circle, 2.0f);
    sfCircleShape_setOrigin(circle, (sfVector2f){2.0f, 2.0f});
    sfCircleShape_setPosition(circle,
        (sfVector2f){app->particles->blood_particles[i].x,
        app->particles->blood_particles[i].y});
    sfCircleShape_setFillColor(circle,
        sfColor_fromRGBA(180, 0, 0, (sfUint8)opacity));
    sfRenderWindow_drawCircleShape(app->window, circle, NULL);
}

/**
 * @brief Dessine les particules de sang actives
 * @param app Structure contenant les données de l'application
 */
void draw_blood_particles(app_t *app)
{
    int i;
    sfCircleShape *circle;

    if (!app->particles)
        return;
    update_blood_particles(app);
    if (app->particles->active_particles <= 0)
        return;
    circle = sfCircleShape_create();
    for (i = 0; i < 100; i++) {
        if (!app->particles->blood_particles[i].active)
            continue;
        render_particles(app, circle, i);
    }
    sfCircleShape_destroy(circle);
}
