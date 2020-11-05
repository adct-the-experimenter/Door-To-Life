#ifndef DUNGEONXMLREGISTRY_H
#define DUNGEONXMLREGISTRY_H

#include <vector>
#include <string>


struct DungeonXMLEntry
{
	std::string filepath;
	size_t id_number;
};


class DungeonXMLRegistry
{
	
public:

	//constructor
	DungeonXMLRegistry();

	//destructor
	~DungeonXMLRegistry();
	

	//function to set dungeon xml entries based on what is read from file
	void SetDungeonXMLEntriesFromXML(std::string xml_filepath, std::string xml_file_dir_path);
	
	DungeonXMLEntry& GetReferenceToDungeonXMLEntry(size_t& index);
	size_t GetSizeOfDungeonXMLEntriesVector();
	
	std::string GetXMLDungeonFilePathFromIndex(size_t index);
	
	void ClearRegistry();
	
private:

	std::vector <DungeonXMLEntry> dungeon_xml_entries;
	
};

#endif
