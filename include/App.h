#ifndef APP_H
#define APP_H
#include <SFML/Graphics.hpp>
#include <iostream>
class App
{
    public:
        App();
        ~App();
        void gameLoop();
    private:
        struct Queen{
            public:
                int row = -1;
                sf::Sprite sp;
        };
        int nAttempts;
        size_t width, height;
        static const size_t size = 8;
        static const int delta = 17;
        sf::RenderWindow *window;
        sf::RectangleShape board[size][size];
        sf::Texture texture;
        sf::Text attempts;
        sf::Font font;
        Queen queens[size];
        void events();
        void draw(size_t);
        void initialize();
        void solve(int i, bool & solution);
        bool isOk(int i);
};

#endif

