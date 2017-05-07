#pragma once
#include <d3d11.h>
#include "../win32/win32_define.h"
namespace PO
{
	namespace Dx11
	{

		struct UINT2 { UINT x, y; };

		struct vertex
		{
			Win32::com_ptr<ID3D11Buffer> ptr;
			UINT offset;
			UINT element_size;
			size_t num;
			std::vector<D3D11_INPUT_ELEMENT_DESC> layout;
		};

		struct index
		{
			Win32::com_ptr<ID3D11Buffer> ptr;
			UINT offset;
			DXGI_FORMAT format;
			size_t num;
		};

		struct index_vertex
		{
			Win32::com_ptr<ID3D11Buffer> ptr;
			UINT v_offset;
			UINT v_element_size;
			size_t v_num;
			std::vector<D3D11_INPUT_ELEMENT_DESC> v_layout;
			UINT i_offset;
			DXGI_FORMAT i_format;
			size_t i_num;
		};

		struct tex1 { Win32::com_ptr<ID3D11Texture1D> ptr; };
		struct tex2 { Win32::com_ptr<ID3D11Texture2D> ptr; };
		struct tex3 { Win32::com_ptr<ID3D11Texture3D> ptr; };

		struct constant_buffer { Win32::com_ptr<ID3D11Buffer> ptr; };
		struct structed_buffer { Win32::com_ptr<ID3D11Buffer> ptr; };
		struct readable_buffer { Win32::com_ptr<ID3D11Buffer> ptr; };

		struct shader_resource_view { Win32::com_ptr<ID3D11ShaderResourceView> ptr; };
		struct unordered_access_view { Win32::com_ptr<ID3D11UnorderedAccessView> ptr; UINT offset; };
		struct render_target_view { Win32::com_ptr<ID3D11RenderTargetView> ptr; };
		struct depth_stencil_view { Win32::com_ptr<ID3D11DepthStencilView> ptr; };

		struct sample_state { 
			using scription = D3D11_SAMPLER_DESC;
			static scription default_scription;
			Win32::com_ptr<ID3D11SamplerState> ptr;
		};

		struct raterizer_state {
			using scription = D3D11_RASTERIZER_DESC;
			static scription default_scription;

			Win32::com_ptr<ID3D11RasterizerState> ptr;
			std::vector<D3D11_VIEWPORT> viewports;
			std::vector<D3D11_RECT> scissor;
		};

		struct blend_state {
			using scription = D3D11_BLEND_DESC;
			static scription default_scription;

			Win32::com_ptr<ID3D11BlendState> ptr;
			std::array<float, 4> bind_factor = {1.0f, 1.0f, 1.0f, 1.0f};
			UINT sample_mask = 0xffffffff;
		};

		struct depth_stencil_state {
			using scription = D3D11_DEPTH_STENCIL_DESC;
			static scription default_scription;

			Win32::com_ptr<ID3D11DepthStencilState> ptr;
			UINT stencil_ref = 0;
		};

		struct shader_stage
		{
			Win32::com_vector<ID3D11Buffer> cbuffer_array;
			Win32::com_vector<ID3D11ShaderResourceView> shader_resource_view_array;
			Win32::com_vector<ID3D11SamplerState> sample_array;
			void set_constant_buffer(const constant_buffer& cb, size_t solt);
			void set_shader_resource_view(const shader_resource_view& ptr, size_t solt);
			void set_sample_state(const sample_state& sd, size_t solt);
		};

		struct input_assember_stage
		{
			Win32::com_vector<ID3D11Buffer> vertex_array;
			std::vector<UINT> offset_array;
			std::vector<UINT> element_array;
			std::vector<D3D11_INPUT_ELEMENT_DESC> input_element;
			Win32::com_ptr<ID3D11InputLayout> layout;
			D3D11_PRIMITIVE_TOPOLOGY primitive = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

			Win32::com_ptr<ID3D11Buffer> index_ptr;
			UINT offset;
			DXGI_FORMAT format;

