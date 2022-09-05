#include "main.h"
Cache::Cache(SearchEngine *s, ReplacementPolicy *r) : rp(r), s_engine(s) {}
Cache::~Cache()
{
    delete rp;
    delete s_engine;
}
Data *Cache::read(int addr)
{
    rp->updatePeriod();
    Factor *ftr = rp->find(addr);
    if (ftr == nullptr) {
        delete ftr;
        return nullptr;
    }
    Data *dt = ftr->elem->data;
    return dt;
}
Elem *Cache::put(int addr, Data *cont)
{
    Factor *f = new Factor(addr, cont, true);
    Elem *ele = rp->insert(f);
    Factor *ftr = new Factor(addr, cont, true);
    if (ele != nullptr) {
        rp->swapPri(ele->addr, *ftr);
    }
    else {
        rp->insertPri(*ftr);
    }
    
    if (ele != nullptr) {
        s_engine->remove(ele->addr);
    }
  
    s_engine->insert(*ftr);
    return ele;
}
Elem *Cache::write(int addr, Data *cont)
{
    rp->updatePeriod();
    Factor *f = new Factor(addr, cont, false);
    bool check = rp->size < MAXSIZE && !rp->findFac(addr);
    Elem *ele = rp->write(addr, f);
    Factor *ftr = new Factor(addr, cont, false);
    if (ele != nullptr) {
        s_engine->remove(ele->addr);
        s_engine->insert(*ftr);
    }
    else if (check){
        s_engine->insert(*ftr);
    }
    else {
        s_engine->set(addr, *ftr);
    }
    return ele;
}

void Cache::printRP()
{
    rp->print();
}

void Cache::printSE()
{
    s_engine->print();
}

void Cache::printLP()
{
    cout << "Prime memory\n";
    rp->printPri();
    cout << "Hash table memory\n";
    rp->printHashTable();
}