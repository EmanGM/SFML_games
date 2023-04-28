#include <SFML/Graphics.hpp>
#define NOMINMMAX

#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <string>
#include "Button.h"

void create_process_windows(std::wstring path) {

    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Start the child process. 
    if (!CreateProcess(NULL,   // No module name (use command line)
        &path[0],            // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi)           // Pointer to PROCESS_INFORMATION structure
        )
    {
        printf("CreateProcess failed (%d).\n", GetLastError());
        return;
    }

    // Wait until child process exits.
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close process and thread handles. 
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

void create_process_unix() {

}

void open_game(const std::string& game_name) {

#ifdef _WIN32
    std::string name = "../Release/";
    name += game_name + ".exe";
    std::wstring path(name.begin(), name.end());
    create_process_windows(path);
#else
    std::cout << "No support for your operative system";
    create_process_unix();
#endif // _WIN32
}

void create_hub() {
    sf::RenderWindow window(sf::VideoMode(360, 460), "Games Hub");

    Button snake_b(sf::Vector2f(30.0f, 50.0f), "snake");
    Button asteroids_b(sf::Vector2f(30.0f, 110.0f), "asteroids");
    Button arkanoid_b(sf::Vector2f(30.0f, 170.0f), "arkanoid");
    Button tetris_b(sf::Vector2f(30.0f, 240.0f), "tetris");
    Button flappy_b(sf::Vector2f(30.0f, 300.0f), "flappy");
    while (window.isOpen()) {
        
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                if (snake_b.checkButtonClicked(mouse_pos)) {
                    open_game("Snake_Game");
                }
            }
        }

        window.clear(sf::Color::Blue);
        snake_b.draw(window);
        asteroids_b.draw(window);
        arkanoid_b.draw(window);
        tetris_b.draw(window);
        flappy_b.draw(window);
        window.display();
    }
}

int main() {
    create_hub();
}