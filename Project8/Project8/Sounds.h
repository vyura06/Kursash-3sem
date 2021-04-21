#pragma once
#include <SFML/Audio.hpp>
#include <iostream>

using namespace sf;

//����� ���������� �� ������������ ������
class Sounds
{
public:

	//������ ������ music
	Music music;

	//����������� �� ���������
	Sounds() {  }

	//������ ������� �������� �� ������������� music
	void initMusic(String path) {
		music.openFromFile(path);//��������� ����������� �������
		music.setVolume(2);//����� ��������� ������
	}

	//������ ������� �������� �� ������������ ������
	void play() {
		music.play();//������ ������������ ������
	}

	//������ ������� �������� �� �������� ������ � �� ���������
	void loadSound(String path) {
		buffer.loadFromFile(path);
		Sound sound(buffer);
		sound.setVolume(3); //����� ��������� ������
		soundPlay = sound;
	}

	//������ ������� �������� �� ������������ ������
	void playSound() {
		soundPlay.play();
	}

	//������ ������� �������� �� ������ �������
	void setLoopFalse() {
		soundPlay.setLoop(false);
	}

	//������ ������� �������� �� ���������� �������
	void setLoopTrue() {
		soundPlay.setLoop(true);
	}

private:

	//������ ������ soundPlay
	Sound soundPlay;

	//������ ������ buffer
	SoundBuffer buffer;
};