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
#include "Address.hpp"

int	main()
{
        // Construct an address using getaddrinfo
        Address address0("11.233.0.1", "99");
        Address address1("api.binance.com", "https");
        Address address2("127.0.0.1", "ssh");
        Address address3("localhost", 80);
        Address	address4("./here.sock");

        std::cout << address0 << std::endl;
        std::cout << address1 << std::endl;
        std::cout << address2 << std::endl;
        std::cout << address3 << std::endl;
        std::cout << address4 << std::endl;
}
