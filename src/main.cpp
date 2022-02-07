#include "Graph.h"

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 640;

int main()
{
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode( SCREEN_WIDTH, SCREEN_HEIGHT ), "Graph Algorithm visualizer" );
    if ( window ) 
    {

    Graph* g = new Graph();
    // g->addVertex();
    

    while ( window->isOpen() )
    {
        sf::Event event;
        while ( window->pollEvent(event) )
        {
            if(event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
                window->setView(sf::View(visibleArea));
                /* update the view to the new size of the window otherwise when the window is resized, everything is squeezed/stretched to the new size */
            }

            if (event.type == sf::Event::Closed)
                window->close();
            
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		    {
			    g->addVertex(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
		    }
        }

        window->clear( sf::Color::White );
        g->draw( window );


        window->display();
    }

    }

   
   

    return 0;
}