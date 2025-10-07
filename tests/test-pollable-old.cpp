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

#include "PollSet.hpp"
#include "PollableReadable.hpp"
#include <iostream>
#include <fcntl.h>
#include "FdReader.hpp"

int	main(int ac, char **av)
{
        // define the poll set
        PollSet		pset;

        // get file name
        const char	*filename = ac != 2 ? "./webserv.cpp" : av[1];

        // open file
        int	fd = open(filename, O_RDONLY);


        // define buffer where file is written
        std::stringstream	buff;

        // add the reader to the pollset
        FdReader	file(fd, pset, buff);

        while (!file.done)
                pset.poll(50);

        // prints/consume the buffer contianing the file
        std::cout << buff.rdbuf();

        return (0);
}
