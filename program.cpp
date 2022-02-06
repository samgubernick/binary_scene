
#include "program.hpp"

#include "assign_unique_index.hpp"
#include "is_match.hpp"
#include "scenes.hpp"

#include "bitsery/adapter/stream.h"
#include "bitsery/bitsery.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

namespace cur = sam::binary_data;

namespace
{
	
	constexpr auto const KEY_NAME = size_t{ 0 };
	constexpr auto const KEY_PATH = size_t{ 1 };
	constexpr auto const KEY_IMAGE_FORMAT = size_t{ 2 };
	constexpr auto const KEY_BEHAVIOR_X = size_t{ 3 };
	constexpr auto const KEY_BEHAVIOR_Y = size_t{ 4 };

	bool isSpacer(char const & c)
	{
		if (cur::is_match(c, '\t')
			|| cur::is_match(c, ':')
			|| cur::is_match(c, '\n'))
		{
			return true;
		}

		return false;
	}

	bool isValidChar(char const & c)
	{
		if (cur::is_match(c, '\t')
			|| cur::is_match(c, ':')
			|| cur::is_match(c, '\n'))
		{
			return false;
		}

		return true;
	}
}

cur::Program::Program()
{

}

cur::option::Behavior cur::Program::getBehavior(std::string const & behavior)
{
	//std::cout << "Behavior: (" << behavior << ")" << std::endl;
	if (is_match(behavior, "mirror"))
	{
		return option::Behavior::mirror;
	}
	else if (is_match(behavior, "stretch"))
	{
		return option::Behavior::stretch;
	}
	else if (is_match(behavior, "repeat"))
	{
		return option::Behavior::repeat;
	}
	else if (is_match(behavior, "center"))
	{
		return option::Behavior::center;
	}

	return option::Behavior::repeat;
}

cur::option::ImageFormat cur::Program::getImageFormat(std::string & imageFormat)
{
	//std::cout << "Image format: (" << imageFormat << ")" << std::endl;
	if (is_match(imageFormat, "l") || is_match(imageFormat, "r"))
	{
		return option::ImageFormat::l;
	}
	else if (is_match(imageFormat, "a"))
	{
		return option::ImageFormat::a;
	}
	else if (is_match(imageFormat, "la"))
	{
		return option::ImageFormat::la;
	}
	else if (is_match(imageFormat, "rgb"))
	{
		return option::ImageFormat::rgb;
	}
	else if (is_match(imageFormat, "rgba"))
	{
		return option::ImageFormat::rgba;
	}
	else if (is_match(imageFormat, "srgb"))
	{
		return option::ImageFormat::srgb;
	}
	else if (is_match(imageFormat, "srgba"))
	{
		return option::ImageFormat::srgba;
	}

	return option::ImageFormat::a;
}

void cur::Program::addTexture(std::string const & line, std::vector<cur::Texture> & textures, size_t lineIndex)
{
	std::cout << "Adding animation texture (" << line << ")" << std::endl;
	auto items = std::vector<std::string>();
	items.reserve(5);

	auto const END = std::end(line);
	auto current = std::begin(line);
	auto next = std::find_if(current, END, isSpacer);
	items.push_back(std::to_string(lineIndex));
	items.push_back(line.substr(0, std::distance(std::begin(line), next)));
	while (next < END)
	{
		current = std::find_if(next, END, isValidChar);
		next = std::find_if(current, END, isSpacer);
		items.push_back(line.substr(std::distance(std::begin(line), current), std::distance(current, next)));
	}

	if (items.size() == 5)
	{
		auto options = cur::Options(getBehavior(items.at(KEY_BEHAVIOR_X)),
									getBehavior(items.at(KEY_BEHAVIOR_Y)),
									getImageFormat(items.at(KEY_IMAGE_FORMAT)));

		textures.emplace_back(items.at(KEY_NAME),
							  items.at(KEY_PATH),
							  std::move(options));

		std::cout << "Successfully added animation texture" << std::endl;
	}
	else
	{	// texture line isn't formatted correctly
		std::cerr << "Error--line isn't formatted correctly: (" << line << ")" << std::endl;
	}
}

