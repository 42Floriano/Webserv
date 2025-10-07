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

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <sstream>
#include "ConfigItem.hpp"
#include "ConfigParser.hpp"
#include "FieldSpec.hpp"

class Config: public ConfigItem
{
public:
        static const char	*default_config_path;
        static Config		*fromFile(const char *path, Config *cfg = NULL);
        Config(void);
        //~Config() {};

private:
        size_t _scopeLvl;
        size_t _current_line;
        void parse(std::istream &input); /** throw exception */
public:
        static ConfigItem&	match_location(const ConfigItem *self,
                                           const std::string &path);
        static std::string	resolve_path(ConfigItem *self, const std::string &path);
        void   delete_conf(const Config &conf);
};

std::ostream&	operator<<(std::ostream &os, const Config &conf);
std::string		normalize_path(const std::string& path);

#endif
