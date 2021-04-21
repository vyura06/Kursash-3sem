#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.h"
#include "SpriteManager.h"
#include "SoundsGame.h"
#include "Sounds.h"

using namespace sf;

//������ ������ ������
SpriteManager buttons[21];

	//������ ������� �������� �� ���������� ��������
void setSprite() {
	//������� ������
	buttons[0].setSp("Images/1.png");
	buttons[1].setSp("Images/2.png");
	buttons[2].setSp("Images/3.png");

	//������� ���������
	buttons[3].setSp("Images/4.png");
	buttons[4].setSp("Images/5.png");
	
	//������ ������������ ���������� ������
	for (int i = 4; i < 20; i++) {
		buttons[i].setSp("Images/greyclose.png");
	} buttons[20].setSp("Images/exit.png");
}

//������ ������� �������� ������������ ��������������� �������� � ������� ��������
void setSpriteRectAndPosition() {

	buttons[20].sprite.setTextureRect(IntRect(0, 0, 133, 53));
	buttons[20].sprite.setPosition(570, 692);

	//������ ������
	for (int i = 1; i < 20; i++) {
		buttons[i].sprite.setTextureRect(IntRect(0, 0, 60, 60));
	}

	int xSprite = 370;

	//��������� ������
	const int arrayPositionButtons[4] = { 370, 450, 530, 610 };

	for (int i = 0, indexP = 0; i < 20; i++, indexP++) {

		if (i % 4 == 0 && i != 0) {

			indexP = 0;

			xSprite += 120;
		}
		buttons[i].sprite.setPosition(xSprite, arrayPositionButtons[indexP]);
	}
}

//������ ������� �������� �� �������� ������� �������� � ���� �� ������
void hittRectangle(RenderWindow& window, int& selectNum) {

	//������ exit
	if (IntRect(570, 692, 133, 53).contains(Mouse::getPosition(window))) { selectNum = 1; }

	//������ �������
	if (IntRect(370, 370, 60, 60).contains(Mouse::getPosition(window))) { selectNum = 2; }
	if (IntRect(370, 450, 60, 60).contains(Mouse::getPosition(window))) { selectNum = 3; }
	if (IntRect(370, 530, 60, 60).contains(Mouse::getPosition(window))) { selectNum = 4; }
	if (IntRect(370, 610, 60, 60).contains(Mouse::getPosition(window))) { selectNum = 5; }
}

//������ ������� �������� �� ��������� ��������
void drawSprites(RenderWindow& window) {

	for (int i = 0; i < 21; i++) {
		window.draw(buttons[i].sprite);
	}
}


//������� �������������� �������� � ���� ������ � ������ ������
void selectLevel(RenderWindow& window, bool& isMenu) {

	setSprite();//���������� ���� � ������
	setSpriteRectAndPosition();//���������� ������� �������� ������

	int selectNum = 0;//������ ���������� �������� �� ������� �������

	SpriteManager levelBackground;//������ SpriteManager, �������� ��� ����
	levelBackground.setSp("Images/FON4.jpg");//�������� ������� �� �����

	//���� ���������� � �������
	while (isMenu)
	{
		//��������
		//�������� "���������" � �������������
		hittRectangle(window, selectNum);

		//���� ������ ����� ������ ����
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			//���� selectNum 1 - ������� ����
			if (selectNum == 1) { window.close(); }

				//���� selectNum 2 - ��������� 1 �������
				if (selectNum == 2) {

					s[8].playSound();//����������� ���� ������� �� �������
					isMenu = false;
					numberLevel = 1;//���������� ����� ������


					//������������ ������� ������ � ������ �������� ������
					width_map = WIDTH_MAP_I;
				}

				if (selectNum == 3) {

					s[8].playSound();//����������� ���� ������� �� �������
					isMenu = false;//������� �� ����
					numberLevel = 2;//���������� ����� ������

					//������������ ������� ������ � ������ �������� ������
					width_map = WIDTH_MAP_I;
				}

				if (selectNum == 4) {

					s[8].playSound();//����������� ���� ������� �� �������
					isMenu = false;//������� �� ����
					numberLevel = 3;//���������� ����� ������

					//������������ ������� ������ � ������ �������� ������
					width_map = WIDTH_MAP_I;
				}

				if (selectNum == 5) {

					s[8].playSound();//����������� ���� ������� �� �������
					isMenu = false;//������� �� ����
					numberLevel = 4;//���������� ����� ������

					//������������ ������� ������ � ������ �������� ������
					width_map = WIDTH_MAP_II;
				}
		}
		window.draw(levelBackground.sprite);//��������� ������� ����
		drawSprites(window);//��������� �������� ������
		window.display();//����� ����
	}
}

//������� �������������� �������� � �������� ���� 
void menu(RenderWindow& window, bool& isSelectLevel) {

	//�������� ������� SpriteManager
	SpriteManager buttonMenu[2];

	//�������� ����������� � �������
	buttonMenu[0].setSp("Images/begin.png");
	buttonMenu[1].setSp("Images/close.png");

	bool isMenu = true;//���������� ���������� �� ��������� ����

	int menuNum = 0;//������ ���������� �������� �� �������� � ����

	//���������� ��������������� �������
	buttonMenu[0].sprite.setTextureRect(IntRect(0, 0, 56, 56));
	buttonMenu[1].sprite.setTextureRect(IntRect(0, 0, 56, 56));
	//���������� ������� �������
	buttonMenu[0].sprite.setPosition(1690, 900);
	buttonMenu[1].sprite.setPosition(30, 30);

	//�������� ������� SpriteManager ��� ������� ����
	SpriteManager menuBackground;

	//�������� �����������
	menuBackground.setSp("Images/FON3.jpg");

	//���� ���������� � ����
	while (isMenu)
	{
		//�������� �� ��������� �������� �� ������������� ������
		if (IntRect(1690, 900, 56, 56).contains(Mouse::getPosition(window))) { menuNum = 1; }
		if (IntRect(30, 30, 56, 56).contains(Mouse::getPosition(window))) { menuNum = 2; }

		//���� ������ ����� ������ ����
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			//�������� �� �������������� � ������ �� ������
			if (menuNum == 1) { s[8].playSound(); isMenu = false; }
			if (menuNum == 2) { s[8].playSound(); window.close(); }
		}

		//��������� ��������
		window.draw(menuBackground.sprite);

		//��������� ������
		window.draw(buttonMenu[0].sprite);
		window.draw(buttonMenu[1].sprite);

		//����� �����������
		window.display();
	}
}

