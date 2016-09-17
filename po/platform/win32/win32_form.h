#pragma once
#include <Windows.h>
#include <string>
#include "log\win32_log.h"
#include "../../tool/mail.h"
#include "../../event/event.h"
#include <mutex>
#include <atomic>
#include <future>
#include <chrono>
#include <thread>
namespace PO
{
	namespace Platform
	{
		namespace Win32
		{
			struct win32_init_error :std::exception
			{
				virtual char const* what() const override
				{
					return "unable to create win32 form";
				}
			};

			namespace Assistant
			{
				struct win32_style
				{
					DWORD window_style = WS_VISIBLE | WS_OVERLAPPEDWINDOW;
					DWORD ex_window_style = WS_EX_CLIENTEDGE;
				};
			}
			

			struct win32_initializer
			{
				std::u16string title = u"PO default title :>";
				int shitf_x = (GetSystemMetrics(SM_CXSCREEN) - 1024) / 2;
				int shift_y = (GetSystemMetrics(SM_CYSCREEN) - 768) / 2;
				int width = 1024;
				int height = 768;
				Assistant::win32_style style = Assistant::win32_style();
			};
			

			class win32_form
			{
				HWND raw_handle = nullptr;
				std::atomic_bool avalible;
				Mail::single_mail_completeness_request<bool(const event&)> respond_call_back;
			public:
				template<typename ...AT>
				decltype(auto) bind_event_function(AT&& ...at) { return respond_call_back.bind(std::forward<AT>(at)...); }
				using event_receipt = decltype(respond_call_back)::receipt;
				bool window_close = false;
				HWND raw() const { return raw_handle; }
				operator bool() const 
				{
					return avalible; 
				}
				win32_form(
					const win32_initializer& = win32_initializer()
					);
				~win32_form();
				bool reapond_window_evnet(const PO::event&);
				void close_window() { avalible = false; }
				void wait_for_close(const std::chrono::duration<long long, std::ratio<1, 1000>>& time) 
				{
					while (avalible) 
					{ 
						std::this_thread::sleep_for(time); 
					} 
				}
			};

		}
	}
}