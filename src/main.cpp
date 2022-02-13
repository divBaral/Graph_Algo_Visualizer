#include <iostream>
#include <new>

//local headers
#include "Graph.h"
#include "Dijkstra.h"

//screen dimensions
constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 640;

int main()
{
    sf::RenderWindow *window;
    window = new(std::nothrow) sf::RenderWindow( sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Graph Algorithm visualizer" );

    // sf::ContextSettings settings;
    // settings.antialiasingLevel = 8;   //for smooth edges of shapes, this depends upon graphics card

    if( window )
    {
        Dijkstra *d = new Dijkstra( window );
        Graph *g = new Graph( window );
        
        //coordinates of mouse left-click; for creating new vertices
        float posX, posY;
        bool singleClick = true;

        //vertices needed while drawing edges
        Vertex *vertex1 = NULL;
        Vertex *vertex2 = NULL;

        // synchronize refresh rate with frquency of monitor
        window->setVerticalSyncEnabled( true ); 

        while ( window->isOpen() )
        {
            sf::Event event;
            while ( window->pollEvent(event) )
            {
                switch(event.type)
                {
                    case sf::Event::Closed:  
                        window->close();     //closes the window
                        break;

                    case sf::Event::Resized:
                    {
                        sf::FloatRect visibleArea( 0.f, 0.f, event.size.width, event.size.height );
                        window->setView( sf::View(visibleArea) );
                        /* update the view to the new size of the window otherwise when the window is resized, 
                        everything is squeezed/stretched to the new size */
                        break;
                    }

                    case sf::Event::MouseButtonPressed:
                        if( singleClick && event.mouseButton.button == sf::Mouse::Left ) 
                        {
                            vertex1 = g->getVertex( (sf::Vector2f)sf::Mouse::getPosition(*window) );
                            singleClick = false;
                            posX = sf::Mouse::getPosition( *window ).x;      //to get the position when left mouse button is clicked      
                            posY = sf::Mouse::getPosition( *window ).y;      //and use that when it is released
                        }
                        break;

                    case event.MouseButtonReleased:
                        singleClick = true;
                        if( vertex1 )
                        {
                            vertex2 = g->getVertex( (sf::Vector2f)sf::Mouse::getPosition(*window) );
                            if( vertex2 && vertex1 != vertex2 )
                            {
                                g->addEdge( vertex1, vertex2 );
                                vertex1 = vertex2 = NULL;
                            }
                            vertex1 = NULL;
                        }
                        else
                        {
                            g->addVertex( posX, posY );     //adds vertex only after mouse button is released
                        }
                        break;

                    case sf::Event::KeyPressed:
                        if( sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) )
                        {
                            if( sf::Keyboard::isKeyPressed(sf::Keyboard::Z) )
                            {
                                g->removeVertex();          // to undo the vertex added
                            }

                        }
                        if( sf::Keyboard::isKeyPressed(sf::Keyboard::D) )
                        {
                            if( vertex1 )
                            d->run( vertex1, g );   //to run dijkstra, just for checking
                            //g->DFS( vertex1 );
                        }
                        if( sf::Keyboard::isKeyPressed(sf::Keyboard::B) )
                        {
                            if( vertex1 )
                                g->BFS( vertex1 );
                        }
                        break;

                    default:
                        break;

                }

            }


            window->clear( sf::Color::White );
            g->draw();

            window->display();
        }
    }

    return 0;
}