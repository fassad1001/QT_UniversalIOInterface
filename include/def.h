#ifndef DEF_H
#define DEF_H

#include <QString>

/*enum TYPE_SCREEN {DIFFUSING, LENS, NONE};
enum CONTROL_METHOD {COM, ETHERNET, NONE_CONTROL};

const QString NAME_SIMULATOR = "Фианит 2";

const QString NAME_UPPER_POWER = "DS-216MT";
const QString NAME_LOWER_POWER = "DS-116LVT";
const QString NAME_VIDEOCOMMUTATOR = "PSOE-3232-3G";
const QString NAME_BLACKMAGIC4_MULTIPLEXER = "Blackmagic Multiview 4";
const QString NAME_BLACKMAGIC16_MULTIPLEXER1 = "Blackmagic Multiview 16 - 1";
const QString NAME_BLACKMAGIC16_MULTIPLEXER2 = "Blackmagic Multiview 16 - 2";
const QString NAME_VIDEOREGISTRATOR8 = "Видеорегистратор KR082";
const QString NAME_VIDEOREGISTRATOR16 = "Видеорегистратор DS-7216HVI-S";
const QString NAME_PROJECTOR = "Проектор (ВСК-4)";
const QString NAME_MONITORS = "NEOVO";
const QString NAME_TKN1 = "КН1";
const QString NAME_TKN2 = "КН2";
const QString NAME_TKN3 = "КН3";
const QString NAME_TKN4 = "КН4";
const QString NAME_TKN5 = "КН5";
const QString NAME_TKN6 = "КН6";
const QString NAME_TK_SA = "ТК СА";
const QString NAME_TK_2_SA = "ТК 2 СА";
const QString NAME_RIGHT_ILLUMINATOR = "Правый (№6) иллюминатор";
const QString NAME_LEFT_ILLUMINATOR = "Левый (№3) иллюминатор";
const QString NAME_MATROX1 = "Matrox Monarch (1)";
const QString NAME_MATROX2 = "Matrox Monarch (2)";

namespace EnumDailyJournal{
    const QString VS_SIMULATOR = "ВС тренажёра";
    const QString LVS_TVA = "Управляющая программа";
    const QString UNKNOWN = "Неизвестный";
    const QString OPERATOR = "Оператор";
    const QString FACEPLATE = "Лицевая панель";
    const QString RECOVERY = "Восстановление системы";
    enum TypeMessage {Information, Error, Deviation, Recovery, NoAppropriate};
    enum TypeJournal {Functioning, Settings};  
}

//using namespace EnumDailyJournal;

//const int FISHPLUG              = 1;
const int COMMUTATORPROFITTPLUG = 2;
const int DAILYJOURNALPLUG      = 4;
const int UPSPOWERPLUG          = 6;
const int SELECTPROJECTORPLUG   = 777;
const int MITSUBISHIPROJECTORPLUG = 7;
const int PANASONICPROJECTORPLUG = 8;
const int MITSUBISHIPROJECTOR300PLUG = 9;
const int CSUDPPLUG             = 10;
const int BTNBINDPLUG           = 121;
const int COMSETTINGSPLUG       = 15;
const int IPSETTINGSPLUG        = 16;
const int ADDPROGPLUG           = 17;
const int TKNPLUG               = 18;
const int HUNTPLUG              = 19;
const int MNEMOPLUG             = 20;
const int TVSIGPLUG             = 21;
const int EXUPSSETTINGSPLUG     = 22;
const int DS116LVPLUG           = 23;
const int DS216MTPLUG           = 24;
const int TIMEPLUG              = 25;
const int CLEARMNEMOPLUG        = 26;
const int STARTEDITMNEMO        = 27;
const int ENDEDITMNEMO          = 28;
const int IPEXTSETTINGSPLUG     = 29;
const int BUILDPLUG             = 30; // 30L - 36L заняты
const int ECPLUG                = 37;
const int ECPLUGEd              = 38;
const int CONVERTERC2APLUG      = 39;
const int CONVERTERC2BPLUG      = 40;
const int REGPOWEROFFPLUG       = 41;
const int TOTALSHUTDOWNPLUG     = 42;
const int SELECTIONMODEPLUG     = 43;
const int CONTROLPASSWORDPLUG   = 44;
const int EDITPASSWORDPLUG      = 45;
const int RESETPASSWORDPLUG     = 46;
const int INFORMATIONPLUG       = 47;
const int ECPLUGEd2             = 48;
const int RECOVERYPLUG          = 49;
const int SCANCONVERTERSPLUG    = 50;
const int INDICATIONPLUG        = 51;
const int CONTROLMONITORPLUG    = 52;
const int BLACKMAGICMULTIPLEXER16_1 = 53;
const int BLACKMAGICMULTIPLEXER16_2 = 54;
const int BLACKMAGICMULTIPLEXER4PLUG = 55;
const int VIDEOREGISTRATOR8PLUG = 56;
const int VIDEOREGISTRATOR16PLUG = 57;
const int CAMERAPLUG = 58;
const int MATROXMONARCHPLUG = 59;
const int MULTIPLEXERS = 60;
const int DEFAULTPASSWORDPLUG   = 99;
const int PROFLEXPLUG           = 100;

///MENU
const int MENU      = 100;
const int SEPARATOR = 200;

const int MNEMOMENU = MNEMOPLUG+MENU;
const int CLEARMNEMOMENU = CLEARMNEMOPLUG+MENU;
const int STARTEDITMNEMOMENU = STARTEDITMNEMO+MENU;
const int ENDEDITMNEMOMENU = ENDEDITMNEMO+MENU;
const int SELECTPROJECTORMENU = SELECTPROJECTORPLUG+MENU;
const int SETTINGSPROJECTORMENU = SELECTPROJECTORPLUG+MENU+1;
const int HUNTPLUGMENU = HUNTPLUG+MENU;
const int BUILDMENU = BUILDPLUG+MENU;
const int CONVERTERC2AMENU = CONVERTERC2APLUG+MENU;
const int CONVERTERC2BMENU = CONVERTERC2BPLUG+MENU;
const int BTNBINDFORM = BTNBINDPLUG+MENU;
const int COMSETTINGSFORM = COMSETTINGSPLUG+MENU;
const int IPSETTINGSFORM = IPSETTINGSPLUG+MENU;
const int IPEXTSETTINGSFORM = IPEXTSETTINGSPLUG+MENU;
const int ADDPROGMENU = ADDPROGPLUG+MENU;
const int SCANCONVERTERSMENU = SCANCONVERTERSPLUG+MENU;
const int CAMERAMENU = CAMERAPLUG+MENU;
const int INFORMATIONMENU = INFORMATIONPLUG+MENU;

const int ECPLUGMENU = ECPLUG+MENU;
const int ECPLUGMENUEd1 = ECPLUGEd+MENU;
const int ECPLUGMENUEd2 = ECPLUGEd2+MENU+1;

const int EDITPASSWORDMENU = EDITPASSWORDPLUG+MENU;
const int RESETPASSWORDMENU = RESETPASSWORDPLUG+MENU;
const int DEFAULTPASSWORDMENU = DEFAULTPASSWORDPLUG+MENU;

const int MATROXMONARCH1MENU = MATROXMONARCHPLUG+MENU;
const int MATROXMONARCH2MENU = MATROXMONARCHPLUG+MENU+1;


#define PLUGUSER   3000L


#define CUDP_1   1L + PLUGUSER
#define TO_LOG   2L + PLUGUSER*/

