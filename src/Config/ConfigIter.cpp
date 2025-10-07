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

#include "ConfigIter.hpp"

ConfigIter::ConfigIter(const ConfigItem &server_config): server_config(
                server_config),
        name(), index(server_config.children.size())
{
}

ConfigIter::ConfigIter(const ConfigItem &server_config,
                       const std::string &name): server_config(server_config), name(name), index(0)
{
}

ConfigIter::ConfigIter(const ConfigItem &server_config, const std::string &name,
                       size_t index): server_config(server_config), name(name), index(index)
{
}

ConfigIter ConfigIter::begin(const ConfigItem &server_config,
                             const std::string &name)
{
        ConfigIter	it(server_config, name);

        if (it->name == name)
                return it;
        return ++it;
}
ConfigIter	ConfigIter::end(const ConfigItem &server_config)
{
        return ConfigIter(server_config);
}

ConfigItem& ConfigIter::operator*(void)
{
        return *(this->server_config.children[index]);
}

ConfigItem *ConfigIter::operator->(void)
{
        return this->server_config.children[index];
}

ConfigIter& ConfigIter::operator++()
{
        if (this->is_valid())
                ++index;
        while (!this->is_valid() && this->index < this->max_index_value())
        {
                ++index;
        }
        return *this;
}

bool ConfigIter::operator!=(const ConfigIter& other) const
{
        return this->index != other.index;
}

ConfigIter::~ConfigIter(void)
{

}

ConfigIter::ConfigIter(const ConfigIter &other):
        server_config(other.server_config),
        name(other.name),
        index(other.index)
{}
ConfigIter&	ConfigIter::operator=(const ConfigIter &rhs)
{
        this->name = rhs.name;
        this->index = rhs.index;
        return *this;
}

/* private */

size_t	ConfigIter::max_index_value(void) const
{
        return this->server_config.children.size();
}

bool	ConfigIter::is_valid(void) const
{
        if (this->index >= this->max_index_value())
                return false;
        if (this->server_config.children[index]->name != name)
                return false;
        return true;
}
