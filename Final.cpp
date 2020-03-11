#include <iostream> 
#include <string> 
#include <vector> 
#include <cctype>
#include <algorithm>

using namespace std;

bool debug = false;
 
enum en_DIRS {NORTH, EAST, SOUTH, WEST};
enum en_ROOMS {SPORTSHOP, CASINO, CARPARK, LOBBY, RESTAURANT, CORRIDOR, STOREROOM, POOL,
GARDEN, PATIO, PUMPROOM, MASTERBEDROOM, DININGROOM, BEDROOM, POOLTROOM,
TVAREA, KITCHEN, ASTROROOF, ESPORTSROOM, DAYROOM, GARAGE, SAUNAROOM,
PRIVATEPOOL, LIBRARY, PLANTROOM, BUDROOM, GUNRANGE, PARTSHOP ,PARKINGLOT, SECURITYROOM};

enum en_VERBS {GET, DROP, USE, OPEN, CLOSE, EXAMINE, INVENTORY, LOOK};

enum en_NOUNS {STORE_DOOR, CANE, VASE, ROSES, ROLEX, AMMOBOX,PIANOBOOK,MACBOOK,PEN,NIKES,PILLOW,IMAC,CIGARS,TSCOPE,LAKERSJERSEY}; //15 nouns

const int NONE= -1; // it means no exit in this direction
const int DIRS = 4; // DIRS = NORTH, EAST, WEST, SOUTH
const int ROOMS = 30; //changed rooms to 30 // rooms = locations in the game
const int VERBS = 8; // verbs = actions?? 

const int NOUNS = 15; //changed nouns to 15 // nouns = objects in the game
int invcount = 30;

class words {  //Step (1) changing structs into classes and setup get & set // (f) finished
public:
	words(string wd,int cde) 
	{
		word = wd;
		code = cde;
	}
	void setWord(string givenWord){
		word = givenWord;
	}
	void setCode(int givenCode){
		code = givenCode;
	}
	string getWord(){
		return word;
	}
	int getCode(){
		return code;
	}
	
private:
	int code;
	string word;
};

class room{  // (1) structs to classes 
public:
	room(string desc, int NRTH , int EST, int STH, int WST ){ // (1) setup like how its originally placed in rms array
		description = desc;
		exits_to_room[NORTH] = NRTH;
		exits_to_room[EAST] = EST;
		exits_to_room[SOUTH] = STH;
		exits_to_room[WEST] = WST;
		roomID = gRoom;
		gRoom++;
	}
	
	void setDesc(string givenDscript){
		string description = givenDscript;
	}
	void setExit(int givenDIR, int room){
		exits_to_room[givenDIR] = room;
	}	
	int getExit(int DIRS){
		return exits_to_room[DIRS];
	}
	string getDesc(){
		return description;
	}
	int getRoom(){
		return roomID;
	}

private:
string description;
int exits_to_room[DIRS];
static int gRoom;
int roomID;
};

class noun{  // (1) structs to classes
public:	
	noun(string wrd, string desc, int cde, int loc, bool car){
		description = desc;
		word = wrd;
		code = cde;
		location = loc;
		can_carry = car;
	}
	void setLoc(int givenLoc){
		location = givenLoc;
	}

	string getWord(){
		return word;
	}
	string getDesc(){
		return description;
	}
	int getCode(){
		return code;
	}
	int getLoc(){
		return location;
	}
	bool getCarry(){
		return can_carry;
	}
	string Examine(noun){
		return description;
	}
	
private:
string word;
string description;
int code;
int location;
bool can_carry;
};

class Inventory {			//setting up inventory, display inv, get items, examine items 
public:
	
	Inventory(vector<room>&rms,vector<noun>&nns){
		display(rms,nns);
	}
	
