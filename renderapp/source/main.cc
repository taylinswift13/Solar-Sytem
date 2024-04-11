// main.cc

#include "main.hpp"

namespace avocado {
	// note: application create implementation
	application* application::create(settings& settings)
	{
		settings.title_ = "renderapp";
		settings.width_ = 1280;
		settings.height_ = 720;
		settings.center_ = true;

		return new renderapp;
	}

	// note: renderapp class
	renderapp::renderapp()
	{
	}

	bool renderapp::on_init()
	{
		if (!renderer_.initialize()) {
			return false;
		}
		// note: load shader source from disk
		{
			string vertex_source;
			if (!file_system::read_file_content("assets/triangle.vs.txt", vertex_source)) {
				return on_error("Could not load vertex source");
			}

			string fragment_source;
			if (!file_system::read_file_content("assets/triangle.fs.txt", fragment_source)) {
				return on_error("Could not load fragment source");
			}
			if (!shader_.create(vertex_source.c_str(),
				fragment_source.c_str()))
			{
				return on_error("Could not create shader program!");
			}
		}

		// note: create cube
		{
			v = 1.0f;
			const glm::vec3 p[] =
			{
			   { -v, +v, +v },
			   { -v, -v, +v },
			   { +v, -v, +v },
			   { +v, +v, +v },

			   { -v, +v, -v },
			   { -v, -v, -v },
			   { +v, -v, -v },
			   { +v, +v, -v },
			};

			const vertex vertices[] =
			{
				// front
				{ p[0], glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), },
				{ p[1], glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), },
				{ p[2], glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), },
				{ p[2], glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), },
				{ p[3], glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), },
				{ p[0], glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), },
				// right                                  
				{ p[3], glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), },
				{ p[2], glm::vec2(0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), },
				{ p[6], glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), },
				{ p[6], glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), },
				{ p[7], glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), },
				{ p[3], glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), },
				// back                                   
				{ p[7], glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f,-1.0f), },
				{ p[6], glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f,-1.0f), },
				{ p[5], glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 0.0f,-1.0f), },
				{ p[5], glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 0.0f,-1.0f), },
				{ p[4], glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f,-1.0f), },
				{ p[7], glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f,-1.0f), },
				// left
				{ p[4], glm::vec2(0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), },
				{ p[5], glm::vec2(0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), },
				{ p[1], glm::vec2(1.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), },
				{ p[1], glm::vec2(1.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), },
				{ p[0], glm::vec2(1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), },
				{ p[4], glm::vec2(0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), },
				// top
				{ p[4], glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), },
				{ p[0], glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), },
				{ p[3], glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), },
				{ p[3], glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), },
				{ p[7], glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), },
				{ p[4], glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), },
				// bottom                                 
				{ p[1], glm::vec2(0.0f, 0.0f), glm::vec3(0.0f,-1.0f, 0.0f), },
				{ p[5], glm::vec2(0.0f, 1.0f), glm::vec3(0.0f,-1.0f, 0.0f), },
				{ p[6], glm::vec2(1.0f, 1.0f), glm::vec3(0.0f,-1.0f, 0.0f), },
				{ p[6], glm::vec2(1.0f, 1.0f), glm::vec3(0.0f,-1.0f, 0.0f), },
				{ p[2], glm::vec2(1.0f, 0.0f), glm::vec3(0.0f,-1.0f, 0.0f), },
				{ p[1], glm::vec2(0.0f, 0.0f), glm::vec3(0.0f,-1.0f, 0.0f), },
			};

			vertex_count_ = sizeof(vertices) / sizeof(vertices[0]);

			if (!buffer_.create(BUFFER_ACCESS_MODE_STATIC, sizeof(vertices), vertices)) {
				return on_error("could not create vertex buffer!");
			}
		}

		// note: describe vertex layout
		{
			layout_.add_attribute(0, vertex_layout::ATTRIBUTE_FORMAT_FLOAT, 3, false);
			layout_.add_attribute(1, vertex_layout::ATTRIBUTE_FORMAT_FLOAT, 2, false);
			layout_.add_attribute(2, vertex_layout::ATTRIBUTE_FORMAT_FLOAT, 3, false);
		}

		// note: load bitmap and create sun texture
		{
			bitmap image;
			if (!image.create("assets/bigSun.png")) {
				return on_error("could not load bitmap image!");
			}
			texture_format format = texture::from_bitmap_format(image.pixel_format());
			int32 width = image.width();
			int32 height = image.height();
			const uint8* data = image.data();
			if (!texture_Sun.create(format, width, height, data)) {
				return on_error("could not create texture!");
			}
			image.destroy();
		}

		// note: load bitmap and create earth texture
		{
			bitmap image;
			if (!image.create("assets/earth.png")) {
				return on_error("could not load bitmap image!");
			}
			texture_format format = texture::from_bitmap_format(image.pixel_format());
			int32 width = image.width();
			int32 height = image.height();
			const uint8* data = image.data();
			if (!texture_Earth.create(format, width, height, data)) {
				return on_error("could not create texture!");
			}
			image.destroy();
		}

		// note: load bitmap and create moon texture
		{
			bitmap image;
			if (!image.create("assets/moon.png")) {
				return on_error("could not load bitmap image!");
			}
			texture_format format = texture::from_bitmap_format(image.pixel_format());
			int32 width = image.width();
			int32 height = image.height();
			const uint8* data = image.data();
			if (!texture_Moon.create(format, width, height, data)) {
				return on_error("could not create texture!");
			}
			image.destroy();
		}

		// note: load bitmap and create mars texture
		{
			bitmap image;
			if (!image.create("assets/mars.png")) {
				return on_error("could not load bitmap image!");
			}
			texture_format format = texture::from_bitmap_format(image.pixel_format());
			int32 width = image.width();
			int32 height = image.height();
			const uint8* data = image.data();
			if (!texture_Mars.create(format, width, height, data)) {
				return on_error("could not create texture!");
			}
			image.destroy();
		}

		// note: load bitmap and create venus texture
		{
			bitmap image;
			if (!image.create("assets/venus.png")) {
				return on_error("could not load bitmap image!");
			}
			texture_format format = texture::from_bitmap_format(image.pixel_format());
			int32 width = image.width();
			int32 height = image.height();
			const uint8* data = image.data();
			if (!texture_Venus.create(format, width, height, data)) {
				return on_error("could not create texture!");
			}
			image.destroy();
		}
		// note: load bitmap and create jupiter texture
		{
			bitmap image;
			if (!image.create("assets/jupiter.png")) {
				return on_error("could not load bitmap image!");
			}
			texture_format format = texture::from_bitmap_format(image.pixel_format());
			int32 width = image.width();
			int32 height = image.height();
			const uint8* data = image.data();
			if (!texture_Jupiter.create(format, width, height, data)) {
				return on_error("could not create texture!");
			}
			image.destroy();
		}

		// note: load bitmap and create mercury texture
		{
			bitmap image;
			if (!image.create("assets/mercury.png")) {
				return on_error("could not load bitmap image!");
			}
			texture_format format = texture::from_bitmap_format(image.pixel_format());
			int32 width = image.width();
			int32 height = image.height();
			const uint8* data = image.data();
			if (!texture_Mercury.create(format, width, height, data)) {
				return on_error("could not create texture!");
			}
			image.destroy();
		}

		// note: load bitmap and create Neptune texture
		{
			bitmap image;
			if (!image.create("assets/neptune.png")) {
				return on_error("could not load bitmap image!");
			}
			texture_format format = texture::from_bitmap_format(image.pixel_format());
			int32 width = image.width();
			int32 height = image.height();
			const uint8* data = image.data();
			if (!texture_Neptune.create(format, width, height, data)) {
				return on_error("could not create texture!");
			}
			image.destroy();
		}

		// note: load bitmap and create saturn texture
		{
			bitmap image;
			if (!image.create("assets/saturn.png")) {
				return on_error("could not load bitmap image!");
			}
			texture_format format = texture::from_bitmap_format(image.pixel_format());
			int32 width = image.width();
			int32 height = image.height();
			const uint8* data = image.data();
			if (!texture_Saturn.create(format, width, height, data)) {
				return on_error("could not create texture!");
			}
			image.destroy();
		}

		// note: load bitmap and create uranus texture
		{
			bitmap image;
			if (!image.create("assets/uranus.png")) {
				return on_error("could not load bitmap image!");
			}
			texture_format format = texture::from_bitmap_format(image.pixel_format());
			int32 width = image.width();
			int32 height = image.height();
			const uint8* data = image.data();
			if (!texture_Uranus.create(format, width, height, data)) {
				return on_error("could not create texture!");
			}
			image.destroy();
		}
		// note: create sampler state
		{
			if (!sampler_.create(SAMPLER_FILTER_MODE_LINEAR,
				SAMPLER_ADDRESS_MODE_CLAMP,
				SAMPLER_ADDRESS_MODE_CLAMP))
			{
				return on_error("could not create sampler state!");
			}
		}
		projection_ = glm::perspective(3.141592f / 4, 16.0f / 9.0f, 1.0f, 200.0f);
		return true;
	}

	void renderapp::on_exit()
	{
	}

	bool renderapp::on_tick(const time& deltatime)
	{
		if (keyboard_.key_pressed(keyboard::key::escape)) {
			return false;
		}
		//update Sun
		{
			const glm::mat4 t1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -3.0f, -80.0f));
			const glm::mat4 r = glm::rotate(glm::mat4(1.0f), time::now().as_seconds() / 10, glm::vec3(0.0f, 1.0f, 0.0f));
			const glm::mat4 s = glm::scale(glm::mat4(1.0f), glm::vec3(6.2f, 6.2f, 6.2f));
			world_sun = t1 * r * s;

		}
		//update Mercury
		{
			const glm::mat4 t1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -3.0f, -80.0f));
			const glm::mat4 t2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
			const glm::mat4 r = glm::rotate(glm::mat4(1.0f), time::now().as_seconds() / 3, glm::vec3(0.0f, 1.0f, 0.0f));
			const glm::mat4 s = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
			world_mercury = t1 * r * t2 * s;
		}
		//update Venus
		{
			const glm::mat4 t1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -3.0f, -80.0f));
			const glm::mat4 t2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -15.0f));
			const glm::mat4 r = glm::rotate(glm::mat4(1.0f), time::now().as_seconds() / 3, glm::vec3(0.0f, 1.0f, 0.0f));
			const glm::mat4 s = glm::scale(glm::mat4(1.0f), glm::vec3(1.2f, 1.2f, 1.2f));
			world_venus = t1 * r * t2 * s;
		}
		//update Earth
		{
			const glm::mat4 t1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -3.0f, -80.0f));
			const glm::mat4 t2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -20.0f));
			const glm::mat4 r1 = glm::rotate(glm::mat4(1.0f), time::now().as_seconds() / 3, glm::vec3(0.0f, 1.0f, 0.0f));
			const glm::mat4 s = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f, 1.5f, 1.5f));
			world_earth = t1 * r1 * t2 * r1* s;
		}
		//update Moon
		{
			const glm::mat4 t1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -3.0f, -80.0f));
			const glm::mat4 t2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -20.0f));
			const glm::mat4 t3 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));

			const glm::mat4 r1 = glm::rotate(glm::mat4(1.0f), time::now().as_seconds() / 3, glm::vec3(0.0f, 1.0f, 0.0f));
			const glm::mat4 r2 = glm::rotate(glm::mat4(1.0f), time::now().as_seconds(), glm::vec3(0.0f, 1.0f, 0.0f));

			const glm::mat4 s = glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 0.3f, 0.3f));
			world_moon = t1 * r1 * t2 * s * r2 * t3;
		}
		//update Mars
		{
			const glm::mat4 t1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -3.0f, -80.0f));
			const glm::mat4 t2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -25.0f));
			const glm::mat4 r = glm::rotate(glm::mat4(1.0f), time::now().as_seconds() / 3, glm::vec3(0.0f, 1.0f, 0.0f));
			const glm::mat4 s = glm::scale(glm::mat4(1.0f), glm::vec3(1.3f, 1.3f, 1.3f));
			world_mars = t1 * r * t2 * s;
		}
		//update Jupiter
		{
			const glm::mat4 t1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -3.0f, -80.0f));
			const glm::mat4 t2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -32.0f));
			const glm::mat4 r = glm::rotate(glm::mat4(1.0f), time::now().as_seconds() / 3, glm::vec3(0.0f, 1.0f, 0.0f));
			const glm::mat4 s = glm::scale(glm::mat4(1.0f), glm::vec3(3.5f, 3.5f, 3.5f));
			world_jupiter = t1 * r * t2 * s;
		}
		//update Saturn
		{
			const glm::mat4 t1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -3.0f, -80.0f));
			const glm::mat4 t2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -42.0f));
			const glm::mat4 r = glm::rotate(glm::mat4(1.0f), time::now().as_seconds() / 3, glm::vec3(0.0f, 1.0f, 0.0f));
			const glm::mat4 s = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 2.0f));
			world_saturn = t1 * r * t2 * s;
		}
		//update uranus
		{
			const glm::mat4 t1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -3.0f, -80.0f));
			const glm::mat4 t2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -50.0f));
			const glm::mat4 r = glm::rotate(glm::mat4(1.0f), time::now().as_seconds() / 3, glm::vec3(0.0f, 1.0f, 0.0f));
			const glm::mat4 s = glm::scale(glm::mat4(1.0f), glm::vec3(1.8f, 1.8f, 1.8f));
			world_uranus = t1 * r * t2 * s;
		}
		return true;
	}

	void renderapp::on_draw()
	{
		renderer_.clear(0.0f, 0.0f, 0.0f, 1.0f);

		renderer_.set_shader_program(shader_);
		renderer_.set_sampler_state(sampler_);
		renderer_.set_vertex_buffer(buffer_);
		renderer_.set_vertex_layout(layout_);
		renderer_.set_depth_state(true, true);

		renderer_.set_shader_uniform(shader_, UNIFORM_TYPE_MATRIX, "u_projection", 1, glm::value_ptr(projection_));

		DrawSun();
		DrawEarth();
		DrawMoon();
		DrawMercury();
		DrawVenus();
		DrawMars();
		DrawJupiter();
		DrawNeptune();
		DrawSaturn();
		DrawUranus();
	}
	void renderapp::DrawSun()
	{
		renderer_.set_texture(texture_Sun);
		renderer_.set_shader_uniform(shader_, UNIFORM_TYPE_MATRIX, "u_world", 1, glm::value_ptr(world_sun));
		renderer_.draw(PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, 0, vertex_count_);
	}
	void renderapp::DrawEarth()
	{
		renderer_.set_texture(texture_Earth);
		renderer_.set_shader_uniform(shader_, UNIFORM_TYPE_MATRIX, "u_world", 1, glm::value_ptr(world_earth));
		renderer_.draw(PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, 0, vertex_count_);
	}
	void renderapp::DrawMoon()
	{
		renderer_.set_texture(texture_Moon);
		renderer_.set_shader_uniform(shader_, UNIFORM_TYPE_MATRIX, "u_world", 1, glm::value_ptr(world_moon));
		renderer_.draw(PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, 0, vertex_count_);
	}
	void renderapp::DrawMercury()
	{
		renderer_.set_texture(texture_Mercury);
		renderer_.set_shader_uniform(shader_, UNIFORM_TYPE_MATRIX, "u_world", 1, glm::value_ptr(world_mercury));
		renderer_.draw(PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, 0, vertex_count_);
	}
	void renderapp::DrawVenus()
	{
		renderer_.set_texture(texture_Venus);
		renderer_.set_shader_uniform(shader_, UNIFORM_TYPE_MATRIX, "u_world", 1, glm::value_ptr(world_venus));
		renderer_.draw(PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, 0, vertex_count_);
	}
	void renderapp::DrawMars()
	{
		renderer_.set_texture(texture_Mars);
		renderer_.set_shader_uniform(shader_, UNIFORM_TYPE_MATRIX, "u_world", 1, glm::value_ptr(world_mars));
		renderer_.draw(PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, 0, vertex_count_);
	}
	void renderapp::DrawJupiter()
	{
		renderer_.set_texture(texture_Jupiter);
		renderer_.set_shader_uniform(shader_, UNIFORM_TYPE_MATRIX, "u_world", 1, glm::value_ptr(world_jupiter));
		renderer_.draw(PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, 0, vertex_count_);
	}
	void renderapp::DrawNeptune()
	{
		renderer_.set_texture(texture_Neptune);
		renderer_.set_shader_uniform(shader_, UNIFORM_TYPE_MATRIX, "u_world", 1, glm::value_ptr(world_neptune));
		renderer_.draw(PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, 0, vertex_count_);
	}
	void renderapp::DrawSaturn()
	{
		renderer_.set_texture(texture_Saturn);
		renderer_.set_shader_uniform(shader_, UNIFORM_TYPE_MATRIX, "u_world", 1, glm::value_ptr(world_saturn));
		renderer_.draw(PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, 0, vertex_count_);
	}
	void renderapp::DrawUranus()
	{
		renderer_.set_texture(texture_Uranus);
		renderer_.set_shader_uniform(shader_, UNIFORM_TYPE_MATRIX, "u_world", 1, glm::value_ptr(world_uranus));
		renderer_.draw(PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, 0, vertex_count_);
	}
} // !avocado
