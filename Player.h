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

	Player(cml::vector3f pos)
	{
		position = pos;
	}

	//vector3 position;
	//position.set(0,0,-200);

};

}
