/*
** EPITECH PROJECT, 2022
** test
** File description:
** Created by dany,
*/
#ifndef TEST_CCHARACTER_HPP
#define TEST_CCHARACTER_HPP

#include "/usr/local/include/irr/irrlicht.h"
#include "../include/CTimer.hpp"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

const f32 MOVEMENT_SPEED = 50.f;

class CCharacter {
	public:
	enum EState {WALK, IDLE, ATTACK};
	enum EPlayer {PLAYERONE, PLAYERTWO, BOTTWO, BOTTHREE, BOTFOUR};
	public:
	CCharacter(IrrlichtDevice *device, IVideoDriver *driver, ISceneManager *smgr, const char *pathmesh, const char *pathtext, vector3df pos);
	IAnimatedMesh			*getmesh();
	IAnimatedMeshSceneNode	 	*getnode();
	void				setState(EState);
	CCharacter::EState		getState();
	void 				OnAnimationEnd(IAnimatedMeshSceneNode* node);
	void				idle();
	void				walk();
	void				attack();
	CTimer				*bombTimer;
	CTimer				*bonusSpeedTimer;
	bool				isDead;
	bool				bonusSpeed;
	private:
	EState 				state;
	IAnimatedMesh			*mesh;
	IAnimatedMeshSceneNode		*node;
};

#endif //TEST_CCHARACTER_HPP
