#pragma once
#include <SFML\Graphics.hpp>
#include "Player.h"

#include <string>
#include <fstream>
#include <iostream>

using namespace std;
using namespace sf;

	
	//высота карты 
	const int HEIGHT_MAP_I = 20;

	//ширина карты 
	const int WIDTH_MAP_I = 40;
	const int WIDTH_MAP_II = 60;
	const int WIDTH_MAP_III = 80;

	//количество движений
	const int SIZE_MOVEMENT_I = 10;
	const int SIZE_MOVEMENT_II = 17;
	const int SIZE_MOVEMENT_III = 24;
	const int SIZE_MOVEMENT_IV = 31;

	//текущие ширина и высота карты
	int height_map = 20;
	int width_map = 40;

	//номер текущего урокня
	int numberLevel;

	sf::String thisArray[HEIGHT_MAP_I] = { "0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0", };


	void readMap(string path) {

		string line = "";

		ifstream in(path); // окрываем файл для чтения
		int index = 0;
		if (in.is_open())

		{
			while (getline(in, line))
			{
				thisArray[index] = line;
				index++;
			}

		}

		in.close(); // закрываем файл
	}