#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Sounds.h"
#include "Map.h"
#include "Player.h"
#include <sstream>
#include <string>
#include "SoundsGame.h"
#include "SpriteManager.h"


using namespace sf;
using namespace std;


void isPaused(float& time, bool pause) {
	if (pause == true) {
		time = 0;
	}
}


void fillMap(String array[HEIGHT_MAP_I]) {
	for (int i = 0; i < HEIGHT_MAP_I; i++) {
		thisArray[i] = array[i];
	}
}
void changeLevel(Player& p) {

	if (numberLevel == 1) {
		readMap("Maps\\LVL1.txt");
		p.sizeEnemy = 1;
		p.sizeMovement = SIZE_MOVEMENT_I;
	}
	if (numberLevel == 2) {
		readMap("Maps\\LVL2.txt");
		p.sizeEnemy = 6;
		p.sizeMovement = SIZE_MOVEMENT_II;
	}
	if (numberLevel == 3) {
		width_map = WIDTH_MAP_II;
		readMap("Maps\\LVL3.txt");
		p.sizeEnemy = 13;
		p.sizeMovement = SIZE_MOVEMENT_III;
	}
	if (numberLevel == 4) {
		width_map = WIDTH_MAP_II;
		readMap("Maps\\LVL4.txt");
		p.sizeEnemy = 10;
		p.sizeMovement = SIZE_MOVEMENT_III;
	}
}

void resetGame(Player& p, int x, int y) {
	p.setIsWin(false);
	p.isPlay = true;
	p.isMove = true;
	p.savePlayerSprite();
	changeLevel(p);
	p.setPlayerCoordinateX(x);
	p.setPlayerCoordinateY(y);
}



