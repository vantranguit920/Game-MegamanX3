#include"Mapinfo.h"

Mapinfo::Mapinfo(TiXmlElement *node, string name)
{
	this->ReadXML(node, name);
}
Mapinfo::~Mapinfo()
{

}
void Mapinfo::ReadXML(TiXmlElement *node, string name)
{
	this->name = name;
	node->QueryIntAttribute("id", &id);
	node->QueryFloatAttribute("x", &x);
	node->QueryFloatAttribute("y", &y);
	node->QueryFloatAttribute("width", &width);
	node->QueryFloatAttribute("height", &height);
}