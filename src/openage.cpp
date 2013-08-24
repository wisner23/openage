#include "openage.h"

#include <SDL2/SDL.h>
#include <GL/gl.h>

#include "engine/engine.h"
#include "engine/texture.h"
#include "log/log.h"
#include "util/fps.h"

namespace openage {

engine::Texture *gaben;

util::FrameCounter fpscounter;

void input_handler(SDL_Event *e) {
	if (e->type == SDL_QUIT) {
		engine::running = false;
	}
}

void draw_method() {
	gaben->draw(0, 0);

	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	{
		glVertex3f(0, 0, 0);
		glVertex3f(0, 10, 0);
		glVertex3f(10, 10, 0);
		glVertex3f(10, 0, 0);
	}
	glEnd();

	fpscounter.frame();
	log::msg("fps: %f", fpscounter.fps);
}

int mainmethod() {
	//init engine
	engine::init(draw_method, input_handler);

	//load textures and stuff
	gaben = new engine::Texture("gaben.bmp");

	//run main loop
	engine::loop();

	//de-init engine
	engine::destroy();

	return 0;
}

} //namespace openage

int main() {
	return openage::mainmethod();
}
