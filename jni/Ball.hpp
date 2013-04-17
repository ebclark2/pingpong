#ifndef __BALL_HPP__
#define __BALL_HPP__

#include "Paddle.hpp"

#include <osg/PositionAttitudeTransform>

namespace test
{

enum GameState
{
	SERVE_P1,
	SERVE_P2,
	PLAY_P1,
	PLAY_P2
};

class Ball : public osg::PositionAttitudeTransform
{
public:
	Ball();

	inline void setVelocity(osg::Vec3d const& velocity) { Velocity = velocity; }

	inline void setPaddle1(test::Paddle * paddle1) { Paddle1 = paddle1; }
	inline void setPaddle2(test::Paddle * paddle2) { Paddle2 = paddle2; }

	inline void setState(GameState state) { State = state; }

	virtual void accept(osg::NodeVisitor & visitor);

protected:
	void update();

private:
	osg::Vec3d Velocity;

	osg::ref_ptr<test::Paddle> Paddle1;
	osg::ref_ptr<test::Paddle> Paddle2;

	GameState State;

};

}

#endif
