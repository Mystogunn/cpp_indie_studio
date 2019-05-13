/*
** EPITECH PROJECT, 2022
** test
** File description:
** Created by elias,
*/

#include "../include/CGame.hpp"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

CGame::CGame(IrrlichtDevice *ddevice, IVideoDriver *ddriver,
	ISceneManager *ssmgr, CMap *mmap, CCharacter *cchar1,
	CCharacter *cchar2, CTimer *time
)
{
	device = ddevice;
	driver = ddriver;
	smgr = ssmgr;
	map = mmap;
	char1 = cchar1;
	char2 = cchar2;
	timer = time;
	sound = new CSound();
}

int CGame::updateExplosion(CBox *explosion)
{
	if (explosion->getTimer()->getDelta() > 1000)
		return 1;
	return 0;
}

int CGame::updateBomb(CBox *bomb)
{
	if (bomb->getTimer()->getDelta() > 2000)
		return 1;
	return 0;
}

void CGame::addXExplosion(vector3df pos)
{
	std::pair<u32, u32> postemp;
	addExplosion(pos);
	sound->play("assets/soundfx/bomb3.ogg", 0.8f);
	postemp.first = (pos.X + 15) / 24 + 1;
	postemp.second = (pos.Z - 3) / 24 * -1;
	if (map->getCBox(postemp)->getType() == CBox::EBoxType::EMPTY ||
		map->getCBox(postemp)->getType() == CBox::EBoxType::BOX ||
		map->getCBox(postemp)->getType() == CBox::EBoxType::BONUS) {
		addExplosion(vector3df(pos.X + 24, pos.Y, pos.Z));
		if (map->getCBox(postemp)->getType() == CBox::EBoxType::BOX||
			map->getCBox(postemp)->getType() == CBox::EBoxType::BONUS) {
			map->getCBox(postemp)->getnode()->remove();
			delete map->getCBox(postemp);
			map->setMap(postemp,new CBox(device, driver, smgr, vector3df(pos), CBox::EBoxType::EMPTY, postemp, sound));
		}
		//
		postemp.first = (pos.X + 15) / 24 + 2;
		postemp.second = (pos.Z - 3) / 24 * -1;
		if (map->getCBox(postemp)->getType() == CBox::EBoxType::EMPTY ||
			map->getCBox(postemp)->getType() == CBox::EBoxType::BOX ||
			map->getCBox(postemp)->getType() == CBox::EBoxType::BONUS)
			addExplosion(vector3df(pos.X + 48, pos.Y, pos.Z));
		if (map->getCBox(postemp)->getType() == CBox::EBoxType::BOX ||
			map->getCBox(postemp)->getType() == CBox::EBoxType::BONUS) {
			map->getCBox(postemp)->getnode()->remove();
			delete map->getCBox(postemp);
			map->setMap(postemp,new CBox(device, driver, smgr, vector3df(pos), CBox::EBoxType::EMPTY, postemp, sound));
		}
	}
	//
	postemp.first = (pos.X + 15) / 24 - 1;
	postemp.second = (pos.Z - 3) / 24 * -1;
	if (map->getCBox(postemp)->getType() == CBox::EBoxType::EMPTY ||
		map->getCBox(postemp)->getType() == CBox::EBoxType::BOX ||
		map->getCBox(postemp)->getType() == CBox::EBoxType::BONUS) {
		addExplosion(vector3df(pos.X - 24, pos.Y, pos.Z));
		if (map->getCBox(postemp)->getType() == CBox::EBoxType::BOX ||
			map->getCBox(postemp)->getType() == CBox::EBoxType::BONUS) {
			map->getCBox(postemp)->getnode()->remove();
			delete map->getCBox(postemp);
			map->setMap(postemp,new CBox(device, driver, smgr, vector3df(pos), CBox::EBoxType::EMPTY, postemp, sound));
		}
		//
		postemp.first = (pos.X + 15) / 24 - 2;
		postemp.second = (pos.Z - 3) / 24 * -1;
		if (map->getCBox(postemp)->getType() == CBox::EBoxType::EMPTY ||
			map->getCBox(postemp)->getType() == CBox::EBoxType::BOX ||
			map->getCBox(postemp)->getType() == CBox::EBoxType::BONUS)
			addExplosion(vector3df(pos.X - 48, pos.Y, pos.Z));
		if (map->getCBox(postemp)->getType() == CBox::EBoxType::BOX ||
			map->getCBox(postemp)->getType() == CBox::EBoxType::BONUS) {
			map->getCBox(postemp)->getnode()->remove();
			delete map->getCBox(postemp);
			map->setMap(postemp,new CBox(device, driver, smgr, vector3df(pos), CBox::EBoxType::EMPTY, postemp, sound));
		}
	}
	//
	postemp.first = (pos.X + 15) / 24;
	postemp.second = (pos.Z - 3) / 24 * -1 + 1;
	if (map->getCBox(postemp)->getType() == CBox::EBoxType::EMPTY ||
		map->getCBox(postemp)->getType() == CBox::EBoxType::BOX ||
		map->getCBox(postemp)->getType() == CBox::EBoxType::BONUS) {
		addExplosion(vector3df(pos.X, pos.Y, pos.Z - 24));
		if (map->getCBox(postemp)->getType() == CBox::EBoxType::BOX ||
			map->getCBox(postemp)->getType() == CBox::EBoxType::BONUS) {
			map->getCBox(postemp)->getnode()->remove();
			delete map->getCBox(postemp);
			map->setMap(postemp,new CBox(device, driver, smgr, vector3df(pos), CBox::EBoxType::EMPTY, postemp, sound));
		}
		//
		postemp.first = (pos.X + 15) / 24;
		postemp.second = (pos.Z - 3) / 24 * -1 + 2;
		if (map->getCBox(postemp)->getType() == CBox::EBoxType::EMPTY ||
			map->getCBox(postemp)->getType() == CBox::EBoxType::BOX ||
			map->getCBox(postemp)->getType() == CBox::EBoxType::BONUS)
			addExplosion(vector3df(pos.X, pos.Y, pos.Z - 48));
		if (map->getCBox(postemp)->getType() == CBox::EBoxType::BOX ||
			map->getCBox(postemp)->getType() == CBox::EBoxType::BONUS) {
			map->getCBox(postemp)->getnode()->remove();
			delete map->getCBox(postemp);
			map->setMap(postemp,new CBox(device, driver, smgr, vector3df(pos), CBox::EBoxType::EMPTY, postemp, sound));
		}
	}
	//
	postemp.first = (pos.X + 15) / 24;
	postemp.second = (pos.Z - 3) / 24 * -1 - 1;
	if (map->getCBox(postemp)->getType() == CBox::EBoxType::EMPTY ||
		map->getCBox(postemp)->getType() == CBox::EBoxType::BOX ||
		map->getCBox(postemp)->getType() == CBox::EBoxType::BONUS) {
		addExplosion(vector3df(pos.X, pos.Y, pos.Z + 24));
		if (map->getCBox(postemp)->getType() == CBox::EBoxType::BOX ||
			map->getCBox(postemp)->getType() == CBox::EBoxType::BONUS) {
			map->getCBox(postemp)->getnode()->remove();
			delete map->getCBox(postemp);
			map->setMap(postemp,new CBox(device, driver, smgr, vector3df(pos), CBox::EBoxType::EMPTY, postemp, sound));
		}
		//
		postemp.first = (pos.X + 15) / 24;
		postemp.second = (pos.Z - 3) / 24 * -1 - 2;
		if (map->getCBox(postemp)->getType() == CBox::EBoxType::EMPTY ||
			map->getCBox(postemp)->getType() == CBox::EBoxType::BOX ||
			map->getCBox(postemp)->getType() == CBox::EBoxType::BONUS)
			addExplosion(vector3df(pos.X, pos.Y, pos.Z + 48));
		if (map->getCBox(postemp)->getType() == CBox::EBoxType::BOX ||
			map->getCBox(postemp)->getType() == CBox::EBoxType::BONUS) {
			map->getCBox(postemp)->getnode()->remove();
			delete map->getCBox(postemp);
			map->setMap(postemp,new CBox(device, driver, smgr, vector3df(pos), CBox::EBoxType::EMPTY, postemp, sound));
		}
	}
	//
}

