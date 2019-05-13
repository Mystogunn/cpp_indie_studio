/*
** EPITECH PROJECT, 2022
** test
** File description:
** Created by dany,
*/
#include "../include/CEventReceiver.hpp"
#include "../include/CCharacter.hpp"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

CEventReceiver::CEventReceiver(CCharacter *character, CCharacter *character2, CMap *map, IrrlichtDevice *ddevice, CMenu *mmenu, IVideoDriver *ddriver, ISceneManager *ssmgr)
{
	device = ddevice;
	driver = ddriver;
	smgr = ssmgr;
	for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
		KeyIsDown[i] = false;
	menu = mmenu;
}

void CEventReceiver::setMap(CMap *map)
{
	mmap = map;
}

bool CEventReceiver::OnEvent(const irr::SEvent &event)
{
	if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
	}
	return false;
}

bool CEventReceiver::IsKeyDown(EKEY_CODE keyCode)
{
	return KeyIsDown[keyCode];
}

void CEventReceiver::majPosMesh(CCharacter *character, std::map<std::string, EKEY_CODE> keybind, f32 factor, CGame *game)
{
	irr::core::vector3df	rot(0,0,0);
	irr::core::vector3df	vold = character->getnode()->getPosition();
	irr::core::vector3df	v = character->getnode()->getPosition();

	if (character->bonusSpeed && character->bonusSpeedTimer->getDelta() > 5000)
		character->bonusSpeed = false;
	if (IsKeyDown(keybind["FORWARD"])) {
		if (character->bonusSpeed)
			v.Z += factor * MOVEMENT_SPEED * 2;
		else
			v.Z += factor * MOVEMENT_SPEED;
		rot.Y = 0;
		character->getnode()->setRotation(rot);
	}
	else if (IsKeyDown(keybind["BACKWARD"])) {
		if (character->bonusSpeed)
			v.Z -= factor * MOVEMENT_SPEED * 2;
		else
			v.Z -= factor * MOVEMENT_SPEED;
		rot.Y = 180;
		character->getnode()->setRotation(rot);
	}
	if (IsKeyDown(keybind["LEFT"])) {
		if (character->bonusSpeed)
			v.X -= factor * MOVEMENT_SPEED * 2;
		else
			v.X -= factor * MOVEMENT_SPEED;
		if (v.Z > vold.Z)
			rot.Y -= 45;
		else if (v.Z < vold.Z)
			rot.Y += 45;
		else
			rot.Y = 270;
		character->getnode()->setRotation(rot);
	}
	else if (IsKeyDown(keybind["RIGHT"])) {
		if (character->bonusSpeed)
			v.X += factor * MOVEMENT_SPEED * 2;
		else
			v.X += factor * MOVEMENT_SPEED;
		if (v.Z > vold.Z)
			rot.Y += 45;
		else if (v.Z < vold.Z)
			rot.Y -= 45;
		else
			rot.Y = 90;
		character->getnode()->setRotation(rot);
	}
	if (IsKeyDown(keybind["ATTACK"])) {
		if (character->bombTimer->getDelta() > 500) {
			character->setState(CCharacter::ATTACK);
			character->attack();
			game->addBomb(vold);
			character->bombTimer->reset();
		}
	}
	if(vold != v && character->getState() != CCharacter::WALK) {
		character->setState(CCharacter::WALK);
		character->walk();
	}
	else if (vold == v && character->getState() != CCharacter::IDLE && character->getState() != CCharacter::ATTACK) {
		character->setState(CCharacter::IDLE);
		character->idle();
	}
	if (mmap->isAvailableSpace(v, vold) == CBox::EBoxType::BONUS) {
		character->bonusSpeed = true;
		character->bonusSpeedTimer->reset();
		menu->sound->play("assets/soundfx/bonus.ogg", 0.4f);
	}
	if (mmap->isAvailableSpace(v, vold) != CBox::EBoxType::BOX)
		character->getnode()->setPosition(v);
	if (mmap->isAvailableSpace(v, vold) == CBox::EBoxType::EXPLOSION) {
		character->isDead = true;
		character->getnode()->remove();
	}
}

void CEventReceiver::majMenu(CMenu *menu, std::map<std::string, EKEY_CODE> keybind, f32 factor)
{
	if(IsKeyDown(keybind["SPACE"])) {
		if (menu->getState() == CMenu::EMenuState::SPLASH){
			menu->setState(CMenu::EMenuState::MENU);
		}
	}
	if(IsKeyDown(keybind["PAUSE"])) {
		if (menu->pause)
			menu->pause = false;
		else
		{
			menu->pause = true;
			menu->savedtime = menu->currentime;
		}
		menu->device->sleep(100);
	}
	if(IsKeyDown(keybind["ENTER"])) {
		if (menu->getState() == CMenu::EMenuState::MENU && menu->pause == false)
		{
			if (menu->level == 2)
			{
				if (menu->map->isSaveAvailable)
				{
					menu->setState(CMenu::EMenuState::LOADING);
					menu->resume = true;
					//menu->sound->play("assets/soundfx/load.ogg", 0.4f);
				} else
				{
					menu->sound->play("assets/soundfx/negative.ogg", 0.4f);
					menu->device->sleep(200);
					menu->bnegative = true;
					menu->negative->reset();
				}
			}
			else if (menu->level == 1)
			{
				//menu->sound->play("assets/soundfx/load.ogg", 0.4f);
				menu->setState(CMenu::EMenuState::LOADING);
			}
		}
		else {
			if (menu->levelpause == 3)
				menu->pause = false;
			else if (menu->levelpause == 2)
			{
				/*menu->map = new CMap(device, driver, smgr);
				menu->enable();
				menu->restart = true;
				menu->pause = false;
				menu->setState(CMenu::EMenuState::LOADING);*/
				mmap->saveMap();
				menu->quit = true;
			}
			else
				menu->quit = true;
		}
	}
	if(IsKeyDown(keybind["DOWN"])) {
		if (!menu->pause) {
			menu->sound->play("assets/soundfx/click.ogg", 0.4f);
				if (menu->level > 1)
					menu->level--;
		} else {
			menu->sound->play("assets/soundfx/click.ogg", 0.4f);
			if (menu->levelpause > 1)
				menu->levelpause--;
		}
		menu->device->sleep(200);
	}
	if(IsKeyDown(keybind["UP"])) {
		if (!menu->pause) {
			menu->sound->play("assets/soundfx/click.ogg", 0.4f);
				if (menu->level < 3)
					menu->level++;
		} else {
			menu->sound->play("assets/soundfx/click.ogg", 0.4f);
			if (menu->levelpause < 3)
				menu->levelpause++;
		}
		menu->device->sleep(200);
	}
	if(IsKeyDown(keybind["RIGHT"]) || IsKeyDown(keybind["LEFT"])) {
		if (menu->level == 3 )
		{
			menu->sound->play("assets/soundfx/mode.ogg", 0.4f);
			if (menu->getState() == CMenu::EMenuState::MENU && menu->getbsetting() == false) {
				if (menu->getGameType() == CMenu::EGameType::MULTI)
					menu->setGameType(CMenu::EGameType::SOLO);
				else
					menu->setGameType(CMenu::EGameType::MULTI);
			}
		}
		menu->device->sleep(200);
	}
}