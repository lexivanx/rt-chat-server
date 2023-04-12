#include "ChatServer.h"

int main() {
    unsigned short port = 3000; // Choose an appropriate port
    ChatServer server(port);

    server.start();

    return 0;
}
