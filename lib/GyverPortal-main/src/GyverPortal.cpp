#include "Arduino.h"
#include "GyverPortal.h"

// собирать страницу
void BUILD_BEGIN() {
    GP.PAGE_BEGIN();
    GP.AJAX_CLICK();
    GP.PAGE_BLOCK_BEGIN();
}

// завершить сборку
void BUILD_END() {
    GP.PAGE_BLOCK_END();
    GP.PAGE_END();
    //GP_SHOW();
}

// ===================== DEPRECATED =====================
void GP_BUILD(__attribute__((unused)) String& s) {
    //_GP = &s;
}
void BUILD_BEGIN(__attribute__((unused)) String& s) {
    //GP_BUILD(s);
    BUILD_BEGIN();
}
void GP_SHOW() {
    //if (_gp_ptr && _GP) (*(GyverPortal*)_gp_ptr).showPage(*_GP);
}

Builder add;
Builder GP;
