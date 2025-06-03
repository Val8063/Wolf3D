/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-valentin.rueda
** File description:
** struct_wolf.h
*/

#include "lib.h"

#ifndef STRUCT_WOLF
    #define STRUCT_WOLF

typedef struct {
    sfSound *s;
    sfSoundBuffer *buf;
} snd_t;

typedef struct {
    float x, y;
    float vx, vy;
    float lifespan;
    int active;
} blood_particle_t;

typedef struct {
    sfTexture *tex;
    sfSprite *spr;
    int cur_weapon;
    int anim_frame;
    int firing;
    int fire_frame;
    sfClock *anim_clk;
    snd_t pistol_snd;
    snd_t knife_snd;
} weapon_t;

typedef struct {
    sfTexture *fill_heart;
    sfTexture *empty_heart;
    sfSprite *heart1;
    sfSprite *heart2;
    sfSprite *heart3;
} life_t;

typedef struct {
    sfTexture *tex;
    sfSprite *sp;
    life_t *life;
    sfText *ammo;
    sfText *score;
    sfText *e_left;
    sfFont *font;
    sfRectangleShape *flashlight_icon;
    sfText *flashlight_text;
} hud_t;

typedef struct {
    float x, y;
    float dx, dy;
    float planeX, planeY;
    float speed;
    int life;
    weapon_t *w;
    int score;
    float light_intensity;
    int flashlight_on;
} player_t;

typedef struct enemy_s {
    float x;
    float y;
    int alive;
    float transformX;
    float transformY;
    int screenX;
    int screenY;
    int width;
    int height;
    int render;
    sfSprite *sprite;
    sfTexture *texture;
} enemy_t;

typedef struct {
    player_t *p;
    enemy_t *enemies;
    int enemy_count;
    int enemies_alive;
    int **map;
    float snd_efct_vol;
    hud_t *hud;
} game_t;

typedef struct {
    sfSprite *menu_spr;
    sfTexture *menu_tex;
    sfRectangleShape *settings_bg;
    sfRectangleShape *settings_btn[4];
    sfText *settings_txt[4];
    int show_menu;
    int show_settings;
} menu_t;

typedef struct {
    sfRectangleShape *bg;
    sfText *victory_text;
    int show_victory;
} victory_screen_t;

typedef struct {
    sfImage *wall_img;
    sfTexture *wall_tex;
} wall_textures_t;

typedef struct {
    sfTexture *cross_tex;
    sfSprite *cross_spr;
} crosshair_t;

typedef struct {
    sfImage *fb;
    sfTexture *frame_tex;
    sfSprite *frame_spr;
} framebuffer_t;

typedef struct {
    blood_particle_t blood_particles[100];
    int active_particles;
    sfClock *particle_clock;
} particles_t;

typedef struct {
    int fire;
    int win_w;
    int win_h;
    int fullscreen;
    sfEvent evt;
    game_t *g;
    sfFont *font;
    sfRenderWindow *window;
    menu_t *menu;
    victory_screen_t *victory;
    wall_textures_t *wall_textures;
    crosshair_t *crosshair;
    framebuffer_t *fb;
    particles_t *particles;
    sfClock *move_clk;
} app_t;

typedef struct {
    float ray_dir[2];
    float side_dist[2];
    float wall_dist[2];
    int step[2];
    int map_pos[2];
    int **map;
    player_t *player;
} raycast_data_t;

typedef struct {
    sfRenderWindow *window;
    sfRectangleShape *column;
    float perp_wall_dist;
    int x;
    int side;
    int texX;
    int texY;
    int draw_start;
    int draw_end;
    int y;
    int d;
    float ray_dir[2];
} draw_context_t;

#endif
