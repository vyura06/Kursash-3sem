#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include "Map.h"
#include "Sounds.h"
#include "SoundsGame.h"
#include "SpriteManager.h"


using namespace sf;

//класс Игрока
class Player {
public:

	//время исчезновения блока g
	Clock clockBlock;
	float time = 0;

	//количество врагов и движений
	int sizeEnemy = 0, sizeMovement = 0;

	//спрайт нашего игрока
	SpriteManager playerSM;

	//переменные состояния
	bool isLife, onGround, isMove, isPlay, isRestartTimer;

	//конструктор с параметрами(формальными) для класса Player. 
	Player(float x, float y, float w, float h) {

		//обнуляем часть начальных параметров
		speed = 0; dx = 0; dy = 0;
		isMove = true;
		isRestartTimer = false;
		isLife = true; onGround = false;

		//сохранение полученных данных
		this->w = w; this->h = h;
		this->x = x; this->y = y;

		//сохраняем спрайт игрока
		savePlayerSprite();
	}

	//функция сохраняющая спрайт игрока
	void savePlayerSprite() {

		playerSM.setSp("Images/TILE6.png");//загружаем спрайт-лист с блоками и персонажами
		playerSM.sprite.setTextureRect(IntRect(278, 1, w, h));//задаем спрайту прямоугольник
		playerSM.sprite.setOrigin(w / 2, h / 2);//сохранение начальных координат
	}

	//функция сохраняющая спрайт сгоревшего игрока
	void setSpriteFire() {

		playerSM.setSp("Images/fireman.png");//загружаем спрайт сгоревшего игрока
		playerSM.sprite.setTextureRect(IntRect(0, 0, 57, 53));//задаем спрайту прямоугольник
		playerSM.sprite.setOrigin(w / 2, h / 2);//сохранение начальных координат
	}

	//функция отвечающая за дейсвия персонажа, в зависимости от нажатой клавиши
	void control() {

		//проверка на нажатие какой-либо клавиши
		if (Keyboard::isKeyPressed) {

			//нажата клавиша А и стрелка влево
			if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) {

				state = left;//смена состояния
				speed = 0.15;//смена скорости
				playerSM.sprite.setTextureRect(IntRect(278, 1, w, h));
			}

			//нажата клавиша D и стрелка вправо
			if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) {

				state = right;//смена состояния
				speed = 0.15;//смена скорости
				playerSM.sprite.setTextureRect(IntRect(335, 1, -w, h));
			}

