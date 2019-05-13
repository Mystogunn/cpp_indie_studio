/*
** EPITECH PROJECT, 2022
** test
** File description:
** Created by elias,
*/
#ifndef CGAME_HPP
#define CGAME_HPP

#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#include "../include/CMap.hpp"
#include "../include/CCharacter.hpp"
#include "../include/CTimer.hpp"
#include "../include/CBox.hpp"
#include "/usr/local/include/irr/irrlicht.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class CGame
{
    public:
	CGame(IrrlichtDevice *, IVideoDriver *, ISceneManager *, CMap *, CCharacter *, CCharacter *, CTimer*);
	void				update(CMap*);
	void 				updateBombStack();
	void				updateExplosionStack();
	int				updateBomb(CBox *);
	int				updateExplosion(CBox *);
	void				updateBonus();
	void				addBomb(vector3df);
	void				addExplosion(vector3df);
	void				addXExplosion(vector3df);
	CTimer 				*timer;
	CSound				*sound;
    private:
	IrrlichtDevice			*device;
	IVideoDriver			*driver;
	ISceneManager			*smgr;
	CMap				*map;
	CCharacter			*char1;
	CCharacter			*char2;
	std::vector<CBox*>		bomb_stack;
	std::vector<CBox*>		explosion_stack;
    	std::vector<CBox*>		player_life_stack;
    	std::pair<u32,u32>		keypos_temp;
    	vector3df			pos_temp;
};

#endif //CGAME_HPP
