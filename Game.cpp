#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int N = 62, M = 62;
int size = 16;
int w = size*N;
int h = size*M;

int dir, num = 1;

struct Snake {
	int x, y;
} s[100];

struct Fruct {
	int x, y;
} f;

void Tick(bool GO) {
	if (GO == false) {
		// Sets the tail of the snake to follow the head. IE the second bit moves to where the first bit was and so on
		for (int i = num; i > 0; --i) {
			s[i].x = s[i - 1].x;
			s[i].y = s[i - 1].y;
		}
		// Sets where the head of the snake will move based on the current value of direction
		if (dir == 0) {
			s[0].y += 1;
		}
		if (dir == 1) {
			s[0].x -= 1;
		}
		if (dir == 2) {
			s[0].x += 1;
		}
		if (dir == 3) {
			s[0].y -= 1;
		}
		// If the snake hits the fruit, the snake length is increased by one and the position of the fruit is randomized
		if ((s[0].x == f.x) && (s[0].y == f.y)) {
			num++;
			f.x = rand() % N;
			f.y = rand() % M;
			for (int i = 1; i < num; i++) {
				if (f.x == s[i].x && f.y == s[i].y) {
					f.x = rand() % N;
					f.y = rand() % M;
				}
			}
		}

		// Sets the wrap conditions so that if it goes through an edge it comes out the other side
		
	}
	
}


int main() {

	srand(time(0));

	RenderWindow window(VideoMode(w, h), "Snake Game!");

	// creates the sprites for the snake, fruit, background, and game over screen
	Texture t1, t2, t3, t4;
	t1.loadFromFile("images/white.png");
	t2.loadFromFile("images/red.png");
	t3.loadFromFile("images/green.png");
	t4.loadFromFile("images/GameOver.png");
	Sprite sprite1(t1);
	Sprite sprite2(t2);
	Sprite sprite3(t3);
	Sprite sprite4(t4);

	Clock clock;
	float timer = 0, delay = 0.1; 

	f.x = 10;
	f.y = 10;
	bool GO = false;
	while (window.isOpen()) {
		
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		Event e;
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) {
				window.close();
			}
		}

		// Sets the Keyboard Arros to Control the Snake's direction of Travel
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			if (dir != 2) {
				dir = 1;
			}
			else {
				dir = 2;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			if (dir != 1) {
				dir = 2;
			}
			else {
				dir = 1;
			}

		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			if (dir != 0) {
				dir = 3;
			}
			else {
				dir = 0;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			if (dir != 3) {
				dir = 0;
			}
			else {
				dir = 3;
			}
		}

		if (timer > delay) {
			timer = 0;
			Tick(GO);
		}

		window.clear();

		// Controls the drawing of the background
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				sprite1.setPosition(i*size, j*size);
				window.draw(sprite1);
			}
		}

		// Controls the drawing of the snake
		for (int i = 0; i < num; i++) {
			sprite2.setPosition(s[i].x*size, s[i].y*size);
			window.draw(sprite2);
		}

		// Sprite controls for the fruit including generation and position
		sprite3.setPosition(f.x*size, f.y*size);
		window.draw(sprite3);
		
		// If the snake goes out of the bounds of the arena, the Game Over flag is turned on
		if (s[0].x >= N) {
			GO = true;
		}
		if (s[0].x < 0) {
			GO = true;
		}
		if (s[0].y >= M) {
			GO = true;;
		}
		if (s[0].y < 0) {
			GO = true;;
		}

		// This detects if the snake hits itself and turns on the Game Over flag if it does
		for (int i = 1; i < num; i++) {
			if (s[0].x == s[i].x && s[0].y == s[i].y) {
				GO = true;
			}
		}

		// If the Game Over flag is on, this draws a game over message
		if (GO == true) {
			window.draw(sprite4);
			// This rebegins the game if space is pressed. It resest the Game Over flag, sets the snake length back to 1, and randomizes it's position
			if (Keyboard::isKeyPressed(Keyboard::Space)) {
				GO = false;
				num = 1;
				s[0].x = 15;// 5 + rand() % (N-10);
				s[0].y = 10;//5+ rand() % (M-10);
				dir = 1;
				// This makes sure that the random start is not an unfair by making sure the start is far enough away from the wall. 
				/*
				if (s[0].x < 8) {
					s[0].x += 5;
				}
				if (s[0].y < 8) {
					s[0].y += 7;
				}
				if (s[0].x > 22) {
					s[0].x -= 5;
				}
				if (s[0].y > 12) {
					s[0].y -= 7;
				}
				*/
			}
		}
		// Don't put anything below this or it won't work properly
		window.display();
		
	}

	return 0;
}
