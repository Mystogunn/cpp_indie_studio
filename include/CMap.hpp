/*
** EPITECH PROJECT, 2022
** test
** File description:
** Created by elias,
*/

#ifndef CMAP_HPP
#define CMAP_HPP

#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include "/usr/local/include/irr/irrlicht.h"
#include "../include/CBox.hpp"
#include "../include/CCharacter.hpp"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class CMap
{
	public:
	enum EBoxType {EMPTY, CHARACTER, BOX, UBOX, BOMB, BONUS, EXPLOSION};
	enum EBoxState {UNBROKEN, EXPLODED, WALL};
	public:
	CMap(IrrlichtDevice *ddevice, IVideoDriver *ddriver, ISceneManager *ssmgr);
	void					clear();
	bool					isSaveAvailable;
	CBox::EBoxType				isAvailableSpace(vector3df v, vector3df vold);
	void					setMap(std::pair<u32, u32>, CBox *);
	CBox					*getCBox(std::pair<u32,u32> key);
	bool 					loaderProcedural();
	bool 					loaderSave();
	void					saveMap();
	CSound					*sound;
	private:
	IrrlichtDevice 				*device;
	IVideoDriver 				*driver;
	ISceneManager				*smgr;
	std::map<std::pair<u32, u32>, CBox *>	bm_map;
	EBoxState				state;
	std::pair<u32, u32>			pos;
	std::ifstream				ifs;
	std::string				buffer;
	f32					tmp_x;
	f32					tmp_y;
	f32					tmp_z;
	u32					x;
	u32					y;
};

#endif //TEST_CORE_HPP