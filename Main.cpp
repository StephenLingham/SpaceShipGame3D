#define NOMINMAX 
#include "Main.h"
#include <cml/cml.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Player.cpp"
#include "Enemy.cpp"
#include <list>
#include "BoundingBox.h"
#include "Projectile.cpp"


void Update();
void Draw();
void DrawCube(float size);
void DrawCube2(float size, cml::vector3f colour);
void DrawFace(float size);
void Initialize();
static std::string toString(float value); 
void MouseMovement();
void ProcessKeyboard();
void ProcessMouse(sf::Event Event);
void UpdateProjectiles();


sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Space Ship Demo", sf::Style::Fullscreen);
sf::Clock Clock;
sf::Clock updateClock;


//sf:String Text;
//sf::Font Arial;

SpaceShip::Player player(cml::vector3f(0,0,100));

std::vector<SpaceShip::Enemy> enemies;


bool initMousePos = false;
std::vector<SpaceShip::Projectile> projectiles;


int main()
{   	

	/*
    if (!Arial.LoadFromFile("arial.ttf"))
         return EXIT_FAILURE;
     //Text("Hello SFML", Arial, 50);
	
	Text.SetText("Hello");
	Text.SetFont(MyFont);
	Text.SetSize(50);
	*/

	Initialize();		
	    
    while (window.IsOpened())
    {
		if (updateClock.GetElapsedTime() > 1.f/60.f) //update a set number of times per second, set time to avoid players moving at different speeds on different computers
		{
			Update();       
			updateClock.Reset();
		}

		Draw(); //draws as fast as possible
    }

    return EXIT_SUCCESS;
}

void Update()
{		
	sf::Event Event;
	while (window.GetEvent(Event))
	{		
		if (Event.Type == sf::Event::Closed)
			window.Close();
		
		if (Event.Type == sf::Event::Resized)
			glViewport(0, 0, Event.Size.Width, Event.Size.Height);

		if (Event.Type == sf::Event::MouseMoved)
		{
			player.mouseX = Event.MouseMove.X;
			player.mouseY = Event.MouseMove.Y;			
		}

		//stores the players mouse pos initially, otherwise it takes it as (0,0) 
		//and calculates that the player makes a big spin at the start of the game
		//making him upside down
		if (!initMousePos)
		{
			const sf::Input& input = window.GetInput();

			player.lastMouseX = input.GetMouseX();
			player.lastMouseY = input.GetMouseY();

			initMousePos = true;
		}
		
		ProcessMouse(Event);

	}	

	ProcessKeyboard();
	
	UpdateProjectiles();	
}

void UpdateProjectiles()
{
	for(int i = 0; i < projectiles.size(); i++)
	{
		projectiles[i].SetPosition(projectiles[i].GetPosition() + projectiles[i].velocity);
		
		for (int k = 0; k < enemies.size(); k++)
		{
			if (projectiles[i].boundingBox.Intersects(enemies[k].boundingBox))
			{
				enemies[k].colour = cml::vector3f(enemies[k].colour[0] + 0.1f, enemies[k].colour[1] - 0.1f, enemies[k].colour[2] - 0.1f);
				projectiles.erase(projectiles.begin() + i);
				k = enemies.size();
			}
			else for(int j = 0; j < 3; j++)
				if(projectiles[i].GetPosition()[j] > 1000 || projectiles[i].GetPosition()[j] < -1000)
				{
					projectiles.erase(projectiles.begin() + i);
					k = enemies.size();
					j = 3;
				}
		}		
	}
}

