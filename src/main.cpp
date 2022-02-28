#include <iostream>
#include <new>

// local headers
#include "Graph.h"
#include "Dijkstra.h"
#include "Kruskal.h"
#include "Button.h"

// screen dimensions
constexpr int SCREEN_WIDTH = 1920;
constexpr int SCREEN_HEIGHT = 1080;

// for different modes
enum modes
{
    DIJKSTRAMODE = 0,
    BFSMODE,
    DFSMODE,
    KRUSKALMODE,
    DRAWINGMODE,
    RESTOREMODE,
    DELETEMODE,
    CLEARMODE,
    EXITMODE
};

namespace windowmgr // for managing window
{
    sf::Texture *m_texture = NULL;
    sf::Sprite *m_sprite = NULL;
    sf::RenderWindow *window = NULL;
    Graph *graph = NULL;
    bool RUNNING = true;

    sf::Rect<float> buttonArea;
    // coordinates of mouse left-click; for creating new vertices
    float mouseX, mouseY;
    bool singleClick = true;
    int mode = -1;

    // vertices needed while drawing edges
    Vertex *vertexA = NULL;
    Vertex *vertexB = NULL;
    Vertex *startVertex = NULL;

    // to set cursor for different modes
    sf::Cursor cursor;

    std::vector<button *> buttons;

    void createButtons();

    inline void renderButtons();

    inline void getMode();

    inline void DRAWINGMODE();
    inline void getStartingVertex();    

};

int main()
{
    try
    {
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8; // for smooth edges of shapes, this depends upon graphics card

        sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Graph Algorithm visualizer", sf::Style::Default, settings);
        Graph *graph = new Graph(window, windowmgr::mode);
        Dijkstra *D = new Dijkstra(window);

        windowmgr::window = window;
        windowmgr::graph = graph;

        // synchronize refresh rate with frquency of monitor
        window->setVerticalSyncEnabled(true);

        // creating buttons required for different modes like edit, del, run...etc
        windowmgr::createButtons();

        while ( window->isOpen() && windowmgr::RUNNING )
        {
            sf::Event event;
            while (window->pollEvent( event ))
            {
                switch (event.type)
                {
                case sf::Event::Closed:
                    window->close(); // closes the window
                    break;

                case sf::Event::Resized:
                {
                    sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
                    window->setView(sf::View( visibleArea ));
                    /* update the view to the new size of the window otherwise when the window is resized,
                    everything is squeezed/stretched to the new size */
                    break;
                }

                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        windowmgr::mouseX = sf::Mouse::getPosition( *window ).x;
                        windowmgr::mouseY = sf::Mouse::getPosition( *window ).y;
                        windowmgr::getMode();

                        switch (windowmgr::mode)
                        {

                        case modes::DIJKSTRAMODE: // run dijkstra
                            if (windowmgr::cursor.loadFromSystem( sf::Cursor::Arrow ))
                                window->setMouseCursor( windowmgr::cursor ); // change cursor to arrow
                            graph->restoreDefault(); // to run dijkstra again, restoring the colors of vertices & edges
                            windowmgr::getStartingVertex();
                            D->run(graph, windowmgr::startVertex);
                            break;

                        case modes::BFSMODE: // run bfs
                            if (windowmgr::cursor.loadFromSystem( sf::Cursor::Arrow ))
                                window->setMouseCursor( windowmgr::cursor );
                            windowmgr::getStartingVertex();
                            graph->restoreDefault(); // to run bfs again, restoring the colors of vertices & edges
                            graph->BFS(windowmgr::startVertex);
                            break;

                        case modes::DFSMODE: // run dfs
                            if (windowmgr::cursor.loadFromSystem( sf::Cursor::Arrow ))
                                window->setMouseCursor(windowmgr::cursor);
                            graph->restoreDefault(); // to run dfs again, restoring the colors of vertices & edges
                            windowmgr::getStartingVertex();
                            graph->DFS(windowmgr::startVertex);
                            break;

                        case modes::KRUSKALMODE: // exiting the whole program in exit mode
                            if (windowmgr::cursor.loadFromSystem( sf::Cursor::Arrow ))
                                window->setMouseCursor( windowmgr::cursor );
                            graph->restoreDefault(); // to run kruskal again, restoring the colors of vertices & edges
                            KRUSKAL::kruskalMST(graph);
                            break;

                        case modes::DRAWINGMODE: // adding vertices and edges in DRAWINGMODE
                            if (windowmgr::cursor.loadFromSystem( sf::Cursor::Cross ))
                                window->setMouseCursor(windowmgr::cursor); // change cursor to Cross
                            windowmgr::DRAWINGMODE();
                            break;

                        case modes::RESTOREMODE: // exiting the whole program in exit mode
                            if (windowmgr::cursor.loadFromSystem( sf::Cursor::NotAllowed ))
                                window->setMouseCursor( windowmgr::cursor );
                            graph->restoreDefault(); // restoring the colors of vertices & edges
                            D->m_start = NULL;
                            break;

                        case modes::DELETEMODE: // deleting vertices and edges in DRAWINGMODE function, it is DELETEMODE though
                            if (windowmgr::cursor.loadFromSystem( sf::Cursor::Hand ))
                                window->setMouseCursor( windowmgr::cursor ); // change cursor to Hand
                            windowmgr::DRAWINGMODE();
                            break;

                        case modes::CLEARMODE: // clearing the graph in cancel mode
                            if (windowmgr::cursor.loadFromSystem( sf::Cursor::NotAllowed ))
                                window->setMouseCursor( windowmgr::cursor ); // change cursor to NotAllowed
                            delete graph;
                            graph = new Graph( window, windowmgr::mode );
                            delete D;
                            D = new Dijkstra( window );
                            windowmgr::graph = graph;
                            break;

                        case modes::EXITMODE: // exiting the whole program in exit mode
                            windowmgr::RUNNING = false;
                            break;
                            
                        default:
                            if (windowmgr::cursor.loadFromSystem(sf::Cursor::Arrow))
                                window->setMouseCursor(windowmgr::cursor);
                            windowmgr::DRAWINGMODE();
                            break;
                        }
                    }

                    else
                    {
                        windowmgr::vertexA = windowmgr::vertexB = NULL; // to clear the vertex buffer
                    }
                    break;

                case sf::Event::KeyPressed:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                    {
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
                        {
                            windowmgr::graph->removeVertex(); // to undo the latest vertex
                            // this can be done in any mode except when running algorithms
                        }
                    }
                    break;

                default:
                    break;
                }
            }

            window->clear( sf::Color(33, 31, 32) );
            window->draw( *windowmgr::m_sprite );

            graph->draw();
            windowmgr::renderButtons();

            window->display();

        }

        if( D )
        {
            delete D;
            D = NULL;
        }
        if( graph )
        {
            delete graph;
            graph = NULL;
        }
        if( window )
        {
            delete window;
            window = NULL;
        }
    }
    catch (std::bad_alloc &ba)
    {
        std::cerr << "Error\n";
    }

    return 0;
}