void CGame::updateBombStack()
{
	int x = 0;
	for (std::vector<CBox *>::iterator it = bomb_stack.begin();
		it != bomb_stack.end(); it++, x++) {
		keypos_temp = bomb_stack.at(x)->getKeyMapPos();
		pos_temp = bomb_stack.at(x)->getnode()->getPosition();
		if (updateBomb(bomb_stack.at(x)) == 1) {
			if (bomb_stack.at(x)->bombbool == false) {
				bomb_stack.at(x)->getnode()->setVisible(false);
				addXExplosion(bomb_stack.at(
					x)->getnode()->getPosition());
				bomb_stack.at(x)->bombbool = true;
			}
		}
	}
}

void CGame::updateExplosionStack()
{
	int x = 0;
	std::pair<u32, u32>	pos;
	std::pair<u32, u32>	pos2;
	vector3df		temppos;
	vector3df		temppos2;
	for (std::vector<CBox *>::iterator it = explosion_stack.begin();
		it != explosion_stack.end(); it++, x++) {
		if (updateExplosion(explosion_stack.at(x)) == 1 &&
			explosion_stack.at(x)->explosionbool == false) {
			explosion_stack.at(x)->getParticleBox()->setVisible(
				false);
			explosion_stack.at(x)->explosionbool = true;
		}
		else if (updateExplosion(explosion_stack.at(x)) == 0) {
			temppos = explosion_stack.at(x)->getParticleBox()->getPosition();
			pos2.first = (temppos.X) / 24;
			pos2.second = (temppos.Z) / 24 * -1;
			if (!char1->isDead)
			{
				temppos = char1->getnode()->getPosition();
				pos.first = (temppos.X + 15) / 24;
				pos.second = (temppos.Z - 3) / 24 * -1;
				if (pos == pos2)
				{
					char1->isDead = true;
					char1->getnode()->setVisible(false);
				}
			}
			if (!char2->isDead)
			{
				temppos = char2->getnode()->getPosition();
				pos.first = (temppos.X + 15) / 24;
				pos.second = (temppos.Z - 3) / 24 * -1;
				if (pos == pos2)
				{
					char2->isDead = true;
					char2->getnode()->setVisible(false);
				}
			}
		}
	}
}

