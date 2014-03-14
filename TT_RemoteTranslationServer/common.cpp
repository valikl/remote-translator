/*
 * Copyright (c) 2005-2013, BearWare.dk
 *
 * Contact Information:
 *
 * Bjoern D. Rasmussen
 * Bedelundvej 79
 * DK-9830 Taars
 * Denmark
 * Email: contact@bearware.dk
 * Phone: +45 20 20 54 59
 * Web: http://www.bearware.dk
 *
 * This source code is part of the TeamTalk 4 SDK owned by
 * BearWare.dk. All copyright statements may not be removed
 * or altered from any source distribution. If you use this
 * software in a product, an acknowledgment in the product
 * documentation is required.
 *
 */

#include "common.h"
#include "mainwindow.h"

#include <QSound>
#include <QDateTime>

extern QSettings* ttSettings;
extern TTInstance* ttInst;

bool getSoundDevice(int deviceid, const QVector<SoundDevice>& devs,
                    SoundDevice& dev)
{
    for(int i=0;i<devs.size();i++)
        if(devs[i].nDeviceID == deviceid)
        {
            dev = devs[i];
            return true;
        }
    return false;
}

bool getSoundDevice(const QString& devid, const QVector<SoundDevice>& devs,
                    SoundDevice& dev)
{
    if(devid.isEmpty())
        return false;

    for(int i=0;i<devs.size();i++)
        if(_Q(devs[i].szDeviceID) == devid)
        {
            dev = devs[i];
            return true;
        }
    return false;
}


#ifdef Q_OS_DARWIN
QString QCFStringToQString(CFStringRef str)
{
    if(!str)
        return QString();
    CFIndex length = CFStringGetLength(str);
    const UniChar *chars = CFStringGetCharactersPtr(str);
    if (chars)
        return QString(reinterpret_cast<const QChar *>(chars), length);

    QVector<UniChar> buffer(length);
    CFStringGetCharacters(str, CFRangeMake(0, length), buffer.data());
    return QString(reinterpret_cast<const QChar *>(buffer.constData()), length);
}

QString TranslateKey(quint8 vk)
{
    TISInputSourceRef currentKeyboard = TISCopyCurrentKeyboardInputSource();
    const CFDataRef layoutData =
        reinterpret_cast<const CFDataRef>(TISGetInputSourceProperty(currentKeyboard,
                                          kTISPropertyUnicodeKeyLayoutData) );

    const UCKeyboardLayout *keyboardLayout =
        reinterpret_cast<const UCKeyboardLayout*>(CFDataGetBytePtr(layoutData));

    UInt32 keysDown = 0;
    UniChar chars[10];
    UniCharCount realLength = 0;

    OSStatus oss = UCKeyTranslate(keyboardLayout,
                                  vk,
                                  kUCKeyActionDown,
                                  0,
                                  LMGetKbdType(),
                                  0,//kUCKeyTranslateNoDeadKeysBit,
                                  &keysDown,
                                  sizeof(chars) / sizeof(chars[0]),
                                  &realLength,
                                  chars);
    Q_ASSERT(oss == 0);

    CFStringRef ptr_str = CFStringCreateWithCharacters(kCFAllocatorDefault,
                                                       chars, (int)realLength);
    QString ss = QCFStringToQString(ptr_str);
    CFRelease(ptr_str);
    CFRelease(currentKeyboard);
    return ss;
}

