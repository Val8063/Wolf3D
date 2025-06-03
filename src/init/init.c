/*
** EPITECH PROJECT, 2024
** Wolf3D
** File description:
** init.c
*/

#include "wolf.h"

static int init_menu_sprite(menu_t *menu)
{
    sfVector2u size;
    float scale_x = 0.0f;
    float scale_y = 0.0f;

    menu->menu_tex = sfTexture_createFromFile(MENU_ASSET, NULL);
    if (!menu->menu_tex) {
        return free(menu), -1;
    }
    menu->menu_spr = sfSprite_create();
    if (!menu->menu_spr) {
        sfTexture_destroy(menu->menu_tex);
        return free(menu), -1;
    }
    sfSprite_setTexture(menu->menu_spr, menu->menu_tex, sfTrue);
    size = sfTexture_getSize(menu->menu_tex);
    scale_x = (float)SCR_W / size.x;
    scale_y = (float)SCR_H / size.y;
    sfSprite_setScale(menu->menu_spr, (sfVector2f){scale_x, scale_y});
    return 0;
}

static menu_t *init_menu_struct(void)
{
    menu_t *menu = malloc(sizeof(menu_t));

    if (!menu)
        return NULL;
    init_menu_sprite(menu);
    menu->show_menu = 1;
    menu->show_settings = 0;
    menu->settings_bg = NULL;
    for (int i = 0; i < 4; i++) {
        menu->settings_btn[i] = NULL;
        menu->settings_txt[i] = NULL;
    }
    return menu;
}

static victory_screen_t *init_victory_struct(sfFont *font)
{
    victory_screen_t *victory = malloc(sizeof(victory_screen_t));
    sfVector2f position = {SCR_W / 2 - 200, SCR_H / 2 - 100};

    if (!victory)
        return NULL;
    victory->show_victory = 0;
    victory->bg = sfRectangleShape_create();
    if (!victory->bg)
        return free(victory), NULL;
    sfRectangleShape_setSize(victory->bg, (sfVector2f){SCR_W, SCR_H});
    sfRectangleShape_setFillColor(victory->bg, sfColor_fromRGBA(0, 0, 0, 200));
    victory->victory_text = sfText_create();
    if (victory->victory_text && font) {
        sfText_setFont(victory->victory_text, font);
        sfText_setString(victory->victory_text, "VICTORY!\n");
        sfText_setCharacterSize(victory->victory_text, 72);
        sfText_setColor(victory->victory_text, sfYellow);
        sfText_setPosition(victory->victory_text, position);
    }
    return victory;
}

static wall_textures_t *init_wall_textures(void)
{
    wall_textures_t *textures = malloc(sizeof(wall_textures_t));

    if (!textures)
        return NULL;
    textures->wall_tex = sfTexture_createFromFile(WALL_ASSET, NULL);
    if (!textures->wall_tex) {
        printf("Erreur: Impossible de charger la texture des murs.\n");
        free(textures);
        return NULL;
    }
    textures->wall_img = sfTexture_copyToImage(textures->wall_tex);
    if (!textures->wall_img) {
        printf("Erreur: erreur de convertion de la texture des murs\n");
        sfTexture_destroy(textures->wall_tex);
        free(textures);
        return NULL;
    }
    return textures;
}

static crosshair_t *init_crosshair(void)
{
    crosshair_t *crosshair = malloc(sizeof(crosshair_t));
    sfVector2u size;

    if (!crosshair)
        return NULL;
    crosshair->cross_tex = sfTexture_createFromFile(CROSSHAIR_ASSET, NULL);
    if (!crosshair->cross_tex) {
        printf("Erreur: Impossible de charger la texture du viseur.\n");
        free(crosshair);
        return NULL;
    }
    crosshair->cross_spr = sfSprite_create();
    sfSprite_setTexture(crosshair->cross_spr, crosshair->cross_tex, sfTrue);
    size = sfTexture_getSize(crosshair->cross_tex);
    sfSprite_setOrigin(crosshair->cross_spr,
        (sfVector2f){size.x / 2.0f, size.y / 2.0f});
    sfSprite_setPosition(crosshair->cross_spr,
        (sfVector2f){SCR_W / 2.0f, SCR_H / 2.0f});
    return crosshair;
}

static framebuffer_t *init_framebuffer(void)
{
    framebuffer_t *fb = malloc(sizeof(framebuffer_t));

    if (!fb)
        return NULL;
    fb->fb = sfImage_create(SCR_W, SCR_H);
    if (!fb->fb) {
        free(fb);
        return NULL;
    }
    fb->frame_tex = sfTexture_create(SCR_W, SCR_H);
    if (!fb->frame_tex) {
        sfImage_destroy(fb->fb);
        free(fb);
        return NULL;
    }
    fb->frame_spr = sfSprite_create();
    sfSprite_setTexture(fb->frame_spr, fb->frame_tex, sfTrue);
    return fb;
}

static particles_t *init_particles(void)
{
    particles_t *particles = malloc(sizeof(particles_t));

    if (!particles)
        return NULL;
    particles->active_particles = 0;
    particles->particle_clock = sfClock_create();
    for (int i = 0; i < 100; i++) {
        particles->blood_particles[i].active = 0;
    }
    return particles;
}

static int init_app_window(app_t *app)
{
    app->window = init_window();
    if (!app->window)
        return -1;
    app->win_w = SCR_W;
    app->win_h = SCR_H;
    app->fullscreen = 0;
    return 0;
}

static int init_app_variable(app_t *app)
{
    app->fire = 0;
    app->g = NULL;
    app->menu = NULL;
    app->victory = NULL;
    app->wall_textures = NULL;
    app->crosshair = NULL;
    app->fb = NULL;
    app->particles = NULL;
    app->move_clk = NULL;
    if (init_app_window(app) == -1) {
        free(app);
        return -1;
    }
    app->font = sfFont_createFromFile(ARIAL_FONT);
    if (!app->font) {
        sfRenderWindow_destroy(app->window);
        free(app);
        return -1;
    }
    return 0;
}

app_t *init_application(void)
{
    app_t *app = malloc(sizeof(app_t));

    if (app == NULL)
        return NULL;
    if (init_app_variable(app) == -1)
        return NULL;
    app->menu = init_menu_struct();
    app->wall_textures = init_wall_textures();
    app->crosshair = init_crosshair();
    app->fb = init_framebuffer();
    app->particles = init_particles();
    app->victory = init_victory_struct(app->font);
    app->move_clk = sfClock_create();
    if (init_game(app) == -1) {
        free_app(app);
        return NULL;
    }
    return app;
}
