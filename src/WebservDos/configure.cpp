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

#include "Webserv.hpp"

int	Webserv::configure(const char *config_path)
{
        try
        {
                if (Config::fromFile(config_path, &this->conf) == NULL)
                {
                        console::error << "Failed to parse configuration file" << std::endl;
                        return (1);
                }
        }
        catch (const std::runtime_error &e)
        {
                console::error << "Catched error while parsing: " << e.what() << std::endl;
                return (1);
        }
        if (this->conf.children.size() == 0)
        {
                console::error << "Empty or invalid configuration" << std::endl;
                return (1);
        }
        return (0);
}

