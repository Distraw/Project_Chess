#include "program.h"

Program::Program(shared_ptr<spdlog::logger> log) {
    _log = log;
}

Program::~Program() {
    if (!_program) {
        _log->error("attempted to delete non-existent shader program");
        return;
    }

    _log->trace("deleting shader program {0}...", _program);
    glDeleteProgram(_program);
}

bool Program::Init(GLuint vertex_shader, GLuint fragment_shader) {
    if (!vertex_shader) {
        _log->critical("vertex shader was not initialized before passing to program {0}", _program);
        return false;
    }

    if (!fragment_shader) {
        _log->critical("fragment shader was not initialized before passing to program {0}", _program);
        return false;
    }

    _program = glCreateProgram();
    _log->trace("created shader program {0}", _program);

    glAttachShader(_program, vertex_shader);
    glAttachShader(_program, fragment_shader);
    _log->trace("attached vertex shader {0} and fragment shader {1} to shader program {2}", 
        vertex_shader, fragment_shader, _program);

    glLinkProgram(_program);

    GLint ok;
    glGetProgramiv(_program, GL_LINK_STATUS, &ok);
    if (!ok) {
        GLchar infolog[1024];
		glGetProgramInfoLog(_program, 1024, NULL, infolog);
        _log->critical("failed to link program: {0}", string(infolog));
        return false;
    }
    _log->trace("linked shader program {0}", _program);

    return true;
}

void Program::Use(bool state) {
    glUseProgram(state ? _program : 0);
}

GLuint Program::native_program() {
    return _program;
}