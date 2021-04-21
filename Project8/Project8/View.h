#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

	View view;//объ€вили  камеры

	//функци€ дл€ считывани€ координат игрока
	void setViewPosition(float x, float y) {

		float tempX = x; float tempY = y;//считываем корд игрока и провер€ем их, чтобы убрать кра€

		//убираем из вида левую часть
		if (x < 960) { tempX = 960; }
		if (numberLevel > 6 && numberLevel < 11) { if (x > 3840) tempX = 3840; }
		if (numberLevel > 2 && numberLevel < 7) { if (x > 2640) tempX = 2640; }

		//убираем из вида правую часть
		if (numberLevel > 0 && numberLevel < 3) { if (x > 1440) tempX = 1440; }

		//убираем верхнюю часть
		if (y < 540) { tempY = 540; }

		//убираем нижнюю часть
		if (y > 661) { tempY = 661; }

		view.setCenter(tempX, tempY); //следим за игроком, передава€ его координаты
	}

	//функци€ дл€ перемещени€ камеры по карте
	void viewMap(float time) {

		if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) {
			view.move(0.1 * time, 0);//скроллим карту вправо
		}

		if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) {
			view.move(-0.1 * time, 0);//скроллим карту влево
		}

		if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Space)) {
			view.move(0, 0.1 * time);//скроллим карту вверх
		}


		if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)) {
			view.move(0, -0.1 * time);//скроллим карту вниз
		}
	}