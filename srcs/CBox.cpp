/*
** EPITECH PROJECT, 2021
** Project
** File description:
** Created by dany,
*/

#include "../include/CBox.hpp"

CBox::CBox(IrrlichtDevice *ddevice, IVideoDriver *ddriver, ISceneManager *ssmgr, vector3df pos, CBox::EBoxType type, std::pair<u32, u32> kkeymappos, CSound *ssound)
{
	keymappos = kkeymappos;
	device = ddevice;
	driver = ddriver;
	smgr = ssmgr;
	ttype = type;
	timer = new CTimer(device);
	sound = ssound;
	if (type == CBox::EBoxType::BOX)
		box(pos);
	else if (type == CBox::EBoxType::BONUS)
		bonus(pos);
	else if (type == CBox::EBoxType::UBOX)
		ubox(pos);
	else if (type == CBox::EBoxType::EXPLOSION)
		particle(pos, CBox::EParticleType::BOMBEXPLOSION);
	else if (type == CBox::EBoxType::BOMB)
		bomb(pos);
	else if (type == CBox::EBoxType::PALMTREE)
		palmtree(pos);
}

void	CBox::bomb(vector3df pos)
{
	mesh = smgr->getMesh("assets/box/bomb/Bomb.x");
	if (!mesh)
		device->drop();
	node = smgr->addAnimatedMeshSceneNode(mesh);
	animator = smgr->createRotationAnimator(vector3df(0,1,0));
	node = smgr->addAnimatedMeshSceneNode(mesh);
	if (node)
	{
		node->setMaterialTexture(0, driver->getTexture("assets/box/bomb/bomb.png"));
		node->getMaterial(0).SpecularColor.set(255,255,255,255);
		node->getMaterial(0).Shininess = 512.6f;
		node->setMaterialFlag(EMF_LIGHTING, false);
		node->setPosition(vector3df(pos.X-3, 20, pos.Z-10));
		node->setRotation(vector3df(0.0f,0.0f,0.0f));
		node->setScale(vector3df(70.f,70.f,70.f));
		node->addShadowVolumeSceneNode();
		//node->addAnimator(animator);
		//animator->drop();
		node->setAnimationSpeed(50);
		node->setFrameLoop(0, 20);
	}
	bombbool = false;
	//sound->play("assets/soundfx/allah.ogg", 0.8f);
	sound->play("assets/soundfx/fuse.ogg", 0.8f);
}

void	CBox::particle(vector3df pos, CBox::EParticleType type)
{
	particlebox = smgr->addParticleSystemSceneNode(false);
	emitter = particlebox->createBoxEmitter(
		aabbox3d<irr::f32>(-1,-1,-1,1,1,1), // coordonnees de la boite
		vector3df(0.0f,0.1f,0.0f),// direction de diffusion
		30,40, // nb particules emises a la sec min / max
		SColor(255,0,0,255),                  // couleur la plus sombre
		SColor(255,200,200,255),            // couleur la plus claire
		300, 300,                                    // duree de vie min / max
		20,                                            // angle max d'ecart / direction prevue
		dimension2df(20.0f,20.0f),           // taille minimum
		dimension2df(30.0f,30.0f));
	particlebox->setEmitter(emitter);
	particlebox->setPosition(vector3df(pos.X, 5, pos.Z));
	emitter->drop();
	particlebox->setMaterialFlag(EMF_LIGHTING, true);          // insensible a la lumiere
	particlebox->setMaterialFlag(EMF_ZWRITE_ENABLE, false);     // desactive zbuffer pour surfaces derriere
	particlebox->setMaterialTexture(0, driver->getTexture("assets/box/explosion/explosion.jpg"));     // on colle une texture
	particlebox->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);
	affector = particlebox->createFadeOutParticleAffector(
			SColor(0,0,0,0),             // la couleur finale
			20);                                   // temps necessaire a la modification
	particlebox->addAffector(affector);       // ajout du modificateur au particle system                                                                                              
	affector->drop();
	explosionbool = false;
}

void	CBox::box(vector3df pos)
{
	mesh = smgr->getMesh("assets/box/box/box_3ds.3DS");
	if (!mesh)
		device->drop();
	video::ITexture* normalMap = driver->getTexture("assets/normal.jpg");
	if (normalMap)
		driver->makeNormalMapTexture(normalMap, 2.0f);
	node = smgr->addAnimatedMeshSceneNode(mesh);
	if (node)
	{
		node->setMaterialTexture(0, driver->getTexture("assets/box/box/diffuse.jpg"));
		node->setMaterialTexture(1, normalMap);
		node->getMaterial(0).SpecularColor.set(255,255,255,255);
		node->getMaterial(0).Shininess = 0.6f;
		node->setMaterialType(video::EMT_PARALLAX_MAP_SOLID);
		node->setMaterialFlag(EMF_LIGHTING, true);
		node->getMaterial(0).NormalizeNormals = true;
		node->getMaterial(0).MaterialTypeParam = 1.f / 64.f;
		node->setPosition(vector3df(pos.X, pos.Y, pos.Z));
		//node->setPosition(vector3df(-20.0f,-8.0f,-20.0f));
		node->setRotation(vector3df(0.0f,20.0f,0.0f));
		node->setScale(vector3df(0.75f,0.75f,0.75f));
		//node->setDebugDataVisible(irr::scene::EDS_BBOX);
		node->addShadowVolumeSceneNode();
	}
}