QString GetMacOSHotKeyText(const hotkey_t& hotkey)
{
    if(hotkey.size() == 0)
        return QString();

    QString comp;
    if(hotkey.size()==2)
    {
        if(hotkey[0] & cmdKey)
            comp += comp.size()? " + Cmd" : "Cmd";
        if(hotkey[0] & shiftKey)
            comp += comp.size()? " + Shift" : "Shift";
        if(hotkey[0] & optionKey)
            comp += comp.size()? " + Option" : "Option";
        if(hotkey[0] & controlKey)
            comp += comp.size()? "+ Ctrl" : "Ctrl";
    }

    quint8 vk = hotkey.size()==2? hotkey[1] : hotkey[0];
    QString tmp;
    switch(vk)
    {
    case kVK_ANSI_A:
    case kVK_ANSI_S:
    case kVK_ANSI_D:
    case kVK_ANSI_F:
    case kVK_ANSI_H:
    case kVK_ANSI_G:
    case kVK_ANSI_Z:
    case kVK_ANSI_X:
    case kVK_ANSI_C:
    case kVK_ANSI_V:
    case kVK_ANSI_B:
    case kVK_ANSI_Q:
    case kVK_ANSI_W:
    case kVK_ANSI_E:
    case kVK_ANSI_R:
    case kVK_ANSI_Y:
    case kVK_ANSI_T:
    case kVK_ANSI_1:
    case kVK_ANSI_2:
    case kVK_ANSI_3:
    case kVK_ANSI_4:
    case kVK_ANSI_6:
    case kVK_ANSI_5:
    case kVK_ANSI_Equal:
    case kVK_ANSI_9:
    case kVK_ANSI_7:
    case kVK_ANSI_Minus:
    case kVK_ANSI_8:
    case kVK_ANSI_0:
    case kVK_ANSI_RightBracket:
    case kVK_ANSI_O:
    case kVK_ANSI_U:
    case kVK_ANSI_LeftBracket:
    case kVK_ANSI_I:
    case kVK_ANSI_P:
    case kVK_ANSI_L:
    case kVK_ANSI_J:
    case kVK_ANSI_Quote:
    case kVK_ANSI_K:
    case kVK_ANSI_Semicolon:
    case kVK_ANSI_Backslash:
    case kVK_ANSI_Comma:
    case kVK_ANSI_Slash:
    case kVK_ANSI_N:
    case kVK_ANSI_M:
    case kVK_ANSI_Period:
    case kVK_ANSI_Grave:
    case kVK_ANSI_KeypadDecimal:
    case kVK_ANSI_KeypadMultiply:
    case kVK_ANSI_KeypadPlus:
    case kVK_ANSI_KeypadClear:
    case kVK_ANSI_KeypadDivide:
    case kVK_ANSI_KeypadEnter:
    case kVK_ANSI_KeypadMinus:
    case kVK_ANSI_KeypadEquals:
    case kVK_ANSI_Keypad0:
    case kVK_ANSI_Keypad1:
    case kVK_ANSI_Keypad2:
    case kVK_ANSI_Keypad3:
    case kVK_ANSI_Keypad4:
    case kVK_ANSI_Keypad5:
    case kVK_ANSI_Keypad6:
    case kVK_ANSI_Keypad7:
    case kVK_ANSI_Keypad8:
    case kVK_ANSI_Keypad9:
        tmp = TranslateKey(vk);
        break;
    case kVK_Return:
        tmp = "Return";break;
    case kVK_Tab:
        tmp = "Tab";break;
    case kVK_Space:
        tmp = "Space";break;
    case kVK_Delete:
        tmp = "BackSpace";break;
    case kVK_Escape:
        tmp = "Esc";break;
        //case kVK_Command:
        //case kVK_Shift:
    case kVK_CapsLock:
        tmp = "CapsLock";break;
        //case kVK_Option:
        //case kVK_Control:
        //case kVK_RightShift:
        //case kVK_RightOption:
        //case kVK_RightControl:
    case kVK_Function:
        tmp = "Fn";break;
    case kVK_F17:
        tmp = "F17";break;
    case kVK_VolumeUp:
        tmp = "VolUp";break;
    case kVK_VolumeDown:
        tmp = "VolDown";break;
    case kVK_Mute:
        tmp = "Mute";break;
    case kVK_F18:
        tmp = "F18";break;
    case kVK_F19:
        tmp = "F19";break;
    case kVK_F20:
        tmp = "F20";break;
    case kVK_F5:
        tmp = "F5";break;
    case kVK_F6:
        tmp = "F6";break;
    case kVK_F7:
        tmp = "F7";break;
    case kVK_F3:
        tmp = "F3";break;
    case kVK_F8:
        tmp = "F8";break;
    case kVK_F9:
        tmp = "F9";break;
    case kVK_F11:
        tmp = "F11";break;
    case kVK_F13:
        tmp = "F13";break;
    case kVK_F16:
        tmp = "F16";break;
    case kVK_F14:
        tmp = "F14";break;
    case kVK_F10:
        tmp = "F10";break;
    case kVK_F12:
        tmp = "F12";break;
    case kVK_F15:
        tmp = "F15";break;
    case kVK_Help:
        tmp = "Help";break;
    case kVK_Home:
        tmp = "Home";break;
    case kVK_PageUp:
        tmp = "PgUp";break;
    case kVK_ForwardDelete:
        tmp = "Delete";break;
    case kVK_F4:
        tmp = "F4";break;
    case kVK_End:
        tmp = "End";break;
    case kVK_F2:
        tmp = "F2";break;
    case kVK_PageDown:
        tmp = "PgDown";break;
    case kVK_F1:
        tmp = "F1";break;
    case kVK_LeftArrow:
        tmp = "Left";break;
    case kVK_RightArrow:
        tmp = "Right";break;
    case kVK_DownArrow:
        tmp = "Down";break;
    case kVK_UpArrow:
        tmp = "Up";break;
    default:
        tmp += QString::number(vk);
    }
    comp += comp.size()? " + " + tmp : tmp;
    return comp;
}
#endif


