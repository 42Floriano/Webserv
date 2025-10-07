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

#include "Console.hpp"
#include "ConfigParser.hpp"

bool ConfigParser::verif_scope(const std::string &obj, size_t scope)
{
        Specs::const_iterator it_ctx = _contextSpecs.find(obj);
        Specs::const_iterator it_dir = _directiveSpecs.find(obj);
        if (it_ctx != _contextSpecs.end() && it_ctx->second.scope == scope)
                return true;
        if (it_dir != _directiveSpecs.end() &&
                        (it_dir->second.scope == BOTH || it_dir->second.scope == scope))
                return true;
        return false;
}

bool ConfigParser::validateField(const std::string &dir,
                                 const std::vector<std::string>& args)
{
        // Verify `dir` is a valid name
        Specs::const_iterator it = _directiveSpecs.find(dir);
        if (it == _directiveSpecs.end())
        {
                console::error << "Invalid directive: " << dir << std::endl;
                return false;
        }

        const FieldSpec &spec = it->second;

        // Verify argument count
        if (args.size() < static_cast<size_t>(spec.minParams)
                        || args.size() > static_cast<size_t>(spec.maxParams))
        {
                console::error << "Invalid number of arguments" << std::endl;
                return false;
        }

        // Verify string values
        if (spec.type == "string")
        {
                if (!spec.allowedValues.empty())
                {
                        for (size_t i = 0; i < args.size(); ++i)
                        {
                                if (spec.allowedValues.find(args[i]) == spec.allowedValues.end())
                                {
                                        console::error << "Invalid string value" << std::endl;
                                        return false;
                                }
                        }
                }
        }

        // Verify numerical value
        else if (spec.type == "int")
        {
                for (size_t i = 0; i < args.size(); ++i)
                {
                        if (!ConfigParser::isInteger(args[i]))
                        {
                                console::error << "Value is not a number";
                                return false;
                        }
                }
        }

        // Verify boolean value
        else if (spec.type == "bool")
        {
                for (size_t i = 0; i < args.size(); ++i)
                {
                        if (args[i] != "on" && args[i] != "off")
                        {
                                console::error << "Value is not a boolean";
                                return false;
                        }
                }
        }

        // FieldSpec is wrong, you mistiped the type
        else
        {
                console::error << "Unknown FieldSpec type: wtf ?" << std::endl;
                return false;
        }

        return true;
}
