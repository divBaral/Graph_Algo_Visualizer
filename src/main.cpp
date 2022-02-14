#include <iostream>
#include <new>

//local headers
#include "Graph.h"
#include "Dijkstra.h"
#include "Button.h"

//screen dimensions
constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 640;

namespace windowmgr //for managing window
{
    sf::RenderWindow *window = NULL;
    Graph *graph = NULL;

    sf::Rect<float> buttonArea;
    //coordinates of mouse left-click; for creating new vertices
    float mouseX, mouseY;
    bool singleClick = true;
    int mode;

    //vertices needed while drawing edges
    Vertex *vertexA = NULL;
    Vertex *vertexB = NULL;

    std::vector<button*> buttons;

    void createButtons();
    inline void renderButtons();

    inline int getMode();

    inline void drawingMode();
    inline void addEdge();
};


int main()
{
try{    
    sf::RenderWindow *window = new sf::RenderWindow( sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Graph Algorithm visualizer" );
    Graph *graph = new Graph( window );

    windowmgr::window = window;
    windowmgr::graph = graph;


    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;   //for smooth edges of shapes, this depends upon graphics card


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

                        windowmgr::mode = windowmgr::getMode();

                    }
                    break;


                case event.MouseButtonReleased:
                    windowmgr::addEdge();
                    break;


                case sf::Event::KeyPressed:
                    if( sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) )
                    {
                        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Z) )
                        {
                            windowmgr::graph->removeVertex();          // to undo the vertex added
                        }
                    }
                    // if( sf::Keyboard::isKeyPressed(sf::Keyboard::D) )
                    // {
                    //     if( vertex1 )
                    //     d->run( vertex1, graph );   //to run dijkstra, just for checking
                    //     //g->DFS( vertex1 );
                    // }
                    // if( sf::Keyboard::isKeyPressed(sf::Keyboard::B) )
                    // {
                    //     if( vertex1 )
                    //         graph->BFS( vertex1 );
                    // }
                    break;


                default:
                    break;

            }

        }

        switch ( windowmgr::mode )
        {
            case 0://run dijkstra
                //graph->Dijkstra();
            break;
            case 1: //run bfs
                //graph->BFS();
            break;
            case 2: //run dfs
                //graph->DFS();
                break;
            case 3: //add vertex
                windowmgr::drawingMode();
                break;
            default:
                break;
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
    button* addVertex = new button();
    button* runDijkstra = new button();
    button* bfs = new button();
    button* dfs = new button();

    addVertex->name = "Add Vertex";
    runDijkstra->name = "Dijkstra";
    bfs->name = "BFS";
    dfs->name = "DFS";

    buttons.push_back(runDijkstra);
    buttons.push_back(bfs);
    buttons.push_back(dfs);
    buttons.push_back(addVertex);

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
	buttonArea.width = size.x;
	buttonArea.height = 8*size.y;
	//top left corner coordinates of rectangular button
	buttonArea.left = pos.x;
	buttonArea.top = pos.y;
}


inline void windowmgr::renderButtons()
{
    for( button *b: buttons )
    {
        b->update( window );
        b->draw( window );
    }
}



inline int windowmgr::getMode()
{
    button *Button = NULL;
    for ( auto b : buttons ) 
    {
        //selecting button
        if ( b->buttonArea.contains( mouseX, mouseY ) )
        {
            Button = b;
            break;
        }
    }
    
    return button::m_modes[Button];
}



inline void windowmgr::drawingMode()
{  
    if( singleClick )
    {

        mouseX = sf::Mouse::getPosition( *window ).x;      //to get the position when left mouse button is clicked      
        mouseY = sf::Mouse::getPosition( *window ).y;      //and use that when it is released
        if( !buttonArea.contains( mouseX, mouseY ) )
            graph->addVertex( mouseX, mouseY );
        vertexA = graph->getVertex( (sf::Vector2f)sf::Mouse::getPosition(*window) );

        singleClick = false;

    }
}


inline void windowmgr::addEdge()
{
    if( vertexA )
    {
        vertexB = graph->getVertex( (sf::Vector2f)sf::Mouse::getPosition(*window) );
        if( vertexB && vertexA != vertexB )
        {
            graph->addEdge( vertexA, vertexB );
            vertexA = vertexB = NULL;
        }
        vertexA = NULL;
    }
    else
    {
        graph->addVertex( mouseX, mouseY );     //adds vertex only after mouse button is released
    }

    singleClick = true;
}