#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <time.h>
#include<vector>
#include<deque>
#include <random>
using namespace std;
using namespace sf;
int main() {
	srand(time(0));
	RenderWindow window(VideoMode(1520, 1080), "7kemdar El Fada2", Style::Titlebar | Style::Close);
	window.setFramerateLimit(60);
	Event event;
	Clock gameClock;
	float deltaTime = 0;
	float timer = 0;
	int reload = 0;     // countdown for shooting
	float reloadcanon = 0;
	float delay = 0.3f;
	float frameTime = 0.1;
	int waittime = 80;
	float mm = 0;
	int mn = 0;
	float pu = 0;
	//player stats
	int hp = 100;
	int player_power = 20;
	short player_damage = 5;
	float bullet_speed = 20;
	float reload_time = 20;
	bool powerup = 0;
	float hp_percent = 1;
	//enemy stats
	int round = 0;
	int enemy_damage = 5;
	int enemy_health = 3;
	int enemy_firingspeed = 5;
	int row_count = 2;
	int type1 = 30;
	int type2 = -5;
	int type3 = -5;
	float move = 0;
	float move_speed = 0.5;
	float enemybullet_speed = 7.0f;
	int bullets_amount = 710;


	unsigned int seed = 0;
	long long score = 0;

	struct bullet_struct {
		short x;
		short y;
		short damage;
		short type;
	};
	struct enemybullet_struct {
		int x;
		int y;
		int damage;
		int type;
	};
	struct enemies_struct {
		int hp;
		int damage;
		int type;
		int hp1 = hp * (type + 1), hp2 = hp * (type + 1), hp3 = hp * (type + 1), hp4 = hp * (type + 1),
			hp5 = hp * (type + 1), hp6 = hp * (type + 1), hp7 = hp * (type + 1), hp8 = hp * (type + 1),
			hp9 = hp * (type + 1), hp10 = hp * (type + 1);
	};
	struct explode_struct {
		int x;
		int y;
		int c = 0;
	};
	struct hit_struct {
		int x;
		int y;
		int c = 0;
	};

	deque<bullet_struct> bullets;     //projectiles location vector
	deque<enemies_struct> enemies;
	deque<explode_struct> exploding;
	deque<hit_struct> hits;
	deque<enemybullet_struct> enemybullets;

	Vector2f velocity = { 0, 0 };           //player's velocity
	Texture spaceShipTex, bggTex, bgTex, engineTex, idleTex, frontTex, backTex, weaponTex, extraweaponTex, bulletTex, canonballzTex, enemy1Tex,
		enemy2Tex, enemy3Tex, enemy1effectTex, enemy2effectTex, enemy3effectTex, explotionTex, hitTex, enemy1bulletTex, enemy2bulletTex, enemy3bulletTex;
	bggTex.loadFromFile("bgg.png");         // side bars background
	idleTex.loadFromFile("idleeffect.png");     // engine idle state
	frontTex.loadFromFile("fronteffect.png");    // engine moving forward state
	backTex.loadFromFile("backeffect.png");        // engine moving backwards state
	spaceShipTex.loadFromFile("spaceship.png");      // spaceship (has damage state {1-->4})
	engineTex.loadFromFile("engine 1.png");         //engine (1, 2 and 3 avilabale)
	weaponTex.loadFromFile("weapon 1.png");         //main weapon
	extraweaponTex.loadFromFile("weapon 2.png");        //powerup weapon
	bulletTex.loadFromFile("rockets.png");          // bullets (multiple states avilable) incomplete
	canonballzTex.loadFromFile("canonballz.png");
	enemy1Tex.loadFromFile("enemy1.png");
	enemy2Tex.loadFromFile("enemy2.png");
	enemy3Tex.loadFromFile("enemy3.png");
	enemy1effectTex.loadFromFile("enemy1effect.png");
	enemy2effectTex.loadFromFile("enemy2effect.png");
	enemy3effectTex.loadFromFile("enemy3effect.png");
	enemy1bulletTex.loadFromFile("enemy1bullet.png");
	enemy2bulletTex.loadFromFile("enemy2bullet.png");
	enemy3bulletTex.loadFromFile("enemy3bullet.png");
	explotionTex.loadFromFile("explotion.png");
	hitTex.loadFromFile("hit.png");
	Sprite spaceShip, bgg, bg, engineeffect, engine, weapon, extraweapon, bulletsprite, enemysprite, enemyspriteeffect, explotion, hit, enemybullet;
	//backgrounds sprite
	bgg.setTexture(bggTex);
	bgg.setPosition(0, 0);
	bgg.setScale(1.5, 1.5);
	RectangleShape blackbg;
	blackbg.setFillColor(Color::Black);
	blackbg.setSize({ 1520, 1080 });
	//healthbar
	RectangleShape health_bar;
	health_bar.setFillColor(Color(0, 150, 0, 200));
	health_bar.setSize({ 1520, 32 });
	health_bar.setPosition(0, 1048);
	//spaceship sprite
	spaceShip.setTexture(spaceShipTex);
	spaceShip.setTextureRect(IntRect(0, 0, 48, 48));
	spaceShip.setOrigin(48 / 2, 48 / 2);
	spaceShip.setPosition(760, 960);
	spaceShip.scale(2, 2);
	//engine effect sprite
	engineeffect.setTexture(idleTex);
	engineeffect.setTextureRect(IntRect(0, 0, 48, 48));
	engineeffect.setOrigin(48 / 2, 48 / 2);
	engineeffect.setPosition(760, 960);
	engineeffect.scale(2, 2);
	//engine sprite
	engine.setTexture(engineTex);
	engine.setTextureRect(IntRect(0, 0, 48, 48));
	engine.setOrigin(48 / 2, 48 / 2);
	engine.setPosition(760, 960);
	engine.scale(2, 2);
	//weapon sprite
	weapon.setTexture(weaponTex);
	weapon.setTextureRect(IntRect(0, 0, 48, 48));
	weapon.setOrigin(48 / 2, 48 / 2);
	weapon.setPosition(760, 960);
	weapon.scale(2, 2);
	//powerup weapon sprite
	extraweapon.setTexture(extraweaponTex);
	extraweapon.setTextureRect(IntRect(0, 0, 48, 48));
	extraweapon.setOrigin(48 / 2, 48 / 2);
	extraweapon.setPosition(760, 960);
	extraweapon.scale(2, 2);
	// bullet sprite
	bulletsprite.setTexture(bulletTex);
	bulletsprite.setTextureRect(IntRect(12, 9, 20, 26));
	bulletsprite.setOrigin(32 / 2, 32 / 2);
	bulletsprite.scale(2, 2);
	//enemie sprite
	enemysprite.setTexture(enemy1Tex);
	enemysprite.setTextureRect(IntRect(0, 0, 64, 64));
	enemysprite.setOrigin(64 / 2, 64 / 2);
	enemysprite.scale(2, 2);
	//enemy effect
	enemyspriteeffect.setTexture(enemy1effectTex);
	enemyspriteeffect.setTextureRect(IntRect(0, 0, 8, 8));
	enemyspriteeffect.setOrigin(8 / 2, 8 / 2);
	enemyspriteeffect.scale(4, 4);
	//explotions
	explotion.setTexture(explotionTex);
	explotion.setTextureRect(IntRect(0, 0, 64, 64));
	explotion.setOrigin(64 / 2, 64 / 2);
	explotion.scale(3, 3);
	//hits
	hit.setTexture(hitTex);
	hit.setTextureRect(IntRect(0, 0, 133, 133));
	hit.setOrigin(133 / 2, 133 / 2);
	hit.scale(1, 1);
	// enemy bullet sprite
	enemybullet.setTexture(enemy1bulletTex);
	enemybullet.setTextureRect(IntRect(0, 0, 8, 8));
	enemybullet.setOrigin(8 / 2, 8 / 2);
	enemybullet.scale(2, 2);



	//retro font
	Font font;
	font.loadFromFile("font.TTF");
	//pause text
	Text pause, esc, start, newround, title, scoretext, gameovertext, score_is, returnmenu;
	pause.setFillColor(Color::White);
	pause.setFont(font);
	pause.setString("Game  Paused");
	pause.setPosition(580, 450);
	pause.setCharacterSize(60);
	esc.setFillColor(Color::White);
	esc.setFont(font);
	esc.setString("Press  ESC  to  continue");
	esc.setPosition(585, 570);
	//start text
	start.setFont(font);
	start.setString("Press  ENTER  to  start!");
	start.setPosition(600, 800);

	// round text
	newround.setFont(font);
	newround.setPosition(680, 500);
	newround.setString("Round 1");
	newround.setCharacterSize(50);

	// title 
	title.setFont(font);
	title.setPosition(195, 350);
	title.setString("7kemdar  el  Fada2");
	title.setCharacterSize(140);
	//score
	scoretext.setFont(font);
	scoretext.setPosition(42, 980);
	scoretext.setCharacterSize(40);

	//gameover
	gameovertext.setFont(font);
	gameovertext.setString("GAMEOVER!");
	gameovertext.setPosition(640, 500);
	gameovertext.setCharacterSize(50);

	//score
	score_is.setFont(font);
	score_is.setPosition(64, 64);


	//exit
	returnmenu.setFont(font);
	returnmenu.setString("Press  Enter  to  return  to  Main  Menu  or  ESC   to   Exit");
	returnmenu.setPosition(380, 970);


	//audio
	SoundBuffer menuBuff, ingameBuff, gameoverBuff, explosionBuff, shootBuff, loseBuff, enemyshootBuff, launchBuff, gettingshotBuff;
	menuBuff.loadFromFile("menu.wav");
	ingameBuff.loadFromFile("slow-travel.wav");
	gameoverBuff.loadFromFile("gameover.wav");
	explosionBuff.loadFromFile("explosion.wav");
	shootBuff.loadFromFile("shoot.wav");
	loseBuff.loadFromFile("lose.wav");
	enemyshootBuff.loadFromFile("enemyshoot.wav");
	launchBuff.loadFromFile("launch.wav");
	gettingshotBuff.loadFromFile("gettingshot.wav");

	Sound menu(menuBuff), ingame(ingameBuff), gameoverS(gameoverBuff), explosion(explosionBuff), shootS(shootBuff), loseS(loseBuff), enemyshoot(enemyshootBuff),
		launch(launchBuff), gettingshot(gettingshotBuff);
	menu.setVolume(60);
	menu.setLoop(true);
	ingame.setVolume(60);
	ingame.setLoop(true);
	gameoverS.setVolume(60);
	gameoverS.setLoop(true);
	explosion.setVolume(60);
	shootS.setVolume(40);
	loseS.setVolume(60);
	enemyshoot.setVolume(30);
	launch.setVolume(35);
	gettingshot.setVolume(70);

	bool menuplaying = 0, ingameplaying = 0, gameoverplaying = 0;

	//variables and boolians
	int i = 0, j = 0, k = 0, m = 0;
	bool paused = 0, right = 0, left = 0, up = 0, down = 0, shoot = 0, switchsides = 0, rowdead = 1, move_switch = 1;
	bool mainmenu = 1, maingame = 0, transition = 0, new_round = 0, gameover = 1, escc = 1, cheat = 0;
	while (window.isOpen()) {
		while (escc) {
			gameClock.restart();
			if (!gameover) {     //reseting variables
				i = 0, j = 0, k = 0, m = 0;
				paused = 0, right = 0, left = 0, up = 0, down = 0, shoot = 0, switchsides = 0, rowdead = 1, move_switch = 1;
				mainmenu = 1, maingame = 0, transition = 0, new_round = 0, gameover = 1, escc = 1;
				score = 0; hp = 100; powerup = 0; hp_percent = 1; row_count = 2; type1 = 30, type2 = -5; type3 = -5;
				bullets_amount = 710; round = 0; waittime = 80;
				bullets.clear(); enemies.clear(); exploding.clear(); hits.clear();	enemybullets.clear();
				newround.setString("Round 1");
				bg.setPosition(311, 0);
				bgg.setTexture(bggTex);
				bgg.setPosition(0, 0);
				//healthbar
				health_bar.setFillColor(Color(0, 150, 0, 200));
				//spaceship sprite
				spaceShip.setTexture(spaceShipTex);
				spaceShip.setTextureRect(IntRect(0, 0, 48, 48));
				spaceShip.setOrigin(48 / 2, 48 / 2);
				spaceShip.setPosition(760, 960);
				//engine effect sprite
				engineeffect.setTexture(idleTex);
				engineeffect.setTextureRect(IntRect(0, 0, 48, 48));
				engineeffect.setOrigin(48 / 2, 48 / 2);
				engineeffect.setPosition(760, 960);
				//engine sprite
				engine.setTexture(engineTex);
				engine.setTextureRect(IntRect(0, 0, 48, 48));
				engine.setOrigin(48 / 2, 48 / 2);
				engine.setPosition(760, 960);
				//weapon sprite
				weapon.setTexture(weaponTex);
				weapon.setTextureRect(IntRect(0, 0, 48, 48));
				weapon.setOrigin(48 / 2, 48 / 2);
				weapon.setPosition(760, 960);
				//powerup weapon sprite
				extraweapon.setTexture(extraweaponTex);
				extraweapon.setTextureRect(IntRect(0, 0, 48, 48));
				extraweapon.setOrigin(48 / 2, 48 / 2);
				extraweapon.setPosition(760, 960);
				// bullet sprite
				bulletsprite.setTexture(bulletTex);
				bulletsprite.setTextureRect(IntRect(12, 9, 20, 26));
				bulletsprite.setOrigin(32 / 2, 32 / 2);
				//enemie sprite
				enemysprite.setTexture(enemy1Tex);
				enemysprite.setTextureRect(IntRect(0, 0, 64, 64));
				enemysprite.setOrigin(64 / 2, 64 / 2);
				//enemy effect
				enemyspriteeffect.setTexture(enemy1effectTex);
				enemyspriteeffect.setTextureRect(IntRect(0, 0, 8, 8));
				enemyspriteeffect.setOrigin(8 / 2, 8 / 2);
				//explotions
				explotion.setTexture(explotionTex);
				explotion.setTextureRect(IntRect(0, 0, 64, 64));
				explotion.setOrigin(64 / 2, 64 / 2);
				//hits
				hit.setTexture(hitTex);
				hit.setTextureRect(IntRect(0, 0, 133, 133));
				hit.setOrigin(133 / 2, 133 / 2);
				// enemy bullet sprite
				enemybullet.setTexture(enemy1bulletTex);
				enemybullet.setTextureRect(IntRect(0, 0, 8, 8));
				enemybullet.setOrigin(8 / 2, 8 / 2);
			}
			while (mainmenu) {
				if (!menuplaying) {
					menu.play(); menuplaying = 1;
				}
				//pollEvents
				while (window.pollEvent(event)) {
					switch (event.type) {
						//close window
					case Event::Closed:
						menu.stop();
						window.close(); break;
					case Event::KeyPressed:
						//startgame 
						if (event.key.code == Keyboard::Enter) {
							transition = 1, mainmenu = 0, menuplaying = 0, menu.stop();
							break;
						}
					}
				}
				window.clear(Color::Black);
				window.draw(bgg);
				window.draw(start);
				window.draw(title);
				window.display();
			}

			while (transition) {
				if (!ingameplaying) {
					ingame.play(); ingameplaying = 1;
				}
				while (window.pollEvent(event)) {
					switch (event.type) {
						//close window
					case Event::Closed:
						ingame.stop();
						window.close(); break;
					case Event::KeyPressed:
						if (event.key.code == Keyboard::Enter)
							waittime = 0;
						break;
					}
				}
				if (waittime) waittime--;
				else
				{
					maingame = 1; transition = 0; ingameplaying = 0;
				}
				window.clear(Color::Black);
				window.draw(bgg);
				window.draw(blackbg);
				window.draw(newround);
				window.display();
			}

			while (maingame && hp > 0) {
				//pollEvents
				while (window.pollEvent(event)) {
					switch (event.type) {
						//close window
					case Event::Closed:
					{
						ingame.stop();
						window.close(); break;
					}
					case Event::KeyPressed:
						//pause/unpause 
						if (event.key.code == Keyboard::Escape)
						{
							if (!paused) paused = 1;
							else paused = 0;
							break;
						}
						//skip round
						if (event.key.code == Keyboard::P)
						{
							cheat = 1;
							enemies.clear();
							break;
						}
					}
				}
				//gameloop
				if (!paused) {
					srand(time(0));
					seed += rand();
					if (enemies.size() == 0 && pu < 0 && !cheat) {
						seed += rand();
						srand(seed);
						enemy_health += 1;
						if (round % 3 == 0) { enemy_damage += 2; enemybullet_speed += 2; }
						round++, type2 += 4, type3 += 2; new_round = 0; if (bullets_amount > 200) bullets_amount -= 10;
						newround.setString("Round " + to_string(round + 1));
						if (round == 5) row_count++;
						else if (round == 10) row_count++;
						int row_type, current_count = row_count;
						while (current_count--) {
							int random = rand();
							random %= 30;
							if (type3 >= random)
								row_type = 2;
							else if (type2 >= random)
								row_type = 1;
							else
								row_type = 0;
							enemies.push_back({ enemy_health, (enemy_damage * (row_type + 1)), row_type });
						}
					}
					else if (cheat) { cheat = 0; pu += delay * 25; }
					else if (enemies.size() == 0) { pu -= frameTime; new_round = 1; }
					//main spaceship state (J++ --> more damaged state texture {1 -->4})
					j = -1 * (((hp - 1) / 25) - 3);
					spaceShip.setTextureRect(IntRect(((j) * 48), 0, 48, 48));

					hp_percent = hp / 100.0;
					Vector2f bar(1520 * hp_percent, 32);
					health_bar.setSize(bar);
					if (hp < 10) health_bar.setFillColor(Color(150, 0, 0, 200));
					else if (hp < 25)	health_bar.setFillColor(Color(150, 75, 0, 200));
					else if (hp < 50)	health_bar.setFillColor(Color(130, 130, 0, 200));
					else if (hp < 75)	health_bar.setFillColor(Color(70, 140, 0, 200));
					else 	health_bar.setFillColor(Color(0, 150, 0, 200));


					//engine effect + weapon shooting animation
					if (timer <= 0) {
						i++;
						i = i % 4;
						if (Keyboard::isKeyPressed(Keyboard::Space)) {
							weapon.setTextureRect(IntRect(((i) * 48), 0, 48, 48));
							if (powerup) extraweapon.setTextureRect(IntRect(((i) * 48), 0, 48, 48));
						}
						engineeffect.setTextureRect(IntRect(((i) * 48), 0, 48, 48));
						timer = delay;
					}
					else
						timer -= frameTime;
					//reset velocity
					velocity.x = 0, velocity.y = 0;
					//movement
					if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
						if (spaceShip.getPosition().x < 1484)
							velocity.x = 100 * frameTime;
						right = 1;
					}
					if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {
						if (spaceShip.getPosition().x > 36)
							velocity.x = -100 * frameTime;
						left = 1;
					}
					if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) {
						if (spaceShip.getPosition().y > 36)
							velocity.y = -100 * frameTime;
						engineeffect.setTexture(frontTex);
						up = 1;
					}
					if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) {
						if (spaceShip.getPosition().y < 1012)
							velocity.y = 100 * frameTime;
						engineeffect.setTexture(backTex);
						down = 1;
					}
					//shooting
					if (Keyboard::isKeyPressed(Keyboard::Space)) {
						if (reload == 0) {
							launch.play();
							short a = spaceShip.getPosition().x + 26, a2 = spaceShip.getPosition().x, b = spaceShip.getPosition().y - 28;
							if (switchsides) { a += 16; switchsides = 0; }
							else { a -= 16; switchsides = 1; }
							bullets.push_back({ a,b, player_damage, 1 });
							reload += reload_time;
							if (powerup) {
								if (reloadcanon == 0) {
									b -= 24;
									bullets.push_back({ a2,b, player_damage, 0 });
									reloadcanon += reload_time * 4;
								}
							}
						}
						shoot = 1;
					}
					if (reload) { reload--; reloadcanon--; }
					//opposite directions cancel movement
					if (right && left)
						velocity.x = 0;
					if (up && down)
						velocity.y = 0;
					//update score text
					scoretext.setString("Score  " + to_string(score) + "!");

					//idle engine effect animation
					if (!up && !down)
						engineeffect.setTexture(idleTex);
					if (!shoot) weapon.setTextureRect(IntRect(0, 0, 48, 48));
					//reset boolians
					right = 0, left = 0, up = 0, down = 0, shoot = 0;
					//body movements
					spaceShip.move(velocity), engine.move(velocity), engineeffect.move(velocity), weapon.move(velocity), extraweapon.move(velocity);
				}
				//drawing
				window.clear(Color::Black);
				window.draw(bgg);
				if (hp) {
					//bullets vector drawing
					if (!paused) {
						for (int l = 0; l < bullets.size(); l++) {
							bulletsprite.setPosition(bullets[l].x, bullets[l].y);
							//bullets movement
							if (bullets[l].type) {
								bulletsprite.setTexture(bulletTex);
								bullets[l].y -= bullet_speed;
							}
							else {
								bulletsprite.setTexture(canonballzTex);
								bullets[l].y -= bullet_speed / 2;
							}
							window.draw(bulletsprite);
							m++;
							m %= 3;
							bulletsprite.setTextureRect(IntRect(((m * 32) + 12), 9, 20, 26));
							if (bullets[l].y < -1080) bullets.pop_front();
						}
						for (int l = 0; l < enemybullets.size(); l++) {
							enemybullet.setPosition(enemybullets[l].x, enemybullets[l].y + 64);
							//bullets movement
							if (enemybullets[l].type == 0) {
								enemybullet.setTexture(enemy1bulletTex);
								enemybullets[l].y += enemybullet_speed / 2;
							}
							else if (enemybullets[l].type == 1) {
								enemybullet.setTexture(enemy2bulletTex);
								enemybullets[l].y += enemybullet_speed;
							}
							else {
								enemybullet.setTexture(enemy3bulletTex);
								enemybullets[l].y += enemybullet_speed * 2;
							}
							if (enemybullet.getGlobalBounds().intersects(spaceShip.getGlobalBounds())) {
								gettingshot.play();
								int tx = enemybullets[l].x, ty = enemybullets[l].y + 64;
								hits.push_back({ tx,ty });
								hp -= enemybullets[l].damage;
								enemybullets[l].y = 1400;
							}
							window.draw(enemybullet);
							mn++;
							mn %= 8;
							enemybullet.setTextureRect(IntRect((mn * 8), 0, 8, 8)); // intialize
							if (enemybullets[l].y > 2180) enemybullets.pop_front();
						}
					}
					for (int l = 0; l < enemies.size(); l++) {
						for (int p = 0; p < bullets.size(); p++) {
							bulletsprite.setPosition(bullets[p].x, bullets[p].y);
							enemysprite.setPosition(1 * 128 + move, (l + 1) * 128);
							if (enemysprite.getGlobalBounds().intersects(bulletsprite.getGlobalBounds()) && enemies[l].hp1 > 0) {
								int ix = bulletsprite.getPosition().x, iy = bulletsprite.getPosition().y - 64;
								hits.push_back({ ix,iy });
								enemies[l].hp1 -= bullets[p].damage;
								bullets[p].y = -50;
								score += 116;
								shootS.play();
								if (enemies[l].hp1 <= 0) {
									int jx = enemysprite.getPosition().x, jy = enemysprite.getPosition().y;
									exploding.push_back({ jx,jy });
									score += 547 * (enemies[l].type + 1);
									explosion.play();
								}
							}
							enemysprite.setPosition(2 * 128 + move, (l + 1) * 128);
							if (enemysprite.getGlobalBounds().intersects(bulletsprite.getGlobalBounds()) && enemies[l].hp2 > 0) {
								int ix = bulletsprite.getPosition().x, iy = bulletsprite.getPosition().y - 64;
								hits.push_back({ ix,iy });
								enemies[l].hp2 -= bullets[p].damage;
								bullets[p].y = -50;
								score += 116;
								shootS.play();
								if (enemies[l].hp2 <= 0) {
									int jx = enemysprite.getPosition().x, jy = enemysprite.getPosition().y;
									exploding.push_back({ jx,jy });
									score += 547 * (enemies[l].type + 1);
									explosion.play();
								}
							}
							enemysprite.setPosition(3 * 128 + move, (l + 1) * 128);
							if (enemysprite.getGlobalBounds().intersects(bulletsprite.getGlobalBounds()) && enemies[l].hp3 > 0) {
								int ix = bulletsprite.getPosition().x, iy = bulletsprite.getPosition().y - 64;
								hits.push_back({ ix,iy });
								enemies[l].hp3 -= bullets[p].damage;
								bullets[p].y = -50;
								score += 116;
								shootS.play();
								if (enemies[l].hp3 <= 0) {
									int jx = enemysprite.getPosition().x, jy = enemysprite.getPosition().y;
									exploding.push_back({ jx,jy });
									score += 547 * (enemies[l].type + 1);
									explosion.play();
								}
							}
							enemysprite.setPosition(4 * 128 + move, (l + 1) * 128);
							if (enemysprite.getGlobalBounds().intersects(bulletsprite.getGlobalBounds()) && enemies[l].hp4 > 0) {
								int ix = bulletsprite.getPosition().x, iy = bulletsprite.getPosition().y - 64;
								hits.push_back({ ix,iy });
								enemies[l].hp4 -= bullets[p].damage;
								bullets[p].y = -50;
								score += 116;
								shootS.play();
								if (enemies[l].hp4 <= 0) {
									int jx = enemysprite.getPosition().x, jy = enemysprite.getPosition().y;
									exploding.push_back({ jx,jy });
									score += 547 * (enemies[l].type + 1);
									explosion.play();
								}
							}
							enemysprite.setPosition(5 * 128 + move, (l + 1) * 128);
							if (enemysprite.getGlobalBounds().intersects(bulletsprite.getGlobalBounds()) && enemies[l].hp5 > 0) {
								int ix = bulletsprite.getPosition().x, iy = bulletsprite.getPosition().y - 64;
								hits.push_back({ ix,iy });
								enemies[l].hp5 -= bullets[p].damage;
								bullets[p].y = -50;
								score += 116;
								shootS.play();
								if (enemies[l].hp5 <= 0) {
									int jx = enemysprite.getPosition().x, jy = enemysprite.getPosition().y;
									exploding.push_back({ jx,jy });
									score += 547 * (enemies[l].type + 1);
									explosion.play();
								}
							}
							enemysprite.setPosition(6 * 128 + move, (l + 1) * 128);
							if (enemysprite.getGlobalBounds().intersects(bulletsprite.getGlobalBounds()) && enemies[l].hp6 > 0) {
								int ix = bulletsprite.getPosition().x, iy = bulletsprite.getPosition().y - 64;
								hits.push_back({ ix,iy });
								enemies[l].hp6 -= bullets[p].damage;
								bullets[p].y = -50;
								score += 116;
								shootS.play();
								if (enemies[l].hp6 <= 0) {
									int jx = enemysprite.getPosition().x, jy = enemysprite.getPosition().y;
									exploding.push_back({ jx,jy });
									score += 547 * (enemies[l].type + 1);
									explosion.play();
								}
							}
							enemysprite.setPosition(7 * 128 + move, (l + 1) * 128);
							if (enemysprite.getGlobalBounds().intersects(bulletsprite.getGlobalBounds()) && enemies[l].hp7 > 0) {
								int ix = bulletsprite.getPosition().x, iy = bulletsprite.getPosition().y - 64;
								hits.push_back({ ix,iy });
								enemies[l].hp7 -= bullets[p].damage;
								bullets[p].y = -50;
								score += 116;
								shootS.play();
								if (enemies[l].hp7 <= 0) {
									int jx = enemysprite.getPosition().x, jy = enemysprite.getPosition().y;
									exploding.push_back({ jx,jy });
									score += 547 * (enemies[l].type + 1);
									explosion.play();
								}
							}
							enemysprite.setPosition(8 * 128 + move, (l + 1) * 128);
							if (enemysprite.getGlobalBounds().intersects(bulletsprite.getGlobalBounds()) && enemies[l].hp8 > 0) {
								int ix = bulletsprite.getPosition().x, iy = bulletsprite.getPosition().y - 64;
								hits.push_back({ ix,iy });
								enemies[l].hp8 -= bullets[p].damage;
								bullets[p].y = -50;
								score += 116;
								shootS.play();
								if (enemies[l].hp8 <= 0) {
									int jx = enemysprite.getPosition().x, jy = enemysprite.getPosition().y;
									exploding.push_back({ jx,jy });
									score += 547 * (enemies[l].type + 1);
									explosion.play();
								}
							}
							enemysprite.setPosition(9 * 128 + move, (l + 1) * 128);
							if (enemysprite.getGlobalBounds().intersects(bulletsprite.getGlobalBounds()) && enemies[l].hp9 > 0) {
								int ix = bulletsprite.getPosition().x, iy = bulletsprite.getPosition().y - 64;
								hits.push_back({ ix,iy });
								enemies[l].hp9 -= bullets[p].damage;
								bullets[p].y = -50;
								score += 116;
								shootS.play();
								if (enemies[l].hp9 <= 0) {
									int jx = enemysprite.getPosition().x, jy = enemysprite.getPosition().y;
									exploding.push_back({ jx,jy });
									score += 547 * (enemies[l].type + 1);
									explosion.play();
								}
							}
							enemysprite.setPosition(10 * 128 + move, (l + 1) * 128);
							if (enemysprite.getGlobalBounds().intersects(bulletsprite.getGlobalBounds()) && enemies[l].hp10 > 0) {
								int ix = bulletsprite.getPosition().x, iy = bulletsprite.getPosition().y - 64;
								hits.push_back({ ix,iy });
								enemies[l].hp10 -= bullets[p].damage;
								bullets[p].y = -50;
								score += 116;
								shootS.play();
								if (enemies[l].hp10 <= 0) {
									int jx = enemysprite.getPosition().x, jy = enemysprite.getPosition().y;
									exploding.push_back({ jx,jy });
									score += 547 * (enemies[l].type + 1);
									explosion.play();
								}
							}
						}
					}
				}
				//enemies drawing
				if (!paused) {
					if (move_switch) {
						move += move_speed;
						if (move > 120) { move_switch = 0; }
					}
					else {
						move -= move_speed;
						if (move < 0) { move_switch = 1; }
					}
					for (int l = 0; l < enemies.size(); l++) {
						seed += rand();
						srand(seed);
						int rowdead = 1, random = rand(); random %= bullets_amount;
						if (enemies[l].type == 0) {
							enemysprite.setTexture(enemy1Tex);
							enemysprite.setTextureRect(IntRect(0, 0, 64, 64));
							enemysprite.setOrigin(64 / 2, 64 / 2);
							enemysprite.setScale(2, 2);
							enemyspriteeffect.setTexture(enemy1effectTex);
							enemyspriteeffect.setTextureRect(IntRect(0, 0, 64, 64));
							enemyspriteeffect.setOrigin(64 / 2, 64 / 2);
							enemyspriteeffect.setTextureRect(IntRect((i * 64), 0, 64, 64));
							enemyspriteeffect.setScale(2, 2);
						}
						else if (enemies[l].type == 1) {
							enemysprite.setTexture(enemy2Tex);
							enemysprite.setTextureRect(IntRect(0, 0, 128, 128));
							enemysprite.setOrigin(128 / 2, 128 / 2);
							enemysprite.setScale(1.3, 1.3);
							enemyspriteeffect.setTexture(enemy2effectTex);
							enemyspriteeffect.setTextureRect(IntRect(0, 0, 128, 128));
							enemyspriteeffect.setOrigin(128 / 2, 128 / 2);
							enemyspriteeffect.setTextureRect(IntRect((i * 2 * 128), 0, 128, 128));
							enemyspriteeffect.setScale(1.3, 1.3);
						}
						else {
							enemysprite.setTexture(enemy3Tex);
							enemysprite.setTextureRect(IntRect(0, 0, 128, 128));
							enemysprite.setOrigin(128 / 2, 128 / 2);
							enemysprite.setScale(1.3, 1.3);
							enemyspriteeffect.setTexture(enemy3effectTex);
							enemyspriteeffect.setTextureRect(IntRect(0, 0, 128, 128));
							enemyspriteeffect.setOrigin(128 / 2, 128 / 2);
							enemyspriteeffect.setTextureRect(IntRect((i * 2 * 128), 0, 128, 128));
							enemyspriteeffect.setScale(1.3, 1.3);
						}
						if (enemies[l].hp1 > 0)
						{
							enemysprite.setPosition(1 * 128 + move, (l + 1) * 128);
							enemyspriteeffect.setPosition(1 * 128 + move, (l + 1) * 128);
							window.draw(enemyspriteeffect);
							window.draw(enemysprite);
							rowdead = 0;
							if (random == 41) {
								enemyshoot.play();
								int fx = 1 * 128 + move, fy = (l + 1) * 128;
								enemybullets.push_back({ fx,fy,enemies[l].damage,enemies[l].type });
							}
						}
						if (enemies[l].hp2 > 0)
						{
							enemysprite.setPosition(2 * 128 + move, (l + 1) * 128);
							enemyspriteeffect.setPosition(2 * 128 + move, (l + 1) * 128);
							window.draw(enemyspriteeffect);
							window.draw(enemysprite);
							rowdead = 0;
							if (random == 24) {
								enemyshoot.play();
								int fx = 2 * 128 + move, fy = (l + 1) * 128;
								enemybullets.push_back({ fx,fy,enemies[l].damage ,enemies[l].type });
							}
						}
						if (enemies[l].hp3 > 0)
						{
							enemysprite.setPosition(3 * 128 + move, (l + 1) * 128);
							enemyspriteeffect.setPosition(3 * 128 + move, (l + 1) * 128);
							window.draw(enemyspriteeffect);
							window.draw(enemysprite);
							rowdead = 0;
							if (random == 33) {
								enemyshoot.play();
								int fx = 3 * 128 + move, fy = (l + 1) * 128;
								enemybullets.push_back({ fx,fy,enemies[l].damage,enemies[l].type });
							}
						}
						if (enemies[l].hp4 > 0)
						{
							enemysprite.setPosition(4 * 128 + move, (l + 1) * 128);
							enemyspriteeffect.setPosition(4 * 128 + move, (l + 1) * 128);
							window.draw(enemyspriteeffect);
							window.draw(enemysprite);
							rowdead = 0;
							if (random == 48) {
								enemyshoot.play();
								int fx = 4 * 128 + move, fy = (l + 1) * 128;
								enemybullets.push_back({ fx,fy,enemies[l].damage,enemies[l].type });
							}
						}
						if (enemies[l].hp5 > 0)
						{
							enemysprite.setPosition(5 * 128 + move, (l + 1) * 128);
							enemyspriteeffect.setPosition(5 * 128 + move, (l + 1) * 128);
							window.draw(enemyspriteeffect);
							window.draw(enemysprite);
							rowdead = 0;
							if (random == 65) {
								enemyshoot.play();
								int fx = 5 * 128 + move, fy = (l + 1) * 128;
								enemybullets.push_back({ fx,fy,enemies[l].damage,enemies[l].type });
							}
						}
						if (enemies[l].hp6 > 0)
						{
							enemysprite.setPosition(6 * 128 + move, (l + 1) * 128);
							enemyspriteeffect.setPosition(6 * 128 + move, (l + 1) * 128);
							window.draw(enemyspriteeffect);
							window.draw(enemysprite);
							rowdead = 0;
							if (random == 67) {
								enemyshoot.play();
								int fx = 6 * 128 + move, fy = (l + 1) * 128;
								enemybullets.push_back({ fx,fy,enemies[l].damage,enemies[l].type });
							}
						}
						if (enemies[l].hp7 > 0)
						{
							enemysprite.setPosition(7 * 128 + move, (l + 1) * 128);
							enemyspriteeffect.setPosition(7 * 128 + move, (l + 1) * 128);
							window.draw(enemyspriteeffect);
							window.draw(enemysprite);
							rowdead = 0;
							if (random == 71) {
								enemyshoot.play();
								int fx = 7 * 128 + move, fy = (l + 1) * 128;
								enemybullets.push_back({ fx,fy,enemies[l].damage,enemies[l].type });
							}
						}
						if (enemies[l].hp8 > 0)
						{
							enemysprite.setPosition(8 * 128 + move, (l + 1) * 128);
							enemyspriteeffect.setPosition(8 * 128 + move, (l + 1) * 128);
							window.draw(enemyspriteeffect);
							window.draw(enemysprite);
							rowdead = 0;
							if (random == 89) {
								enemyshoot.play();
								int fx = 8 * 128 + move, fy = (l + 1) * 128;
								enemybullets.push_back({ fx,fy,enemies[l].damage,enemies[l].type });
							}
						}
						if (enemies[l].hp9 > 0)
						{
							enemysprite.setPosition(9 * 128 + move, (l + 1) * 128);
							enemyspriteeffect.setPosition(9 * 128 + move, (l + 1) * 128);
							window.draw(enemyspriteeffect);
							window.draw(enemysprite);
							rowdead = 0;
							if (random == 99) {
								enemyshoot.play();
								int fx = 9 * 128 + move, fy = (l + 1) * 128;
								enemybullets.push_back({ fx,fy,enemies[l].damage,enemies[l].type });
							}
						}
						if (enemies[l].hp10 > 0)
						{
							enemysprite.setPosition(10 * 128 + move, (l + 1) * 128);
							enemyspriteeffect.setPosition(10 * 128 + move, (l + 1) * 128);
							window.draw(enemyspriteeffect);
							window.draw(enemysprite);
							rowdead = 0;
							if (random == 70) {
								enemyshoot.play();
								int fx = 10 * 128 + move, fy = (l + 1) * 128;
								enemybullets.push_back({ fx,fy,enemies[l].damage,enemies[l].type });
							}
						}
						if (rowdead) { enemies.pop_back(); }
						if (enemies.size() == 0) pu = delay * 25;
					}
					for (int l = 0; l < enemies.size(); l++) {
						enemysprite.setPosition(1 * 128 + move, (l + 1) * 128);
						if (enemysprite.getGlobalBounds().intersects(spaceShip.getGlobalBounds()) && enemies[l].hp1 > 0)
						{
							hp -= 2; gettingshot.play();
						}
						enemysprite.setPosition(2 * 128 + move, (l + 1) * 128);
						if (enemysprite.getGlobalBounds().intersects(spaceShip.getGlobalBounds()) && enemies[l].hp2 > 0)
						{
							hp -= 2; gettingshot.play();
						}
						enemysprite.setPosition(3 * 128 + move, (l + 1) * 128);
						if (enemysprite.getGlobalBounds().intersects(spaceShip.getGlobalBounds()) && enemies[l].hp3 > 0)
						{
							hp -= 2; gettingshot.play();
						}
						enemysprite.setPosition(4 * 128 + move, (l + 1) * 128);
						if (enemysprite.getGlobalBounds().intersects(spaceShip.getGlobalBounds()) && enemies[l].hp4 > 0)
						{
							hp -= 2; gettingshot.play();
						}
						enemysprite.setPosition(5 * 128 + move, (l + 1) * 128);
						if (enemysprite.getGlobalBounds().intersects(spaceShip.getGlobalBounds()) && enemies[l].hp5 > 0)
						{
							hp -= 2; gettingshot.play();
						}						enemysprite.setPosition(6 * 128 + move, (l + 1) * 128);
						if (enemysprite.getGlobalBounds().intersects(spaceShip.getGlobalBounds()) && enemies[l].hp6 > 0)
						{
							hp -= 2; gettingshot.play();
						}
						enemysprite.setPosition(7 * 128 + move, (l + 1) * 128);
						if (enemysprite.getGlobalBounds().intersects(spaceShip.getGlobalBounds()) && enemies[l].hp7 > 0)
						{
							hp -= 2; gettingshot.play();
						}
						enemysprite.setPosition(8 * 128 + move, (l + 1) * 128);
						if (enemysprite.getGlobalBounds().intersects(spaceShip.getGlobalBounds()) && enemies[l].hp8 > 0)
						{
							hp -= 2; gettingshot.play();
						}
						enemysprite.setPosition(9 * 128 + move, (l + 1) * 128);
						if (enemysprite.getGlobalBounds().intersects(spaceShip.getGlobalBounds()) && enemies[l].hp9 > 0)
						{
							hp -= 2; gettingshot.play();
						}
						enemysprite.setPosition(10 * 128 + move, (l + 1) * 128);
						if (enemysprite.getGlobalBounds().intersects(spaceShip.getGlobalBounds()) && enemies[l].hp10 > 0)
						{
							hp -= 2; gettingshot.play();
						}
					}
				}
				window.draw(scoretext);
				window.draw(spaceShip);
				window.draw(engine);
				window.draw(weapon);
				if (powerup) window.draw(extraweapon);
				window.draw(engineeffect);
				if (!paused) {
					for (int l = 0; l < hits.size(); l++) {
						hit.setPosition(hits[l].x, hits[l].y);
						hit.setTextureRect(IntRect((hits[l].c * 133), 0, 133, 133));
						hits[l].c++;
						if (hits[l].c > 44) hits.pop_front();
						window.draw(hit);
					}
					for (int l = 0; l < exploding.size(); l++) {
						explotion.setPosition(exploding[l].x, exploding[l].y);
						explotion.setTextureRect(IntRect((exploding[l].c * 64), 0, 64, 64));
						exploding[l].c++;
						if (exploding[l].c > 44) exploding.pop_front();
						window.draw(explotion);
					}
				}
				if (new_round) window.draw(newround);
				if (paused) { window.draw(pause); window.draw(esc); } //paused text
				window.draw(health_bar);
				window.display();
			}
			while (gameover) {
				if (hp <= 0) {
					loseS.play();
					ingameplaying = 0;
					ingame.stop();
					hp = 100;
				}
				if (!gameoverplaying) {
					gameoverS.play(); gameoverplaying = 1;
				}
				while (window.pollEvent(event)) {
					switch (event.type) {
						//close window
					case Event::Closed: {
						gameoverS.stop();
						window.close(); break;
					}
					case Event::KeyPressed:
						if (event.key.code == Keyboard::Enter)
						{
							gameoverS.stop(); gameoverplaying = 0;
							maingame = 1; gameover = 0;
							break;
						}
						if (event.key.code == Keyboard::Escape)
						{
							gameoverS.stop(); gameoverplaying = 0;
							escc = 0; gameover = 0; window.close(); break;
							break;
						}
					}
				}
				score_is.setString("Your  score  is  " + to_string(score) + " !");
				window.clear(Color::Black);
				window.draw(bgg);
				window.draw(gameovertext);
				window.draw(score_is);
				window.draw(returnmenu);
				window.display();
			}
		}
	}
	return 0;
}