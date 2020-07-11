
#include "scenes.hpp"

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

option::Behavior getBehavior(std::string const & behavior) {
	//std::cout << "Behavior: (" << behavior << ")" << std::endl;
	if (behavior.compare("mirror") == MATCH) {
		return option::Behavior::mirror;
	} else if (behavior.compare("stretch") == MATCH) {
		return option::Behavior::stretch;
	}
	else if (behavior.compare("repeat") == MATCH) {
		return option::Behavior::repeat;
	}

	return option::Behavior::repeat;
}

option::ImageFormat getImageFormat(std::string & imageFormat) {
	//std::cout << "Image format: (" << imageFormat << ")" << std::endl;
	if (imageFormat.compare("l") == MATCH) {
		return option::ImageFormat::l;
	} else if (imageFormat.compare("a") == MATCH) {
		return option::ImageFormat::a;
	}
	else if (imageFormat.compare("la") == MATCH) {
		return option::ImageFormat::la;
	}
	else if (imageFormat.compare("rgb") == MATCH) {
		return option::ImageFormat::rgb;
	}
	else if (imageFormat.compare("rgba") == MATCH) {
		return option::ImageFormat::rgba;
	}
	else if (imageFormat.compare("srgb") == MATCH) {
		return option::ImageFormat::srgb;
	}
	else if (imageFormat.compare("srgba") == MATCH) {
		return option::ImageFormat::srgba;
	}

	return option::ImageFormat::a;
}

void assignUniqueIndex(Scenes & scenes) {
	auto id = size_t{ 0 };

	for (auto & s : scenes.scenes) {
		for (auto & t : s.textures) {

			auto found = false;
			for (auto & otherS : scenes.scenes) {
				for (auto & otherT : otherS.textures) {
					if (&t != &otherT && t.hash.compare(otherT.hash) == MATCH) {
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
			if (!found) {
				++id;
				t.id = id;
			}
		}
	}

	std::cout << "Assigned " << id << " ids to textures in " << scenes.scenes.size() << " scenes" << std::endl;
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

bool loadScenesText(std::filesystem::path const & path, Scenes & scenes) {
	auto line = std::string();
	auto ifs = std::ifstream(path);
	if (ifs.is_open()) {
		std::getline(ifs, line);
		if (line.compare("plaintext") != MATCH) {
			std::cerr << "Opened file, but the first line isn't 'plaintext'" << std::endl;
			return false;
		}

		std::cout << "Filename: " << path.filename().string() << "		" << path.string() << std::endl
			<< "-								-" << std::endl;

		auto const FILENAME = path.filename().string().substr(0, path.filename().string().size() - path.extension().string().size());
		auto & scene = scenes.scenes.emplace_back(FILENAME);
		while (std::getline(ifs, line)) {
			if (!line.empty()) {
				auto items = std::vector<std::string>();
				items.reserve(5);

				auto const END = std::end(line);
				auto current = std::begin(line);
				auto next = std::find(current, END, '\t');
				items.push_back(line.substr(0, std::distance(std::begin(line), next)));
				while (next < END) {
					current = next + 1;
					next = std::find(current, END, '\t');
					items.push_back(line.substr(std::distance(std::begin(line), current), std::distance(current, next)));
				}

				if (items.size() == 5) {

					auto options = Options(getBehavior(items.at(KEY_BEHAVIOR_X)),
										   getBehavior(items.at(KEY_BEHAVIOR_Y)),
										   getImageFormat(items.at(KEY_IMAGE_FORMAT)));

					auto & texture = scene.textures.emplace_back(items.at(KEY_NAME),
																 items.at(KEY_PATH),
																 std::move(options));
				}
				else {	// texture line isn't formatted correctly
					std::cerr << "Error--line isn't formatted correctly: (" << line << ")" << std::endl;
				}
			}
		}
		ifs.close();

		std::cout << "Scene contains " << scene.textures.size() << " named textures" << std::endl;

		return true;
	}
	else {
		std::cerr << "Couldn't read file" << std::endl;
	}

	return false;
}

bool loadScenes(std::filesystem::path const & path, Scenes & scenes) {
	auto result = bool{ false };
	auto ifs = std::ifstream(path);

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

bool saveScenes(std::filesystem::path const & path, Scenes const & scenes) {
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

void convertScenesText(Scenes & scenes) {
	auto textFiles = std::vector<std::filesystem::path>();
	if (std::filesystem::exists("../scenes_text/")) {
		std::filesystem::directory_iterator files("../scenes_text/");
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
	auto scenes = Scenes();
	convertScenesText(scenes);
	saveScenes(FILENAME, scenes);

	std::cout << std::endl << "Press any key to exit..." << std::endl;
	for (auto line = std::string(); std::getline(std::cin, line);) {
		break;
	}
	return EXIT_SUCCESS;
}
