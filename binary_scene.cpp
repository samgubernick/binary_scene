
#include "scenes.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

namespace {
	constexpr auto const MATCH = int{ 0 };
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

		std::cout << std::endl << "Filename: " << path.filename().string() << "		" << path.string() << std::endl
			<< "-								-" << std::endl;

		auto const FILENAME = path.filename().string().substr(0, path.filename().string().size() - path.extension().string().size());
		auto & scene = scenes.scenes.emplace_back(FILENAME);
		while (std::getline(ifs, line)) {
			//std::cout << "Line: " << line << std::endl;

			auto startOfPath = line.find("	");
			auto const NAME = line.substr(0, startOfPath);
			while (true) {
				auto i = line.find("	", startOfPath);
				if (startOfPath < i) {
					startOfPath = i;
				}
				else {
					break;
				}
			}
			++startOfPath;
			auto const PATH = line.substr(startOfPath, line.size() - startOfPath);
			std::cout << NAME << "			" <<  PATH << std::endl;

			scene.textures.emplace_back(NAME, PATH);
		}
		ifs.close();

		std::cout << std::endl;
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
		catch (std::exception e) {	// why isn't boost::exception catching? Maybe I have to build it?
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
		catch (std::exception e) {
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
}

int main()
{
	std::cout << "Hello CMake." << std::endl;
#ifdef ARCH_X64
	auto const FILENAME = std::filesystem::path("../data/scenes_x64.bin");
#elif defined ARCH_X86
	auto const FILENAME = std::filesystem::path("../data/scenes_x86.bin");
#endif // ARCH_X64
	auto scenes = Scenes();
	convertScenesText(scenes);
	saveScenes(FILENAME, scenes);

	auto i = int{ 0 };
	std::cin >> i;
	return EXIT_SUCCESS;
}
