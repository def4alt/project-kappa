#define IMGUI_IMPL_OPENGL_LOADER_GLEW

#include <SDL.h>
#include <imgui/imgui.h>
#include "logger.h"
#include "game.h"

#undef main

int main() {
    logger::start_log("log.txt");

    auto *game =
            new Game("Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                    1920, 1080, false);

    while (game->is_running) {
        game->handle_events();

        game->update(1000 / ImGui::GetIO().Framerate);
        game->render();
        game->imgui_render();

        SDL_GL_SwapWindow(game->window);
    }

    delete game;

    return 0;
}
