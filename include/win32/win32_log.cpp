#include "win32_log.h"
#include <unordered_map>
#include <mutex>
#define MAP_PAIR(x) { x , (#x) }
#define SWITCH_CASE(x) case x: return (#x);

namespace
{
	

	std::mutex ss_mutex;
	char max_string_buffer[256] = "";
	std::stringstream ss;

	const std::unordered_map<UINT, std::string> Win32MessageMapping =
	{
		MAP_PAIR(WM_NULL),
		MAP_PAIR(WM_CREATE),
		MAP_PAIR(WM_DESTROY),
		MAP_PAIR(WM_MOVE),
		MAP_PAIR(WM_SIZE),
		MAP_PAIR(WM_ACTIVATE),
		MAP_PAIR(WM_SETFOCUS),
		MAP_PAIR(WM_KILLFOCUS),
		MAP_PAIR(WM_ENABLE),
		MAP_PAIR(WM_SETREDRAW),
		MAP_PAIR(WM_SETTEXT),
		MAP_PAIR(WM_GETTEXT),
		MAP_PAIR(WM_GETTEXTLENGTH),
		MAP_PAIR(WM_PAINT),
		MAP_PAIR(WM_CLOSE),
		MAP_PAIR(WM_QUERYENDSESSION),
		MAP_PAIR(WM_QUIT),
		MAP_PAIR(WM_QUERYOPEN),
		MAP_PAIR(WM_ERASEBKGND),
		MAP_PAIR(WM_SYSCOLORCHANGE),
		MAP_PAIR(WM_ENDSESSION),
		MAP_PAIR(WM_SHOWWINDOW),
		MAP_PAIR(WM_ACTIVATEAPP),
		MAP_PAIR(WM_FONTCHANGE),
		MAP_PAIR(WM_TIMECHANGE),
		MAP_PAIR(WM_CANCELMODE),
		MAP_PAIR(WM_SETCURSOR),
		MAP_PAIR(WM_MOUSEACTIVATE),
		MAP_PAIR(WM_CHILDACTIVATE),
		MAP_PAIR(WM_QUEUESYNC),
		MAP_PAIR(WM_GETMINMAXINFO),
		MAP_PAIR(WM_PAINTICON),
		MAP_PAIR(WM_ICONERASEBKGND),
		MAP_PAIR(WM_NEXTDLGCTL),
		MAP_PAIR(WM_SPOOLERSTATUS),
		MAP_PAIR(WM_DRAWITEM),
		MAP_PAIR(WM_MEASUREITEM),
		MAP_PAIR(WM_DELETEITEM),
		MAP_PAIR(WM_VKEYTOITEM),
		MAP_PAIR(WM_CHARTOITEM),
		MAP_PAIR(WM_SETFONT),
		MAP_PAIR(WM_GETFONT),
		MAP_PAIR(WM_SETHOTKEY),
		MAP_PAIR(WM_GETHOTKEY),
		MAP_PAIR(WM_QUERYDRAGICON),
		MAP_PAIR(WM_COMPAREITEM),
		MAP_PAIR(WM_GETOBJECT),
		MAP_PAIR(WM_COMPACTING),
		MAP_PAIR(WM_WINDOWPOSCHANGING),
		MAP_PAIR(WM_WINDOWPOSCHANGED),
		MAP_PAIR(WM_POWER),
		MAP_PAIR(WM_COPYDATA),
		MAP_PAIR(WM_CANCELJOURNAL),
		MAP_PAIR(WM_NOTIFY),
		MAP_PAIR(WM_INPUTLANGCHANGEREQUEST),
		MAP_PAIR(WM_INPUTLANGCHANGE),
		MAP_PAIR(WM_TCARD),
		MAP_PAIR(WM_HELP),
		MAP_PAIR(WM_USERCHANGED),
		MAP_PAIR(WM_NOTIFYFORMAT),
		MAP_PAIR(WM_CONTEXTMENU),
		MAP_PAIR(WM_STYLECHANGING),
		MAP_PAIR(WM_STYLECHANGED),
		MAP_PAIR(WM_DISPLAYCHANGE),
		MAP_PAIR(WM_GETICON),
		MAP_PAIR(WM_SETICON),
		MAP_PAIR(WM_NCCREATE),
		MAP_PAIR(WM_NCDESTROY),
		MAP_PAIR(WM_NCCALCSIZE),
		MAP_PAIR(WM_NCHITTEST),
		MAP_PAIR(WM_NCPAINT),
		MAP_PAIR(WM_NCACTIVATE),
		MAP_PAIR(WM_GETDLGCODE),
		MAP_PAIR(WM_NCMOUSEMOVE),
		MAP_PAIR(WM_NCLBUTTONDOWN),
		MAP_PAIR(WM_NCLBUTTONUP),
		MAP_PAIR(WM_NCLBUTTONDBLCLK),
		MAP_PAIR(WM_NCRBUTTONDOWN),
		MAP_PAIR(WM_NCRBUTTONUP),
		MAP_PAIR(WM_NCRBUTTONDBLCLK),
		MAP_PAIR(WM_NCMBUTTONDOWN),
		MAP_PAIR(WM_NCMBUTTONUP),
		MAP_PAIR(WM_NCMBUTTONDBLCLK),
		MAP_PAIR(WM_KEYDOWN),
		MAP_PAIR(WM_KEYUP),
		MAP_PAIR(WM_CHAR),
		MAP_PAIR(WM_DEADCHAR),
		MAP_PAIR(WM_SYSKEYDOWN),
		MAP_PAIR(WM_SYSKEYUP),
		MAP_PAIR(WM_SYSCHAR),
		MAP_PAIR(WM_SYSDEADCHAR),
		MAP_PAIR(WM_KEYLAST),
		MAP_PAIR(WM_INITDIALOG),
		MAP_PAIR(WM_COMMAND),
		MAP_PAIR(WM_SYSCOMMAND),
		MAP_PAIR(WM_TIMER),
		MAP_PAIR(WM_HSCROLL),
		MAP_PAIR(WM_VSCROLL),
		MAP_PAIR(WM_INITMENU),
		MAP_PAIR(WM_INITMENUPOPUP),
		MAP_PAIR(WM_MENUSELECT),
		MAP_PAIR(WM_MENUCHAR),
		MAP_PAIR(WM_ENTERIDLE),
		MAP_PAIR(WM_MENURBUTTONUP),
		MAP_PAIR(WM_MENUDRAG),
		MAP_PAIR(WM_MENUGETOBJECT),
		MAP_PAIR(WM_UNINITMENUPOPUP),
		MAP_PAIR(WM_MENUCOMMAND),
		MAP_PAIR(WM_CHANGEUISTATE),
		MAP_PAIR(WM_UPDATEUISTATE),
		MAP_PAIR(WM_QUERYUISTATE),
		MAP_PAIR(WM_CTLCOLORMSGBOX),
		MAP_PAIR(WM_CTLCOLOREDIT),
		MAP_PAIR(WM_CTLCOLORLISTBOX),
		MAP_PAIR(WM_CTLCOLORBTN),
		MAP_PAIR(WM_CTLCOLORDLG),
		MAP_PAIR(WM_CTLCOLORSCROLLBAR),
		MAP_PAIR(WM_CTLCOLORSTATIC),
		MAP_PAIR(WM_MOUSEMOVE),
		MAP_PAIR(WM_LBUTTONDOWN),
		MAP_PAIR(WM_LBUTTONUP),
		MAP_PAIR(WM_LBUTTONDBLCLK),
		MAP_PAIR(WM_RBUTTONDOWN),
		MAP_PAIR(WM_RBUTTONUP),
		MAP_PAIR(WM_RBUTTONDBLCLK),
		MAP_PAIR(WM_MBUTTONDOWN),
		MAP_PAIR(WM_MBUTTONUP),
		MAP_PAIR(WM_MBUTTONDBLCLK),
		MAP_PAIR(WM_MOUSEWHEEL),
		MAP_PAIR(WM_MOUSELAST),
		MAP_PAIR(WM_PARENTNOTIFY),
		MAP_PAIR(WM_ENTERMENULOOP),
		MAP_PAIR(WM_EXITMENULOOP),
		MAP_PAIR(WM_NEXTMENU),
		MAP_PAIR(WM_SIZING),
		MAP_PAIR(WM_CAPTURECHANGED),
		MAP_PAIR(WM_MOVING),
		MAP_PAIR(WM_POWERBROADCAST),
		MAP_PAIR(WM_DEVICECHANGE),
		MAP_PAIR(WM_IME_STARTCOMPOSITION),
		MAP_PAIR(WM_IME_ENDCOMPOSITION),
		MAP_PAIR(WM_IME_COMPOSITION),
		MAP_PAIR(WM_IME_SETCONTEXT),
		MAP_PAIR(WM_IME_NOTIFY),
		MAP_PAIR(WM_IME_CONTROL),
		MAP_PAIR(WM_IME_COMPOSITIONFULL),
		MAP_PAIR(WM_IME_SELECT),
		MAP_PAIR(WM_IME_CHAR),
		MAP_PAIR(WM_IME_REQUEST),
		MAP_PAIR(WM_IME_KEYDOWN),
		MAP_PAIR(WM_IME_KEYUP),
		MAP_PAIR(WM_MDICREATE),
		MAP_PAIR(WM_MDIDESTROY),
		MAP_PAIR(WM_MDIACTIVATE),
		MAP_PAIR(WM_MDIRESTORE),
		MAP_PAIR(WM_MDINEXT),
		MAP_PAIR(WM_MDIMAXIMIZE),
		MAP_PAIR(WM_MDITILE),
		MAP_PAIR(WM_MDICASCADE),
		MAP_PAIR(WM_MDIICONARRANGE),
		MAP_PAIR(WM_MDIGETACTIVE),
		MAP_PAIR(WM_MDISETMENU),
		MAP_PAIR(WM_ENTERSIZEMOVE),
		MAP_PAIR(WM_EXITSIZEMOVE),
		MAP_PAIR(WM_DROPFILES),
		MAP_PAIR(WM_MDIREFRESHMENU),
		MAP_PAIR(WM_MOUSEHOVER),
		MAP_PAIR(WM_MOUSELEAVE),
		MAP_PAIR(WM_CUT),
		MAP_PAIR(WM_COPY),
		MAP_PAIR(WM_PASTE),
		MAP_PAIR(WM_CLEAR),
		MAP_PAIR(WM_UNDO),
		MAP_PAIR(WM_RENDERFORMAT),
		MAP_PAIR(WM_RENDERALLFORMATS),
		MAP_PAIR(WM_DESTROYCLIPBOARD),
		MAP_PAIR(WM_DRAWCLIPBOARD),
		MAP_PAIR(WM_PAINTCLIPBOARD),
		MAP_PAIR(WM_VSCROLLCLIPBOARD),
		MAP_PAIR(WM_SIZECLIPBOARD),
		MAP_PAIR(WM_ASKCBFORMATNAME),
		MAP_PAIR(WM_CHANGECBCHAIN),
		MAP_PAIR(WM_HSCROLLCLIPBOARD),
		MAP_PAIR(WM_QUERYNEWPALETTE),
		MAP_PAIR(WM_PALETTEISCHANGING),
		MAP_PAIR(WM_PALETTECHANGED),
		MAP_PAIR(WM_HOTKEY),
		MAP_PAIR(WM_PRINT),
		MAP_PAIR(WM_PRINTCLIENT),
		MAP_PAIR(WM_HANDHELDFIRST),
		MAP_PAIR(WM_HANDHELDLAST),
		MAP_PAIR(WM_PENWINFIRST),
		MAP_PAIR(WM_DDE_INITIATE),
		MAP_PAIR(WM_PENWINLAST),
		MAP_PAIR(WM_DDE_TERMINATE),
		MAP_PAIR(WM_DDE_ADVISE),
		MAP_PAIR(WM_DDE_UNADVISE),
		MAP_PAIR(WM_DDE_ACK),
		MAP_PAIR(WM_DDE_DATA),
		MAP_PAIR(WM_DDE_REQUEST),
		MAP_PAIR(WM_DDE_POKE),
		MAP_PAIR(WM_DDE_EXECUTE),
		MAP_PAIR(WM_APP),
		MAP_PAIR(WM_USER),
		MAP_PAIR(WM_NCMOUSELEAVE)
	};


}






namespace PO
{
	namespace Platform
	{
		namespace Win32
		{
			namespace Log
			{
				std::string translate_error_code_to_string(DWORD code) noexcept
				{
					std::lock_guard<decltype(ss_mutex)> lg(ss_mutex);
					DWORD resault = FormatMessageA(
						FORMAT_MESSAGE_FROM_SYSTEM,
						nullptr,
						code,
						0, // language identifier
						max_string_buffer,
						255,
						nullptr
					);
					if (resault == 0)
					{
						ss.clear();
						ss << code;
						std::string Tem;
						ss >> Tem;
						return "unknow error code - " + Tem;
					}
					return std::string(max_string_buffer);
				}

				std::string translate_event_type_to_string(UINT type) noexcept
				{
					auto ptr = Win32MessageMapping.find(type);
					if (ptr != Win32MessageMapping.end())
						return ptr->second;

					std::lock_guard<decltype(ss_mutex)> lg(ss_mutex);
					ss.clear();
					ss << type;
					std::string str;
					ss >> str;
					return "unknow event with code: " + str;
				}

			}
		}
	}
}