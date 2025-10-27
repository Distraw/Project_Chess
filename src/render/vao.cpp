#include "vao.h"

VAO::VAO(shared_ptr<spdlog::logger> log) {
    _log = log;
}

VAO::~VAO() {
    glDeleteVertexArrays(1, &_vao);
}

void VAO::Init() {
    _log->trace("initializing vertex array object...");
    glGenVertexArrays(1, &_vao);
}

void VAO::Attach(GLuint vbo, GLuint index) {
    glBindVertexArray(_vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(index, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(index);

    glBindVertexArray(0);
}

void VAO::Use(bool state) {
    glBindVertexArray(state ? _vao : 0);
}

GLuint VAO::native_vao() {
    return _vao;
}