void CGame::update(CMap *mmap)
{
	map = mmap;
	if (timer->getDelta() > 300) {
		updateBombStack();
		updateExplosionStack();
		timer->reset();
	}
}

void CGame::addBomb(vector3df pos)
{
	std::pair<u32, u32> keypos;
	std::pair<s32, s32> newpos;
	keypos.first = pos.X / 24;
	keypos.second = pos.Z / 24;
	newpos.first = (pos.X + 15) / 24;
	newpos.second = (pos.Z - 3) / 24;
	//std::cout << char1->getnode()->getPosition().X << " " << char1->getnode()->getPosition().Z << std::endl;
	//std::cout << newpos.first << " " << newpos.second << std::endl;
	CBox *bomb = new CBox(device, driver, smgr,
		vector3df(newpos.first * 24, 0, newpos.second * 24),
		CBox::EBoxType::BOMB, keypos, sound);
	bomb->getTimer()->reset();
	bomb_stack.emplace_back(bomb);
}

void CGame::addExplosion(vector3df pos)
{
	std::pair<u32, u32> postemp;
	postemp.first = (pos.X + 15) / 24 + 1;
	postemp.second = (pos.Z - 3) / 24 * -1;
	std::pair<u32, u32> keypos;
	std::pair<s32, s32> newpos;
	keypos.first = pos.X / 24;
	keypos.second = pos.Z / 24;
	newpos.first = (pos.X + 15) / 24;
	newpos.second = (pos.Z - 3) / 24;
	CBox *explosion = new CBox(device, driver, smgr,
		vector3df(newpos.first * 24, 0, newpos.second * 24),
		CBox::EBoxType::EXPLOSION, keypos, sound);
	explosion->getTimer()->reset();
	explosion_stack.emplace_back(explosion);
	//map->setMap(postemp, explosion);
}
