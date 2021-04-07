#include <SFML/Graphics.hpp>
#include <TSPsolver.h>
#include <chrono>



int main()
{
    int width = 800;
    int height = 800;
    double scaling = 15;
    double transX = 175;
    double transY = 75;
    sf::RenderWindow window(sf::VideoMode(width, height), "Graph Viewer");

    TSPsolver solver;
    
    solver.parseCSV("short_path.csv");
    
    auto startSolve = std::chrono::system_clock::now();
    
    solver.solve(1,20000);
    auto endSolve = std::chrono::system_clock::now();
    std::cout << "TSP solve time: "<< std::chrono::duration_cast<std::chrono::milliseconds>(endSolve - startSolve).count() << " ms" << std::endl;
    
    std::vector<Point2D> nodes = solver.getNodes();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        
        for (Point2D node: nodes) {
            sf::CircleShape shape(5);
            double tmpX = (node.x * scaling)+width/2+transX;
            double tmpY = (node.y * scaling)+height/2+transY;
            shape.setPosition(tmpX, tmpY);
            shape.setFillColor(sf::Color::Yellow);
            window.draw(shape);
        }

        for (int i = 0; i < nodes.size(); ++i) {
            sf::Vertex line[2];
            
            double tmpX1 = (nodes.at(i).x * scaling)+width/2+transX + 5;
            double tmpY1 = (nodes.at(i).y * scaling)+height/2+transY + 5;

            double tmpX2,tmpY2;
            if (i == nodes.size()-1) {
                tmpX2 = (nodes.at(0).x * scaling)+width/2+transX + 5;
                tmpY2 = (nodes.at(0).y * scaling)+height/2+transY + 5;
            } else {
                tmpX2 = (nodes.at(i+1).x * scaling)+width/2+transX + 5;
                tmpY2 = (nodes.at(i+1).y * scaling)+height/2+transY + 5;
            }

            line[0].position = sf::Vector2f(tmpX1, tmpY1);
            line[0].color  = sf::Color::Yellow;
            line[1].position = sf::Vector2f(tmpX2, tmpY2);
            line[1].color = sf::Color::Yellow;
            window.draw(line, 2, sf::Lines);
        }

        window.display();
    }
    
    return 0;
}