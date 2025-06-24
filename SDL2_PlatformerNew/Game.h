#pragma once
#include "IGame.h"
#include "Player.h"
#include "Ball.h"
#include "Background.h"
#include "Wall.h"
#include "IRenderer.h"
#include "Brick.h"
#include "Bubble.h"
#include "Bomb.h"
#include "Text.h"
#include "Timer.h"
#include "File.h"

#define FPS		60

class SGame : public IGame {
public:
	SGame() {}
	SGame(const SGame& rhs) = delete;
	SGame(SGame&& rhs) = delete;
	~SGame();

	void operator=(const SGame& rhs) = delete;
	void operator=(SGame&& rhs) = delete;

	void Init(const std::string& windowName = "Window", int posX = SDL_WINDOWPOS_CENTERED,
					 int posY = SDL_WINDOWPOS_CENTERED, int windowWidth = 800, int windowHeight = 600, int flags = SDL_WINDOW_SHOWN) override;
	void Loop() override;
	void Start() override;

	//int CountOfBricks() const;
	bool IsEnd() override;

	
	void SetBackground(const std::string& BGpath);
private:
	std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> window { nullptr, SDL_DestroyWindow };
	std::unique_ptr<Background> background;

	std::vector<std::unique_ptr<Wall>> walls;
	std::vector<std::unique_ptr<Ball>> balls;
	std::vector<std::unique_ptr<Player>> players;
	std::vector<std::unique_ptr<Brick>> bricks;
	std::vector<std::unique_ptr<Bubble>> bubbles;
	std::vector<std::unique_ptr<Bomb>> bombs;
	
	Vec4f respawnBubbleBox;
	std::random_device randomNum;
	

	const float deltaTime = 1000.0f / FPS;
	Timer frameTimer, updateTimer, fileTimer, bubbleRespawnTimer;
	File file {"data.bin"};
	

	SDL_Rect gameOverRect = { 0, 800, 600, 20 };
	bool isEnd = false;

	std::unique_ptr<TTF_Font, void(*)(TTF_Font*)> font { nullptr, TTF_CloseFont };
	SDL_Color textColor = { 255, 255, 255, 255 };

	Text scoreText, scoreNumber;
	Text livesText, livesNumber;

	template <typename Ty> void Add(SDL_Rect dstBox, const std::string& path, int characterWidth);
	template<> void Add<Wall>(SDL_Rect dstBox, const std::string& path, int characterWidth) {
		Vec4f box = { (float)dstBox.x, (float)dstBox.y, (float)dstBox.w, (float)dstBox.h };

		walls.emplace_back(std::make_unique<Wall>(box, path, characterWidth));
	}
	template<> void Add<Player>(SDL_Rect dstBox, const std::string& path, int characterWidth) {
		Vec4f box = { (float)dstBox.x, (float)dstBox.y, (float)dstBox.w, (float)dstBox.h };

		players.emplace_back(std::make_unique<Player>(box, path, characterWidth));
	}
	template<> void Add<Ball>(SDL_Rect dstBox, const std::string& path, int characterWidth) {
		Vec4f box = { (float)dstBox.x, (float)dstBox.y, (float)dstBox.w, (float)dstBox.h };

		balls.emplace_back(std::make_unique<Ball>(box, path, characterWidth));
	}
	template<> void Add<Brick>(SDL_Rect dstBox, const std::string& path, int characterWidth) {
		Vec4f box = { (float)dstBox.x, (float)dstBox.y, (float)dstBox.w, (float)dstBox.h };

		bricks.emplace_back(std::make_unique<Brick>(box, path, characterWidth));
	}
	template<> void Add<Bubble>(SDL_Rect dstBox, const std::string& path, int characterWidth) {
		Vec4f box = { (float)dstBox.x, (float)dstBox.y, (float)dstBox.w, (float)dstBox.h };

		bubbles.emplace_back(std::make_unique<Bubble>(box, path, characterWidth));
	}
	template<> void Add<Bomb>(SDL_Rect dstBox, const std::string& path, int characterWidth) {
		Vec4f box = { (float)dstBox.x, (float)dstBox.y, (float)dstBox.w, (float)dstBox.h };

		bombs.emplace_back(std::make_unique<Bomb>(box, path, characterWidth));
	}

	void Basket();
	void Render();
	void Update();
	void HandleEvents();
	void Collision();
	void FileHandle();
	void Save();
	void Load();
};