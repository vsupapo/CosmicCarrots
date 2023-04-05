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

| Object | Image | Health Points | Score Points | Description |
|:--------------:| :----------: |:--------------------------:|:--------------:|
| Asteroid | <img src="https://github.com/vsupapo/CosmicCarrots/blob/master/data/images/asteroid.png?raw=true" width="100" height="100"> | 1 | 5 | Asteroids will damage a player if the player's spaceship directly collides with an asteroid.
| Green Teddy | <img src="https://github.com/vsupapo/CosmicCarrots/blob/master/data/images/enemyUFOGreen.png?raw=true" width="100" height="70"> | 1 | 15 | Enemy green teddies shoot missiles that can be detroyed by colliding with player missiles. |
| Blue Teddy | <img src="https://github.com/vsupapo/CosmicCarrots/blob/master/data/images/enemyUFOBlue.png?raw=true" width="100" height="70"> | 1 | 15 | Enemy blue teddies shoot missiles that can be detroyed by colliding with player missiles. |
| Mothership Teddy | <img src="https://github.com/vsupapo/CosmicCarrots/blob/master/data/images/mothership.png?raw=true" width="150" height="105"> | 10 | 25 | The mothership teddy will appear with the final carrot once the player reaches a score of at least 200. The mothership teddy shoots missiles that can be detroyed by colliding with player missiles. |


## Advanced Settings
Press `G` to open the GUI window and access advanced player missile settings. Using the GUI sliders, change missile settings for:
| Setting          | Value                                                          |
|:----------------:|----------------------------------------------------------------|
| `Size`           | Pixel size of missles as a value from 0 to 100.                |
| `Rate`           | Missile rate of fire as a value from 0 to 10.                  |
| `X Velocity`     | Vertical velocity of missiles as a value from -100 to 100.     |
| `Y Velocity`     | Horizontal velocity of missiles as a value from -100 to 100.   |
