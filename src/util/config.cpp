#include "config.h"

#include <nlohmann/json.hpp>
#include <fstream>

using namespace nlohmann;
using namespace std;

Config::Config(shared_ptr<spdlog::logger> log) {
    _log = log;
}

bool Config::Init(string path) {
    _path = path;

    ifstream file(_path);

    if (!file.is_open()) {
        _log->critical("failed to open configuration file: {0}", _path);
        return false;
    }
    _log->trace("opened config file from {0}", _path);

    json cfg;
    try {
        file >> cfg;
    } catch (const json::parse_error& e) {
        _log->critical("failed to parse {0}: {1}", _path, e.what());
        return false;
    }

    try {
        _window_width      = cfg.at("window").at("resolution")[0];
        _window_height     = cfg.at("window").at("resolution")[1];
        _window_fullscreen = cfg.at("window").at("fullscreen");
    } catch (const json::out_of_range& e) {
        _log->critical("failed to parse {0}: {1}", _path, e.what());
        return false;
    }
    _log->trace("parsed config file from JSON");

    file.close();
    return true;
}

int Config::window_height() {
    return _window_height;
}

int Config::window_width() {
    return _window_width;
}

bool Config::window_fullscreen() {
    return _window_fullscreen;
}