void	CBox::bonus(vector3df pos)
{
	mesh = smgr->getMesh("assets/Star/star.obj");
	if (!mesh) {
		device->drop();
	}
	animator = smgr->createRotationAnimator(vector3df(0,1,0));
	node = smgr->addAnimatedMeshSceneNode(mesh);
	if (node)
	{
		node->setMaterialTexture(0, driver->getTexture("assets/Star/Tex_0221_0.png"));
		node->getMaterial(0).SpecularColor.set(255,255,255,255);
		node->getMaterial(0).Shininess = 0.6f;
		node->setMaterialFlag(EMF_LIGHTING, false);
		node->setPosition(vector3df(pos.X-3, 0, pos.Z));
		node->setRotation(vector3df(0.0f,0.0f,0.0f));
		node->setScale(vector3df(4.f,4.f,4.f));
		node->addShadowVolumeSceneNode();
		node->addAnimator(animator);
		animator->drop();
	}
}

void	CBox::ubox(vector3df pos)
{
	mesh = smgr->getMesh("assets/box/box/box_3ds.3DS");
	if (!mesh) {
		std::cout << "fail"<< std::endl;
		device->drop();
	}
	node = smgr->addAnimatedMeshSceneNode(mesh);
	if (node)
	{
		node->setMaterialTexture(0, driver->getTexture("assets/ubox/ubox.png"));
		//node->getMaterial(0).SpecularColor.set(255,255,255,255);
		node->getMaterial(0).Shininess = 0.0f;
		//node->setMaterialType(video::EMT_PARALLAX_MAP_SOLID);
		node->setMaterialFlag(EMF_LIGHTING, true);
		//node->getMaterial(0).NormalizeNormals = true;
		//node->getMaterial(0).MaterialTypeParam = 1.f / 6.f;
		node->setPosition(vector3df(pos.X, pos.Y, pos.Z));
		//node->setPosition(vector3df(-20.0f,-8.0f,-20.0f));
		node->setRotation(vector3df(0.0f,21.0f,0.0f));
		node->setScale(vector3df(0.75f,0.75f,0.75f));
		//node->getMesh()->getMeshBuffer(0)->recalculateBoundingBox();
		//aabbox3df box = node->getMesh()->getMeshBuffer(0)->getBoundingBox();
		//node->getMesh()->getMesh(0)->setBoundingBox(box);
		//node->setDebugDataVisible(irr::scene::EDS_BBOX);
		node->addShadowVolumeSceneNode();
	}
}

void	CBox::palmtree(vector3df pos)
{
	mesh = smgr->getMesh("assets/terrain/Palm_Tree.3ds");
	if (!mesh)
		device->drop();
	node = smgr->addAnimatedMeshSceneNode(mesh);
	if (node)
	{
		//node->getMaterial(0).SpecularColor.set(255,255,255,255);
		node->getMaterial(0).Shininess = 20.6f;
		node->setMaterialFlag(EMF_LIGHTING, true);
		//node->getMaterial(0).NormalizeNormals = true;
		//node->getMaterial(0).MaterialTypeParam = 1.f / 64.f;
		node->setPosition(vector3df(pos.X, pos.Y, pos.Z));
		//node->setPosition(vector3df(-20.0f,-8.0f,-20.0f));
		node->setRotation(vector3df(0.0f,0.0f,0.0f));
		node->setScale(vector3df(20.0f,20.0f,20.0f));
		//node->setDebugDataVisible(irr::scene::EDS_BBOX);
		node->addShadowVolumeSceneNode();
	}
}

IAnimatedMeshSceneNode* CBox::getnode()
{
	return node;
}

CBox::EBoxState CBox::getState()
{
	return state;
}

IAnimatedMesh* CBox::getmesh()
{
	return mesh;
}

void CBox::setState(CBox::EBoxState newstate)
{
	state = newstate;
}

CBox::EBoxType	CBox::getType()
{
	return ttype;
}

std::pair<u32, u32> CBox::getKeyMapPos()
{
	return keymappos;
}

CTimer* CBox::getTimer()
{
	return timer;
}

IParticleSystemSceneNode* CBox::getParticleBox()
{
	return particlebox;
}