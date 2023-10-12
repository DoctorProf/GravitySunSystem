#include "../Headers/LogicFunc.h"

void lf::logicPlanet(std::vector<Planet> &planets, double &G, double &scalePhy, View &world)
{
    Concurrency::parallel_for(0, (int)planets.size(), [&](int j)
        {
            for (int i = 0; i < planets.size(); i++)
            {
                if (i == j) continue;

                double distan = distance(planets[j].getPosition() + offset(planets[j].getRadius()), planets[i].getPosition() + offset(planets[i].getRadius())) * scalePhy;
                double a = (double)(G * (planets[j].getMass() * planets[i].getMass()) / pow(distan, 2)) / planets[j].getMass();
                planets[j].update(normalizeVector(planets[i], planets[j]), a);
            }
            planets[j].move();
            if (planets[j].getFocus())
            {
                world.setCenter(Vector2f(planets[j].getPosition().x + planets[j].getRadius(), planets[j].getPosition().y + planets[j].getRadius()));
            }
        });
}
void lf::drawButtons(std::vector<Button>& buttons, RenderWindow& window) 
{
    for (int i = 0; i < buttons.size(); i++) 
    {
        buttons[i].draw(window);
    }
}
