#include"MapObject.h"

MapObject::MapObject(TiXmlElement *node)
{
	ReadXML(node);
}
MapObject::~MapObject()
{
	for (std::size_t i = 0; i < numObjects; i++)
	{
		Mapinfo *obj = objects.at(i);
		delete obj;
	}
}
void MapObject::ReadXML(TiXmlElement *node)
{
	name = (char *)node->Attribute("name");
	TiXmlElement *indexml = NULL;
	numObjects = 0;
	for (indexml = node->FirstChildElement(); indexml != NULL; indexml = indexml->NextSiblingElement())
	{
		numObjects++;
		Mapinfo *obj = new Mapinfo(indexml, name);
		objects.push_back(obj);
	}
}