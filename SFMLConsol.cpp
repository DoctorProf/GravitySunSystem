#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <string>

using namespace sf;

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
void spawnPlanet(float radius, double mass, Vector2f velocity, Vector2f position, std::vector<CircleShape>& circleVec,
    std::vector<Vector2f>& velocities, std::vector<Vector2f>& positions, std::vector<double>& masses,
    std::vector<float>& radiuses, std::vector<VertexArray> &circleTrack, Color color)
    {
    
    CircleShape circle(radius);
    circle.setFillColor(color);
    circleVec.push_back(circle);
    velocities.push_back(velocity);
    positions.push_back(Vector2f(position.x - radius, position.y - radius));
    radiuses.push_back(radius);
    masses.push_back(mass);
    circleTrack.push_back(VertexArray(Lines));
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

    std::vector<CircleShape> circleVec;
    std::vector<Vector2f> velocities;
    std::vector<Vector2f> positions;
    std::vector<double> masses;
    std::vector<float> radiuses;
    std::vector<VertexArray> circleTrack;

    float G = 6.67;
    float scale = (float)2e9;
    float low = 100;
    float F = 0;
    float a = 0;
    float rSun = 7;
    CircleShape sun(rSun);
    float sunSpeed = 1.0f;
    Vector2f offset(rSun, rSun);
    float mSun = (float)2e30;
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
                spawnPlanet(5, 3.33e23, Vector2f(0, 7.4), Vector2f(sun.getPosition().x + rSun + 29, sun.getPosition().y + rSun), std::ref(circleVec), std::ref(velocities),
                    std::ref(positions), std::ref(masses), std::ref(radiuses), std::ref(circleTrack), Color::Color(128, 128, 128));
                
                spawnPlanet(5, 4.87e24, Vector2f(0, 5.5), Vector2f(sun.getPosition().x + rSun + 54, sun.getPosition().y + rSun), std::ref(circleVec), std::ref(velocities),
                    std::ref(positions), std::ref(masses), std::ref(radiuses), std::ref(circleTrack), Color::Color(234, 205, 177));

                spawnPlanet(5, 5.97e24, Vector2f(0, 4.7), Vector2f(sun.getPosition().x + rSun + 75, sun.getPosition().y + rSun), std::ref(circleVec), std::ref(velocities),
                    std::ref(positions), std::ref(masses), std::ref(radiuses), std::ref(circleTrack), Color::Color(154, 205, 50));

                spawnPlanet(5, 6.42e23, Vector2f(0, 3.8), Vector2f(sun.getPosition().x + rSun + 114, sun.getPosition().y + rSun), std::ref(circleVec), std::ref(velocities),
                    std::ref(positions), std::ref(masses), std::ref(radiuses), std::ref(circleTrack), Color::Color(228, 64, 3));

                spawnPlanet(5, 1.89e27, Vector2f(0, 2), Vector2f(sun.getPosition().x + rSun + 389, sun.getPosition().y + rSun), std::ref(circleVec), std::ref(velocities),
                    std::ref(positions), std::ref(masses), std::ref(radiuses), std::ref(circleTrack), Color::Color(255, 226, 183));

                spawnPlanet(5, 5.68e26, Vector2f(0, 1.5), Vector2f(sun.getPosition().x + rSun + 700, sun.getPosition().y + rSun), std::ref(circleVec), std::ref(velocities),
                    std::ref(positions), std::ref(masses), std::ref(radiuses), std::ref(circleTrack), Color::Color(255, 219, 139));

                spawnPlanet(5, 8.68e25, Vector2f(0, 1.1), Vector2f(sun.getPosition().x + rSun + 1400, sun.getPosition().y + rSun), std::ref(circleVec), std::ref(velocities),
                    std::ref(positions), std::ref(masses), std::ref(radiuses), std::ref(circleTrack), Color::Color(150, 229, 233));
            }
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Num5)
            {

            }
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::T)
            {
                trackDraw = !trackDraw;
                for (int i = 0; i < circleVec.size(); i++) 
                {
                    circleTrack[i].clear();
                }
            }
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Delete)
            {
                for (int i = 0; i < circleVec.size(); i++)
                {
                    circleVec.clear();
                    circleTrack.clear();
                    masses.clear();
                    positions.clear();
                    velocities.clear();
                    radiuses.clear();
                }
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
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::H)
            {
                sunSpeed += 1.0f;
            }
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::L)
            {
                sunSpeed -= 1.0f;
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
                        sunSpeed = -sunSpeed;
                    }
                }
                for (int i = 0; i < circleVec.size(); i++) 
                {
                    if (trackDraw) 
                    {
                        Vertex pos(Vector2f(positions[i].x + (float)radiuses[i], (float)positions[i].y + (float)radiuses[i]));
                        pos.color = circleVec[i].getFillColor();
                        circleTrack[i].append(pos);
                    }

                    float distan = distance(sun.getPosition() + offset, positions[i] + Vector2f(radiuses[i], radiuses[i])) * scale;
                    F = G * (mSun * masses[i]) / pow(distan, 2) * (int)spawnSun;
                        a = F / masses[i];
                    Vector2f normalizeDirection = ((positions[i] + Vector2f(radiuses[i], radiuses[i])) - (sun.getPosition() + offset)) / (float)distan;
                    velocities[i] -= normalizeDirection * a;
                    positions[i] += velocities[i];
                    //|| frameCollisionX(positions[i].x + radiuses[i], radiuses[i]) || frameCollisionY(positions[i].y + radiuses[i], radiuses[i])
                    if (distan <= radiuses[i] + rSun) 
                    {
                        circleVec.erase(circleVec.begin() + i);
                        positions.erase(positions.begin() + i);
                        radiuses.erase(radiuses.begin() + i);
                        masses.erase(masses.begin() + i);
                        velocities.erase(velocities.begin() + i);
                        circleTrack.erase(circleTrack.begin() + i);
                    }   
                }
            }
        }
        accumulatedTime2 += clock2.restart();
        if (accumulatedTime2 >= timePerFrame2)
        {
            window.clear(Color::Black);
            for (int i = 0; i < circleVec.size(); i++)
            {
                if (circleTrack[i].getVertexCount() > 1) 
                {
                    window.draw(circleTrack[i]);
                }
                circleVec[i].setPosition(positions[i]);
                window.draw(circleVec[i]);
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
