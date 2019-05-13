/*
** EPITECH PROJECT, 2021
** Project
** File description:
** Created by dany,
*/
#include "../include/CMenu.hpp"

CMenu::CMenu(IVideoDriver *vdriver, IrrlichtDevice *ddevice,
	IGUIEnvironment *ggui, ISceneManager *ssmgr, CSound *ssound
)
{
	restartok = false;
	restart = true;
	resume = false;
	quit = false;
	pause = false;
	levelpause = 3;
	level = 3;
	isEnabled = true;
	setting = false;
	state = SPLASH;
	gametype = MULTI;
	driver = vdriver;
	device = ddevice;
	guienv = ggui;
	smgr = ssmgr;
	Tsplashkonami = driver->getTexture("assets/menu/konami.png");
	Tsplashscreen = driver->getTexture("assets/menu/title_bg.png");
	Tmenu = driver->getTexture("assets/menu/menu_bg.png");
	TBstart = driver->getTexture("assets/menu/newgame.png");
	TBstart2 = driver->getTexture("assets/menu/newgame2.png");
	TBquit = driver->getTexture("assets/menu/back.png");
	TBsetting = driver->getTexture("assets/menu/setting.png");
	TBhelp = driver->getTexture("assets/menu/help.png");
	TBleft = driver->getTexture("assets/menu/left.png");
	TBright = driver->getTexture("assets/menu/right.png");
	TBlefth = driver->getTexture("assets/menu/lefth.png");
	TBrighth = driver->getTexture("assets/menu/righth.png");
	TBvsia = driver->getTexture("assets/menu/vsia.png");
	TBlocalm = driver->getTexture("assets/menu/localm.png");
	TBribbon = driver->getTexture("assets/menu/ribbon.png");
	Ttimer = driver->getTexture("assets/menu/timer.png");
	Tloadinganimation = driver->getTexture("assets/menu/loading.png");
	Tgo = driver->getTexture("assets/menu/go.png");
	Thurryup = driver->getTexture("assets/menu/hurryup.png");
	Ttimeup = driver->getTexture("assets/menu/timeup.png");
	Thalo = driver->getTexture("assets/menu/halo.png");
	Tfinish = driver->getTexture("assets/menu/finish.png");
	Tresume = driver->getTexture("assets/menu/resume.png");
	Tresume2 = driver->getTexture("assets/menu/resume2.png");
	Tresume3 = driver->getTexture("assets/menu/resume3.png");
	TBsave = driver->getTexture("assets/menu/saveh.png");
	TBsaveh = driver->getTexture("assets/menu/saveh.png");
	TBsave = driver->getTexture("assets/menu/save.png");
	TBquit2 = driver->getTexture("assets/menu/quit.png");
	TBquit2h = driver->getTexture("assets/menu/quith.png");
	Tbgblack = driver->getTexture("assets/menu/bgblack.png");
	transparency = 255;
	transparencybool = true;
	fontbig = guienv->getFont("assets/font/font3.xml");
	font = guienv->getFont("assets/font/font.xml");
	timeloading = 0;
	animationloading = 0;
	timer = new CTimer(device);
	negative = new CTimer(device);
	bnegative = false;
	timer->reset();
	partytimer = new CTimer(device);
	eventtimer = new CTimer(device);
	pausetimer = new CTimer(device);
	pausetimer->reset();
	eventtimer->reset();
	pausetime = 0;
	map = new CMap(device, driver, smgr);
	sound = ssound;
	//sound = new CSound();
	//sound->play("assets/soundfx/menu.ogg");
}

bool CMenu::menuhandler()
{
	if (isEnabled) {
		if (state == SPLASH)
			splashscreen();
		else if (state == LOADING)
			loadingscreen(resume);
		else if (state == MENU)
			menuscreen();
		return true;
	} else
		gui();
	return false;
}

