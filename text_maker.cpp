
#include "text_maker.hpp"

#include "assign_unique_index.hpp"
#include "get_text_id.hpp"
#include "is_match.hpp"

#include "bitsery/adapter/stream.h"
#include "bitsery/bitsery.h"
#include "bitsery/traits/vector.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

namespace sam::binary_data {
namespace
{
constexpr auto const PATH_STRINGS = "../../../../kurt/text/strings/";
constexpr auto const KEY_NAME = size_t{0};
constexpr auto const KEY_FACE_NAME = size_t{1};
constexpr auto const KEY_FACE_SIZE = size_t{2};
constexpr auto const KEY_TEXT = size_t{3};
constexpr auto const KEY_LANGUAGE_NAME = size_t{0};
constexpr auto const KEY_LANGUAGE_TEXT = size_t{1};

auto isSpacer(char const & c)
{
	if (is_match(c, '\t')
		|| is_match(c, ':')
		|| is_match(c, '\n'))
	{
		return true;
	}

	return false;
}

auto isValidChar(char const & c)
{
	if (is_match(c, '\t')
		|| is_match(c, ':')
		|| is_match(c, '\n')
		|| is_match(c, ' '))
	{
		return false;
	}

	return true;
}

auto makeFileDirs(std::filesystem::path const & file) -> bool
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
						std::cout << "Successfully created directory: " << fullPath.c_str() << std::endl;
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
}

TextMaker::TextMaker()
{ }

auto TextMaker::processStrings() -> int
{
	std::cout << "Converting strings to binary data" << std::endl;
	auto outputFilename = std::string();
#ifdef ARCH_X64
	auto const FILENAME = std::filesystem::path("../data/languages.bin");
#elif defined ARCH_X86
	auto const FILENAME = std::filesystem::path("../data_x86/languages.bin");
#endif // ARCH_X64
	auto languages = Languages();
	convertStrings(languages);
	std::cout << "Enums:" << std::endl << std::endl;
	std::cout << "None," << std::endl;
	for (auto const & s : languages.list.front().strings)
	{
		auto correctedName = std::string{s.name};
		correctedName.front() = std::toupper(correctedName.front());
		std::cout << correctedName << "," << std::endl;
	}
	std::cout << std::endl << "Enum to string converter:" << std::endl;
	for (auto const & s : languages.list.front().strings)
	{
		auto correctedName = std::string{s.name};
		correctedName.front() = std::toupper(correctedName.front());
		std::cout << "if (name == \"" << s.name << "\") return Id::" << correctedName << "; " << std::endl;
	}
	std::cout << "else return Id::None;" << std::endl;
	std::cout << std::endl;
	save(FILENAME, languages);

	return EXIT_SUCCESS;
}

auto TextMaker::convertStrings(Languages & languages) -> void
{
	if (std::filesystem::exists(PATH_STRINGS))
	{
		auto files = std::filesystem::directory_iterator(PATH_STRINGS);
		for (auto & f : files)
		{
			std::cout << "File: " << f.path().string() << std::endl;
			if (f.path().filename().compare("languages.txt") == 0)
			{
				std::cout << "Reading the languages file" << std::endl;
				std::cout << "Filename: " << f.path().filename().string() << std::endl
					<< "-								-" << std::endl;

				languages = loadLanguagesFile(f);
			}
		}

		files = std::filesystem::directory_iterator(PATH_STRINGS);
		for (auto & language : languages.list)
		{
			std::cout << "Current language: " << language.name << std::endl;
			auto languageFilename = std::string(language.name).append(".txt");
			for (auto & f : files)
			{
				if (f.path().filename().compare(languageFilename) == 0)
				{
					std::cout << "Found language file: " << language.name << ".txt (\"" << language.text << "\")" << std::endl;
					loadLanguageFiles(f, language);
				}
			}
		}
	}
	else
	{
		std::cout << "Path \"" << PATH_STRINGS << "\" doesn't exist" << std::endl;
	}
	std::cout << std::endl;
}

auto TextMaker::processLanguageLine(Languages & languages, std::string const & line) -> void
{
	if (!line.empty())
	{
		std::cout << "Line: " << line << std::endl;

		auto const BEGIN = std::begin(line);
		auto const END = std::end(line);

		auto firstCharacter = std::find_if(BEGIN, END, isValidChar);
		auto lastCharacter = std::find_if(firstCharacter, END, isSpacer);

		addLanguage(languages, line.substr(std::distance(BEGIN, firstCharacter)));
	}
}

auto TextMaker::processStringLine(std::vector<String> & strings, std::string const & line) -> void
{
	if (!line.empty())
	{
		//std::cout << "Line: " << line << std::endl;

		auto const BEGIN = std::begin(line);
		auto const END = std::end(line);

		auto firstCharacter = std::find_if(BEGIN, END, isValidChar);
		auto lastCharacter = std::find_if(firstCharacter, END, isSpacer);

		if (firstCharacter < END && (*firstCharacter) != '<')
		{
			addString(strings, line.substr(std::distance(BEGIN, firstCharacter)));
		}
	}
}

auto TextMaker::loadLanguageFiles(std::filesystem::path const & filepath, Language & language) -> void
{
	std::cout << "Loading strings file from " << filepath << std::endl;
	if (std::filesystem::exists(filepath.string()))
	{
		auto ifs = std::ifstream(filepath);
		auto line = std::string();
		if (ifs.is_open())
		{
			std::cout << "---------" << line << std::endl;
			while (std::getline(ifs, line))
			{
				//std::cout << "	" << line << std::endl;
				processStringLine(language.strings, line);
			}
			ifs.close();
			std::cout << "---------" << line << std::endl;
			std::cout << "Finished reading strings file" << std::endl;
		}
		else {
			std::cerr << "Couldn't read file" << std::endl;
		}
	}
	else
	{
		std::cout << "Path \"" << filepath.string() << "\" doesn't exist" << std::endl;
	}
}

auto TextMaker::loadLanguagesFile(std::filesystem::path const & path) -> Languages
{
	auto line = std::string();
	auto ifs = std::ifstream(path);
	auto languages = Languages();
	if (ifs.is_open())
	{
		auto const FILENAME = path.filename().string().substr(0, path.filename().string().size() - path.extension().string().size());
		while (std::getline(ifs, line))
		{
			processLanguageLine(languages, line);
		}
		ifs.close();
		std::cout << "Finished reading languages file" << std::endl;
	}
	else {
		std::cerr << "Couldn't read file" << std::endl;
	}

	return languages;
}

auto TextMaker::addString(std::vector<String> & strings, std::string const & line) -> void
{
	auto items = std::vector<std::string>();
	items.reserve(4);

	auto const END = std::end(line);
	auto current = std::begin(line);
	auto next = std::find_if(current, END, isSpacer);
	items.push_back(line.substr(0, std::distance(std::begin(line), next)));
	while (next < END && items.size() < 4)
	{
		current = std::find_if(next, END, isValidChar);
		next = std::find_if(current, END, isSpacer);
		if (items.size() < 3)
		{
			items.push_back(line.substr(std::distance(std::begin(line), current), std::distance(current, next)));
		}
		else
		{
			items.push_back(line.substr(std::distance(std::begin(line), current), std::distance(current, END)));
		}
	}

	if (items.size() >= 4)
	{
		auto faceName = FaceName::None;
		if (is_match(items.at(KEY_FACE_NAME), "primary"))
		{
			faceName = FaceName::Primary;
		}
		else if (is_match(items.at(KEY_FACE_NAME), "secondary"))
		{
			faceName = FaceName::Secondary;
		}

		auto & faceSizeString = items.at(KEY_FACE_SIZE);
		auto faceSize = uint8_t{0};
		try {
			faceSize = std::stoi(faceSizeString, nullptr);
		}
		catch (std::invalid_argument e)
		{
			std::cerr << "Error--invalid argument on this line: (" << line << ")" << std::endl;
		}

		std::cout << "Data: " << items.at(KEY_NAME) << ", " << items.at(KEY_FACE_NAME) << ", " << faceSize << ", " << items.at(KEY_TEXT) << std::endl;

		strings.emplace_back(
			items.at(KEY_NAME),
			faceName,
			faceSize,
			items.at(KEY_TEXT),
			getTextId(items.at(KEY_NAME))
		);
	}
	else
	{
		std::cerr << "Error--line isn't formatted correctly: (" << line << ")" << std::endl;
	}
}

auto TextMaker::addLanguage(Languages & languages, std::string const & line) -> void
{
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
		languages.list.emplace_back(items.at(KEY_LANGUAGE_NAME),
									items.at(KEY_LANGUAGE_TEXT));
	}
	else
	{	// language line isn't formatted correctly
		std::cerr << "Error--line isn't formatted correctly: (" << line << ")" << std::endl;
	}
}

auto TextMaker::save(std::filesystem::path const & path, Languages const & languages) -> bool
{
	std::cout << "Attempting to save serialized languages" << std::endl;
	auto result = bool{false};

	makeFileDirs(path);

	auto ofs = std::ofstream(path, std::ios::binary | std::ios::trunc | std::ios::out);

	if (ofs.is_open())
	{
		std::cout << "Saving data list" << std::endl;
		auto ser = bitsery::Serializer<bitsery::OutputBufferedStreamAdapter>(ofs);
		ser.object(languages);
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
}
