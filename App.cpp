#include "App.h"

App::App()
{
    initialize();
}
App::~App()
{
    delete window;
}

void App::initialize(){
    width = 904;
    height = 750;
    auto gray = sf::Color(211, 211, 211);
    sf::Color color;
    texture.loadFromFile("q.png");
    font.loadFromFile("Fuente.ttf");
    nAttempts = 0;
    float s = 80;
    float x = 75;
    float y = 35;
    attempts.setFont(font);
    attempts.setCharacterSize(24);
    attempts.setFillColor(sf::Color::Black);
    attempts.setPosition(720, y);
    window = new sf::RenderWindow(sf::VideoMode(width, height), "8 queens problem");
    window->setPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width-width)/2,
    (sf::VideoMode::getDesktopMode().height-height)/2));
    window->setFramerateLimit(30);
    for(size_t i = 0; i < size; i++){
        for(size_t j = 0; j < size; j++){
            board[i][j].setSize({s, s});
            board[i][j].setPosition(x + j*s, y + i*s);
            board[i][j].setOutlineThickness(2);
            board[i][j].setOutlineColor(sf::Color::Black);
            if(j % 2 == 0){
                if(i % 2 == 0) color = gray;
                else color = sf::Color::White;
            }else{
                if(i % 2 == 0) color = sf::Color::White;
                else color = gray;
            }
            board[i][j].setFillColor(color);
        }
    }
    for(size_t i = 0; i < size; i++) queens[i].sp.setTexture(texture);
}
bool App::isOk(int i){
    int r;
    bool flag = true;
    for(r = 0; r <= i - 1; r++){
        flag = flag && (queens[r].row != queens[i].row);
        flag = flag && (queens[r].row - r) != (queens[i].row - i);
        flag = flag && (queens[r].row + r) != (queens[i].row + i);
    }
    return flag;
}
void App::solve(int i, bool & solution){
    int k;
    solution = false;
    k = -1;
    do{
        k++;
        queens[i].row = k;
        attempts.setString("Attempts: " + std::to_string(++nAttempts));
        if(isOk(i)){
            queens[i].sp.setPosition(board[queens[i].row][i].getPosition().x - delta, board[queens[i].row][i].getPosition().y);
            draw(i);
            if(i < int(size) - 1){
                solve(i + 1, solution);
                if(!solution){
                    queens[i].row = 0;
                }
            }else solution = true;
        }
    }while(!solution && (k < int(size) - 1));
}

void App::gameLoop(){
    bool solution;
    solve(0, solution);
    for(size_t i = 0; i < size; i++) std::cout << queens[i].row << ", " << i << std::endl;
    while(window->isOpen()){
        events();
        draw(size);
    }
}
void App::draw(size_t t){
    window->clear(sf::Color::White);
    window->draw(attempts);
    for(size_t i = 0; i < size; i++){
        for(size_t j = 0; j < size; j++){
            window->draw(board[i][j]);
        }
    }
    for(size_t i = 0; i < t; i++) window->draw(queens[i].sp);
    window->display();
}
void App::events(){
    sf::Event event;
    while(window->pollEvent(event)){
        switch(event.type){
            case sf::Event::Closed:
                window->close();
                break;
            default:
                break;
        }
    }
}
