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

    public:
        Planet(double radius, double mass, Vector2f position, Vector2f velocity, Color color) :
            radius(radius),
            mass(mass),
            position(position - Vector2f(radius, radius)),
            velocity(velocity),
            color(color)             
        {
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
void PhyPlanet(std::vector<Planet> &planets, Planet sun , bool trackDraw, double G, double scalePhy) 
{
    for (int i = 0; i < planets.size(); i++)
    {
        {
            if (trackDraw)
            {
                Vertex pos(Vector2f(planets[i].getPosition().x + planets[i].getRadius(), planets[i].getPosition().y + planets[i].getRadius()));
                pos.color = planets[i].getColor();
                planets[i].addTrack(pos);
            }
            double F = 0;
            double a = 0;
            double distan = distance(sun.getPosition() + Vector2f(sun.getRadius(), sun.getRadius()), planets[i].getPosition() + Vector2f(planets[i].getRadius(), planets[i].getRadius())) * scalePhy;
            F = (double)G * (sun.getMass() * planets[i].getMass()) / pow(distan, 2);
            a = (double)F / planets[i].getMass();
            Vector2f normDir = ((planets[i].getPosition() + Vector2f(planets[i].getRadius(), planets[i].getRadius()) - (sun.getPosition() + Vector2f(sun.getRadius(), sun.getRadius())))) / (float)distan;
            planets[i].update(normDir, a);
        }
    }
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
    std::vector<Planet> moonEarth;
    std::vector<Planet> moonJupiter;
    std::vector<Planet> moonSaturn;
    std::vector<Planet> moonUran;
    float G = 6.67e-2;
    double scalePhy = (double)2e9;
    double scaleJupiterSaturn = (double)2e8;
    double scaleMoon = 2e7;
    double scaleGrap = 1;
    double F = 0;
    double a = 0;
    float rSun = 2;
    CircleShape sun(rSun);
    float sunSpeed = 0.1f;
    Vector2f offset(rSun, rSun);
    double mSun = (double)2e30;
    sun.setFillColor(Color::Yellow);
    sun.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);


    Time timePerFrame = seconds(1.0f / 120); // tps
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
                planets.push_back(Planet(3 / scaleGrap, 3.33e23, Vector2f(sun.getPosition().x + rSun + 29/ scaleGrap, sun.getPosition().y + rSun), Vector2f(0, 0.76 / scaleGrap), Color::Color(128, 128, 128)));
                planets.push_back(Planet(5 / scaleGrap, 4.87e24, Vector2f(sun.getPosition().x + rSun + 54 / scaleGrap, sun.getPosition().y + rSun), Vector2f(0, 0.555 / scaleGrap), Color::Color(234, 205, 177)));
                planets.push_back(Planet(5 / scaleGrap, 5.97e24, Vector2f(sun.getPosition().x + rSun + 75 / scaleGrap, sun.getPosition().y + rSun), Vector2f(0, 0.47 / scaleGrap), Color::Color(154, 205, 50)));
                planets.push_back(Planet(4 / scaleGrap, 6.42e23, Vector2f(sun.getPosition().x + rSun + 114 / scaleGrap, sun.getPosition().y + rSun), Vector2f(0, 0.38 / scaleGrap), Color::Color(228, 64, 3)));
                planets.push_back(Planet(14 / scaleGrap, 1.89e27, Vector2f(sun.getPosition().x + rSun + 389 / scaleGrap, sun.getPosition().y + rSun), Vector2f(0, 0.205 / scaleGrap), Color::Color(255, 226, 183)));
                planets.push_back(Planet(12 / scaleGrap, 5.68e26, Vector2f(sun.getPosition().x + rSun + 700 / scaleGrap, sun.getPosition().y + rSun), Vector2f(0, 0.155 / scaleGrap), Color::Color(255, 219, 139)));
                planets.push_back(Planet(10 / scaleGrap, 8.68e25, Vector2f(sun.getPosition().x + rSun + 1400 / scaleGrap, sun.getPosition().y + rSun), Vector2f(0, 0.108 / scaleGrap), Color::Color(150, 229, 233)));
                planets.push_back(Planet(10 / scaleGrap, 1.024e26, Vector2f(sun.getPosition().x + rSun + 2275 / scaleGrap, sun.getPosition().y + rSun), Vector2f(0, 0.085 / scaleGrap), Color::Color(0, 0, 255)));
                //planets.push_back(Planet(2, 1.3e22, Vector2f(sun.getPosition().x + rSun + 2950 / scaleGrap, sun.getPosition().y + rSun), Vector2f(0, 0.07 / scaleGrap), Color::Color(117, 90, 87)));
                //planets.push_back(Planet(2, 4.006e21, Vector2f(sun.getPosition().x + rSun + 3225 / scaleGrap, sun.getPosition().y + rSun), Vector2f(0, 0.067 / scaleGrap), Color::Color(128, 128, 128)));
                moonEarth.push_back(Planet(2 / scaleGrap, 7.35e22, Vector2f(planets[2].getPosition().x + planets[2].getRadius() + 19 / scaleGrap, planets[2].getPosition().y + planets[2].getRadius()), Vector2f(0, 1.8 / scaleGrap), Color::Color(210, 210, 210)));
                //Луна
                moonJupiter.push_back(Planet(4 / scaleGrap, 4.80e22, Vector2f(planets[4].getPosition().x + planets[4].getRadius() + 33 / scaleGrap, planets[4].getPosition().y + planets[4].getRadius()), Vector2f(0, 0.9 / scaleGrap), Color::Color(232, 223, 214)));
                //Европа
                moonJupiter.push_back(Planet(4 / scaleGrap, 1.48e23, Vector2f(planets[4].getPosition().x + planets[4].getRadius() + 53 / scaleGrap, planets[4].getPosition().y + planets[4].getRadius()), Vector2f(0, 0.7 / scaleGrap), Color::Color(255, 0, 0)));
                //Ганимед
                moonSaturn.push_back(Planet(4 / scaleGrap, 1.08e20, Vector2f(planets[5].getPosition().x + planets[5].getRadius() + 24 / scaleGrap, planets[5].getPosition().y + planets[5].getRadius()), Vector2f(0, 0.6 / scaleGrap), Color::Color(255, 255, 255)));
                //Энцелад
                moonUran.push_back(Planet(4 / scaleGrap, 6.59e19, Vector2f(planets[6].getPosition().x + planets[5].getRadius() + 13 / scaleGrap, planets[5].getPosition().y + planets[5].getRadius()), Vector2f(0, 0.35 / scaleGrap), Color::Color(194, 178, 128)));
                //Миранда

            }
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::T)
            {
                trackDraw = !trackDraw;
                for (int i = 0; i < planets.size(); i++)
                {
                    planets[i].clearTrack();
                    for (int j = 0; j < moonJupiter.size(); j++) 
                    {
                        moonJupiter[j].clearTrack();
                    }
                    for (int j = 0; j < moonEarth.size(); j++)
                    {
                        moonEarth[j].clearTrack();
                    }
                    for (int j = 0; j < moonSaturn.size(); j++)
                    {
                        moonSaturn[j].clearTrack();
                    }
                    for (int j = 0; j < moonUran.size(); j++)
                    {
                        moonUran[j].clearTrack();
                    }
                }
            }
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Delete)
            {
                mSun = 2e30;
                rSun = 4;
                sun.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
                planets.clear();
                moonJupiter.clear();
                moonEarth.clear();
                moonSaturn.clear();
                moonUran.clear();
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
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Numpad8)
            {
                planets.clear();
                moonJupiter.clear();
                moonEarth.clear();
                moonSaturn.clear();
                moonUran.clear();
                scalePhy *= 2;
                scaleJupiterSaturn *= 2;
                scaleMoon *= 2;
                scaleGrap *= 2;
            }
            
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Numpad2)
            {
                planets.clear();
                moonJupiter.clear();
                moonEarth.clear();
                moonSaturn.clear();
                moonUran.clear();
                scalePhy /= 2;
                scaleMoon /= 2;
                scaleGrap /= 2;
                scaleJupiterSaturn /= 2;
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
                    sun.setPosition(sun.getPosition().x + sunSpeed / scaleGrap, sun.getPosition().y);
                    if (frameCollisionX(sun.getPosition().x + rSun, rSun)) 
                    {
                        //sun.setPosition(0, sun.getPosition().y);
                        sunSpeed = -sunSpeed;
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
                    }
                }
                if(planets.size() > 0 && moonJupiter.size() > 0)
                    PhyPlanet(std::ref(moonJupiter), planets[4], trackDraw, G, scaleJupiterSaturn);
                if(planets.size() > 0 && moonEarth.size() > 0)
                    PhyPlanet(std::ref(moonEarth), planets[2], trackDraw, G, scaleMoon);
                if (planets.size() > 0 && moonSaturn.size() > 0)
                    PhyPlanet(std::ref(moonSaturn), planets[5], trackDraw, G, scaleJupiterSaturn);
                if (planets.size() > 0 && moonUran.size() > 0)
                    PhyPlanet(std::ref(moonUran), planets[6], trackDraw, G, scaleJupiterSaturn);
            }
        }
        accumulatedTime2 += clock2.restart();
        if (accumulatedTime2 >= timePerFrame2)
        {
            window.clear(Color::Black);
            
            for(int i = 0; i < moonJupiter.size(); i++)
            {
                if (moonJupiter[i].getTrack().getVertexCount() > 1)
                {
                    moonJupiter[i].drawTrack(window);
                }
                moonJupiter[i].drawPlanet(window);
            }
            for (int i = 0; i < moonEarth.size(); i++)
            {
                if (moonEarth[i].getTrack().getVertexCount() > 1)
                {
                    moonEarth[i].drawTrack(window);
                }
                moonEarth[i].drawPlanet(window);
            }
            for (int i = 0; i < moonSaturn.size(); i++)
            {
                if (moonSaturn[i].getTrack().getVertexCount() > 1)
                {
                    moonSaturn[i].drawTrack(window);
                }
                moonSaturn[i].drawPlanet(window);
            }
            for (int i = 0; i < moonUran.size(); i++)
            {
                if (moonUran[i].getTrack().getVertexCount() > 1)
                {
                    moonUran[i].drawTrack(window);
                }
                moonUran[i].drawPlanet(window);
            }
            for (int i = 0; i < planets.size(); i++)
            {
                if (planets[i].getTrack().getVertexCount() > 1)
                {
                    planets[i].drawTrack(window);
                }
                planets[i].drawPlanet(window);

            }
            if (spawnSun) 
            {
                
                window.draw(sun);
                
            }
            window.display();
            accumulatedTime2 -= timePerFrame2;
        }
    }
    return 0;
}
