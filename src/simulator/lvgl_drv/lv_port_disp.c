/**
 * @file lv_port_disp_templ.c
 *
 */

/*Copy this file as "lv_port_disp.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_disp.h"
#include <stdbool.h>
#include "SDL2/SDL.h"

/*********************
 *      DEFINES
 *********************/
#ifndef MY_DISP_HOR_RES
#warning Please define or replace the macro MY_DISP_HOR_RES with the actual screen width, default value 320 is used for now.
#define MY_DISP_HOR_RES    320
#endif

#ifndef MY_DISP_VER_RES
#warning Please define or replace the macro MY_DISP_HOR_RES with the actual screen height, default value 240 is used for now.
#define MY_DISP_VER_RES    240
#endif

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void disp_init(void);

static void disp_flush(lv_display_t * disp, const lv_area_t * area, uint8_t * px_map);

/**********************
 *  STATIC VARIABLES
 **********************/

SDL_Window *g_window = NULL;
SDL_Renderer *g_renderer = NULL;
SDL_Texture *g_texture = NULL;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_disp_init(void)
{
    /*-------------------------
     * Initialize your display
     * -----------------------*/
    disp_init();

    /*------------------------------------
     * Create a display and set a flush_cb
     * -----------------------------------*/
    lv_display_t * disp = lv_display_create(MY_DISP_HOR_RES, MY_DISP_VER_RES);
    lv_display_set_flush_cb(disp, disp_flush);

    /* Example 1
     * One buffer for partial rendering*/
    static lv_color_t buf_1_1[MY_DISP_HOR_RES * MY_DISP_VER_RES];               /*full screen buffer*/
    lv_display_set_buffers(disp, buf_1_1, NULL, sizeof(buf_1_1), LV_DISPLAY_RENDER_MODE_PARTIAL);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*Initialize your display and the required peripherals.*/
static void disp_init(void)
{
    int ret;
    ret = SDL_InitSubSystem(SDL_INIT_VIDEO);
    if (ret != 0) {
        printf("SDL init err:%d\n", ret);
    }
    g_window = SDL_CreateWindow("lvgl-sdl",
                                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                MY_DISP_HOR_RES, MY_DISP_VER_RES, 0);
    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_SOFTWARE);
    g_texture = SDL_CreateTexture(g_renderer,
                                  (LV_COLOR_DEPTH == 32) ? (SDL_PIXELFORMAT_ARGB8888) : (SDL_PIXELFORMAT_RGB565),
                                  SDL_TEXTUREACCESS_STREAMING,
                                  MY_DISP_HOR_RES,
                                  MY_DISP_VER_RES);
}

volatile bool disp_flush_enabled = true;

/* Enable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_enable_update(void)
{
    disp_flush_enabled = true;
}

/* Disable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_disable_update(void)
{
    disp_flush_enabled = false;
}

/*Flush the content of the internal buffer the specific area on the display.
 *`px_map` contains the rendered image as raw pixel map and it should be copied to `area` on the display.
 *You can use DMA or any hardware acceleration to do this operation in the background but
 *'lv_display_flush_ready()' has to be called when it's finished.*/
static void disp_flush(lv_display_t * disp_drv, const lv_area_t * area, uint8_t * px_map)
{
    SDL_Rect r;
    if (disp_flush_enabled) {
        r.x = area->x1;
        r.y = area->y1;
        r.w = area->x2 - area->x1 + 1;
        r.h = area->y2 - area->y1 + 1;
        SDL_UpdateTexture(g_texture, &r, px_map, r.w * ((LV_COLOR_DEPTH + 7) / 8));
        SDL_RenderCopy(g_renderer, g_texture, NULL, NULL);
        SDL_RenderPresent(g_renderer);
    }

    /*IMPORTANT!!!
     *Inform the graphics library that you are ready with the flushing*/
    lv_display_flush_ready(disp_drv);
}

#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
