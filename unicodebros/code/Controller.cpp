#include "Controller.h"

void Controller::setInputs(){
    a = key_is_pressed(XK_Z);
    b = key_is_pressed(XK_X);
    start = key_is_pressed(XK_C);
    select = key_is_pressed(XK_V);
    up = key_is_pressed(XK_Up);
    down = key_is_pressed(XK_Down);
    left = key_is_pressed(XK_Left);
    right = key_is_pressed(XK_Right);
}

bool Controller::key_is_pressed(KeySym ks) {
    Display *dpy = XOpenDisplay(":0");
    char keys_return[32];
    XQueryKeymap(dpy, keys_return);
    KeyCode kc2 = XKeysymToKeycode(dpy, ks);
    bool isPressed = !!(keys_return[kc2 >> 3] & (1 << (kc2 & 7)));
    XCloseDisplay(dpy);
    //std::cout << "Reads: " << readNum << '\n';
    return isPressed;
}

void Controller::resetRead(){
    readNum = 0;
}

byte Controller::returnButton(){
    //Because on bus and top 5 bits not driven top 5 bytes are usually 0x40/41 (from controller port address) and games like Paperboy rely on this.
    readNum += 1;
    switch(readNum){
        case 1:
            a = key_is_pressed(XK_Z);
            return a;
            break;
        case 2:
            b = key_is_pressed(XK_X);
            return b;
            break;
        case 3:
            select = key_is_pressed(XK_V);
            return select;
            break;
        case 4:
            start = key_is_pressed(XK_C);
            if(start){
                slctpressed = true;
            }
            return start;
            break;
        case 5:
            up = key_is_pressed(XK_Up);
            return up;
            break;
        case 6:
            down = key_is_pressed(XK_Down);
            return down;
            break;
        case 7:
            left = key_is_pressed(XK_Left);
            return left;
            break;
        case 8:
            right = key_is_pressed(XK_Right);
            return right;
            break;
        default:
            return 1;
    }
}