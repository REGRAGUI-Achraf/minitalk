# Minitalk

## Description

Minitalk is a client-server communication project using UNIX signals (`SIGUSR1` and `SIGUSR2`). The goal is to transmit a string from the client to the server using only these two signals.

## How It Works

### Principle

The project is based on inter-process communication (IPC) via UNIX signals:
- **SIGUSR1**: represents bit `1`
- **SIGUSR2**: represents bit `0`

The client sends each character of the message bit by bit to the server. The server reconstructs the characters from the received bits and displays the complete message.

### Algorithm

#### Server ([server.c](server.c))
1. Starts and displays its PID (Process ID)
2. Configures handlers for `SIGUSR1` and `SIGUSR2`
3. Waits for signals in an infinite loop
4. For each signal received:
   - Shifts the current character one bit to the left
   - If it's `SIGUSR1`, sets the bit to 1 (otherwise it stays 0)
   - After 8 bits received, displays the character and resets

#### Client ([client.c](client.c))
1. Receives as parameters the server PID and the message to send
2. For each character of the message:
   - Sends the 8 bits of the character, from most significant to least significant
   - Uses `SIGUSR1` for a 1 bit, `SIGUSR2` for a 0 bit
   - Waits 500 microseconds between each signal to give the server time to process

## Compilation

### Mandatory version
```bash
make
```
Compiles the `client` and `server` programs.

### Bonus version
```bash
make bonus
```
Compiles the `client_bonus` and `server_bonus` programs.

### Other commands
```bash
make clean    # Removes object files (.o)
make fclean   # Removes object files and executables
make re       # Recompiles everything from scratch
```

## Usage

### 1. Start the server
```bash
./server
```
The server will display its PID:
```
Server PID: 12345
```

### 2. Send a message from the client
```bash
./client [SERVER_PID] "Your message"
```

### Complete example
Terminal 1 (server):
```bash
./server
Server PID: 12345
```

Terminal 2 (client):
```bash
./client 12345 "Hello World!"
```

Terminal 1 (server) will display:
```
Server PID: 12345
Hello World!
```

## Technical Details

### Bit-by-bit conversion
Each character is encoded on 8 bits (ASCII). For example, the character 'A' (65 in decimal):
- Binary: `01000001`
- The client sends: SIGUSR2, SIGUSR1, SIGUSR2, SIGUSR2, SIGUSR2, SIGUSR2, SIGUSR2, SIGUSR1

### Signal handling
- Signals are asynchronous and non-blocking
- The 500 microsecond delay (usleep) prevents signal loss
- The server uses static variables to maintain state between handler calls

### Limitations
- No error handling if the PID is invalid
- No acknowledgment of reception (in the mandatory version)
- Unidirectional communication (client → server)

## Project Structure

```
.
├── client.c           # Mandatory client
├── server.c           # Mandatory server
├── client_bonus.c     # Bonus client
├── server_bonus.c     # Bonus server
├── minitalk.h         # Header with necessary includes
├── Makefile           # Compilation file
└── README.md          # This file
```

## Prerequisites

- GCC compiler
- UNIX/Linux operating system
- Make

## Author

aregragu