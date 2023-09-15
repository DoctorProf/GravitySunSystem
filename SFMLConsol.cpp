#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <string>

using namespace sf;

bool frameCollisionX(double x, int radius) {
    return (x + radius > 1920 || x - radius < 0);
}

bool frameCollisionY(double y, int radius) {
    return (y + radius > 1080 || y - radius < 0);
}

double distance(Vector2f vec1, Vector2f vec2) {
    double dx = vec1.x - vec2.x;
    double dy = vec1.y - vec2.y;
    return std::sqrt(dx * dx + dy * dy);
}
void spawnPlanet(double radius, double mass, Vector2f velocity, Vector2f position, std::vector<CircleShape>& circleVec,
    std::vector<Vector2f>& velocities, std::vector<Vector2f>& positions, std::vector<double>& masses,
    std::vector<int>& radiuses, std::vector<std::vector<Vector2f>> &circleTrack, Color color)
    {
    
    CircleShape circle(radius);
    circle.setFillColor(color);
    std::vector<Vector2f> circTrack;
    circleVec.push_back(circle);
    velocities.push_back(velocity);
    positions.push_back(position);
    radiuses.push_back(radius);
    masses.push_back(mass);
    circleTrack.push_back(circTrack);
}

int main() {
    std::setlocale(LC_ALL, "rus");
    bool pause = false;
    bool trackDraw = true;
    bool spawnSun = true;
    bool moveSun = true;
    RenderWindow window(VideoMode(1920, 1080), "Gravity");
    Clock clock;
    Clock clock2;
    Clock clock3;
    std::vector<CircleShape> circleVec;
    std::vector<Vector2f> velocities;
    std::vector<Vector2f> positions;
    std::vector<double> masses;
    std::vector<int> radiuses;
    std::vector<std::vector<Vector2f>> circleTrack;
    double G = 6.67;
    double scale = (double)2e9;
    double low = 100;
    double rSun = 7;
    double F = 0;
    double a = 0;;
    sf::Vertex track;
    track.color = Color::Red;
    CircleShape sun(rSun);
    double sunSpeed = 1.0f;
    Vector2f offset(rSun, rSun);
    double mSun = 2e30;
    sun.setFillColor(Color::Yellow);
    sun.setPosition(window.getSize().x / 2, window.getSize().y / 2);


    Time timePerFrame = seconds(1.0f / 60); // lps
    Time timePerFrame2 = seconds(1.0f / 60); // fps
    Time accumulatedTime = Time::Zero;
    Time accumulatedTime2 = Time::Zero;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            
            if (event.type == Event::KeyReleased && event.key.code == Keyboard::Num1) {
                
                spawnPlanet(5, 3.33e23, Vector2f(0, 7.8), Vector2f(sun.getPosition().x + 29, sun.getPosition().y), std::ref(circleVec), std::ref(velocities),
                    std::ref(positions), std::ref(masses), std::ref(radiuses), std::ref(circleTrack), Color::Color(128,128,128));
                
                spawnPlanet(5, 4.87e24, Vector2f(0,5.8), Vector2f(sun.getPosition().x + 54, sun.getPosition().y), std::ref(circleVec), std::ref(velocities),
                    std::ref(positions), std::ref(masses), std::ref(radiuses), std::ref(circleTrack), Color::Color(234, 205, 177));
                
                spawnPlanet(5, 5.97e24, Vector2f(0, 5), Vector2f(sun.getPosition().x + 75, sun.getPosition().y), std::ref(circleVec), std::ref(velocities),
                    std::ref(positions), std::ref(masses), std::ref(radiuses), std::ref(circleTrack), Color::Color(154, 205, 50));
                
                spawnPlanet(5, 6.42e23, Vector2f(0, 4), Vector2f(sun.getPosition().x + 114, sun.getPosition().y), std::ref(circleVec), std::ref(velocities),
                    std::ref(positions), std::ref(masses), std::ref(radiuses), std::ref(circleTrack), Color::Color(228, 64, 3));
                
                spawnPlanet(5, 1.89e27, Vector2f(0, 1.8), Vector2f(sun.getPosition().x + 389, sun.getPosition().y), std::ref(circleVec), std::ref(velocities),
                    std::ref(positions), std::ref(masses), std::ref(radiuses), std::ref(circleTrack), Color::Color(255, 226, 183));
                
                
                spawnPlanet(5, 5.68e26, Vector2f(0, 1.4), Vector2f(sun.getPosition().x + 700, sun.getPosition().y), std::ref(circleVec), std::ref(velocities),
                    std::ref(positions), std::ref(masses), std::ref(radiuses), std::ref(circleTrack), Color::Color(255, 219, 139));
                
                spawnPlanet(5, 8.68e25, Vector2f(0, 1), Vector2f(sun.getPosition().x + 1400, sun.getPosition().y), std::ref(circleVec), std::ref(velocities),
                    std::ref(positions), std::ref(masses), std::ref(radiuses), std::ref(circleTrack), Color::Color(150,229,233));
                   
                 
            } else if (event.type == Event::KeyReleased && event.key.code == Keyboard::T)
            {
                trackDraw = !trackDraw;
                for (int i = 0; i < circleVec.size(); i++) {
                    circleTrack[i].clear();
                }
            } else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Delete)
            {
                for (int i = 0; i < circleVec.size(); i++) {
                    circleVec.clear();
                    circleTrack.clear();
                    masses.clear();
                    positions.clear();
                    velocities.clear();
                    radiuses.clear();
                }
            } else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Space) {
                
                pause = !pause;
            }
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::S) {
                spawnSun = !spawnSun;
            }
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::M) {
                moveSun = !moveSun;
            }
        }
        
        
        accumulatedTime += clock.restart();
        while (accumulatedTime >= timePerFrame) {
            accumulatedTime -= timePerFrame;
            
            if (!pause) {
                if (moveSun) {
                    sun.setPosition(sun.getPosition().x + sunSpeed, sun.getPosition().y);
                    if (frameCollisionX(sun.getPosition().x + rSun, rSun)) {
                        //sun.setPosition(0, sun.getPosition().y);
                        sunSpeed = -sunSpeed;
                    }
                }
                for (int i = 0; i < circleVec.size(); i++) {
                    if (trackDraw) {
                        Vector2f pos(positions[i].x + radiuses[i], positions[i].y + radiuses[i]);
                        circleTrack[i].push_back(pos);
                    }
                    
                    double distan = distance(sun.getPosition() + offset, positions[i] + Vector2f(radiuses[i], radiuses[i])) * scale;
                    Vector2f normalizeDirection;
                    F = G * (mSun * masses[i]) / pow(distan, 2) * (int)spawnSun;
                    a = F / masses[i];
                    normalizeDirection = ((positions[i] + Vector2f(radiuses[i], radiuses[i])) - (sun.getPosition() + offset)) / (float)distan;
                    velocities[i] -= normalizeDirection * static_cast<float>(a);
                    positions[i] += velocities[i];
                    //|| frameCollisionX(positions[i].x + radiuses[i], radiuses[i]) || frameCollisionY(positions[i].y + radiuses[i], radiuses[i])
                    if (distan <= radiuses[i] + rSun) {
                        circleVec.erase(circleVec.begin() + i);
                        positions.erase(positions.begin() + i);
                        radiuses.erase(radiuses.begin() + i);
                        masses.erase(masses.begin() + i);
                        velocities.erase(velocities.begin() + i);
                        circleTrack.erase(circleTrack.begin() + i);
                    }
                    /*
                    for (int i = 0; i < circleVec.size() - 1; i++) {
                        if (distance(positions[i] + Vector2f(radiuses[i], radiuses[i]), positions[i + 1] + Vector2f(radiuses[i + 1], radiuses[i + 1])) <= (radiuses[i] + radiuses[i + 1])) {
                            circleVec.erase(circleVec.begin() + i + 1);
                            positions.erase(positions.begin() + i + 1);
                            radiuses.erase(radiuses.begin() + i + 1);
                            masses.erase(masses.begin() + i + 1);
                            velocities.erase(velocities.begin() + i + 1);
                            circleTrack.erase(circleTrack.begin() + i + 1);
                            circleVec.erase(circleVec.begin() + i);
                            positions.erase(positions.begin() + i);
                            radiuses.erase(radiuses.begin() + i);
                            masses.erase(masses.begin() + i);
                            velocities.erase(velocities.begin() + i);
                            circleTrack.erase(circleTrack.begin() + i);
                        }
                    }
                    */
                }
            }
        } 
        
        std::cout << "///" << circleVec.size() << "\n";
        // Отрисовка с учетом интерполяции
        accumulatedTime2 += clock2.restart();
        if (accumulatedTime2 >= timePerFrame2) {
            window.clear(Color::Black);
            for (int i = 0; i < circleVec.size(); i++) {
                for (int j = 0; j < circleTrack[i].size(); j++) {
                    track.color = circleVec[i].getFillColor();
                    track.position = circleTrack[i][j];
                    window.draw(&track, 1, Points);
                }
                circleVec[i].setPosition(positions[i]);
                window.draw(circleVec[i]);
            }
            if (spawnSun) {
                window.draw(sun);
            }
            window.display();
            accumulatedTime2 -= timePerFrame2;
        }
    }

    return 0;
}