	void display(vector<room> rms,vector<noun> nns)
    {
        int j = 1;
        for (int i = 0; i < nns.size(); i++)
        {
            if ((nns[i]).getLoc() == INVENTORY)
            {
                cout << j << ": " << (nns[i]).getWord() << endl;
                j++;
            }
        }
    }
	void get(vector<noun>& nns,vector <room> rms, int givenItem, int location)
    {
        if (((nns[givenItem]).getCarry()) == true && ((rms[location]).getRoom() == nns[givenItem].getLoc()))
        {
            cout << "Picked up.. " << nns[givenItem].getDesc() << ".\n";
            nns[givenItem].setLoc(INVENTORY);
            invcount++;
            return;
        }
        else if(((nns[givenItem].getCarry()) == false) && ((rms[location]).getRoom() == nns[givenItem].getLoc()))
        {
            cout << "Cant carry that.\n";
            return;
        }
        else if ((rms[location]).getRoom() != (nns[givenItem].getLoc()))
        {
            cout << "Items not here.\n";
            return;
        }        
    }
	void examine(vector<noun>& nns,vector<room>rms, int givenItem, int location)
	{
		if ((nns[givenItem]).getLoc() == (rms[location]).getRoom())
		{
			cout << "Examining.... " << (nns[givenItem]).getWord() << ".\n";
			cout << "The item is a " << (nns[givenItem].getDesc()) << ".\n";
		}
	}	

private:
};


