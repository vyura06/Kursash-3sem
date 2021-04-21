#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include "Map.h"
#include "Sounds.h"
#include "SoundsGame.h"
#include "SpriteManager.h"


using namespace sf;

//����� ������
class Player {
public:

	//����� ������������ ����� g
	Clock clockBlock;
	float time = 0;

	//���������� ������ � ��������
	int sizeEnemy = 0, sizeMovement = 0;

	//������ ������ ������
	SpriteManager playerSM;

	//���������� ���������
	bool isLife, onGround, isMove, isPlay, isRestartTimer;

	//����������� � �����������(�����������) ��� ������ Player. 
	Player(float x, float y, float w, float h) {

		//�������� ����� ��������� ����������
		speed = 0; dx = 0; dy = 0;
		isMove = true;
		isRestartTimer = false;
		isLife = true; onGround = false;

		//���������� ���������� ������
		this->w = w; this->h = h;
		this->x = x; this->y = y;

		//��������� ������ ������
		savePlayerSprite();
	}

	//������� ����������� ������ ������
	void savePlayerSprite() {

		playerSM.setSp("Images/TILE6.png");//��������� ������-���� � ������� � �����������
		playerSM.sprite.setTextureRect(IntRect(278, 1, w, h));//������ ������� �������������
		playerSM.sprite.setOrigin(w / 2, h / 2);//���������� ��������� ���������
	}

	//������� ����������� ������ ���������� ������
	void setSpriteFire() {

		playerSM.setSp("Images/fireman.png");//��������� ������ ���������� ������
		playerSM.sprite.setTextureRect(IntRect(0, 0, 57, 53));//������ ������� �������������
		playerSM.sprite.setOrigin(w / 2, h / 2);//���������� ��������� ���������
	}

	//������� ���������� �� ������� ���������, � ����������� �� ������� �������
	void control() {

		//�������� �� ������� �����-���� �������
		if (Keyboard::isKeyPressed) {

			//������ ������� � � ������� �����
			if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) {

				state = left;//����� ���������
				speed = 0.15;//����� ��������
				playerSM.sprite.setTextureRect(IntRect(278, 1, w, h));
			}

			//������ ������� D � ������� ������
			if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) {

				state = right;//����� ���������
				speed = 0.15;//����� ��������
				playerSM.sprite.setTextureRect(IntRect(335, 1, -w, h));
			}

