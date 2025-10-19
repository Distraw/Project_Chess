#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "core/window.h"
#include "core/shader.h"
#include "core/program.h"
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
        return -1;
    }

    Shader vertex_shader(log);
    if (!vertex_shader.Load("./shader/vertex.glsl", GL_VERTEX_SHADER)) {
        log->critical("failed to load vertex shader");
        return -1;
    }

    Shader fragment_shader(log);
    if (!fragment_shader.Load("./shader/fragment.glsl", GL_FRAGMENT_SHADER)) {
        log->critical("failed to load fragment shader");
        return -1;
    }

    Program program(log);
    if (!program.Init(vertex_shader.native_shader(), fragment_shader.native_shader())) {
        log->critical("failed to load program");
        return -1;
    }

    program.Use();
    vertex_shader.Unload();
    fragment_shader.Unload();

    GLfloat triangle[6]{
        -0.5f, -0.5f,
        0.f, 0.5f,
        0.5f, -0.5f
    };

    //
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //

    window.ChangeBackgroundColor(0, 0, 0);
    while (window.IsOpened()) {
        window.Refresh();
        glfwPollEvents();

        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    return 0;
}