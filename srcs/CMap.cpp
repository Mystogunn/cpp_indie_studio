/*
** EPITECH PROJECT, 2021
** cpp_indie_studio
** File description:
** Created by Yoann Sarkissian,
*/

#include "../include/CMap.hpp"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

CMap::CMap(IrrlichtDevice *ddevice, IVideoDriver *ddriver, ISceneManager *ssmgr)
{
	isSaveAvailable = true;
	device = ddevice;
	driver = ddriver;
	smgr = ssmgr;
	sound = new CSound();
	tmp_y = -17.0f;
	tmp_z = 0.0f;
	x = 0;
	y = 0;
	ifs.open("assets/map/map.save");
	if (! ifs.is_open()) {
		isSaveAvailable = false;
	}
}

void CMap::saveMap()
{
	std::ofstream save("assets/map/map.save", std::ios::out);
	std::pair<u32,u32> pos;
	pos.first = 0;
	pos.second = 0;
	std::cout<< "1 "<< std::endl;
	while (pos.second <= 12) {
		while (pos.first <= 18) {
			save << bm_map[pos]->getType();
			pos.first++;
		}
		save << std::endl;
		pos.second++;
		pos.first = 0;
	}
	save.close();
}

void CMap::clear()
{
	std::pair<u32, u32> poss;
	for (u32 yy = 0; yy <= 12; yy++)
	{
		for (u32 xx = 0; xx <= 18; xx++)
		{
			poss.first = xx;
			poss.second = yy;
			//if (bm_map[poss]->CBox::getType() == CBox::EBoxType::BOX)
			//	bm_map[poss]->getnode()->setVisible(false);
			bm_map[poss]->CBox::getType();
		}
	}
}

bool CMap::loaderSave()
{
	x = 0;
	if (std::getline(ifs, buffer)) {
		tmp_x = 0.0f;
		std::cout<< tmp_z<< std::endl;
		for (auto it = buffer.begin(); it != buffer.end(); it++, x++) {
			pos.first = x;
			pos.second = y;
			if (*it == '0')
				bm_map[pos] = new CBox(device, driver, smgr, vector3df(tmp_x, tmp_y, tmp_z), CBox::EBoxType::EMPTY, pos, sound);
			else if (*it == '1')
				bm_map[pos] = new CBox(device, driver, smgr, vector3df(tmp_x, tmp_y, tmp_z), CBox::EBoxType::BOX, pos, sound);
			else if (*it == '2')
				bm_map[pos] = new CBox(device, driver, smgr, vector3df(tmp_x, tmp_y, tmp_z), CBox::EBoxType::UBOX, pos, sound);
			else if (*it == '3')
				bm_map[pos] = new CBox(device, driver, smgr, vector3df(tmp_x, tmp_y, tmp_z), CBox::EBoxType::BOMB, pos, sound);
			else if (*it == '4')
				bm_map[pos] = new CBox(device, driver, smgr, vector3df(tmp_x, tmp_y, tmp_z), CBox::EBoxType::BONUS, pos, sound);
			else if (*it == '5')
				bm_map[pos] = new CBox(device, driver, smgr, vector3df(tmp_x, tmp_y, tmp_z), CBox::EBoxType::EXPLOSION, pos, sound);
			tmp_x += 24.0f;
		}
		tmp_z -= 24.0f;
		x = 0;
		y++;
		return true;
	}
	ifs.close();
	return false;
}

