/****************************************************************************
 FileName     [ cirGate.h ]
 PackageName  [ cir ]
 Synopsis     [ Define basic gate data structures ]
 Author       [ Chung-Yang (Ric) Huang ]
 Copyright    [ Copyleft(c) 2008-present LaDs(III), GIEE, NTU, Taiwan ]
 ****************************************************************************/

#ifndef CIR_GATE_H
#define CIR_GATE_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <bitset>
#include <string>
#include <algorithm>
#include "cirDef.h"

using namespace std;

class CirGate;

//------------------------------------------------------------------------
//   Define classes
//------------------------------------------------------------------------
// TODO: Define your own data members and member functions, or classes
class CirGate
{
public:
    CirGate() {}
    CirGate(unsigned i, unsigned l): _ref(0),_id(i),_lineNo(l),SimVal(0) {
        _name="";
        SimOutStr=bitset<64>(0).to_string();
    }
    virtual ~CirGate() {}
    static unsigned _globalRef;
    // Basic access methods
    virtual string getTypeStr() const { return ""; }
    unsigned getLineNo() const { return _lineNo; }
    unsigned getID() const { return _id; }
    void setname(string token) {
        _name=token;
    }
    void setlineNo(unsigned no) {
        _lineNo=no;
    }
    virtual bool isAig() const { return false; }
    string getname() { return _name;}
    // Printing functions
    virtual void printGate()  {}
    void reportGate() const;
    void reportFanin(int level) ;
    void reportFanout(int level) ;
    void getFaninReport(int curlevel, int level);
    void getFanoutReport(int curlevel, int level);
    //DFS functions
    bool isGlobalRef(){ return (_ref == _globalRef); }
    void setToGlobalRef(){ _ref = _globalRef; }
    static void setGlobalRef() { _globalRef++; }
    unsigned _ref;
    void setfanin(CirGate* in){
        faninlist.push_back(in);
    }
    void setfanout(CirGate* out){
        fanoutlist.push_back(out);
    }
    //simulation
    vector<CirGate*> faninlist;
    vector<CirGate*> fanoutlist;
    vector<unsigned> faninID;
    vector<unsigned> fanoutID;
    vector<CirGate*> report;
    string _name;
    void setSimVal(size_t& s) { SimVal=s;}
    void setSimOutStr(string& ss) { SimOutStr=ss; }
    size_t getSimVal() { return SimVal;}
    virtual void gateSim() {}
    string SimOutStr;
    vector<unsigned> fec;
protected:
    unsigned _id;
    unsigned _lineNo;
    size_t SimVal;
private:
};

class ConstGate : public CirGate
{
public:
    ConstGate(unsigned i, unsigned l):CirGate(i,l) {}
    ~ConstGate() {}
    string getTypeStr() const { return "CONST"; }
    void printGate();
private:
    
    
};

class UndefGate : public CirGate
{
public:
    UndefGate(unsigned i, unsigned l):CirGate(i,l) {}
    ~UndefGate() {}
    string getTypeStr() const { return "UNDEF"; }
    void printGate();
private:
};

class PIGate : public CirGate
{
public:
    PIGate(unsigned i, unsigned l):CirGate(i,l) {}
    ~PIGate() {}
    string getTypeStr() const { return "PI"; }
    void printGate();
private:
    //string _name;
};


class POGate : public CirGate
{
public:
    POGate(unsigned i,  unsigned l):CirGate(i,l) {}
    ~POGate() {}
    string getTypeStr() const { return "PO"; }
    void printGate();
    void gateSim();
private:
    //string _name;
};

class LGate : public CirGate {};

class AIGGate : public CirGate
{
public:
    AIGGate(unsigned i,  unsigned l):CirGate(i,l) {}
    ~AIGGate() {}
    string getTypeStr() const { return "AIG"; }
    void printGate();
    void gateSim();
private:
    
};
#endif // CIR_GATE_H