const int KL163A        = 1;
const int KL105M        = 2;
const int KL160AM       = 3;
const int KL160M        = 4;
const int KL213A        = 5;

const int TEST_DEVICE_PROTOCOL  = 1001;
const int COMSETTINGSPLUG = 1002;
const int IPSETTINGSPLUG = 1003;
const int PVS_1616_V_PROTOCOL = 1004;
const int PROTOCOL_COM_DT_V24 = 1005;
const int GEN_40_19           = 1006;
const int OL_101102           = 1007;
const int OL_511              = 1008;
const int OL_521              = 1009;
const int OL_522              = 1010;
const int OL_523              = 1011;
const int N9000A503           = 1012;

const QString PVS_1616_V_NAME = "PVS1010V";

const int OL_101_102_DEV_ID = 5;
const int CODEC_MPEG_2_DEV_ID = 7;
const int QNAP_TS_431U_DEV_ID = 13;
const int WFM_7200_DEV_ID = 14;
const int PVS_1616_V_DEV_ID = 15;
const int PVS_6401V_DEV_ID = 16;
const int PVS_1616_HDSI_DEV_ID = 17;
const int PVS_3201_HDSI_DEV_ID = 18;
const int B_2350_DEV_ID = 19;
const int ATP_DEV_ID = 20;
const int D_LINK_DSG_1024A_A1A_DEV_ID = 21;
const int AFL_12A_N26_R_2G_DEV_ID = 22;
const int G_420 = 23;


