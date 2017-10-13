#pragma once
#include <chrono>
#include <stdint.h>
#include "..\tool\tool.h"
#include "..\tool\thread_tool.h"
#include "event.h"
namespace PO
{
	using duration = std::chrono::duration<long long, std::ratio<1, 1000>>;
	using time_point = std::chrono::time_point<std::chrono::system_clock>;

	inline decltype(auto) get_time_now() { return std::chrono::system_clock::now(); }

	struct time_calculator
	{
		time_point record_point;
		duration require_duration;
	public:
		time_calculator(time_calculator&) = default;
		time_calculator(duration du = duration(10)) : record_point(get_time_now()), require_duration(du) {}
		void set_duration(duration du) { require_duration = du; }
		bool tick(time_point tp, duration& dua);
	};


	class binary
	{
		std::shared_ptr<std::vector<char>> ptr;
	public:
		class weak_ref
		{
			std::weak_ptr<std::vector<char>> ptr;
			friend class binary;
		public:
			weak_ref() = default;
			weak_ref(const binary& b) : ptr(b.ptr) {}
			weak_ref(const weak_ref&) = default;
			weak_ref(weak_ref&&) = default;
			weak_ref& operator=(const weak_ref&) = default;
			weak_ref& operator=(weak_ref&&) = default;
			operator bool() const { return !ptr.expired(); }
			binary lock() const { binary tem; tem.ptr = ptr.lock(); return tem; }
			bool operator ==(const weak_ref& b) const { return ptr.owner_before(b.ptr); }
		};

		binary() {}
		binary(size_t s) { ptr = std::make_shared<std::vector<char>>(s, '\0'); }

		bool operator ==(const binary& b) const { return ptr == b.ptr; }

		binary(const binary& b) = default;
		binary(binary&& b) = default;
		binary& operator=(binary&&) = default;
		binary& operator=(const binary&) = default;
		void reset() { ptr.reset(); }
		uint64_t size() const
		{ 
			return ptr ? ptr->size() : 0;
		}
		operator char* () const 
		{
			if (ptr)
				return ptr->data();
			return nullptr; 
		}
		operator void* () const 
		{ 
			if (ptr)
				return reinterpret_cast<void*>(ptr->data());
			return nullptr; 
		}
		operator uint8_t*() const {return reinterpret_cast<uint8_t*>(ptr->data()); }
		operator bool() const { return static_cast<bool>(ptr); }
	};
}