void set_rooms(vector<room>& rms){    
	rms.push_back(room("soccer turf",NONE ,NONE ,CARPARK ,NONE));  			//"sports shop"
	rms.push_back(room("smoking room", SECURITYROOM, NONE, LOBBY, NONE));  //"bustling casino"
	rms.push_back(room("driveway",SPORTSHOP,LOBBY,PARKINGLOT,NONE));				//"car park"
	rms.push_back(room("main lobby",CASINO,RESTAURANT,CORRIDOR,CARPARK));	//"hotel lobby"
	rms.push_back(room("personal restaurant", MASTERBEDROOM, NONE, NONE, LOBBY));	//"restaurant"
	rms.push_back(room("hallway",LOBBY,NONE,GARDEN,NONE));					//"corridor"
	rms.push_back(room("store room",NONE,NONE,NONE,NONE));					//"storeroom"
	rms.push_back(room("jacuzzi",NONE,GARDEN,PUMPROOM,NONE));	//"swimming pool area"
	rms.push_back(room("chill zone",CORRIDOR,PATIO,DAYROOM,POOL));		//"tranquill garden"
	rms.push_back(room("wood deck",NONE,NONE,SAUNAROOM,GARDEN));	//"patio with a fish"
	rms.push_back(room("tool shed",POOL,NONE,PLANTROOM,NONE));			//"Damn pump room"  
	rms.push_back(room("Masterbedroom",DININGROOM,NONE,RESTAURANT,NONE));	
	rms.push_back(room("Dining Room",BEDROOM,ASTROROOF,MASTERBEDROOM,NONE));
	rms.push_back(room("Bedroom",KITCHEN,POOLTROOM,DININGROOM,NONE));
	rms.push_back(room("Pool table room",NONE,TVAREA,NONE,BEDROOM));
	rms.push_back(room("TV Area",NONE,NONE,NONE,POOLTROOM));
	rms.push_back(room("KITCHEN",NONE,NONE,BEDROOM,NONE));
	rms.push_back(room("ASTROROOF",NONE,ESPORTSROOM,NONE,DININGROOM));
	rms.push_back(room("ESPORTROOM",NONE,NONE,NONE,ASTROROOF));
	rms.push_back(room("Dayroom",GARDEN,NONE,GARAGE,NONE));
	rms.push_back(room("Garage",DAYROOM,NONE,NONE,NONE));
	rms.push_back(room("Saunaroom",PATIO,LIBRARY,PRIVATEPOOL,NONE));
	rms.push_back(room("Private Pool",SAUNAROOM,BUDROOM,NONE,NONE));
	rms.push_back(room("Library",NONE,NONE,NONE,SAUNAROOM));
	rms.push_back(room("Plant room",PUMPROOM,NONE,GUNRANGE,NONE));
	rms.push_back(room("Budroom",NONE,NONE,NONE,PRIVATEPOOL));
	rms.push_back(room("Gun Range",PLANTROOM,PARTSHOP,NONE,NONE));
	rms.push_back(room("Parts shop",NONE,NONE,NONE,GUNRANGE));
	rms.push_back(room("Parking lot",CARPARK,NONE,NONE,NONE));
	rms.push_back(room("Security room",NONE,NONE,CASINO,NONE));  //30 rooms
} 	
void set_directions(vector<words>& dir){	// (2) change to vector // (f) Finished√
	dir.push_back(words("NORTH", NORTH));		
	dir.push_back(words("EAST", EAST));
	dir.push_back(words("SOUTH", SOUTH));
	dir.push_back(words("WEST", WEST));
}
void set_verbs(vector<words>& vbs){   // (2) change to vector  // (f) Finished√
	vbs.push_back(words("GET", GET));
	vbs.push_back(words("DROP", DROP));
	vbs.push_back(words("DROP", DROP));
	vbs.push_back(words("USE", USE));
	vbs.push_back(words("OPEN", OPEN));
	vbs.push_back(words("CLOSE", CLOSE));
	vbs.push_back(words("EXAMINE", EXAMINE));
	vbs.push_back(words("INVENTORY", INVENTORY));
	vbs.push_back(words("LOOK", LOOK));
}
void set_nouns(vector<noun>& nns){ 
	//string wrd, string desc, int cde, int loc, bool car
	nns.push_back(noun("Glass Door","a fancy glass door",STORE_DOOR, LOBBY, false)); 
	nns.push_back(noun("CANE", "a cane", CANE ,CASINO,true));		
	nns.push_back(noun("VASE","a beautiful vase", VASE, PATIO ,false));	
	nns.push_back(noun("ROSES","a vase with roses", ROSES,PLANTROOM,false));	
	nns.push_back(noun("ROLEX", "a rolex",ROLEX, DAYROOM, true));				
	nns.push_back(noun("AMMO", "a ammobox",AMMOBOX, GUNRANGE, false)); 
	nns.push_back(noun("PIANOBOOK", "a piano book",PIANOBOOK, GARDEN,true));		
	nns.push_back(noun("MACBOOK","a macbook",MACBOOK,MASTERBEDROOM,true));
	nns.push_back(noun("PEN","a mighty pen",PEN,RESTAURANT,true));
	nns.push_back(noun("NIKES","a fresh pair of nikes",NIKES,DININGROOM,false));
	nns.push_back(noun("PILLOW","a nice pillow",PILLOW,BEDROOM,false));
	nns.push_back(noun("iMAC","a new iMAC",IMAC,BUDROOM,false));
	nns.push_back(noun("CIGAR","a nice cigar",CIGARS,POOL,true));
	nns.push_back(noun("TELESCOPE","a telescope",TSCOPE,ASTROROOF,false));
	nns.push_back(noun("LAKERSJERSEY","a hanged up lakers jersey",LAKERSJERSEY,POOLTROOM,false)); //15 nouns
}

