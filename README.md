# Real-Time Chat Application

This is a real-time chat application implemented in C++. The application includes both a server and a client, which can be used to send and receive messages in real-time.

## Deatures
The chat application includes the following features:

- Real-time messaging: Messages are sent and received in real-time.
- Multiple clients: The server can handle multiple clients simultaneously.
- Usernames: Clients can choose a username to identify themselves in the chat.
- Error handling: The application includes error handling to handle common errors, such as socket errors.

## Requirements
To run the chat application, you will need the following:

- A C++ compiler, such as GCC or Clang
- CMake
- A Unix-based operating system (e.g. Linux, macOS)

## Building the Application
To build the chat application, follow these steps:

Clone the repository:

```
git clone git@github.com:lexivanx/rt-chat-server.git
```

Navigate to the project directory:

```
cd rt-chat-server
```

Create a build directory:

```
Copy code
mkdir build
cd build
```

Run CMake to generate the Makefile:

```
cmake ..
```

Build the application:

```
make
```

## Running the Application

To run the chat application, follow these steps:

### Start the server:

```
./server <port>
```

Replace <port> with the port number you want to use for the server (e.g. 8080).

### Start the client:

```
./client <host> <port>
```

Replace <host> with the hostname or IP address of the server, and <port> with the port number used by the server.

### Enter a username:

```
Enter your username:
```

### Send and receive messages:

```
<username>: Hello, world!
```

Messages sent by other clients will appear in the same format.

## License
This project is licensed under the MIT License. See the LICENSE file for more information.