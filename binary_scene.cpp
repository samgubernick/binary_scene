
#include "scenes.hpp"

#include "program.hpp"

namespace cur = sam::binary_data;

#ifdef SAM_IGNORE
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

namespace {
	constexpr auto const MATCH = int{ 0 };

	constexpr auto const KEY_NAME = size_t{ 0 };
	constexpr auto const KEY_PATH = size_t{ 1 };
	constexpr auto const KEY_IMAGE_FORMAT = size_t{ 2 };
	constexpr auto const KEY_BEHAVIOR_X = size_t{ 3 };
	constexpr auto const KEY_BEHAVIOR_Y = size_t{ 4 };
}

enum class Stage {
	none,
	searchingForEndAnimation,
	searchingForEndBgm,
	searchingForEndImage,
	searchingForEndSfx,
};

struct Search {
	Stage stage;

	Search()
		: stage(Stage::none) {

	}
};

bool matches(std::string const & a, std::string const & b) {
	return a.compare(b) == MATCH;
}

bool matches(char a, char b) {
	return a == b;
}

bool isSpacer(char const & c) {
	if (matches(c, '\t')
		|| matches(c, ':')
		|| matches(c, '\n')) {
		return true;
	}

	return false;
}

bool isValidChar(char const & c) {
	if (matches(c, '\t')
		|| matches(c, ':')
		|| matches(c, '\n')) {
		return false;
	}

	return true;
}

cur::option::Behavior getBehavior(std::string const & behavior) {
	//std::cout << "Behavior: (" << behavior << ")" << std::endl;
	if (matches(behavior, "mirror")) {
		return option::Behavior::mirror;
	} else if (matches(behavior, "stretch")) {
		return option::Behavior::stretch;
	}
	else if (matches(behavior, "repeat")) {
		return option::Behavior::repeat;
	}
	else if (matches(behavior, "center")) {
		return option::Behavior::center;
	}

	return option::Behavior::repeat;
}

cur::option::ImageFormat getImageFormat(std::string & imageFormat) {
	//std::cout << "Image format: (" << imageFormat << ")" << std::endl;
	if (matches(imageFormat, "l") || matches(imageFormat, "r")) {
		return option::ImageFormat::l;
	} else if (matches(imageFormat, "a")) {
		return option::ImageFormat::a;
	}
	else if (matches(imageFormat, "la")) {
		return option::ImageFormat::la;
	}
	else if (matches(imageFormat, "rgb")) {
		return option::ImageFormat::rgb;
	}
	else if (matches(imageFormat, "rgba")) {
		return option::ImageFormat::rgba;
	}
	else if (matches(imageFormat, "srgb")) {
		return option::ImageFormat::srgb;
	}
	else if (matches(imageFormat, "srgba")) {
		return option::ImageFormat::srgba;
	}

	return option::ImageFormat::a;
}

