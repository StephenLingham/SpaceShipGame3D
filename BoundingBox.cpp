#define NOMINMAX 
#include <cml/cml.h>
#include "BoundingBox.h"
#include <math.h>

namespace SpaceShip
{

	BoundingBox::BoundingBox(cml::vector3f position, float width, float height, float depth)
	{
		this->position = position;
		this->width = width;
		this->height = height;
		this->depth = depth;

		if (width > height && width > depth)
			maxOuterBoundary = width * 1.5f;
		else if (height > depth)
			maxOuterBoundary = height * 1.5f;
		else 
			maxOuterBoundary = depth * 1.5f;

	}
	

	void BoundingBox::SetCorners()
	{
		corners.clear();

		corners.push_back(cml::vector3f(position[0] - width/2, position[1] + height/2, position[2] + depth/2)); //left,top,back
		corners.push_back(cml::vector3f(position[0] + width/2, position[1] + height/2, position[2] + depth/2)); //right,top,back
		corners.push_back(cml::vector3f(position[0] - width/2, position[1] + height/2, position[2] - depth/2)); //left,top,front
		corners.push_back(cml::vector3f(position[0] + width/2, position[1] + height/2, position[2] - depth/2)); //right,top,front
		corners.push_back(cml::vector3f(position[0] - width/2, position[1] - height/2, position[2] + depth/2)); //left,bottom,back
		corners.push_back(cml::vector3f(position[0] + width/2, position[1] - height/2, position[2] + depth/2)); //right,bottom,back
		corners.push_back(cml::vector3f(position[0] - width/2, position[1] - height/2, position[2] - depth/2)); //left,bottom,front
		corners.push_back(cml::vector3f(position[0] + width/2, position[1] - height/2, position[2] - depth/2)); //right,bottom,front

	}

	bool BoundingBox::Intersects(BoundingBox otherBox)
	{
		bool hasCollided = false;			

		float distance = sqrt (pow(position[0] - otherBox.position[0], 2) + pow(position[1] - otherBox.position[1], 2) + pow(position[2] - otherBox.position[2], 2));//distance between two boxes positions

		//only do more accurate detection if boxes are near enough to each other
		if (distance < maxOuterBoundary + otherBox.maxOuterBoundary)
		{
			SetCorners();

			cml::vector3f minPosOtherBox = otherBox.GetMinPosition();
			cml::vector3f maxPosOtherBox = otherBox.GetMaxPosition();

			for (int i = 0; i < corners.size(); i++)
			{
				if (corners[i][0] <= maxPosOtherBox[0] && 
					corners[i][0] >= minPosOtherBox[0] &&
					corners[i][1] <= maxPosOtherBox[1] && 
					corners[i][1] >= minPosOtherBox[1] &&
					corners[i][2] <= maxPosOtherBox[2] && 
					corners[i][2] >= minPosOtherBox[2])
				{
					hasCollided = true;
					break;
				}


			}
		}

		return hasCollided;
	}

	cml::vector3f BoundingBox::GetMinPosition()
	{
		return cml::vector3f(position[0] - width/2, position[1] - height/2, position[2] - depth/2);
	}

	cml::vector3f BoundingBox::GetMaxPosition()
	{
		return cml::vector3f(position[0] + width/2, position[1] + height/2, position[2] + depth/2);		
	}

}

