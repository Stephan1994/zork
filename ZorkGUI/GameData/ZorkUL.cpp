#include <iostream>

using namespace std;
#include "ZorkUL.h"


ZorkUL::ZorkUL(int roomsRow, int roomsCol)
{
    maxRoomsRow = roomsRow;
    maxRoomsCol = roomsCol;
    player = new Player("player1");
	createRooms();
}

ZorkUL::~ZorkUL()
{
    delete player;
    for(int i = 0; i< maxRoomsRow; i++)
    {
        for(int j = 0; j < maxRoomsCol; j++)
        {
            delete rooms[i][j];
        }
    }
}

void ZorkUL::createRooms()
{
    //creating rooms
    for (int i=0; i<maxRoomsRow; i++)
    {
        for (int j=0; j<maxRoomsCol; j++)
        {
            rooms[i][j] = new Room(to_string(i)+ "," + to_string(j), i, j);

            //add knives
            if((rand() % 10) == 0)
            {
                Item *it = new Item("knife", ":/GameView\\pictures\\knife.png", 10);
                rooms[i][j]->addItem(it);
            }

            //add ghosts
            if(!rooms[i][j]->enemyAvailable() && (rand() % 20) == 0)
            {
                Enemy *en = new Enemy("ghost", ":/GameView\\pictures\\ghost.jpg");
                rooms[i][j]->setEnemy(en);
            }

        }
    }

    //setting exits for rooms
    for (int i=0; i<maxRoomsRow; i++)
    {
        for (int j=0; j<maxRoomsCol; j++)
        {
            Room *exitsArray[4];
            int falseCounter;
            do{
                falseCounter = - rooms[i][j]->getNumberofExits();
                for (int k=0; k<4; k++)
                {
                    //doors are randomly generated
                    if (rand() % 2 == 0)
                    {
                        falseCounter++;
                        exitsArray[k] = NULL;
                    }
                    else //set room as exit or NULL if at the edge
                    {
                        //north
                        if (k == 0){
                            if (i-1 >= 0 && !rooms[i][j]->hasExit("north"))
                                exitsArray[k] = rooms[i-1][j];
                            else{
                                exitsArray[k] = NULL;
                                falseCounter++;
                            }
                        }
                        //east
                        else if (k == 1){
                            if (j+1 < maxRoomsCol && !rooms[i][j]->hasExit("east"))
                                exitsArray[k] = rooms[i][j+1];
                            else{
                                exitsArray[k] = NULL;
                                falseCounter++;
                            }
                        }
                        //south
                        else if (k == 2){
                            if (i+1 < maxRoomsRow && !rooms[i][j]->hasExit("south"))
                                exitsArray[k] = rooms[i+1][j];
                            else{
                                exitsArray[k] = NULL;
                                falseCounter++;
                            }
                        }
                        //west
                        else if (k == 3){
                            if (j-1 >= 0 && !rooms[i][j]->hasExit("west"))
                                exitsArray[k] = rooms[i][j-1];
                            else{
                                exitsArray[k] = NULL;
                                falseCounter++;
                            }
                        }
                    }
                }
            } while (falseCounter == 4); //repeat if there's no door

            int randDoors[4] = {rand() % 6, rand()%6, rand()%6, rand()%6};
            rooms[i][j]->setExits(exitsArray[0], randDoors[0], exitsArray[1], randDoors[1], exitsArray[2], randDoors[2], exitsArray[3], randDoors[3]);

            //add the backdoors for the connected rooms
            for (int k = 0; k < 4; k++)
            {
                if (exitsArray[k] != NULL)
                {
                    //north
                    if (k == 0){
                        exitsArray[k]->setExits(NULL,0,NULL,0,rooms[i][j],randDoors[0],NULL,0);
                    }
                    //east
                    else if (k == 1){
                        exitsArray[k]->setExits(NULL,0,NULL,0,NULL,0,rooms[i][j],randDoors[1]);
                    }
                    //south
                    else if (k == 2){
                        exitsArray[k]->setExits(rooms[i][j],randDoors[2],NULL,0,NULL,0,NULL,0);
                    }
                    //west
                    else if (k == 3){
                        exitsArray[k]->setExits(NULL,0,rooms[i][j],randDoors[3],NULL,0,NULL,0);
                    }
                }
            }
        }
    }

    //add 10 quest items
    for (int i = 0; i < 10; i++)
    {
        int randRow, randCol;
        do{
            randRow = rand() % maxRoomsRow;
            randCol = rand() % maxRoomsCol;
        }
        while(rooms[randRow][randCol]->getNumberofItems() != 0);

        Item *it = new Item("coin", ":/GameView\\pictures\\coin.png", 0, true, false);
        rooms[randRow][randCol]->addItem(it);
    }

    int randI = rand() % maxRoomsRow;
    int randJ = rand() % maxRoomsCol;
    if (rooms[randI][randJ]->enemyAvailable())
        rooms[randI][randJ]->enemyDefeated();
    currentRoom = rooms[randI][randJ];

}

void ZorkUL::play()
{
    startStory();
}

void ZorkUL::startStory()
{
    guiOutput = "You play as a Postman named Spoones McFreind.\n\
Due to a deep, mysterious love of mazes and maze-games, You enter yourself into the most dangerous real life maze-game ever devised.\n\
The Grand prize is the magical ability to summon wasps. \n\
You are blindfolded, spun around 3 times, then put under general anesthetic and man-hadled into  the center of a damp, dark, mysterious maze.\n\
You appear to be in a tudor-style town house with Italian marble floors and off white mouldy walls, teastefuly coupled with rotting furniture.\n\n\
You can only escape by collecting ten of these very rare and antique golden coins.\n\n";
}

/** COMMANDS **/

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
        guiOutput += "----------------------------\n";
        guiOutput += currentRoom->longDescription();
        guiOutput += "\n";
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
        unsigned int randRoomI = rand() % maxRoomsRow;
        unsigned int randRoomJ = rand() % maxRoomsCol;
        currentRoom = rooms[randRoomI][randRoomJ];
    }
   guiOutput = currentRoom->longDescription();
   guiOutput += "\n";
}

/** GET/SET **/

Room* ZorkUL::getRoom(int row, int col) const
{
   return rooms[row][col];
}

int ZorkUL::getMaxRoomsRow() const
{
    return maxRoomsRow;
}

int ZorkUL::getMaxRoomsCol() const
{
    return maxRoomsCol;
}
