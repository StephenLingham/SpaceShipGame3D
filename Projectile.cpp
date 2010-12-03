#define NOMINMAX 
#include <cml/cml.h>
#include "BoundingBox.h"

namespace SpaceShip
{
	class Projectile
	{
	private:
		cml::vector3f position;
	public:		
		cml::vector3f colour;
		SpaceShip::BoundingBox boundingBox;
		cml::vector3f velocity;
		
		Projectile(cml::vector3f pos, cml::vector3f col, SpaceShip::BoundingBox bb, cml::vector3f vel)
		{
			position = pos;
			colour = col;
			boundingBox = bb;
			velocity = vel;
		}

		void SetPosition(cml::vector3f pos)
		{
			position = pos;
			boundingBox.position = pos;
			boundingBox.SetCorners();
		}

		cml::vector3f GetPosition()
		{
			return position;
		}

	};
}
