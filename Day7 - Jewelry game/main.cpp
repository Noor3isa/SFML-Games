#include <SFML/Graphics.hpp>
#include <time.h>
#include <string>
#include <iostream>

using namespace sf;

int ts = 54; //tile size
Vector2i offset(48,24);

struct piece
{ int x,y,col,row,kind,match,alpha;
  piece(){match=0; alpha=255;}
} grid[10][10];

void swap(piece p1,piece p2)
{
  std::swap(p1.col,p2.col);
  std::swap(p1.row,p2.row);

  grid[p1.row][p1.col]=p1;
  grid[p2.row][p2.col]=p2;
}


int main()
{
    srand(time(0));

    RenderWindow app(VideoMode(740,480), "Match-3 Game!");
    app.setFramerateLimit(60);

    Texture t1,t2;
    t1.loadFromFile("images/bg.jpg");
    t2.loadFromFile("images/gems.png");

    Sprite background(t1), gems(t2);
    //background.setScale(1.3,1.4);

    Font fnt;
    fnt.loadFromFile("NightmarePills-BV2w.ttf");

    int score = 0;


    Text txt;
    txt.setCharacterSize(40);
    txt.setPosition({ 500, 200 });
    txt.setFont(fnt);
    txt.setString(" ");


    for (int i=1;i<=8;i++)
      for (int j=1;j<=8;j++)
      {
          grid[i][j].kind=rand()%3;
          grid[i][j].col=j;
          grid[i][j].row=i;
          grid[i][j].x = j*ts;
          grid[i][j].y = i*ts;
      }

    int x0,y0,x,y; int click=0; Vector2i pos;
    bool isSwap=false, isMoving=false;
    std::string praise[6]={"Well Done!", "Great!", "Marvelous", "Gamed yasta", "Mesh momken!", "Aalamyy"};

    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();

            if (e.type == Event::MouseButtonPressed)
                if (e.key.code == Mouse::Left)
                {
                   if (!isSwap && !isMoving) click++;
                   pos = Mouse::getPosition(app)-offset;
                }
         }

   app.clear();
   app.draw(background);
   app.draw(txt);

   // mouse click
   if (click==1)
    {
      x0=pos.x/ts+1;
      y0=pos.y/ts+1;
    }
   if (click==2)
    {
      x=pos.x/ts+1;
      y=pos.y/ts+1;
      if (abs(x-x0)+abs(y-y0)==1)
        {swap(grid[y0][x0],grid[y][x]); isSwap=1; click=0;}
      else click=1;
    }

   //Match finding
   for(int i=1;i<=8;i++)
   for(int j=1;j<=8;j++)
   {
    if (grid[i][j].kind==grid[i+1][j].kind)
    if (grid[i][j].kind==grid[i-1][j].kind)
     for(int n=-1;n<=1;n++) grid[i+n][j].match++;

    if (grid[i][j].kind==grid[i][j+1].kind)
    if (grid[i][j].kind==grid[i][j-1].kind)
     for(int n=-1;n<=1;n++) grid[i][j+n].match++;
   }

   //Moving animation
   isMoving=false;
   for (int i=1;i<=8;i++)
    for (int j=1;j<=8;j++)
     {
       piece &p = grid[i][j];
       int dx,dy;
       for(int n=0;n<4;n++)   // 4 - speed
       {dx = p.x-p.col*ts;
        dy = p.y-p.row*ts;
        if (dx) p.x-=dx/abs(dx);
        if (dy) p.y-=dy/abs(dy);}
       if (dx||dy) isMoving=1;
     }

   //Deleting animation
   if (!isMoving)
    for (int i=1;i<=8;i++)
    for (int j=1;j<=8;j++)
    if (grid[i][j].match) if (grid[i][j].alpha>10) {grid[i][j].alpha-=10; score++; isMoving=true;}

   //Get score
   //for (int i=1;i<=8;i++)
    //for (int j=1;j<=8;j++)
      //score+=grid[i][j].match;

   //Second swap if no match
   if (isSwap && !isMoving)
      {if (!score) swap(grid[y0][x0],grid[y][x]); isSwap=0;}

   //Update grid
   if (!isMoving)
    {
      for(int i=8;i>0;i--)
       for(int j=1;j<=8;j++)
         if (grid[i][j].match)
         for(int n=i;n>0;n--)
            if (!grid[n][j].match) {swap(grid[n][j],grid[i][j]); std::cout<<score<<"\n"; txt.setString(praise[score%6]); break;};

      for(int j=1;j<=8;j++)
       for(int i=8,n=0;i>0;i--)
         if (grid[i][j].match)
           {
            grid[i][j].kind = rand()%7;
            grid[i][j].y = -ts*n++;
            grid[i][j].match=0;
            grid[i][j].alpha = 255;
           }
     }


    //////draw///////

    for (int i=1;i<=8;i++)
     for (int j=1;j<=8;j++)
      {
        piece p = grid[i][j];
        gems.setTextureRect( IntRect(p.kind*49,0,49,49));
        gems.setColor(Color(255,255,255,p.alpha));
        gems.setPosition(p.x,p.y);
        gems.move(offset.x-ts,offset.y-ts);
        app.draw(gems);
      }

     app.display();
    }
    return 0;
}