			void set_vertex(const vertex& v, size_t solt);
			void set_index(const index& bp);
			void set_index_vertex(const index_vertex& iv, size_t solt);
		};

		struct vertex_shader
		{
			binary code;
			Win32::com_ptr<ID3D11VertexShader> ptr;
		};

		struct vertex_stage : shader_stage, vertex_shader
		{
		};

		struct pixel_shader
		{
			Win32::com_ptr<ID3D11PixelShader> ptr;
		};

		struct pixel_stage : shader_stage, pixel_shader
		{

		};

		struct output_merge_stage : shader_stage
		{
			Win32::com_vector<ID3D11RenderTargetView> render_array;
			depth_stencil_view depth;
			blend_state blend;
			depth_stencil_state depth_stencil;
			void set_render_target_view(render_target_view& rtv, size_t o);
			void set_DSV(depth_stencil_view dsv) { depth = std::move(dsv); }
			void set_state(blend_state bs) { blend = std::move(bs); }
			void set_state(depth_stencil_state dss) { depth_stencil = std::move(dss); }
		};

		struct compute_shader
		{
			Win32::com_ptr<ID3D11ComputeShader> ptr;
		};

		struct compute_stage : shader_stage , compute_shader
		{
			Win32::com_vector<ID3D11UnorderedAccessView> UAV_array;
			std::vector<UINT> offset;
			
			void set_unordered_access_view(const unordered_access_view& uav, size_t solt);
			using compute_shader::operator=;
		};

		enum class DST_format
		{
			D16,
			D24_UI8,
			F32,
			F32_UI8,
			UNKNOW
		};

		struct creator
		{
			Win32::com_ptr<ID3D11Device> dev;
			creator(Win32::com_ptr<ID3D11Device> d) : dev(std::move(d)) {}

			static DXGI_FORMAT translate_depth_stencil_format_to_dxgi_format(DST_format dsf);
			static UINT creator::translate_usage_to_cpu_flag(D3D11_USAGE DU);

			sample_state create_sample_state(const sample_state::scription& scri = sample_state::default_scription);
			raterizer_state create_raterizer_state(const raterizer_state::scription& scri = raterizer_state::default_scription);
			blend_state create_blend_state(const blend_state::scription& scri = blend_state::default_scription, std::array<float, 4> bind_factor = { 1.0f, 1.0f, 1.0f, 1.0f }, UINT sample_mask = 0xffffffff);
			depth_stencil_state create_depth_stencil_state(const depth_stencil_state::scription& scri = depth_stencil_state::default_scription, UINT stencil_ref = 0);

			void update_layout(input_assember_stage& ia, const vertex_shader& vd);

			Win32::com_ptr<ID3D11Buffer> create_buffer_implement(UINT width, D3D11_USAGE DU, UINT BIND, UINT misc_flag, UINT struct_byte,  const void* data);

			constant_buffer create_constant_buffer(UINT width, const void* data = nullptr, bool write_enable = true);
			structed_buffer create_struct_buffer(UINT element_size, UINT element_num, const void* data = nullptr, bool write_enable = true) {
				structed_buffer sb;
				sb.ptr = create_buffer_implement(element_size * element_num, (write_enable ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_IMMUTABLE), D3D11_BIND_SHADER_RESOURCE, D3D11_RESOURCE_MISC_BUFFER_STRUCTURED, element_size, data);
				return sb;
			}
			template<typename T, typename K> structed_buffer create_struct_buffer(const std::vector<T, K>& v, bool write_enable = true) {
				return create_struct_buffer(static_cast<UINT>(sizeof(T)), static_cast<UINT>(v.size()), v.data(), write_enable);
			}
			structed_buffer create_struct_buffer_unorder_access(UINT element_size, UINT element_num, const void* data = nullptr) {
				structed_buffer sb;
				sb.ptr = create_buffer_implement(element_size * element_num, D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS, D3D11_RESOURCE_MISC_BUFFER_STRUCTURED, element_size, data);
				return sb;
			}

			vertex_shader create_vertex_shader(binary b);
			pixel_shader create_pixel_shader(const binary& b);
			compute_shader create_compute_shader(const binary& b);

