#pragma once
#include "po_dx11\dx11_renderer.h"
#include "po_dx\controller.h"
#include "po\plugin.h"
using namespace PO;
using namespace PO::Dx11;

struct new_plugin
{
	int swith_state = 0;
	tex2 worley;
	tex2 perlin_out;
	element compute;
	element output_volume_cube;
	element back_ground;
	element perlin_element;
	//defer_element viewer;
	transfer3D ts1;
	transfer3D ts2;
	showcase s;
	float layer = 0.5;
	float scale = 1.0;
	float max_denstiy;
	adapter_map mapping(self& sel);
	void init(defer_renderer_default& dr);
	void tick(defer_renderer_default& dr, duration da);
	Respond respond(event& e);
};