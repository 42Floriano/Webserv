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

#include <climits>
#include "Process.hpp"

Process::Process(const std::string &cmd):
        pid(-1),
        command(),
        argv(),
        envp(),
        stdio(),
        real_stdio(),
        done(0),
        exit_status(INT_MIN),
        env()
{
        std::stringstream	input(cmd);

        this->_parse_command(input);
        this->_create_channels();
        console::debug << this->stdin() << "<-" << this->stdio[0] << std::endl;
        console::debug << this->stdout() << "<-" << this->stdio[1] << std::endl;
        console::debug << this->stderr() << "<-" << this->stdio[2] << std::endl;
}

Process::~Process(void)
{

        std::vector<char *>::iterator	it = this->argv.begin();
        std::vector<char *>::iterator	end = this->argv.end();

        for (; it != end; it++)
        {
                delete[] (*it);
        }
}
