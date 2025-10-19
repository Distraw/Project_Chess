#include "shader.h"

#include <fstream>

Shader::Shader(shared_ptr<spdlog::logger> log) {
    _log = log;
}

Shader::~Shader() {
    Unload();
}

bool Shader::Load(string path, GLenum type) {
    _type = type;

    _log->trace("opening {0}...", path);
    ifstream file(path);
	if (!file.is_open()) {
        _log->critical("failed to open {0}", path);
        return false;
	}

	stringstream buffer;
	buffer << file.rdbuf();
	_source = buffer.str();

	_shader = glCreateShader(_type);

    _log->trace("compiling shader from {0}...", path);
	const char* cc_source = _source.c_str();
	glShaderSource(_shader, 1, &cc_source, nullptr);
	glCompileShader(_shader);

	int ok;
	glGetShaderiv(_shader, GL_COMPILE_STATUS, &ok);
	if (!ok) {
		char infolog[1024];
		glGetShaderInfoLog(_shader, 1024, NULL, infolog);
        _log->critical("failed to compile shader: {0}", string(infolog));
        return false;
	}

    file.close();
    return true;
}

void Shader::Unload() {
    if (!_shader) {
        _log->trace("deleting shader {0}...", _shader);
        glDeleteShader(_shader);
    }
}

GLuint Shader::native_shader() {
    return _shader;
}