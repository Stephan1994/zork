#include <iostream>

#include <QString>

using namespace std;
#include "ZorkUL.h"

/*int main(int argc, char argv[]) {
	ZorkUL temp;
	temp.play();
	return 0;
}*/

ZorkUL::ZorkUL() {
	createRooms();
}

void ZorkUL::createRooms()  {
    //Room *a, *b, *c, *d, *e, *f, *g, *h, *i, *j;

    //creating rooms
    for (int i=0; i<50; i++)
    {
        for (int j=0; j<50; j++)
        {
            rooms[i][j] = new Room(to_string(i)+ "," + to_string(j));
            //TODO: add items, enemies
        }
    }

    //setting exits for rooms
    for (int i=0; i<50; i++)
    {
        for (int j=0; j<50; j++)
        {
            Room *exitsArray[4];
            int falseCounter;
            do{
                falseCounter = 0;
                for (int k=0; k<4; k++)
                {
                    if (rand() % 2 == 0)
                        falseCounter++;
                    else //set room as exit or NULL if at the edge
                    {
                        if (k == 0){
                            if (i-1 >= 0)
                                exitsArray[k] = rooms[i-1][j];
                            else{
                                exitsArray[k] = NULL;
                                falseCounter++;
                            }
                        }
                        else if (k == 1){
                            if (j+1 < 50)
                                exitsArray[k] = rooms[i][j+1];
                            else{
                                exitsArray[k] = NULL;
                                falseCounter++;
                            }
                        }
                        else if (k == 2){
                            if (i+1 < 50)
                                exitsArray[k] = rooms[i+1][j];
                            else{
                                exitsArray[k] = NULL;
                                falseCounter++;
                            }
                        }
                        else if (k == 3){
                            if (j-1 >= 0)
                                exitsArray[k] = rooms[i][j-1];
                            else{
                                exitsArray[k] = NULL;
                                falseCounter++;
                            }
                        }
                    }
                }
            } while (falseCounter == 4); //repeat if there's no door

            rooms[i][j]->setExits(exitsArray[0], exitsArray[1], exitsArray[2], exitsArray[3]);
        }
    }
    /*
	a = new Room("a");
        a->addItem(new Item("x", 1, 11));
        a->addItem(new Item("y", 2, 22));
    rooms.push_back(a);
	b = new Room("b");
        b->addItem(new Item("xx", 3, 33));
        b->addItem(new Item("yy", 4, 44));
    rooms.push_back(b);
	c = new Room("c");
    rooms.push_back(c);
	d = new Room("d");
    rooms.push_back(d);
	e = new Room("e");
    rooms.push_back(e);
	f = new Room("f");
    rooms.push_back(f);
	g = new Room("g");
    rooms.push_back(g);
	h = new Room("h");
    rooms.push_back(h);
	i = new Room("i");
    rooms.push_back(i);
    j = new Room("j");
    rooms.push_back(j);

//             (N, E, S, W)
	a->setExits(f, b, d, c);
	b->setExits(NULL, NULL, NULL, a);
	c->setExits(NULL, a, NULL, NULL);
    d->setExits(a, e, j, i);
	e->setExits(NULL, NULL, NULL, d);
	f->setExits(NULL, g, a, h);
	g->setExits(NULL, NULL, NULL, f);
	h->setExits(NULL, f, NULL, NULL);
    i->setExits(NULL, d, NULL, NULL);
    j->setExits(d, NULL, NULL, NULL);
    */
    int randI = rand() % 50;
    int randJ = rand() % 50;
    currentRoom = rooms[randI][randJ];
}

/**
 *  Main play routine.  Loops until end of play.
 */
void ZorkUL::play() {
	printWelcome();

	// Enter the main command loop.  Here we repeatedly read commands and
	// execute them until the ZorkUL game is over.

    /*bool finished = false;
	while (!finished) {
		// Create pointer to command and give it a command.
		Command* command = parser.getCommand();
		// Pass dereferenced command and check for end of game.
		finished = processCommand(*command);
		// Free the memory allocated by "parser.getCommand()"
		//   with ("return new Command(...)")
		delete command;
    }
	cout << endl;
    cout << "end" << endl;*/
}

