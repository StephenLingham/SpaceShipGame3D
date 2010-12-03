/*#define NOMINMAX 
#include <cml/cml.h>

namespace SpaceShip
{
	class BoundingBox
	{
		public:
		cml::vector3f maxPos;
		cml::vector3f minPos;
		cml::vector3f corners[8];

		BoundingBox()
		{
		}
		
		BoundingBox(cml::vector3f maxPos, cml::vector3f minPos)
		{
			this->maxPos = maxPos;
			this->minPos = minPos;

			corners[0] = cml::vector3f(minPos[0], maxPos[1], maxPos[2]); //left,top,back
			corners[1] = cml::vector3f(maxPos[0], maxPos[1], maxPos[2]); //right,top,back
			corners[2] = cml::vector3f(minPos[0], maxPos[1], minPos[2]); //left, top, front
			corners[3] = cml::vector3f(maxPos[0], maxPos[1], minPos[2]); //right, top, front
			corners[4] = cml::vector3f(minPos[0], minPos[1], maxPos[2]); //left, bottom, back
			corners[5] = cml::vector3f(maxPos[0], minPos[1], maxPos[2]); //right, bottom, back
			corners[6] = cml::vector3f(minPos[0], minPos[1], minPos[2]); //left, bottom, front
			corners[7] = cml::vector3f(maxPos[0], minPos[1], minPos[2]); // right, bottom, front
			
		}

		bool intersects(BoundingBox otherBox)
		{
			bool hasCollided = false;

			for (int i = 0; i < sizeof(corners); i++)
			{
				if (corners[i][0] <= otherBox.maxPos[0] && corners[i][0] >= otherBox.minPos[0])
					hasCollided = true;

				if (corners[i][1] <= otherBox.maxPos[1] && corners[i][1] >= otherBox.minPos[1])
					hasCollided = true;

				if (corners[i][2] <= otherBox.maxPos[2] && corners[i][2] >= otherBox.minPos[2])
					hasCollided = true;
				  
			}

			return hasCollided;
		}

	};

}
*/

#define NOMINMAX 
#include <cml/cml.h>
#include "BoundingBox.h"


namespace SpaceShip
{
	//class BoundingBox
	//{
		BoundingBox::BoundingBox(cml::vector3f position, float width, float height, float depth)
		{
			this->position = position;
			this->width = width;
			this->height = height;
			this->depth = depth;

			SetCorners();//position, width, height, depth);
			
		}
		/*
		BoundingBox::BoundingBox(cml::vector3f maxPos, cml::vector3f minPos)
		{
			this->maxPos = maxPos;
			this->minPos = minPos;

			corners[0] = cml::vector3f(minPos[0], maxPos[1], maxPos[2]); //left,top,back
			corners[1] = cml::vector3f(maxPos[0], maxPos[1], maxPos[2]); //right,top,back
			corners[2] = cml::vector3f(minPos[0], maxPos[1], minPos[2]); //left, top, front
			corners[3] = cml::vector3f(maxPos[0], maxPos[1], minPos[2]); //right, top, front
			corners[4] = cml::vector3f(minPos[0], minPos[1], maxPos[2]); //left, bottom, back
			corners[5] = cml::vector3f(maxPos[0], minPos[1], maxPos[2]); //right, bottom, back
			corners[6] = cml::vector3f(minPos[0], minPos[1], minPos[2]); //left, bottom, front
			corners[7] = cml::vector3f(maxPos[0], minPos[1], minPos[2]); // right, bottom, front
			
		}*/

		void BoundingBox::SetCorners()//cml::vector3f position, float width, float height, float depth)
		{/*
			corners[0] = cml::vector3f(position[0] - width/2, position[1] + height/2, position[2] + depth/2); //left,top,back
			corners[1] = cml::vector3f(position[0] + width/2, position[1] + height/2, position[2] + depth/2); //right,top,back
			corners[2] = cml::vector3f(position[0] - width/2, position[1] + height/2, position[2] - depth/2); //left,top,front
			corners[3] = cml::vector3f(position[0] + width/2, position[1] + height/2, position[2] - depth/2); //right,top,front
			corners[4] = cml::vector3f(position[0] - width/2, position[1] - height/2, position[2] + depth/2); //left,bottom,back
			corners[5] = cml::vector3f(position[0] + width/2, position[1] - height/2, position[2] + depth/2); //right,bottom,back
			corners[6] = cml::vector3f(position[0] - width/2, position[1] - height/2, position[2] - depth/2); //left,bottom,front
			corners[7] = cml::vector3f(position[0] + width/2, position[1] - height/2, position[2] - depth/2); //right,bottom,front
			*/
			corners.push_back(cml::vector3f(position[0] - width/2, position[1] + height/2, position[2] + depth/2)); //left,top,back
			corners.push_back(cml::vector3f(position[0] + width/2, position[1] + height/2, position[2] + depth/2)); //right,top,back
			corners.push_back(cml::vector3f(position[0] - width/2, position[1] + height/2, position[2] - depth/2)); //left,top,front
			corners.push_back(cml::vector3f(position[0] + width/2, position[1] + height/2, position[2] - depth/2)); //right,top,front
			corners.push_back(cml::vector3f(position[0] - width/2, position[1] - height/2, position[2] + depth/2)); //left,bottom,back
			corners.push_back(cml::vector3f(position[0] + width/2, position[1] - height/2, position[2] + depth/2)); //right,bottom,back
			corners.push_back(cml::vector3f(position[0] - width/2, position[1] - height/2, position[2] - depth/2)); //left,bottom,front
			corners.push_back(cml::vector3f(position[0] + width/2, position[1] - height/2, position[2] - depth/2)); //right,bottom,front
			

			minPos = cml::vector3f(position[0] - width/2, position[1] - height/2, position[2] - depth/2); 
			maxPos = cml::vector3f(position[0] + width/2, position[1] + height/2, position[2] + depth/2); 
			
		}
		
		bool BoundingBox::Intersects(BoundingBox otherBox)
		{
			bool hasCollided = false;

			for (int i = 0; i < corners.size(); i++)
			{
				if (corners[i][0] <= otherBox.maxPos[0] && 
					corners[i][0] >= otherBox.minPos[0] &&
					corners[i][1] <= otherBox.maxPos[1] && 
					corners[i][1] >= otherBox.minPos[1] &&
					corners[i][2] <= otherBox.maxPos[2] && 
					corners[i][2] >= otherBox.minPos[2])
						hasCollided = true;
								  
			}

			return hasCollided;
		}

	//};

}