///Configurations
namespace CFG {
    enum edit{ start = 0u, quit = 1u, save = 2u };
}

namespace POWER_STATE {
    enum P_STATE{ fault = 0u, alloff = 1u, oneon = 2u };
}

#define cfgEditSlot void ConfigurationEdit( uchar flag )
#define cfgEditConnect(src, dst) connect( src, SIGNAL(ConfigurationEdit( flag )), dst, SLOT(ConfigurationEdit( flag )) )



namespace CS{
    enum err { singleType = 0x1, powerOff = 0x2, unknowIntCommand = 0x8, errTV = 0x10, errPower220 = 0x20, errProj = 0x40, incorrectData = 0x80, incorrectDataSize = 0x400, unknownCommand = 0x800, errRGBHV = 0x2000, errPower12 = 0x4000 };
}

#include <QObject>
__attribute__((unused))
static bool IsSlotExists(QObject *obj, const char *slot_sign)
{
    if(obj == NULL) return false;
    if(obj->metaObject()->indexOfSlot(QMetaObject::normalizedSignature(qPrintable(slot_sign))) == -1) return false;
    return true;
}
__attribute__((unused))
static bool IsSignalExists(QObject *obj, const char *sign)
{
    if(obj == NULL) return false;
    if(obj->metaObject()->indexOfSignal(QMetaObject::normalizedSignature(qPrintable(sign))) == -1) return false;
    return true;
}

#include <windows.h>
#include <QTextCodec>
#include <QByteArray>
__attribute__((unused))
static LPCSTR UTF2LPSTR( QString str ){
    QTextCodec *codec = QTextCodec::codecForName("CP1251");
    QByteArray encodedString = codec->fromUnicode(str);
    return (LPCSTR)encodedString;
}

typedef struct EXTCode{
    EXTCode(){restore_flag = 0;}
    EXTCode( int _id, int _flag, BYTE _PowerOn, bool IsNetwork, int rflag, int bldID ){
        buildID = bldID;
        restore_flag = rflag;
        btn_id = _id;
        flags = _flag | (IsNetwork == true ? cmd_network : 0);
        PowerOn = _PowerOn;        
    }
    EXTCode( int _id, int _flag, BYTE _PowerOn, int rflag ){
        restore_flag = rflag;
        btn_id = _id;
        flags = _flag;
        PowerOn = _PowerOn;
    }

    /*void setVal( int _id, int _flag, bool _PowerOn){
        btn_id = _id;
        flags   = _flag;
        PowerOn = _PowerOn;
    }*/
    enum { btnClick = 1L, monitor = 2L, hook = 4L, cmd_network = 8L, abrt = 16L };
    int  btn_id;
    BYTE PowerOn;
    int  flags;    
    int  restore_flag;
    int  buildID;
}TEXTCode;

struct SPowerUpdate{
    SPowerUpdate(){}
    SPowerUpdate(uint _devID, uint _status){ devID = _devID; status = _status; }
    uint devID;
    uint status;
};