void assignUniqueIndex(cur::Scenes & scenes) {
	auto id = size_t{ 0 };

	for (auto & s : scenes.scenes) {
		for (auto & t : s.textures) {
			if (t.id == 0) {
				auto found = false;
				for (auto & otherS : scenes.scenes) {
					for (auto & otherT : otherS.textures) {
						if (&t != &otherT && matches(t.hash, otherT.hash)) {
							found = true;
							if (otherT.id == 0) {
								++id;
								t.id = id;
								otherT.id = id;
							}
							else {
								t.id = otherT.id;
							}
							break;
						}

						if (found) {
							break;
						}
					}
					if (found) {
						break;
					}

					for (auto & otherSprite : otherS.sprites) {
						for (auto & otherAnimation : otherSprite.animations) {
							for (auto & otherT : otherAnimation.textures) {
								if (&t != &otherT && matches(t.hash, otherT.hash)) {
									found = true;
									if (otherT.id == 0) {
										++id;
										t.id = id;
										otherT.id = id;
									}
									else {
										t.id = otherT.id;
									}
									break;
								}
							}
							if (found) {
								break;
							}
						}
						if (found) {
							break;
						}
					}
					if (found) {
						break;
					}
				}
				if (!found) {
					++id;
					t.id = id;
				}
			}
		}

		for (auto & sprite : s.sprites) {
			for (auto & animation : sprite.animations) {
				for (auto & t : animation.textures) {
					auto found = false;
					for (auto & otherS : scenes.scenes) {
						for (auto & otherT : otherS.textures) {
							if (&t != &otherT && matches(t.hash, otherT.hash)) {
								found = true;
								if (otherT.id == 0) {
									++id;
									t.id = id;
									otherT.id = id;
								}
								else {
									t.id = otherT.id;
								}
								break;
							}
						}

						if (found) {
							break;
						}

						for (auto & otherSprite : otherS.sprites) {
							for (auto & otherAnimation : otherSprite.animations) {
								for (auto & otherT : otherAnimation.textures) {
									if (&t != &otherT && matches(t.hash, otherT.hash)) {
										found = true;
										if (otherT.id == 0) {
											++id;
											t.id = id;
											otherT.id = id;
										}
										else {
											t.id = otherT.id;
										}
										break;
									}
								}
								if (found) {
									break;
								}
							}
							if (found) {
								break;
							}
						}
					}
					if (!found) {
						++id;
						t.id = id;
					}
				}
			}
		}

		for (auto & t : s.bgm) {
			if (t.id == 0) {
				auto found = false;
				for (auto & otherS : scenes.scenes) {
					for (auto & otherT : otherS.bgm) {
						if (&t != &otherT && matches(t.hash, otherT.hash)) {
							found = true;
							if (otherT.id == 0) {
								++id;
								t.id = id;
								otherT.id = id;
							}
							else {
								t.id = otherT.id;
							}
							break;
						}

						if (found) {
							break;
						}
					}
					if (found) {
						break;
					}
				}
				if (!found) {
					++id;
					t.id = id;
				}
			}
		}

		for (auto & t : s.sfx) {
			if (t.id == 0) {
				auto found = false;
				for (auto & otherS : scenes.scenes) {
					for (auto & otherT : otherS.sfx) {
						if (&t != &otherT && matches(t.hash, otherT.hash)) {
							found = true;
							if (otherT.id == 0) {
								++id;
								t.id = id;
								otherT.id = id;
							}
							else {
								t.id = otherT.id;
							}
							break;
						}

						if (found) {
							break;
						}
					}
					if (found) {
						break;
					}
				}
				if (!found) {
					++id;
					t.id = id;
				}
			}
		}
	}

	std::cout << "Assigned " << id << " ids to textures in " << scenes.scenes.size() << " scenes" << std::endl;
}

void addTexture(std::string const & line, std::vector<cur::Texture> & textures, size_t index) {
	std::cout << "Adding animation texture (" << line << ")" << std::endl;
	auto items = std::vector<std::string>();
	items.reserve(5);

	auto const END = std::end(line);
	auto current = std::begin(line);
	auto next = std::find_if(current, END, isSpacer);
	items.push_back(std::to_string(index));
	items.push_back(line.substr(0, std::distance(std::begin(line), next)));
	while (next < END) {
		current = std::find_if(next, END, isValidChar);
		next = std::find_if(current, END, isSpacer);
		items.push_back(line.substr(std::distance(std::begin(line), current), std::distance(current, next)));
	}

	if (items.size() == 5) {
		auto options = cur::Options(getBehavior(items.at(KEY_BEHAVIOR_X)),
									getBehavior(items.at(KEY_BEHAVIOR_Y)),
									getImageFormat(items.at(KEY_IMAGE_FORMAT)));

		textures.emplace_back(items.at(KEY_NAME),
							  items.at(KEY_PATH),
							  std::move(options));

		std::cout << "Successfully added animation texture" << std::endl;
	}
	else {	// texture line isn't formatted correctly
		std::cerr << "Error--line isn't formatted correctly: (" << line << ")" << std::endl;
	}
}

