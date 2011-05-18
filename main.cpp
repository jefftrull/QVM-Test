#include <iostream>

#include <OgreMatrix4.h>
#include <OgreVector3.h>
#include <OgreQuaternion.h>
#include "AdaptOgreQVM.h"

#include <Math/COLLADABUMathMatrix4.h>
#include <Math/COLLADABUMathVector3.h>
#include <Math/COLLADABUMathQuaternion.h>
#include "AdaptColladaQVM.h"

#include <boost/qvm/v_access.hpp>
#include <boost/qvm/v.hpp>
#include <boost/qvm/sw3.hpp>
#include <boost/qvm/q_access.hpp>
#include <boost/qvm/q.hpp>
#include <boost/qvm/m.hpp>

using boost::qvm::X;
using boost::qvm::Y;
using boost::qvm::Z;
using boost::qvm::mag;
using boost::qvm::make;
using boost::qvm::rotx_q;
using boost::qvm::inverse;

using namespace boost::qvm;

int main(int argc, char **argv) {
  // access elements of vectors from two different libraries identically
  Ogre::Vector3 votest; votest%X = 0.1; votest%Y = 0.2; votest%Z = 0.3;
  COLLADABU::Math::Vector3 vctest; vctest%X = 0.1; vctest%Y = 0.2; vctest%Z = 0.3;
  std::cout << "magnitude of Ogre vector is: " << mag(votest) << std::endl;
  std::cout << "magnitude of Collada vector is: " << mag(vctest) << std::endl;

  // creating compatible vectors is almost as easy as assignment:
  Ogre::Vector3 vcotest(-1, 2, 12);
  COLLADABU::Math::Vector3 vcatest = make<COLLADABU::Math::Vector3>(vcotest);
  std::cout << "Collada vector (" << vcatest.x << ", " << vcatest.y << ", " << vcatest.z << ") ";
  std::cout << " made from Ogre Vector " << vcotest << std::endl;

  // an arbitrary quaternion (this one represents a rotation from "Y-Up" to "Z-Up" coordinates)
  Ogre::Quaternion oorientation = Ogre::Vector3(0, 1, 0).getRotationTo(Ogre::Vector3(0, 0, 1));
  // a scale
  Ogre::Vector3 oscale(1.0, 2.0, 3.0);
  // a translation
  Ogre::Vector3 oxlat(-10.0, 4.0, 2.0);
  // turn into a transformation matrix
  Ogre::Matrix4 otrans; otrans.makeTransform(oxlat, oscale, oorientation);
  std::cout << "Ogre transformation matrix " << otrans << std::endl;

  // now make the same one using some QVM operations on Collada data types
  COLLADABU::Math::Quaternion corientation = rotx_q(3.14159f / 2);
  COLLADABU::Math::Vector3 cscale(1.0, 1.0, 1.0); cscale%Y *= 2.0; cscale%Z *= 3.0;
  COLLADABU::Math::Vector3 cxlat(-10.0, 4.0, 2.0);
  COLLADABU::Math::Matrix4 ctrans; ctrans.makeTransform(cxlat, cscale, corientation);

  // multiply together with one inverted; the result should be close to the identity transform
  // we can't take non-const references of individual elements in a COLLADABU::Math::Matrix4
  // so do this carefully:
  Ogre::Matrix4 ctrans_copy = make<Ogre::Matrix4>(otrans);
  Ogre::Matrix4 result = ctrans_copy * inverse(make<Ogre::Matrix4>(otrans));
  std::cout << "Result matrix (should be near identity) is " << result << std::endl;

  return 0;
}
