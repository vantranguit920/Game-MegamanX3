#pragma once
#include"Mapinfo.h"
#include<string>
#include <vector>
using namespace std;
#include "TinyXML\tinyxml.h"

class MapObject
{
public:
	string name;
	vector<Mapinfo*> objects;
	int numObjects;

	MapObject(TiXmlElement *node);
	~MapObject();
	void ReadXML(TiXmlElement *node);
};