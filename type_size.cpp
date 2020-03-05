#include <iostream>
#include <sys/utsname.h>

int main()
{
    struct utsname sysinfo;
    uname(&sysinfo);
    std::cout << "System Name: " << sysinfo.sysname << "\n"
        << "Host Name: " << sysinfo.nodename << "\n"
        << "Release(Kernel) Version: " << sysinfo.release << "\n"
        << "Kernel Build Timestamp: " << sysinfo.version << "\n"
        << "Machine Arch: " << sysinfo.machine << "\n"
        << "Domain Name: " << sysinfo.domainname << "\n" << std::endl;

    std::cout << "size_of_int = " << sizeof(int) << "\n"
        << "size_of_long = " << sizeof(long) << "\n"
        << "size_of_long_long = " << sizeof(long long) << "\n"
        << "size_of_float = " << sizeof(float) << "\n"
        << "size_of_double = " << sizeof(double) << "\n" << std::endl;
    return 0;
}