			tex1 create_tex1_implement(DXGI_FORMAT DF, UINT length, UINT miplevel, UINT count, D3D11_USAGE DU, UINT BIND, UINT misc, void** data);
			tex2 create_tex2_implement(DXGI_FORMAT DF, UINT width, UINT height, UINT miplevel, UINT count, UINT sample_num, UINT sample_quality, D3D11_USAGE usage, UINT bind, UINT mis, void** data, UINT* line);
			tex3 create_tex3_implement(DXGI_FORMAT DF, UINT width, UINT height, UINT depth, UINT miplevel, D3D11_USAGE usage, UINT bind, UINT mis, void* data, UINT line, UINT slice);

			tex1 create_tex1(DXGI_FORMAT DF, UINT length, Tool::optional<UINT> miplevel = {}, Tool::optional<UINT> count = {}, D3D11_USAGE DU = D3D11_USAGE_DYNAMIC, void** data = nullptr) {
				return create_tex1_implement(DF, length, (miplevel ? *miplevel : 1), (count ? *count : 1), DU, D3D11_BIND_SHADER_RESOURCE, 0, data);
			}
			tex1 create_tex1_unordered_access(DXGI_FORMAT DF, UINT length, Tool::optional<UINT> miplevel = {}, Tool::optional<UINT> count = {}, void** data = nullptr) {
				return create_tex1_implement(DF, length, (miplevel ? *miplevel : 1), (count ? *count : 1), D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS, 0, data);
			}
			tex1 create_tex1_render_target(DXGI_FORMAT DF, UINT length, Tool::optional<UINT> miplevel = {}, Tool::optional<UINT> count = {}, void** data = nullptr) {
				return create_tex1_implement(DF, length, (miplevel ? *miplevel : 1), (count ? *count : 1), D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET, 0, data);
			}
			tex1 create_tex1_depth_stencil(DST_format DF, UINT length, Tool::optional<UINT> miplevel = {}, Tool::optional<UINT> count = {}, void** data = nullptr) {
				return create_tex1_implement(translate_depth_stencil_format_to_dxgi_format(DF), length, (miplevel ? *miplevel : 1), (count ? *count : 1), D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET, 0, data);
			}

			tex2 create_tex2(DXGI_FORMAT DF, UINT width, UINT height, Tool::variant<UINT, UINT2> miplevel = {}, Tool::optional<UINT> count = {}, D3D11_USAGE usage = D3D11_USAGE_DYNAMIC, void** data = nullptr, UINT* line = nullptr) {
				UINT2 sample = miplevel.able_cast<UINT2>() ? miplevel.cast<UINT2>() : UINT2{ 1, 0 };
				return create_tex2_implement(DF, width, height, (miplevel.able_cast<UINT>() ? miplevel.cast<UINT>() : 1), (count ? *count : 1), sample.x, sample.y, usage, D3D11_BIND_SHADER_RESOURCE, 0, data, line);
			}
			tex2 create_tex2_unordered_access(DXGI_FORMAT DF, UINT width, UINT height, Tool::variant<UINT, UINT2> miplevel = {}, Tool::optional<UINT> count = {}, void** data = nullptr, UINT* line = nullptr) {
				UINT2 sample = miplevel.able_cast<UINT2>() ? miplevel.cast<UINT2>() : UINT2{ 1, 0 };
				return create_tex2_implement(DF, width, height, (miplevel.able_cast<UINT>() ? miplevel.cast<UINT>() : 1), (count ? *count : 1), sample.x, sample.y, D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS, 0, data, line);
			}
			tex2 create_tex2_render_target(DXGI_FORMAT DF, UINT width, UINT height, Tool::variant<UINT, UINT2> miplevel = {}, Tool::optional<UINT> count = {}, void** data = nullptr, UINT* line = nullptr) {
				UINT2 sample = miplevel.able_cast<UINT2>() ? miplevel.cast<UINT2>() : UINT2{ 1, 0 };
				return create_tex2_implement(DF, width, height, (miplevel.able_cast<UINT>() ? miplevel.cast<UINT>() : 1), (count ? *count : 1), sample.x, sample.y, D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET, 0, data, line);
			}
			tex2 create_tex2_depth_stencil(DST_format DF, UINT width, UINT height, Tool::variant<UINT, UINT2> miplevel = {}, Tool::optional<UINT> count = {}, void** data = nullptr, UINT* line = nullptr) {
				UINT2 sample = miplevel.able_cast<UINT2>() ? miplevel.cast<UINT2>() : UINT2{ 1, 0 };
				return create_tex2_implement(translate_depth_stencil_format_to_dxgi_format(DF), width, height, (miplevel.able_cast<UINT>() ? miplevel.cast<UINT>() : 1), (count ? *count : 1), sample.x, sample.y, D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET, 0, data, line);
			}
			tex2 create_tex2_depth_stencil(DST_format DF, const tex2& t, void** data = nullptr, UINT* line = nullptr);