void ProcessKeyboard()
{
	const sf::Input& input = window.GetInput();
	if (input.IsKeyDown(sf::Key::Escape))
		window.Close();
	
	float speed = 6.f;
	
	//key press events
	// Escape key : exit
	//if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
	//	window.Close();
	if (input.IsKeyDown(sf::Key::W))
	{
	//if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::W))
	//{
		float xrotrad, yrotrad;
		yrotrad = (player.rotY / 180 * 3.141592654f);
		xrotrad = (player.rotX / 180 * 3.141592654f); 
		player.position[0] += float(sin(yrotrad)) * speed ;
		player.position[2] -= float(cos(yrotrad)) * speed;
		player.position[1] -= float(sin(xrotrad)) * speed;
	}

	if (input.IsKeyDown(sf::Key::S))
	{
		float xrotrad, yrotrad;
		yrotrad = (player.rotY / 180 * 3.141592654f);
		xrotrad = (player.rotX / 180 * 3.141592654f); 
		player.position[0] -= float(sin(yrotrad)) * speed;
		player.position[2] += float(cos(yrotrad)) * speed;
		player.position[1] += float(sin(xrotrad)) * speed;
	}

	if (input.IsKeyDown(sf::Key::D))
	{
		float yrotrad;
		yrotrad = (player.rotY / 180 * 3.141592654f);
		player.position[0] += float(cos(yrotrad)) * speed;// * 0.2f;
		player.position[2] += float(sin(yrotrad)) * speed;// * 0.2f;
	}

	if (input.IsKeyDown(sf::Key::A))
	{
		float yrotrad;
		yrotrad = (player.rotY / 180 * 3.141592654f);
		player.position[0] -= float(cos(yrotrad)) * speed;// * 0.2f;
		player.position[2] -= float(sin(yrotrad)) * speed;// * 0.2f;
	}

}

void Draw()
{
	// Clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Apply some transformations
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//glPushMatrix();
	//glTranslatef(0.f, 0.f, 0.f);
	/*
	glRotatef(Clock.GetElapsedTime() * 50, 1.f, 0.f, 0.f);
	glRotatef(Clock.GetElapsedTime() * 30, 0.f, 1.f, 0.f);
	glRotatef(Clock.GetElapsedTime() * 90, 0.f, 0.f, 1.f);
	*/
	//draw outer surrounding box of maze
	//DrawCube(5.f);
	//glPopMatrix();

	//translate camera to player position
	glRotatef(player.rotX,1.0,0.0,0.0);  //rotate our camera on the x-axis (left and right)
	glRotatef(player.rotY,0.0,1.0,0.0);  //rotate our camera on the y-axis (up and down)
	glTranslatef(-player.position[0], -player.position[1], -player.position[2]);

	//Draw enemy1
	glPushMatrix();
	glTranslatef(enemies[0].position[0], enemies[0].position[1], enemies[0].position[2]);
	glRotatef(enemies[0].cubeRotX, 1.f, 0.f, 0.f);
	glRotatef(enemies[0].cubeRotY, 0.f, 1.f, 0.f);
	glRotatef(enemies[0].cubeRotZ, 0.f, 0.f, 1.f);
	DrawCube2(1.f, enemies[0].colour);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(enemies[1].position[0], enemies[1].position[1], enemies[1].position[2]);
	glRotatef(enemies[1].cubeRotX, 1.f, 0.f, 0.f);
	glRotatef(enemies[1].cubeRotY, 0.f, 1.f, 0.f);
	glRotatef(enemies[1].cubeRotZ, 0.f, 0.f, 1.f);
	DrawCube2(1.f, enemies[1].colour);
	glPopMatrix();

	for(int i = 0; i < projectiles.size(); i++)
	{	
		glPushMatrix();
		glTranslatef(projectiles[i].GetPosition()[0], projectiles[i].GetPosition()[1], projectiles[i].GetPosition()[2]);
		DrawCube2(0.25f, projectiles[i].colour);
		glPopMatrix();
				
	}
	

	//glPushMatrix();
	//DrawFace(1.f);
	//DrawCube2(1.f, cml::vector3f(0.3f, 0.9f, 0.6f));
	//glPopMatrix();


	/*
	glPushMatrix();
	glTranslatef(player.position[0], player.position[1], player.position[2]);
	//glTranslatef(0.f, 0.f, -200.f);
	DrawCube(1.f);
	glPopMatrix();
	*/

/*
	float Xvalue = player.position[0];
	std::string coordX = toString(Xvalue);

	float Yvalue = player.position[1];
	std::string coordY = toString(Yvalue);

	float Zvalue = player.position[2];
	std::string coordZ = toString(Zvalue);
	
	sf::String text("Player coords: " + coordX +","+ coordY +","+ coordZ, sf::Font::GetDefaultFont());

	window.Draw(text);*/
	
	window.Display();
}


