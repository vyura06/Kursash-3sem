#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Player.h"
#include "View.h"
#include "Sounds.h"
#include "Menu.h"
#include "StartGame.h"


using namespace sf;

//функция отвечающая за запуск игры
int main()
{
    //создание объекта класса Sound 
    initSounds();

    //проигрывание музыки
    backgroundMusic.play();

    //запуск игры
    startGame();
    return 0;
};