void CMenu::splashscreen()
{
	driver->draw2DImage(Tsplashscreen, position2d<s32>(0, 0));
	if (device->getTimer()->getTime() < 1500)
		driver->draw2DImage(Tsplashkonami, position2d<s32>(0, 0),
			rect<s32>(0, 0, 1920, 1080), 0,
			SColor(255, 255, 255, 250), false);
	else if (device->getTimer()->getTime() > 1500 &&
		device->getTimer()->getTime() < 2000) {
		driver->draw2DImage(Tsplashkonami, position2d<s32>(0, 0),
			rect<s32>(0, 0, 1920, 1080), 0,
			SColor(transparency, 255, 255, 250), false);
		if (transparency >= 1)
			transparency -= 1;
	} else if (device->getTimer()->getTime() >= 2000 &&
		device->getTimer()->getTime() <= 2400) {
		transparency = 40;
	} else if (device->getTimer()->getTime() > 2400) {
		if (transparency <= 40)
			transparencybool = true;
		else if (transparency >= 248)
			transparencybool = false;
		if (transparencybool &&
			(device->getTimer()->getTime() % 2) == 0)
			transparency += 2;
		else if ((device->getTimer()->getTime() % 2) == 0)
			transparency -= 2;
		if (font)
			font->draw(L"Press SPACE to PLAY",
				core::rect<s32>(0, 800, 1920, 1080),
				video::SColor(transparency, 255, 255, 255),
				true, false);
	}
}

void CMenu::loadingscreen(bool save)
{
	if (animationloading == 3)
		animationloading = 0;
	else
		animationloading++;
	timer->reset();
	driver->draw2DImage(Tmenu, position2d<s32>(0, 0));
	driver->draw2DImage(TBribbon, position2d<s32>(0, 760));
	if (animationloading == 0) {
		driver->draw2DImage(Tloadinganimation,
			core::rect<s32>(1920 - 50 - 162, 1080 - 85 - 223,
				1920 - 50, 1080 - 85),
			core::rect<s32>(0, 0, 162, 223), 0, 0, true);
		font->draw(L"LOADING", core::rect<s32>(1250, 965, 1920, 1080),
			video::SColor(255, 255, 255, 255), true, false);
	} else if (animationloading == 1) {
		driver->draw2DImage(Tloadinganimation,
			core::rect<s32>(1920 - 50 - 162, 1080 - 85 - 223,
				1920 - 50, 1080 - 85),
			core::rect<s32>(162, 0, 162 * 2, 223), 0, 0, true);
		font->draw(L"LOADING.", core::rect<s32>(1250, 965, 1920, 1080),
			video::SColor(255, 255, 255, 255), true, false);
	} else if (animationloading == 2) {
		driver->draw2DImage(Tloadinganimation,
			core::rect<s32>(1920 - 50 - 162, 1080 - 85 - 223,
				1920 - 50, 1080 - 85),
			core::rect<s32>(0, 223, 162, 223 * 2), 0, 0, true);
		font->draw(L"LOADING..", core::rect<s32>(1250, 965, 1920, 1080),
			video::SColor(255, 255, 255, 255), true, false);
	} else {
		driver->draw2DImage(Tloadinganimation,
			core::rect<s32>(1920 - 50 - 162, 1080 - 85 - 223,
				1920 - 50, 1080 - 85),
			core::rect<s32>(162, 223, 162 * 2, 223 * 2), 0, 0,
			true);
		font->draw(L"LOADING...",
			core::rect<s32>(1250, 965, 1920, 1080),
			video::SColor(255, 255, 255, 255), true, false);
	}
	if (!save) {
		if (!map->loaderProcedural()) {
			setState(CMenu::EMenuState::MENU);
			character1 = new CCharacter(device, driver, smgr, "assets/character/Bomberman.x", "assets/character/textures/black_body.png", vector3df(1, 0,11));
			character2 = new CCharacter(device, driver, smgr, "assets/character/Bomberman.x", "assets/character/textures/body.png", vector3df(17, 0,1));
			restartok = true;
			setState(CMenu::EMenuState::MENU);
			disable();
			partytimer->reset();
			sound->play("assets/soundfx/Speedrunner.ogg", 0.4f);
		}
	} else {
		if (!map->loaderSave()) {
			character1 = new CCharacter(device, driver, smgr, "assets/character/Bomberman.x", "assets/character/textures/black_body.png", vector3df(1, 0,11));
			character2 = new CCharacter(device, driver, smgr, "assets/character/Bomberman.x", "assets/character/textures/body.png", vector3df(17, 0,1));
			restartok = true;
			setState(CMenu::EMenuState::MENU);
			disable();
			partytimer->reset();
			sound->play("assets/soundfx/Speedrunner.ogg", 0.4f);

		}
	}
}

