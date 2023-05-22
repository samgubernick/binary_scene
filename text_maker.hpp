#ifndef SAM_BINARY_DATA_TEXT_MAKER_HPP_INCLUDED
#define SAM_BINARY_DATA_TEXT_MAKER_HPP_INCLUDED
#pragma once

#include "languages.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

namespace sam { namespace binary_data {
class TextMaker
{
public:
	TextMaker();

	int processStrings();
private:
	void addLanguage(Languages & languages, std::string const & line);
	void addString(std::vector<String> & strings, std::string const & line);
	void loadLanguageFiles(std::filesystem::path const & directory, Language & language);
	auto loadLanguagesFile(std::filesystem::path const & path) -> Languages;
	void convertStrings(Languages & languages);
	void processLanguageLine(Languages & languages, std::string const & line);
	void processStringLine(std::vector<String> & strings, std::string const & line);
	bool save(std::filesystem::path const & path, Languages const & languages);
private:
	std::vector<std::filesystem::path> languageFiles;
};
}}
#endif // INCLUDE_GUARD
