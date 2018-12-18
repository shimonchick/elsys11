#include "swap.hh"
void Swap::execute(){
    double v1 = get_calc().pop();
    double v2 = get_calc().pop();

    get_calc().push(v1);
    get_calc().push(v2);
}