void section_command(string Cmd, string &wd1, string &wd2)
{
	if (debug){
		cout << "Cmd = " << Cmd << ", wd1 = " << wd1 << ", wd2 = " << wd2 << " \n";
	}

	string sub_str; 
	vector<string> words; 
	char search = ' '; 
	size_t i, j;

	// Cycle through Cmd (command)
	for(i = 0; i < Cmd.size(); i++)
	{
		// If any spot in Cmd is NOT ' '
		// put it into sub_str
		// EX: LOOK
		// L != ' ', so it goes into sub_str
		// O
		// O
		// K
		// End sub_str;
		if(Cmd.at(i) != search)
		{
			sub_str.insert(sub_str.end(), Cmd.at(i));
		}

		// if i = Cmd.size() - 1...
		// If i reaches the location right before the end of the command word
		// put sub_str in words vector
		if(i == Cmd.size() - 1)
		{
			words.push_back(sub_str); 
			sub_str.clear();
		}
		
		// if i = ' ', put sub_str in words vector
		if(Cmd.at(i) == search)
		{
			words.push_back(sub_str); 
			sub_str.clear();
		}
	}

	// go through words vector size, starting at second to last element,
	// and go backwards
	for(i = words.size() - 1; i > 0; i--)
	{
		// if words(i) = "", erase words(i)
		if(words.at(i) == "")
		{
			words.erase(words.begin() + i);
		}
	}

	// go through words starting from the beginning
	for(i = 0; i < words.size(); i++)
	{
		// capatilize all the shit
		for(j = 0; j < words.at(i).size(); j++)
		{	
			if(islower(words.at(i).at(j)))
			{
				words.at(i).at(j) = toupper(words.at(i).at(j));
			}
		}
	}

	// If vector words is empty, no command given
	if(words.size() == 0)	
	{	
		cout << "No command given"<< endl;
	}	

	// if one command given, set wd1 = command
	if(words.size() == 1)
	{
		wd1 = words.at(0);
	}

	// if two commands given, set wd1 equal to first command
	// and wd2 equat to second.
	if(words.size() == 2)
	{
		wd1 = words.at(0); 
		wd2 = words.at(1);
	}

	// If more than two commands, fuck off.
	if(words.size() > 2)
	{ 
		cout << "Command too long. Only type one or two words (direction or verb and noun)" 
		<< endl;
	}
}

void look_around(int loc, vector<room>& rms, vector<words>& dir, vector<noun>& nns)   //adjust to vector references 
{
	int i;
	cout << "I am in a " << rms[loc].getDesc() << "." << endl;
	cout << "My room id is " << loc << endl;
	for(i = 0; i < DIRS; i++)
	{
 		if(rms[loc].getExit(i) != NONE)
		{
			cout << "There is an exit " << dir[i].getWord() << " to a " <<
			rms[rms[loc].getExit(i)].getDesc() << "." << endl;  //DONT KNOW HOW TO DO THIS SHOULD ASK FOSTER (!!!!)
		}	
 	}


	for(i = 0; i < NOUNS; i++)
	{	
		if(nns[i].getLoc() == loc)
		{
			cout << "I see "<< nns[i].getDesc() << "." << endl;		
		}
	}
}


