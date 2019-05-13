/*
** EPITECH PROJECT, 2021
** Project
** File description:
** Created by dany,
*/
#include "CTimer.hpp"

CTimer::CTimer(IrrlichtDevice *ddevice)
{
	device = ddevice;
}

void CTimer::reset()
{
	m_Time = device->getTimer()->getTime();
}

void CTimer::update()
{
	m_DeltaTime = device->getTimer()->getTime() - m_Time;
	m_Time =+ m_DeltaTime;
	m_TimeFactor = m_DeltaTime * 0.001f;
}

f32 CTimer::getTimeFactor()
{
	return (m_TimeFactor);
}

f32 CTimer::getDelta()
{
	f32 tmp = device->getTimer()->getTime();
	return tmp - m_Time;
}