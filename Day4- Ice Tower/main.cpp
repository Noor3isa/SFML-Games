#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <time.h>
using namespace sf;

struct position{
    int j, k;
};

int main()
{
    //create main windwo
    RenderWindow window(VideoMode(600, 800), "New App!", Style::Close | Style::Titlebar);
    window.setFramerateLimit(100);

    Clock clock;
    float y = 0, yi = 0;
    int x = 240, h = 100;

    srand(time(0));
    struct position plat[7];
    for(int i=0; i<7; i++){
        plat[i].j=rand()%500;
        plat[i].k=rand()%800;
        }

    //text
    Font fnt;
    fnt.loadFromFile("NightmarePills-BV2w.ttf");

    /*Text txt, score;
    txt.setFont(fnt);
    txt.setString("Score: ");
    txt.setCharacterSize(50);
    txt.setPosition(400,20);
    txt.setColor(Color(220, 220, 255, 150));
    txt.setStyle(Text::Bold);

    score.setFont(fnt);
    score.setString(toString(si));
    score.setCharacterSize(50);
    score.setPosition(520,20);
    score.setColor(Color(220, 220, 255, 150));
    score.setStyle(Text::Bold);*/

    Text gameover;
    gameover.setFont(fnt);
    gameover.setString("Game Over..");
    gameover.setCharacterSize(80);
    gameover.setPosition(100,300);
    gameover.setColor(Color(220, 220, 255, 150));
    gameover.setStyle(Text::Bold);


    //loading files
    Texture characterpng, woodpng, wallpaperpng;
    characterpng.loadFromFile("character.png");
    woodpng.loadFromFile("wood2.png");
    wallpaperpng.loadFromFile("wallpaper.png");

    //creating sprites
    Sprite character(characterpng), step(woodpng), wallpaper(wallpaperpng);
    //character.setOrigin(20,29.5);
    step.setScale(0.2,0.3);



    while(window.isOpen()){
        Event evnt;
        while (window.pollEvent(evnt))
        {
            if (evnt.type == Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(wallpaper);
        //window.draw(txt);
        //window.draw(score);
        window.draw(character);
        for(int i=0; i<7; i++){
            step.setPosition(plat[i].j, plat[i].k);
            window.draw(step);
        }
        for(int i=0; i<7; i++){
            if((x+40>plat[i].j) && (x<plat[i].j+98) && (y+59>=plat[i].k) && (y<plat[i].k+2) && (yi>0)) {
                    yi=-10;
                    //do{character.rotate(30.f);} while(character.getRotation()<=360 && character.getRotation()>=30);
            }
        }

        if(y<h){
            for(int i=0; i<7; i++){
                y=h;
                plat[i].k -= yi;
                if(plat[i].k>800) {plat[i].k=0; plat[i].j=rand()%500;}
            }
        }

        yi+= 0.1;
        y += yi;
        if(Keyboard::isKeyPressed(Keyboard::Right) && character.getPosition().x < 560 ){ x +=2;}
        if(Keyboard::isKeyPressed(Keyboard::Left) && character.getPosition().x > 0){ x -=2;}
        character.setPosition(x, y);
        if(character.getPosition().x < 0){character.setPosition(0, y);}
        if(character.getPosition().x > 550){ character.setPosition(550, y);}
        if(character.getPosition().y > 750){
                window.draw(gameover);}

        window.display();
    }
    return 0;
}
