#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <zip.h>

namespace g
{
	class Asset
	{
	public:
		void* data;
		size_t size;
		void unload();
		~Asset();
	};

	class AssetManager
	{
	public:
		AssetManager();
		~AssetManager();
		void useArchive(const char* resDir, const char* password = nullptr);
		void loadFile(Asset& asset, const char* filename);
		sf::Image loadFileImage(const char* filename);
		sf::Texture loadFileTexture(const char* filename);
		sf::Font loadFileFont(const char* filename);
		sf::SoundBuffer loadFileSoundBuffer(const char* filename);
	private:
		const char* m_archiveDir;
		bool m_loadFromArchive;
		zip_t* m_archive;
	};
}