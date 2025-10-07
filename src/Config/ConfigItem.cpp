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

#include "ConfigItem.hpp"

ConfigItem::ConfigItem(
        const std::string &name,
        const std::vector<std::string> args,
        const std::vector<ConfigItem *>& items
): name(name), args(args), children(items), type(CONTEXT)
{

} ;

ConfigItem::ConfigItem(
        const std::string &name,
        const std::vector<std::string> args
): name(name), args(args), children(DIRECTIVE), type(DIRECTIVE)
{
} ;

void ConfigItem::print(std::ostream &os, int indent) const
{
        std::string prefix(indent, ' ');
        os << prefix << "Context: " << this->name << " ";
        for (size_t i = 0; i < this->args.size(); i++)
        {
                os << this->args[i];
        }
        os << std::endl;
        const std::vector<ConfigItem *>& items = this->children;
        for (size_t i = 0; i < items.size(); i++)
        {
                items[i]->print(os, indent + 2);
        }
}

std::ostream&	operator<<(std::ostream &os, const ConfigItem &item)
{
        item.print(os, 0);
        return os;
};

bool ConfigItem::ConfigItemSort::operator()(const ConfigItem *a,
                const ConfigItem *b) const
{
        if (a->name > b->name)
        {
                return true;
        }
        else if (a->name < b->name)
        {
                return false;
        }
        else /* if (a->name == b->name) */
        {
                if (b->args.empty())
                {
                        return true;
                }
                else if (a->args.empty())
                {
                        return false;
                }
                else
                {
                        return a->args[0].size() > b->args[0].size();
                }
        }
}

ConfigItem::ConfigItem() : type(CONFIG_NULL)
{

}

ConfigItem::ConfigItem(const ConfigItem &other):
        name(other.name),
        args(other.args),
        children(other.children),
        type(other.type)
{

}

ConfigItem& ConfigItem::operator=(const ConfigItem &rhs)
{
        this->name = rhs.name;
        this->args = rhs.args;
        this->children = rhs.children;
        this->type = rhs.type;
        return (*this);
}

const std::string& ConfigItem::getRoot(void) const
{
        if (this->type != CONTEXT)
                throw std::runtime_error("GetRoot on a non-context element");

        const std::vector<ConfigItem *>& items = this->children;
        for (size_t i = 0; i < items.size(); ++i)
        {
                const ConfigItem *item = items[i];
                if (item->type == DIRECTIVE && item->name == "root")
                {
                        const std::vector<std::string>& args = item->args;
                        if (!args.empty())
                        {
                                return args[0];
                        }
                }
        }
        throw std::runtime_error("Root is empty");
}

const std::vector<ConfigItem> ConfigItem::getLocs(void) const
{
        if (this->type != CONTEXT || this->name != "server")
        {
                throw std::runtime_error("Get locs in non-server context");
        }
        std::vector<ConfigItem> locs;
        const std::vector<ConfigItem *>& children = this->children;
        for (size_t j = 0; j < children.size(); ++j)
        {
                const ConfigItem *child = children[j];
                if (child->type == CONTEXT && child->name == "location")
                        locs.push_back(*child);
        }
        return locs;
}

const ConfigItem& ConfigItem::getField(const std::string &name) const
{
        if (this->type != CONTEXT)
                throw std::runtime_error("Searching: " + name + "in a non context item");

        const std::vector<ConfigItem *>& items = this->children;
        std::vector<ConfigItem *>::const_iterator it;

        for (it = items.begin(); it != items.end(); ++it)
        {
                ConfigItem *item = *it;
                if (item->name == name)
                        return *item;
        }
        throw std::runtime_error("Field not found: " + name);
}

size_t ConfigItem::getSize(void) const
{
        return this->type == CONTEXT ? this->children.size() : 0;
}

const std::string *ConfigItem::operator[](size_t i) const
{
        if (i < this->args.size())
        {
                return (&this->args[i]);
        }
        else
        {
                return NULL;
        }
}

const ConfigItem *ConfigItem::operator[](const std::string &key) const
{
        try
        {
                return &this->getField(key);
        }
        catch (const std::exception &e)
        {
                (void) e;
                return NULL;
        }
}

#include "Console.hpp"
ConfigItem::~ConfigItem(void)
{
        if (this->name.empty())
                console::info << "Deconstructing global config" << std::endl;
        for (size_t i = 0; i < this->children.size(); ++i)
        {
                delete this->children[i];
        }
}
