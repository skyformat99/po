#include "ecs_framework.h"
namespace PO
{





	/*
	namespace Implement
	{

		component_interface::~component_interface() {}
		component_interface::component_interface(const std::type_index& id) : complete_info(id), reference(0) {}

		extension_ptr::extension_ptr(const extension_ptr& ep) : ptr(ep.ptr)
		{
			if (ptr != nullptr)
				ptr->add_reference();
		}

		extension_ptr::extension_ptr(extension_ptr&& ep) : ptr(ep.ptr)
		{
			ep.ptr = nullptr;
		}

		extension_ptr& extension_ptr::operator= (extension_ptr ep)
		{
			if (ptr != nullptr) ptr->del_reference();
			ptr = ep.ptr;
			ep.ptr = nullptr;
			return *this;
		}

		extension_ptr::~extension_ptr()
		{
			if (ptr != nullptr)
			{
				ptr->del_reference();
			}
		}

		extension_ptr::extension_ptr(extension_interface* ei) : ptr(ei)
		{
			if (ptr != nullptr)
				ptr->add_reference();
		}

		void extension_packet::remove(map_type& m, const std::type_index& ti) {
			auto ite = m.find(typeid(ti));
			if (ite != m.end())
				m.erase(ite);
		}

		void extension_packet::insert(map_type& m, const std::type_index& ti, extension_ptr p)
		{
			m.insert({ ti, std::move(p) });
		}

		extension_ptr extension_packet::find_ptr(map_type& m, const std::type_index& ti)
		{
			auto ite = m.find(ti);
			if (ite != m.end())
				return ite->second;
			return extension_ptr{};
		}

		bool extension_packet::shader_extension(extension_packet& ep, const std::type_index& ti)
		{
			extension_ptr ptr = extension_map.lock([&](decltype(extension_map)::type& t) {
				return find_ptr(t, ti);
			});
			if (ptr)
				return ep.extension_map.lock([&](decltype(ep.extension_map)::type& t) {
				remove(t, ti);
				insert(t, ti, std::move(ptr));
			}), true;
			return false;
		}
	}
	*/
}