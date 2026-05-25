#pragma once
#include <glm/glm.hpp>
using namespace std;


struct Effect
{
	int timer = 0, id = -1, duration = 0;
	glm::ivec2 point = glm::ivec2(0);
};