void cur::Program::addTexture(std::string const & line, std::vector<cur::Texture> & textures)
{
	//std::cout << "Texture line (" << line << ")" << std::endl;
	auto items = std::vector<std::string>();
	items.reserve(5);

	auto const END = std::end(line);
	auto current = std::begin(line);
	auto next = std::find_if(current, END, isSpacer);
	items.push_back(line.substr(0, std::distance(std::begin(line), next)));
	while (next < END)
	{
		current = std::find_if(next, END, isValidChar);
		next = std::find_if(current, END, isSpacer);
		items.push_back(line.substr(std::distance(std::begin(line), current), std::distance(current, next)));
	}

	if (items.size() == 5)
	{
		auto options = cur::Options(getBehavior(items.at(KEY_BEHAVIOR_X)),
									getBehavior(items.at(KEY_BEHAVIOR_Y)),
									getImageFormat(items.at(KEY_IMAGE_FORMAT)));

		textures.emplace_back(items.at(KEY_NAME),
							  items.at(KEY_PATH),
							  std::move(options));
	}
	else
	{	// texture line isn't formatted correctly
		std::cerr << "Error--line isn't formatted correctly: (" << line << ")" << std::endl;
	}
}

void cur::Program::addAnimationOption(std::string const & line, cur::Animation & animation)
{
	//std::cout << "Adding animation option: (" << line << ")" << std::endl;

	auto const END = std::end(line);
	auto const BEGIN = std::begin(line);

	auto current = std::begin(line);
	auto next = std::find_if(current, END, isSpacer);

	auto KEY = line.substr(0, std::distance(current, next));

	current = std::find_if(next, END, isValidChar);
	next = std::find_if(current, END, isSpacer);
	auto VALUE = line.substr(std::distance(BEGIN, current), std::distance(current, next));

	std::cout << "Adding animation option: (" << KEY << ") = (" << VALUE << ")" << std::endl;

	if (is_match(KEY, "do_at_end"))
	{
		if (is_match(VALUE, "reset"))
		{
			animation.endOfAnimation = cur::EndOfAnimation::reset;
		}
		else if (is_match(VALUE, "reverse"))
		{
			animation.endOfAnimation = cur::EndOfAnimation::reverse;
		}
		else if (is_match(VALUE, "stop"))
		{
			animation.endOfAnimation = cur::EndOfAnimation::stop;
		}
	}
	else if (is_match(KEY, "speed_default"))
	{
		animation.speedDefault = std::stod(VALUE);
	}
	else if (is_match(KEY, "speed_slow"))
	{
		animation.speedSlow = std::stod(VALUE);
	}
}

void cur::Program::addSound(std::string const & line, std::vector<cur::Sound> & sounds, cur::Sound::Group group)
{
	//std::cout << "Texture line (" << line << ")" << std::endl;
	auto items = std::vector<std::string>();
	items.reserve(2);

	auto const END = std::end(line);
	auto current = std::begin(line);
	auto next = std::find_if(current, END, isSpacer);
	items.push_back(line.substr(0, std::distance(std::begin(line), next)));
	while (next < END)
	{
		current = std::find_if(next, END, isValidChar);
		next = std::find_if(current, END, isSpacer);
		items.push_back(line.substr(std::distance(std::begin(line), current), std::distance(current, next)));
	}

	if (items.size() == 2)
	{
		sounds.emplace_back(items.at(KEY_NAME),
							items.at(KEY_PATH),
							group);
	}
	else
	{	// sound line isn't formatted correctly
		std::cerr << "Error--line isn't formatted correctly: (" << line << ")" << std::endl;
	}
}

