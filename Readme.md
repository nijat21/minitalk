# Minitalk

Minitalk is a simple client-server communication program using UNIX signals (`SIGUSR1` and `SIGUSR2`). The client sends a string message to the server, which reconstructs and prints it.

## Features

- Sends messages from client to server using signals
- Handles variable-length messages
- Implements bonus features with additional clients and servers
- Converts characters into binary and transmits them bit by bit
- Uses signal handling to reconstruct and display messages on the server

## Functionality

1. The server starts and prints its PID.
2. The client retrieves the server's PID and sends the message by converting each character into binary and transmitting it bit by bit using `SIGUSR1` (0) and `SIGUSR2` (1).
3. The server receives signals, reconstructs the message, and prints it once fully received.
4. The program ensures smooth transmission using `usleep` to control signal timing.

## Compilation

```sh
make
```

This compiles both `client` and `server` along with bonus versions.

## Usage

Start the server:

```sh
./server
```

Send a message from the client:

```sh
./client <PID> "Your message here"
```

Where `<PID>` is the process ID of the running server.

## Cleanup

To remove compiled files:

```sh
make clean
```

To remove binaries:

```sh
make fclean
```

To recompile everything:

```sh
make re
```
