#include "ofMain.h"
#include "Emitter.h"



//  Create a new Emitter - needs a SpriteSystem
//
Emitter::Emitter(SpriteSystem *spriteSys) {
	sys = spriteSys;
	lifespan = 3000;    // milliseconds
	started = false;

	lastSpawned = 0;
	rate = 1;    // sprites/sec
	haveChildImage = false;
	haveImage = false;
	velocity = ofVec3f(100, 100, 0);
	drawable = true;
	width = 50;
	height = 50;
	childWidth = 10;
	childHeight = 10;
}

//  Draw the Emitter if it is drawable. In many cases you would want a hidden emitter
//
//
void Emitter::draw() {

	// draw sprite system
	//
	sys->draw();

	if (drawable) {

		if (haveImage) {
			image.draw(-image.getWidth() / 2.0 + trans.x, -image.getHeight() / 2.0 + trans.y);
		}
		else {
			ofSetColor(0, 0, 255);
			ofDrawRectangle(-width / 2 + trans.x, -height / 2 + trans.y, width, height);
		}
	}
}

//  Update the Emitter. If it has been started, spawn new sprites with
//  initial velocity, lifespan, birthtime.
//
void Emitter::update() {
	float time = ofGetElapsedTimeMillis();

	if (started) {
		// spawn a new sprite
		if ((time - lastSpawned) > (1000.0 / rate)) {
			Sprite sprite;
			if (haveChildImage) sprite.setImage(childImage);
			sprite.velocity = velocity;
			sprite.lifespan = lifespan;
			sprite.setPosition(trans);
			sprite.birthtime = time;
			sprite.width = childWidth;
			sprite.height = childHeight;
			sys->add(sprite);
			sound.play();
			lastSpawned = time;
		}
	}
	sys->update(); // Updates sprites already sent out even if emitter is not set to started(prevents hard reset of emitter)
}

// Start/Stop the emitter.
//
void Emitter::start() {
	started = true;
}

void Emitter::stop() {
	started = false;
}


void Emitter::setLifespan(float life) {
	lifespan = life;
}

void Emitter::setVelocity(ofVec3f v) {
	velocity = v;
}

void Emitter::setChildImage(ofImage img) {
	img.resize(img.getWidth() / 2.0, img.getHeight() / 2.0);
	childImage = img;
	haveChildImage = true;
	childWidth = img.getWidth();
	childHeight = img.getHeight();
}

void Emitter::setImage(ofImage img) {
	image = img;
	haveImage = true;
	width = img.getWidth();
	height = img.getHeight();
}

void Emitter::setRate(float r) {
	rate = r;
}

float Emitter::maxDistPerFrame() {
	return  velocity.length() / ofGetFrameRate();
}

void Emitter::integrate() {
	trans = trans + (integrateVelocity * 1 / ofGetFrameRate()); // Translate triangle based on velocity
	integrateVelocity = integrateVelocity + (acceleration * 1 / ofGetFrameRate()); // Apply acceleration force to velocity
	integrateVelocity *= damping; // Apply damping to simulate drag
}

