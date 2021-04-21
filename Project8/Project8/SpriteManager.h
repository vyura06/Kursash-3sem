#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

//класс, отвечающий за работу со спрайтами
class SpriteManager {
public:

	//текстура и спрайт
	Texture texture;
	Sprite sprite;

	//конструктор по умолчанию
	SpriteManager() {}

	//метод получающий путь и загружающий текстуру и спрайт
	void setSp(String path) {
		texture.loadFromFile(path);//загрузка текстры
		sprite.setTexture(texture);//загрузка спрайта
	}
};

