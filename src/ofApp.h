#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Sprite.h"
#include "Particle.h"
#include "ParticleEmitter.h"


typedef enum { MoveStop, MoveLeft, MoveRight, MoveUp, MoveDown, StopTrans } MoveDir;

class Emitter;

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void checkCollisions();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	ofImage background;

	bool startAnim = false;

	Emitter *player = NULL;
	Emitter *asteroids = NULL;
	Emitter *asteroids1 = NULL;
	Emitter *enemyLeft = NULL;
	Emitter *enemyLeftChild1 = NULL;
	Emitter *enemyLeftChild2 = NULL;
	Emitter *enemyRight = NULL;
	Emitter *enemyRightChild1 = NULL;
	Emitter *enemyRightChild2 = NULL;
	Emitter *mothership = NULL;
	Emitter *child1 = NULL;
	Emitter *child2 = NULL;
	Emitter *carrotEmitter = NULL;
	Emitter *animationEmitter = NULL;

	ParticleEmitter explosion;

	ofImage defaultImage;
	ofVec3f mouse_last;

	bool bHide;

	ofxFloatSlider rate;
	ofxFloatSlider life;
	ofxVec3Slider velocity;
	ofxLabel screenSize;

	MoveDir moveDir;

	void moveEmitter(MoveDir);
	void stopEmitter();

	int score;
	int health, mothershipHealth, enemyLeftHealth, enemyLeftChild1Health, enemyRightChild1Health, enemyLeftChild2Health, enemyRightChild2Health, enemyRightHealth, child1Health, child2Health, carrotCount;

	bool child1Alive, child2Alive;
	bool goingLeft = true;
	bool goingRight = false;

	float collisionDist;
	ofVec3f explosionPos;

	ofxPanel gui;
	ofSoundPlayer enemyExplosion, asteroidExplosion;

	ofTrueTypeFont titleFont;

	bool phase1, startPhase, carrotCollected, bossPhase, gameEnded, endPhase, endScreen;

	bool explodingAnim;

	ofVec3f mothershipTrans, animationTrans;

	ofImage tiltedCarrot, mothershipImage;
};