void addTexture(std::string const & line, std::vector<cur::Texture> & textures) {
	//std::cout << "Texture line (" << line << ")" << std::endl;
	auto items = std::vector<std::string>();
	items.reserve(5);

	auto const END = std::end(line);
	auto current = std::begin(line);
	auto next = std::find_if(current, END, isSpacer);
	items.push_back(line.substr(0, std::distance(std::begin(line), next)));
	while (next < END) {
		current = std::find_if(next, END, isValidChar);
		next = std::find_if(current, END, isSpacer);
		items.push_back(line.substr(std::distance(std::begin(line), current), std::distance(current, next)));
	}

	if (items.size() == 5) {
		auto options = cur::Options(getBehavior(items.at(KEY_BEHAVIOR_X)),
									getBehavior(items.at(KEY_BEHAVIOR_Y)),
									getImageFormat(items.at(KEY_IMAGE_FORMAT)));

		textures.emplace_back(items.at(KEY_NAME),
							  items.at(KEY_PATH),
							  std::move(options));
	}
	else {	// texture line isn't formatted correctly
		std::cerr << "Error--line isn't formatted correctly: (" << line << ")" << std::endl;
	}
}

void addAnimationOption(std::string const & line, cur::Animation & animation) {
	//std::cout << "Adding animation option: (" << line << ")" << std::endl;

	auto const END = std::end(line);
	auto const BEGIN = std::begin(line);

	auto current = BEGIN;
	auto next = std::find_if(current, END, isSpacer);

	auto KEY = line.substr(0, std::distance(current, next));

	current = std::find_if(next, END, isValidChar);
	next = std::find_if(current, END, isSpacer);
	auto VALUE = line.substr(std::distance(BEGIN, current), std::distance(current, next));

	std::cout << "Adding animation option: (" << KEY << ") = (" << VALUE << ")" << std::endl;

	if (matches(KEY, "do_at_end")) {
		if (matches(VALUE, "reset")) {
			animation.endOfAnimation = cur::EndOfAnimation::reset;
		} else if (matches(VALUE, "reverse")) {
			animation.endOfAnimation = cur::EndOfAnimation::reverse;
		} else if (matches(VALUE, "stop")) {
			animation.endOfAnimation = cur::EndOfAnimation::stop;
		}
	}
	else if (matches(KEY, "speed_default")) {
		animation.speedDefault = std::stod(VALUE);
	}
	else if (matches(KEY, "speed_slow")) {
		animation.speedSlow = std::stod(VALUE);
	}
}

void addSound(std::string const & line, std::vector<cur::Sound> & sounds, cur::Sound::Group group) {
	//std::cout << "Texture line (" << line << ")" << std::endl;
	auto items = std::vector<std::string>();
	items.reserve(2);

	auto const END = std::end(line);
	auto current = std::begin(line);
	auto next = std::find_if(current, END, isSpacer);
	items.push_back(line.substr(0, std::distance(std::begin(line), next)));
	while (next < END) {
		current = std::find_if(next, END, isValidChar);
		next = std::find_if(current, END, isSpacer);
		items.push_back(line.substr(std::distance(std::begin(line), current), std::distance(current, next)));
	}

	if (items.size() == 2) {
		sounds.emplace_back(items.at(KEY_NAME),
							items.at(KEY_PATH),
							group);
	}
	else {	// sound line isn't formatted correctly
		std::cerr << "Error--line isn't formatted correctly: (" << line << ")" << std::endl;
	}
}

