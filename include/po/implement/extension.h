#pragma once
#include <typeindex>
#include <functional>
#include "..\tool\thread_tool.h"
namespace PO
{

	template<typename extension_t> class extension {
		using type = std::decay_t<extension_t>;
	public:
		void operator()(extension_t&) {}
	};

	namespace Implement
	{
		template<typename extension_t> struct extension_implement;

		class extension_interface
		{
			std::type_index complete_info;
			std::atomic_uint reference;
		public:
			const std::type_index& id() const { return complete_info; }
			extension_interface(const std::type_index& id);
			void add_reference() { ++reference; }
			void del_reference() { if ((--reference) == 0) release(); }
			virtual ~extension_interface();
			virtual void release() = 0;

			template<typename true_type_t> bool able_cast() const { return id() == typeid(true_type_t); }
			template<typename true_type_t> true_type_t& cast() { return static_cast<true_type_t&>(static_cast<extension_implement<true_type_t>&>(*this)); }
			template<typename true_type_t> const true_type_t& cast() const { return static_cast<const true_type_t&>(static_cast<const extension_implement<true_type_t>&>(*this)); }
		};

		template<typename extension_t> struct extension_allocator;

		template<typename extension_t>
		struct alignas(alignof(extension_t) > 4 ? alignof(extension_t) : 0)  extension_implement : extension_t, extension_interface
		{
			static extension_allocator<extension_t> allocator;
			template<typename ...AT> extension_implement(AT&& ... at) : extension_t{ std::forward<AT>(at)... }, extension_interface(typeid(extension_t)) {}
			virtual void release() { allocator.deallocate(this); }
			template<typename ...AT>
			static extension_implement* allocate(AT&& ...at) { return allocator.allocate(std::forward<AT>(at)...); }
		};

		template<typename extension_t> 
		struct extension_allocator
		{
			template<typename ...AT>
			extension_implement<extension_t>* allocate(AT&& ...at) { return  new extension_implement<extension_t>{ std::forward<AT>(at)... }; }
			void deallocate(extension_implement<extension_t>* ei) { delete ei; }
			friend class extension_packet;
		};

		template<typename extension_t> extension_allocator<extension_t> extension_implement<extension_t>::allocator;

		class extension_ptr
		{
			extension_interface* ptr;
		public:
			extension_ptr() : ptr(nullptr) {}
			extension_ptr(extension_interface* ei);
			extension_ptr(const extension_ptr& ep);
			extension_ptr(extension_ptr&&);
			extension_ptr& operator= (extension_ptr);
			operator bool() const { return ptr != nullptr; }
			extension_interface* operator->() { return ptr; }
			const extension_interface* operator->() const { return ptr; }
			~extension_ptr();
		};

		//todo need a memorary pool
		class extension_packet
		{
			using map_type = std::unordered_map<std::type_index, extension_ptr>;
			Tool::scope_lock<map_type> extension_map;
			static void remove(map_type& , const std::type_index& ti);
			static void insert(map_type& m, const std::type_index& ti, extension_ptr ep);
			static extension_ptr find_ptr(map_type& m, const std::type_index& ti);
		public:

			template<typename init_function, typename ...AT> void create(init_function&& ifunction, AT&& ...at)
			{
				using funtype = Tmp::pick_func<typename Tmp::degenerate_func<Tmp::extract_func_t<init_function>>::type>;
				static_assert(funtype::size == 1, "only receive one parameter");
				using true_type = std::decay_t<typename funtype::template out<Tmp::itself>::type>;
				extension_map.lock([&](decltype(extension_map)::type& t) {
					remove(t, typeid(true_type));
					extension_implement<true_type>* ptr = extension_implement<true_type>::allocate(std::forward<AT>(at)...);
					extension_ptr inter_ptr{ ptr };
					std::forward<init_function>(ifunction)(static_cast<true_type&>(*ptr));
					insert(t, typeid(true_type), std::move(inter_ptr));
				});
			}

			bool shader_extension(extension_packet& ep, const std::type_index& ti);

			template<typename function> bool find(function&& func)
			{
				using funtype = Tmp::pick_func<typename Tmp::degenerate_func<Tmp::extract_func_t<function>>::type>;
				static_assert(funtype::size == 1, "only receive one parameter");
				using true_type = std::decay_t<typename funtype::template out<Tmp::itself>::type>;
				extension_ptr ptr = extension_map.lock([&](decltype(extension_map)::type& m) {
					return find_ptr(m, typeid(true_type));
				});
				if (ptr->able_cast<true_type>())
					return func(ptr->cast<true_type>()), true;
				return false;
			}
		}; 

	}

}