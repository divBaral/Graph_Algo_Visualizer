#include <iostream>
#include "Graph.h"
#include "Dijkstra.h"

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 640;

int main()
{
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Graph Algorithm visualizer");

    if (window)
    {
        Dijkstra *d = new Dijkstra();
        Graph *g = new Graph();
        // g->addVertex();

        float tempx, tempy;       //for the addition of vertices after the mouse click is released
        bool singleClick = true;

        Vertex *temp1, *temp2;

        window->setVerticalSyncEnabled(true); // synchronize refresh rate with frquency of monitor

        while (window->isOpen())
        {
            sf::Event event;
            while (window->pollEvent(event))
            {
                switch(event.type)
                {
                    case sf::Event::Closed:  
                            window->close();     //closes the window
                            break;

                    case sf::Event::Resized:
                        {
                            sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
                            window->setView(sf::View(visibleArea));
                            /* update the view to the new size of the window otherwise when the window is resized, everything is squeezed/stretched to the new size */
                            break;
                        }

                    case sf::Event::MouseButtonPressed:
                        if(singleClick && event.mouseButton.button == sf::Mouse::Left) 
                        {
                            temp1 = g->getVertex((sf::Vector2f)sf::Mouse::getPosition(*window));
                            singleClick = false;
                            tempx = sf::Mouse::getPosition(*window).x;      //to get the position when left mouse button is clicked      
                            tempy = sf::Mouse::getPosition(*window).y;      //and use that when it is released
                        }
                        break;

                    case event.MouseButtonReleased:
                        singleClick = true;
                        if(temp1)
                        {
                            temp2 = g->getVertex((sf::Vector2f)sf::Mouse::getPosition(*window));
                            if(temp2)
                            {
                                g->addEdge(temp1, temp2);
                                temp1 = temp2 = NULL;
                                break;
                            }
                            temp1 = NULL;
                        }
                        else{
                            g->addVertex(tempx, tempy);            //adds vertex only after mouse button is released
                            break;
                        }

                    case sf::Event::KeyPressed:
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                        {
                            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
                            {
                                g->removeVertex();                        // to undo the vertex added
                                break;
                            }

                        }

                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                        {
                            if(temp1)
                                d->run(temp1, window, g);   //to run dijkstra, just for checking
                                break;
                        }

                }

            }


            window->clear(sf::Color::White);
            g->draw(window);

            window->display();
        }
    }

    return 0;
}