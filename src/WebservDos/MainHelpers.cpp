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

void	Webserv::init_console(char *option)
{

        if (strchr(option, 'd'))
                console::debug.on();
        if (strchr(option, 'e'))
                console::error.on();
        if (strchr(option, 'i'))
                console::info.on();
}

char	*Webserv::parse_args(int ac, char **av)
{
        char	*filename;

        filename = NULL;

        console::info.off();
        console::debug.off();
        console::error.off();

        for (int i = 1; i < ac; i++)
        {
                if (av[i][0] != '-')
                {
                        if (filename == NULL)
                                filename = av[i];
                        else
                        {
								console::error.on();
                                console::error << "Too many arguments" << std::endl;
                                exit(-1);
                        }
                }
                else
                        init_console(av[i] + 1);
        }
        return (filename);
}
