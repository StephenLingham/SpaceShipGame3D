#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

namespace SpaceShip
{
	class BoundingBox
	{
	private:
		cml::vector3f maxPos;
		cml::vector3f minPos;
	public:
		cml::vector3f position;
		float width;
		float height;
		float depth;		
		std::vector<cml::vector3f> corners;
		float maxOuterBoundary;

		
		BoundingBox()
		{
			maxPos = cml::vector3f(0.f,0.f,0.f);
			minPos = cml::vector3f(0.f,0.f,0.f);
			/*
			corners[0] = cml::vector3f(0.f,0.f,0.f);
			corners[1] = cml::vector3f(0.f,0.f,0.f);
			corners[2] = cml::vector3f(0.f,0.f,0.f);
			corners[3] = cml::vector3f(0.f,0.f,0.f);
			corners[4] = cml::vector3f(0.f,0.f,0.f);
			corners[5] = cml::vector3f(0.f,0.f,0.f);
			corners[6] = cml::vector3f(0.f,0.f,0.f);
			corners[7] = cml::vector3f(0.f,0.f,0.f);
			*/
		
		}

		BoundingBox(cml::vector3f position, float width, float height, float depth);
		
		//BoundingBox(cml::vector3f maxPos, cml::vector3f minPos);

		void SetCorners();//cml::vector3f position, float width, float height, float depth);

		bool Intersects(BoundingBox otherBox);

		cml::vector3f GetMinPosition();

		cml::vector3f GetMaxPosition();

	};

}

#endif

