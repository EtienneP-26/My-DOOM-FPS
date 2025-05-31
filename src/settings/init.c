/*
** EPITECH PROJECT, 2024
** My-DOOM FPS
** File description:
** init.c
*/

#include "settings.h"
#include "define.h"

static void init_title(SettingsScene_t *settings)
{
    settings->title->Text = create_text("Settings",
        FONT, 0, (sfVector2f){0, 0});
    settings->title->Text = create_text("Settings",
        FONT, 0, (sfVector2f){0, 0});
}

static void init_volume(SettingsScene_t *settings)
{
    char volumeStr[3];

    VOLUMEB = create_rectangle((sfVector2f){0, 0},
    (sfVector2f){0, 0}, sfColor_fromRGB(50, 50, 50));
    VOLUMET = create_text("Volume", FONT, 0, (sfVector2f){0, 0});
    MINUSVB = create_rectangle((sfVector2f){0, 0},
    (sfVector2f){0, 0}, sfColor_fromRGB(100, 100, 100));
    PLUSVB = create_rectangle((sfVector2f){0, 0},
    (sfVector2f){0, 0}, sfColor_fromRGB(100, 100, 100));
    VOLUME = 5;
    sprintf(volumeStr, "%d", VOLUME);
    VOLUMEN = create_text(volumeStr, FONT, 0, (sfVector2f){0, 0});
    PLUSVT = create_text("+", FONT, 0, (sfVector2f){0, 0});
    MINUSVT = create_text("-", FONT, 0, (sfVector2f){0, 0});
}

static void init_sensi(SettingsScene_t *settings)
{
    char sensiStr[3];

    SENSIB = create_rectangle((sfVector2f){0, 0},
    (sfVector2f){0, 0}, sfColor_fromRGB(50, 50, 50));
    SENSIT = create_text("Sensibility", FONT, 0, (sfVector2f){0, 0});
    MINUSSB = create_rectangle((sfVector2f){0, 0},
    (sfVector2f){0, 0}, sfColor_fromRGB(100, 100, 100));
    PLUSSB = create_rectangle((sfVector2f){0, 0},
    (sfVector2f){0, 0}, sfColor_fromRGB(100, 100, 100));
    SENSI = 5;
    sprintf(sensiStr, "%d", SENSI);
    SENSIN = create_text(sensiStr, FONT, 0, (sfVector2f){0, 0});
    PLUSST = create_text("+", FONT, 0, (sfVector2f){0, 0});
    MINUSST = create_text("-", FONT, 0, (sfVector2f){0, 0});
}

static void init_screen_case(SettingsScene_t *settings)
{
    SCREENB = create_rectangle((sfVector2f){0, 0},
    (sfVector2f){0, 0}, sfColor_fromRGB(50, 50, 50));
    SWINDOWB = create_rectangle((sfVector2f){0, 0},
    (sfVector2f){0, 0}, sfColor_fromRGB(100, 100, 100));
    SWINDOWT = create_text("1600x900", FONT, 0, (sfVector2f){0, 0});
    sfText_setColor(SWINDOWT, sfColor_fromRGB(10, 10, 10));
    FULLSCREENB = create_rectangle((sfVector2f){0, 0},
    (sfVector2f){0, 0}, sfColor_fromRGB(110, 110, 110));
    FULLSCREENT = create_text("Full screen", FONT, 0, (sfVector2f){0, 0});
    sfText_setColor(FULLSCREENT, sfColor_fromRGB(10, 10, 10));
    SCREENT = create_text("Size screen", FONT, 0, (sfVector2f){0, 0});
}

static void init_background(SettingsScene_t *settings)
{
    BACKGROUND = sfTexture_createFromFile
        ("./assets/images/menu/background_menu.png", NULL);
    BACKGROUNDSPRITE = sfSprite_create();
    sfSprite_setTexture(BACKGROUNDSPRITE, BACKGROUND, sfTrue);
    sfSprite_setPosition(BACKGROUNDSPRITE, (sfVector2f){0, 0});
    sfSprite_setScale(BACKGROUNDSPRITE, (sfVector2f){0, 0});
    TITLEB = create_rectangle((sfVector2f){0, 0},
    (sfVector2f){0, 0}, sfColor_fromRGB(50, 50, 50));
}

static void init_keys(SettingsScene_t *settings)
{
    settings->shoot = creat_key(settings,
        (sfVector2f){0, 0}, "Shoot", "Mouse L");
    settings->Forward = creat_key(settings,
        (sfVector2f){0, 0}, "Forward", "Z");
    settings->Backward = creat_key(settings,
        (sfVector2f){0, 0}, "Backward", "S");
    settings->Left = creat_key(settings,
        (sfVector2f){0, 0}, "Left", "Q");
    settings->Right = creat_key(settings,
        (sfVector2f){0, 0}, "Right", "D");
}

static void init_back(SettingsScene_t *settings)
{
    BACKB = create_rectangle((sfVector2f){0, 0},
    (sfVector2f){0, 0}, sfColor_fromRGB(20, 20, 20));
    BACKT = create_text("Exit", FONT, 0, (sfVector2f){0, 0});
}

static void intit_binding(SettingsScene_t *settings, scenebinding_t *bind)
{
    bind->slider = create_rectangle((sfVector2f){0, 0},
    (sfVector2f){0, 0}, sfColor_fromRGB(50, 50, 50));
    sfRectangleShape_setOutlineColor(bind->slider,
        sfColor_fromRGB(200, 200, 200));
    sfRectangleShape_setOutlineThickness(bind->slider, 5);
    bind->Text = create_text("Select your key :", FONT, 0, (sfVector2f){0, 0});
}

void init_settings_scene(SettingsScene_t *settings, sfRenderWindow *window)
{
    float ScF = 1.0f;

    malloc_settings_scene(settings);
    WINDOW = window;
    settings->goBack = false;
    settings->scenebinding->is_binding = false;
    settings->fullscreen_view = NULL;
    if (sfRenderWindow_getSize(WINDOW).x == 1920 &&
    sfRenderWindow_getSize(WINDOW).y == 945)
        ScF = 1.2f;
    FONT = sfFont_createFromFile("assets/fonts/videotype.ttf");
    init_title(settings);
    init_background(settings);
    init_volume(settings);
    init_sensi(settings);
    init_screen_case(settings);
    init_keys(settings);
    init_back(settings);
    intit_binding(settings, settings->scenebinding);
    resize_elements(settings, ScF);
}