void cur::Program::processLineAnimation(std::string const & line, Search & search, cur::Animation & animation, size_t lineIndex)
{
	//std::cout << "Line (" << line << ")" << std::endl;
	auto const BEGIN = std::begin(line);
	auto const END = std::end(line);

	auto firstCharacter = std::find_if(BEGIN, END, isValidChar);
	auto lastCharacter = std::find_if(firstCharacter, END, isSpacer);

	switch (search.stage)
	{
		case Stage::searchingForEndImage:
		{
			if (is_match(line.substr(std::distance(BEGIN, firstCharacter), std::distance(firstCharacter, lastCharacter)), "</image>"))
			{
				std::cout << "Found </image>" << std::endl;
				search.stage = Stage::none;
			}
			else
			{
				addTexture(line.substr(std::distance(BEGIN, firstCharacter)), animation.textures, lineIndex);
			}
			break;
		}
		case Stage::searchingForEndAnimation:
		{
			if (is_match(line.substr(std::distance(BEGIN, firstCharacter), std::distance(firstCharacter, lastCharacter)), "</options>"))
			{
				std::cout << "Found </options>" << std::endl;
				search.stage = Stage::none;
			}
			else
			{
				addAnimationOption(line.substr(std::distance(BEGIN, firstCharacter)), animation);
			}
			break;
		}
		default: {
			if (is_match(line.substr(std::distance(BEGIN, firstCharacter), std::distance(firstCharacter, lastCharacter)), "<image>"))
			{
				std::cout << "Found <image>" << std::endl;
				search.stage = Stage::searchingForEndImage;
			}
			else if (is_match(line.substr(std::distance(BEGIN, firstCharacter), std::distance(firstCharacter, lastCharacter)), "<options>"))
			{
				std::cout << "Found <options>" << std::endl;
				search.stage = Stage::searchingForEndAnimation;
			}
			break;
		}
	}
}

void cur::Program::addAnimation(std::string const & line, std::vector<cur::Sprite> & sprites)
{
	auto path = std::string("../text/anim/");

	auto const END = std::end(line);
	auto current = std::begin(line);
	auto next = std::find_if(current, END, isSpacer);

	auto const SPRITE_NAME = line.substr(0, std::distance(current, next));

	current = std::find_if(next, END, isValidChar);
	next = std::find_if(current, END, isSpacer);
	auto const ANIMATION_NAME = line.substr(std::distance(std::begin(line), current));
	path.append(ANIMATION_NAME);

	if (!is_match(path.substr(ANIMATION_NAME.length() - 4, 4), ".txt"))
	{
		path.append(".txt");
	}

	std::cout << "Adding animation: Sprite name (" << SPRITE_NAME << "), animation name (" << ANIMATION_NAME << "), line (" << line << ")" << std::endl;

	cur::Sprite * sprite = nullptr;
	auto it = std::begin(sprites);
	while (it < std::end(sprites))
	{
		if (is_match(it->name, SPRITE_NAME))
		{
			sprite = &*it;
			break;
		}
		it = std::next(it);
	}

	if (sprite == nullptr)
	{
		sprite = &sprites.emplace_back(SPRITE_NAME);
	}

	auto ifs = std::ifstream(path);
	if (ifs.is_open())
	{
		std::cout << "Opened file (" << path << ")" << std::endl;
		auto s = std::string();
		if (sprite != nullptr)
		{
			auto lineIndex = size_t{ 0 };
			auto found = false;
			for (auto const & a : sprite->animations)
			{
				if (is_match(a.name, ANIMATION_NAME))
				{
					found = true;
					break;
				}
			}
			if (!found)
			{
				auto & animation = sprite->animations.emplace_back(ANIMATION_NAME);
				auto search = Search();
				while (std::getline(ifs, s))
				{
					if (!s.empty())
					{
						++lineIndex;
						processLineAnimation(s, search, animation, lineIndex);
					}
				}
			}
		}

		std::cout << "Sprite (" << SPRITE_NAME << ") added animation (" << ANIMATION_NAME << ")" << std::endl;
		ifs.close();
	}
	else
	{
		std::cerr << "Couldn't read file (" << path << ")" << std::endl;
	}

	auto & c = sprite;
}

