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

#include <ostream>
#include "Address.hpp"

static void	print_ipv4_address(std::ostream &os, const Address &addr)
{
        os
                        << "(" << "ipV4" << ") "
                        << ((addr.host() >> 24) & 255)	<< '.'
                        << ((addr.host() >> 16) & 255)	<< '.'
                        << ((addr.host() >> 8) & 255)	<< '.'
                        << ((addr.host() >> 0) & 255)	<< ':'
                        << addr.port();
}

static void	print_unix_address(std::ostream &os, const Address &addr)
{
        os
                        << "(" << "unix" << ") "
                        << addr.path();
}

static void	print_ipv6_address(std::ostream &os, const Address &addr)
{
        os << "some ip version 6 address: " << addr.port();
}

std::ostream&	operator<<(std::ostream &output, const Address &address)
{
        switch (address.family())
        {

        case (AF_INET):
                print_ipv4_address(output, address);
                break;
        case (AF_INET6):
                print_ipv6_address(output, address);
                break;
        case (AF_UNIX):
                print_unix_address(output, address);
                break;
        }
        return (output);
}

#include <iostream>
std::ostream&	operator<<(std::ostream &output, const Address *address)
{
        if (address != NULL)
        {
                output << *address;
        }
        else
        {
                output << "(null)";
        }
        return (output);
}
