//
// Error handling
//

#ifndef SJASMPLUS_ERRORS_H
#define SJASMPLUS_ERRORS_H

#include <string>
#include <iostream>
#include <stack>

using namespace std::string_literals;

using std::cout;
using std::cerr;
using std::endl;
using std::flush;
using std::stack;

extern std::string ErrorStr;
extern int PreviousErrorLine;

extern int WarningCount;

enum EStatus {
    ALL, PASS1, PASS2, PASS3, FATAL, CATCHALL, SUPPRESS
};
enum EReturn {
    END, ELSE, ENDIF, ENDTEXTAREA, ENDM
};

void Error(const std::string &fout, const std::string &bd, int type = PASS2);

void Error(const std::string &fout, int type = PASS2);

[[noreturn]] void Fatal(const std::string &errstr);

[[noreturn]] void Fatal(const std::string &errstr, const std::string &bd);

void Warning(const std::string &fout, const std::string &bd, int type = PASS2);

void Warning(const std::string &fout, int type = PASS2);

// output
#define _COUT cout <<
#define _CMDL  <<
#define _ENDL << endl
#define _END ;

#endif //SJASMPLUS_ERRORS_H
