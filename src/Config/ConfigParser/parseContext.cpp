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

ConfigItem *ConfigParser::parseContext(std::istream &input, size_t& line,
                                       size_t& scope)
{

        std::string name = nextToken(input, line);
        std::vector<std::string> args;
        std::string tok;
        std::vector<ConfigItem *> items;
        try
        {
                while (true)
                {
                        tok = nextToken(input, line);

                        if (tok == "{")
                        {
                                break;
                        }

                        if (tok.empty())
                        {
                                throw std::runtime_error("Parse Ctx: token is empty");
                        }

                        args.push_back(tok);
                }

                if (name == "location" && args.size() < 1)
                {
                        std::stringstream error_msg;
                        error_msg << "Config[" << line << "]: " << name << ": not enough arguments"
                                  << std::endl;
                        throw std::runtime_error(error_msg.str());
                        // throw std::runtime_error("Ctx: " + name + " not enough arguments");
                }

                if (name == "server" && args.size() != 0)
                {
                        std::stringstream error_msg;
                        error_msg << "Config[" << line << "]: " << name << ": Too many argument"
                                  << std::endl;
                        throw std::runtime_error(error_msg.str());
                        // throw std::runtime_error("Ctx: " + name + " Too many argument");
                }

                while (true)
                {
                        std::string tok = peekToken(input);

                        if (tok == "}")
                        {
                                nextToken(input, line);
                                break;
                        }
                        if (ConfigParser::isCtx(tok) && ConfigParser::verif_scope(tok, scope))
                        {
                                scope++;
                                items.push_back(parseContext(input, line, scope));
                                scope--;
                        }
                        else if (isDir(tok) && verif_scope(tok, scope))
                        {
                                scope++;
                                items.push_back(parseDirective(input, line));
                                scope--;
                        }
                        else
                        {
                                std::stringstream error_msg;
                                error_msg << "Config[" << line << "]: " << tok << ": invalid field"
                                          << std::endl;
                                throw std::runtime_error(error_msg.str());
                        }
                }
                if(name == "server")
                {
                        // std::stringstream error_msg;
                        // error_msg << "Server contains no locations"
                        //           << std::endl;
                        // throw std::runtime_error(error_msg.str());
                }

        }
        catch  (const std::exception&) {}

        return new ConfigItem(name, args, items);
}
