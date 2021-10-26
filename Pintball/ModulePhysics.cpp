#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "ModuleSceneIntro.h"
#include "p2Point.h"
#include "math.h"

#ifdef _DEBUG
#pragma comment( lib, "Box2D/libx86/Debug/Box2D.lib" )
#else
#pragma comment( lib, "Box2D/libx86/Release/Box2D.lib" )
#endif

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	world = NULL;
	mouse_joint = NULL;
	debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));
	world->SetContactListener(this);
	App->renderer->camera.x = App->renderer->camera.y = 0;

	//map = App->textures->load("pinball/wheel.png");

	// needed to create joints like mouse joint
	b2BodyDef bd;
	ground = world->CreateBody(&bd);	

	
	//map limits
	{ 
		//V2
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
		b2BodyDef body;
		body.type = b2_staticBody;
		body.position.Set(PIXEL_TO_METERS(0), PIXEL_TO_METERS(0) * 0.8f);

		b2Body* big_Map = world->CreateBody(&body);
		b2Vec2 points1[33];

		for (int i = 0; i < 27; i++)
		{
			points1[i].x = PIXEL_TO_METERS(Pinball_Map[i * 2]);
			points1[i].y = PIXEL_TO_METERS(Pinball_Map[(i * 2) + 1]);
		}

		b2ChainShape Chain;
		Chain.CreateLoop(points1, 27);
		b2FixtureDef fixture;
		fixture.shape = &Chain;
		fixture.density = 1.0f;
		big_Map->CreateFixture(&fixture);

		b2BodyDef bd2;
		ground = world->CreateBody(&bd2);
	}
	//P.esquerra1
	{
	int Pquerra[14] = {
	51, 148,
	33, 235,
	33, 348,
	107, 270,
	132, 264,
	112, 184,
	50, 148
	};
	b2BodyDef body2;
	body2.type = b2_staticBody;
	body2.position.Set(PIXEL_TO_METERS(0), PIXEL_TO_METERS(0)* 0.8f);

	b2Body* big_Map2 = world->CreateBody(&body2);
	b2Vec2 points2[7];

	for (int i = 0; i < 7; i++)
	{
		points2[i].x = PIXEL_TO_METERS(Pquerra[i * 2]);
		points2[i].y = PIXEL_TO_METERS(Pquerra[(i * 2) + 1]);
	}

	b2ChainShape Chain2;
	Chain2.CreateLoop(points2, 7);
	b2FixtureDef fixture2;
	fixture2.shape = &Chain2;
	fixture2.density = 1.0f;
	big_Map2->CreateFixture(&fixture2);
	}//P.esquerra1
	//P.esquerra2
	{
	int Pquerra[14] = {
	56, 647,
	55, 771,
	140, 857,
	155, 843,
	61, 749,
	60, 647,
	55, 647
	};
	b2BodyDef body2;
	body2.type = b2_staticBody;
	body2.position.Set(PIXEL_TO_METERS(0), PIXEL_TO_METERS(0)* 0.8f);

	b2Body* big_Map2 = world->CreateBody(&body2);
	b2Vec2 points2[7];

	for (int i = 0; i < 7; i++)
	{
		points2[i].x = PIXEL_TO_METERS(Pquerra[i * 2]);
		points2[i].y = PIXEL_TO_METERS(Pquerra[(i * 2) + 1]);
	}

	b2ChainShape Chain2;
	Chain2.CreateLoop(points2, 7);
	b2FixtureDef fixture2;
	fixture2.shape = &Chain2;
	fixture2.density = 1.0f;
	big_Map2->CreateFixture(&fixture2);
	}
	//P.dreta1
	{
	int Pdreta[14] = {
	 329, 190,
	388, 151,
	397, 229,
	396, 352,
	324, 274,
	299, 266,
	328, 190
	};
	b2BodyDef body3;
	body3.type = b2_staticBody;
	body3.position.Set(PIXEL_TO_METERS(0), PIXEL_TO_METERS(0) * 0.8f);

	b2Body* big_Map3 = world->CreateBody(&body3);
	b2Vec2 points3[7];

	for (int i = 0; i < 7; i++)
	{
		points3[i].x = PIXEL_TO_METERS(Pdreta[i * 2]);
		points3[i].y = PIXEL_TO_METERS(Pdreta[(i * 2) + 1]);
	}

	b2ChainShape Chain3;
	Chain3.CreateLoop(points3, 7);
	b2FixtureDef fixture3;
	fixture3.shape = &Chain3;
	fixture3.density = 1.0f;
	big_Map3->CreateFixture(&fixture3);
	}//P.dreta2
	//P.dreta2
	{
	int Pdreta[14] = {
	381, 646,
	380, 747,
	285, 843,
	301, 858,
	385, 772,
	385, 646,
	380, 646
	};
	b2BodyDef body3;
	body3.type = b2_staticBody;
	body3.position.Set(PIXEL_TO_METERS(0), PIXEL_TO_METERS(0) * 0.8f);

	b2Body* big_Map3 = world->CreateBody(&body3);
	b2Vec2 points3[7];

	for (int i = 0; i < 7; i++)
	{
		points3[i].x = PIXEL_TO_METERS(Pdreta[i * 2]);
		points3[i].y = PIXEL_TO_METERS(Pdreta[(i * 2) + 1]);
	}

	b2ChainShape Chain3;
	Chain3.CreateLoop(points3, 7);
	b2FixtureDef fixture3;
	fixture3.shape = &Chain3;
	fixture3.density = 1.0f;
	big_Map3->CreateFixture(&fixture3);
	}
	//Wall Ball
	{
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
	b2BodyDef body4;
	body4.type = b2_staticBody;
	body4.position.Set(PIXEL_TO_METERS(0), PIXEL_TO_METERS(0) * 0.8f);

	b2Body* big_Map4 = world->CreateBody(&body4);
	b2Vec2 points4[12];

	for (int i = 0; i < 12; i++)
	{
		points4[i].x = PIXEL_TO_METERS(Limit_ball[i * 2]);
		points4[i].y = PIXEL_TO_METERS(Limit_ball[(i * 2) + 1]);
	}

	b2ChainShape Chain4;
	Chain4.CreateLoop(points4, 12);
	b2FixtureDef fixture4;
	fixture4.shape = &Chain4;
	fixture4.density = 1.0f;
	big_Map4->CreateFixture(&fixture4);
	}
	//Tesquerra
	{
		int Tesquerra[8] = {
			99, 655,
	98, 735,
	160, 798,
	98, 655
		};
		b2BodyDef body5;
		body5.type = b2_staticBody;
		body5.position.Set(PIXEL_TO_METERS(0), PIXEL_TO_METERS(0) * 0.8f);

		b2Body* big_Map5 = world->CreateBody(&body5);
		b2Vec2 points5[4];

		for (int i = 0; i < 4; i++)
		{
			points5[i].x = PIXEL_TO_METERS(Tesquerra[i * 2]);
			points5[i].y = PIXEL_TO_METERS(Tesquerra[(i * 2) + 1]);
		}

		b2ChainShape Chain5;
		Chain5.CreateLoop(points5, 4);
		b2FixtureDef fixture5;
		fixture5.shape = &Chain5;
		fixture5.density = 1.0f;
		big_Map5->CreateFixture(&fixture5);
	}
	//Tdreta
	{
	int Tdreta[8] = {
			347, 652,
	282, 797,
	345, 733,
	346, 652
	};
	b2BodyDef body6;
	body6.type = b2_staticBody;
	body6.position.Set(PIXEL_TO_METERS(0), PIXEL_TO_METERS(0) * 0.8f);

	b2Body* big_Map6 = world->CreateBody(&body6);
	b2Vec2 points6[4];

	for (int i = 0; i < 4; i++)
	{
		points6[i].x = PIXEL_TO_METERS(Tdreta[i * 2]);
		points6[i].y = PIXEL_TO_METERS(Tdreta[(i * 2) + 1]);
	}

	b2ChainShape Chain6;
	Chain6.CreateLoop(points6, 4);
	b2FixtureDef fixture6;
	fixture6.shape = &Chain6;
	fixture6.density = 1.0f;
	big_Map6->CreateFixture(&fixture6);
	}
	//Qesquerra
	{
		int Qesquerra[10] = {
		152, 177,
		171, 256,
		195, 251,
		176, 172,
		151, 177
		};
		b2BodyDef body7;
		body7.type = b2_staticBody;
		body7.position.Set(PIXEL_TO_METERS(0), PIXEL_TO_METERS(0) * 0.8f);

		b2Body* big_Map7 = world->CreateBody(&body7);
		b2Vec2 points7[5];

		for (int i = 0; i < 5; i++)
		{
			points7[i].x = PIXEL_TO_METERS(Qesquerra[i * 2]);
			points7[i].y = PIXEL_TO_METERS(Qesquerra[(i * 2) + 1]);
		}

		b2ChainShape Chain7;
		Chain7.CreateLoop(points7, 5);
		b2FixtureDef fixture7;
		fixture7.shape = &Chain7;
		fixture7.density = 1.0f;
		big_Map7->CreateFixture(&fixture7);
	}
	//QDreta
	{
		int Qdreta[10] = {
		269, 171,
		242, 247,
		265, 256,
		293, 180,
		268, 171
		};
		b2BodyDef body8;
		body8.type = b2_staticBody;
		body8.position.Set(PIXEL_TO_METERS(0), PIXEL_TO_METERS(0) * 0.8f);

		b2Body* big_Map8 = world->CreateBody(&body8);
		b2Vec2 points8[5];

		for (int i = 0; i < 5; i++)
		{
			points8[i].x = PIXEL_TO_METERS(Qdreta[i * 2]);
			points8[i].y = PIXEL_TO_METERS(Qdreta[(i * 2) + 1]);
		}

		b2ChainShape Chain8;
		Chain8.CreateLoop(points8, 5);
		b2FixtureDef fixture8;
		fixture8.shape = &Chain8;
		fixture8.density = 1.0f;
		big_Map8->CreateFixture(&fixture8);
	}
	//bola
	{
		Ball = CreateCircle(positionPX, positionPY, 14);

		/*Ball.type = b2_dynamicBody;
		Ball.position.Set(10, 18);

		b2Body* b = world->CreateBody(&Ball);

		b2CircleShape shape;
		shape.m_radius = PIXEL_TO_METERS(12);
		b2FixtureDef fixture;
		fixture.shape = &shape;
		fixture.density = 1.0f;

		b->CreateFixture(&fixture);

		PhysBody* pbody = new PhysBody();
		pbody->body = b;
		b->SetUserData(pbody);
		pbody->width = pbody->height = 5;*/

	}
	//BolaObj1
	{
		b2BodyDef body;
		body.type = b2_staticBody;
		body.position.Set(4.4, 1.75);

		b2Body* b = world->CreateBody(&body);

		b2CircleShape shape;
		shape.m_radius = PIXEL_TO_METERS(46);
		b2FixtureDef fixture;
		fixture.shape = &shape;
		fixture.density = 1.0f;

		b->CreateFixture(&fixture);

		PhysBody* pbody = new PhysBody();
		pbody->body = b;
		b->SetUserData(pbody);
		pbody->width = pbody->height = 46;
	}
	//BolaObj2
	{
		b2BodyDef body;
		body.type = b2_staticBody;
		body.position.Set(3.05, 7.56);

		b2Body* b = world->CreateBody(&body);

		b2CircleShape shape;
		shape.m_radius = PIXEL_TO_METERS(40);
		b2FixtureDef fixture;
		fixture.shape = &shape;
		fixture.density = 1.0f;

		b->CreateFixture(&fixture);

		PhysBody* pbody = new PhysBody();
		pbody->body = b;
		b->SetUserData(pbody);
		pbody->width = pbody->height = 40;
	}
	//BolaObj3
	{
		b2BodyDef body;
		body.type = b2_staticBody;
		body.position.Set(5.85, 7.56);

		b2Body* b = world->CreateBody(&body);

		b2CircleShape shape;
		shape.m_radius = PIXEL_TO_METERS(40);
		b2FixtureDef fixture;
		fixture.shape = &shape;
		fixture.density = 1.0f;

		b->CreateFixture(&fixture);

		PhysBody* pbody = new PhysBody();
		pbody->body = b;
		b->SetUserData(pbody);
		pbody->width = pbody->height = 40;
	}
	//BolaObj4
	{
		b2BodyDef body;
		body.type = b2_staticBody;
		body.position.Set(4.46, 9.8);

		b2Body* b = world->CreateBody(&body);

		b2CircleShape shape;
		shape.m_radius = PIXEL_TO_METERS(40);
		b2FixtureDef fixture;
		fixture.shape = &shape;
		fixture.density = 1.0f;

		b->CreateFixture(&fixture);

		PhysBody* pbody = new PhysBody();
		pbody->body = b;
		b->SetUserData(pbody);
		pbody->width = pbody->height = 40;
	}
	//Stick Dret
	{
	
		RecD = CreateRectangle(300, 790, 60, 12);
		CerD = App->physics->CreateCircle(300, 850, 2);
		CerD->body->SetType(b2_staticBody);

		StickD.bodyA = RecD->body;
		StickD.bodyB = CerD->body;

		StickD.referenceAngle = 0 * DEGTORAD;
		StickD.enableLimit = true;

		StickD.lowerAngle = -30 * DEGTORAD;
		StickD.upperAngle = 30 * DEGTORAD;

		StickD.localAnchorA.Set(PIXEL_TO_METERS(48), 0.2);
		StickD.localAnchorB.Set(0, 0);

		b2RevoluteJoint* StickDer = (b2RevoluteJoint*)App->physics->world->CreateJoint(&StickD);
	}
	//Stick Esquerra
	{
		RecE = CreateRectangle(125, 790, 60, 12);
		CerE = App->physics->CreateCircle(140, 850, 2);
		CerE->body->SetType(b2_staticBody);

		StickE.bodyA = RecE->body;
		StickE.bodyB = CerE->body;

		StickE.referenceAngle = 0 * DEGTORAD;
		StickE.enableLimit = true;

		StickE.lowerAngle = -30 * DEGTORAD;
		StickE.upperAngle = 30 * DEGTORAD;

		StickE.localAnchorA.Set(PIXEL_TO_METERS(-48), 0.2);
		StickE.localAnchorB.Set(0, 0);

		b2RevoluteJoint* StickEsq = (b2RevoluteJoint*)App->physics->world->CreateJoint(&StickE);
	}
	//Bar Up
	{
	
	Barup = CreateRectangle(488, 953, 25, 12);
	LineBarup = CreateRectangle(488, 953, 5, 20);
	LineBarup->body->SetType(b2_staticBody);

	bar.bodyA = Barup->body;
	bar.bodyB = LineBarup->body;

	bar.collideConnected = false;
	bar.enableLimit = true;

	bar.upperTranslation = PIXEL_TO_METERS(50);
	bar.lowerTranslation = PIXEL_TO_METERS(10);
	bar.localAxisA.Set(0, 10);

	b2PrismaticJoint* PushUpBall = (b2PrismaticJoint*)App->physics->world->CreateJoint(&bar);
	}
	
	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	world->Step(1.0f / 60.0f, 6, 2);

	for(b2Contact* c = world->GetContactList(); c; c = c->GetNext())
	{
		if(c->GetFixtureA()->IsSensor() && c->IsTouching())
		{
			PhysBody* pb1 = (PhysBody*)c->GetFixtureA()->GetBody()->GetUserData();
			PhysBody* pb2 = (PhysBody*)c->GetFixtureA()->GetBody()->GetUserData();
			if(pb1 && pb2 && pb1->listener)
				pb1->listener->OnCollision(pb1, pb2);
		}
	}

	return UPDATE_CONTINUE;
}

