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
#include <iostream>

int main()
{
        try
        {
                Config cfg("../../config-files/test_skip.conf");
                std::cout << cfg << std::endl;
                std::cout << cfg[1].getField("listen") << std::endl;

                std::cout << cfg.getLocs(1)[0].getField("root") << std::endl;
                std::cout << cfg[0].getLocs()[0].getField("root") << std::endl;
        }
        catch (std::exception &e)
        {
                std::cerr << e.what() << std::endl;
                return 1;
        }
        return (0);
}
