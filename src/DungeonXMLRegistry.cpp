#include "DungeonXMLRegistry.h"

#include "pugixml.hpp"
#include <iostream>
#include <string>

DungeonXMLRegistry::DungeonXMLRegistry()
{
	
}

DungeonXMLRegistry::~DungeonXMLRegistry()
{
	dungeon_xml_entries.clear();
}

void DungeonXMLRegistry::SetDungeonXMLEntriesFromXML(std::string filepath, std::string xml_file_dir_path)
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
    
    pugi::xml_node dungeonsRoot = doc.child("DungeonXMLRoot").child("Dungeons");
    
    std::int16_t iterator = 1;
	
	//go through each tile type in tiles node
	for (pugi::xml_node name = dungeonsRoot.first_child(); name; name = name.next_sibling())
	{
		DungeonXMLEntry entry;
			
		std::string full_path = "";
		
		std::string valString = name.first_child().value();
		//std::cout << valString << std::endl;
		
		full_path = xml_file_dir_path + valString + ".xml";
		
		entry.filepath = full_path;
		entry.id_number = iterator;
		
		dungeon_xml_entries.push_back(entry);
				
		iterator++;		
	}
}

DungeonXMLEntry& DungeonXMLRegistry::GetReferenceToDungeonXMLEntry(size_t& index){return dungeon_xml_entries[index];}

size_t DungeonXMLRegistry::GetSizeOfDungeonXMLEntriesVector(){return dungeon_xml_entries.size();}

std::string DungeonXMLRegistry::GetXMLDungeonFilePathFromIndex(size_t index){ return dungeon_xml_entries[index-1].filepath;}

void DungeonXMLRegistry::ClearRegistry(){dungeon_xml_entries.clear();}
