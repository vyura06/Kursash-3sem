#pragma once
#include "Player.h"
#include "Sounds.h"
#include "SpriteManager.h"
#include <SFML/Audio.hpp>

//создаём массив для звуков
Sounds s[10];
Sounds backgroundMusic;

//функция для загрузки музыки и звуков
void initSounds() {

	//загружаем в массив звуки
	s[0].loadSound("Sounds/Прыжок.ogg");
	s[1].loadSound("Sounds/Победа.ogg");
	s[2].loadSound("Sounds/Конец Игры.ogg");
	s[3].loadSound("Sounds/Убийство.ogg");
	s[4].loadSound("Sounds/Удар.ogg");
	s[5].loadSound("Sounds/Появление.ogg");
	s[6].loadSound("Sounds/Вкл.ogg");
	s[7].loadSound("Sounds/Выкл.ogg");
	s[8].loadSound("Sounds/Клик.ogg");
	s[9].loadSound("Sounds/Бонус.ogg");

	//загружаем музыку
	backgroundMusic.initMusic("Sounds/Фон.ogg");//загрузка файла с музыкой

	//ставим музыку на повтор
	backgroundMusic.music.setLoop(true);
}