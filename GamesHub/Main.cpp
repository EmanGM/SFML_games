#include <SFML/Graphics.hpp>
#define NOMINMMAX

#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <string>

void create_process(std::wstring path) {

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

void create_hub() {
    sf::RenderWindow window(sf::VideoMode(400, 400), "Games Hub");

    while (window.isOpen()) {
        
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.display();
    }
}

int main() {

	std::cout << "Here\n";
    create_hub();
#ifdef _WIN32
    std::wstring path(L"../Release/Snake_Game.exe");
    create_process(path);
#else
    std::cout << "No support for your operative system";
#endif // _WIN32

}