/*

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU Affero General Public License as
 published by the Free Software Foundation, either version 3 of the
 License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Affero General Public License for more details.

 You should have received a copy of the GNU Affero General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/

#include "ConfigParser.hpp"

void ConfigParser::skipWhiteSpaces(std::istream &input, size_t& line)
{
        while (input && std::isspace(input.peek()))
        {
                if (input.peek() == '\n')
                        line++;
                input.get();
        }
}

void ConfigParser::burnCommentLine(std::istream &input, size_t& line)
{
        skipWhiteSpaces(input, line);
        while (input.peek() == '#')
        {
                std::string discard;
                std::getline(input, discard);
                skipWhiteSpaces(input, line);
        }
}

std::string ConfigParser::nextToken(std::istream &input, size_t& line)
{
        char c;
        std::string tok;

        while (input && tok.empty())
        {
                burnCommentLine(input, line);
                while (!input.eof())
                {
                        c = input.peek();
                        if (std::isspace(c) || is_sep(c))
                        {
                                if (tok.empty())
                                {
                                        input.get();
                                        tok += c;
                                }
                        }
                        else
                        {
                                input.get();
                                tok += c;
                                continue;
                        }
                        break;
                }
        }
        return tok;
}

std::string ConfigParser::peekArgs(std::istream &input, size_t& line)
{
        std::streampos pos = input.tellg();
        std::string burn = nextToken(input, line);
        std::string arg = nextToken(input, line);
        input.clear();
        input.seekg(pos);
        return arg;
}

std::string ConfigParser::peekToken(std::istream &input)
{
        size_t ignore;
        std::streampos pos = input.tellg();
        std::string tok = nextToken(input, ignore);
        input.clear();
        input.seekg(pos);
        return tok;
}
