#pragma once
#define INV_INLINE __forceinline

#define CHECK_PTR if(!get_ptr()){return;}
#define CHECK_PTR_R_P if(!get_ptr()){return nullptr;}