			//������ ������� W, ������� ����� � ������
			if ((Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Space)) && (onGround)) {

				state = jump;//����� ���������
				dy = -0.87;//����������� ������ �� �����
				onGround = false;//��������� ������ � ��������� �� �� �����
				sizeMovement--;
			}

			//������ ������� S � ������� ����
			if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)) {

				state = down;//����� ���������
				speed = 0.15;//����� ��������
			}
		}

	}

	//������� ���������� ���������� �������� ���������� ������
	void update(float time) {

		if (isLife && isMove && sizeMovement > 0) {//�������� �� "����� ������"

			control();//����� ������� �������������� � ���������
			changeAcceleration();//����� ��������� �� ��������� 
			x += dx * time;//���������� ��������� � � ����������� �� �������
			checkCollisionWithMap(dx, 0);//�������� ������������ �� �
			y += dy * time;//���������� ��������� y � ����������� �� �������
			checkCollisionWithMap(0, dy);//�������� ������������ �� Y
			playerSM.sprite.setPosition(x + w / 2, y + h / 2); //����� ����� ������� sprite
			speed = 0;
			dy = dy + 0.0015 * time;//���������� ��������� � �����
		}
	}

	//������ ������� �������� �� ������������ ������ �� �����������
	void playerPuching(float Dx, float Dy,int i,int j) {

		if (Dy > 0) { y = i * 60 - h;  dy = 0; onGround = true; }//�������� ���� �� �����
		if (Dy < 0) { y = i * 60 + 60;  dy = 0; }//������������ � �������� ������ �����
		if (Dx > 0) { x = j * 60 - w; }//������������ � ������ ����� �����
		if (Dx < 0) { x = j * 60 + 60; }//������������ � ����� ����� �����
	}

	//������� �������� �� �������������� ��������� � ������
	void checkCollisionWithMap(float Dx, float Dy)
	{
		//���������� �� ��������� �����
		for (int i = y / 60; i < (y + h) / 60; i++) {
			for (int j = x / 60; j < (x + w) / 60; j++)
			{
				//���� ������� - �����
				if (thisArray[i][j] == '0')
				{
					playerPuching(Dx, Dy, i, j);
				}
				//���� ������� - ����������� ������ (� ����� ����)
				if (thisArray[i][j] == 'h')
				{
					//�������� �� ������� ������
					if (sizeEnemy != 0) {

						playerPuching(Dx, Dy, i, j);
					}
				}

				//���� ������� - ����
				if (thisArray[i][j] == 'l') {

					isLife = false;//����� ��������
					s[2].playSound();//����������� ���� ���������
				}

				//���� ������� - ���������
				if (thisArray[i][j] == 'e') {

					thisArray[i][j] = ' ';//������� ����������
					s[3].playSound();//����������� ���� ����� �� ����������
					s[4].playSound();//����������� ���� ������ ����������
					sizeEnemy--;//��������� ���������� ����������� �� 1
				}

				//���� ������ - ���������
				if (thisArray[i][j] == 'p') {

					isWin = true;
					isMove = false;
					if (isPlay) {
						s[1].playSound();//����������� ���� ������
						isPlay = false;
					}
				}
				
				//���� ������� - �����
				if (thisArray[i][j] == 'g') {
					s[9].playSound();//��������� ���� ������
					sizeMovement += 3;//��� �������� ������ ��������� 3 ��������
					thisArray[i][j] = ' ';
				}

				//���� ������� - ����������� ����
				if (thisArray[i][j] == 's') {

					//������ ���������� �����
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

	//������ ������� ���������� ���������� �	
	float getPlayerCoordinateX() {
		return x;
	}

	//������ ������� ���������� ���������� Y 	
	float getPlayerCoordinateY() {
		return y;
	}

	//������ ������� ��������� ���������� �
	void setPlayerCoordinateX(int x) {
		this->x = x;
	}

	//������ ������� ��������� ���������� Y 	
	void setPlayerCoordinateY(int y) {
		this->y = y;
	}

	//������ ������� ���������� ���������� �����������
	int getSizeEnemy() {
		return sizeEnemy;
	}

	//������ ������� ���������� ��������� ������
	bool getIsWin() {
		return isWin;
	}

	//������ ������� ��������� ��������� ������
	void setIsWin(bool isWin) {
		this->isWin = isWin;
	}

	//������ ������� ��������� ��������� �����
	void setIsLife(bool isLife) {
		this->isLife = isLife;
	}

private:

	//��������� ������ ���������� - ����
	bool isWin = false;

	//���������� ������ � � �, ������, ������, ��������� (�� � � �� �), ��������
	float x, y, w, h, dx, dy, speed;

	//��������� ��������  ������
	enum state { left, right, down, jump } state;

	//������� ���������� ��������� ������ � ����������� �� ���������
	void changeAcceleration() {
		switch (state)
		{

		//��������� ���� ������
		case right: {
			dx = speed;
			break;
		}

		//��������� ���� �����		
		case left: {
			dx = -speed;
			break;
		}
		}
	}

	//������� ���������� ������� ������
	void check�ollision(int Dx, int Dy, int j, int i) {

		if (Dy > 0) { y = i * 60 - h;  dy = 0; onGround = true; }//�������� ���� �� �����
		if (Dy < 0) { y = i * 60 + 60;  dy = 0; }//������������ � �������� ������ �����
		if (Dx > 0) { x = j * 60 - w; }//������������ � ������ ����� �����
		if (Dx < 0) { x = j * 60 + 60; }//������������ � ����� ����� �����
	}
};