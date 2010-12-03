#define NOMINMAX 
#include <cml/cml.h>
//#include <cml/vector.h>

//using namespace SpaceShip;
namespace SpaceShip
{

	class Player
	{
	public:
		cml::vector3f position;
		float rotX;
		float rotY;
		float rotZ;
		float lastMouseX;
		float lastMouseY;
		float mouseX;
		float mouseY;
		
		Player(cml::vector3f pos)
		{
			position = pos;
			rotX = 0;
			rotY = 0;
			rotZ = 0;
			lastMouseX = 0;
			lastMouseY = 0;
			mouseX = 0;
			mouseY = 0;
		}
		
		//vector3 position;
		//position.set(0,0,-200);

	};

}
