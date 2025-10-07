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

#include <vector>
#include <iostream>
#include <climits>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/wait.h>
#include "Process.hpp"

void	Process::_parse_command(std::istream &input)
{

        std::string	word;

        while (!input.eof())
        {
                input >> word;
                if (word.size() > 0)
                {
                        if (this->argv.size() == 0)
                                this->command = this->_resolve_command(word);
                        char *arg = new char[word.size() + 1];
                        ::strcpy(arg, word.c_str());
                        this->argv.push_back(arg);
                }
        }
}