			tex2 create_tex_cube(DXGI_FORMAT DF, UINT width, UINT height, Tool::optional<UINT> miplevel = {}, Tool::optional<UINT> count = {}, void** data = nullptr, UINT* line = nullptr) {
				return create_tex2_implement(DF, width, height, (miplevel ? *miplevel : 1), (count ? *count * 6 : 6), 1, 0, D3D11_USAGE_DYNAMIC, D3D11_BIND_SHADER_RESOURCE, D3D11_RESOURCE_MISC_TEXTURECUBE, data, line);
			}
			tex2 create_tex_cube_unorder_access(DXGI_FORMAT DF, UINT width, UINT height, Tool::optional<UINT> miplevel = {}, Tool::optional<UINT> count = {}, void** data = nullptr, UINT* line = nullptr) {
				return create_tex2_implement(DF, width, height, (miplevel ? *miplevel : 1), (count ? *count * 6 : 6), 1, 0, D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS, D3D11_RESOURCE_MISC_TEXTURECUBE, data, line);
			}

			tex3 create_tex3(DXGI_FORMAT DF, UINT width, UINT height, UINT depth, Tool::optional<UINT> miplevel = {}, D3D11_USAGE usage = D3D11_USAGE_DYNAMIC, void* data = nullptr, UINT line = 0, UINT slice = 0){
				return create_tex3_implement(DF, width, height, depth, (miplevel ? *miplevel : 1), usage, D3D11_BIND_SHADER_RESOURCE, 0, data, line, slice);
			}
			tex3 create_tex3_unordered_access(DXGI_FORMAT DF, UINT width, UINT height, UINT depth, Tool::optional<UINT> miplevel = {}, void* data = nullptr, UINT line = 0, UINT slice = 0) {
				return create_tex3_implement(DF, width, height, depth, (miplevel ? *miplevel : 1), D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS, 0, data, line, slice);
			}

			shader_resource_view cast_shader_resource_view(const structed_buffer& t, Tool::optional<UINT2> range = {});

			shader_resource_view cast_shader_resource_view(const tex1& t, Tool::optional<UINT2> mip_range = {});
			shader_resource_view cast_shader_resource_view(const tex2& t, Tool::optional<UINT2> mip_range = {});

			shader_resource_view cast_shader_resource_view_array(const tex1& t, Tool::optional<UINT2> mip_range = {}, Tool::optional<UINT2> array = {});
			shader_resource_view cast_shader_resource_view_array(const tex2& t, Tool::optional<UINT2> mip_range = {}, Tool::optional<UINT2> array = {});

			shader_resource_view cast_shader_resource_view_ms(const tex2& t);
			shader_resource_view cast_shader_resource_view_ms_array(const tex2& t, Tool::optional<UINT2> array = {});

			shader_resource_view cast_shader_resource_view_cube(const tex2& t, Tool::optional<UINT2> mip_range = {});
			shader_resource_view cast_shader_resource_view_cube_array(const tex2& t, Tool::optional<UINT2> mip_range = {}, Tool::optional<UINT2> array = {});

