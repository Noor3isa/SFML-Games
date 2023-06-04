#include <iostream>
#include <SFML\Graphics.hpp>
#include <sstream>

class Coin {
public:
    Coin(sf::Vector2f size) {
        coin.setSize(size);
        coin.setFillColor(sf::Color::Yellow);
    }

    void drawTo(sf::RenderWindow &window) {
        window.draw(coin);
    }

    sf::FloatRect getGlobalBounds() {
        return coin.getGlobalBounds();
    }

    void setPos(sf::Vector2f newPos) {
        coin.setPosition(newPos);
    }
private:
    sf::RectangleShape coin;
};

class Player {
public:
    Player(sf::Vector2f size) {
        player.setSize(size);
        player.setFillColor(sf::Color::Green);
    }

    void drawTo(sf::RenderWindow &window) {
        window.draw(player);
    }

    void move(sf::Vector2f distance) {
        player.move(distance);
    }

    void setPos(sf::Vector2f newPos) {
        player.setPosition(newPos);
    }

    int getY() {
        return player.getPosition().y;
    }

    bool isCollidingWithCoin(Coin *coin) {
        if (player.getGlobalBounds().intersects(coin->getGlobalBounds())) {
            return true;
        }
        return false;
    }
private:
    sf::RectangleShape player;
};


int main() {
    sf::RenderWindow window;

    sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445, (sf::VideoMode::getDesktopMode().height / 2) - 480);

    window.create(sf::VideoMode(900, 900), "SFML Gravity", sf::Style::Titlebar | sf::Style::Resize);
    window.setPosition(centerWindow);

    window.setKeyRepeatEnabled(true);

    //Player Object:
    Player player({ 40, 40 });
    player.setPos({ 50, 700 });

    //Coin Objects:
    std::vector<Coin*> coinVec;
    Coin coin1({ 20, 20 });
    Coin coin2({ 20, 20 });
    coinVec.push_back(&coin1);
    coinVec.push_back(&coin2);

    coin1.setPos({ 50, 600 });
    coin2.setPos({ 100, 600 });

    //Score Objects:

    int score = 0;

    sf::Font arial;
    arial.loadFromFile("arial.ttf");

    std::ostringstream ssScore;
    ssScore << "Score: " << score;

    sf::Text lblScore;
    lblScore.setCharacterSize(30);
    lblScore.setPosition({ 10, 10 });
    lblScore.setFont(arial);
    lblScore.setString(ssScore.str());

    //Gravity Variables:
    const int groundHeight = 700;
    const float gravitySpeed = 0.3;
    bool isJumping = false;

    //Main Loop:
    while (window.isOpen()) {

        sf::Event Event;

        const float moveSpeed = 0.2;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            player.move({ 0, -moveSpeed });
            isJumping = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            player.move({ moveSpeed, 0 });
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            player.move({ -moveSpeed, 0 });
        }

        //Event Loop:
        while (window.pollEvent(Event)) {
            switch (Event.type) {

            case sf::Event::Closed:
                window.close();

            case sf::Event::KeyReleased:
                isJumping = false;
            }
        }

        //Gravity Logic:
        if (player.getY() < groundHeight && isJumping == false) {
            player.move({ 0, gravitySpeed });
        }

        //Coin Logic:
        for (int i = 0; i < coinVec.size(); i++) {
            if (player.isCollidingWithCoin(coinVec[i])) {
                coinVec[i]->setPos({ 422234, 423432 });
                score++;
                ssScore.str("");
                ssScore << "Score " << score;
                lblScore.setString(ssScore.str());
            }
        }

        window.clear();
        coin1.drawTo(window);
        window.draw(lblScore);
        coin2.drawTo(window);
        player.drawTo(window);
        window.display();
    }
}