void CMenu::eventscreen()
{
	dimension2d<u32> size;
	ITexture *texture;
	ITexture *texturehalo = Thalo;
	dimension2d<u32> sizehalo = texturehalo->getSize();;
	u32 currentime = partytimer->getDelta() * 0.001f;

	if (currentime == 0)
		eventtype = CMenu::EEventType::GO;
	if (currentime == 30 || currentime == 60)
		eventtype = CMenu::EEventType::HURRYUP;
	if (currentime == 80)
		eventtype = CMenu::EEventType::TIMEUP;
	if (currentime == 90)
		eventtype = CMenu::EEventType::FINISH;
	if (eventtype != CMenu::EEventType::NONE) {
		if (eventtimer->getDelta() > 1000) {
			eventtimer->reset();
			eventtype = CMenu::EEventType::NONE;
		} else if (eventtimer->getDelta() < 1000) {
			size = texturehalo->getSize();
			driver->draw2DImage(texturehalo, core::rect<s32>(
				(1920 / 2) - (sizehalo.Width / 2),
				(1080 / 2) - (sizehalo.Height / 2),
				(1920 / 2) + (sizehalo.Width / 2),
				(1080 / 2) + (sizehalo.Height / 2)),
				core::rect<s32>(0, 0, sizehalo.Width,
					sizehalo.Height), 0, 0, true);
			if (eventtype == CMenu::EEventType::GO)
				texture = Tgo;
			else if (eventtype == CMenu::EEventType::FINISH)
				texture = Tfinish;
			else if (eventtype == CMenu::EEventType::HURRYUP)
				texture = Thurryup;
			else
				texture = Ttimeup;
			size = texture->getSize();
			driver->draw2DImage(texture,
				core::rect<s32>((1920 / 2) - (size.Width / 2),
					(1080 / 2) - (size.Height / 2),
					(1920 / 2) + (size.Width / 2),
					(1080 / 2) + (size.Height / 2)),
				core::rect<s32>(0, 0, size.Width, size.Height),
				0, 0, true);
		}
	}
}

void CMenu::gui()
{
	std::string timetext;
	if (!pause)
		currentime = partytimer->getDelta() * 0.001f -  pausetime+0.1;
	else
		currentime = savedtime;
	if (currentime < 90)
		timetext = std::to_string(90 - currentime) + " sec";
	else
		timetext = "TIME";
	driver->draw2DImage(Ttimer, core::rect<s32>((1920 / 2) - (350 / 2), 50,
		(1920 / 2) + (350 / 2), 50 + 99),
		core::rect<s32>(0, 0, 350, 99), 0, 0, true);
	font->draw(timetext.c_str(),
		core::rect<s32>((1920 / 2) - 50, 88, 1920, 1080),
		video::SColor(255, 255, 255, 255), false, false);
	eventscreen();
	if (pause)
		pausescreen();
}