			//нажата клавиша W, стрелка вверх и пробел
			if ((Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Space)) && (onGround)) {

				state = jump;//смена состояния
				dy = -0.87;//отталкиваем игрока от земли
				onGround = false;//переводим игрока в состояние не на земле
				sizeMovement--;
			}

			//нажата клавиша S и стрелка вниз
			if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)) {

				state = down;//смена состояния
				speed = 0.15;//смена скорости
			}
		}

	}

	//функция отвечающая обновление основных параметров игрока
	void update(float time) {

		if (isLife && isMove && sizeMovement > 0) {//проверка на "жизнь игрока"

			control();//вызов функции взаимодействия с клавишами
			changeAcceleration();//смена ускорения от состояния 
			x += dx * time;//увелчиваем коордитау х в зависимости от времени
			checkCollisionWithMap(dx, 0);//обрабока столкновения по Х
			y += dy * time;//увелчиваем коордитау y в зависимости от времени
			checkCollisionWithMap(0, dy);//обрабока столкновения по Y
			playerSM.sprite.setPosition(x + w / 2, y + h / 2); //задаём новую позицию sprite
			speed = 0;
			dy = dy + 0.0015 * time;//притяжение персонажа к земле
		}
	}

	//данная функция отвечает за отталкивание игрока от поверхности
	void playerPuching(float Dx, float Dy,int i,int j) {

		if (Dy > 0) { y = i * 60 - h;  dy = 0; onGround = true; }//персонаж упал на землю
		if (Dy < 0) { y = i * 60 + 60;  dy = 0; }//столкновение с верхними краями карты
		if (Dx > 0) { x = j * 60 - w; }//столкновение с правым краем карты
		if (Dx < 0) { x = j * 60 + 60; }//столкновение с левым краем карты
	}

	//функция отвечает за взаимодействие персонажа с картой
	void checkCollisionWithMap(float Dx, float Dy)
	{
		//проходимся по элементам карты
		for (int i = y / 60; i < (y + h) / 60; i++) {
			for (int j = x / 60; j < (x + w) / 60; j++)
			{
				//если элемент - земля
				if (thisArray[i][j] == '0')
				{
					playerPuching(Dx, Dy, i, j);
				}
				//если элемент - разрушаемый объект (в конце игры)
				if (thisArray[i][j] == 'h')
				{
					//проверка на наличие врагов
					if (sizeEnemy != 0) {

						playerPuching(Dx, Dy, i, j);
					}
				}

				//если элемент - лава
				if (thisArray[i][j] == 'l') {

					isLife = false;//игрок погибает
					s[2].playSound();//проигрываем звук проигрыша
				}

				//если элемент - противник
				if (thisArray[i][j] == 'e') {

					thisArray[i][j] = ' ';//убираем противника
					s[3].playSound();//проигрываем звук удара по противнику
					s[4].playSound();//проигрываем звук гибели противника
					sizeEnemy--;//уменьшаем количество противников на 1
				}

				//если элемнт - принцесса
				if (thisArray[i][j] == 'p') {

					isWin = true;
					isMove = false;
					if (isPlay) {
						s[1].playSound();//проигрываем звук победы
						isPlay = false;
					}
				}
				
				//если элемент - бонус
				if (thisArray[i][j] == 'g') {
					s[9].playSound();//проиграем звук бонуса
					sizeMovement += 3;//при поднятии бонуса добавляем 3 движения
					thisArray[i][j] = ' ';
				}

				//если элемент - разрушаемый блок
				if (thisArray[i][j] == 's') {

					//таймер разрушения блока
					if (isRestartTimer) {
						time = clockBlock.getElapsedTime().asSeconds();
						if (time > 3) {
							thisArray[i][j] = ' ';
							clockBlock.restart();
						}
					}
					else {
						isRestartTimer = true;
						clockBlock.restart();
					}
					playerPuching(Dx, Dy, i, j);
				}
			}
		}
	}

	//данная функция возвращает координату Х	
	float getPlayerCoordinateX() {
		return x;
	}

	//данная функция возвращает координату Y 	
	float getPlayerCoordinateY() {
		return y;
	}

	//данная функция сохраняет координату Х
	void setPlayerCoordinateX(int x) {
		this->x = x;
	}

	//данная функция сохраняет координату Y 	
	void setPlayerCoordinateY(int y) {
		this->y = y;
	}

	//данная функция возвращает количество противников
	int getSizeEnemy() {
		return sizeEnemy;
	}

	//данная функция возвращает состояние победы
	bool getIsWin() {
		return isWin;
	}

	//данная функция сохраняет состояние победы
	void setIsWin(bool isWin) {
		this->isWin = isWin;
	}

	//данная функция сохраняет состояние жизни
	void setIsLife(bool isLife) {
		this->isLife = isLife;
	}

private:

	//состояние победы изначально - ложь
	bool isWin = false;

	//координаты игрока х и у, высота, ширина, ускорение (по х и по у), скорость
	float x, y, w, h, dx, dy, speed;

	//состояния движения  игрока
	enum state { left, right, down, jump } state;

	//функция изменяющая ускорение игрока в зависимости от состояния
	void changeAcceleration() {
		switch (state)
		{

		//состояние идти вправо
		case right: {
			dx = speed;
			break;
		}

		//состояние идти влево		
		case left: {
			dx = -speed;
			break;
		}
		}
	}

	//функция сохранения позиции игрока
	void checkСollision(int Dx, int Dy, int j, int i) {

		if (Dy > 0) { y = i * 60 - h;  dy = 0; onGround = true; }//персонаж упал на землю
		if (Dy < 0) { y = i * 60 + 60;  dy = 0; }//столкновение с верхними краями карты
		if (Dx > 0) { x = j * 60 - w; }//столкновение с правым краем карты
		if (Dx < 0) { x = j * 60 + 60; }//столкновение с левым краем карты
	}
};