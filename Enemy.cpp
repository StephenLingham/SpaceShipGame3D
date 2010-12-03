#define NOMINMAX 
#include <cml/cml.h>
#include "BoundingBox.h"


namespace SpaceShip
{
	class Enemy
	{
	public:
		cml::vector3f position;
		float cubeRotX;
		float cubeRotY;
		float cubeRotZ;
		cml::vector3f colour;
		SpaceShip::BoundingBox boundingBox;
		
		Enemy(cml::vector3f pos, cml::vector3f col, SpaceShip::BoundingBox bb)
		{
			position = pos;
			cubeRotX = 0;
			cubeRotY = 0;
			cubeRotZ = 0;
			colour = col;
			boundingBox = bb;
		}
		
		//vector3 position;
		//position.set(0,0,-200);

	};
}
