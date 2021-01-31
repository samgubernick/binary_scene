
#ifndef SAM_BINARY_PROGRAM_HPP_INCLUDED
#define SAM_BINARY_PROGRAM_HPP_INCLUDED
#pragma once

#include "scenes.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

namespace sam
{
	namespace binary
	{
		class Program
		{
		public:
			Program();

			int now();
		private:
			enum class Stage
			{
				none,
				searchingForEndAnimation,
				searchingForEndBgm,
				searchingForEndImage,
				searchingForEndSfx,
			};

			struct Search
			{
				Stage stage;

				Search()
					: stage(Stage::none)
				{ }
			};

			option::Behavior getBehavior(std::string const & behavior);
			option::ImageFormat getImageFormat(std::string & imageFormat);
			void assignUniqueIndex(Scenes & scenes);
			void addTexture(std::string const & line, std::vector<Texture> & textures, size_t lineIndex);
			void addTexture(std::string const & line, std::vector<Texture> & textures);
			void addAnimationOption(std::string const & line, Animation & animation);
			void addSound(std::string const & line, std::vector<Sound> & sounds, Sound::Group group);
			void processLineAnimation(std::string const & line, Search & search, Animation & animation, size_t lineIndex);
			void addAnimation(std::string const & line, std::vector<Sprite> & sprites);
			void processLine(std::string const & line, Search & search, Scene & scene);
			bool makeFileDirs(std::filesystem::path const & file);
			bool loadScenesText(std::filesystem::path const & path, Scenes & scenes);
			bool loadScenes(std::filesystem::path const & path, Scenes & scenes);
			bool saveScenes(std::filesystem::path const & path, Scenes const & scenes);
			void convertScenesText(Scenes & scenes);
		};
	}
}
#endif // INCLUDE_GUARD
