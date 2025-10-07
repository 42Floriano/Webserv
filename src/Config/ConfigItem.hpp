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

#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

class ConfigItem
{

public:
        enum Type
        {
                CONFIG_NULL,
                DIRECTIVE,
                CONTEXT,
        };

public:
        std::string					name;
        std::vector<std::string>	args;
        std::vector<ConfigItem *>	children;
        ConfigItem::Type			type;

        ConfigItem(
                const std::string &name,
                const std::vector<std::string> args,
                const std::vector<ConfigItem *>& items
        );

        ConfigItem(
                const std::string &name,
                const std::vector<std::string> args
        );

        ConfigItem(void);
        ConfigItem(const ConfigItem &other);
        virtual ~ConfigItem(void);
        ConfigItem& operator=(const ConfigItem &rhs);


public:
        struct ConfigItemSort
        {
                bool operator()(const ConfigItem *a, const ConfigItem *b) const;
        };
        const ConfigItem& getField(const std::string &name)
        const;           /* throw exception */
        const std::vector<ConfigItem> getLocs(void) const; /* throw exception */
        size_t getSize(void) const;
        const std::string	*operator[](size_t i) const;
        const ConfigItem *operator[](const std::string &key) const;
        const std::string& getRoot(void) const; /* throw exception */
        void	print(std::ostream &os, int indent) const;
};

std::ostream&		operator<<(std::ostream &os, const ConfigItem &item);

#endif
