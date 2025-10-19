#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <spdlog/spdlog.h>

using namespace std;

class Window {
private:
    GLFWwindow* _window;

    int    _width;
    int    _height;
    string _title;

    shared_ptr<spdlog::logger> _log;
public:
    Window(shared_ptr<spdlog::logger> log);
    ~Window();

    bool Init(int width, int height, string title);
    void Refresh();

    void ChangeBackgroundColor(int r, int g, int b);

    bool IsOpened();

    int    width();
    int    height();
    string title();
    GLFWwindow* native_window();
};