bool parser(int &loc, string wd1, string wd2, vector<words>& dir, vector<words>& vbs, vector<room>& rms, vector<noun>& nns, Inventory inv)
{
	if(debug) {
		cout << "wd1 = " << wd1 << " and wd2 = " << wd2 << endl;
	}

	// Door is false
	static bool door_state = false; 
	int i;

	// Go through all 4 directions
	for(i = 0; i < DIRS; i++)
	{
		// If wd1 = a direction
		if(wd1 == dir[i].getWord())   //ask how to set this up??
		{	
			// if carpark (location from main) .getExit

			// if the room next to current room is not invalid
			if(rms[loc].getExit(dir[i].getCode()) != NONE)
			{
				// location = vector index based on the given direction
				// uses getCode to return CARPARK instead of "Carpark"
				loc = rms[loc].getExit(dir[i].getCode());
				cout << "I am now in a "<< rms[loc].getDesc() << "." << endl;

				// if location = either storeroom or corridor
				// go through nouns and set location equal to corridor
				// prevents you from entering storeroom
				if(loc == STOREROOM || loc == CORRIDOR)
				{
					nns[STORE_DOOR].setLoc(loc);   // should figure out how to convert (ASK PROFESSOR//in class noun (the get is) int getLoc()	)  setLoc setter					
				}
				return true;
				}
			else
			{
				cout << "No exit that way."<< endl; 
				return true;
			}
		}
	}

	// NOUN_MATCH = -1
	// VERB_MATCH = -1
	int NOUN_MATCH = NONE;
	int VERB_ACTION = NONE;

	// Go through VERBS (8)
	for(i = 0; i < VERBS + 1; i++)
	{
		// if wd1 = the word at index of vbs
		if(wd1 == vbs[i].getWord())
		{
			// Then set VERB_ACTION equal to the getCode at the index of vbs
			VERB_ACTION = vbs[i].getCode(); 
			break;
		}
	}

	if(wd2 != "")
	{
		for(i = 0; i < NOUNS; i++)
		{
			if(wd2 == nns[i].getWord())
			{
				NOUN_MATCH = nns[i].getCode(); 
				break;
			}
		}
	}

	if(VERB_ACTION == NONE)
	{
		cout << "No valid command entered."<< endl; 
		return true;
	}
	
	if(VERB_ACTION == LOOK)
	{
		look_around(loc, rms, dir, /* Added parameter nns */ nns); 
		return true;
	}
	
	if (VERB_ACTION == INVENTORY){
		cout << "Displaying inventory!: \n";  
        inv.display(rms,nns);         
        return true;
	}
	if (VERB_ACTION == GET)
    {
        if (wd2 != "")
        {
            inv.get(nns, rms, NOUN_MATCH, loc);
            return true;
        }
        else
        {
            cout << "This action requires an item.\n";
            return false;
        }
    }
	
	if (VERB_ACTION == EXAMINE)
	{
		if (wd2 != "")
		{
			inv.examine(nns,rms, NOUN_MATCH, loc);
			return true;
		}
		else
		{
			cout << "This action requires an item.\n";
			return false;
		}
	}
	
	if(debug) {
		cout << "noun = " << NOUN_MATCH << endl;
		cout << "StoreDoor = " << STORE_DOOR << endl;
		cout << "nns[0] = '" << nns[0].getWord() << "'.\n";
	}

	if(VERB_ACTION == OPEN)
	{	
		if(NOUN_MATCH == STORE_DOOR)
		{ 
			if(loc == CORRIDOR || loc == STOREROOM)
			{
				if(door_state == false)
				{
					door_state = true; 
					rms[CORRIDOR].setExit(EAST,STOREROOM);  
					rms[STOREROOM].setExit(WEST,CORRIDOR); 
					nns[STORE_DOOR].getDesc().clear(); 
					nns[STORE_DOOR].getDesc().assign("an open store room door");
					cout << "I have opened the door." << endl;
					return true;
				}
				else if(door_state == true)
				{
					cout << "The door is already open." << endl; 
					return true;
				}
			}
			else
			{
				cout << "There is no door to open here."<< endl; 
				return true;
			}
		}
		else
		{	
			cout << "opening that is not possible."<< endl; 
			return true;
		}
	}
return false;
}

int room::gRoom = 0;


int main(){      
	if (debug) cout << "Starting main(*)\n";
	vector<room> rooms;      //(p)protyping changed vecs from arrays
	vector<words> directions; // (p)
	vector<words> verbs;		// (p)
	vector<noun> nouns;      // (p)
	
	Inventory inv(rooms,nouns);

	
	string command; 
	string word_1;
	string word_2;
 	
	//room rooms[ROOMS];
	set_rooms(rooms);
	// words directions[DIRS];
	set_directions(directions);
	//words verbs[VERBS];
	set_verbs(verbs);
	// noun nouns[NOUNS]; 
	set_nouns(nouns); 

	//setting up inventory
	
	if(debug)   //for finding push_back errors
	{
		for (int i = 0; i < ROOMS; i++)
		{
			cout << i << ": " << rooms[i].getDesc() << endl;
		}
	}

	int location= CARPARK;
	
	while(word_1 != "QUIT")
	{
		command.clear();
		cout << "[Abra's Dreamhome]\n";
		cout << "\nWhat shall I do? "; 
		getline(cin, command);
		
		word_1.clear(); 
		word_2.clear();


		section_command(command, word_1, word_2); 
		
		if(word_1 != "QUIT")
		{
			parser(location, word_1, word_2, directions, verbs, rooms, /* Added parameter*/ nouns, inv);
		}
	}
	return 0;
}
