#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

int main(){

    //create main window
    RenderWindow window(VideoMode(600,900), "Try to land challenge! lol", Style::Close | Style::Titlebar);
    window.setFramerateLimit(100);

    float y=0;
    bool gamedone=0;

    //text
    //text
    Font fnt;
    fnt.loadFromFile("NightmarePills-BV2w.ttf");

    Text welldone, gameover;
    welldone.setFont(fnt);
    welldone.setString("Well Done!");
    welldone.setCharacterSize(80);
    welldone.setPosition(100,300);
    welldone.setColor(Color(220, 220, 255));
    welldone.setStyle(Text::Bold);

    gameover.setFont(fnt);
    gameover.setString("Game Over..");
    gameover.setCharacterSize(80);
    gameover.setPosition(100,300);
    gameover.setColor(Color(220, 220, 255));
    gameover.setStyle(Text::Bold);

    Texture bg, planet, spaceship;
    bg.loadFromFile("space.jpg");
    planet.loadFromFile("planet.png");
    spaceship.loadFromFile("spaceship.png");

    Sprite BG(bg), Planet(planet), Spaceship(spaceship);

    Planet.setScale(0.4,0.4);
    Spaceship.setScale(0.3, 0.3);
    BG.setScale(0.9, 0.9);

    Planet.setPosition(-100, 600);
    Spaceship.setPosition(200,0);


    while(window.isOpen()){
        Event evnt;
        while(window.pollEvent(evnt)){
            if(evnt.type == Event::Closed)
                window.close();
        }
        window.clear();

        window.draw(BG);
        window.draw(Planet);
        window.draw(Spaceship);


        if((Keyboard::isKeyPressed(Keyboard::Up)) && (Spaceship.getPosition().y > 0) && (!gamedone)){ y -=1;}
        if(Keyboard::isKeyPressed(Keyboard::Down) && (!gamedone)){ y +=1;}
        Spaceship.move(0, y);

        if(Spaceship.getPosition().y < 0){Spaceship.setPosition(200, 0);}

        if(Spaceship.getGlobalBounds().intersects(Planet.getGlobalBounds())){
            gamedone=1;
            if(y<=10){
                y=0;
                window.draw(welldone);
                //std::cout<<"well done";
            }
            else{
                window.draw(gameover);
                //std::cout<<"game over";
            }
        }
        if(Spaceship.getPosition().y>900){
                window.draw(gameover);}


        window.display();


    }
    return 0;
}
