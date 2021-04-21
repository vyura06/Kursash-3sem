#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.h"
#include "SpriteManager.h"
#include "SoundsGame.h"
#include "Sounds.h"

using namespace sf;

//массив кнопок подмен
SpriteManager buttons[21];

	//данная функция отвечает за сохранение спрайтов
void setSprite() {
	//Рабочие уровни
	buttons[0].setSp("Images/1.png");
	buttons[1].setSp("Images/2.png");
	buttons[2].setSp("Images/3.png");

	//Требуют доработки
	buttons[3].setSp("Images/4.png");
	buttons[4].setSp("Images/5.png");
	
	//Кнопки показывающие неоткрытые уровни
	for (int i = 4; i < 20; i++) {
		buttons[i].setSp("Images/greyclose.png");
	} buttons[20].setSp("Images/exit.png");
}

//данная функция отвечает засохранение прямоугольников текстуры и позиции спрайтов
void setSpriteRectAndPosition() {

	buttons[20].sprite.setTextureRect(IntRect(0, 0, 133, 53));
	buttons[20].sprite.setPosition(570, 692);

	//размер кнопок
	for (int i = 1; i < 20; i++) {
		buttons[i].sprite.setTextureRect(IntRect(0, 0, 60, 60));
	}

	int xSprite = 370;

	//положение кнопок
	const int arrayPositionButtons[4] = { 370, 450, 530, 610 };

	for (int i = 0, indexP = 0; i < 20; i++, indexP++) {

		if (i % 4 == 0 && i != 0) {

			indexP = 0;

			xSprite += 120;
		}
		buttons[i].sprite.setPosition(xSprite, arrayPositionButtons[indexP]);
	}
}

//данная функция отвечает за проверку нажатия курсором в одну из кнопок
void hittRectangle(RenderWindow& window, int& selectNum) {

	//кнопка exit
	if (IntRect(570, 692, 133, 53).contains(Mouse::getPosition(window))) { selectNum = 1; }

	//кнопки уровней
	if (IntRect(370, 370, 60, 60).contains(Mouse::getPosition(window))) { selectNum = 2; }
	if (IntRect(370, 450, 60, 60).contains(Mouse::getPosition(window))) { selectNum = 3; }
	if (IntRect(370, 530, 60, 60).contains(Mouse::getPosition(window))) { selectNum = 4; }
	if (IntRect(370, 610, 60, 60).contains(Mouse::getPosition(window))) { selectNum = 5; }
}

//данная функция отвечает за отрисовку спрайтов
void drawSprites(RenderWindow& window) {

	for (int i = 0; i < 21; i++) {
		window.draw(buttons[i].sprite);
	}
}


//функция обробатывающая действия в меню вывода и выбора уровня
void selectLevel(RenderWindow& window, bool& isMenu) {

	setSprite();//сохранение пути к файлам
	setSpriteRectAndPosition();//сохранение позиции спрайтов кнопок

	int selectNum = 0;//данная переменная отвечает за нажатую клавишу

	SpriteManager levelBackground;//объект SpriteManager, хранящий фон меню
	levelBackground.setSp("Images/FON4.jpg");//загрузка спрайта из файла

	//цикл нахождения в подменю
	while (isMenu)
	{
		//обнуляем
		//проверка "попадания" в прямоугольник
		hittRectangle(window, selectNum);

		//если нажата левая кнопка мыши
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			//если selectNum 1 - закрыть окно
			if (selectNum == 1) { window.close(); }

				//если selectNum 2 - загрузить 1 уровень
				if (selectNum == 2) {

					s[8].playSound();//проигрываем звук нажатия по клавише
					isMenu = false;
					numberLevel = 1;//записываем номер уровня


					//присваивание текущий ширине и высоте значений уровня
					width_map = WIDTH_MAP_I;
				}

				if (selectNum == 3) {

					s[8].playSound();//проигрываем звук нажатия по клавише
					isMenu = false;//выходим из меню
					numberLevel = 2;//записываем номер уровня

					//присваивание текущий ширине и высоте значений уровня
					width_map = WIDTH_MAP_I;
				}

				if (selectNum == 4) {

					s[8].playSound();//проигрываем звук нажатия по клавише
					isMenu = false;//выходим из меню
					numberLevel = 3;//записываем номер уровня

					//присваивание текущий ширине и высоте значений уровня
					width_map = WIDTH_MAP_I;
				}

				if (selectNum == 5) {

					s[8].playSound();//проигрываем звук нажатия по клавише
					isMenu = false;//выходим из меню
					numberLevel = 4;//записываем номер уровня

					//присваивание текущий ширине и высоте значений уровня
					width_map = WIDTH_MAP_II;
				}
		}
		window.draw(levelBackground.sprite);//отрисовка заднего фона
		drawSprites(window);//отрисовка основных кнопок
		window.display();//показ окна
	}
}

//функция обрабатывающая действия в основном меню 
void menu(RenderWindow& window, bool& isSelectLevel) {

	//создание массива SpriteManager
	SpriteManager buttonMenu[2];

	//загрузка изображений в спрайты
	buttonMenu[0].setSp("Images/begin.png");
	buttonMenu[1].setSp("Images/close.png");

	bool isMenu = true;//переменная отвечающая за состояние меню

	int menuNum = 0;//данная переменная отвечает за действие в меню

	//сохранение прямоугольников текстур
	buttonMenu[0].sprite.setTextureRect(IntRect(0, 0, 56, 56));
	buttonMenu[1].sprite.setTextureRect(IntRect(0, 0, 56, 56));
	//сохранение позиции текстур
	buttonMenu[0].sprite.setPosition(1690, 900);
	buttonMenu[1].sprite.setPosition(30, 30);

	//создание объекта SpriteManager для заднего фона
	SpriteManager menuBackground;

	//загрузка изображения
	menuBackground.setSp("Images/FON3.jpg");

	//цикл нахождения в меню
	while (isMenu)
	{
		//проверки на попадания курсором на прямоугольник кнопки
		if (IntRect(1690, 900, 56, 56).contains(Mouse::getPosition(window))) { menuNum = 1; }
		if (IntRect(30, 30, 56, 56).contains(Mouse::getPosition(window))) { menuNum = 2; }

		//если нажата левая кнопка мыши
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			//проверки на взаимодействие с каждой из кнопок
			if (menuNum == 1) { s[8].playSound(); isMenu = false; }
			if (menuNum == 2) { s[8].playSound(); window.close(); }
		}

		//отрисовка спрайтов
		window.draw(menuBackground.sprite);

		//отрисовка кнопок
		window.draw(buttonMenu[0].sprite);
		window.draw(buttonMenu[1].sprite);

		//вывод изображений
		window.display();
	}
}

