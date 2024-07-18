#include "common.h"
#include "Game.h"

Game::Game(const std::string& windowName, int posX, int posY, int windowWidth, int windowHeight, int flags) {
	SDL_Init(SDL_INIT_EVERYTHING);
	this->window = SDL_CreateWindow(windowName.c_str(), posX, posY, windowWidth, windowHeight, flags);
	SRenderer::Init(window);
	
	this->windowRect = { 0, 0, windowWidth, windowHeight };
}

Game::~Game() {
	for (auto& object : objects) {
		delete object;
	}
	delete background;
}

void Game::Loop() {
	durationUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(secondUpdate - firstUpdate);
	if (durationUpdate.count() >= updateDelta) {
		firstUpdate = std::chrono::high_resolution_clock::now();

		Update(/*durationPosun.count()**/1/*0*/);
	}
	secondUpdate = std::chrono::high_resolution_clock::now();

	durationFrame = std::chrono::duration_cast<std::chrono::milliseconds>(secondFrame - firstFrame);
	if (durationFrame.count() >= deltaTime) {
		firstFrame = std::chrono::high_resolution_clock::now();
		Render();
		//std::cout << "<====New Frame====>\n";
	}
	secondFrame = std::chrono::high_resolution_clock::now();
}

void Game::SetBackground(const std::string& BGpath) {
	background = new Background(windowRect.w, windowRect.h, BGpath);
}

bool Game::IsGameOver() {
	return isGameOver;
}

void Game::Render() {
	SDL_RenderClear(SRenderer::Get().Renderer());

	background->Render(&windowRect);
	for (auto& wall : walls) {
		wall->Render();
	}
	for (auto& ball : balls) {
		ball->Render();
	}
	for (auto& player : players) {
		player->Render();
	}

	SDL_RenderPresent(SRenderer::Get().Renderer());
}

void Game::Update(float delta) {
	/*for (auto& wall : walls) {
		wall->
	}*/
	for (auto& ball : balls) {
		for (auto wall : walls) {
			ball->Collision(wall, delta);
		}
	}
	for (auto& ball : balls) {
		for (auto player : players) {
			ball->Collision(player, delta);
		}
	}
	for (auto& ball : balls) {
		ball->HandleEvents();
		ball->Update(delta);
	}
	for (auto& player : players) {
		for (auto& wall : walls) {
			player->Collision(wall, delta);
		}
	}

	for (auto& player : players) {
		player->HandleEvents();
		player->Update(delta);	// !!! i se pricita vektor k pozici!!! -> zde jen kontrola kolize
	}
	int uncatchedBalls = 0;
	for (auto ball : balls) {
		if (ball->GetPosition().y > 540) {
			uncatchedBalls++;
		}
	}
	for (auto& player : players) {
		player->DecreaseLives(uncatchedBalls);
	}
	for (auto& player : players) {
		if (player->IsGameOver()) {
			isGameOver = true;
		}
	}

}