PhysBody* ModulePhysics::CreateCircle(int x, int y, int radius)
{
	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2CircleShape ball;
	ball.m_radius = PIXEL_TO_METERS(radius);
	b2FixtureDef fixture;
	fixture.shape = &ball;
	fixture.density = 1.0f;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = radius;

	return pbody;
}

PhysBody* ModulePhysics::CreateRectangle(int x, int y, int width, int height)
{
	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);
	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = width * 0.5f;
	pbody->height = height * 0.5f;

	return pbody;
}

PhysBody* ModulePhysics::CreateRectangleSensor(int x, int y, int width, int height)
{
	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;
	fixture.isSensor = true;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = width;
	pbody->height = height;

	return pbody;
}

PhysBody* ModulePhysics::CreateCircleSensor(int x, int y, int radius)
{
	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2CircleShape ball;
	ball.m_radius = PIXEL_TO_METERS(radius);
	b2FixtureDef fixture;
	fixture.shape = &ball;
	fixture.density = 1.0f;
	fixture.isSensor = true;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = radius;

	return pbody;
}

PhysBody* ModulePhysics::CreateChain(int x, int y, int* points, int size)
{
	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2ChainShape shape;
	b2Vec2* p = new b2Vec2[size / 2];

	for(uint i = 0; i < size / 2; ++i)
	{
		p[i].x = PIXEL_TO_METERS(points[i * 2 + 0]);
		p[i].y = PIXEL_TO_METERS(points[i * 2 + 1]);
	}

	shape.CreateLoop(p, size / 2);

	b2FixtureDef fixture;
	fixture.shape = &shape;

	b->CreateFixture(&fixture);

	delete p;

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = 0;

	return pbody;
}