void ZorkUL::printWelcome() {
    guiOutput = "start\n";
    guiOutput += "info for help\n\n";
    guiOutput += currentRoom->longDescription();
    guiOutput += "\n";
    //cout << "start"<< endl;
    //cout << "info for help"<< endl;
    //cout << endl;
    //cout << currentRoom->longDescription() << endl;
   // emit outputChanged(QString::fromStdString( guiOutput))
}

/**
 * Given a command, process (that is: execute) the command.
 * If this command ends the ZorkUL game, true is returned, otherwise false is
 * returned.
 */
bool ZorkUL::processCommand(Command command) {
	if (command.isUnknown()) {
		cout << "invalid input"<< endl;
		return false;
	}

	string commandWord = command.getCommandWord();
	if (commandWord.compare("info") == 0)
		printHelp();

	else if (commandWord.compare("map") == 0)
		{
        cout << "[h] --- [f] --- [g]" << endl;
		cout << "         |         " << endl;
        cout << "         |         " << endl;
		cout << "[c] --- [a] --- [b]" << endl;
		cout << "         |         " << endl;
		cout << "         |         " << endl;
		cout << "[i] --- [d] --- [e]" << endl;
        cout << "         |         " << endl;
        cout << "         |         " << endl;
        cout << "        [j]        " << endl;
		}

	else if (commandWord.compare("go") == 0)
		goRoom(command);

    else if (commandWord.compare("take") == 0)
    {
       	if (!command.hasSecondWord()) {
		cout << "incomplete input"<< endl;
        }
        else
         if (command.hasSecondWord()) {
        cout << "you're trying to take " + command.getSecondWord() << endl;
        int location = currentRoom->isItemInRoom(command.getSecondWord());
        if (location  < 0 )
            cout << "item is not in room" << endl;
        else
            cout << "item is in room" << endl;
            cout << "index number " << + location << endl;
            cout << endl;
            cout << currentRoom->longDescription() << endl;
        }
    }
    else if (commandWord.compare("teleport") == 0)
    {
        teleport(command);
    }

    else if (commandWord.compare("put") == 0)
    {

    }
    /*
    {
    if (!command.hasSecondWord()) {
		cout << "incomplete input"<< endl;
        }
        else
            if (command.hasSecondWord()) {
            cout << "you're adding " + command.getSecondWord() << endl;
            itemsInRoom.push_Back;
        }
    }
*/
    else if (commandWord.compare("quit") == 0) {
		if (command.hasSecondWord())
			cout << "overdefined input"<< endl;
		else
			return true; /**signal to quit*/
	}
	return false;
}
/** COMMANDS **/
void ZorkUL::printHelp() {
	cout << "valid inputs are; " << endl;
	parser.showCommands();

}

void ZorkUL::goRoom(Command command) {
	if (!command.hasSecondWord()) {
		cout << "incomplete input"<< endl;
		return;
	}

	string direction = command.getSecondWord();

	// Try to leave current room.
	Room* nextRoom = currentRoom->nextRoom(direction);

	if (nextRoom == NULL)
        guiOutput = "underdefined input\n";
	else {
		currentRoom = nextRoom;
        guiOutput = currentRoom->longDescription();
        guiOutput += "\n";
	}
}

string ZorkUL::go(string direction) {
	//Make the direction lowercase
	//transform(direction.begin(), direction.end(), direction.begin(),:: tolower);
	//Move to the next room
	Room* nextRoom = currentRoom->nextRoom(direction);
	if (nextRoom == NULL)
		return("direction null");
	else
	{
		currentRoom = nextRoom;
		return currentRoom->longDescription();
	}
}

void ZorkUL::teleport(Command com){
    if (!com.hasSecondWord()){
        guiOutput = "incomplete input\n";
        return;
    }

    string room = com.getSecondWord();
    if (room.compare("rand") == 0){
        //unsigned int roomSize = rooms.size();
        unsigned int randRoomI = rand() % 50;
        unsigned int randRoomJ = rand() % 50;
        currentRoom = rooms[randRoomI][randRoomJ];
    }
   /* else{
        for (unsigned int i = 0; i < rooms.size(); i++)
        {
            if (rooms[i]->shortDescription().compare(room) == 0)
                currentRoom = rooms[i];
        }
    }*/
   guiOutput = currentRoom->longDescription();
   guiOutput += "\n";
}
