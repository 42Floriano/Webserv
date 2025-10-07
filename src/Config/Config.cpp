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

#include <Console.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <vector>

#include "Config.hpp"

const char *Config::default_config_path = "../config-files/default.conf";

Config	*Config::fromFile(const char *path, Config *dst)
{

        // TODO: stat the file, if the path is a dir? what happens?

        bool	is_new = false;
        if (path == NULL)
        {
                console::info << "no configuration filepath given: using defualt" << std::endl;
                path = Config::default_config_path;
        }
        if (dst == NULL)
        {
                dst = new Config;
                is_new = true;
        }

        console::info << "creating configuration object on the: " <<
                      (is_new ? "heap" : "stack") << std::endl;
        console::info << "trying to load configuration file in memory" << std::endl;
        ++console::info;

        console::info << "configuration file name: " << path << std::endl;
        std::ifstream	config_file(path);

        if (config_file.good())
        {
                console::info << "file successfully opened, parsing..." << std::endl;
                ++console::info;
                dst->parse(config_file);
                --console::info;
                console::info << "... parsing done" << std::endl;
                config_file.close();
                --console::info;
                return dst;
        }
        else
        {
                console::error << "failed to open configuration file" << std::endl;
                config_file.close();
                if (is_new)
                        delete dst;
                --console::info;
                return NULL;
        }
}

Config::Config() : _scopeLvl(0), _current_line(0) {}

void Config::parse(std::istream &input)
{
        while (1)
        {
                std::string tok = ConfigParser::peekToken(input);
                if (tok.empty())
                        break;
                if (ConfigParser::isCtx(tok) && ConfigParser::verif_scope(tok, _scopeLvl))
                {
                        _scopeLvl++;
                        this->children.push_back(ConfigParser::parseContext(input,
                                                 _current_line,
                                                 _scopeLvl));
                        _scopeLvl--;
                }
                else
                {
                        std::stringstream error_msg;
                        error_msg << "Config[" << _current_line << "]: " << tok
                                  << ": invalid field" << std::endl;
                        throw std::runtime_error(error_msg.str());
                }
        }
}

std::ostream& operator<<(std::ostream &os, const Config &conf)
{
        conf.print(os, 0);
        return os;
}
