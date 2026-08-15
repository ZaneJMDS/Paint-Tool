#pragma once
#include <Windows.h> // Includes windows file explorer
#include <ShObjIdl.h> // Includes file types
#include <string>
#include "Button.h" // Includes needed SFML files

class FileInterface
{
public:
	FileInterface();
	~FileInterface();

	void LoadFile(sf::RenderTexture* _texture);
	void SaveFile(sf::RenderTexture* _texture);
};

