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

#ifndef CONFIGPARSER_HPP
#define CONFIGPARSER_HPP

#include <sstream>
#include <map>
#include "ConfigItem.hpp"
#include "FieldSpec.hpp"

struct ConfigParser
{

        typedef std::map<std::string, FieldSpec> Specs;

        static const Specs _directiveSpecs;
        static const Specs _contextSpecs;

        static bool verif_scope(const std::string &obj, size_t scope);
        static bool isCtx(const std::string &str);
        static bool isFieldCtx(const std::string &ctx, const std::string &field);
        static bool isDir(const std::string &str);
        static bool is_sep(char c);
        static bool isInteger(const std::string &s);

        static bool validateField(const std::string &dir,
                                  const std::vector<std::string>& args);
        static void skipWhiteSpaces(std::istream &input, size_t& line);
        static void burnCommentLine(std::istream &input, size_t& line);
        static std::string peekArgs(std::istream &input, size_t& line);
        static std::string nextToken(std::istream &input, size_t& line);
        static std::string peekToken(std::istream &input);
        static ConfigItem *parseDirective(std::istream &input,
                                          size_t& line); /** throw exception */
        static ConfigItem *parseContext(std::istream &input, size_t& line,
                                        size_t& scope); /** throw exception */
};

#endif
