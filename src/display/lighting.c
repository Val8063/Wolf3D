/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-valentin.rueda
** File description:
** lighting.c
*/

#include "wolf.h"

float calculate_light_intensity(float distance,
    float player_light, int flashlight_on)
{
    float intensity = 0.0f;

    if (flashlight_on) {
        intensity = 1.0f - (distance / (MAX_VISIBILITY * 2.0f)) * 0.3f;
        intensity = fmaxf(0.7f, intensity);
    } else {
        intensity = MIN_LIGHT_LEVEL + 0.1f;
    }
    intensity *= player_light;
    intensity = fmaxf(MIN_LIGHT_LEVEL, fminf(intensity, 1.0f));
    return intensity;
}

sfColor apply_lighting(sfColor color, float light_intensity)
{
    sfColor result;
    float factor = light_intensity;

    factor = fmaxf(MIN_LIGHT_LEVEL, fminf(factor, 1.0f));
    result.r = (sfUint8)(color.r * factor);
    result.g = (sfUint8)(color.g * factor);
    result.b = (sfUint8)(color.b * factor);
    result.a = color.a;
    return result;
}
