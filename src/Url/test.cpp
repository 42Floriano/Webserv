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

#include <iostream>
#include <string>
#include "Url.hpp"

int	main(int ac, char **av)
{
        if (ac == 1)
        {
                Url	url("http://example.org/path/to/file?key=value#hello");
                std::cout << url;
        }
        else
        {
                Url	url(av[1]);
                std::cout << url;
        }

        return (0);
}
