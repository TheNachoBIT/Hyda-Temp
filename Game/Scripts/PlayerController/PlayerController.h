#ifndef GAME_PLAYERCONTROLLER_H
#define GAME_PLAYERCONTROLLER_H

#include "geometria.h"
#include "Physics/Rigidbody/Rigidbody.h"

struct PlayerController : public ScriptBehaviour
{
	void OnStartup();

	void OnStart();
	void CameraUpdate();
	void OnUpdate();

	float interpVelocity = 0;
	Vector3 offset, targetPos;
	float cameraY = 1.5f;
	bool isGrounded = false;
	Camera* camera = nullptr;
	bool reverse = false;
	bool audioPlayed = false;
	bool canStart = false;
	int speed = 6;
	Rigidbody* rb = nullptr;
	BoxCollider* bC = nullptr;
};

#endif