void processLineAnimation(std::string const & line, Search & search, cur::Animation & animation, size_t index) {
	//std::cout << "Line (" << line << ")" << std::endl;
	auto const BEGIN = std::begin(line);
	auto const END = std::end(line);

	auto firstCharacter = std::find_if(BEGIN, END, isValidChar);
	auto lastCharacter = std::find_if(firstCharacter, END, isSpacer);

	switch (search.stage) {
		case Stage::searchingForEndImage: {
			if (matches(line.substr(std::distance(BEGIN, firstCharacter), std::distance(firstCharacter, lastCharacter)), "</image>")) {
				std::cout << "Found </image>" << std::endl;
				search.stage = Stage::none;
			}
			else {
				addTexture(line.substr(std::distance(BEGIN, firstCharacter)), animation.textures, index);
			}
			break;
		}
		case Stage::searchingForEndAnimation: {
			if (matches(line.substr(std::distance(BEGIN, firstCharacter), std::distance(firstCharacter, lastCharacter)), "</options>")) {
				std::cout << "Found </options>" << std::endl;
				search.stage = Stage::none;
			}
			else {
				addAnimationOption(line.substr(std::distance(BEGIN, firstCharacter)), animation);
			}
			break;
		}
		default: {
			if (matches(line.substr(std::distance(BEGIN, firstCharacter), std::distance(firstCharacter, lastCharacter)), "<image>")) {
				std::cout << "Found <image>" << std::endl;
				search.stage = Stage::searchingForEndImage;
			}
			else if (matches(line.substr(std::distance(BEGIN, firstCharacter), std::distance(firstCharacter, lastCharacter)), "<options>")) {
				std::cout << "Found <options>" << std::endl;
				search.stage = Stage::searchingForEndAnimation;
			}
			break;
		}
	}
}

void addAnimation(std::string const & line, std::vector<cur::Sprite> & sprites) {
	auto path = std::string("../text/anim/");

	auto const END = std::end(line);
	auto current = std::begin(line);
	auto next = std::find_if(current, END, isSpacer);
	
	auto const SPRITE_NAME = line.substr(0, std::distance(current, next));

	current = std::find_if(next, END, isValidChar);
	next = std::find_if(current, END, isSpacer);
	auto const ANIMATION_NAME = line.substr(std::distance(std::begin(line), current));
	path.append(ANIMATION_NAME);

	if (!matches(path.substr(ANIMATION_NAME.length() - 4, 4), ".txt")) {
		path.append(".txt");
	}

	std::cout << "Adding animation: Sprite name (" << SPRITE_NAME << "), animation name (" << ANIMATION_NAME << "), line (" << line << ")" << std::endl;

	cur::Sprite * sprite = nullptr;
	auto it = std::begin(sprites);
	while (it < std::end(sprites)) {
		if (matches(it->name, SPRITE_NAME)) {
			sprite = &*it;
			break;
		}
		it = std::next(it);
	}

	if (sprite == nullptr) {								
		sprite = &sprites.emplace_back(SPRITE_NAME);
	}

	auto ifs = std::ifstream(path);
	if (ifs.is_open()) {
		std::cout << "Opened file (" << path << ")" << std::endl;
		auto s = std::string();
		if (sprite != nullptr) {
			auto index = size_t{ 0 };
			auto found = false;
			for (auto const & a : sprite->animations) {
				if (matches(a.name, ANIMATION_NAME)) {
					found = true;
						break;
				}
			}
			if (!found) {
				auto & animation = sprite->animations.emplace_back(ANIMATION_NAME);
				auto search = Search();
				while (std::getline(ifs, s)) {
					if (!s.empty()) {
						++index;
						processLineAnimation(s, search, animation, index);
					}
				}
			}
		}

		std::cout << "Sprite (" << SPRITE_NAME << ") added animation (" << ANIMATION_NAME << ")" << std::endl;
		ifs.close();
	}
	else {
		std::cerr << "Couldn't read file (" << path << ")" << std::endl;
	}
}

