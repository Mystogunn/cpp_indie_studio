/*
** EPITECH PROJECT, 2022
** test
** File description:
** Created by dany,
*/
#ifndef TEST_CORE_HPP
#define TEST_CORE_HPP

#include <iostream>
#include <map>
#include <time.h>
#include "/usr/local/include/irr/irrlicht.h"
#include "../include/CCharacter.hpp"
#include "../include/CEventReceiver.hpp"
#include "../include/CMenu.hpp"
#include "../include/CTimer.hpp"
#include "../include/CBox.hpp"
#include "../include/CMap.hpp"
#include "../include/CGame.hpp"
#include "../include/CSound.hpp"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class CCore
{
	public:
	CCore();
	void			loader();
	void			run();
	void			close();
	private:
	CSound			*sound;
	std::map<std::string, EKEY_CODE> keybindPlayer1;
	std::map<std::string, EKEY_CODE> keybindPlayer2;
	std::map<std::string, EKEY_CODE> keybindMenu;
	CCharacter		*character1;
	CCharacter		*character2;
	CCharacter		*character3;
	CCharacter		*character4;
	CMenu			*menu;
	CTimer			*timer;
	CMap			*map;
	CGame			*game;
	IrrlichtDevice		*device;
	IGUIEnvironment		*guienv;
	IVideoDriver		*driver;
	ISceneManager		*smgr;
	bool			gameloaded;
};
#endif //TEST_CORE_HPP
