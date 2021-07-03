#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>

using namespace std;
using namespace sf;

const int size = 60;


Sprite fig[32];

int board[8][8]=
{
    -1,-2,-3,-4,-5,-3,-2,-1,
    -6,-6,-6,-6,-6,-6,-6,-6,
     0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0,        //Positions of figures
     0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0,
     6, 6, 6, 6, 6, 6, 6, 6,
     1, 2, 3, 4, 5, 3, 2, 1
};


void pos()
{
    int q = 0;

    for(int i = 0; i<8;++i)
        for(int j = 0;j<8;++j)
        {
            int b = board[i][j];
            if(!b) continue;
            int x = abs(b)-1;
            int y = b>0?1:0;
            fig[q].setTextureRect(IntRect(size*x,size*y,size,size));
            fig[q].setPosition(size*j+20,size*i+7);
            ++q;
        }
}

int main()
{
    RenderWindow window(VideoMode(512,512),"The Chess game beta 1.0");

    Texture figures,board;
    figures.loadFromFile("Textures/Chees_figures.png");
    board.loadFromFile("Textures/Chess_board.png");

    Sprite f(figures);
    Sprite bo(board);

    for (int i = 0; i<32;++i) fig[i].setTexture(figures);

    pos();

    bool isMove=false;
    double x=0;
    double y=0;
    Vector2f oldPos,newPos;
    string str;
    int n = 0;

    while (window.isOpen())
    {
        Vector2i position = Mouse::getPosition(window);
        Event e;
        while (window.pollEvent(e))
        {
            if(e.type == sf::Event::Closed || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
                window.close();
            if (e.type == Event::MouseButtonPressed)
                if (e.key.code == Mouse::Left)
                for(int i = 0;i<32;++i)
                    if (fig[i].getGlobalBounds().contains(position.x,position.y))
                    {
                        isMove=1;n=i;
                        x=position.x - fig[i].getPosition().x;
                        y=position.y - fig[i].getPosition().y;
                        oldPos = fig[i].getPosition();
                    }
            if (e.type == Event::MouseButtonReleased)
                if (e.key.code == Mouse::Left)
                {
                    isMove=0;
                    Vector2f p = fig[n].getPosition() + Vector2f(size/2,size/2);
                    Vector2f np = Vector2f(size*int(p.x/size)+20,size*int(p.y/size)+7);
                    newPos = Vector2f(size*int(p.x/size),size*int(p.y/size));
                    fig[n].setPosition(np);
                }
        }

                if (isMove) fig[n].setPosition(position.x-x,position.y-y);
        window.clear();
        window.draw(bo);
        for(int i=0;i<32;++i) window.draw(fig[i]);
        window.display();
    }
    
    return 0;
}