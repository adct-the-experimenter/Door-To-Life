#include "DungeonXMLReader.h"

#include "pugixml.hpp"
#include <iostream>
#include <string>

DungeonXMLReader::DungeonXMLReader()
{

}

DungeonXMLReader::~DungeonXMLReader()
{
	
}

void DungeonXMLReader::SetDungeonTilesFromXML(std::string filepath, Dungeon* dungeon)
{
	// Create empty XML document within memory
    pugi::xml_document doc;
    
    // Load XML file into memory
    // Remark: to fully read declaration entries you have to specify
    // "pugi::parse_declaration"
    pugi::xml_parse_result result = doc.load_file(filepath.c_str(),
												pugi::parse_default);
    if (!result)
    {
        std::cout << "Parse error: " << result.description()
            << ", character pos= " << result.offset;
        return;
    }
    
    pugi::xml_node tileRoot = doc.child("DungeonXMLRoot").child("Tiles");
    
    size_t iterator = 0;
	
	//go through each tile type in tiles node
	for (pugi::xml_node tileType = tileRoot.first_child(); tileType; tileType = tileType.next_sibling())
	{	
		DungeonTile::TileType type = DungeonTile::TileType::RED;
		
		std::string valString = tileType.first_child().value();
		//std::cout << valString << std::endl;
		
		if(valString ==  "GREEN"){type = DungeonTile::TileType::GREEN; }
		else if(valString ==  "BLUE"){ type = DungeonTile::TileType::BLUE; }
		else if(valString ==  "RED"){ type = DungeonTile::TileType::RED; }
		else if(valString ==  "TOP"){ type = DungeonTile::TileType::TOP; }
		else if(valString ==  "TOP_LEFT"){ type = DungeonTile::TileType::TOP_LEFT; }
		else if(valString ==  "TOP_RIGHT"){ type = DungeonTile::TileType::TOP_RIGHT; }
		else if(valString ==  "LEFT"){ type = DungeonTile::TileType::LEFT; }
		else if(valString ==  "CENTER"){ type = DungeonTile::TileType::CENTER; }
		else if(valString ==  "RIGHT"){ type = DungeonTile::TileType::RIGHT; }
		else if(valString ==  "BOTTOM_LEFT"){ type = DungeonTile::TileType::BOTTOM_LEFT; }
		else if(valString ==  "BOTTOM"){ type = DungeonTile::TileType::BOTTOM; }
		else if(valString ==  "BOTTOM_RIGHT"){ type = DungeonTile::TileType::BOTTOM_RIGHT; }
		else{std::cout << "Tile type not handled!" << "i:" << iterator << std::endl; }
			
		dungeon->dungeonTileSet[iterator]->setType(type);
		
		iterator++;		
	}
	
	dungeon->setTiles();
}
