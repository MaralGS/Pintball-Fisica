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

// Small class to return to other modules to track position and rotation of physics bodies
class PhysBody
{
public:
	PhysBody() : listener(NULL), body(NULL)
	{}

	void GetPosition(int& x, int &y) const;
	float GetRotation() const;
	bool Contains(int x, int y) const;
	int RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const;

public:
	int width, height;
	b2Body* body;
	Module* listener;
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

	PhysBody* CreateCircle(int x, int y, int radius);
	PhysBody* CreateRectangle(int x, int y, int width, int height, float rotation);
	PhysBody* CreateBlocker(int x, int y, int width, int height, float rotation);
	PhysBody* CreateRectangleSensor(int x, int y, int width, int height, float rotation);
	PhysBody* CreateCircleSensor(int x, int y, int radius);
	PhysBody* CreateChain(int x, int y, int* points, int size);
	b2RevoluteJointDef StickE;
	b2RevoluteJointDef StickD;
	b2PrismaticJointDef bar;
	PhysBody* RecE;
	PhysBody* CerE;
	PhysBody* RecD;
	PhysBody* CerD;
	PhysBody* Barup;
	PhysBody* LineBarup;
	bool PAudio = false;
	bool Puntuacio = false;

	//walls
	int Pinball_Map[54] = {
	255, 953,
	504, 954,
504, 210,
495, 166,
476, 127,
454, 96,
434, 75,
398, 47,
347, 22,
298, 10,
249, 6,
188, 7,
143, 19,
96, 43,
50, 86,
30, 114,
10, 162,
2, 197,
0, 361,
25, 427,
48, 520,
26, 600,
26, 788,
184, 955,
184, 1108,
254, 1108,
254, 953
	};
	int Pquerra1[14] = {
	51, 148,
	33, 235,
	33, 348,
	107, 270,
	132, 264,
	112, 184,
	50, 148
	};
	int Pquerra2[14] = {
	56, 647,
	55, 771,
	140, 857,
	155, 843,
	61, 749,
	60, 647,
	55, 647
	};
	int Pdreta1[14] = {
 329, 190,
388, 151,
397, 229,
396, 352,
324, 274,
299, 266,
328, 190
	};
	int Pdreta2[14] = {
	381, 646,
	380, 747,
	285, 843,
	301, 858,
	385, 772,
	385, 646,
	380, 646
	};
	int Limit_ball[24] = {
		470, 952,
470, 198,
462, 178,
456, 165,
451, 172,
438, 223,
437, 360,
414, 414,
391, 509,
414, 587,
414, 787,
254, 952
	};
	int Tesquerra[8] = {
			99, 655,
	98, 735,
	160, 798,
	98, 655
	};
	int Tdreta[8] = {
			347, 652,
	282, 797,
	345, 733,
	346, 652
	};
	int Qesquerra[10] = {
		152, 177,
		171, 256,
		195, 251,
		176, 172,
		151, 177
	};
	int Qdreta[10] = {
	269, 171,
	242, 247,
	265, 256,
	293, 180,
	268, 171
	};
	// b2ContactListener ---
	void BeginContact(b2Contact* contact);

private:

	bool debug;
	b2World* world;
	b2MouseJoint* mouse_joint;
	b2Body* ground;
	b2Body* mouseB;
};