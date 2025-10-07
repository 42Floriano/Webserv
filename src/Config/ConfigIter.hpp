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

#ifndef CONFIGITER_HPP
# define CONFIGITER_HPP

#include "ConfigItem.hpp"

class	ConfigIter
{

public:
        static ConfigIter	begin(const ConfigItem &server_config,
                                 const std::string &name);
        static ConfigIter	end(const ConfigItem &server_config);

private:
        const ConfigItem&		server_config;
        std::string	name;
        size_t		index;


public:
        // constructs iterator at end
        ConfigIter(const ConfigItem &server_config);
        // constructs iterator at start
        ConfigIter(const ConfigItem &server_config, const std::string &name);
        // constructs iterator at any index
        ConfigIter(const ConfigItem &server_config, const std::string &name,
                   size_t index);

        // orthodox
        ConfigIter(void);
        ConfigIter(const ConfigIter &other);
        ConfigIter&	operator=(const ConfigIter &other);
        ~ConfigIter(void);

        // iterator op
        ConfigItem&			operator*(void);
        ConfigItem			*operator->(void);
        ConfigIter&			operator++();
        bool				operator!=(const ConfigIter& other) const;

private:
        size_t				max_index_value(void) const;
        bool				is_valid(void) const;
};

#endif
