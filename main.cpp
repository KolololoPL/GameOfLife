#include <cstdlib>
#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;

void Update();
void Draw();
void EventHandle(sf::Event);

sf::RenderWindow rWindow(sf::VideoMode(700, 700, 32), "Kurs SFML");

sf::Texture cellTx;
sf::Sprite cellSp;

bool cells[140][140];
bool cellsTmp[140][140];
bool run = true;

int main() {
    if (!cellTx.loadFromFile("Resources/cell.jpg"))
        cout << "Blad odczytu obrazka!";
    cellSp.setTexture(cellTx);

    for (int x = 0; x < 140; x++) {
        for (int y = 0; y < 140; y++) {
            cells[x][y] = false;
        }
    }

    //Initialization
    cells[10][10] = true;
    cells[11][10] = true;
    cells[12][10] = true;
    cells[12][9] = true;
    cells[11][8] = true;

    cells[100][100] = true;
    cells[100][101] = true;
    cells[101][101] = true;
    cells[101][100] = true;

    cells[102][102] = true;
    cells[102][103] = true;
    cells[103][103] = true;
    cells[103][102] = true;

    while (rWindow.isOpen()) {
        //Update!
        Update();

        sf::Event event;
        while (rWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                rWindow.close();
            } else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) {
                rWindow.close();
            }

            //Handling events
            EventHandle(event);
        }

        rWindow.clear(sf::Color(0, 0, 0));
        //Draw scene
        Draw();
        rWindow.display();
    }

    return 0;
}

void Update () {
    if (!run)
        return;

    for (int x = 1; x < 139; x++) {
        for (int y = 1; y < 139; y++) {
            cellsTmp[x][y] = cells[x][y];

            int aliveNbr = 0;
            if (cells[x - 1][y - 1])
                aliveNbr++;
            if (cells[x][y - 1])
                aliveNbr++;
            if (cells[x + 1][y - 1])
                aliveNbr++;
            if (cells[x - 1][y])
                aliveNbr++;
            if (cells[x + 1][y])
                aliveNbr++;
            if (cells[x - 1][y + 1])
                aliveNbr++;
            if (cells[x][y + 1])
                aliveNbr++;
            if (cells[x + 1][y + 1])
                aliveNbr++;

            if (aliveNbr == 3)
                cellsTmp[x][y] = true;
            else if (aliveNbr != 2)
                cellsTmp[x][y] = false;
        }
    }
}

void Draw () {
    for (int x = 0; x < 140; x++) {
        for (int y = 0; y < 140; y++) {
            cells[x][y] = cellsTmp[x][y];
            if (cells[x][y]) {
                cellSp.setPosition(x * 5, y * 5);
                rWindow.draw(cellSp);
            }
        }
    }
}

void EventHandle (sf::Event event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
        run = !run;
    else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::C) {
        for (int x = 0; x < 140; x++) {
            for (int y = 0; y < 140; y++) {
                cellsTmp[x][y] = false;
            }
        }
    } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i positionInWindow = sf::Mouse::getPosition(rWindow);
        sf::Vector2f positionOnScene = rWindow.mapPixelToCoords(positionInWindow);

        int x = (int)(positionOnScene.x / 5);
        int y = (int)(positionOnScene.y / 5);

        cellsTmp[x][y] = !cellsTmp[x][y];
    }
}
