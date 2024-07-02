#include "pocketpy/interpreter/vm.h"
#include "pocketpy/objects/base.h"
#include "pocketpy/pocketpy.h"

bool py_isidentical(const py_Ref lhs, const py_Ref rhs) {
    if(lhs->type != rhs->type) return false;
    switch(lhs->type){
        case tp_int: return lhs->_i64 == rhs->_i64;
        case tp_float: return lhs->_f64 == rhs->_f64;
        case tp_bool: return lhs->_bool == rhs->_bool;
        case tp_nativefunc: return lhs->_cfunc == rhs->_cfunc;
        case tp_none_type: return true;
        case tp_not_implemented_type: return true;
        case tp_ellipsis: return true;
        // fallback to pointer comparison
        default: return lhs->is_ptr && rhs->is_ptr && lhs->_obj == rhs->_obj;
    }    
}

int py_bool(const py_Ref val) { return 1; }

bool py_hash(const py_Ref val, int64_t* out) { return 0; }

bool py_getattr(const py_Ref self, py_Name name, py_Ref out) { return true; }

bool py_setattr(py_Ref self, py_Name name, const py_Ref val) { return -1; }

bool py_delattr(py_Ref self, py_Name name) { return -1; }

bool py_getitem(const py_Ref self, const py_Ref key, py_Ref out) { return -1; }

bool py_setitem(py_Ref self, const py_Ref key, const py_Ref val) { return -1; }

bool py_delitem(py_Ref self, const py_Ref key) { return -1; }

#define COMPARE_OP_IMPL(name, op, rop)                                                             \
    int py_##name(const py_Ref lhs, const py_Ref rhs) {                                            \
        bool ok = py_binaryop(lhs, rhs, op, rop);                                                  \
        if(!ok) return -1;                                                                         \
        return py_tobool(py_retval());                                                         \
    }

COMPARE_OP_IMPL(eq, __eq__, __eq__)
COMPARE_OP_IMPL(ne, __ne__, __ne__)
COMPARE_OP_IMPL(lt, __lt__, __gt__)
COMPARE_OP_IMPL(le, __le__, __ge__)
COMPARE_OP_IMPL(gt, __gt__, __lt__)
COMPARE_OP_IMPL(ge, __ge__, __le__)