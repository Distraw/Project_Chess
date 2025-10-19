#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <spdlog/spdlog.h>

using namespace std;

class Program {
private:
    GLuint _program;

    shared_ptr<spdlog::logger> _log;
public:
    Program(shared_ptr<spdlog::logger> log);
    ~Program();

    bool Init(GLuint vertex_shader, GLuint fragment_shader);

    void Use();

    GLuint native_program();
};