#pragma once
#include "Player.h"
#include "Sounds.h"
#include "SpriteManager.h"
#include <SFML/Audio.hpp>

//������ ������ ��� ������
Sounds s[10];
Sounds backgroundMusic;

//������� ��� �������� ������ � ������
void initSounds() {

	//��������� � ������ �����
	s[0].loadSound("Sounds/������.ogg");
	s[1].loadSound("Sounds/������.ogg");
	s[2].loadSound("Sounds/����� ����.ogg");
	s[3].loadSound("Sounds/��������.ogg");
	s[4].loadSound("Sounds/����.ogg");
	s[5].loadSound("Sounds/���������.ogg");
	s[6].loadSound("Sounds/���.ogg");
	s[7].loadSound("Sounds/����.ogg");
	s[8].loadSound("Sounds/����.ogg");
	s[9].loadSound("Sounds/�����.ogg");

	//��������� ������
	backgroundMusic.initMusic("Sounds/���.ogg");//�������� ����� � �������

	//������ ������ �� ������
	backgroundMusic.music.setLoop(true);
}