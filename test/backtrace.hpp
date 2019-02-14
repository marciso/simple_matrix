#pragma once
#include<vector>
#include<cstdio>
#include<ostream>
#include<csignal>
#include<functional>

/* Override signal handlers to provide stack trace information on selected signals.
 *
 * If exit is true, then exit the application from the signal handler; otherwise continue
 */
void register_backtrace_handler_for_signals(
        std::vector<int> signals = {SIGABRT, SIGSEGV, SIGBUS, SIGILL, SIGFPE, SIGPIPE},
        bool exit = true);

/* Walk the stack trace and calls fn for each entry
 * Uses backtrace_symbols to convert the pointer into string
 */
bool walk_backtrace(std::function<void(void*, char*)> fn);

/* uses backtrace_symbols_fd to print the information into file descriptor
 */
void print_backtrace_fd(int fd);

/* Output stack info into the stream.
 * First it uses walk_backtrace (backtrace_symbols) to get strings, then the strings
 * are serialized to the stream with specified separator between them.
 */
std::ostream & output_backtrace(std::ostream & o, char const * sep = "\n");

/* like output_backtrace, but prints into C-file with new line after each entry.
 */
void print_backtrace(FILE* f = stderr);


