#pragma once
#include <iostream>
#include "form_define.h"
#include "../../../gui/dx11/dx11_frame.h"
#include "../../../tool/mail.h"
#include "../../../gui/dx/movement.h"
#include "../../../gui/dx11/dx11_form.h"
#include "DirectXTex.h"
#include "../../po/gui/dx11/simple_renderer.h"
using namespace PO::Dx;
using namespace PO::Dx11;
using namespace PO;

struct new_creator
{
	raw_scene rs;

	input_assember_stage ias;
	pixel_stage ps;
	vertex_stage vs;
	depth_stencil_state dss;
	output_merge_stage oms;

	float4 filter = float4{ 1.0, 1.0, 1.0, 1.0 };

	new_creator(construction<simple_renderer> p);
	void init(simple_renderer& s);
	void tick(simple_renderer& s);
	Respond respond(event& e);
};