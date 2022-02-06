#include "../include/Vertex.h"
#include "../include/Edge.h"

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 640;

int main()
{
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode( SCREEN_WIDTH, SCREEN_HEIGHT ), "Graph Algorithm visualizer" );

    Vertex* v1 = new Vertex(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    Vertex* v2 = new Vertex(600, 100);
    Edge* e =  new Edge(v1, v2);
    

    while ( window->isOpen() )
    {
        sf::Event event;
        while ( window->pollEvent(event) )
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear( sf::Color::White );

        v1->draw( window );
        v2->draw( window );
        e->draw( window );



        window->display();
    }

    return 0;
}