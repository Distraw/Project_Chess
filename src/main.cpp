#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "util/config.h"

int main() {
    auto log = spdlog::stdout_color_mt("stdout");

    Config config(log);
    if (!config.Init("./settings.json")) {
        log->critical("failed to initialize config");
        return -1;
    }

    if (glfwInit() == GLFW_FALSE) {
        log->error("failed to initialize GLFW");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    log->info("MacOS is detected");
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(config.window_width(), config.window_height(), "Distraw Chess", 
                                            config.window_fullscreen() == true ? glfwGetPrimaryMonitor() : NULL, NULL);
    if (window == NULL) {
        log->error("failed to create window");
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        log->error("failed to initialize GLAD");
        return -1;
    }

    glClearColor(1, 1, 1, 0);
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    log->info("terminating GLFW and exiting application");
    return 0;
}