void CMenu::pausescreen()
{
	if (pausetimer->getDelta() > 1000)
	{
		pausetimer->reset();
		pausetime++;
	}
	driver->draw2DRectangle(SColor(200, 0, 0, 0), core::rect<s32>(0, 0, 1920, 1080));
	ITexture *texture = Tresume;
	ITexture *texture2 = TBsaveh;
	ITexture *texture3 = TBquit2h;
	dimension2d<u32> size = texture->getSize();
	dimension2d<u32> size2 = texture2->getSize();
	dimension2d<u32> size3 = texture3->getSize();

	if (levelpause == 3)
	{
		driver->draw2DImage(Tresume2,
			core::rect<s32>((1920 / 2) - (size.Width / 2),
				(1080 / 2 - 100) - (size.Height / 2),
				(1920 / 2) + (size.Width / 2),
				(1080 / 2 - 100) + (size.Height / 2)),
			core::rect<s32>(0, 0, size.Width, size.Height), 0, 0,
			true);
	} else {
		driver->draw2DImage(Tresume,
			core::rect<s32>((1920 / 2) - (size.Width / 2),
				(1080 / 2 - 100) - (size.Height / 2),
				(1920 / 2) + (size.Width / 2),
				(1080 / 2 - 100) + (size.Height / 2)),
			core::rect<s32>(0, 0, size.Width, size.Height), 0, 0,
			true);
	}
	if (levelpause == 2)
	{
		driver->draw2DImage(TBsave,
			core::rect<s32>((1920 / 2) - (size2.Width / 2),
				(1080 / 2) - (size2.Height / 2),
				(1920 / 2) + (size2.Width / 2),
				(1080 / 2) + (size2.Height / 2)),
			core::rect<s32>(0, 0, size2.Width, size2.Height), 0, 0,
			true);
	} else {
		driver->draw2DImage(TBsaveh,
			core::rect<s32>((1920 / 2) - (size2.Width / 2),
				(1080 / 2) - (size2.Height / 2),
				(1920 / 2) + (size2.Width / 2),
				(1080 / 2) + (size2.Height / 2)),
			core::rect<s32>(0, 0, size2.Width, size2.Height), 0, 0,
			true);
	}
	if (levelpause == 1)
	{
		driver->draw2DImage(TBquit2,
			core::rect<s32>((1920 / 2) - (size3.Width / 2),
				(1080 / 2 + 100) - (size3.Height / 2),
				(1920 / 2) + (size3.Width / 2),
				(1080 / 2 + 100) + (size3.Height / 2)),
			core::rect<s32>(0, 0, size3.Width, size3.Height), 0, 0,
			true);
	} else {
		driver->draw2DImage(TBquit2h,
			core::rect<s32>((1920 / 2) - (size3.Width / 2),
				(1080 / 2 + 100) - (size3.Height / 2),
				(1920 / 2) + (size3.Width / 2),
				(1080 / 2 + 100) + (size3.Height / 2)),
			core::rect<s32>(0, 0, size3.Width, size3.Height), 0, 0,
			true);
	}

}

