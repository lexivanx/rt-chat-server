#include "ChatClient.h"

int main() {
    std::string host = "127.0.0.1"; // Use an appropriate server address
    unsigned short port = 3000; // Choose the same port as the server

    ChatClient client(host, port);

    client.start();

    return 0;
}
