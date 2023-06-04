#include <SFML/Graphics.hpp>
sf::Color mycolor(255, 100, 255); // pink

int main()
{
    sf::RenderWindow window(sf::VideoMode(1300, 800), "Look at my shapes!", sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(60);

    sf::Texture sherlock, watson, bg, dementor;
    sherlock.loadFromFile("sherlock.png");
    watson.loadFromFile("watson.png");
    bg.loadFromFile("bg.jpg");
    dementor.loadFromFile("dementor.png");
    sf::Sprite Sherlock, Watson, BG, Dementor;
    Dementor.setTexture(dementor);
    BG.setTexture(bg);
    Sherlock.setTexture(sherlock);
    Watson.setTexture(watson);
    Sherlock.setScale(0.3f,0.3f);
    Watson.setScale(0.5f,0.5f);
    BG.setScale(0.9f,0.9f);
    Dementor.setScale(0.5f, 0.5f);
    Sherlock.setPosition(900,200);
    Sherlock.setOrigin(450,100);
    Watson.setPosition(300,200);
    Watson.setPosition(150,100);
    BG.setPosition(-100,0);


    while (window.isOpen())
    {
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            if (evnt.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(BG);
        window.draw(Dementor);
        window.draw(Sherlock);
        window.draw(Watson);

        //Sherlock Holmes
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){ Sherlock.move(0, -2);};
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){Sherlock.move(0, 2);};
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){Sherlock.move(2, 0);};
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){Sherlock.move(-2, 0);};
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){Sherlock.rotate(5.f);}
        //Dr.Watson
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){ Watson.move(0, -2);};
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){Watson.move(0, 2);};
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){Watson.move(2, 0);};
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){Watson.move(-2, 0);};
        if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){Watson.rotate(5.f);}
        Dementor.move(1.f, 0);
        if(Dementor.getPosition().x > 1300) { Dementor.setPosition(-200,0);}

        if(Sherlock.getPosition().x > 1300) { Sherlock.setPosition(1300,Sherlock.getPosition().y);}
        if(Sherlock.getPosition().x < 0) { Sherlock.setPosition(0,Sherlock.getPosition().y);}
        if(Sherlock.getPosition().y > 700) { Sherlock.setPosition(Sherlock.getPosition().x,700);}
        if(Sherlock.getPosition().y < 0) { Sherlock.setPosition(Sherlock.getPosition().x,0);}

        if(Watson.getPosition().x > 1300) { Watson.setPosition(1300,Watson.getPosition().y);}
        if(Watson.getPosition().x < 0) { Watson.setPosition(0,Watson.getPosition().y);}
        if(Watson.getPosition().y > 700) { Watson.setPosition(Watson.getPosition().x,700);}
        if(Watson.getPosition().y < 0) { Watson.setPosition(Watson.getPosition().x,0);}

        window.display();
    }

    return 0;
}
