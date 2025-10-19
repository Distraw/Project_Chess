#include "program.h"

Program::Program(shared_ptr<spdlog::logger> log) {
    _log = log;
}

Program::~Program() {
    if (!_program) {
        _log->trace("deleting program {0}...", _program);
        glDeleteProgram(_program);
    }
}

bool Program::Init(GLuint vertex_shader, GLuint fragment_shader) {
    if (!vertex_shader) {
        _log->critical("vertex shader was not initialized before passing to program");
        return false;
    }

    if (!fragment_shader) {
        _log->critical("fragment shader was not initialized before passing to program");
        return false;
    }

    _program = glCreateProgram();
    glAttachShader(_program, vertex_shader);
    glAttachShader(_program, fragment_shader);
    glLinkProgram(_program);

    int ok;
    glGetProgramiv(_program, GL_LINK_STATUS, &ok);
    if (!ok) {
        char infolog[1024];
		glGetProgramInfoLog(_program, 1024, NULL, infolog);
        _log->critical("failed to link program: {0}", string(infolog));
        return false;
    }

    return true;
}

void Program::Use() {
    glUseProgram(_program);
}

GLuint Program::native_program() {
    return _program;
}