// 
update_status ModulePhysics::PostUpdate()
{
	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	for(b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch(f->GetType())
			{
				// Draw circles ------------------------------------------------
				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), METERS_TO_PIXELS(shape->m_radius), 255, 255, 255);
				}
				break;

				// Draw polygons ------------------------------------------------
				case b2Shape::e_polygon:
				{
					b2PolygonShape* polygonShape = (b2PolygonShape*)f->GetShape();
					int32 count = polygonShape->GetVertexCount();
					b2Vec2 prev, v;

					for(int32 i = 0; i < count; ++i)
					{
						v = b->GetWorldPoint(polygonShape->GetVertex(i));
						if(i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);

						prev = v;
					}

					v = b->GetWorldPoint(polygonShape->GetVertex(0));
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);
				}
				break;

				// Draw chains contour -------------------------------------------
				case b2Shape::e_chain:
				{
					b2ChainShape* shape = (b2ChainShape*)f->GetShape();
					b2Vec2 prev, v;

					for(int32 i = 0; i < shape->m_count; ++i)
					{
						v = b->GetWorldPoint(shape->m_vertices[i]);
						if(i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
						prev = v;
					}

					v = b->GetWorldPoint(shape->m_vertices[0]);
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
				}
				break;

				// Draw a single segment(edge) ----------------------------------
				case b2Shape::e_edge:
				{
					b2EdgeShape* shape = (b2EdgeShape*)f->GetShape();
					b2Vec2 v1, v2;

					v1 = b->GetWorldPoint(shape->m_vertex0);
					v1 = b->GetWorldPoint(shape->m_vertex1);
					App->renderer->DrawLine(METERS_TO_PIXELS(v1.x), METERS_TO_PIXELS(v1.y), METERS_TO_PIXELS(v2.x), METERS_TO_PIXELS(v2.y), 100, 100, 255);
				}
				break;
			}

			// TODO 1: If mouse button 1 is pressed ...
			// App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN
			// test if the current body contains mouse position
		}
	}

	// If a body was selected we will attach a mouse joint to it
	// so we can pull it around
	// TODO 2: If a body was selected, create a mouse joint
	// using mouse_joint class property


	// TODO 3: If the player keeps pressing the mouse button, update
	// target position and draw a red line between both anchor points

	// TODO 4: If the player releases the mouse button, destroy the joint

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!
	delete world;

	return true;
}

