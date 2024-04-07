#include "stdio.h"
#include "SDL2/SDL.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "SDL2/SDL_thread.h"
#include "demos/widgets/lv_demo_widgets.h"


static SDL_Thread *g_tickThread = NULL;

static int TickThread(void *data);
static void PlayDemo(void);

int main(int argc, char *argv[])
{
    SDL_Event event;
    int32_t ret;
    bool running = true;

    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();
    g_tickThread = SDL_CreateThread(TickThread, "tick_thread", NULL);
    PlayDemo();
    while (running) {
        ret = SDL_PollEvent(&event);
        if (ret != 0) {
            switch (event.type) {
            case SDL_QUIT:
                running = 0;
                break;
            case SDL_MOUSEMOTION:
                SetTouchXY(event.motion.x, event.motion.y);
                break;
            case SDL_MOUSEBUTTONDOWN:
                SetTouchPressed(true);
                break;
            case SDL_MOUSEBUTTONUP:
                SetTouchPressed(false);
                break;
            default:
                break;
            }
        }
        lv_timer_handler();
        SDL_Delay(10);
    }
    return 0;
}



static int TickThread(void *data)
{
    while (1) {
        lv_tick_inc(5);
        SDL_Delay(5);
    }
    return 0;
}


static void PlayDemo(void)
{
#if LV_USE_DEMO_BENCHMARK
    lv_demo_benchmark();
#elif LV_USE_DEMO_KEYPAD_AND_ENCODER
    lv_demo_keypad_encoder();
#elif LV_USE_DEMO_WIDGETS
    lv_demo_widgets();
#elif LV_USE_DEMO_RENDER
    lv_demo_render(LV_DEMO_RENDER_SCENE_IMAGE_NORMAL, LV_OPA_50);
#elif LV_USE_DEMO_STRESS
    lv_demo_stress();
#elif LV_USE_DEMO_MUSIC
    lv_demo_music();
#elif LV_USE_DEMO_FLEX_LAYOUT
    lv_demo_flex_layout();
#elif LV_USE_DEMO_TRANSFORM
    lv_demo_transform();
#elif LV_USE_DEMO_MULTILANG
    lv_demo_multilang();
#elif LV_USE_DEMO_SCROLL
    lv_demo_scroll();
#elif LV_USE_DEMO_VECTOR_GRAPHIC
    lv_demo_vector_graphic();
#else
    #error "no demo played"
#endif
}

