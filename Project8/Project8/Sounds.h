#pragma once
#include <SFML/Audio.hpp>
#include <iostream>

using namespace sf;

//класс отвечающий за проигрывание звуков
class Sounds
{
public:

	//создаём объект music
	Music music;

	//конструктор по умолчанию
	Sounds() {  }

	//данная функция отвечает за инициализацию music
	void initMusic(String path) {
		music.openFromFile(path);//загружаем музыкальную дорожку
		music.setVolume(2);//задаём громкости музыки
	}

	//данная функция отвечает за проигрывание музыки
	void play() {
		music.play();//запуск проигрывания музыки
	}

	//данная функция отвечает за загрузку звуков и их громкость
	void loadSound(String path) {
		buffer.loadFromFile(path);
		Sound sound(buffer);
		sound.setVolume(3); //задаём громкость звуков
		soundPlay = sound;
	}

	//данная функция отвечает за проигрывание звуков
	void playSound() {
		soundPlay.play();
	}

	//данная функция отвечает за запрет повтора
	void setLoopFalse() {
		soundPlay.setLoop(false);
	}

	//данная функция отвечает за разрешение повтора
	void setLoopTrue() {
		soundPlay.setLoop(true);
	}

private:

	//создаём объект soundPlay
	Sound soundPlay;

	//создаём объект buffer
	SoundBuffer buffer;
};