void CMenu::menuscreen()
{
	ITexture *texture = TBstart;
	ITexture *texture2 = Tresume;
	dimension2d<u32> size = texture->getSize();
	dimension2d<u32> size2 = texture2->getSize();
	driver->draw2DImage(Tmenu, position2d<s32>(0, 0));
	driver->draw2DImage(TBribbon, position2d<s32>(0, 760));
	driver->draw2DImage(TBquit,
		core::rect<s32>(50, 1080 - 125 - 132, 50 + 176, 1080 - 125),
		core::rect<s32>(0, 0, 176, 132), 0, 0, true);
	if (!setting) {
		if (bnegative)
		{
			if (negative->getDelta() > 300)
				bnegative = false;
			driver->draw2DImage(Tresume3,
				core::rect<s32>((1920 / 2) - (size2.Width / 2),
					(1080 - 250) - (size2.Height / 2),
					(1920 / 2) + (size2.Width / 2),
					(1080 - 250) + (size2.Height / 2)),
				core::rect<s32>(0, 0, size2.Width,
					size2.Height), 0, 0, true);
		} else {
			if (level == 2)
			{
				driver->draw2DImage(Tresume2,
					core::rect<s32>((1920 / 2) - (size2.Width / 2),
						(1080 - 250) - (size2.Height / 2),
						(1920 / 2) + (size2.Width / 2),
						(1080 - 250) + (size2.Height / 2)),
					core::rect<s32>(0, 0, size2.Width, size2.Height), 0, 0,
					true);
			}
			else {
				driver->draw2DImage(Tresume,
					core::rect<s32>((1920 / 2) - (size2.Width / 2),
						(1080 - 250) - (size2.Height / 2),
						(1920 / 2) + (size2.Width / 2),
						(1080 - 250) + (size2.Height / 2)),
					core::rect<s32>(0, 0, size2.Width,
						size2.Height), 0, 0, true);
			}
		}
		if (level == 1) {
			driver->draw2DImage(TBstart2,
				core::rect<s32>((1920 / 2) - (size.Width / 2),
					(1080 - 150) - (size.Height / 2),
					(1920 / 2) + (size.Width / 2),
					(1080 - 150) + (size.Height / 2)),
				core::rect<s32>(0, 0, size.Width, size.Height),
				0, 0, true);
		} else {
			driver->draw2DImage(TBstart,
				core::rect<s32>((1920 / 2) - (size.Width / 2),
					(1080 - 150) - (size.Height / 2),
					(1920 / 2) + (size.Width / 2),
					(1080 - 150) + (size.Height / 2)),
				core::rect<s32>(0, 0, size.Width, size.Height),
				0, 0, true);
		}
		//
		driver->draw2DImage(TBsetting,
			core::rect<s32>(1920 - 50 - 176, 1080 - 125 - 132,
				1920 - 50, 1080 - 125),
			core::rect<s32>(0, 0, 176, 132), 0, 0, true);
		if (level == 3)
		{
			driver->draw2DImage(TBleft,
				core::rect<s32>((1920 / 2) - (80 / 2) - 400,
					(1080 / 2) - (376 / 2) - 150,
					(1920 / 2) + (80 / 2) - 400,
					(1080 / 2) + (376 / 2) - 150),
				core::rect<s32>(0, 0, 80, 376), 0, 0, true);
			driver->draw2DImage(TBright,
				core::rect<s32>((1920 / 2) - (80 / 2) + 400,
					(1080 / 2) - (376 / 2) - 150,
					(1920 / 2) + (80 / 2) + 400,
					(1080 / 2) + (376 / 2) - 150),
				core::rect<s32>(0, 0, 80, 376), 0, 0, true);
		} else {
			driver->draw2DImage(TBlefth,
				core::rect<s32>((1920 / 2) - (80 / 2) - 400,
					(1080 / 2) - (376 / 2) - 150,
					(1920 / 2) + (80 / 2) - 400,
					(1080 / 2) + (376 / 2) - 150),
				core::rect<s32>(0, 0, 80, 376), 0, 0, true);
			driver->draw2DImage(TBrighth,
				core::rect<s32>((1920 / 2) - (80 / 2) + 400,
					(1080 / 2) - (376 / 2) - 150,
					(1920 / 2) + (80 / 2) + 400,
					(1080 / 2) + (376 / 2) - 150),
				core::rect<s32>(0, 0, 80, 376), 0, 0, true);
		}
		if (gametype == MULTI) {
			driver->draw2DImage(TBlocalm,
				core::rect<s32>((1920 / 2) - (454 / 2),
					(1080 / 2) - (394 / 2) - 150,
					(1920 / 2) + (454 / 2),
					(1080 / 2) + (394 / 2) - 150),
				core::rect<s32>(0, 0, 454, 394), 0, 0, true);
			font->draw(L"MULTIPLAYER",
				core::rect<s32>(0, 600, 1920, 1080),
				video::SColor(255, 255, 255, 255), true, false);
		} else {
			driver->draw2DImage(TBvsia,
				core::rect<s32>((1920 / 2) - (454 / 2),
					(1080 / 2) - (394 / 2) - 150,
					(1920 / 2) + (454 / 2),
					(1080 / 2) + (394 / 2) - 150),
				core::rect<s32>(0, 0, 454, 394), 0, 0, true);
			font->draw(L"SOLO GAME",
				core::rect<s32>(0, 600, 1920, 1080),
				video::SColor(255, 255, 255, 255), true, false);
		}
	} else {
		driver->draw2DImage(TBhelp,
			core::rect<s32>(1920 - 50 - 176, 1080 - 55 - 132,
				1920 - 50, 1080 - 55),
			core::rect<s32>(0, 0, 176, 132), 0, 0, true);
	}
}

bool CMenu::getbsetting()
{
	return setting;
}

CMenu::EMenuState CMenu::getState()
{
	return state;
}

CMenu::EGameType CMenu::getGameType()
{
	return gametype;
}

void CMenu::setGameType(CMenu::EGameType newtype)
{
	gametype = newtype;
}

void CMenu::setState(CMenu::EMenuState newstate)
{
	state = newstate;
}

void CMenu::disable()
{
	isEnabled = false;
}

void CMenu::enable()
{
	isEnabled = true;
}

bool CMenu::getEnabled()
{
	return isEnabled;
}