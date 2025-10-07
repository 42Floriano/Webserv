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

ConfigItem *ConfigParser::parseDirective(std::istream &input, size_t& line)
{
        std::string command = nextToken(input, line);
        std::vector<std::string> args;
        std::string tok;

        while ((tok = nextToken(input, line)) != ";")
        {
                if (tok.empty())
                        throw std::runtime_error("Parse Dir: " + command + " token is empty");
                args.push_back(tok);
        }

        if (args.size() < 1)
                throw std::runtime_error("Directive: " + command + " not enough arguments");
        if (!validateField(command, args))
                throw std::runtime_error("Directive: " + command +
                                         " arguments are not corect");
        return new ConfigItem(command, args);
}
