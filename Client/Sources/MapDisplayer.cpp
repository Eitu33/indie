#include "MapDisplayer.hpp"

void MapDisplayer::renderMap(irr::IrrlichtDevice * device, irr::video::IVideoDriver *driver, irr::scene::ISceneManager *sceneManager) {
    for (int i = 0; i < 17; i++) {
        for (int j = 0; j < 12; j++) {
            irr::scene::IMeshSceneNode* plane = sceneManager->addCubeSceneNode(50.0f, 0, -1, irr::core::vector3df(j * 50.0f, -50.0f, i * 50.0f));
            plane->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            plane->setMaterialTexture(0, driver->getTexture("grass.png"));
            this->_map.push_back(plane);
        }
    }
}