void cur::Program::processLine(std::string const & line, Search & search, cur::Scene & scene)
{
	//std::cout << "Line (" << line << ")" << std::endl;
	auto const BEGIN = std::begin(line);
	auto const END = std::end(line);

	auto firstCharacter = std::find_if(BEGIN, END, isValidChar);
	auto lastCharacter = std::find_if(firstCharacter, END, isSpacer);

	switch (search.stage)
	{
		case Stage::searchingForEndBgm:
		{
			if (is_match(line.substr(std::distance(BEGIN, firstCharacter), std::distance(firstCharacter, lastCharacter)), "</bgm>"))
			{
				std::cout << "Found </bgm>" << std::endl;
				search.stage = Stage::none;
			}
			else
			{
				addSound(line.substr(std::distance(BEGIN, firstCharacter)), scene.bgm, cur::Sound::Group::bgm);
			}
			break;
		}
		case Stage::searchingForEndSfx:
		{
			if (is_match(line.substr(std::distance(BEGIN, firstCharacter), std::distance(firstCharacter, lastCharacter)), "</sfx>"))
			{
				std::cout << "Found </sfx>" << std::endl;
				search.stage = Stage::none;
			}
			else
			{
				addSound(line.substr(std::distance(BEGIN, firstCharacter)), scene.sfx, cur::Sound::Group::sfx);
			}
			break;
		}
		case Stage::searchingForEndImage:
		{
			if (is_match(line.substr(std::distance(BEGIN, firstCharacter), std::distance(firstCharacter, lastCharacter)), "</image>"))
			{
				std::cout << "Found </image>" << std::endl;
				search.stage = Stage::none;
			}
			else
			{
				addTexture(line.substr(std::distance(BEGIN, firstCharacter)), scene.textures);
			}
			break;
		}
		case Stage::searchingForEndAnimation:
		{
			if (is_match(line.substr(std::distance(BEGIN, firstCharacter), std::distance(firstCharacter, lastCharacter)), "</sprite>"))
			{
				std::cout << "Found </sprite>" << std::endl;
				search.stage = Stage::none;
			}
			else
			{
				addAnimation(line.substr(std::distance(BEGIN, firstCharacter)), scene.sprites);
			}
			break;
		}
		default:
		{
			if (is_match(line.substr(std::distance(BEGIN, firstCharacter), std::distance(firstCharacter, lastCharacter)), "<image>"))
			{
				std::cout << "Found <image>" << std::endl;
				search.stage = Stage::searchingForEndImage;
			}
			else if (is_match(line.substr(std::distance(BEGIN, firstCharacter), std::distance(firstCharacter, lastCharacter)), "<sprite>"))
			{
				std::cout << "Found <sprite>" << std::endl;
				search.stage = Stage::searchingForEndAnimation;
			}
			else if (is_match(line.substr(std::distance(BEGIN, firstCharacter), std::distance(firstCharacter, lastCharacter)), "<bgm>"))
			{
				std::cout << "Found <bgm>" << std::endl;
				search.stage = Stage::searchingForEndBgm;
			}
			else if (is_match(line.substr(std::distance(BEGIN, firstCharacter), std::distance(firstCharacter, lastCharacter)), "<sfx>"))
			{
				std::cout << "Found <sfx>" << std::endl;
				search.stage = Stage::searchingForEndSfx;
			}
			break;
		}
	}
}

bool cur::Program::makeFileDirs(std::filesystem::path const & file)
{
	auto fullPath = std::string();
	if (!std::filesystem::exists(file.parent_path()))
	{
		std::cout << "Requested directory doesn't exist yet: " << file.parent_path().string().c_str() << std::endl;

		if (std::end(file) != std::begin(file))
		{
			auto dir = std::begin(file);

			while (std::next(dir) != std::end(file))
			{
				fullPath.append(dir->string()).append("/");
				if (!std::filesystem::exists(fullPath))
				{
					std::cout << "Directory doesn't exist, creating: " << fullPath.c_str() << std::endl;
					try
					{
						std::filesystem::create_directory(fullPath);
						std::cout << "Successfuly created directory: " << fullPath.c_str() << std::endl;
					}
					catch (std::filesystem::filesystem_error e)
					{
						std::cerr << "Failed to create directory: " << e.what() << std::endl;
						return false;
					}
				}
				else
				{
					std::cout << "Directory already exists: " << fullPath.c_str() << std::endl;
				}
				dir = std::next(dir);
			}
		}
	}
	else
	{
		std::cout << "Requested directory already exists: " << file.parent_path().string().c_str() << std::endl;
	}
	return true;
}

