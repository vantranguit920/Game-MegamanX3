#pragma once
#include<string>
#include "TinyXML\tinyxml.h"
using namespace std;

class Mapinfo
{
public:
	string name;
	float x, y, width, height;
	int id;

	Mapinfo(TiXmlElement *node, string name);
	~Mapinfo();
	void ReadXML(TiXmlElement *node, string name);
};
