/*
** EPITECH PROJECT, 2022
** test
** File description:
** Created by dany,
*/

#include "../include/CCharacter.hpp"

CCharacter::CCharacter(IrrlichtDevice *device, IVideoDriver *driver,
	ISceneManager *smgr, const char *pathmesh, const char *pathtext, vector3df pos)
{
	mesh = smgr->getMesh(pathmesh);
	if (!mesh)
		device->drop();
	node = smgr->addAnimatedMeshSceneNode(mesh);
	if (node)
	{
		node->setMaterialFlag(EMF_LIGHTING, true);
		node->setMD2Animation(scene::EMAT_STAND);
		node->setMaterialTexture( 0, driver->getTexture(pathtext));
		node->setScale(vector3df(0.6f, 0.6f, 0.6f));
		node->addShadowVolumeSceneNode();
		node->setTransitionTime(0.0005);
		node->getMaterial(0).Shininess = 0.1f;
		node->getMaterial(0).Shininess = 0.0f;
		//node->setPosition(vector3df(30,0,-30));
		node->setPosition(vector3df(pos.X*24 + 6 ,0,pos.Z*-24-6));
//		node->setPosition(vector3df(-204,0,132));
		//node->setDebugDataVisible(irr::scene::EDS_BBOX);
	}
	bombTimer = new CTimer(device);
	bonusSpeedTimer = new CTimer(device);
	bombTimer->reset();
	state = IDLE;
	isDead = 0;
	bonusSpeed = false;
	idle();
}

IAnimatedMesh			*CCharacter::getmesh()
{
	return (mesh);
}

IAnimatedMeshSceneNode		*CCharacter::getnode()
{
	return (node);
}

void CCharacter::setState(CCharacter::EState newstate)
{
	state = newstate;
}

CCharacter::EState CCharacter::getState()
{
	return (state);
}

void CCharacter::OnAnimationEnd(IAnimatedMeshSceneNode *node)
{
	idle();
}

void CCharacter::idle()
{
	state = IDLE;
	node->setAnimationSpeed(10);
	node->setLoopMode(true);
	node->setFrameLoop(0, 40);
}

void CCharacter::walk()
{
	node->setAnimationSpeed(250);
	node->setLoopMode(true);
	node->setFrameLoop(60, 140);
}

void CCharacter::attack()
{
	node->setAnimationSpeed(35);
	node->setLoopMode(false);
	node->setFrameLoop(0,0);
	node->setAnimationEndCallback();
}