bool cur::Program::loadScenesText(std::filesystem::path const & path, cur::Scenes & scenes)
{
	std::cout << "Filename: " << path.filename().string() << "		" << path.string() << std::endl
		<< "-								-" << std::endl;

	auto line = std::string();
	auto ifs = std::ifstream(path);
	if (ifs.is_open())
	{
		auto const FILENAME = path.filename().string().substr(0, path.filename().string().size() - path.extension().string().size());
		auto & scene = scenes.scenes.emplace_back(FILENAME);
		auto search = Search();
		search.stage = Stage::none;
		while (std::getline(ifs, line))
		{
			if (!line.empty())
			{
				processLine(line, search, scene);
			}
		}
		ifs.close();

		std::cout << "Scene contains " << scene.textures.size() << " named textures, and "
			<< scene.sprites.size() << " sprites" << std::endl;

		return true;
	}
	else {
		std::cerr << "Couldn't read file" << std::endl;
	}

	return false;
}

bool cur::Program::loadScenes(std::filesystem::path const & path, cur::Scenes & scenes)
{
	auto result = bool{ false };
	auto ifs = std::ifstream(path, std::ios::binary, std::ios::in);

	if (ifs.is_open())
	{
		std::cout << "Opened archive--trying to load data into game" << std::endl;
		auto state = bitsery::quickDeserialization<bitsery::InputStreamAdapter>(ifs, scenes);

		assert(state.first == bitsery::ReaderError::NoError && state.second);
		std::cout << "Successfully loaded archive" << std::endl;
		result = true;
		ifs.close();
	}
	else
	{
		std::cerr << "Load failed -- unable to open file. Does it exist?" << std::endl;
		return false;
	}
	return false;
}

bool cur::Program::saveScenes(std::filesystem::path const & path, cur::Scenes const & scenes)
{
	auto result = bool{ false };

	makeFileDirs(path);

	auto ofs = std::ofstream(path, std::ios::binary | std::ios::trunc | std::ios::out);

	if (ofs.is_open())
	{
		std::cout << "Saving data list" << std::endl;
		auto ser = bitsery::Serializer<bitsery::OutputBufferedStreamAdapter>(ofs);
		ser.object(scenes);
		//flush to writer
		ser.adapter().flush();

		ofs.close();

		std::cout << "Save successful" << std::endl;
		return true;
	}
	else
	{
		std::cerr << "Save failed - output file is not open" << std::endl;
		return false;
	}

	return false;
}

void cur::Program::convertScenesText(cur::Scenes & scenes)
{
	auto textFiles = std::vector<std::filesystem::path>();
	if (std::filesystem::exists("../text/scene/"))
	{
		std::filesystem::directory_iterator files("../text/scene/");
		for (auto & f : files)
		{
			textFiles.push_back(f.path());
		}
	}
	else
	{
		std::cout << "../scenes_text/ doesn't exist" << std::endl;
	}

	for (auto & t : textFiles)
	{
		std::cout << std::endl << "Loading scenes text file " << t.string() << "..." << std::endl;
		auto success = loadScenesText(t, scenes);
		if (success)
		{
			std::cout << "Successfully loaded scenes text file" << std::endl;
		}
		else
		{
			std::cout << "Error reading scenes text file" << std::endl;
		}
	}

	std::cout << std::endl;
	assign_unique_index(scenes);
}

int cur::Program::now()
{
	std::cout << "Converting scene textures to binary data" << std::endl;
#ifdef ARCH_X64
	auto const FILENAME = std::filesystem::path("../data/scene/textures.bin");
#elif defined ARCH_X86
	auto const FILENAME = std::filesystem::path("../data_x86/scene/textures.bin");
#endif // ARCH_X64
	auto scenes = cur::Scenes();
	convertScenesText(scenes);
	saveScenes(FILENAME, scenes);

	std::cout << std::endl << "Press any key to exit..." << std::endl;
	for (auto line = std::string(); std::getline(std::cin, line);)
	{
		break;
	}
	return EXIT_SUCCESS;
}
