#pragma once
#include <ppl.h>
#include "Global.h"
using namespace gl;

namespace lf 
{
	void logicPlanet(std::vector<Planet>& planets, double& G, double& scalePhy, View& world);
	void drawButtons(std::vector<Button>& buttons, RenderWindow& window);
}