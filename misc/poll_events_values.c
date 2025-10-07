#include <stdio.h>
#include <poll.h>

void	p(short e, const char *s) {
	printf("Event: %s: %d\n", s, e);
}

int	main() {
	p(POLLIN,"POLLIN");
	p(POLLRDNORM,"POLLRDNORM");
	p(POLLRDBAND,"POLLRDBAND");
	p(POLLPRI,"POLLPRI");
	p(POLLOUT,"POLLOUT");
	p(POLLWRNORM,"POLLWRNORM");
	p(POLLWRBAND,"POLLWRBAND");
    p(POLLERR,"POLLERR");
	p(POLLHUP,"POLLHUP");
	p(POLLNVAL,"POLLNVAL");
}
