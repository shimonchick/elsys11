#include "rot3.hh"

void Rot3::execute(){
    double v1 = get_calc().pop();
    double v2  = get_calc().pop();
    double v3 = get_calc().pop();

    get_calc().push(v3);
    get_calc().push(v2);
    get_calc().push(v1);
}