int startGame() {

	bool isLevel = true;
	bool isStartMenu = true;
	int sizeEnemy = 0;

	RenderWindow window(sf::VideoMode(1920, 1080), "NINJA", Style::Fullscreen);

	menu(window, isLevel);
	selectLevel(window, isStartMenu);
	window.clear();

	view.reset(sf::FloatRect(0, 0, 1920, 1080));

	Image map_image;//объект изображения для карты
	Image map_image_background;//объект изображения для карты
	Image map_image_lava;

	map_image_background.loadFromFile("Images/FON7.jpg");//загружаем фон для карты
	Texture map_image_b;
	map_image_b.loadFromImage(map_image_background);//заливаем текстуру спрайтом
	Sprite s_map_image;//создаём спрайт для карты
	s_map_image.setTexture(map_image_b);//заливаем текстуру спрайтом
	Sprite s_map_image2;//создаём спрайт для карты
	s_map_image2.setTexture(map_image_b);//заливаем текстуру спрайтом
	s_map_image2.setPosition(1919, 0);

	map_image.loadFromFile("Images/TILE6.png");//загружаем файл для карты
	Texture map;//текстура карты
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом

	Player p(100, 700, 57.0, 52.0);

	Clock clock;

	Font font;//шрифт 
	font.loadFromFile("CHILLER.ttf");
	Text pauseText("", font, 110);

	pauseText.setString("PAUSE");
	Text done("", font, 110);

	done.setString("YOU ARE WIN!");

	Text lose("", font, 110);
	lose.setString("YOU ARE LOSE!");
	Text pressWin("", font, 80);

	Text moveSize("", font, 40);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	moveSize.setStyle(sf::Text::Bold | sf::Text::Underlined);

	SpriteManager spriteHelp;
	spriteHelp.setSp("Images/questMenu.png");
	
	pressWin.setString("Press F to continue");
	Text pressLose("", font, 80);
	pressLose.setString("Press N to restart");

	pauseText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	done.setStyle(sf::Text::Bold | sf::Text::Underlined);
	lose.setStyle(sf::Text::Bold | sf::Text::Underlined);

	pressWin.setStyle(sf::Text::Bold);
	pressLose.setStyle(sf::Text::Bold);

	bool pause = false;

	changeLevel(p);

	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
		clock.restart(); //перезагружает время
		time = time / 300; //скорость игры

		pauseText.setString("PAUSE");//сохраняем текст паузы

		done.setString("YOU ARE WIN!");
		lose.setString("YOU ARE LOSE!");

		pressWin.setString("Press F to continue");

		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		isPaused(time, pause);

		float coordinatePlayerX, coordinatePlayerY = 0;
		coordinatePlayerX = p.getPlayerCoordinateX();
		coordinatePlayerY = p.getPlayerCoordinateY();

		pauseText.setPosition(view.getCenter().x - 150, view.getCenter().y -390);//сохраняем позицию текста

		done.setPosition(view.getCenter().x - 280, view.getCenter().y - 200);
		pressWin.setPosition(view.getCenter().x - 240, view.getCenter().y - 80);

		lose.setPosition(view.getCenter().x - 250, view.getCenter().y - 200);
		pressLose.setPosition(view.getCenter().x - 180, view.getCenter().y - 80);

		spriteHelp.sprite.setPosition(view.getCenter().x - 287, view.getCenter().y - 250);

		if (Keyboard::isKeyPressed(Keyboard::Tab)) {//проверка на нажатие клавиши Tab

			if (pause == true) {

				pause = false;
				
			}
			else {

				pause = true;

			}//выход/вход в состояние паузы
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			break;
		}

		if (p.onGround == false) {
			s[0].playSound();
		}

		setViewPosition(coordinatePlayerX, coordinatePlayerY);
		p.update(time);
		viewMap(time);//функция скроллинга карты, передаем ей время sfml
		window.setView(view);//"оживляем" камеру в окне sfml
		window.clear();
		window.draw(s_map_image);
		window.draw(s_map_image2);

		for (int i = 0; i < height_map; i++)
			for (int j = 0; j < width_map; j++)
			{
				if (thisArray[i][j] == ' ') continue;
				if (thisArray[i][j] == 'h') {
					if (p.sizeEnemy != 0) {
						s_map.setTextureRect(IntRect(68, 1, 60, 60));
					}
					else {
						thisArray[i][j] = ' ';
					}
				}
				if (thisArray[i][j] == 's')  s_map.setTextureRect(IntRect(138, 1, 60, 60));//если встретили символ s, то рисуем 2й квадратик
				if ((thisArray[i][j] == '0')) s_map.setTextureRect(IntRect(68, 1, 60, 60));//если встретили символ 0, то рисуем 4й квадратик
				if ((thisArray[i][j] == 'e')) {
					s_map.setTextureRect(IntRect(211, 1, 57, 60));

				}
				if ((thisArray[i][j] == 'p')) {
					s_map.setTextureRect(IntRect(347, 1, 56, 60)); //если встретили символ 0, то рисуем 4й квадратик


				}
				if ((thisArray[i][j] == 'l')) {
					s_map.setTextureRect(IntRect(0, 1, 60, 60));
				}
				if ((thisArray[i][j] == 'g')) {
					s_map.setTextureRect(IntRect(412, 0, 59, 59));
				}

				s_map.setPosition(j * 60, i * 60);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

				window.draw(s_map);//рисуем квадратики на экран

			}

		if (Keyboard::isKeyPressed(Keyboard::N)) {

			p.setIsLife(true);
			s[5].playSound();
			resetGame(p, 100, 700);
		}

		if (pause) { 
			window.draw(spriteHelp.sprite);
			window.draw(pauseText); }//вывод текста паузы

		if (p.getIsWin() == true) {
			window.draw(done);
			window.draw(pressWin);
			if (Keyboard::isKeyPressed(Keyboard::F) && numberLevel < 10) {
				s[5].playSound();
				numberLevel++;
				resetGame(p, 100, 700);
			}
		}
		else if(!p.isLife){
			p.setSpriteFire();
			window.draw(lose);
			window.draw(pressLose);
		}
		ostringstream playerMoveString;
		playerMoveString << p.sizeMovement;
		moveSize.setString("Moving:\t" + playerMoveString.str());
		moveSize.setPosition(view.getCenter().x + 700, view.getCenter().y - 480);
		window.draw(moveSize);
		window.draw(p.playerSM.sprite);
		window.display();
	}

	return 0;
}
