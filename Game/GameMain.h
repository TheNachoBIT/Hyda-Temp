#pragma once

#include "geometria.h"
#include "Scripts/PlayerController/PlayerController.h"

struct SortingSpikeTest : public ScriptBehaviour
{
	void OnUpdate()
	{
		if(Input::GetKeyDown(GLFW_KEY_UP))
			GetTransform().position = Vector3(GetTransform().position.x, GetTransform().position.y, -0.0001f);
		else if(Input::GetKeyDown(GLFW_KEY_DOWN))
			GetTransform().position = Vector3(GetTransform().position.x, GetTransform().position.y, 0.0001f);
	}
};

struct GameMain
{
	static Model* InitPlayer(Texture* playerTexture)
	{
		Model* m = new Model(Model::Primitives::SQUARE, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));
		m->texture = playerTexture;
		PlayerController* pC = m->AddScript<PlayerController>();
		pC->camera = Graphics::MainCamera();
		Rigidbody* r = m->AddScript<Rigidbody>();
		r->freezePositionZ = true;
		r->freezePositionX = true;
		pC->rb = r;
		m->AddScript<BoxCollider>();
		return m;
	}

	static void Init()
	{
		DrawCall* firstD = SceneManager::MainScene().CreateDrawCall();
		//firstD->sort = DrawCall::Sorting::AtStartup;
		//firstD->Close();

		Texture* playerTexture = new Texture("Game/Textures/Player/1.png", Texture::Type::Default);
		Texture* spikeTexture = new Texture("Game/Textures/Spikes/spike1.png", Texture::Type::Default);
		Texture* backgroundTexture = new Texture("Game/Textures/Backgrounds/bg2.png", Texture::Type::Default);
		Texture* groundTexture = new Texture("Game/Textures/Grounds/g1.png", Texture::Type::Default);
		TextureManager::UploadToGPU();

		Model* player = InitPlayer(playerTexture);
		RendererCore::AddModel(*player, firstD->Target());

		//Model* ground = new Model(Model::Primitives::SQUARE, Vector3(0, -2, 0), Vector3(0, 0, 0), Vector3(10000, 2, 1));
		//ground->color = Color(0, 0, 0, 1);
		//ground->AddScript<BoxCollider>();
		//RendererCore::AddModel(*ground, firstD->Target());

		int xPosGround = -64;
		Color gC = Color(1, 0, 0, 1);
		for(int i = 0; i < 50; i++)
		{
			Model* ground = new Model(Model::Primitives::SQUARE, Vector3(xPosGround, -4, 0), Vector3(0, 0, 0), Vector3(6.1, 6, 1));
			ground->color = gC;
			ground->texture = groundTexture;
			ground->AddScript<BoxCollider>();
			RendererCore::AddModel(*ground, firstD->Target());
			xPosGround += 6;
		}

		Model* spike = new Model(Model::Primitives::SQUARE, Vector3(0, -0.5, 0.0001f), Vector3(0, 0, 0), Vector3(1, 1, 1));
		spike->texture = spikeTexture;
		spike->AddScript<SortingSpikeTest>();
		RendererCore::AddModel(*spike, firstD->Target());

		int xPos = -1024;
		Color c = Color(1, 0, 0, 1);
		for(int i = 0; i < 10; i++)
		{
			Model* background = new Model(Model::Primitives::SQUARE, Vector3(xPos, 0, -800), Vector3(0, 0, 0), Vector3(1024, 1024, 1));
			background->color = c;
			background->texture = backgroundTexture;
			RendererCore::AddModel(*background, firstD->Target());
			xPos += 1024;
		}
	}
};