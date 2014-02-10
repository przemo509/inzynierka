/*
 * Skybox.h
 *
 *  Created on: 23 sty 2014
 *      Author: Przemo
 */

#ifndef SKYBOX_H_
#define SKYBOX_H_

class Skybox {
public:
	Skybox();
	virtual ~Skybox();
	void draw();

private:
	int worldSize;
	int floorLevel;
	int skyLevel;
	int leftWall;
	int rightWall;
	int frontWall;
	int backWall;
};

#endif /* SKYBOX_H_ */
