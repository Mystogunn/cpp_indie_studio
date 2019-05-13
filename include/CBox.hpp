/*
** EPITECH PROJECT, 2022
** test
** File description:
** Created by dany,
*/
#ifndef TEST_CBOX_HPP
#define TEST_CBOX_HPP

#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include "/usr/local/include/irr/irrlicht.h"
#include "../include/CTimer.hpp"
#include "../include/CSound.hpp"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class CBox {
	public:
	enum EBoxType {EMPTY, BOX, UBOX, BOMB, BONUS, EXPLOSION, PALMTREE};
	enum EBoxState {UNBROKEN, EXPLODED, WALL};
	enum EParticleType {BOMBEXPLOSION, BOXEXPLOSION};
	public:
	CBox(IrrlichtDevice *ddevice, IVideoDriver *ddriver, ISceneManager *ssmgr, vector3df pos, CBox::EBoxType type, std::pair<u32, u32> kkeymappos, CSound *ssound);
	void				bomb(vector3df pos);
	void				palmtree(vector3df pos);
	void				box(vector3df pos);
	void				ubox(vector3df pos);
	void				bonus(vector3df pos);
	void				particle(vector3df pos, CBox::EParticleType type);
	//CBox(IrrlichtDevice *device, IVideoDriver *driver, ISceneManager *smgr, const char *pathmesh, const char *pathtext, vector3df pos);
	IAnimatedMesh			*getmesh();
	IAnimatedMeshSceneNode 		*getnode();
	void				setState(EBoxState);
	CBox::EBoxState			getState();
	CBox::EBoxType			getType();
	std::pair<u32, u32>		getKeyMapPos();
	CTimer				*getTimer();
	IParticleSystemSceneNode	*getParticleBox();
	bool				bombbool;
	bool				explosionbool;
	CSound				*sound;
	private:
	std::pair<u32, u32> 		keymappos;
	IrrlichtDevice 			*device;
	IVideoDriver 			*driver;
	ISceneManager			*smgr;
	EBoxState			state;
	EBoxType			ttype;
	IAnimatedMesh			*mesh;
	IAnimatedMeshSceneNode		*node;
	//particule
	IParticleSystemSceneNode	*particlebox;
	IParticleEmitter		*emitter;
	IParticleAffector		*affector;
	ISceneNodeAnimator 		*animator;
	CTimer				*timer;
};

#endif //TEST_CBOX_HPP