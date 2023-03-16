#include "ofApp.h"
#include "Emitter.h"
//----------------------------------------------------------------------------------
//
// This example code demonstrates the use of an "Emitter" class to emit Sprites
// and set them in motion. The concept of an "Emitter" is taken from particle
// systems (which we will cover next week).
//
//  1) Creates a simple Emitter  that you can drag around (without images)
//  2) Creates an Sprite to Collide with
//
//  requires ofxGUI add-in for sliders for changing parameters
// 
//
//
//  Kevin M. Smith - CS 134 SJSU

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetVerticalSync(true);
	background.load("images/startBackground.png");
	background.resize(ofGetWindowWidth(), ofGetWindowHeight());

	// Set up health hit points for enemies and player
	// 
	health = 20;
	carrotCount = 0;
	score = 0;
	mothershipHealth = 6;
	child1Health = 3;
	child2Health = 3;
	enemyLeftHealth = 1;
	enemyLeftChild1Health = 1;
	enemyLeftChild2Health = 1;
	enemyRightHealth = 1;
	enemyRightChild1Health = 1;
	enemyRightChild2Health = 1;

	// Import images for sprites and emitters
	tiltedCarrot = ofImage("images/tiltedCarrot.png");
	mothershipImage = ofImage("images/mothership.png");
	ofImage carrot = ofImage("images/carrot.png");
	ofImage asteroidImage = ofImage("images/asteroid.png");
	ofImage bunny = ofImage("images/bunnyUFO.png");
	ofImage enemyImage = ofImage("images/enemyUFOBlue.png");
	ofImage enemyChildImage = ofImage("images/enemyUFOGreen.png");
	ofImage childImage = ofImage("images/enemyUFOBlue.png");
	ofImage glowingBall = ofImage("images/glowingBall.png");

	titleFont.load("titleFont.ttf", 30);
	enemyExplosion.load("enemyExplosion.mp3");
	animationTrans = ofVec3f(-100, 3 * ofGetWindowHeight() / 4, 0);

	// Resize images
	asteroidImage.resize(150, 150);
	carrot.resize(29, 50);
	tiltedCarrot.resize(55, 58);
	bunny.resize(125, 81);
	enemyImage.resize(100, 65);
	childImage.resize(100, 65);
	enemyChildImage.resize(75, 50);
	mothershipImage.resize(150, 98);
	glowingBall.resize(30, 30);

	// Create player emitter, set image for emitter, image for child sprites, sound, lifespan
	player = new Emitter(new SpriteSystem());
	player->setImage(bunny);
	player->setChildImage(carrot);
	player->width = bunny.getWidth();
	player->height = bunny.getHeight();
	player->setChildSize(carrot.getWidth(), carrot.getHeight());
	player->sound.load("laser8.mp3");
	player->setLifespan(-1);
	player->acceleration.set(0, 0, 0);
	player->damping = .99;
	player->integrateVelocity.set(0, 1, 0);
	
	// Create animation emitter, set image for emitter, image for child sprites, sound, lifespan
	animationEmitter = new Emitter(new SpriteSystem());
	animationEmitter->setImage(mothershipImage);
	animationEmitter->setChildImage(mothershipImage);
	animationEmitter->setChildSize(mothershipImage.getWidth(), mothershipImage.getHeight());
	animationEmitter->sound.load("laser8.mp3");
	animationEmitter->sound.setVolume(0.0);

	animationEmitter->velocity.set(ofRandom(50, 100), ofRandom(50, 100), 0);
	animationEmitter->setLifespan(20000);
	animationEmitter->setRate(0.08);
	
	// Create carrot emitter, set image for emitter, image for child sprites, sound, lifespan
	carrotEmitter = new Emitter(new SpriteSystem());
	carrotEmitter->setImage(carrot);
	tiltedCarrot.resize(110, 116);
	carrotEmitter->setChildImage(tiltedCarrot);
	carrotEmitter->setChildSize(tiltedCarrot.getWidth(), tiltedCarrot.getHeight());
	tiltedCarrot.resize(55, 58);
	carrotEmitter->sound.load("laser8.mp3");
	carrotEmitter->sound.setVolume(0.0);

	carrotEmitter->velocity.set(ofRandom(50, 100), ofRandom(50, 100), 0);
	carrotEmitter->setLifespan(20000);
	carrotEmitter->setRate(0.08);

	// Create and set up asteroids emitter (left asteroid emitter)
	asteroids = new Emitter(new SpriteSystem());
	asteroids->setImage(asteroidImage);
	asteroids->setChildImage(asteroidImage);
	asteroids->setChildSize(asteroidImage.getWidth(), asteroidImage.getHeight());
	asteroids->sound.load("laser8.mp3");
	asteroids->sound.setVolume(0.0);

	asteroids->velocity.set(2 * ofRandom(50, 100), ofRandom(2 * 50, 100), 0);
	asteroids->setLifespan(20000);
	asteroids->setRate(0.8);

	// Create and set up asteroids emitter (right asteroid emitter)
	asteroids1 = new Emitter(new SpriteSystem());
	asteroids1->setImage(asteroidImage);
	asteroids1->setChildImage(asteroidImage);
	asteroids1->setChildSize(asteroidImage.getWidth(), asteroidImage.getHeight());
	asteroids1->sound.load("laser8.mp3");
	asteroids1->sound.setVolume(0.0);

	asteroids1->velocity.set(2 * ofRandom(50, 100), 2 * ofRandom(50, 100), 0);
	asteroids1->setLifespan(20000);
	asteroids1->setRate(0.8);

	// Create and set up left enemy emitter
	enemyLeft = new Emitter(new SpriteSystem());
	enemyLeft->setImage(enemyImage);
	enemyLeft->setChildImage(glowingBall);
	enemyLeft->setChildSize(glowingBall.getWidth(), glowingBall.getHeight());
	enemyLeft->sound.load("laser6.mp3");
	enemyLeft->sound.setVolume(0.0);

	enemyLeft->velocity.set(0, ofRandom(100, 150), 0);
	enemyLeft->setLifespan(7000);
	enemyLeft->setRate(0.8);

	// Create and set up left enemy emitter child 1
	enemyLeftChild1 = new Emitter(new SpriteSystem());
	enemyLeftChild1->setImage(enemyChildImage);
	enemyLeftChild1->setChildImage(glowingBall);
	enemyLeftChild1->setChildSize(glowingBall.getWidth(), glowingBall.getHeight());
	enemyLeftChild1->sound.load("laser6.mp3");
	enemyLeftChild1->sound.setVolume(0.0);

	enemyLeftChild1->velocity.set(0, ofRandom(100, 150), 0);
	enemyLeftChild1->setLifespan(7000);
	enemyLeftChild1->setRate(0.7);

	// Create and set up left enemy emitter child 2
	enemyLeftChild2 = new Emitter(new SpriteSystem());
	enemyLeftChild2->setImage(enemyChildImage);
	enemyLeftChild2->setChildImage(glowingBall);
	enemyLeftChild2->setChildSize(glowingBall.getWidth(), glowingBall.getHeight());
	enemyLeftChild2->sound.load("laser6.mp3");
	enemyLeftChild2->sound.setVolume(0.0);

	enemyLeftChild2->velocity.set(0, ofRandom(100, 150), 0);
	enemyLeftChild2->setLifespan(7000);
	enemyLeftChild2->setRate(0.7);

	// Create and set up right enemy emitter
	enemyRight = new Emitter(new SpriteSystem());
	enemyRight->setImage(enemyImage);
	enemyRight->setChildImage(glowingBall);
	enemyRight->setChildSize(glowingBall.getWidth(), glowingBall.getHeight());
	enemyRight->sound.load("laser6.mp3");
	enemyRight->sound.setVolume(0.0);

	enemyRight->velocity.set(0, ofRandom(100, 150), 0);
	enemyRight->setLifespan(7000);
	enemyRight->setRate(0.7);

	// Create and set up right enemy emitter child 1
	enemyRightChild1 = new Emitter(new SpriteSystem());
	enemyRightChild1->setImage(enemyChildImage);
	enemyRightChild1->setChildImage(glowingBall);
	enemyRightChild1->setChildSize(glowingBall.getWidth(), glowingBall.getHeight());
	enemyRightChild1->sound.load("laser6.mp3");
	enemyRightChild1->sound.setVolume(0.0);

	enemyRightChild1->velocity.set(0, ofRandom(100, 150), 0);
	enemyRightChild1->setLifespan(7000);
	enemyRightChild1->setRate(0.7);

	// Create and set up right enemy emitter child 2
	enemyRightChild2 = new Emitter(new SpriteSystem());
	enemyRightChild2->setImage(enemyChildImage);
	enemyRightChild2->setChildImage(glowingBall);
	enemyRightChild2->setChildSize(glowingBall.getWidth(), glowingBall.getHeight());
	enemyRightChild2->sound.load("laser6.mp3");
	enemyRightChild2->sound.setVolume(0.0);

	enemyRightChild2->velocity.set(0, ofRandom(100, 150), 0);
	enemyRightChild2->setLifespan(7000);
	enemyRightChild2->setRate(0.7);

	// Create and set up enemy mothership emitter
	mothership = new Emitter(new SpriteSystem());
	mothership->setImage(mothershipImage);
	mothership->setChildImage(glowingBall);
	mothership->setChildSize(glowingBall.getWidth(), glowingBall.getHeight());
	mothership->sound.load("laser6.mp3");
	//mothership->sound.setVolume(0.0);

	mothership->velocity.set(0, 100, 0);
	mothership->setLifespan(10000);
	mothership->setRate(1.2);

	// Create and set up mothership's left child emitter
	child1 = new Emitter(new SpriteSystem());
	child1->setImage(childImage);
	child1->setChildImage(glowingBall);
	child1->setChildSize(glowingBall.getWidth(), glowingBall.getHeight());
	child1->sound.load("laser6.mp3");
	//child1->sound.setVolume(0.0);

	child1->velocity.set(0, 100, 0);
	child1->setLifespan(10000);
	child1->setRate(0.1);

	// Create and set up mothership's right enemy emitter
	child2 = new Emitter(new SpriteSystem());
	child2->setImage(childImage);
	child2->setChildImage(glowingBall);
	child2->setChildSize(glowingBall.getWidth(), glowingBall.getHeight());
	child2->sound.load("laser6.mp3");
	child2->sound.setVolume(0.0);

	child2->velocity.set(0, 100, 0);
	child2->setLifespan(10000);
	child2->setRate(0.1);

	explosion.setOneShot(true);
	explosion.setEmitterType(RadialEmitter);
	explosion.setGroupSize(50);
	explosion.setLifespan(2);
	explosion.setVelocity(ofVec3f(100, 0, 0));
	explosion.setParticleRadius(2);

	// GUI set up
	gui.setup();
	gui.add(rate.setup("rate", 1.75, 1, 10));
	gui.add(life.setup("life", 2, .1, 10));
	gui.add(velocity.setup("velocity", ofVec3f(0, -200, 0), ofVec3f(-1000, -1000, -1000), ofVec3f(1000, 1000, 1000)));

	bHide = true;

	// Set positions of the emitters
	player->setPosition(ofVec3f(ofGetWindowWidth() + 300, ofGetWindowHeight() + 300, 0));
	asteroids->setPosition(ofVec3f(-100, 50, 0));
	asteroids1->setPosition(ofVec3f((ofGetWindowWidth() + 100), 50, 0));
	enemyLeft->setPosition(ofVec3f(-150, ofGetWindowHeight() / 8, 0));
	enemyLeftChild1->setPosition(ofVec3f(-150, ofGetWindowHeight() / 8, 0));
	enemyLeftChild2->setPosition(ofVec3f(-150, ofGetWindowHeight() / 8, 0));
	enemyRight->setPosition(ofVec3f(ofGetWindowWidth() + 150, ofGetWindowHeight() / 8, 0));
	enemyRightChild1->setPosition(ofVec3f(ofGetWindowWidth() + 150, ofGetWindowHeight() / 8, 0));
	enemyRightChild2->setPosition(ofVec3f(ofGetWindowWidth() + 150, ofGetWindowHeight() / 8, 0));
	mothership->setPosition(ofVec3f(ofGetWindowWidth() / 2, -300, 0));
	child1->setPosition(ofVec3f(ofGetWindowWidth() / 2, -300, 0));
	child2->setPosition(ofVec3f(ofGetWindowWidth() / 2, -300, 0));
	carrotEmitter->setPosition(ofVec3f(ofGetWindowWidth() / 2, -100, 0));
	animationEmitter->setPosition(ofVec3f(-100, ofGetWindowHeight() / 3, 0));

	// Set initial state of the emitters
	player->stop();
	asteroids->stop();
	asteroids1->stop();
	enemyLeft->start();
	enemyLeftChild1->stop();
	enemyLeftChild2->stop();
	enemyRight->stop();
	enemyRightChild1->stop();
	enemyRightChild2->stop();
	mothership->stop();
	child1->stop();
	child2->stop();
	carrotEmitter->stop();
	animationEmitter->stop();

	startAnim = false;
	phase1 = true;
	child1Alive = true;
	child2Alive = true;
	carrotCollected = false;
	gameEnded = false;
	endScreen = false;
	startPhase = false;
	explodingAnim = false;
}
//--------------------------------------------------------------
void ofApp::update() {
	float dist = 120 / ofGetFrameRate();
	ofVec3f dir;
	background.resize(ofGetWindowWidth(), ofGetWindowHeight()); // fit background to window resize(temporary until window size is finalized)

	if (carrotCount > 3) {
		carrotEmitter->stop();
	}
	// Move emitter based on directional buttons
	if (startAnim) {
		if (carrotCount == 0 && !carrotCollected) {
			startPhase = true;
			if (player->trans.y > 500) {
				player->trans -= ofVec3f(0, dist, 0);
			}
			else {
				carrotCount += 1;
			}
		}
		if (carrotCollected && carrotCount < 4) { 
			carrotEmitter->start();
		}
		carrotEmitter->update();
		carrotEmitter->sys->windowBounce();

		if (health < 1) {
			startAnim = false;
		}

		if (carrotCount > 0) {
			startPhase = false;
		}

		if (!startPhase) {
			switch (moveDir)
			{
			case MoveUp:
				if (player->trans.y - (player->height / 2.0) > 0) {
					player->acceleration = ofVec3f(0, -dist, 0);
					player->trans += player->acceleration;
					player->integrateVelocity += player->acceleration;
					player->integrateVelocity *= player->damping;
				}
				break;
			case MoveDown:
				if (player->trans.y + (player->height / 2.0) < ofGetWindowHeight()) {
					player->acceleration = ofVec3f(0, dist, 0);
					player->trans += player->acceleration;
					player->integrateVelocity += player->acceleration;
					player->integrateVelocity *= player->damping;
				}
				break;
			case MoveLeft:
				if (player->trans.x - (player->width / 2.0) > 0) {
					player->acceleration = ofVec3f(-dist, 0, 0);
					player->trans += player->acceleration;
					player->integrateVelocity += player->acceleration;
					player->integrateVelocity *= player->damping;
				}
				break;
			case MoveRight:
				if (player->trans.x + (player->width / 2.0) < ofGetWindowWidth()) {
					player->acceleration = ofVec3f(dist, 0, 0);
					player->trans += player->acceleration;
					player->integrateVelocity += player->acceleration;
					player->integrateVelocity *= player->damping;
				}
				break;
			case StopTrans:
				player->acceleration -= player->acceleration;
				if (player->trans.y - (player->height / 2.0) > 0 && player->trans.y + (player->height / 2.0) < ofGetWindowHeight()
					&& player->trans.x - (player->width / 2.0) > 0 && player->trans.x + (player->width / 2.0) < ofGetWindowWidth()) {
					player->integrate();
				}
				else {
					player->integrateVelocity = ofVec3f(0, 0, 0);
				}
				break;
			}
		}

		// If the player has started the game and has gotten at least one point
		// Start left and right enemy emitters
		if (score >= 0 && carrotCollected) {
			if (enemyLeft->started) {
				// Set velocity of the emitters so they will not move across the screen in the same spot
				// If emitters go off screen, move back to original side
				if (enemyLeft->trans.x < ofGetWindowWidth() + 180 && enemyLeftHealth > 0) {
					enemyLeft->trans += ofVec3f(dist, ofRandom(dist / 4, dist), 0);
					if (enemyLeftChild1Health > 0) {
						enemyLeftChild1->setPosition(ofVec3f(enemyLeft->trans.x - 100, enemyLeft->trans.y - 30, 0));
						enemyLeftChild1->start();
					}
					if (enemyLeftChild2Health > 0) {
						enemyLeftChild2->setPosition(ofVec3f(enemyLeft->trans.x - enemyLeftChild1->width - 100, enemyLeft->trans.y - enemyLeftChild1->height, 0));
						enemyLeftChild2->start();
					}
				}
				else {
					enemyLeft->stop();
					enemyLeft->setPosition(ofVec3f(-150, ofGetWindowHeight() / 8, 0));
					enemyLeftChild1->setPosition(ofVec3f(-150, ofGetWindowHeight() / 8, 0));
					enemyLeftChild2->setPosition(ofVec3f(-150, ofGetWindowHeight() / 8, 0));
					enemyLeftHealth = 1;
					enemyLeftChild1Health = 1;
					enemyLeftChild2Health = 1;
					enemyRight->start();
				}
			}

			if (enemyRight->started) {
				if (enemyRight->trans.x > -180 && enemyRightHealth > 0) {
					enemyRight->trans += ofVec3f(-dist, ofRandom(dist / 4, dist), 0);
					if (enemyRightChild1Health > 0) {
						enemyRightChild1->setPosition(ofVec3f(enemyRight->trans.x + 100, enemyRight->trans.y - 30, 0));
						enemyRightChild1->start();
					}
					if (enemyRightChild2Health > 0) {
						enemyRightChild2->setPosition(ofVec3f(enemyRight->trans.x + enemyRightChild1->width + 100, enemyRight->trans.y - enemyRightChild1->height, 0));
						enemyRightChild2->start();
					}
				}
				else {
					enemyRight->stop();
					enemyRightChild1->stop();
					enemyRightChild2->stop();
					enemyRight->setPosition(ofVec3f(ofGetWindowWidth() + 150, ofGetWindowHeight() / 8, 0));
					enemyRightChild1->setPosition(ofVec3f(ofGetWindowWidth() + 150, ofGetWindowHeight() / 8, 0));
					enemyRightChild2->setPosition(ofVec3f(ofGetWindowWidth() + 150, ofGetWindowHeight() / 8, 0));
					enemyRightHealth = 1;
					enemyRightChild1Health = 1;
					enemyRightChild2Health = 1;
					enemyLeft->start();
				}
			}

		}

		// If player has reached a score of at least 200, start mothership phase
		if (mothershipHealth > 0 && carrotCount == 4) {
			carrotEmitter->stop();
			bossPhase = true;
			if (mothership->trans.y < 150) {
				mothership->trans += ofVec3f(0, dist, 0);
			}
			else {
				ofVec3f direction = ofVec3f(dist, 0, 0);
				int leftBound = ofGetWindowWidth() / 2 - 100;
				int rightBound = ofGetWindowWidth() / 2 + 100;

				// Strafing movement of mothership
				if (mothership->trans.x > leftBound && goingLeft) {
					mothership->trans -= direction / 2;
					goingLeft = true;
					goingRight = false;	
				}
				else if (mothership->trans.x < leftBound && goingLeft) {
					mothership->trans += direction / 2;
					goingLeft = false;
					goingRight = true;
				}
				else if (mothership->trans.x < rightBound && goingRight) {
					mothership->trans += direction / 2;
					goingLeft = false;
					goingRight = true;
				}
				else if (mothership->trans.x > rightBound && goingRight) {
					mothership->trans -= direction / 2;
					goingLeft = true;
					goingRight = false;
				}
				mothership->start();
				child1->start();
				child2->start();
			}
		}
		else if (mothershipHealth == 0 && carrotCount == 4) {
			bossPhase = false;
			gameEnded = true;
		}
		else {
			mothership->setPosition(ofVec3f(ofGetWindowWidth() / 2, -300, 0));
		}

		if (gameEnded && !endPhase) {
			explosion.setPosition(mothership->trans);
			explosion.start();
			enemyExplosion.play();
			endPhase = true;
		}

		if (endPhase) {
			asteroids->stop();
			asteroids1->stop();
			enemyLeft->stop();
			enemyLeftChild1->stop();
			enemyLeftChild2->stop();
			enemyRight->stop();
			enemyRightChild1->stop();
			enemyRightChild2->stop();
			mothership->stop();
			child1->stop();
			child2->stop();
			carrotEmitter->stop();

			asteroids->setPosition(ofVec3f(-100, 50, 0));
			asteroids1->setPosition(ofVec3f((ofGetWindowWidth() + 100), 50, 0));
			enemyLeft->setPosition(ofVec3f(-150, ofGetWindowHeight() / 8, 0));
			enemyLeftChild1->setPosition(ofVec3f(-150, ofGetWindowHeight() / 8, 0));
			enemyLeftChild2->setPosition(ofVec3f(-150, ofGetWindowHeight() / 8, 0));
			enemyRight->setPosition(ofVec3f(ofGetWindowWidth() + 150, ofGetWindowHeight() / 8, 0));
			enemyRightChild1->setPosition(ofVec3f(ofGetWindowWidth() + 150, ofGetWindowHeight() / 8, 0));
			enemyRightChild2->setPosition(ofVec3f(ofGetWindowWidth() + 150, ofGetWindowHeight() / 8, 0));
			mothership->setPosition(ofVec3f(ofGetWindowWidth() / 2, -300, 0));
			child1->setPosition(ofVec3f(ofGetWindowWidth() / 2, -300, 0));
			child2->setPosition(ofVec3f(ofGetWindowWidth() / 2, -300, 0));
			carrotEmitter->setPosition(ofVec3f(ofGetWindowWidth() / 2, -100, 0));

			if (endScreen) {
				if (player->trans.y > ofGetWindowHeight() / 2) {
					player->trans -= ofVec3f(0, dist, 0);
				}
				else {
					carrotCount += 1;
					startAnim = false;
				}
			}
			if (player->trans.x > ofGetWindowWidth() / 2) {
				player->trans -= ofVec3f(dist, 0, 0);
			}
			if (player->trans.x < ofGetWindowWidth() / 2) {
				player->trans += ofVec3f(dist, 0, 0);
			}
			if (player->trans.y > -(player->width)) {
				player->trans -= ofVec3f(0, dist / 2, 0);
			}
			else {
				player->setPosition(ofVec3f(ofGetWindowWidth() / 2, ofGetWindowHeight() + player->width, 0));
				endScreen = true;
			}
		}

		// Update player emitter parameters
		player->setRate(rate);
		player->setLifespan(life * 1000);    // convert to milliseconds 
		player->setVelocity(glm::vec3(velocity));
		player->update();

		ofVec3f v = mothership->velocity;
		mothership->setVelocity(ofVec3f(ofRandom(-v.y, v.y), v.y, v.z));

		asteroids->update();
		asteroids1->update();
		mothership->update();
		
		// If mothership's child1 still has health, tether its position to the motheship
		if (child1Health > 0) {
			child1->setPosition(ofVec3f(mothership->trans.x - 80, mothership->trans.y + 80, 0));
			ofVec3f v = child1->velocity;
			child1->setVelocity(ofVec3f(ofRandom(-v.y, v.y), v.y, v.z));
		}
		else {
			child1->stop();
			if (child1Alive) {
				child1Alive = false; 
				score += 25;
				explosion.setPosition(child1->trans);
				explosion.start();
				enemyExplosion.play();
			}
			child1->setPosition(ofVec3f(ofGetWindowWidth() / 2, -300, 0));
		}
		
		// If mothership's child2 still has health, tether its position to the motheship
		if (child2Health > 0) {
			child2->setPosition(ofVec3f(mothership->trans.x + 80, mothership->trans.y + 80, 0));
			ofVec3f v1 = child2->velocity;
			child2->setVelocity(ofVec3f(ofRandom(-v1.y, v1.y), v1.y, v1.z));
		}
		else {
			child2->stop();
			if (child2Alive) {
				child2Alive = false;
				score += 25;
				explosion.setPosition(child2->trans);
				explosion.start();
				enemyExplosion.play();
			}
			child2->setPosition(ofVec3f(ofGetWindowWidth() / 2, -300, 0));
		}

		if (endScreen) {
			if (animationEmitter->trans.x < ofGetWindowWidth() / 2) {
				animationEmitter->trans += ofVec3f(1.5 * dist, 0, 0);
			}
			if (animationEmitter->trans.x >= ofGetWindowWidth() / 2 - 50) {
				explodingAnim = true;
			}
			if (explodingAnim) {
				explosion.setPosition(animationEmitter->trans);
				animationEmitter->setPosition(ofVec3f(-300, -300, 0));
				explosion.start();
				explodingAnim = false;
			}
		}
		
		child1->update();
		child2->update();
		explosion.update();

		if (!gameEnded) {
			checkCollisions();
		}

		enemyLeft->update();
		enemyLeftChild1->update();
		enemyLeftChild2->update();
		enemyRight->update();
		enemyRightChild1->update();
		enemyRightChild2->update();

		v = asteroids->velocity;
		ofVec3f v1 = asteroids1->velocity;
		
		// Set asteroid emitter velocities to be random when moving across screen
		asteroids->setVelocity(ofVec3f(ofRandom(-v.y, v.y), v.y, v.z));
		asteroids1->setVelocity(ofVec3f(ofRandom(-v.y, v.y), v.y, v.z));
	}

}


