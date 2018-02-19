using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data;
using System.IO;

namespace DummyClient
{
    static class PacketMakeDate
    {
        static public string stamp()
        {
            return "2018/02/19 17:22:23";
        }
    }
    enum PacketType : long {
    /*2*/    E_C_REQ_EXIT = 2,
    /*3*/    E_S_ANS_EXIT = 3,
    /*4*/    E_I_NOTIFY_TERMINAL = 4,
    /*5*/    E_C_NOTIFY_HEARTBEAT = 5,
    /*6*/    E_C_REQ_ID_PW = 6,
    /*7*/    E_S_ANS_ID_PW_FAIL = 7,
    /*8*/    E_S_ANS_ID_PW_SUCCESS = 8,
    /*9*/    E_I_DB_REQ_ID_PW = 9,
    /*10*/    E_I_DB_ANS_ID_PW = 10,
    /*11*/    E_I_CHTTING_NOTIFY_ID = 11,
    /*12*/    E_I_DB_REQ_LOAD_DATA = 12,
    /*13*/    E_I_DB_ANS_PARSE_DATA = 13,
    /*14*/    E_I_LOGIN_NOTIFY_ID_LOADED = 14,
    /*15*/    E_C_REQ_REGIST_CHATTING_NAME = 15,
    /*16*/    E_C_REQ_CHATTING = 16,
    /*17*/    E_S_ANS_CHATTING = 17,
     }
};
