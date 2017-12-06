#pragma once
#include "gameobject.h"

#pragma once
#include "../EGGIN/gameobject.h"
#include "../EGGIN/api.h"

namespace eui {
	struct rect {
		float x;
		float y;
		float w;
		float h;
	};

	class Image : public GameObject
	{
	private:
		render::mesh mesh;
	public:
		rect pos;
		rect UV;

		void init() {
			mesh = render::mesh();
			mesh.vert_size = 6;
		}

		Image(string texture, rect r = { -0.5f, -0.5f, 0.5f, 0.5f })
		{
			init();
			setRect(r);
			setUv({ 0.0,0.0,1.0,1.0 });
			updateTexture(api->texture.load(texture));
		}

		Image(int textureid, rect r = { -0.5f, -0.5f, 0.5f, 0.5f })
		{
			init();
			setRect(r);
			setUv({ 0.0,0.0,1.0,1.0 });
			updateTexture(textureid);
		}

		void updateTexture(int newtex) {
			mesh.texture = newtex;
		}

		void setRect(rect newrect)
		{
			pos = newrect;
			
			if(mesh.vertices)
				delete[] mesh.vertices;
			mesh.vertices = new float[18]{
				newrect.x, newrect.y, 0.f,
				newrect.x + newrect.w, newrect.y, 0.f,
				newrect.x + newrect.w, newrect.y + newrect.h, 0.f,
				newrect.x + newrect.w, newrect.y + newrect.h, 0.f,
				newrect.x, newrect.y + newrect.h, 0.f,
				newrect.x, newrect.y, 0.f,
			};
		}

		void setUv(rect newuv)
		{
			UV = newuv;

			if (mesh.uvs)
				delete[] mesh.uvs;
			mesh.uvs = new float[12]{
				UV.x, UV.h,
				UV.w, UV.h,
				UV.w, UV.y,
				UV.w, UV.y,
				UV.x, UV.y,
				UV.x, UV.h,
			};
		}

		void draw2D() {
			api->render.api->mesh.draw(&mesh, vec3(), vec3());
		}
	};

	class Button : public GameObject
	{
	private:
		
	public:
		eui::Image *timg = nullptr;
		// Callbacks
		std::map<char, void(*)(Button* go)> events;

		Button(string texture, rect r = { -0.5f, -0.5f, 0.5f, 0.5f })
		{
			timg = new Image(texture, r);
		}

		Button(int textureid, rect r = { -0.5f, -0.5f, 0.5f, 0.5f })
		{
			timg = new Image(textureid, r);
		}

		~Button()
		{
			delete timg;
		}

		void draw2D() {
			timg->draw2D();
		}

		void onEvent(char e) {
			if (events.find(e) != events.end())
				events[e](this);
		}
	};
}