//--------------------------------------------------------------
void ofApp::draw() {
	ofSetColor(255, 255, 255);
	background.draw(0, 0, 0);
	float dist = 120 / ofGetFrameRate();
	
	if (!carrotCollected && startAnim) {
		tiltedCarrot.draw(ofGetWindowWidth() / 2 - tiltedCarrot.getWidth() / 2, 500 - tiltedCarrot.getHeight() / 2, 0);
		
		string introText;
		introText += "You found a carrot!";
		ofSetColor(255, 255, 255);
		ofDrawBitmapString(introText, ofPoint(ofGetWindowWidth() / 2, 420));

		string introText1;
		introText1 += "Collect 4 more to win";
		ofSetColor(255, 255, 255);
		ofDrawBitmapString(introText1, ofPoint(ofGetWindowWidth() / 6, 580));

		string introText2;
		introText2 += "Press SPACE to start";
		ofSetColor(255, 255, 255);
		ofDrawBitmapString(introText2, ofPoint(ofGetWindowWidth() / 2, 680));
	}

	ofSetColor(255, 255, 255);
	player->draw();
	asteroids->draw();
	asteroids1->draw();
	enemyLeft->draw();
	enemyLeftChild1->draw();
	enemyLeftChild2->draw();
	enemyRight->draw();
	enemyRightChild1->draw();
	enemyRightChild2->draw();
	mothership->draw();
	child1->draw();
	child2->draw();
	carrotEmitter->draw();
	animationEmitter->draw();

	ofSetColor(255, 255, 255);
	explosion.draw();

	if (!bHide) {
		gui.draw();
	}

	if (phase1) {
		string startText;
		startText += "Press SPACE to start";
		ofSetColor(255, 255, 255);
		ofDrawBitmapString(startText, ofPoint(70, ofGetWindowHeight() / 2));
		titleFont.drawString("Cosmic", 40, 200);
		titleFont.drawString("Carrots", 60, 250);
	}

	if (carrotCollected) {
		if (bossPhase && mothershipHealth > 0) {
			mothershipTrans = mothership->trans;
			ofSetColor(255, 255, 255);
			tiltedCarrot.draw(mothershipTrans.x - tiltedCarrot.getWidth() / 2, mothershipTrans.y - tiltedCarrot.getHeight() / 2 - 100, 0);
		}
		if (mothershipHealth < 1) {
			if (mothershipTrans.y > -50) {
				ofSetColor(255, 255, 255);
				tiltedCarrot.draw(mothershipTrans.x - tiltedCarrot.getWidth() / 2, mothershipTrans.y - tiltedCarrot.getHeight() / 2 - 100 - dist, 0);
			}
			mothershipTrans -= ofVec3f(0, dist, 0);
		}

		if (endScreen) {
			ofSetColor(255, 255, 255);
			tiltedCarrot.draw(ofGetWindowWidth() / 2 - tiltedCarrot.getWidth() / 2, ofGetWindowHeight() / 2 - tiltedCarrot.getHeight() / 2, 0);
			player->draw();
		}

		string carrotCountText;
		carrotCountText += std::to_string(carrotCount) + "/5";
		ofSetColor(255, 255, 255);
		ofDrawBitmapString(carrotCountText, ofPoint(ofGetWindowWidth() - 45, (6 * ofGetWindowWidth() / 7) - 5));
		for (int i = 0; i < carrotCount; i++) {
			tiltedCarrot.draw(ofGetWindowWidth() - 60, 50 * i + (6 * ofGetWindowWidth() / 7), 0);
		}

		if (carrotCount == 5) {
			string scoreTextFinal;
			scoreTextFinal += "Your score was:";
			ofSetColor(255, 255, 255);
			ofDrawBitmapString(scoreTextFinal, ofPoint(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2 + 80));
			titleFont.drawString(std::to_string(score), ofGetWindowWidth() / 2 + 20, ofGetWindowHeight() / 2 + 130);
			titleFont.drawString("You found", 30, ofGetWindowHeight() / 2 - 200);
			titleFont.drawString("all 5", 80, ofGetWindowHeight() / 2 - 150);
			titleFont.drawString("carrots!", 50, ofGetWindowHeight() / 2 - 100);
		}

		if (!endScreen) {
			// Draw current score
			string scoreText;
			scoreText += "Score:";
			ofSetColor(255, 255, 255);
			ofDrawBitmapString(scoreText, ofPoint(20, 20));
			titleFont.drawString(std::to_string(score), 20, 65);

			// Draw current player health
			string healthText;
			healthText = "Health";
			ofSetColor(255, 255, 255);
			ofDrawBitmapString(healthText, 20, ofGetWindowHeight() - 60);
			ofNoFill();
			ofSetColor(255, 255, 255);
			ofDrawRectangle(20, ofGetWindowHeight() - 50, 10 * 20, 31);
			for (int i = 0; i < health; i++) {
				ofFill();
				if (health < 13) {
					ofSetColor(ofColor::orange);
				}
				if (health < 7) {
					ofSetColor(ofColor::red);
				}
				if (health >= 13) {
					ofSetColor(ofColor::green);
				}
				ofDrawRectangle((i * 10) + 20, ofGetWindowHeight() - 49, 10, 29);
			}
		}

		// Draw current mothership health
		ofNoFill();
		ofSetColor(255, 255, 255);
		ofDrawRectangle(mothership->trans.x - 31, mothership->trans.y - mothership->height / 2 - 20, 10 * 6 + 1, 10);
		for (int i = 0; i < mothershipHealth; i++) {
			ofFill();
			if (mothershipHealth > 0) {
				ofSetColor(ofColor::red);
			}
			if (mothershipHealth > 2) {
				ofSetColor(ofColor::orange);
			}
			if (mothershipHealth > 4) {
				ofSetColor(ofColor::green);
			}
			ofDrawRectangle((i * 10) + mothership->trans.x - 30, mothership->trans.y - mothership->height / 2 - 20, 10, 9);
		}

		// Draw mothership children health
		if (child1Alive) {
			ofNoFill();
			ofSetColor(255, 255, 255);
			ofDrawRectangle(mothership->trans.x - 130, mothership->trans.y + 35, 10 * 3, 7);
			for (int i = 0; i < child1Health; i++) {
				ofFill();
				if (child1Health == 1) {
					ofSetColor(ofColor::red);
				}
				if (child1Health == 2) {
					ofSetColor(ofColor::orange);
				}
				if (child1Health == 3) {
					ofSetColor(ofColor::green);
				}
				ofDrawRectangle((i * 10) + mothership->trans.x - 130, mothership->trans.y + 35, 10, 7);
			}
		}

		if (child2Alive) {
			ofNoFill();
			ofSetColor(255, 255, 255);
			ofDrawRectangle(mothership->trans.x + 105, mothership->trans.y + 35, 10 * 3, 7);
			for (int i = 0; i < child2Health; i++) {
				ofFill();
				if (child2Health == 1) {
					ofSetColor(ofColor::red);
				}
				if (child2Health == 2) {
					ofSetColor(ofColor::orange);
				}
				if (child2Health == 3) {
					ofSetColor(ofColor::green);
				}
				ofDrawRectangle((i * 10) + mothership->trans.x + 105, mothership->trans.y + 35, 10, 7);
			}
		}

		// If health is 0, stop movemement, show game over message and score
		if (health < 1) {
			string over;
			over = "GAME OVER";
			ofSetColor(255, 255, 255);
			titleFont.drawString(over, 45, ofGetWindowHeight() / 2);

			string scoreTextLoss;
			scoreTextLoss += "Your score was:";
			ofSetColor(255, 255, 255);
			ofDrawBitmapString(scoreTextLoss, ofPoint(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2 + 40));
			titleFont.drawString(std::to_string(score), ofGetWindowWidth() / 2 + 20, ofGetWindowHeight() / 2 + 90);
		}
	}
}
//--------------------------------------------------------------

