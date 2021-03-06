#pragma once
#include "Module.h"
#include "Globals.h"
#include "Box2D/Box2D/Box2D.h"


#define GRAVITY_X 0.0f
#define GRAVITY_Y -7.0f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)


class PhysBody
{
public:
	PhysBody() : listener(NULL), body(NULL)
	{}

	void GetPosition(int& x, int &y) const;
	float GetRotation() const;
	bool Contains(int x, int y) const;
	int RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const;
	void Clickers_force(int degrees);
	double getAngle() const;
	void SetSprite(const int&  x, const int & y, const int&  w, const int& h) {
		sprite.h = h;
		sprite.w = w;
		sprite.x = x;
		sprite.y = y;
	}

	void SetSpritefx(const int&  x, const int & y, const int&  w, const int& h) {

		spritefx.h = h;
		spritefx.w = w;
		spritefx.x = x;
		spritefx.y = y;
	}
	SDL_Rect& GetSprite() {
		return sprite;
	}
	SDL_Rect& GetSpritefx() {
		return spritefx;
	}
	
public:
	int width, height;
	b2Body* body;
	Module* listener;
	bool IsTrodden = false;
	SDL_Rect sprite;
	SDL_Rect spritefx;

};

// Module --------------------------------------
class ModulePhysics : public Module, public b2ContactListener // TODO
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	bool mousein=false;
	b2Body* mousebody= nullptr;

	PhysBody* CreateCircle(int x, int y, int radius, float Rest, bool _bullet, b2BodyType type);
	PhysBody* CreateRectangle(int x, int y, int width, int height);
	PhysBody* CreateRectangleSensor(int x, int y, int width, int height);
	PhysBody* CreateChain(int x, int y, int* points, int size, b2BodyType type);
	PhysBody* CreateChainSensor(int x, int y, int* points, int size);
	PhysBody* CreateSensorBall(int x, int y, int* points, int size, bool sensor);
	PhysBody* CreatePolygon(b2Vec2* vertices1, int count1, b2BodyType type, int x, int y, float Rest);
	void CreateRevoluteJoint(b2Body* bodyA, b2Body* bodyB, int upperangle, int lowerangle, int pivot_x, int pivot_y);
	void CreateUpJoint(PhysBody* bodyA, PhysBody* bodyB, b2Vec2 ancorA, b2Vec2 ancorB, int max, int min, int maxMotor, int motorSpeed);

	void DestroyBody(b2Body* body);

	
	void BeginContact(b2Contact* contact);
	b2Body* ground;
	

	p2List<b2RevoluteJoint*> paddleList;
	
	b2Body* b;
	
	b2PrismaticJoint* joint;

private:

	bool debug;
	b2World* world;
	b2MouseJoint* mouse_joint;
	
};