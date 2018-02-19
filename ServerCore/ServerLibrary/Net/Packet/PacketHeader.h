#pragma once
#include "stdafx.h"

#define PACKET_MAKE_DATE "2018/02/19 18:06:23" 
enum PacketType : Int64 {
    /*8*/    E_C_REQ_EXIT = 8,
    /*9*/    E_S_ANS_EXIT = 9,
    /*10*/    E_I_NOTIFY_TERMINAL = 10,
    /*11*/    E_C_NOTIFY_HEARTBEAT = 11,
    /*12*/    E_C_REQ_ID_PW = 12,
    /*13*/    E_S_ANS_ID_PW_FAIL = 13,
    /*14*/    E_S_ANS_ID_PW_SUCCESS = 14,
    /*15*/    E_I_DB_REQ_ID_PW = 15,
    /*16*/    E_I_DB_ANS_ID_PW = 16,
    /*17*/    E_I_CHTTING_NOTIFY_ID = 17,
    /*18*/    E_I_DB_REQ_LOAD_DATA = 18,
    /*19*/    E_I_DB_ANS_PARSE_DATA = 19,
    /*20*/    E_I_LOGIN_NOTIFY_ID_LOADED = 20,
    /*21*/    E_C_REQ_REGIST_CHATTING_NAME = 21,
    /*22*/    E_C_REQ_CHATTING = 22,
    /*23*/    E_S_ANS_CHATTING = 23,
};