void PhysBody::GetPosition(int& x, int &y) const
{
	b2Vec2 pos = body->GetPosition();
	x = METERS_TO_PIXELS(pos.x) - (width);
	y = METERS_TO_PIXELS(pos.y) - (height);
}

float PhysBody::GetRotation() const
{
	return RADTODEG * body->GetAngle();
}

bool PhysBody::Contains(int x, int y) const
{
	b2Vec2 p(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	const b2Fixture* fixture = body->GetFixtureList();

	while(fixture != NULL)
	{
		if(fixture->GetShape()->TestPoint(body->GetTransform(), p) == true)
			return true;
		fixture = fixture->GetNext();
	}

	return false;
}

int PhysBody::RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const
{
	int ret = -1;

	b2RayCastInput input;
	b2RayCastOutput output;

	input.p1.Set(PIXEL_TO_METERS(x1), PIXEL_TO_METERS(y1));
	input.p2.Set(PIXEL_TO_METERS(x2), PIXEL_TO_METERS(y2));
	input.maxFraction = 1.0f;

	const b2Fixture* fixture = body->GetFixtureList();

	while(fixture != NULL)
	{
		if(fixture->GetShape()->RayCast(&output, input, body->GetTransform(), 0) == true)
		{
			// do we want the normal ?

			float fx = x2 - x1;
			float fy = y2 - y1;
			float dist = sqrtf((fx*fx) + (fy*fy));

			normal_x = output.normal.x;
			normal_y = output.normal.y;

			return output.fraction * dist;
		}
		fixture = fixture->GetNext();
	}

	return ret;
}

void ModulePhysics::BeginContact(b2Contact* contact)
{
	PhysBody* physA = (PhysBody*)contact->GetFixtureA()->GetBody()->GetUserData();
	PhysBody* physB = (PhysBody*)contact->GetFixtureB()->GetBody()->GetUserData();

	if(physA && physA->listener != NULL)
		physA->listener->OnCollision(physA, physB);
	
	if (physA == App->scene_intro->Push_Sensor)
	{
		PAudio = true;
	}

	if (physA == App->scene_intro->Loose)
	{
		if (App->scene_intro->vidas > 1)
		{
			App->scene_intro->death = true;
			App->scene_intro->vidas--;
		}
		else {
		App->scene_intro->vidas--;
		}
		
	}
	
	if (physA == App->scene_intro->circle1 || physA == App->scene_intro->circle2 || physA == App->scene_intro->circle3 || physA == App->scene_intro->circle4)
	{
		App->scene_intro->score += 100;
	}

	if(physB && physB->listener != NULL)
		physB->listener->OnCollision(physB, physA);
}