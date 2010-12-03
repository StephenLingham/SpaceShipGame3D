#define NOMINMAX 
#include <cml/cml.h>
//#include "BoundingBox.cpp"

namespace SpaceShip
{
	class Enemy
	{
	public:
		cml::vector3f position;
		float cubeRotX;
		float cubeRotY;
		float cubeRotZ;
		//BoundingBox boundingBox;
		
		Enemy(cml::vector3f pos)
		{
			position = pos;
			cubeRotX = 0;
			cubeRotY = 0;
			cubeRotZ = 0;
		}
		
		//vector3 position;
		//position.set(0,0,-200);

	};
}
