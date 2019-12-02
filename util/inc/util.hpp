#pragma once

#include <string>
#include <vector>
#include <fstream>

std::vector<std::string> split(std::string s, const std::string &delim)
{
    size_t pos = 0;
    size_t delimLen = delim.length();
    std::vector<std::string> result;

    while ((pos = s.find(delim)) != std::string::npos) {
		const auto token = s.substr(0, pos);
		result.push_back(token);
		s.erase(0, pos + delimLen);
	}
	result.push_back(s);

	return result;
}

std::vector<std::string> readFile(const std::string &filename)
{
    std::ifstream               file;
    std::string                 line;
    std::vector<std::string>    result;

    file.open(filename);
    while (getline(file, line))
        result.push_back(line);
    file.close();

    return result;
}