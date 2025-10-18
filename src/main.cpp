#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "core/window.h"
#include "util/config.h"

int main() {
    auto log = spdlog::stdout_color_mt("stdout");

    Config config(log);
    if (!config.Init("./settings.json")) {
        log->critical("failed to initialize config");
        return -1;
    }

    Window window(log);
    if (!window.Init(config.window_width(), config.window_height(), "Distraw Chess")) {
        log->critical("failed to open window");
    }

    window.ChangeBackgroundColor(0, 0, 0);
    while (window.IsOpened()) {
        window.Refresh();
        glfwPollEvents();
    }

    glfwTerminate();
    log->info("terminating GLFW and exiting application");
    return 0;
}