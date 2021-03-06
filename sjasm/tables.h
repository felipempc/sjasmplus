/* 

  SjASMPlus Z80 Cross Compiler

  This is modified sources of SjASM by Aprisobal - aprisobal@tut.by

  Copyright (c) 2006 Sjoerd Mastijn

  This software is provided 'as-is', without any express or implied warranty.
  In no event will the authors be held liable for any damages arising from the
  use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it freely,
  subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not claim
	 that you wrote the original software. If you use this software in a product,
	 an acknowledgment in the product documentation would be appreciated but is
	 not required.

  2. Altered source versions must be plainly marked as such, and must not be
	 misrepresented as being the original software.

  3. This notice may not be removed or altered from any source distribution.

*/

#ifndef SJASMPLUS_TABLES_H
#define SJASMPLUS_TABLES_H

#include <iostream>
#include <string>
#include <map>

using namespace std::string_literals;

using std::cout;
using std::cerr;
using std::endl;

#include "defines.h"
#include "labels.h"
#include "errors.h"

extern int macronummer;
extern int lijst, synerr;

enum EStructureMembers {
    SMEMBUNKNOWN, SMEMBALIGN, SMEMBBYTE, SMEMBWORD, SMEMBBLOCK, SMEMBDWORD, SMEMBD24, SMEMBPARENOPEN, SMEMBPARENCLOSE
};

class FunctionTable {
public:
    bool insert(const std::string &Name, void(*FuncPtr)());

    bool insertDirective(const std::string &, void(*)());

    bool callIfExists(const std::string &, bool = false);

    bool find(const std::string &);

private:
    std::map<std::string, void (*)(void)> Map;
};

class CStringsList {
public:
    char *string;
    CStringsList *next;

    CStringsList() {
        next = 0;
    }

    ~CStringsList() {
        if (next) delete next;
    }

    CStringsList(char *, CStringsList *);
};

class CDefineTableEntry {
public:
    char *name, *value;
    CStringsList *nss; /* added */
    CDefineTableEntry *next;

    CDefineTableEntry(const char *, const char *, CStringsList * /*added*/, CDefineTableEntry *);
};

class CMacroDefineTable {
public:
    void Init();

    void AddMacro(char *, char *);

    CDefineTableEntry *getdefs();

    void setdefs(CDefineTableEntry *);

    char *getverv(char *);

    int FindDuplicate(char *);

    CMacroDefineTable() {
        Init();
    }

private:
    // By Antipod: http://zx.pk.ru/showpost.php?p=159487&postcount=264
    enum {
        KDelimiter = '_',
        KTotalJoinedParams = 64
    };

    void SplitToArray(const char *aName, char **&aArray, int &aCount, int *aPositions) const;

    int Copy(char *aDest, int aDestPos, const char *aSource, int aSourcePos, int aBytes) const;

    void FreeArray(char **aArray, int aCount);

    char tempBuf[LABMAX];    // for 'arg_someLabel_arg_anotherLabel' expansion
    // --

    int used[128];
    CDefineTableEntry *defs;
};

class CMacroTableEntry {
public:
    char *naam;
    CStringsList *args, *body;
    CMacroTableEntry *next;

    CMacroTableEntry(char *, CMacroTableEntry *);

    ~CMacroTableEntry() { if (next)delete next; };
};

class CMacroTable {
public:
    void Add(char *, char *&);

    int Emit(char *, char *&);

    int FindDuplicate(char *);

    void Init();

    CMacroTable() {
        Init();
    }

    ~CMacroTable() { if (macs) delete macs; };
private:
    int used[128];
    CMacroTableEntry *macs;
};

class CStructureEntry1 {
public:
    char *naam;
    aint offset;
    CStructureEntry1 *next;

    CStructureEntry1(char *, aint);
};

class CStructureEntry2 {
public:
    aint offset, len, def;
    EStructureMembers type;
    CStructureEntry2 *next;

    CStructureEntry2(aint, aint, aint, EStructureMembers);
};

class CStructure {
public:
    char *naam, *id;
    int binding;
    int global;
    aint noffset;

    void AddLabel(char *);

    void AddMember(CStructureEntry2 *);

    void CopyLabel(char *, aint);

    void CopyLabels(CStructure *);

    void CopyMember(CStructureEntry2 *, aint);

    void CopyMembers(CStructure *, char *&);

    void deflab();

    void emitlab(char *);

    void emitmembs(char *&);

    CStructure *next;

    CStructure(char *, char *, int, int, int, CStructure *);

private:
    CStructureEntry1 *mnf, *mnl;
    CStructureEntry2 *mbf, *mbl;
};

class CStructureTable {
public:
    CStructure *Add(char *, int, int, int);

    void Init();

    CStructureTable() {
        Init();
    }

    CStructure *zoek(const char *, int);

    int FindDuplicate(char *);

    int Emit(char *, char *, char *&, int);

private:
    CStructure *strs[128];
};

struct RepeatInfo {
    int RepeatCount;
    long CurrentGlobalLine;
    long CurrentLocalLine;
    long CurrentLine;
    CStringsList *Lines;
    CStringsList *Pointer;
    bool Complete;
    int Level;
    char *lp;
};

struct SConditionalStack {
    long CurrentGlobalLine;
    long CurrentLocalLine;
    long CurrentLine;
    CStringsList *Lines;
    CStringsList *Pointer;
    bool IsInWork;
    int Level;
    char *lp;
};

class CDevicePage {
public:
    CDevicePage(aint, aint /*, CDevicePage **/);

    ~CDevicePage();

    aint Size;
    aint Number;
    char *RAM;
    //CDevicePage* Next;
private:
};

class CDeviceSlot {
public:
    CDeviceSlot(aint, aint, aint /*, CDeviceSlot **/);

    ~CDeviceSlot();

    aint Address;
    aint Size;
    CDevicePage *Page;
    aint Number;
    //CDeviceSlot* Next;
private:
};

class CDevice {
public:
    CDevice(const char *, CDevice *);

    ~CDevice();

    void AddSlot(aint adr, aint size);

    void AddPage(aint size);

    CDevicePage *GetPage(aint);

    CDeviceSlot *GetSlot(aint);

    char *ID;
    CDevice *Next;
    aint CurrentSlot;
    aint CurrentPage;
    aint SlotsCount;
    aint PagesCount;
private:
    CDeviceSlot *Slots[256];
    CDevicePage *Pages[256];
};

#endif //SJASMPLUS_TABLES_H