bool CMap::loaderProcedural()
{
	u32 r = 0;

	if (y <= 12) {
		tmp_x = 0.0f;
		x = 0;
		for (;x <= 18 ; x++) {
			pos.first = x;
			pos.second = y;
			if (x == 0 || x == 18 || y == 0 || y == 12) {
				bm_map[pos] = new CBox(device, driver, smgr,
					vector3df(tmp_x, tmp_y, tmp_z),
					CBox::EBoxType::UBOX, pos, sound);
			} else {
				if (x % 2 == 0 && y % 2 == 0) {
					bm_map[pos] = new CBox(device, driver, smgr,
						vector3df(tmp_x, tmp_y, tmp_z),
						CBox::EBoxType::UBOX, pos, sound);
				} else if (x == 1 && y == 1 || x == 1 && y == 2 || x == 2 && y == 1
					|| x == 17 && y == 1 || x == 17 && y == 2 || x == 16 && y == 1
					|| x == 1 && y == 11 || x == 1 && y == 10 || x == 2 && y == 11
					|| x == 17 && y == 11 || x == 17 && y == 10 || x == 16 && y == 11) {
					bm_map[pos] = new CBox(device, driver, smgr,
						vector3df(tmp_x, tmp_y, tmp_z),
						CBox::EBoxType::EMPTY, pos, sound);
				}else {
					r = rand() % 3;
					if (r >= 1) {
						r = rand() % 15;
						if (r >= 1) {
							bm_map[pos] = new CBox(device, driver, smgr,
								vector3df(tmp_x, tmp_y, tmp_z),
								CBox::EBoxType::BOX, pos, sound);
						} else {
							bm_map[pos] = new CBox(device, driver, smgr,
								vector3df(tmp_x, tmp_y, tmp_z),
								CBox::EBoxType::BONUS, pos, sound);
						}
					} else {
						bm_map[pos] = new CBox(device, driver, smgr,
							vector3df(tmp_x, tmp_y, tmp_z),
							CBox::EBoxType::EMPTY, pos, sound);
					}
				}
			}
			tmp_x += 24.0f;
		}
		x = 0;
		y++;
		tmp_z = tmp_z - 24.0f;
		return true;
	}
	ifs.close();
	return false;
}

CBox::EBoxType CMap::isAvailableSpace(vector3df v, vector3df vold)
{
	std::pair<s32, s32> pos;
	bool			Xbool = false;
	bool			Zbool= false;
	if (!(v.X != vold.X && v.Z != vold.Z))
	{
		pos.first = (v.X + 15) / 24;
		pos.second = (v.Z - 3) / 24 * -1;
		if (bm_map[pos]->CBox::getType() == CBox::EBoxType::UBOX ||
			bm_map[pos]->CBox::getType() == CBox::EBoxType::BOX)
			return CBox::EBoxType ::BOX;
	}
	else {
		pos.first = (v.X + 15) / 24;
		pos.second = (vold.Z - 3) / 24 * -1;
		if (bm_map[pos]->CBox::getType() == CBox::EBoxType::UBOX ||
			bm_map[pos]->CBox::getType() == CBox::EBoxType::BOX)
			Xbool = true;
		pos.first = (vold.X + 15) / 24;
		pos.second = (v.Z - 3) / 24 * -1;
		if (bm_map[pos]->CBox::getType() == CBox::EBoxType::UBOX ||
			bm_map[pos]->CBox::getType() == CBox::EBoxType::BOX)
			Zbool = true;
		if (Xbool || Zbool)
			return CBox::EBoxType ::BOX;
		pos.first = (v.X + 15) / 24;
		pos.second = (v.Z - 3) / 24 * -1;
		}
	if (bm_map[pos]->CBox::getType() == CBox::EBoxType::BONUS)
	{
		bm_map[pos]->getnode()->remove();
		delete getCBox(pos);
		setMap(pos,new CBox(device, driver, smgr, vector3df(v), CBox::EBoxType::EMPTY, pos, sound));
		sound->play("assets/soundfx/bonus.ogg", 0.8f);
		return CBox::EBoxType::BONUS;
	}
	return bm_map[pos]->CBox::getType();
}

CBox *CMap::getCBox(std::pair<u32,u32> key)
{
	return (bm_map[key]);
}

void CMap::setMap(std::pair<u32, u32> key, CBox *tmp)
{
	bm_map[key] = tmp;
}
