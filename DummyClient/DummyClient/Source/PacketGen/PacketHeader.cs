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
            return "{0}";
        }
    }
    enum PacketType : long {
    /*1000*/    E_C_REQ_EXIT = 1000,
    /*1001*/    E_S_ANS_EXIT = 1001,
    /*1002*/    E_I_NOTIFY_TERMINAL = 1002,
    /*1003*/    E_C_NOTIFY_HEARTBEAT = 1003,
    /*1004*/    E_C_REQ_ID_PW = 1004,
    /*1005*/    E_S_ANS_ID_PW_FAIL = 1005,
    /*1006*/    E_S_ANS_ID_PW_SUCCESS = 1006,
    /*1007*/    E_I_DB_REQ_ID_PW = 1007,
    /*1008*/    E_I_DB_ANS_ID_PW = 1008,
    /*1009*/    E_I_CHTTING_NOTIFY_ID = 1009,
    /*1010*/    E_I_DB_REQ_LOAD_DATA = 1010,
    /*1011*/    E_I_DB_ANS_PARSE_DATA = 1011,
    /*1012*/    E_I_LOGIN_NOTIFY_ID_LOADED = 1012,
    /*1013*/    E_C_REQ_REGIST_CHATTING_NAME = 1013,
    /*1014*/    E_C_REQ_CHATTING = 1014,
    /*1015*/    E_S_ANS_CHATTING = 1015,
     }
};