			shader_resource_view cast_shader_resource_view(const tex3& t, Tool::optional<UINT2> mip_range = {});

			render_target_view cast_render_target_view(const tex1& t, UINT miplevel = 0);
			render_target_view cast_render_target_view(const tex2& t, UINT miplevel = 0);
			render_target_view cast_render_target_view(const tex3& t, UINT miplevel = 0, Tool::optional<UINT2> z_range = {});

			render_target_view cast_render_target_view_array(const tex1& t, UINT miplevel = 0, Tool::optional<UINT2> array_range = {});
			render_target_view cast_render_target_view_array(const tex2& t, UINT miplevel = 0, Tool::optional<UINT2> array_range = {});

			render_target_view cast_render_target_view_ms(const tex2& t);
			render_target_view cast_render_target_view_ms_array(const tex2& t, Tool::optional<UINT2> array_range = {});

			depth_stencil_view cast_depth_setncil_view(const tex1& t, UINT miplevel = 0, Tool::optional<bool> depth_read_only = {});
			depth_stencil_view cast_depth_setncil_view(const tex2& t, UINT miplevel = 0, Tool::optional<bool> depth_read_only = {});
			depth_stencil_view cast_depth_setncil_view_array(const tex1& t, UINT miplevel = 0, Tool::optional<UINT2> array_range = {}, Tool::optional<bool> depth_read_only = {});
			depth_stencil_view cast_depth_setncil_view_array(const tex2& t, UINT miplevel = 0, Tool::optional<UINT2> array_range = {}, Tool::optional<bool> depth_read_only = {});
			depth_stencil_view cast_depth_setncil_view_ms(const tex2& t, Tool::optional<bool> depth_read_only = {});
			depth_stencil_view cast_depth_setncil_view_ms_array(const tex2& t, Tool::optional<UINT2> array_range = {}, Tool::optional<bool> depth_read_only = {});

			unordered_access_view cast_unordered_access_view(const structed_buffer& tp);
			unordered_access_view cast_unordered_access_view(const tex1& tp, UINT mipslice = 0);
			unordered_access_view cast_unordered_access_view_array(const tex1& tp, UINT mipslice = 0, Tool::optional<UINT2> array = {});
			unordered_access_view cast_unordered_access_view(const tex2& tp, UINT mipslice = 0);
			unordered_access_view cast_unordered_access_view_array(const tex2& tp, UINT mipslice = 0, Tool::optional<UINT2> array = {});
			unordered_access_view cast_unordered_access_view(const tex3& tp, UINT mipslice = 0, Tool::optional<UINT2> z_range = {});
		};

		namespace Implement
		{

			struct input_assember_context_t
			{
				size_t max_buffer_solt = 0;
				void bind(Win32::com_ptr<ID3D11DeviceContext>& cp, const input_assember_stage& id);
				void unbind(Win32::com_ptr<ID3D11DeviceContext>& cp);
			};

			struct vertex_shader_context_t
			{
				size_t max_cbuffer = 0;
				void bind(Win32::com_ptr<ID3D11DeviceContext>& cp, const vertex_stage&);
				void unbind(Win32::com_ptr<ID3D11DeviceContext>& cp);
			};

			struct raterizer_context_t
			{
				size_t max_view = 0;
				void bind(Win32::com_ptr<ID3D11DeviceContext>& cp, const raterizer_state& rs);
				void unbind(Win32::com_ptr<ID3D11DeviceContext>& cp);
			};

			struct pixel_shader_context_t
			{
				size_t max_cbuffer = 0;
				void bind(Win32::com_ptr<ID3D11DeviceContext>& cp, const pixel_stage&);
				void unbind(Win32::com_ptr<ID3D11DeviceContext>& cp);
			};

