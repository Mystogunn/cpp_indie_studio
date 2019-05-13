/*
** EPITECH PROJECT, 2022
** test
** File description:
** Created by dany,
*/

#include "../include/core.hpp"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

CCore::CCore()
{
	device = createDevice(video::EDT_OPENGL,
		dimension2d<u32>(1920, 1080), 16, false, true, true, 0);
	device->setWindowCaption(L"Indie Studio");
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();
	driver->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT, true);
	// key pour player 1
	keybindPlayer1["FORWARD"] = irr::KEY_KEY_Z;
	keybindPlayer1["BACKWARD"] = irr::KEY_KEY_S;
	keybindPlayer1["LEFT"] = irr::KEY_KEY_Q;
	keybindPlayer1["RIGHT"] = irr::KEY_KEY_D;
	keybindPlayer1["ATTACK"] = irr::KEY_KEY_E;
	// key pour player 2
	keybindPlayer2["FORWARD"] = irr::KEY_KEY_O;
	keybindPlayer2["BACKWARD"] = irr::KEY_KEY_L;
	keybindPlayer2["LEFT"] = irr::KEY_KEY_K;
	keybindPlayer2["RIGHT"] = irr::KEY_KEY_M;
	keybindPlayer2["ATTACK"] = irr::KEY_KEY_P;
	// key pour menu
	keybindMenu["UP"] = irr::KEY_UP;
	keybindMenu["DOWN"] = irr::KEY_DOWN;
	keybindMenu["RIGHT"] = irr::KEY_RIGHT;
	keybindMenu["LEFT"] = irr::KEY_LEFT;
	keybindMenu["ENTER"] = irr::KEY_RETURN;
	keybindMenu["SPACE"] = irr::KEY_SPACE;
	keybindMenu["PAUSE"] = irr::KEY_ESCAPE;
	gameloaded = false;
	sound = new CSound();
}

void CCore::loader()
{
	//
	CBox *palm1 = new CBox(device, driver, smgr, vector3df(-20, 0, 20), CBox::EBoxType::PALMTREE, std::pair<u32, u32>(0, 0), sound);
	CBox *palm2 = new CBox(device, driver, smgr, vector3df(24*18 + 20, 0, 20), CBox::EBoxType::PALMTREE, std::pair<u32, u32>(0, 0), sound);
	CBox *palm3 = new CBox(device, driver, smgr, vector3df(-20, 0, (24*12) * -1 - 20), CBox::EBoxType::PALMTREE, std::pair<u32, u32>(0, 0), sound);
	CBox *palm4 = new CBox(device, driver, smgr, vector3df(24*18 + 20, 0, (24*12) * -1 - 20), CBox::EBoxType::PALMTREE, std::pair<u32, u32>(0, 0), sound);
	//
	ICameraSceneNode* cam= smgr->addCameraSceneNode(0, vector3df(213, 320, -290), vector3df(213,0,-156));
	cam->bindTargetAndRotation(true);
	irr::scene::ITerrainSceneNode *terrain = smgr->addTerrainSceneNode("assets/menu/h-map.bmp");
	terrain->setMaterialFlag(video::EMF_LIGHTING, true);
	terrain->setMaterialTexture(0, driver->getTexture("assets/terrain/pelouse.jpg"));
	terrain->scaleTexture(10.0f, 10.0f);
	terrain->setScale(vector3df(13.0f, 13.0f, 13.0f));
	terrain->setPosition(vector3df(-1300,0,-1500));
	smgr->setAmbientLight(video::SColor(0,250,250,250));
	ILightSceneNode *light = smgr->addLightSceneNode (0, irr::core::vector3df(380, 380, -370), irr::video::SColorf(0.4f,0.4f,0.6f,0.0f), 4000.0f);
	//ILightSceneNode *light = smgr->addLightSceneNode (0, irr::core::vector3df(0, 500, 0), irr::video::SColorf(0.4f,0.4f,0.6f,0.0f), 4000.0f);
		//light->getLightData().SpecularColor = irr::video::SColorf(0.2f,1.f,0.f,0.1f);
	menu = new CMenu(driver, device, guienv, smgr, sound);
	timer = new CTimer(device);
}

void CCore::run()
{
	CEventReceiver receiver(character1, character2, map, device, menu, driver, smgr);
	device->setEventReceiver(&receiver);
	while(device->run() && menu->quit == false)
	{
		const s32 fps = driver->getFPS();
		core::stringw str = L"Indie Studio [";
		str += driver->getName();
		str += "] FPS:";
		str += fps;
		device->setWindowCaption(str.c_str());
		// Draw
		// MaJ
		std::cout << "0" << std::endl;
		receiver.majMenu(menu, keybindMenu, timer->getTimeFactor());
		std::cout << "1" << std::endl;
		if (menu->restart == false)
		{
			if (menu->getEnabled() == false && menu->pause == false)
			{
				std::cout << "2" << std::endl;
					timer->update();
				std::cout << "2" << std::endl;
					if (!character1->isDead)
						receiver.majPosMesh(character1, keybindPlayer1, timer->getTimeFactor(), game);
				std::cout << "3" << std::endl;
					if (!character2->isDead)
						receiver.majPosMesh(character2, keybindPlayer2, timer->getTimeFactor(), game);
				std::cout << "4" << std::endl;
					game->update(map);
			}
		}
		else if (menu->restart == true && menu->restartok) {
			std::cout << "5" << std::endl;
				menu->restart = false;
				menu->restartok = false;
				map = menu->map;
				map->sound = sound;
				character1 = menu->character1;
				character2 = menu->character2;
				timer->update();
				game = new CGame(device, driver, smgr, map,
					character1, character2, timer);
				game->timer->reset();
				game->sound = sound;
				receiver.setMap(map);
		}
		std::cout << "6" << std::endl;
		timer->reset();
		// Fin Maj
		smgr->drawAll();
		guienv->drawAll();
		menu->menuhandler();
		driver->endScene();
		driver->beginScene(true, true, SColor(255,100,101,140));
	}
}

void CCore::close()
{
	device->drop();
}