void processLine(std::string const & line, Search & search, cur::Scene & scene) {
	//std::cout << "Line (" << line << ")" << std::endl;
	auto const BEGIN = std::begin(line);
	auto const END = std::end(line);

	auto firstCharacter = std::find_if(BEGIN, END, isValidChar);
	auto lastCharacter = std::find_if(firstCharacter, END, isSpacer);

	switch (search.stage) {
		case Stage::searchingForEndBgm: {
			if (matches(line.substr(std::distance(BEGIN, firstCharacter), std::distance(firstCharacter, lastCharacter)), "</bgm>")) {
				std::cout << "Found </bgm>" << std::endl;
				search.stage = Stage::none;
			}
			else {
				addSound(line.substr(std::distance(BEGIN, firstCharacter)), scene.bgm, cur::Sound::Group::bgm);
			}
			break;
		}
		case Stage::searchingForEndSfx: {
			if (matches(line.substr(std::distance(BEGIN, firstCharacter), std::distance(firstCharacter, lastCharacter)), "</sfx>")) {
				std::cout << "Found </sfx>" << std::endl;
				search.stage = Stage::none;
			}
			else {
				addSound(line.substr(std::distance(BEGIN, firstCharacter)), scene.sfx, cur::Sound::Group::sfx);
			}
			break;
		}
		case Stage::searchingForEndImage: {
			if (matches(line.substr(std::distance(BEGIN, firstCharacter), std::distance(firstCharacter, lastCharacter)), "</image>")) {
				std::cout << "Found </image>" << std::endl;
				search.stage = Stage::none;
			}
			else {
				addTexture(line.substr(std::distance(BEGIN, firstCharacter)), scene.textures);
			}
			break;
		}
		case Stage::searchingForEndAnimation: {
			if (matches(line.substr(std::distance(BEGIN, firstCharacter), std::distance(firstCharacter, lastCharacter)), "</sprite>")) {
				std::cout << "Found </sprite>" << std::endl;
				search.stage = Stage::none;
			}
			else {
				addAnimation(line.substr(std::distance(BEGIN, firstCharacter)), scene.sprites);
			}
			break;
		}
		default: {
			if (matches(line.substr(std::distance(BEGIN, firstCharacter), std::distance(firstCharacter, lastCharacter)), "<image>")) {
				std::cout << "Found <image>" << std::endl;
				search.stage = Stage::searchingForEndImage;
			}
			else if (matches(line.substr(std::distance(BEGIN, firstCharacter), std::distance(firstCharacter, lastCharacter)), "<sprite>")) {
				std::cout << "Found <sprite>" << std::endl;
				search.stage = Stage::searchingForEndAnimation;
			}
			else if (matches(line.substr(std::distance(BEGIN, firstCharacter), std::distance(firstCharacter, lastCharacter)), "<bgm>")) {
				std::cout << "Found <bgm>" << std::endl;
				search.stage = Stage::searchingForEndBgm;
			}
			else if (matches(line.substr(std::distance(BEGIN, firstCharacter), std::distance(firstCharacter, lastCharacter)), "<sfx>")) {
				std::cout << "Found <sfx>" << std::endl;
				search.stage = Stage::searchingForEndSfx;
			}
			break;
		}
	}
}

bool makeFileDirs(std::filesystem::path const & file) {
	auto fullPath = std::string();
	if (!std::filesystem::exists(file.parent_path())) {
		std::cout << "Requested directory doesn't exist yet: " << file.parent_path().string().c_str() << std::endl;

		if (std::end(file) != std::begin(file)) {
			auto dir = std::begin(file);

			while (std::next(dir) != std::end(file)) {
				fullPath.append(dir->string()).append("/");
				if (!std::filesystem::exists(fullPath)) {
					std::cout << "Directory doesn't exist, creating: " << fullPath.c_str() << std::endl;
					try {
						std::filesystem::create_directory(fullPath);
						std::cout << "Successfuly created directory: " << fullPath.c_str() << std::endl;
					}
					catch (std::filesystem::filesystem_error e) {
						std::cerr << "Failed to create directory: " << e.what() << std::endl;
						return false;
					}
				}
				else {
					std::cout << "Directory already exists: " << fullPath.c_str() << std::endl;
				}
				dir = std::next(dir);
			}
		}
	}
	else {
		std::cout << "Requested directory already exists: " << file.parent_path().string().c_str() << std::endl;
	}
	return true;
}

