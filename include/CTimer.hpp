/*
** EPITECH PROJECT, 2021
** Project
** File description:
** Created by dany,
*/
#ifndef PROJECT_CTIMER_HPP
#define PROJECT_CTIMER_HPP

#include "/usr/local/include/irr/irrlicht.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class CTimer {
	public:
	CTimer(IrrlichtDevice *ddevice);
	void		reset();
	void		update();
	f32		getTimeFactor();
	f32 		getDelta();
	u32		m_Time;
	u32		m_DeltaTime;
	f32		m_TimeFactor;
	private:
	IrrlichtDevice	*device;
};
#endif //PROJECT_CTIMER_HPP
