#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "PhysVehicle3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	s.size = vec3(5, 3, 1);
	s.SetPos(0, 2.5f, 20);


	Cube ramp_up(22, 2, 46);
	ramp_up.SetPos(5, 0, 69.5);
	ramp_up.SetRotation(-15, vec3(1, 0, 0));
	App->physics->AddBody(ramp_up, 0);

	Cube ramp_down(22, 2, 46);
	ramp_down.SetPos(5, 0, 138);
	ramp_down.SetRotation(15, vec3(1, 0, 0));
	App->physics->AddBody(ramp_down, 0);

	Cube roof(22, 2, 25);
	roof.SetPos(5, 6, 104);
	App->physics->AddBody(roof, 0);

	sensor = App->physics->AddBody(s, 0.0f);
	sensor->SetAsSensor(true);
	sensor->collision_listeners.add(this);

	//map collisions
	Cube wall1(310, 10, 10);
	wall1.SetPos(0, 0, 0);
	App->physics->AddBody(wall1, 0);

	Cube wall2(10, 10, 300);
	wall2.SetPos(-150, 0, 155);
	App->physics->AddBody(wall2, 0);

	Cube wall3(10, 10, 300);
	wall3.SetPos(150, 0, 155);
	App->physics->AddBody(wall3, 0);

	Cube wall4(310, 10, 10);
	wall4.SetPos(0, 0, 310);
	App->physics->AddBody(wall4, 0);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = false;
	p.Render();


	Cube ramp_up(22, 2, 46);
	ramp_up.SetPos(5, 0, 69.5);
	ramp_up.SetRotation(-15, vec3(1, 0, 0));
	ramp_up.Render();


	Cube ramp_down(22, 2, 46);
	ramp_down.SetPos(5, 0, 138);
	ramp_down.SetRotation(15, vec3(1, 0, 0));
	ramp_down.Render();

	Cube roof(22, 2, 25);
	roof.SetPos(5, 6, 104);
	roof.Render();

	//map
	Cube wall1(310, 10, 10);
	wall1.SetPos(0, 0, 0);
	wall1.Render();

	Cube wall2(10, 10, 300);
	wall2.SetPos(-150, 0, 155);
	wall2.Render();

	Cube wall3(10, 10, 300);
	wall3.SetPos(150, 0, 155);
	wall3.Render();

	Cube wall4(310, 10, 10);
	wall4.SetPos(0, 0, 310);
	wall4.Render();

	sensor->GetTransform(&s.transform);
	s.Render();

	char title[150];
	sprintf_s(title, "%.1f Km/h ", App->player->vehicle->GetKmh());
	App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	LOG("Hit!");
}
