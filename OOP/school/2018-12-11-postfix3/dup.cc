#include "dup.hh"
void Dup::execute(){
    double v = get_calc().pop();
    get_calc().push(v);
    get_calc().push(v);
}