void DrawCube2(float size)
{
	glBegin(GL_QUADS);

			glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(-50.f * size, -50.f * size, -50.f * size);
            glVertex3f(-50.f * size,  50.f * size, -50.f * size);
            glVertex3f( 50.f * size,  50.f * size, -50.f * size);
            glVertex3f( 50.f * size, -50.f * size, -50.f * size);
		
			glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3f(-50.f * size, -50.f * size, 50.f * size);
            glVertex3f(-50.f * size,  50.f * size, 50.f * size);
            glVertex3f( 50.f * size,  50.f * size, 50.f * size);
            glVertex3f( 50.f * size, -50.f * size, 50.f * size);

			glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f(-50.f * size, -50.f * size, -50.f * size);
            glVertex3f(-50.f * size,  50.f * size, -50.f * size);
            glVertex3f(-50.f * size,  50.f * size,  50.f * size);
            glVertex3f(-50.f * size, -50.f * size,  50.f * size);

			glColor3f(1.0f, 1.0f, 0.0f);
            glVertex3f(50.f * size, -50.f * size, -50.f * size);
            glVertex3f(50.f * size,  50.f * size, -50.f * size);
            glVertex3f(50.f * size,  50.f * size,  50.f * size);
            glVertex3f(50.f * size, -50.f * size,  50.f * size);

			glColor3f(1.0f, 0.0f, 1.0f);
            glVertex3f(-50.f * size, -50.f * size,  50.f * size);
            glVertex3f(-50.f * size, -50.f * size, -50.f * size);
            glVertex3f( 50.f * size, -50.f * size, -50.f * size);
            glVertex3f( 50.f * size, -50.f * size,  50.f * size);

			glColor3f(0.0f, 1.0f, 1.0f);
            glVertex3f(-50.f * size, 50.f * size,  50.f * size);
            glVertex3f(-50.f * size, 50.f * size, -50.f * size);
            glVertex3f( 50.f * size, 50.f * size, -50.f * size);
            glVertex3f( 50.f * size, 50.f * size,  50.f * size);

        glEnd();
}

void DrawFace(float size, cml::vector3f colour)
{
	glBegin(GL_QUADS);

			glColor3f(colour[0], colour[1], colour[2]);
            glVertex3f(-45.f * size, -45.f * size, -50.f * size);
            glVertex3f(-45.f * size,  45.f * size, -50.f * size);
            glVertex3f( 45.f * size,  45.f * size, -50.f * size);
            glVertex3f( 45.f * size, -45.f * size, -50.f * size);
			
			//bottom line
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(-50.f * size, -50.f * size, -50.f * size);
            glVertex3f(-50.f * size, -45.f * size, -50.f * size);
            glVertex3f( 50.f * size, -45.f * size, -50.f * size);
            glVertex3f( 50.f * size, -50.f * size, -50.f * size);

			//top line
			//glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(-50.f * size, 50.f * size, -50.f * size);
            glVertex3f(-50.f * size, 45.f * size, -50.f * size);
            glVertex3f( 50.f * size, 45.f * size, -50.f * size);
            glVertex3f( 50.f * size, 50.f * size, -50.f * size);

			//left line
			glVertex3f(-50.f * size, -50.f * size, -50.f * size);
            glVertex3f(-50.f * size,  50.f * size, -50.f * size);
            glVertex3f(-45.f * size,  50.f * size, -50.f * size);
            glVertex3f(-45.f * size, -50.f * size, -50.f * size);
			
			//right line
			glVertex3f(50.f * size, -50.f * size, -50.f * size);
            glVertex3f(50.f * size,  50.f * size, -50.f * size);
            glVertex3f(45.f * size,  50.f * size, -50.f * size);
            glVertex3f(45.f * size, -50.f * size, -50.f * size);

	glEnd();

}

