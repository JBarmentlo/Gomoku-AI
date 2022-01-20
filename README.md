# Gomoku-AI

The program once run listens for a TCP connection on port 1234.   
In the following file **"server"** shall refer to the Gomook executable and **"client"** to the user interface connecting to it.

<br></br>
## **API specifications**
The server excpects to recieve a json message.   
The json **MUST** contain a **"type"** field with a value in **["start", "move"]**.   specifying the type of message :
- "start" requests a new game
- "move"  plays a move in an ongoing game


<br></br>
### **Start message**
An example start message.
```json
{
	"type"	: "start",
	"cpu"	: true,
	"depth"	: 7 				# depth of minmax tree
}
```
The **"cpu"** field specifies if a hotseat or vs cpu game should be started (true =>  play vs cpu)

The server will respond with
```json
{
	"type"	: "game_start",
	"cpu"	: "true / false",
	"depth"	: 7 				
}
```
After this **"move"** type messages can be sent.

<br></br>
###	**Move message**
The server awaits a message of the following shape:
```json
{
	"type"	: "move",
	"move"	:  123
}
```
The move number corresponds to `row * 19 + col`.

The server will respond with:
```json
{
	"type"			: "move",
	"illegal"		: true / false,				# If true the move sent was illegal and was ignored
	"w_captures"	: int						# Number of white captures [1-5]
	"b_captures"	: int						# Number of black captures [1-5]
	"winner"		: "black" / "white" / "no"	# Winner, "no" if no winner
	"player:		: "black" / "white"			# Player who's turn it is
	"cpu"			: true / false				# true if cpu game, false if hotseat game
	"suggested_move": int						# Only if hotseat game, the move suggested
												# by the server
	"white_board"	: str						# explained below
	"black_board"	: str						# explained below
}
```

The **"white_board"** field contains a string of `'0'` and `'1'` of length `19 * 19` representing the white pieces on the board.   
1's are the white pieces, 0's the empty squares. The string is in reverse reading order (i.e. the bottom right square is represented by the first char of the string, the second char is the square to the left of the first.).   
Same for **"black_board"**.
