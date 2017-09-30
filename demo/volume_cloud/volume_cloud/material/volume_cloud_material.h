#pragma once
#include "po_dx11\dx11_buildin_element.h"
#include "po_dx11\dx11_renderer.h"
using namespace PO::Dx;
using namespace PO::Dx11;


class property_volume_cloud_tex : public property_resource
{
	shader_resource_view<tex2> BaseShapeTex;
	sample_state BaseShapeSampler;

	shader_resource_view<tex2> MoveMaskTex;
	sample_state MoveMaskSampler;

	shader_resource_view<tex2> MaskTex;
	sample_state MaskSampler;

public:

	struct renderer_data
	{
		shader_resource_view<tex2> BaseShapeTex;
		sample_state BaseShapeSampler;

		shader_resource_view<tex2> MoveMaskTex;
		sample_state MoveMaskSampler;

		shader_resource_view<tex2> MaskTex;
		sample_state MaskSampler;
	};

	void set_base_shape(shader_resource_view<tex2> tex, sample_state sampler)
	{
		BaseShapeTex = std::move(tex);
		BaseShapeSampler = std::move(sampler);
		need_update();
	}

	void set_move_mask(shader_resource_view<tex2> tex, sample_state sampler)
	{
		MoveMaskTex = std::move(tex);
		MoveMaskSampler = std::move(sampler);
		need_update();
	}

	void set_mask(shader_resource_view<tex2> tex, sample_state sampler)
	{
		MaskTex = std::move(tex);
		MaskSampler = std::move(sampler);
		need_update();
	}

	void update(creator& c, renderer_data& rd)
	{
		rd.BaseShapeSampler = BaseShapeSampler;
		rd.BaseShapeTex = BaseShapeTex;
		rd.MaskSampler = MaskSampler;
		rd.MaskTex = MaskTex;
		rd.MoveMaskSampler = MoveMaskSampler;
		rd.MoveMaskTex = MoveMaskTex;
	}

};



class property_render_2d_for_3d : public property_resource
{
	float3 min_width, max_width, light;
	float density;
	shader_resource_view<tex2> m_srv;
	sample_state m_ss;

public:
	
	struct renderer_data
	{
		shader_resource_view<tex2> m_srv;
		sample_state m_ss;
		buffer_constant m_cb;
	};
	void set_option(float3 min_width, float3 max_width, float3 light, float density) 
	{
		this->min_width = min_width;
		this->max_width = max_width;
		this->light = light;
		this->density = density;
		need_update();
	}
	void set_texture(shader_resource_view<tex2> srv,  sample_state ss) 
	{ 
		m_srv = std::move(srv); m_ss = std::move(ss);
		need_update();
	}
	void update(creator& c, renderer_data& rd);
};

class material_transparent_2d_for_3d_64_without_perlin :public material_resource
{
	depth_stencil_state dss;
public:
	material_transparent_2d_for_3d_64_without_perlin(creator& c);
	const element_requirement& requirement() const;
	const depth_stencil_state& replace_depth_stencil_state(const depth_stencil_state&) { 
		return dss; 
	}
};