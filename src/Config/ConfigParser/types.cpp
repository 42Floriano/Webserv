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

bool ConfigParser::isCtx(const std::string &str)
{
        Specs::const_iterator it = _contextSpecs.find(str);
        if (it != _contextSpecs.end())
                return true;
        return false;
}

bool ConfigParser::isFieldCtx(const std::string &ctx,
                              const std::string &field)
{
        Specs::const_iterator it = _contextSpecs.find(ctx);
        if (it == _contextSpecs.end() || field.empty())
                return false;
        if ((ctx == it->first && field == "{") ||
                        (ctx == it->first && field[0] == '/'))
                return true;
        return false;
}

bool ConfigParser::isDir(const std::string &str)
{
        Specs::const_iterator it =
                _directiveSpecs.find(str);
        if (it != _directiveSpecs.end())
                return true;
        return false;
}

bool ConfigParser::isInteger(const std::string &s)
{
        if (s.empty())
                return false;
        for (size_t i = 0; i < s.size(); ++i)
        {
                if (s[0] < '0' || s[0] > '9')
                        return false;
        }
        return true;
}

bool ConfigParser::is_sep(char c)
{
        return (c == ';' || c == '{' || c == '}');
}


