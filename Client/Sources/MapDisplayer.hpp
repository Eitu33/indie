#include <string>
#include <iostream>
#ifdef __linux__
#include <unistd.h>
#endif
#include <irrlicht.h>
#include <vector>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

class MapDisplayer {
    public:
        MapDisplayer() = default;
        ~MapDisplayer() = default;

        void renderMap(irr::IrrlichtDevice * device, irr::video::IVideoDriver *driver, irr::scene::ISceneManager *sceneManager);
    private:
        std::vector<irr::scene::IMeshSceneNode *> _map;

};