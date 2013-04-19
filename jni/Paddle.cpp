#include "Paddle.hpp"

#include <osg/BlendFunc>
#include <osg/Material>
#include <osg/Shape>
#include <osg/ShapeDrawable>

class PaddleCallback : public::osg::NodeCallback
{
public:
	virtual void operator()(osg::Node * node, osg::NodeVisitor * nv)
	{
		if(nv->getVisitorType() == osg::NodeVisitor::UPDATE_VISITOR)
		{
			test::Paddle * paddle = static_cast<test::Paddle*>(node);
			paddle->update();
		}
	}
};

const osg::Vec3d test::Paddle::OFFSET = osg::Vec3d(0, 1, 0);

test::Paddle::Paddle() :
		HasUpdate(false)
{
	osg::Box *box = new osg::Box(osg::Vec3(0, 0, 0), (1.0/12.0)*6.0, (1.0/12.0)*8.0, (1.0/12.0)*1.0);
	osg::ShapeDrawable *sd = new osg::ShapeDrawable(box);
	Geode = new osg::Geode();
	Geode->addDrawable(sd);
	osg::Vec3d pos(0,0,0);
	Trans = new osg::PositionAttitudeTransform;
	Trans->setPosition(pos);
	//Trans->setAttitude(osg::Quat(osg::DegreesToRadians(-20.0), osg::Vec3d(1.0, 0.0, 0.0)));
	Trans->addChild(Geode);
	this->addChild(Trans);

	sd->setColor(osg::Vec4d(.3, .3, .3, .5));
	osg::StateSet* state = sd->getOrCreateStateSet();
	state->setMode(GL_BLEND,
			osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
	osg::Material* mat = new osg::Material;
	mat->setColorMode(osg::Material::AMBIENT_AND_DIFFUSE);
	mat->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4d(.3, .3, .3, .5));
	mat->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4d(0, 0, 0, .5));
	mat->setEmission(osg::Material::FRONT_AND_BACK, osg::Vec4d(.3, .3, .3, .5));
	mat->setAlpha(osg::Material::FRONT_AND_BACK, .5);
	state->setAttributeAndModes(mat,
			osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);

	osg::BlendFunc* bf = new osg::BlendFunc(osg::BlendFunc::SRC_ALPHA,
			osg::BlendFunc::ONE_MINUS_SRC_ALPHA);
	state->setAttributeAndModes(bf);

	state->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
	state->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	sd->setStateSet(state);

	this->setUpdateCallback(new PaddleCallback);
}

void test::Paddle::setPosition(osg::Vec3d const& pos)
{
	NewPosition = (pos + OFFSET);
	HasUpdate = true;
}

void test::Paddle::setRotation(double rotation)
{
	Rotation = rotation;
	HasUpdate = true;
}

void test::Paddle::update()
{
	if(HasUpdate)
	{
		osg::Vec3d prevPos = Trans->getPosition();
		osg::BoundingBox bb = this->getBoundingBox();
		Trans->setPosition(NewPosition);
		Trans->setAttitude(osg::Quat(Rotation, osg::Vec3d(0, 0, 1)));
		HasUpdate = false;

		bb.expandBy(this->getBoundingBox());
		firePaddleMoved(prevPos, NewPosition);
	}
}

void test::Paddle::firePaddleMoved(osg::Vec3d const& prevPos, osg::Vec3d const& currPos)
{
	for(PaddleListenerSet::const_iterator it = PaddleListeners.begin(), end = PaddleListeners.end(); it != end; ++it)
	{
		PaddleListener * paddleListener = *it;
		paddleListener->paddleMoved(this, prevPos, currPos);
	}
}