//  This is a simple O(M x N) collision check
void ofApp::checkCollisions() {
	// Collisions between player sprites and asteroid emitter(left) sprites
	// Removes asteroids, removes player's sprite
	collisionDist = (player->childHeight / 4) + (asteroids->childHeight / 4);

	for (int i = 0; i < player->sys->sprites.size(); i++) {
		if (asteroids->sys->removeNear(player->sys->sprites[i].trans, collisionDist) > 0) {
			player->sys->sprites[i].lifespan = 0;
			score += 5 * asteroids->sys->removeNear(player->sys->sprites[i].trans, collisionDist);
		}
	}

	// Collisions between player sprites and asteroid emitter(right) sprites
	// Removes asteroids, removes player's sprite
	collisionDist = (player->childHeight / 4) + (asteroids1->childHeight / 4);

	for (int i = 0; i < player->sys->sprites.size(); i++) {
		if (asteroids1->sys->removeNear(player->sys->sprites[i].trans, collisionDist) > 0) {
			player->sys->sprites[i].lifespan = 0;
			score += 5 * asteroids1->sys->removeNear(player->sys->sprites[i].trans, collisionDist);
		}
	}

	// Collisions between player and asteroid emitter(left) sprites
	// Removes asteroids, lowers's player's health
	collisionDist = (player->width / 4) + (asteroids->childHeight / 4);

	for (int i = 0; i < asteroids->sys->sprites.size(); i++) {
		health -= asteroids->sys->removeNear(player->trans, collisionDist);
	}

	// Collisions between player and asteroid emitter(right) sprites
	// Removes asteroids, lowers's player's health
	collisionDist = (player->width / 4) + (asteroids1->childHeight / 4);

	for (int i = 0; i < asteroids1->sys->sprites.size(); i++) {
		health -= asteroids1->sys->removeNear(player->trans, collisionDist);
	}

	// Collisions between player and carrot sprites
	// Removes carrots, adds to carrot amount
	collisionDist = (player->width / 4) + (carrotEmitter->childHeight / 4);

	for (int i = 0; i < carrotEmitter->sys->sprites.size(); i++) {
		carrotCount += carrotEmitter->sys->removeNear(player->trans, collisionDist);
	}


	// Collisions between player and enemy emitter(left) sprites
	// Removes enemy sprites
	collisionDist = (player->width / 4) + (enemyLeft->childHeight / 4);

	for (int i = 0; i < player->sys->sprites.size(); i++) {
		if (enemyLeft->sys->removeNear(player->sys->sprites[i].trans, collisionDist) > 0) {
			int j = enemyLeft->sys->removeNear(player->sys->sprites[i].trans, collisionDist);
			player->sys->sprites[i].lifespan = 0;
		}
	}

	// Collisions between player and enemy emitter(right) sprites
	// Removes enemy sprites
	collisionDist = (player->width / 4) + (enemyRight->childHeight / 4);

	for (int i = 0; i < player->sys->sprites.size(); i++) {
		if (enemyRight->sys->removeNear(player->sys->sprites[i].trans, collisionDist) > 0) {
			int j = enemyRight->sys->removeNear(player->sys->sprites[i].trans, collisionDist);
			player->sys->sprites[i].lifespan = 0;
		}
	}

	// Collisions between player and enemy emitter(left) child 1 sprites
	// Removes enemy sprites
	collisionDist = (player->width / 4) + (enemyLeftChild1->childHeight / 4);

	for (int i = 0; i < player->sys->sprites.size(); i++) {
		if (enemyLeftChild1->sys->removeNear(player->sys->sprites[i].trans, collisionDist) > 0) {
			int j = enemyLeftChild1->sys->removeNear(player->sys->sprites[i].trans, collisionDist);
			player->sys->sprites[i].lifespan = 0;
		}
	}

	// Collisions between player and enemy emitter(right) child 1 sprites
	// Removes enemy sprites
	collisionDist = (player->width / 4) + (enemyRightChild1->childHeight / 4);

	for (int i = 0; i < player->sys->sprites.size(); i++) {
		if (enemyRightChild1->sys->removeNear(player->sys->sprites[i].trans, collisionDist) > 0) {
			int j = enemyRightChild1->sys->removeNear(player->sys->sprites[i].trans, collisionDist);
			player->sys->sprites[i].lifespan = 0;
		}
	}

	// Collisions between player and enemy emitter(left) child 2 sprites
	// Removes enemy sprites
	collisionDist = (player->width / 4) + (enemyLeftChild2->childHeight / 4);

	for (int i = 0; i < player->sys->sprites.size(); i++) {
		if (enemyLeftChild2->sys->removeNear(player->sys->sprites[i].trans, collisionDist) > 0) {
			int j = enemyLeftChild2->sys->removeNear(player->sys->sprites[i].trans, collisionDist);
			player->sys->sprites[i].lifespan = 0;
		}
	}

	// Collisions between player and enemy emitter(right) child 2 sprites
	// Removes enemy sprites
	collisionDist = (player->width / 4) + (enemyRightChild2->childHeight / 4);

	for (int i = 0; i < player->sys->sprites.size(); i++) {
		if (enemyRightChild2->sys->removeNear(player->sys->sprites[i].trans, collisionDist) > 0) {
			int j = enemyRightChild2->sys->removeNear(player->sys->sprites[i].trans, collisionDist);
			player->sys->sprites[i].lifespan = 0;
		}
	}

	// Collisions between player's sprites and enemy emitter(left)
	// Lowers enemy's health, increases score, removes player's sprite
	collisionDist = (player->childHeight / 4) + (enemyLeft->height / 4);

	for (int i = 0; i < player->sys->sprites.size(); i++) {
		if ((player->sys->sprites[i].trans.x - enemyLeft->trans.x) * (player->sys->sprites[i].trans.x - enemyLeft->trans.x) + (player->sys->sprites[i].trans.y - enemyLeft->trans.y) * (player->sys->sprites[i].trans.y - enemyLeft->trans.y) < collisionDist * collisionDist) {
			enemyLeftHealth -= 1;
			score += 25;
			explosion.setPosition(enemyLeft->trans);
			enemyLeft->setPosition(ofVec3f(ofGetWindowWidth() + 550, ofGetWindowHeight() / 8, 0));
			explosion.start();
			enemyExplosion.play();
			player->sys->sprites[i].lifespan = 0;
		}
	}

	// Collisions between player's sprites and enemy emitter(right)
	// Lowers enemy's health, increases score, removes player's sprite
	collisionDist = (player->childHeight / 4) + (enemyRight->height / 4);

	for (int i = 0; i < player->sys->sprites.size(); i++) {
		if ((player->sys->sprites[i].trans.x - enemyRight->trans.x) * (player->sys->sprites[i].trans.x - enemyRight->trans.x) + (player->sys->sprites[i].trans.y - enemyRight->trans.y) * (player->sys->sprites[i].trans.y - enemyRight->trans.y) < collisionDist * collisionDist) {
			enemyRightHealth -= 1;
			score += 25;
			explosion.setPosition(enemyRight->trans);
			enemyRight->setPosition(ofVec3f(-550, ofGetWindowHeight() / 8, 0));
			explosion.start();
			enemyExplosion.play();
			player->sys->sprites[i].lifespan = 0;
		}
	}

	// Collisions between player's sprites and enemy emitter(left) child 1
	// Lowers enemy's health, increases score, removes player's sprite
	collisionDist = (player->childHeight / 4) + (enemyLeftChild1->height / 4);

	for (int i = 0; i < player->sys->sprites.size(); i++) {
		if ((player->sys->sprites[i].trans.x - enemyLeftChild1->trans.x) * (player->sys->sprites[i].trans.x - enemyLeftChild1->trans.x) + (player->sys->sprites[i].trans.y - enemyLeftChild1->trans.y) * (player->sys->sprites[i].trans.y - enemyLeftChild1->trans.y) < collisionDist * collisionDist) {
			enemyLeftChild1Health -= 1;
			enemyLeftChild1->stop();
			score += 15;
			explosion.setPosition(enemyLeftChild1->trans);
			enemyLeftChild1->setPosition(ofVec3f(ofGetWindowWidth() + 550, ofGetWindowHeight() / 8, 0));
			explosion.start();
			enemyExplosion.play();
			player->sys->sprites[i].lifespan = 0;
		}
	}

	// Collisions between player's sprites and enemy emitter(right) child 1
	// Lowers enemy's health, increases score, removes player's sprite
	collisionDist = (player->childHeight / 4) + (enemyRightChild1->height / 4);

	for (int i = 0; i < player->sys->sprites.size(); i++) {
		if ((player->sys->sprites[i].trans.x - enemyRightChild1->trans.x) * (player->sys->sprites[i].trans.x - enemyRightChild1->trans.x) + (player->sys->sprites[i].trans.y - enemyRightChild1->trans.y) * (player->sys->sprites[i].trans.y - enemyRightChild1->trans.y) < collisionDist * collisionDist) {
			enemyRightChild1Health -= 1;
			enemyRightChild1->stop();
			score += 15;
			explosion.setPosition(enemyRightChild1->trans);
			enemyRightChild1->setPosition(ofVec3f(-550, ofGetWindowHeight() / 8, 0));
			explosion.start();
			enemyExplosion.play();
			player->sys->sprites[i].lifespan = 0;
		}
	}

	// Collisions between player's sprites and enemy emitter(left) child 2
	// Lowers enemy's health, increases score, removes player's sprite
	collisionDist = (player->childHeight / 4) + (enemyLeftChild2->height / 4);

	for (int i = 0; i < player->sys->sprites.size(); i++) {
		if ((player->sys->sprites[i].trans.x - enemyLeftChild2->trans.x) * (player->sys->sprites[i].trans.x - enemyLeftChild2->trans.x) + (player->sys->sprites[i].trans.y - enemyLeftChild2->trans.y) * (player->sys->sprites[i].trans.y - enemyLeftChild2->trans.y) < collisionDist * collisionDist) {
			enemyLeftChild2Health -= 1;
			enemyLeftChild2->stop();
			score += 15;
			explosion.setPosition(enemyLeftChild2->trans);
			enemyLeftChild2->setPosition(ofVec3f(ofGetWindowWidth() + 550, ofGetWindowHeight() / 8, 0));
			explosion.start();
			enemyExplosion.play();
			player->sys->sprites[i].lifespan = 0;
		}
	}

	// Collisions between player's sprites and enemy emitter(right) child 1
	// Lowers enemy's health, increases score, removes player's sprite
	collisionDist = (player->childHeight / 4) + (enemyRightChild2->height / 4);

	for (int i = 0; i < player->sys->sprites.size(); i++) {
		if ((player->sys->sprites[i].trans.x - enemyRightChild2->trans.x) * (player->sys->sprites[i].trans.x - enemyRightChild2->trans.x) + (player->sys->sprites[i].trans.y - enemyRightChild2->trans.y) * (player->sys->sprites[i].trans.y - enemyRightChild2->trans.y) < collisionDist * collisionDist) {
			enemyRightChild2Health -= 1;
			enemyRightChild2->stop();
			score += 15;
			explosion.setPosition(enemyRightChild2->trans);
			enemyRightChild2->setPosition(ofVec3f(-550, ofGetWindowHeight() / 8, 0));
			explosion.start();
			enemyExplosion.play();
			player->sys->sprites[i].lifespan = 0;
		}
	}

	// Collisions between player's sprites and child1 emitter(left) sprites
	// Removes child1's sprites
	collisionDist = (player->childHeight / 4) + (child1->childHeight / 4);

	for (int i = 0; i < player->sys->sprites.size(); i++) {
		if (child1->sys->removeNear(player->sys->sprites[i].trans, collisionDist) > 0) {
			int j = child1->sys->removeNear(player->sys->sprites[i].trans, collisionDist);
			player->sys->sprites[i].lifespan = 0;
		}
	}

	// Collisions between player's sprites and child1 emitter(left)
	// Lowers child1's health, removes player's sprite
	collisionDist = (player->childHeight / 4) + (child1->height / 4);

	for (int i = 0; i < player->sys->sprites.size(); i++) {
		if ((player->sys->sprites[i].trans.x - child1->trans.x) * (player->sys->sprites[i].trans.x - child1->trans.x) + (player->sys->sprites[i].trans.y - child1->trans.y) * (player->sys->sprites[i].trans.y - child1->trans.y) < collisionDist * collisionDist) {
			child1Health -= 1;
			player->sys->sprites[i].lifespan = 0;
		}
	}

	// Collisions between player's sprites and child2 emitter(right) sprites
	// Removes child2's sprites
	collisionDist = (player->childHeight / 4) + (child2->childHeight / 4);

	for (int i = 0; i < player->sys->sprites.size(); i++) {
		if (child2->sys->removeNear(player->sys->sprites[i].trans, collisionDist) > 0) {
			int j = child2->sys->removeNear(player->sys->sprites[i].trans, collisionDist);
			player->sys->sprites[i].lifespan = 0;
		}
	}

	// Collisions between player's sprites and child2 emitter(right)
	// Lowers child2's health, removes player's sprite
	collisionDist = (player->childHeight / 4) + (child2->height / 4);

	for (int i = 0; i < player->sys->sprites.size(); i++) {
		if ((player->sys->sprites[i].trans.x - child2->trans.x) * (player->sys->sprites[i].trans.x - child2->trans.x) + (player->sys->sprites[i].trans.y - child2->trans.y) * (player->sys->sprites[i].trans.y - child2->trans.y) < collisionDist * collisionDist) {
			child2Health -= 1;
			player->sys->sprites[i].lifespan = 0;
		}
	}

	// Collisions between player and enemy emitter(left) sprites
	// Lowers player health, removes enemy sprites
	collisionDist = (player->width / 4) + (enemyLeft->childHeight / 4);

	for (int i = 0; i < enemyLeft->sys->sprites.size(); i++) {
		health -= enemyLeft->sys->removeNear(player->trans, collisionDist);
	}

	// Collisions between player and enemy emitter(right) sprites
	// Lowers player health, removes enemy sprites
	collisionDist = (player->width / 4) + (enemyRight->childHeight / 4);

	for (int i = 0; i < enemyRight->sys->sprites.size(); i++) {
		health -= enemyRight->sys->removeNear(player->trans, collisionDist);
	}

	// Collisions between player and enemy emitter(left) child 1 sprites
	// Lowers player health, removes enemy sprites
	collisionDist = (player->width / 4) + (enemyLeftChild1->childHeight / 4);

	for (int i = 0; i < enemyLeftChild1->sys->sprites.size(); i++) {
		health -= enemyLeftChild1->sys->removeNear(player->trans, collisionDist);
	}

	// Collisions between player and enemy emitter(right) child 1 sprites
	// Lowers player health, removes enemy sprites
	collisionDist = (player->width / 4) + (enemyRightChild1->childHeight / 4);

	for (int i = 0; i < enemyRightChild1->sys->sprites.size(); i++) {
		health -= enemyRightChild1->sys->removeNear(player->trans, collisionDist);
	}

	// Collisions between player and enemy emitter(left) child 2 sprites
	// Lowers player health, removes enemy sprites
	collisionDist = (player->width / 4) + (enemyLeftChild2->childHeight / 4);

	for (int i = 0; i < enemyLeftChild2->sys->sprites.size(); i++) {
		health -= enemyLeftChild2->sys->removeNear(player->trans, collisionDist);
	}

	// Collisions between player and enemy emitter(right) child 2 sprites
	// Lowers player health, removes enemy sprites
	collisionDist = (player->width / 4) + (enemyRightChild2->childHeight / 4);

	for (int i = 0; i < enemyRightChild2->sys->sprites.size(); i++) {
		health -= enemyRightChild2->sys->removeNear(player->trans, collisionDist);
	}

	// Collisions between player and enemy emitter(left)
	// Lowers player health, reset's enemy emitter's position
	collisionDist = (player->width / 4) + (enemyLeft->width / 4);

	if ((player->trans.x - enemyLeft->trans.x) * (player->trans.x - enemyLeft->trans.x) + (player->trans.y - enemyLeft->trans.y) * (player->trans.y - enemyLeft->trans.y) < collisionDist * collisionDist) {
		health -= 1;
		explosion.setPosition(enemyLeft->trans);
		explosion.start();
		enemyExplosion.play();
		enemyLeft->setPosition(ofVec3f(-300, -300, 0));
	}

	// Collisions between player and enemy emitter(right)
	// Lowers player health, reset's enemy emitter's position
	collisionDist = (player->width / 4) + (enemyRight->width / 4);

	if ((player->trans.x - enemyRight->trans.x) * (player->trans.x - enemyRight->trans.x) + (player->trans.y - enemyRight->trans.y) * (player->trans.y - enemyRight->trans.y) < collisionDist * collisionDist) {
		health -= 1;
		explosion.setPosition(enemyRight->trans);
		explosion.start();
		enemyExplosion.play();
		enemyRight->setPosition(ofVec3f(-300, -300, 0));
	}

	// Collisions between player and enemy emitter(left)
// Lowers player health, reset's enemy emitter's position
	collisionDist = (player->width / 4) + (enemyLeftChild1->width / 4);

	if ((player->trans.x - enemyLeftChild1->trans.x) * (player->trans.x - enemyLeftChild1->trans.x) + (player->trans.y - enemyLeftChild1->trans.y) * (player->trans.y - enemyLeftChild1->trans.y) < collisionDist * collisionDist) {
		health -= 1;
		explosion.setPosition(enemyLeftChild1->trans);
		explosion.start();
		enemyExplosion.play();
		enemyLeftChild1->setPosition(ofVec3f(-300, -300, 0));
		enemyLeftChild1Health -= 1;
	}

	// Collisions between player and enemy emitter(right)
	// Lowers player health, reset's enemy emitter's position
	collisionDist = (player->width / 4) + (enemyRightChild1->width / 4);

	if ((player->trans.x - enemyRightChild1->trans.x) * (player->trans.x - enemyRightChild1->trans.x) + (player->trans.y - enemyRightChild1->trans.y) * (player->trans.y - enemyRightChild1->trans.y) < collisionDist * collisionDist) {
		health -= 1;
		explosion.setPosition(enemyRightChild1->trans);
		explosion.start();
		enemyExplosion.play();
		enemyRightChild1->setPosition(ofVec3f(-300, -300, 0));
		enemyRightChild1Health -= 1;
	}

	// Collisions between player and enemy emitter(left)
// Lowers player health, reset's enemy emitter's position
	collisionDist = (player->width / 4) + (enemyLeftChild2->width / 4);

	if ((player->trans.x - enemyLeftChild2->trans.x) * (player->trans.x - enemyLeftChild2->trans.x) + (player->trans.y - enemyLeftChild2->trans.y) * (player->trans.y - enemyLeftChild2->trans.y) < collisionDist * collisionDist) {
		health -= 1;
		explosion.setPosition(enemyLeftChild2->trans);
		explosion.start();
		enemyExplosion.play();
		enemyLeftChild2->setPosition(ofVec3f(-300, -300, 0));
		enemyLeftChild2Health -= 1;
	}

	// Collisions between player and enemy emitter(right)
	// Lowers player health, reset's enemy emitter's position
	collisionDist = (player->width / 4) + (enemyRightChild2->width / 4);

	if ((player->trans.x - enemyRightChild2->trans.x) * (player->trans.x - enemyRightChild2->trans.x) + (player->trans.y - enemyRightChild2->trans.y) * (player->trans.y - enemyRightChild2->trans.y) < collisionDist * collisionDist) {
		health -= 1;
		explosion.setPosition(enemyRightChild2->trans);
		explosion.start();
		enemyExplosion.play();
		enemyRightChild2->setPosition(ofVec3f(-300, -300, 0));
		enemyRightChild2Health -= 1;
	}

	// Collisions between player's sprites and mothership's sprites
	// Removes mothership's sprites
	collisionDist = (player->childHeight / 4) + (mothership->childHeight / 4);

	for (int i = 0; i < player->sys->sprites.size(); i++) {
		if (mothership->sys->removeNear(player->sys->sprites[i].trans, collisionDist) > 0) {
			int j = mothership->sys->removeNear(player->sys->sprites[i].trans, collisionDist);
			player->sys->sprites[i].lifespan = 0;
		}
	}

	// Collisions between player's sprites and mothership
	// Lowers mothership's health, removes player's sprite
	collisionDist = (player->childHeight / 4) + (mothership->height / 4);

	for (int i = 0; i < player->sys->sprites.size(); i++) {
		if ((player->sys->sprites[i].trans.x - mothership->trans.x) * (player->sys->sprites[i].trans.x - mothership->trans.x) + (player->sys->sprites[i].trans.y - mothership->trans.y) * (player->sys->sprites[i].trans.y - mothership->trans.y) < collisionDist * collisionDist) {
			mothershipHealth -= 1;
			player->sys->sprites[i].lifespan = 0;
		}
	}

	// Collisions between player and child1 emitter's sprites
	// Lowers player's health, removes child1's sprite
	collisionDist = (player->width / 4) + (child1->childHeight / 4);

	for (int i = 0; i < child1->sys->sprites.size(); i++) {
		health -= child1->sys->removeNear(player->trans, collisionDist);
	}

	// Collisions between player and child2 emitter's sprites
	// Lowers player's health, removes child2's sprite
	collisionDist = (player->width / 4) + (child2->childHeight / 4);

	for (int i = 0; i < child2->sys->sprites.size(); i++) {
		health -= child2->sys->removeNear(player->trans, collisionDist);
	}

	// Collisions between player and mothership emitter's sprites
	// Lowers player's health, removes mothership's sprite
	collisionDist = (player->width / 4) + (mothership->childHeight / 4);

	for (int i = 0; i < mothership->sys->sprites.size(); i++) {
		health -= mothership->sys->removeNear(player->trans, collisionDist);
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
	//	cout << "mouse( " << x << "," << y << ")" << endl;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	if (startAnim) {
		ofPoint mouse_cur = ofPoint(x, y);
		ofVec3f delta = mouse_cur - mouse_last;
		player->trans += delta;
		mouse_last = mouse_cur;
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	mouse_last = ofPoint(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

void ofApp::keyPressed(int key) {
	switch (key) {
	case 'C':
	case 'c':
		break;
	case 'F':
	case 'f':
		ofToggleFullscreen();
		break;
	case 'H':
	case 'h':
		bHide = !bHide;
		break;
	case 'r':
		break;
	case 's':
		break;
	case 'u':
		break;
	case ' ':
		if (!startAnim) {
			background.load("images/background.png");
			player->setPosition(ofVec3f(ofGetWindowWidth() / 2, 700, 0));
			startAnim = true;
			phase1 = false;
			break;
		}
		if (startPhase) {
			break;
		}
		player->start();
		carrotCollected = true;
		asteroids->start();
		asteroids1->start();
		break;
	case OF_KEY_RIGHT:
		moveEmitter(MoveRight);
		break;
	case OF_KEY_LEFT:
		moveEmitter(MoveLeft);
		break;
	case OF_KEY_UP:
		moveEmitter(MoveUp);
		break;
	case OF_KEY_DOWN:
		moveEmitter(MoveDown);
		break;
	case OF_KEY_ALT:
		break;
	case OF_KEY_CONTROL:
		break;
	case OF_KEY_SHIFT:
		break;
	case OF_KEY_DEL:
		break;
	}
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	switch (key) {
	case ' ':
		player->stop();
		break;
	case OF_KEY_LEFT:
	case OF_KEY_RIGHT:
	case OF_KEY_UP:
	case OF_KEY_DOWN:
		stopEmitter();
		moveDir = StopTrans;
		break;
	case OF_KEY_ALT:
		break;
	case OF_KEY_CONTROL:
		break;
	case OF_KEY_SHIFT:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

void ofApp::moveEmitter(MoveDir dir) {
	moveDir = dir;
}

void ofApp::stopEmitter() {
	moveDir = MoveStop;
}

