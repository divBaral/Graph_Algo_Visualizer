#include <iostream>
#include <new>

//local headers
#include "Graph.h"
#include "Dijkstra.h"
#include "Button.h"

//screen dimensions
constexpr int SCREEN_WIDTH = 1920;
constexpr int SCREEN_HEIGHT = 1080;

namespace windowmgr //for managing window
{
    sf::RenderWindow *window = NULL;
    Graph *graph = NULL;

    sf::Rect<float> buttonArea;
    //coordinates of mouse left-click; for creating new vertices
    float mouseX, mouseY;
    bool singleClick = true;
    int mode = -1;

    //vertices needed while drawing edges
    Vertex *vertexA = NULL;
    Vertex *vertexB = NULL;

    std::vector<button*> buttons;

    void createButtons();
    inline void renderButtons();

    inline void getMode();

    inline void drawingMode();

};


int main()
{
try{    
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;   //for smooth edges of shapes, this depends upon graphics card

    sf::RenderWindow *window = new sf::RenderWindow( sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Graph Algorithm visualizer", sf::Style::Default, settings );
    Graph *graph = new Graph( window );
    Dijkstra *D = new Dijkstra( window );

    windowmgr::window = window;
    windowmgr::graph = graph;


    // synchronize refresh rate with frquency of monitor
    window->setVerticalSyncEnabled( true ); 


    //creating buttons required for different modes like edit, del, run...etc
    windowmgr::createButtons();


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
                    if( event.mouseButton.button == sf::Mouse::Left )
                    {
                        windowmgr::mouseX = sf::Mouse::getPosition( *window ).x;
                        windowmgr::mouseY = sf::Mouse::getPosition( *window ).y;

                        windowmgr::getMode();

                    }
                    switch ( windowmgr::mode )
                    {
                        case 0://run dijkstra
                            D->run( windowmgr::vertexB, graph );
                        break;
                        case 1: //run bfs
                            graph->BFS( windowmgr::vertexB );
                        break;
                        case 2: //run dfs
                            graph->DFS( windowmgr::vertexB );
                            break;
                        case 3:
                            windowmgr::drawingMode();
                            break;
                        case 4:
                            windowmgr::mode = -1;
                            delete graph;
                            graph = new Graph( window );                            
                            break;
                        default:
                            break;
                    } 
                    break;


                case sf::Event::KeyPressed:
                    if( sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) )
                    {
                        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Z) )
                        {
                            windowmgr::graph->removeVertex();          // to undo the vertex added
                        }
                    }
                    break;


                default:
                    break;

            }

        }

        window->clear( sf::Color::Cyan );

        graph->draw();
        windowmgr::renderButtons();

        window->display();
    }
}


catch( std::bad_alloc& ba )
{
    std::cerr << "Error\n";
}


    return 0;
}




//definitions of methods inside windowmgr namespace

void windowmgr::createButtons()
{ 
    button *addVertex = new button();
    button *runDijkstra = new button();
    button *bfs = new button();
    button *dfs = new button();
    button *cancel = new button();

    addVertex->name = "Add Vertex";
    runDijkstra->name = "Dijkstra";
    bfs->name = "BFS";
    dfs->name = "DFS";
    cancel->name = "Cancel";

    buttons.push_back(runDijkstra);
    buttons.push_back(bfs);
    buttons.push_back(dfs);
    buttons.push_back(addVertex);
    buttons.push_back(cancel);

    sf::Vector2f size(120.f, 30.f);
    sf::Vector2f pos( SCREEN_WIDTH - size.x , 0 );
    int i = 0;
    for (  button * b : buttons ) 
    {
            b->createButton(size, pos);
            button::m_modes[b] = i++;
            pos.y += 60;
    }

	/*setting coordinates for generating button area*/
	buttonArea.width = SCREEN_WIDTH-200.f;
	buttonArea.height = SCREEN_HEIGHT;
	//top left corner coordinates of rectangular button
	buttonArea.left = 0.f;
	buttonArea.top = 0.f;
}


inline void windowmgr::renderButtons()
{
    for( button *b: buttons )
    {
        b->update( window );
        b->draw( window );
    }
}



inline void windowmgr::getMode()
{
    for ( auto b : buttons ) 
    {
        //selecting button
        if ( b->buttonArea.contains( mouseX, mouseY ) )
        {
            mode = button::m_modes[b];
            break;
        }
    }
}



inline void windowmgr::drawingMode()
{  
        mouseX = sf::Mouse::getPosition( *window ).x;
        mouseY = sf::Mouse::getPosition( *window ).y;

        vertexA = graph->getVertex( (sf::Vector2f)sf::Mouse::getPosition(*window) );
        if ( !vertexA && buttonArea.contains( mouseX, mouseY ) )
            graph->addVertex( mouseX, mouseY );
        
        if ( vertexA && vertexB && vertexA != vertexB )
            graph->addEdge( vertexA, vertexB );
        vertexB = vertexA;
        vertexA = NULL;
}