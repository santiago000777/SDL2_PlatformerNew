#include "common.h"
#include "IGame.h"

// TODO: Pridat Text
//		 Pridat kruhovou kolizi na Bomb
//       Pridat Menu



int main(int argc, char* args[]) {
	Game::Get().Init("PONG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 604, 850, SDL_WINDOW_SHOWN);
	
	Game::Get().SetBackground("Pictures/veitImg.bmp");
	Game::Get().AddWall({ 25, 80, 30, 90 * 8 }, "Pictures/verticalWall.bmp", 7);

	//Game::Get().Add<Wall>({ 25, 80, 30, 90 * 8 }, "Pictures/verticalWall.bmp", 7);	// ?
	Game::Get().AddWall({ 25 + 525, 80, 30, 90 * 8 }, "Pictures/verticalWall.bmp", 7);


	Game::Get().AddWall({ 25, 50, 550, 30 }, "Pictures/horizontalWall.bmp", 9);

	Game::Get().AddWall({ 25, 780, 550, 30 }, "Pictures/horizontalWall.bmp", 9);

	Game::Get().AddPlayer({ 255, 750, 100, 24 }, "Pictures/paddle.bmp", 25);

	const float ballScale = 3.5f;
	Game::Get().AddBall({ 300, 200, (int)roundf(7 * ballScale), (int)roundf(7 * ballScale) }, "Pictures/BallSpriteSheet.bmp", 7);

	for (int i = 0; i < 6; i++) {
		Game::Get().AddBrick({ 120 + 64 * i, 100, 64, 20 }, "Pictures/BrickSpriteSheet.bmp", 16);
	}
	for (int i = 0; i < 5; i++) {
		if (i == 2) {
			Game::Get().AddBomb({ 174 + 64 * i, 122, 20, 20 }, "Pictures/BombSpriteSheet.bmp", 7);
			continue;
		}
		Game::Get().AddBrick({ 152 + 64 * i, 120, 64, 20 }, "Pictures/BrickSpriteSheet.bmp", 16);
	}

	for (int i = 0; i < 4; i++) {
		if (i == 1 || i == 2) continue;
		Game::Get().AddBrick({ 184 + 64 * i, 140, 64, 20 }, "Pictures/BrickSpriteSheet.bmp", 16);
	}

	Game::Get().AddBubble({ 100, 200, 28, 28 }, "Pictures/BubbleSpriteSheet.bmp", 10);

	Game::Get().Start();
	while (!PressedKey(VK_ESCAPE) && !Game::Get().IsEnd()) {
		Game::Get().Loop();
	}
	if (Game::Get().CountOfBricks() > 0)
		std::cout << "Game over!\n\n";
	else
		std::cout << "You won!\n\n";

	return 0;
}


// Git commands
/*
	--CREATE GITHUB REPO--
	* git init									-> vytvoreni .git
	* git branch -M <branch>					-> tvorba nove branch
	* git remote add origin <pathFromGitHub>	-> vytvoreni remote s cestou, ktera se generuje na GitHubu -> musi se rucne repo vytvorit
	* git remote -v								-> kontrola remotu
		...

	--CLONE GITHUB REPO--
	* git clone <pathFromGitHub>				-> kopirovani repo z github

	--PULL--
	* git log									-> zobrazeni vsech commitu
	* git pull origin <branch>					-> nahrani do visual studia

	--COMMIT & PUSH--
	* git status								-> rozdily mezi kodem a poslednim commitem

	* git add <path>							-> pridani daneho souboru, ktery se zmenil, ke commitu
	* git add -A								-> pridani vsech souboru, ktery se zmenil, ke commitu

	* git commit -m "<msg>"						-> commit se zpravou
	* git push origin <branch>					-> nahrani do githubu

	--CHECKOUT--
	* git checkout <branch>						-> prechazeni na novou branch
	* git checkout <commit>						-> vraceni na dany commit
*/