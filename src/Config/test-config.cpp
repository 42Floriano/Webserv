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

#include "Config.hpp"
#include "ConfigIter.hpp"
#include <iostream>
#include <map>

int main(int ac, char **av)
{
        if (ac > 1)
        {
                try
                {
                        ConfigItem	*server_config = Config::fromFile(av[1]);

                        ConfigIter	it = ConfigIter::begin(*server_config, "location");
                        ConfigIter	end = ConfigIter::end(*server_config);

                        for (; it != end; ++it)
                        {
                                std::cout << "##################################" << std::endl;
                                std::cout << "loc: " << it->args[0] << std::endl;
                                std::cout << *it << std::endl;
                                std::cout << "##################################" << std::endl;
                                std::cout << std::endl;
                        }


                }
                catch (std::exception &e)
                {
                        std::cerr << e.what() << std::endl;
                        return 1;
                }
        }
        return (0);
}
