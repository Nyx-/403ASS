# Report
## Statement of completeness
### Task 1
* [y]     Server command line parameter – configurable port & default port
* [y]     Server authenticates client using data in “Authentication.txt” file
* [y]     Server loads & tokenises “hangman_text.txt” file correctly
* [y]     Server randomly selects a two-word phrase
* [ ]     Server updates Leader Board when a client finishes playing a Hangman game
* [y]     Server exits gracefully upon receiving SIGNAL (ctrl + c)
* [y]     Client command line parameters
* [y]     Client menu implementation
* [ ]     Client plays Hangman as per assignment specifications when user selects “Play Hangman”
* [ ]     Client displays leader board as per assignment specifications when user selects option “Show Leader Board”
* [y]     Client exits gracefully when user selects “Quit” option from menu
* [y]     Description of the data structure that is used for the Leader Board in your report

### Task 2
Incomplete

### Task 3
Incomplete

## Statement of Team Contribution
Megan Hunter contribution: ```50%```

Jesse Stanger contribution: ```50%```

## Description of the data structure used for the Leaderboard
The following structs are created in both the Client and the Server programs. 

```
typedef struct User {
    char *name;
    int played;
    int wins;
} User;

typedef struct Leaderboard {
    User *list;
    int userCount;
} Leaderboard;
```

```User *list``` was intented to be extended in the future to contain a list of ```User``` objects, but currently it only contains a single ```User``` object. 

On the client side, when a User fills in their login details, the username is saved in ```Leaderboard->list->name```. The rest of the ```int```'s in the struct are initialised as ```0``` until the client communicates with the server and retrieves any saved data. At this time, the client does not send or receive Leaderboard updates from the server.

On the server side, when the server is launched, the ```Leaderboard``` struct is initialised as completely empty. As the client does not yet communicate with the server, the server's local ```Leaderboard``` struct is not updated.

## Description of how the critical-section problem is handled in Task 2
Task 2 is incomplete, and therefore the critical-section problem is not handled.

## Description of how the thread pool is created and managed in Task 3
Task 3 is incomplete, and therefore thread pools are not implemented.