#include "/usr/local/include/irr/irrlicht.h"
#include "../include/core.hpp"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int	main()
{
	CCore	Core;

	srand(time(NULL));
	Core.loader();
	Core.run();
	Core.close();
	return 0;
}
