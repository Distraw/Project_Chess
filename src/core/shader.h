#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <spdlog/spdlog.h>

using namespace std;

class Shader {
private:
    string _source;
    GLuint _shader;
    GLenum _type;

    shared_ptr<spdlog::logger> _log;
public:
    Shader(shared_ptr<spdlog::logger> log);
    ~Shader();

    bool Load(string path, GLenum type);
    void Unload();

    GLuint native_shader();
};