#include <SFML/Graphics.hpp>
#include <cstdlib>
using namespace sf;

int main()
{
    //create main windwo
    RenderWindow window(VideoMode(800, 900), "Look at my shapes!", Style::Close | Style::Titlebar);
    window.setFramerateLimit(120);
    int x1, y1, x2, y2, xc, yc;
    x1 = y1 = 0;
    xc = yc = 1;

    //text
    Font fnt;
    fnt.loadFromFile("NightmarePills-BV2w.ttf");
    Text txt;
    txt.setFont(fnt);
    txt.setString("ICE TOWER");
    txt.setCharacterSize(80);
    txt.setPosition(200,50);
    txt.setColor(Color(220, 220, 255));
    txt.setStyle(Text::Bold);

    //loading files
    Texture character, wood, wallpaper;
    character.loadFromFile("character.png");
    wood.loadFromFile("wood.png");
    wallpaper.loadFromFile("wallpaper.png");
    //creating sprites
    Sprite Character, Step1, Step2, Wallpaper;
    Character.setTexture(character);
    Step1.setTexture(wood);
    Step2.setTexture(wood);
    Wallpaper.setTexture(wallpaper);
    //positions
    Character.setPosition(rand()%800, rand()%900);
    Step1.setPosition(65, 420);
    Step2.setPosition(795, 420);

    Step1.setScale(0.65, 0.65);
    Step2.setScale(0.65, 0.65);
    Wallpaper.setScale(1.1,1.1);
    Step1.rotate(90);
    Step2.rotate(90);

    while(window.isOpen()){
        Event evnt;
        while (window.pollEvent(evnt))
        {
            if (evnt.type == Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(Wallpaper);
        window.draw(txt);
        window.draw(Step1);
        window.draw(Step2);
        window.draw(Character);

        //logic
        Character.move(xc, yc);

        if(Character.getPosition().x < 0) {xc = -xc;}
        if(Character.getPosition().x > 800) {xc = -xc;}
        if(Character.getPosition().y < 0) {yc = -yc;}
        if(Character.getPosition().y > 800) {yc = -yc;}

        if(evnt.type == Event::KeyReleased){
            if(evnt.key.code == Keyboard::Left | Keyboard::Right | Keyboard::Down | Keyboard::Up){
                x1 = y1 = 0;
            }
        }

        if(Keyboard::isKeyPressed(Keyboard::Up)){ y1 -=1;}
        if(Keyboard::isKeyPressed(Keyboard::Down)){ y1 +=1;}
        Step1.move(x1,y1);
        Step2.move(0, yc);

        if(Step1.getPosition().y < 0){Step1.setPosition(65, 0);}
        if(Step1.getPosition().y > 600){Step1.setPosition(65, 600);}

        if(Step2.getPosition().y < 0){Step2.setPosition(795, 0);}
        if(Step2.getPosition().y > 600){Step2.setPosition(795, 600);}

        if(Character.getGlobalBounds().intersects(Step1.getGlobalBounds())){
            xc = -xc;
            yc = -yc;

        }
        if(Character.getGlobalBounds().intersects(Step2.getGlobalBounds())){
            xc = -xc;
            yc = -yc;
        }



        window.display();
    }
    return 0;
}
