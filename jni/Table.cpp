#include "Table.hpp"

#include <osg/Material>

test::Table::Table()
{
	//9ft x 5ft table
	//1.0 = 9ft
	//1/9 = 1ft
	//1/9/6 = 2inches
	osg::Box *box = new osg::Box(osg::Vec3(0, 0, 0), 5.0f, 1.0f/6.0f, 9.0f);
	osg::ShapeDrawable *sd = new osg::ShapeDrawable(box);
	sd->setColor(osg::Vec4d(0, .4, 0, 1));
	osg::StateSet* state = sd->getOrCreateStateSet();
	osg::Material* mat = new osg::Material;
	mat->setColorMode(osg::Material::AMBIENT_AND_DIFFUSE);
	mat->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4d(0, .4, 0, 1));
	mat->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4d(0, 0, 0, 1));
	mat->setEmission(osg::Material::FRONT_AND_BACK, osg::Vec4d(0, .4, 0, 1));
	state->setAttributeAndModes(mat,
			osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
	sd->setStateSet(state);
	osg::Geode *geode = new osg::Geode();
	geode->addDrawable(sd);
	osg::Vec3d pos(0,0,0);
	this->addChild(geode);
}