QString GetHotKeyText(const hotkey_t& hotkey)
{
#ifdef Q_OS_WIN32
    QString key;
    for(int i=0;i<hotkey.size();i++)
    {
        TTCHAR buff[TT_STRLEN] = {0};
        TT_HotKey_GetKeyString(ttInst, hotkey[i], buff);
        key += (i == hotkey.size()-1)? _Q(buff):_Q(buff) + " + ";
    }
    return key;
#elif defined(Q_OS_LINUX)
    Q_UNUSED(ttInst);
    int keys[4] = {0, 0, 0, 0};
    for(int i=0;i<hotkey.size();i++)
        keys[i] = hotkey[i];

    QKeySequence keyseq(keys[0], keys[1], keys[2], keys[3]);
    return keyseq.toString();
#elif defined(Q_OS_DARWIN)
    Q_UNUSED(ttInst);
    /*
    QString key;
    if(hotkey.size())
        key = QString::number(hotkey[0]);

    for(int i=1;i<hotkey.size();i++)
        key += " + " + QString::number(hotkey[i]);

    return key;
    */
    return GetMacOSHotKeyText(hotkey);
#else
    return QString("Unknown");
#endif

}


#if defined(Q_OS_WIN32) && !defined(Q_OS_WINCE)
bool IsComputerIdle(int idle_secs)
{
    LASTINPUTINFO info;
    info.cbSize = sizeof(LASTINPUTINFO);
    if( GetLastInputInfo(&info))
         return (::GetTickCount() - info.dwTime) / 1000 >= (UINT)idle_secs;
    else
        return false;
}
#elif defined(Q_OS_DARWIN)
#include <IOKit/IOKitLib.h>
bool IsComputerIdle(int idle_secs)
{
    int64_t os_idle_secs = 0;
    io_iterator_t iter = 0;
    if (IOServiceGetMatchingServices(kIOMasterPortDefault,
                                     IOServiceMatching("IOHIDSystem"),
                                     &iter) == KERN_SUCCESS)
    {
        io_registry_entry_t entry = IOIteratorNext(iter);
        if (entry)
        {
            CFMutableDictionaryRef dict = NULL;
            if (IORegistryEntryCreateCFProperties(entry, &dict,
                                                  kCFAllocatorDefault,
                                                  0) == KERN_SUCCESS)
            {
                CFNumberRef obj = static_cast<CFNumberRef>
                (CFDictionaryGetValue(dict,
                                      CFSTR("HIDIdleTime")));
                if (obj)
                {
                    int64_t nanoseconds = 0;
                    if (CFNumberGetValue(obj, kCFNumberSInt64Type,
                                         &nanoseconds))
                    {
// Divide by 10^9 to convert from nanoseconds to seconds.
                        os_idle_secs = (nanoseconds >> 30);
                    }
                }
                CFRelease(dict);
            }
            IOObjectRelease(entry);
        }
        IOObjectRelease(iter);
    }
    return (int)os_idle_secs > idle_secs;
}
#else
bool IsComputerIdle(int idle_secs)
{
    return false;
}
#endif



