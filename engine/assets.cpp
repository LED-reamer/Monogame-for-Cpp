#include "assets.h"

#include "debug.h"

#include <vector>
#include <fstream>
#include <limits>

void g::Asset::unload()
{
	if (data != nullptr)
		free(data);
}

g::Asset::~Asset()
{
	if (data != nullptr)
		free(data);
}


g::AssetManager::AssetManager() : m_loadFromArchive(false)
{

}

g::AssetManager::~AssetManager()
{
	zip_close(m_archive);
}

void g::AssetManager::useArchive(const char* resDir, const char* password)
{
	m_loadFromArchive = true;

	if (m_loadFromArchive)
	{
		int error = 0;
		m_archive = zip_open(resDir, ZIP_RDONLY, &error);

		if (error != 0)
			Debug_LOG(ANSI_COLOR_RED "Could not load archive: %s" ANSI_COLOR_RESET, resDir);
	}
}

void g::AssetManager::loadFile(Asset& asset, const char* filename)
{
	asset.data = nullptr;
	asset.size = 0;
	if (m_loadFromArchive)
	{
		zip_file_t* file = zip_fopen(m_archive, filename, 0);
		zip_stat_t file_info;
	
		zip_stat(m_archive, filename, 0, &file_info);
	
		if (!file)
		{
			zip_close(m_archive);
			Debug_LOG(ANSI_COLOR_RED "Could not load archived file: %s" ANSI_COLOR_RESET, filename);
			return;
		}
	
	
		asset.data = (char*)malloc(file_info.size);
		if (asset.data == nullptr)
		{
			zip_fclose(file);
			zip_close(m_archive);
			Debug_LOG(ANSI_COLOR_RED "Could not load archived file: %s" ANSI_COLOR_RESET, filename);
			return;
		}
	
		zip_fread(file, asset.data, file_info.size);
		asset.size = file_info.size;
		zip_fclose(file);
		Debug_LOG(ANSI_COLOR_BLUE "Loaded: %s" ANSI_COLOR_RESET, filename);
	}
	else
	{
		std::ifstream file(filename, std::ios::binary | std::ios::ate);
		std::streamsize size = file.tellg();
		file.seekg(0, std::ios::beg);

		asset.data = (void*)malloc(sizeof(char) * size);
		asset.size = size;
		if (file.read((char*)asset.data, size))
		{
			Debug_LOG(ANSI_COLOR_BLUE "Loaded: %s" ANSI_COLOR_RESET, filename);
		}
		else
		{
			Debug_LOG(ANSI_COLOR_RED "Could not load file: %s" ANSI_COLOR_RESET, filename);
		}
	}
}

sf::Image g::AssetManager::loadFileImage(const char* filename)
{
	g::Asset asset;
	loadFile(asset, filename);
	sf::Image image;
	image.loadFromMemory(asset.data, asset.size);
	return image;
}

sf::Texture g::AssetManager::loadFileTexture(const char* filename)
{
	g::Asset asset;
	loadFile(asset, filename);
	sf::Texture texture;
	texture.loadFromMemory(asset.data, asset.size);
	return texture;
}

sf::Font g::AssetManager::loadFileFont(const char* filename)
{
	g::Asset asset;
	loadFile(asset, filename);
	sf::Font font;
	font.loadFromMemory(asset.data, asset.size);
	return font;
}

sf::SoundBuffer g::AssetManager::loadFileSoundBuffer(const char* filename)
{
	g::Asset asset;
	loadFile(asset, filename);
	sf::SoundBuffer soundBuffer;
	soundBuffer.loadFromMemory(asset.data, asset.size);
	return soundBuffer;
}