bool loadScenesText(std::filesystem::path const & path, cur::Scenes & scenes) {
	std::cout << "Filename: " << path.filename().string() << "		" << path.string() << std::endl
		<< "-								-" << std::endl;

	auto line = std::string();
	auto ifs = std::ifstream(path);
	if (ifs.is_open()) {
		auto const FILENAME = path.filename().string().substr(0, path.filename().string().size() - path.extension().string().size());
		auto & scene = scenes.scenes.emplace_back(FILENAME);
		auto search = Search();
		search.stage = Stage::none;
		while (std::getline(ifs, line)) {
			if (!line.empty()) {
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

bool loadScenes(std::filesystem::path const & path, cur::Scenes & scenes) {
	auto result = bool{ false };
	auto ifs = std::ifstream(path, std::ios::binary);

	if (ifs.is_open()) {
		try {
			std::cout << "Trying to open Boost archive" << std::endl;
			auto ia = boost::archive::binary_iarchive(ifs);

			std::cout << "Opened archive--trying to load data into game" << std::endl;
			ia >> scenes;

			std::cout << "Successfully loaded archive" << std::endl;
			result = true;
		}
		catch (boost::archive::archive_exception e) {
			std::cerr << "Load exception: " << e.what() << std::endl;
			std::cerr << "Unknown file format" << std::endl;

			result = false;
		}
		catch (boost::exception & e) {
			e;
			std::cerr << "Unknown file format" << std::endl;

			result = false;
		}
		ifs.close();
	}
	else {
		std::cerr << "Can't open file--does it exist?" << std::endl;
		result = false;
	}

	if (result) {
		std::cout << "Load successful" << std::endl;
	}
	else {
		std::cerr << "Load failed" << std::endl;
	}
	return result;
}

bool saveScenes(std::filesystem::path const & path, cur::Scenes const & scenes) {
	auto result = bool{ false };

	makeFileDirs(path);

	auto ofs = std::ofstream(path, std::ios::binary);

	if (ofs.is_open()) {
		try {
			auto oa = boost::archive::binary_oarchive(ofs);
			oa << scenes;
			std::cout << "Saving data list" << std::endl;
			result = true;
		}
		catch (boost::archive::archive_exception e) {
			std::cerr << "Error: " << e.what() << std::endl;
			result = false;
		}
		ofs.close();
	}
	else {
		std::cerr << "Output file is not open" << std::endl;
		result = false;
	}

	if (result) {
		std::cout << "Save successful" << std::endl;
	}
	else {
		std::cerr << "Save failed" << std::endl;
	}

	return result;
}

void convertScenesText(cur::Scenes & scenes) {
	auto textFiles = std::vector<std::filesystem::path>();
	if (std::filesystem::exists("../text/scene/")) {
		std::filesystem::directory_iterator files("../text/scene/");
		for (auto & f : files) {
			textFiles.push_back(f.path());
		}
	}
	else {
		std::cout << "../scenes_text/ doesn't exist" << std::endl;
	}

	for (auto & t : textFiles) {
		std::cout << std::endl << "Loading scenes text file " << t.string() << "..." << std::endl;
		auto success = loadScenesText(t, scenes);
		if (success) {
			std::cout << "Successfully loaded scenes text file" << std::endl;
		}
		else {
			std::cout << "Error reading scenes text file" << std::endl;
		}
	}

	std::cout << std::endl;
	assignUniqueIndex(scenes);
}

int main()
{
	std::cout << "Converting scene textures to binary data" << std::endl;
#ifdef ARCH_X64
	auto const FILENAME = std::filesystem::path("../data_x64/scene/textures.bin");
#elif defined ARCH_X86
	auto const FILENAME = std::filesystem::path("../data_x86/scene/textures.bin");
#endif // ARCH_X64
	auto scenes = cur::Scenes();
	convertScenesText(scenes);
	saveScenes(FILENAME, scenes);

	std::cout << std::endl << "Press any key to exit..." << std::endl;
	for (auto line = std::string(); std::getline(std::cin, line);) {
		break;
	}
	return EXIT_SUCCESS;
}
#endif // SAM_IGNORE

int main()
{
	auto program = cur::Program();
	return program.now();
}
