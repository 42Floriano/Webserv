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
#include "HttpHeaders.hpp"

int	main(void)
{

        HttpHeaders	h;

        while (!std::cin.eof() && !h.is_sealed())
        {
                std::string line;

                std::cout << "> LOOP START" << std::endl;
                std::getline(std::cin, line);
                std::cout << "Input: " << line << std::endl;
                std::cout << "--- Parsing START ---" << std::endl;
                try
                {
                        h.parse(line);
                }
                catch (const std::exception &err)
                {
                        std::cout << "Error: " << std::endl;
                        std::cout << err.what() << std::endl;
                }
                std::cout << "--- Parsing DONE ---" << std::endl;
                h.print(std::cout);
                std::cout << "> LOOP END" << std::endl;
        }
        return (0);
}