struct SCommutateUpdate{
    uint input;
    uint output;
};

enum POWER{ P_NETWORK = 1L, P_OFF = 2L, P_ON = 4L, P_NOCONFIRM = 8L, P_COOP = 16L };
enum MONITORINPUT{ ON = 1L, OFF = 2L, HDMI_1 = 4L, HDMI_2 = 8L, AV = 16L, COOP=32L };

#define ORANGE      RGB( 70, 180, 255)
#define DARK_GREEN  RGB(  0, 166,   0)
#define GREEN       RGB(  0, 196,   0)
#define RED         RGB(  0,   0, 255)
#define DARK_RED    RGB(  0,   0, 225)
#define YELLOW      RGB(  0, 255, 255)
#define DARK_YELLOW RGB(  0, 240, 240)
#define VIOLET      RGB(147, 112, 219)
#define DARK_VIOLET RGB(133, 101, 198)
#define GREY        RGB(128, 128, 128)
#define BLUE        RGB(255,   0,   0)
#define DARK_BLUE   RGB(225,   0,   0)

#include <QColor>
__attribute__((unused))
static QColor convertStringToColor(QString str_color)
{
    if (str_color == "yellow") {
        return QColor(YELLOW);
    } else if (str_color == "red") {
        return QColor(RED);
    } else if (str_color == "green") {
        return QColor(GREEN);
    } else if (str_color == "violet") {
        return QColor(VIOLET);
    } else if (str_color == "dark_yellow") {
        return QColor(DARK_YELLOW);
    } else if (str_color == "dark_red") {
        return QColor(DARK_RED);
    } else if (str_color == "dark_green") {
        return QColor(DARK_GREEN);
    } else if (str_color == "dark_violet") {
        return QColor(DARK_VIOLET);
    } else if (str_color == "orange") {
        return QColor(ORANGE);
    }

    return QColor();
}

__attribute__((unused))
static QString convertColorToString(QColor color)
{
    if (color == QColor(YELLOW)) {
        return "yellow";
    } else if (color == QColor(RED)) {
        return "red";
    } else if (color == QColor(GREEN)) {
        return "green";
    } else if (color == QColor(VIOLET)) {
        return "violet";
    } else if (color == QColor(DARK_YELLOW)) {
        return "dark_yellow";
    } else if (color == QColor(DARK_RED)) {
        return "dark_red";
    } else if (color == QColor(DARK_GREEN)) {
        return "dark_green";
    } else if (color == QColor(DARK_VIOLET)) {
        return "dark_violet";
    } else if (color == QColor(ORANGE)) {
        return "orange";
    }

    return QString();
}

#define FONT_FAMILY_APP "Times New Roman"
#define FONT_SIZE_CAPTION_APP 12
#define FONT_SIZE_APP 9

#include <QWidget>
#include <QGraphicsDropShadowEffect>

__attribute__((unused))
static void setShadowWidget(QWidget *widget)
{
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect();
    shadowEffect->setXOffset(2);
    shadowEffect->setYOffset(2);
    widget->setGraphicsEffect(shadowEffect);
}

#include "db.h"
/*__attribute__((unused))
static bool isCrashSystem(dbsqlite* database)
{
    if ((*database)->exec(QString("SELECT recovery_data FROM recovery WHERE plugid = %1;").arg(RECOVERYPLUG))) {
        while ((*database)->next()) {
            return (*database)->value("recovery_data").toString() == "Y";
        }
    }

    return false;
}

__attribute__((unused))
static TYPE_SCREEN ReadTypeScreen(dbsqlite* database)
{
    if ((*database)->exec(QString("SELECT type_screen FROM CommonData"))) {
        while ((*database)->next()) {
            QString typeScreen = (*database)->value("type_screen").toString();
            if (typeScreen == "Diffusing") return DIFFUSING;
            else if (typeScreen == "Lens") return LENS;
        }
    }

    return NONE;
}*/

#endif
