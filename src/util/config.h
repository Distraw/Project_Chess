#include <string>

#include <spdlog/spdlog.h>

using namespace std;

class Config {
private:
    string _path;

    int  _window_width;
    int  _window_height;
    bool _window_fullscreen;
    
    shared_ptr<spdlog::logger> _log;
public:
    Config(shared_ptr<spdlog::logger> log);

    bool Init(string path);

    int  window_height();
    int  window_width();
    bool window_fullscreen();
};