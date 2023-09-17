#include "Planet.h"

using namespace sf;

class Planet
{
    private:
        CircleShape planet;
        double radius;
        double mass;
        Vector2f position;
        Vector2f velocity;
        VertexArray track;
        Color color;
        CircleShape test;

    public:
        Planet(double radius, double mass, Vector2f position, Vector2f velocity, Color color) :
            radius(radius),
            mass(mass),
            position(position - Vector2f(radius, radius)),
            velocity(velocity),
            color(color)             
        {
            test.setRadius(1);
            test.setFillColor(Color::Black);
            test.setPosition(position);
            planet.setRadius(radius);
            planet.setPosition(position - Vector2f(radius, radius));
            planet.setFillColor(color);
        }
        void addTrack(Vertex pos) 
        {
            track.append(pos);
        }
        void clearTrack() 
        {
            track.clear();
        }
        VertexArray getTrack()
        {
            return track;
        }
        double getRadius() 
        {
            return radius;
        }
        double getMass() 
        {
            return mass;
        }
        Vector2f getPosition()
        {
            return position;
        }
        Color getColor() 
        {
            return color;
        }
        void update(Vector2f normDir, float a) 
        {
            velocity -= normDir * a;
            position += velocity;
        }
        void drawTrack(RenderWindow &window) 
        {
            window.draw(track);
        }
        void drawPlanet(RenderWindow &window) 
        {
            
            planet.setPosition(position);
            window.draw(planet);
            window.draw(test);
        }
};
bool frameCollisionX(float x, float radius) 
{
    return (x + radius > 1920 || x - radius < 0);
}
bool frameCollisionY(float y, float radius)
{
    return (y + radius > 1080 || y - radius < 0);
}
float distance(Vector2f vec1, Vector2f vec2) 
{
    float dx = vec1.x - vec2.x;
    float dy = vec1.y - vec2.y;
    return std::sqrt(dx * dx + dy * dy);
}
int main() 
{
    RenderWindow window(VideoMode(1920, 1080), "Gravity");
    std::setlocale(LC_ALL, "rus");
    bool pause = false;
    bool trackDraw = true;
    bool spawnSun = true;
    bool moveSun = false;
    
    Clock clock;
    Clock clock2;

    std::vector<Planet> planets;
    CircleShape test;
    test.setFillColor(Color::Black);
    test.setRadius(1);
    float G = 6.67;
    double scalePhy = (double)2e9;
    double scaleGrap = 1;
    double F = 0;
    double a = 0;
    float rSun = 1;
    CircleShape sun(rSun);
    float sunSpeed = 1.0f;
    Vector2f offset(rSun, rSun);
    double mSun = (double)2e30;
    sun.setFillColor(Color::Yellow);
    sun.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);


    Time timePerFrame = seconds(1.0f / 600); // tps
    Time timePerFrame2 = seconds(1.0f / 60); // fps
    Time accumulatedTime = Time::Zero;
    Time accumulatedTime2 = Time::Zero;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::KeyReleased && event.key.code == Keyboard::Num1)
            {
                planets.push_back(Planet(2, 3.33e23, Vector2f(sun.getPosition().x + rSun + 29/ scaleGrap, sun.getPosition().y + rSun), Vector2f(0, 7.4 / scaleGrap), Color::Color(128, 128, 128)));
                planets.push_back(Planet(5, 4.87e24, Vector2f(sun.getPosition().x + rSun + 54 / scaleGrap, sun.getPosition().y + rSun), Vector2f(0, 5.5 / scaleGrap), Color::Color(234, 205, 177)));
                planets.push_back(Planet(5, 5.97e24, Vector2f(sun.getPosition().x + rSun + 75 / scaleGrap, sun.getPosition().y + rSun), Vector2f(0, 4.7 / scaleGrap), Color::Color(154, 205, 50)));
                planets.push_back(Planet(3, 6.42e23, Vector2f(sun.getPosition().x + rSun + 114 / scaleGrap, sun.getPosition().y + rSun), Vector2f(0, 3.8 / scaleGrap), Color::Color(228, 64, 3)));
                planets.push_back(Planet(57 / scaleGrap, 1.89e27, Vector2f(sun.getPosition().x + rSun + 389 / scaleGrap, sun.getPosition().y + rSun), Vector2f(0, 2 / scaleGrap), Color::Color(255, 226, 183)));
                planets.push_back(Planet(47 / scaleGrap, 5.68e26, Vector2f(sun.getPosition().x + rSun + 700 / scaleGrap, sun.getPosition().y + rSun), Vector2f(0, 1.5 / scaleGrap), Color::Color(255, 219, 139)));
                planets.push_back(Planet(21 / scaleGrap, 8.68e25, Vector2f(sun.getPosition().x + rSun + 1400 / scaleGrap, sun.getPosition().y + rSun), Vector2f(0, 1.1 / scaleGrap), Color::Color(150, 229, 233)));
                planets.push_back(Planet(20 / scaleGrap, 1.024e26, Vector2f(sun.getPosition().x + rSun + 2275 / scaleGrap, sun.getPosition().y + rSun), Vector2f(0, 0.85 / scaleGrap), Color::Color(0, 0, 255)));
                planets.push_back(Planet(2, 1.3e22, Vector2f(sun.getPosition().x + rSun + 2950 / scaleGrap, sun.getPosition().y + rSun), Vector2f(0, 0.75 / scaleGrap), Color::Color(117, 90, 87)));
                planets.push_back(Planet(2, 4.006e21, Vector2f(sun.getPosition().x + rSun + 3225 / scaleGrap, sun.getPosition().y + rSun), Vector2f(0, 0.73 / scaleGrap), Color::Color(128, 128, 128)));
            }
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::T)
            {
                trackDraw = !trackDraw;
                for (int i = 0; i < planets.size(); i++)
                {
                    planets[i].clearTrack();
                }
            }
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Delete)
            {
                mSun = 2e30;
                scalePhy = 2e9;
                scaleGrap = 1;
                planets.clear();
            }
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Space)
            {
                pause = !pause;
            }
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::S) 
            {
                spawnSun = !spawnSun;
            }
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::M)
            {
                moveSun = !moveSun;
            }
            /*
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Numpad6)
            {
                sunSpeed += 1.0f;
            }
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Numpad4)
            {
                sunSpeed -= 1.0f;
            }
            */
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Numpad8)
            {
                planets.clear();
                scalePhy *= 2;
                scaleGrap *= 2;
            }
            
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Numpad2)
            {
                planets.clear();
                scalePhy /= 2;
                scaleGrap /= 2;
            }
            
        }
        accumulatedTime += clock.restart();
        while (accumulatedTime >= timePerFrame) 
        {
            accumulatedTime -= timePerFrame;
            if (!pause)
            {
                if (moveSun) 
                {
                    sun.setPosition(sun.getPosition().x + sunSpeed, sun.getPosition().y);
                    if (frameCollisionX(sun.getPosition().x + rSun, rSun)) 
                    {
                        //sun.setPosition(0, sun.getPosition().y);
                        //sunSpeed = -sunSpeed;
                    }
                }
                for (int i = 0; i < planets.size(); i++)
                {
                    {
                        if (trackDraw)
                        {
                            Vertex pos(Vector2f(planets[i].getPosition().x + planets[i].getRadius(), planets[i].getPosition().y + planets[i].getRadius()));
                            pos.color = planets[i].getColor();
                            planets[i].addTrack(pos);
                        }
                        double distan = distance(sun.getPosition() + offset, planets[i].getPosition() + Vector2f(planets[i].getRadius(), planets[i].getRadius())) * scalePhy;
                        F = (double)G * (mSun * planets[i].getMass()) / pow(distan, 2) * (int)spawnSun;
                        a = (double)F / planets[i].getMass();
                        Vector2f normDir = ((planets[i].getPosition() + Vector2f(planets[i].getRadius(), planets[i].getRadius()) - (sun.getPosition() + offset))) / (float)distan;
                        planets[i].update(normDir, a);
                        //|| frameCollisionX(positions[i].x + radiuses[i], radiuses[i]) || frameCollisionY(positions[i].y + radiuses[i], radiuses[i])
                        
                        if (distan <= planets[i].getRadius() + rSun)
                        {
                            planets.erase(planets.begin() + i);
                        }
                        
                    }
                }
            }
        }
        accumulatedTime2 += clock2.restart();
        if (accumulatedTime2 >= timePerFrame2)
        {
            window.clear(Color::Black);
            for (int i = 0; i < planets.size(); i++)
            {
                {
                    if (planets[i].getTrack().getVertexCount() > 1)
                    {
                        planets[i].drawTrack(window);
                    }
                    planets[i].drawPlanet(window);
                }
            }
            if (spawnSun) 
            {
                test.setPosition(sun.getPosition() + Vector2f(rSun,rSun));
                
                window.draw(sun);
                window.draw(test);
            }
            window.display();
            accumulatedTime2 -= timePerFrame2;
        }
    }
    return 0;
}
