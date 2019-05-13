/*
** EPITECH PROJECT, 2022
** test
** File description:
** Created by dany,
*/

#ifndef TEST_CEVENTRECEIVER_HPP
#define TEST_CEVENTRECEIVER_HPP

#include <iostream>
#include <map>
#include "/usr/local/include/irr/irrlicht.h"
#include "CCharacter.hpp"
#include "CMenu.hpp"
#include "CMap.hpp"
#include "CGame.hpp"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


class CEventReceiver : public irr::IEventReceiver
{
	public :
	// Send direction to CMap::isAvailableSpace
	enum EDirCollision {DOWNN, UP, RIGHT, LEFT};
	CEventReceiver(CCharacter *character, CCharacter *character2, CMap *map, IrrlichtDevice *ddevice, CMenu *mmenu, IVideoDriver *ddriver, ISceneManager *ssmgr);

	virtual bool 	OnEvent(const irr::SEvent &event);
	bool 		IsKeyDown(irr::EKEY_CODE keyCode);
	void 		majPosMesh(CCharacter*, std::map<std::string, EKEY_CODE>, f32, CGame*);
	void 		majMenu(CMenu *, std::map<std::string, EKEY_CODE>, f32);
	void		setMap(CMap*);
	private :
	IVideoDriver 				*driver;
	ISceneManager				*smgr;
	CMenu 					*menu;
	IrrlichtDevice				*device;
	CMap					*mmap;
	irr::scene::IAnimatedMeshSceneNode	*m_Nmodele;
	bool					KeyIsDown[KEY_KEY_CODES_COUNT];
};

#endif //TEST_CEVENTRECEIVER_HPP
