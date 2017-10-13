#include <map>
#include "../../../include/po/implement/extension.h"
#include "../../../include/po/implement/ecs_framework.h"
#include <iostream>

struct A {};

struct extension_test
{
	int a = 1;
	int b = 2;
	int c = 3;
	extension_test() {
		std::cout << "c" << std::endl;
	}
	~extension_test() { 
		std::cout << "~" << std::endl; 
	}
};

struct alignas(16) Da
{
	float data;
};


int main()
{
	/*
#ifdef DEBUG
	PO::Dx11::add_shader_path<PO::Dx::shader_binary>(u"..\\..\\..\\..\\project\\vs2017\\po_dx11\\lib\\shader\\Debug");
	PO::Dx11::add_shader_path<PO::Dx::shader_binary>(u"..\\..\\..\\..\\..\\project\\vs2017\\po_dx11\\lib\\shader\\Debug");
	PO::Dx11::add_shader_path<PO::Dx::shader_binary>(u"..\\..\\..\\project\\vs2017\\po_dx11\\lib\\shader\\Debug");
#else
	PO::Dx11::add_shader_path<PO::Dx::shader_binary>(u"..\\..\\..\\..\\project\\vs2017\\po_dx11\\lib\\shader\\Release");
	PO::Dx11::add_shader_path<PO::Dx::shader_binary>(u"..\\..\\..\\..\\..\\project\\vs2017\\po_dx11\\lib\\shader\\Release");
	PO::Dx11::add_shader_path<PO::Dx::shader_binary>(u"..\\..\\..\\project\\vs2017\\po_dx11\\lib\\shader\\Release");
#endif // DEBUG
*/

	{
		PO::Implement::extension_packet out_packet;
		{
			PO::Implement::extension_packet packet;
			packet.create(PO::extension<extension_test>{});
			packet.shader_extension(out_packet, typeid(extension_test));
			packet.find([](extension_test& et) {
				//__debugbreak();
			});
		}
		out_packet.find([](extension_test& et) {
			//__debugbreak();
		});
	}

	using type = PO::Implement::ecs_memory_page;

	std::cout << alignof(type) << sizeof(type) << std::endl;
	
	//PO::context con;
	//con.wait_all_form_close();
	system("pause");
	return 0;
}