int gainLevel(int ref_volume)
{
    if(ref_volume <= SOUND_VOLUME_MAX)
        return SOUND_GAIN_DEFAULT;

    float gain = ref_volume/(float)SOUND_VOLUME_MAX;
    gain *= SOUND_GAIN_DEFAULT;
    return gain;
}

bool VersionSameOrLater(const QString& check, const QString& against)
{
    if(check == against) return true;

    QStringList chk_tokens = check.split(".");
    QStringList against_tokens = against.split(".");

    QVector<int> vec_chk, vec_against;
    for(int i=0;i<chk_tokens.size();i++)
        vec_chk.push_back(chk_tokens[i].toInt());
    for(int i=0;i<against_tokens.size();i++)
        vec_against.push_back(against_tokens[i].toInt());

    int less = vec_chk.size() < vec_against.size()?vec_chk.size():vec_against.size();

    for(int i=0;i<less;i++)
        if(vec_chk[i] < vec_against[i])
            return false;
        else if(vec_chk[i] > vec_against[i])
            return true;

    return true;
}

QString GetDateTimeStamp()
{
    return QDateTime::currentDateTime().toString("yyyyMMdd-hhmmss");
}

QString GenerateAudioStorageFilename(AudioFileFormat aff)
{
    QString filename = GetDateTimeStamp() + " ";
    filename += QObject::tr("Conference");
    switch(aff)
    {
    case AFF_WAVE_FORMAT :
        filename += ".wav";
        break;
    case AFF_MP3_16KBIT_FORMAT :
    case AFF_MP3_32KBIT_FORMAT :
    case AFF_MP3_64KBIT_FORMAT :
    case AFF_MP3_128KBIT_FORMAT :
    case AFF_MP3_256KBIT_FORMAT :
        filename += ".mp3";
        break;
    case AFF_NONE :
        break;
    }
    return filename;
}

void setVideoTextBox(const QRect& rect, const QColor& bgcolor,
                     const QColor& fgcolor, const QString& text,
                     quint32 text_pos, int w_percent, int h_percent,
                     QPainter& painter)
{
    int w = w_percent / 100. * rect.width();
    int h = h_percent / 100. * rect.height();

    int x, y;
    switch(text_pos & VIDTEXT_POSITION_MASK)
    {
    case VIDTEXT_POSITION_TOPLEFT :
        x = 0; y = 0;
        break;
    case VIDTEXT_POSITION_TOPRIGHT :
        x = rect.width() - w;
        y = 0;
        break;
    case VIDTEXT_POSITION_BOTTOMLEFT :
        x = 0;
        y = rect.height() - h;
        break;
    case VIDTEXT_POSITION_BOTTOMRIGHT :
    default :
        x = rect.width() - w;
        y = rect.height() - h;
        break;
    }

    if(h>0 && w>0)
    {
        const QFont font = painter.font();
        if(font.pixelSize() != h)
        {
            QFont newFont(font);
            newFont.setPixelSize(h);
            painter.setFont(newFont);
        }
        painter.fillRect(x, y, w, h, bgcolor);
        painter.setPen(fgcolor);
        painter.drawText(x, y, w, h, Qt::AlignHCenter | Qt::AlignCenter, text);

        if(font.pixelSize() != h)
            painter.setFont(font);
    }

}
