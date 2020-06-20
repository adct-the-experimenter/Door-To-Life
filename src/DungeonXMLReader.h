#ifndef DUNGEONXMLREADER_H
#define DUNGEONXMLREADER_H

#include <vector> //header for vector container class
#include <sstream> //header for string stream processing
#include <string>

#include "Dungeon.h"

//file to read from xml


class DungeonXMLReader
{
	
public:

	//constructor
	DungeonXMLReader();

	//destructor
	~DungeonXMLReader();
	

	//function to set tiles in Dungeon based on what is read from file
	void SetDungeonTilesFromXML(std::string filepath,Dungeon* dungeon);
	
private:

};

#endif
