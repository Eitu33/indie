#include "MapDisplayer.hpp"

int main(void)
{
    MapDisplayer mapDisplayer;
    
    irr::IrrlichtDevice * device = irr::createDevice(irr::video::EDT_OPENGL,irr::core::dimension2d<irr::u32>(800, 600), 32, false, false, false, 0);	
    irr::video::IVideoDriver *driver = device->getVideoDriver();	
    irr::scene::ISceneManager *sceneManager = device->getSceneManager();		
    irr::SKeyMap keyMap[5];
	
    keyMap[0].Action = irr::EKA_MOVE_FORWARD;	
    keyMap[0].KeyCode = irr::KEY_KEY_Z;	
    keyMap[1].Action = irr::EKA_MOVE_BACKWARD;
    keyMap[1].KeyCode = irr::KEY_KEY_S;
    keyMap[2].Action = irr::EKA_STRAFE_LEFT;
    keyMap[2].KeyCode = irr::KEY_KEY_Q;
    keyMap[3].Action = irr::EKA_STRAFE_RIGHT;
    keyMap[3].KeyCode = irr::KEY_KEY_D;
    keyMap[4].Action = irr::EKA_JUMP_UP;
    keyMap[4].KeyCode = irr::KEY_SPACE;
    mapDisplayer.renderMap(device, driver, sceneManager);
    sceneManager->addCameraSceneNodeFPS(0, 100.0f, 0.1f, -1, keyMap, 5);
    while(device->run()) {
        driver->beginScene (true, true, irr::video::SColor(255,255,255,255));
        sceneManager->drawAll();
        driver->endScene();
    }
}