void DrawCube2(float size, cml::vector3f colour)
{
	glPushMatrix();

	DrawFace(size, colour);

	glRotatef(90, 0.f, 1.f, 0.f);
	DrawFace(size, colour);

	glRotatef(90, 0.f, 1.f, 0.f);
	DrawFace(size, colour);

	glRotatef(90, 0.f, 1.f, 0.f);
	DrawFace(size, colour);

	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1.f, 0.f, 0.f);
	DrawFace(size, colour);

	glRotatef(180, 1.f, 0.f, 0.f);
	DrawFace(size, colour);

	glPopMatrix();
	
}

void Initialize()
{
	window.EnableKeyRepeat(false);
	window.UseVerticalSync(true);
	
	enemies.push_back(SpaceShip::Enemy(cml::vector3f(200,0,-200), cml::vector3f(0.3f, 1.f, 0.3f), SpaceShip::BoundingBox(cml::vector3f(200,0,-200), 100, 100, 100)));//cml::vector3f(50,50,50), cml::vector3f(-50,-50,-50)));
	enemies.push_back(SpaceShip::Enemy(cml::vector3f(-200,0,-200), cml::vector3f(0.3f, 1.f, 0.3f), SpaceShip::BoundingBox(cml::vector3f(-200,0,-200), 100, 100, 100)));//cml::vector3f(50,50,50), cml::vector3f(-50,-50,-50)));
/*
	if (!initMousePos)
	{
		const sf::Input& input = window.GetInput();

		player.lastMouseX = input.GetMouseX();
		player.lastMouseY = input.GetMouseY();

		initMousePos = true;
	}*/

	// Set color and depth clear value
    glClearDepth(1.f);
    glClearColor(0.3f, 0.7f, 0.7f, 0.f);

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    // Setup a perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.f, 1.f, 1.f, 2000.f);
	
	/*
	const sf::Input& input = window.GetInput();
	player.lastMouseX = input.GetMouseX();
	player.lastMouseY = input.GetMouseY();
	*/
	
}

static std::string toString(float value) 
{ 
	std::ostringstream stream; 
	stream << value; 
	return stream.str(); 
} 

void ProcessMouse(sf::Event Event)
{
	if (Event.Type == sf::Event::MouseButtonPressed && Event.MouseButton.Button == sf::Mouse::Left)
		{
			cml::vector3f initialVector = cml::vector3f(0,0,-5); //initial vector to transform, projectiles have speed of 5
		
			//convert player's rotation to radians and create rotation matrices
			cml::matrix44f_r xrotMatrix;
			cml::matrix_rotation_world_x(xrotMatrix, cml::rad(-player.rotX)); 

			cml::matrix44f_r yrotMatrix;
			cml::matrix_rotation_world_y(yrotMatrix, cml::rad(-player.rotY));

			cml::matrix44f_r zrotMatrix;
			cml::matrix_rotation_world_z(zrotMatrix, cml::rad(-player.rotZ));

			//multiply the three matrices together into one final matrix
			cml::matrix44f_r finalMatrix(cml::operator *(cml::operator *(xrotMatrix, yrotMatrix), zrotMatrix));
				
				//xrotMatrix cml::operator * yrotMatrix cml::operator * zrotMatrix;
			//cml::operator * 

			//apply the matrix rotation information to the vector to make it face in the right direction
			initialVector = cml::transform_vector(finalMatrix, initialVector);
						
			//add projectile with the velocity in initialVector
			projectiles.push_back(SpaceShip::Projectile(player.position, cml::vector3f(1.f,1.f,1.f), SpaceShip::BoundingBox(player.position, 25,25,25), initialVector));
			
		}

	MouseMovement();
}

void MouseMovement()
{	
	float diffx = player.mouseX - player.lastMouseX; //check the difference between the current x and the last x position
	float diffy = player.mouseY - player.lastMouseY; //check the difference between the current y and the last y position
	player.lastMouseX = player.mouseX; //set lastx to the current x position
	player.lastMouseY = player.mouseY; //set lasty to the current y position
	player.rotX += diffy; //set the xrot to xrot with the addition of the difference in the y position
	player.rotY += diffx;    //set the xrot to yrot with the addition of the difference in the x position
}

