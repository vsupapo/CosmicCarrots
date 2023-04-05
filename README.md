# Cosmic Carrots

## Description
Cosmic Carrots is a 2D shooter game developed using the OpenFrameworks C++ toolkit. Avoid enemy missiles and passing asteroids to collect the missing carrots and defeat the space teddies!

## Installation
1. Clone the repository
2. Open the project using Visual Studio

## Controls
Press `SPACE` to start.  
Use `SPACE` to shoot carrot missiles.  
Use the directional keys `UP` `DOWN` `LEFT` `RIGHT` to move.

## Gameplay

| Object | Image | Health | Score Value |
|----------------|-------------------|----------------------------|----------------|
| Asteroid | <img src="https://github.com/vsupapo/CosmicCarrots/blob/master/data/images/asteroid.png?raw=true" width="100" height="100"> | width=100) | 1 | 5 |
| Green Teddy | <img src="https://github.com/vsupapo/CosmicCarrots/blob/master/data/images/enemyUFOGreen.png?raw=true" width="100" height="100"> | width=100) | 1 | 15 |
| Blue Teddy | <img src="https://github.com/vsupapo/CosmicCarrots/blob/master/data/images/enemyUFOBlue.png?raw=true" width="100" height="100"> | width=100) | 1 | 15 |
| Mothership Teddy | <img src="https://github.com/vsupapo/CosmicCarrots/blob/master/data/images/mothership.png?raw=true" width="100" height="100"> | width=100) | 1 | 25 |


## Advanced Settings
Press `G` to open the GUI window and access advanced player missile settings. Using the GUI sliders, change missile settings for:
| Setting          | Value                                                          |
|------------------|----------------------------------------------------------------|
| `Size`           | Pixel size of missles as a value from 0 to 100.                |
| `Rate`           | Missile rate of fire as a value from 0 to 10.                  |
| `X Velocity`     | Vertical velocity of missiles as a value from -100 to 100.     |
| `Y Velocity`     | Horizontal velocity of missiles as a value from -100 to 100.   |
