/*
** EPITECH PROJECT, 2021
** Project
** File description:
** Created by dany,
*/
#ifndef PROJECT_CMENU_HPP
#define PROJECT_CMENU_HPP

#include "/usr/local/include/irr/irrlicht.h"
#include "../include/CTimer.hpp"
#include "../include/CMap.hpp"
#include "../include/CSound.hpp"
#include "../include/CCharacter.hpp"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class CMenu {
	public:
	enum EMenuState {SPLASH, LOADING, MENU, PAUSE};
	enum EGameType {MULTI, SOLO};
	enum EEventType {GO, TIMEUP, HURRYUP, FINISH, NONE};
	CMenu(IVideoDriver *driver, IrrlichtDevice *device, IGUIEnvironment *ggui, ISceneManager *ssmgr, CSound *ssound);
	bool			restart;
	bool			restartok;
	bool			resume;
	bool			quit;
	bool			pause;
	u32 			level;
	u32 			levelpause;
	bool			menuhandler();
	void			setState(CMenu::EMenuState);
	CMenu::EMenuState	getState();
	CMenu::EGameType	getGameType();
	void			setGameType(CMenu::EGameType);
	bool			getbsetting();
	void			enable();
	void			disable();
	IrrlichtDevice		*device;
	bool			getEnabled();
	CMap			*map;
	CSound			*sound;
	EEventType 		eventtype;
	CTimer			*timer;
	CTimer			*negative;
	bool			bnegative;
	CTimer			*pausetimer;
	u32			pausetime;
	u32			savedtime;
	u32			currentime;
	CTimer			*partytimer;
	CTimer			*eventtimer;
	CCharacter		*character1;
	CCharacter		*character2;
	CCharacter		*character3;
	CCharacter		*character4;
	private:
	IGUIFont		*font;
	IGUIFont		*fontbig;
	int			transparency;
	bool			transparencybool;
	void 			pausescreen();
	void			splashscreen();
	void			menuscreen();
	void			loadingscreen(bool);
	void			eventscreen();
	void			gui();
	IVideoDriver		*driver;
	IGUIEnvironment		*guienv;
	ISceneManager		*smgr;
	bool			isEnabled;
	bool			setting;
	EGameType		gametype;
	EMenuState 		state;
	ITexture*		Tsplashscreen;
	ITexture*		Tsplashkonami;
	ITexture*		Tmenu;
	ITexture*		TBstart;
	ITexture*		TBstart2;
	ITexture*		TBquit;
	ITexture*		TBhelp;
	ITexture*		TBsetting;
	ITexture*		TBleft;
	ITexture*		TBright;
	ITexture*		TBlefth;
	ITexture*		TBrighth;
	ITexture*		TBvsia;
	ITexture*		TBlocalm;
	ITexture*		TBribbon;
	ITexture*		Tloadinganimation;
	ITexture*		Ttimer;
	ITexture*		Tgo;
	ITexture*		Tfinish;
	ITexture*		Ttimeup;
	ITexture*		Thurryup;
	ITexture*		Thalo;
	ITexture*		Tresume;
	ITexture*		Tresume2;
	ITexture*		Tresume3;
	ITexture*		TBquit2;
	ITexture*		TBquit2h;
	ITexture*		TBsave;
	ITexture*		TBsaveh;
	ITexture*		Tbgblack;
	u32			timeloading;
	u32			animationloading;
};

#endif //PROJECT_CMENU_HPP
