// main.hpp

#pragma warning(push)
#pragma warning(disable: 4127)
#pragma warning(disable: 4201)
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#pragma warning(pop)
#include<fstream>
#include<iostream>
#include<string>
#include <avocado.hpp>
#include <avocado_render.hpp>
using namespace std;
namespace avocado {
	struct vertex {
		glm::vec3 position_;
		glm::vec2 texcoord_;
		glm::vec3 normal_;
	};
	struct renderapp final : application {
		renderapp();

		float v;

		virtual bool on_init();
		virtual void on_exit();
		virtual bool on_tick(const time& deltatime);
		virtual void on_draw();

		void DrawSun();
		void DrawEarth();
		void DrawMoon();
		void DrawMercury();
		void DrawVenus();
		void DrawMars();
		void DrawJupiter();
		void DrawNeptune();
		void DrawSaturn();
		void DrawUranus();

		renderer renderer_;
		shader_program shader_;
		vertex_buffer buffer_;
		vertex_layout layout_;
		texture texture_Sun;
		texture texture_Earth;
		texture texture_Moon;
		texture texture_Mercury;//shui xing
		texture texture_Venus;
		texture texture_Mars;
		texture texture_Jupiter;
		texture texture_Neptune;//hai wang
		texture texture_Saturn;//tu
		texture texture_Uranus;//tian wang
		sampler_state sampler_;
		int32 vertex_count_;

		glm::mat4 projection_;
		glm::mat4 world_earth;
		glm::mat4 world_sun;
		glm::mat4 world_moon;
		glm::mat4 world_mercury;
		glm::mat4 world_venus;
		glm::mat4 world_jupiter;
		glm::mat4 world_neptune;
		glm::mat4 world_uranus;
		glm::mat4 world_saturn;
		glm::mat4 world_mars;

		int PlanetIndex;
	};
} // !avocado
