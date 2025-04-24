#ifndef __SETTING_H__
#define __SETTING_H__

#include <iostream>

using namespace std;

const int MAX_ASC_SIZE = 256;

const char *control[] = {
    "NUL", "SOH", "STX", "ETX", "EOT", "ENQ", "ACK", "BEL",
    "BS", "HT", "LF", "VT", "FF", "CR", "SO", "SI",
    "DLE", "DC1", "DC2", "DC3", "DC4", "NAK", "SYN", "ETB",
    "CAN", "EM", "SUB", "ESC", "FS", "GS", "RS", "US"};

// 제어 문자 출력
string getControlCharName(int code)
{

    if (code >= 0 && code < 32)
        return control[code];
    else if (code == 127)
        return "DEL";
    else
        return "UNKNOWN";
}

const int MAX_INT = 99999999;

#endif