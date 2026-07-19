#include <iostream>

#include <httplib.h>

#include "database/DatabaseConnection.h"
#include "repositories/ChickenRepository.h"
#include "services/ChickenService.h"
#include "controllers/ChickenController.h"

using namespace httplib;
using namespace std;

// Global pointer so the signal handler can stop the server.
Server* g_server = nullptr;

/**
 * Handles Ctrl+C (SIGINT) and SIGTERM.
 * Instead of killing the application immediately,
 * stop the HTTP server gracefully.
 */
void signalHandler(int signal)
{
    std::cout << "\nReceived signal: " << signal << std::endl;

    if (g_server != nullptr)
    {
        std::cout << "Stopping HTTP server..." << std::endl;
        g_server->stop();
    }
}

int main()
{
    DatabaseConnection database("database/nchabi-chickens.db", "database/schema.sql");

    ChickenRepository repository(database);
    ChickenService service(repository);
    ChickenController controller(service);

    Server server;
    // Allow the signal handler to access the server
    g_server = &server;

    // Register Linux signals
    signal(SIGINT, signalHandler);   // Ctrl+C
    signal(SIGTERM, signalHandler);  // Docker / Kubernetes / Azure

    controller.registerRoutes(server);

    std::cout << "Server running on http://localhost:8080" << std::endl;
    std::cout << "Press Ctrl+C to stop the server." << std::endl;

    // Start listening (blocks until server.stop() is called)
    server.listen("0.0.0.0", 8080);

    std::cout << "Application exiting normally." << std::endl;

    return 0;
}