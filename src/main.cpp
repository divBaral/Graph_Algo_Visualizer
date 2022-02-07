#include "Graph.h"

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 640;

int main()
{
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode( SCREEN_WIDTH, SCREEN_HEIGHT ), "Graph Algorithm visualizer" );
    if ( window ) 
    {

    Graph* g = new Graph();
    g->addVertex();
    

    while ( window->isOpen() )
    {
        sf::Event event;
        while ( window->pollEvent(event) )
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear( sf::Color::White );
        g->draw( window );


        window->display();
    }

    }

   
   

    return 0;
}