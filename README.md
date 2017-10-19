# Client/Server Hangman in C using Socket Programming
A client/server implementation of the game of Hangman, a word guessing game.

In the game of Hangman the server randomly selects a two-word phrase from a given text file. The client and server will be implemented in the C programming language using BSD sockets on the Linux operating system.

One potential problem that you must be handled in this multithreaded programming task is a so-called Critical-Section Problem because the Leaderboard is a database that may be shared among multiple concurrent connections, each of which may read or update the database.

# Authors
* [Megan Hunter](https://github.com/Nyx-), N1234567
* [Jesse Stanger](https://github.com/stangahh), N9162259

# How to Build
Navigate to root of project and run:
```
make
```

# How to Run
Navigate to ```/bin``` and in one console window, run:
```
./server <port number>
```

then in another console window, run:
```
./client <server IP address> <server port number>
```