			struct output_merge_context_t
			{
				void clear_render_target(Win32::com_ptr<ID3D11DeviceContext>& cp, output_merge_stage& omd, size_t solt, const std::array<float, 4>& color);
				void clear_render_target(Win32::com_ptr<ID3D11DeviceContext>& cp, output_merge_stage& omd, const std::array<float, 4>& color);
				void clear_depth(Win32::com_ptr<ID3D11DeviceContext>& cp, output_merge_stage& omd, float depth);
				void clear_stencil(Win32::com_ptr<ID3D11DeviceContext>& cp, output_merge_stage& omd, uint8_t ref);
				void clear_depth_stencil(Win32::com_ptr<ID3D11DeviceContext>& cp, output_merge_stage& omd, float depth, uint8_t ref);
				void bind(Win32::com_ptr<ID3D11DeviceContext>& cp, const output_merge_stage&);
				void unbind(Win32::com_ptr<ID3D11DeviceContext>& cp);
			};

			struct compute_shader_context_t
			{
				size_t max_cbuffer = 0;
				void bind(Win32::com_ptr<ID3D11DeviceContext>& cp, const compute_stage& cd);
				void unbind(Win32::com_ptr<ID3D11DeviceContext>& cp);
			};
		}

		struct pipe_line
		{
			Win32::com_ptr<ID3D11DeviceContext> ptr;
			Implement::input_assember_context_t IA;
			Implement::vertex_shader_context_t VS;
			Implement::raterizer_context_t RA;
			Implement::pixel_shader_context_t PS;
			Implement::output_merge_context_t OM;

			Implement::compute_shader_context_t CS;

			pipe_line(Win32::com_ptr<ID3D11DeviceContext> cp) :ptr(std::move(cp)) {}

			enum DrawMode
			{
				PIPELINE,
				COMPLUTE,
				NONE
			};

			DrawMode last_mode = DrawMode::NONE;

			void dispatch(UINT x, UINT y, UINT z);

			void draw_vertex(UINT count, UINT start);
			void draw_index(UINT index_count, UINT index_start, UINT vertex_count);
			void draw_vertex_instance(UINT vertex_pre_instance, UINT instance_count, UINT vertex_start, UINT instance_start);
			void draw_index_instance(UINT index_pre_instance, UINT index_count, UINT index_start, UINT vertex_start, UINT instance_start);

			void unbind();

			void bind(const input_assember_stage& d) { IA.bind(ptr, d); }
			void bind(const vertex_stage& d) { VS.bind(ptr, d); }
			void bind(const pixel_stage& d) { PS.bind(ptr, d); }
			void bind(const output_merge_stage& d) { OM.bind(ptr, d); }
			void bind(const raterizer_state& rs) { RA.bind(ptr, rs); }
			void bind(const compute_stage& cd) { CS.bind(ptr, cd); }

			void clear_render_target(output_merge_stage& omd, size_t solt, const std::array<float, 4>& color) { OM.clear_render_target(ptr, omd, solt, color); }
			void clear_render_target(output_merge_stage& omd, const std::array<float, 4>& color) { OM.clear_render_target(ptr, omd, color); }
			void clear_depth(output_merge_stage& omd, float depth) { OM.clear_depth(ptr, omd, depth); }
			void clear_stencil(output_merge_stage& omd, uint8_t ref) { OM.clear_stencil(ptr, omd, ref); }
			void clear_depth_stencil(output_merge_stage& omd, float depth, uint8_t ref) { OM.clear_depth_stencil(ptr, omd, depth, ref); }

			template<typename T> bool write_constant_buffer(constant_buffer& b, T&& t)
			{
				if (b.ptr == nullptr) return false;
				D3D11_MAPPED_SUBRESOURCE DMS;
				if (SUCCEEDED(ptr->Map(b.ptr, 0, D3D11_MAP_WRITE_DISCARD, 0, &DMS)))
				{
					Tool::at_scope_exit ate([&, this]() { ptr->Unmap(b.ptr, 0); });
					return t(DMS.pData, DMS.RowPitch, DMS.DepthPitch), true;
				}
				return false;
			}

			template<typename T> bool write_constant_buffer(shader_stage& b, size_t o, T&& t)
			{
				if (b.cbuffer_array.size() <= o) return false;
				cbuffer ptr;
				ptr.ptr = b.cbuffer_array[o];
				return write_cbuffer(ptr, t);
			}
		};
	}
}