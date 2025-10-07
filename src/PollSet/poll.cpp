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

void	PollSet::poll(int timeout)
{

        console::debug << "=== Poll Event Loop: Start ===" << std::endl;
        console::debug << "PollSet size: " << this->_pollfdset.size() << std::endl;
        ++console::debug;
        errno = 0;
        int n = ::poll(this->_pollfdset.ptr(), this->_pollfdset.size(), timeout);
        this->print_events(console::debug);
        (n < 0)		?
        this->onPollError(errno):
        (n == 0)	?
        this->onPollTimeout(timeout):
        this->onPollSuccess(n);
        --console::debug;
        console::debug << "=== Poll Event Loop: End ===\n" << std::endl;
}
