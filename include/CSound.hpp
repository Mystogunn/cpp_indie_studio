/*
** EPITECH PROJECT, 2021
** cpp_indie_studio
** File description:
** Created by dany,
*/
#ifndef CPP_INDIE_STUDIO_CSOUND_HPP
#define CPP_INDIE_STUDIO_CSOUND_HPP

#include <iostream>
#include "/usr/local/include/irr/irrlicht.h"
#include "../include/irrklang/irrKlang.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class	CSound {
	public:
	CSound();
	~CSound();
	void 		play(const char*, irrklang::ik_f32);
	void		stop();
	irrklang::ISoundEngine* engine;
	irrklang::ISound *music;
	private:
	irrklang::vec3df position;
	irrklang::ik_f32 tmp;

};

#endif //CPP_INDIE_STUDIO_CSOUND_HPP
