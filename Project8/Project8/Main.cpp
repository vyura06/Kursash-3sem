#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Player.h"
#include "View.h"
#include "Sounds.h"
#include "Menu.h"
#include "StartGame.h"


using namespace sf;

//������� ���������� �� ������ ����
int main()
{
    //�������� ������� ������ Sound 
    initSounds();

    //������������ ������
    backgroundMusic.play();

    //������ ����
    startGame();
    return 0;
};