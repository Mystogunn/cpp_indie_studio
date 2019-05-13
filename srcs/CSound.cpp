/*
** EPITECH PROJECT, 2021
** cpp_indie_studio
** File description:
** Created by dany,
*/

#include "../include/CSound.hpp"

CSound::CSound()
{
	engine = irrklang::createIrrKlangDevice();
}

CSound::~CSound()
{
	//music->drop();
}

void CSound::play(const char *path, irrklang::ik_f32 vol)
{
	music = engine->play2D(path);
}

void CSound::stop()
{
	//tmp = 0;
	//engine->drop();
	//music->setVolume(tmp);
	music->drop();
}
