# C4 - Connect 4

A TCP server manages a game between two or more clients with JSON messages, any client can be automatic or interactive.

## Executing

### Dependencies

There are no dependencies and the only requirement is being under a Windows 10 or 11 system.

### Building

All the build scripts are under the `cmd` directory, each of them uses the `zig cc` compiler for simplicity, if desired change the script to specify which other compiler it should use.

To build:

- The server run `cmd/server` from the project's root directory
- The client run `cmd/client` from the project's root directory

## Details

To host a match start the server by specifying:

1. The port with `--server-port`
2. The number of players with `--players`
3. The width and height of the board with `--board-width` and `--board-height`

The server then waits for clients to join.

To join a match start a client by specifying:

1. The address with `--server-addr`
2. The port with `--server-port`

The client then joins by sending a `PLAYER_JOIN` and if the server responds with `PLAYER_ACCEPT` the client has joined the match. Any client after the first receives a list of all the ones that have already joined in the form of many consecutive `PLAYER_DATA`, while the server broadcasts to all of them the new client's `PLAYER_DATA`.

When all the clients have joined the server sends a `GAME_START`, after that the server broadcasts a `PLAYER_TURN` with the client that should make a move and waits for their `PLAYER_CHOICE` from such client. Then:

- If the server receives a `PLAYER_CHOICE` it broadcasts it to all the other clients, executes it and then:
    1. If the player has won it broadcasts a `GAME_STOP` with the winner
    2. If the player hasn't won and the board is full it broadcasts a `GAME_STOP` with no winner
- If the server receives a `PLAYER_SKIP`, it broadcasts it to all of the other clients and does nothing
- If the server receives any other message, it broadcastas a `PLAYER_SKIP` to all of the other clients and does nothing

A new turn always starts unless the server sends a `GAME_STOP`.

On the other side the client waits for a message after the `GAME_START` and:

- If the message is a `PLAYER_TURN` then:
    1. If the turn is theirs it sends a `PLAYER_CHOICE`
    2. If the turn isn't theirs it waits for either a `PLAYER_CHOICE` or a `PLAYER_SKIP` from the server
- If the message is a `GAME_STOP` then communicates the result

The client always waits for a message unless it receives a `GAME_STOP`.

## Planned

### Automatic clients

An automatic client decides which move to make without human intervention.
