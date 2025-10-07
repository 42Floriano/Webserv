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
 along with self program.  If not, see <https://www.gnu.org/licenses/>.

*/

#include <sstream>
#include "Config.hpp"
#include "ConfigIter.hpp"
#include "Console.hpp"

// TODO: these are defined below, as static funcs, but they probably need to
// find a place to be as non-static.
template<typename Number>
static std::string nbr_tostr(Number n);
static std::string	postfix_index(const std::string &s, const ConfigItem &loc);
static std::string	prefix_root(std::string &s, const ConfigItem &serv,
                                const ConfigItem &loc);
static std::string	get_root(const ConfigItem &c);

std::string	Config::resolve_path(ConfigItem *self, const std::string &s)
{

        try
        {
                std::string	file_path = s;
                ConfigItem	&loc = Config::match_location(self, s);
                file_path = normalize_path(s);
                file_path = postfix_index(file_path, loc);
                file_path = prefix_root(file_path, *self, *((ConfigItem *)&loc));
                return (file_path);
        }
        catch (const std::runtime_error& e)
        {
                (void) e;
                return (s);
        }
}

template<typename Number>
static std::string	nbr_tostr(Number n)
{
        std::stringstream	str;

        str << n;
        return str.str();
}

static std::string	postfix_index(const std::string &path,
                                  const ConfigItem &loc)
{

        std::string	new_path = path;

        if (new_path == loc.args[0] && loc.getField("index").args.size() == 1)
                new_path += loc.getField("index").args[0];
        return new_path;
}

static std::string	get_root(const ConfigItem &c)
{
        std::string	ret;
        try
        {
                ret = c.getField("root").args[0];
        }
        catch (const std::exception &e)
        {
                (void) e;
        }
        return ret;
}

static std::string	prefix_root(std::string &file_path,
                                const ConfigItem &server_config,
                                const ConfigItem &location)
{

        std::string	root;

        root = get_root(location);
        if (root.size() == 0)
                root = get_root(server_config);
        file_path.erase(0, location.args[0].size() - 1);
        return root + location.args[0] + file_path;
}
