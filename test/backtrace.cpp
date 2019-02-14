#include"backtrace.hpp"
#include<cstdlib>
#include<cstring>
#include<csignal>
#include<execinfo.h>

static void backtrace_handler(int signum, siginfo_t* si, void* context)
{
    fprintf( stderr, "Caught signal %d (%s)\n", signum, strsignal(signum));
    print_backtrace(stderr);
}

static void backtrace_handler_exit(int signum, siginfo_t* si, void* context)
{
    backtrace_handler(signum, si, context);
    std::exit(signum);
}

void register_backtrace_handler_for_signals(std::vector<int> signals, bool exit)
{
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = exit ? backtrace_handler_exit : backtrace_handler;
    ::sigemptyset( &sa.sa_mask );

    for( int signum : signals)
    {
        ::sigaction(signum, &sa, nullptr);
    }
}

bool walk_backtrace(std::function<void(void*, char*)> fn)
{
    constexpr size_t sz = 512;
    void * buffer[sz];
    if (int nptrs = ::backtrace(buffer, sz)) {
        if (char ** strings = ::backtrace_symbols(buffer, nptrs)) {
            for(int i = 0; i < nptrs; ++i)
                fn(buffer[i], strings[i]);
            ::free(strings);
            return true;
        }
    }
    return false;
}

std::ostream & output_backtrace(std::ostream & o, char const * sep)
{
    char const * s = "";
    walk_backtrace([&o, &s, sep](void * ptr, char* str){ o << s << str; s = sep; });
    return o;
}

void print_backtrace(FILE* f)
{
    walk_backtrace([f](void * ptr, char* str){ fprintf(f, "%s\n", str); });
}

void print_backtrace_fd(int fd)
{
    constexpr size_t sz = 512;
    void * buffer[sz];
    if (int nptrs = ::backtrace(buffer, sz)) {
        ::backtrace_symbols_fd(buffer, nptrs, fd);
    }
}