// definitions of methods inside windowmgr namespace

void windowmgr::createButtons()
{
    m_texture = new sf::Texture;
    if ( !m_texture->loadFromFile("res/background1.jpg") )
    {
        std::cerr << "Texture not loaded ";
    }
    m_sprite = new sf::Sprite;
    m_sprite->setTexture( *m_texture );
    m_sprite->setPosition( sf::Vector2f(SCREEN_WIDTH-250, 0) );
    
    sf::IntRect rect = m_sprite->getTextureRect();
    float X = 250.f/rect.width;
    float Y = static_cast<float> (SCREEN_HEIGHT)/rect.height;
    m_sprite->setScale(X, Y);

    button *drawGraph = new button();
    button *runDijkstra = new button();
    button *kruskal = new button();
    button *bfs = new button();
    button *dfs = new button();
    button *clear = new button();
    button *del = new button();
    button *exit = new button();
    button *restore = new button();

    drawGraph->name = "     Draw";
    del->name = "     Delete";
    runDijkstra->name = "   Dijkstra";
    kruskal->name = "    Kruskal";
    bfs->name = "      BFS";
    dfs->name = "      DFS";
    clear->name = "      Clear";
    exit->name = "       Exit";
    restore->name = "    Restore";

    buttons.push_back(runDijkstra);
    buttons.push_back(bfs);
    buttons.push_back(dfs);
    buttons.push_back(kruskal);
    buttons.push_back(drawGraph);
    buttons.push_back(restore);
    buttons.push_back(del);
    buttons.push_back(clear);
    buttons.push_back(exit);

    sf::Vector2f size(120.f, 30.f);
    sf::Vector2f pos( SCREEN_WIDTH-size.x-65.f, 200.f );
    int i = 0;
    for (button *b : buttons)
    {
        b->createButton(size, pos);
        button::m_modes[b] = i++;
        pos.y += 60;
    }

    /*setting coordinates for generating button area*/
    buttonArea.width = SCREEN_WIDTH - 275.f;
    buttonArea.height = SCREEN_HEIGHT;
    // top left corner coordinates of rectangular button
    buttonArea.left = 0.f;
    buttonArea.top = 0.f;
}

inline void windowmgr::renderButtons()
{
    for (button *b : buttons)
    {
        b->update(window);
        b->draw(window);
    }
}

inline void windowmgr::getMode()
{
    for (auto b : buttons)
    {
        // selecting button
        if (b->buttonArea.contains(mouseX, mouseY))
        {
            mode = button::m_modes[b];
            break;
        }
    }
}

inline void windowmgr::DRAWINGMODE()
{
    mouseX = sf::Mouse::getPosition(*window).x;
    mouseY = sf::Mouse::getPosition(*window).y;

    vertexA = graph->getVertex((sf::Vector2f)sf::Mouse::getPosition(*window));

    // removing vertex is also done in this function, so separated for drawing mode and delete mode
    if (windowmgr::mode == modes::DRAWINGMODE)
    {
        if (!vertexA && buttonArea.contains(mouseX, mouseY)) // if no vertex there, make the vertex
        {
            graph->addVertex(mouseX, mouseY);
            vertexA = graph->getVertex((sf::Vector2f)sf::Mouse::getPosition(*window));
        }

        else if (vertexA && vertexB && vertexA != vertexB) // if both vertex there and not equal, make the edge
            graph->addEdge(vertexA, vertexB);

        else if (vertexA == vertexB) // if both vertex are equal, clean the vertex buffer i.e. nulling vertexA & vertexB
            vertexA = NULL;

        vertexB = vertexA;
        startVertex = vertexB;
        vertexA = NULL; // actually vertexA is being used as second vertex for edge
    }

    else // else represents delete mode because this function is called only for drawing and delete modes
    {
        if (vertexA)
        {
            graph->removeVertex(vertexA); // removes the vertex if present, but only in delete mode
        }
    }
}

inline void windowmgr::getStartingVertex()
{
    startVertex = NULL;
    startVertex = graph->getVertex((sf::Vector2f)sf::Mouse::getPosition(*window));
}