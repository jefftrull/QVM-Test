// QVM Adapter for Ogre3D Vector3, Quaternion, and Matrix4 classes
// Jeff Trull <jetrull@sbcglobal.net> 2011-05-17 
#include <OgreVector3.h>
#include <OgreQuaternion.h>
#include <OgreMatrix4.h>

#include <boost/qvm/v_traits.hpp>
#include <boost/qvm/q_traits.hpp>
#include <boost/qvm/m_traits.hpp>

namespace boost {
  namespace qvm {
    template<> struct v_traits<Ogre::Vector3> {
      static int const dim = 3;
      typedef Ogre::Real scalar_type;

      template <int I> static inline scalar_type & w( Ogre::Vector3 & v );
      template <int I> static inline scalar_type r( Ogre::Vector3 const & v );

      static inline scalar_type & iw( int i, Ogre::Vector3 & v ) { return v[i]; }
      static inline scalar_type ir( int i, Ogre::Vector3 const & v ) { return v[i]; }
    };

    // specialize compile-time constant accesses for speed
    template<> v_traits<Ogre::Vector3>::scalar_type & v_traits<Ogre::Vector3>::w<0>( Ogre::Vector3 & v) { return v.x; }
    template<> v_traits<Ogre::Vector3>::scalar_type & v_traits<Ogre::Vector3>::w<1>( Ogre::Vector3 & v) { return v.y; }
    template<> v_traits<Ogre::Vector3>::scalar_type & v_traits<Ogre::Vector3>::w<2>( Ogre::Vector3 & v) { return v.z; }

    template<> v_traits<Ogre::Vector3>::scalar_type v_traits<Ogre::Vector3>::r<0>( Ogre::Vector3 const & v) { return v.x; }
    template<> v_traits<Ogre::Vector3>::scalar_type v_traits<Ogre::Vector3>::r<1>( Ogre::Vector3 const & v) { return v.y; }
    template<> v_traits<Ogre::Vector3>::scalar_type v_traits<Ogre::Vector3>::r<2>( Ogre::Vector3 const & v) { return v.z; }

    template<> struct q_traits<Ogre::Quaternion> {
      typedef Ogre::Real scalar_type;

      // I think that 0-3 is W, X, Y, Z...
      template <int I> static inline scalar_type & w( Ogre::Quaternion & q );
      template <int I> static inline scalar_type   r( Ogre::Quaternion const & q );
    };

    // specialize for each of W, X, Y, Z (not stored as vector in Ogre)
    template <> q_traits<Ogre::Quaternion>::scalar_type & q_traits<Ogre::Quaternion>::w<0>( Ogre::Quaternion & q ) { return q.w; }
    template <> q_traits<Ogre::Quaternion>::scalar_type & q_traits<Ogre::Quaternion>::w<1>( Ogre::Quaternion & q ) { return q.x; }
    template <> q_traits<Ogre::Quaternion>::scalar_type & q_traits<Ogre::Quaternion>::w<2>( Ogre::Quaternion & q ) { return q.y; }
    template <> q_traits<Ogre::Quaternion>::scalar_type & q_traits<Ogre::Quaternion>::w<3>( Ogre::Quaternion & q ) { return q.z; }

    template <> q_traits<Ogre::Quaternion>::scalar_type q_traits<Ogre::Quaternion>::r<0>( Ogre::Quaternion const & q ) { return q.w; }
    template <> q_traits<Ogre::Quaternion>::scalar_type q_traits<Ogre::Quaternion>::r<1>( Ogre::Quaternion const & q ) { return q.x; }
    template <> q_traits<Ogre::Quaternion>::scalar_type q_traits<Ogre::Quaternion>::r<2>( Ogre::Quaternion const & q ) { return q.y; }
    template <> q_traits<Ogre::Quaternion>::scalar_type q_traits<Ogre::Quaternion>::r<3>( Ogre::Quaternion const & q ) { return q.z; }

    template<> struct m_traits<Ogre::Matrix4> {
      typedef Ogre::Real scalar_type;
      static int const rows = 4;
      static int const cols = 4;

      // Ogre::Matrix4 provides no special named access for individual entries
      template <int Row,int Col> static scalar_type r( Ogre::Matrix4 const & x ) { return x[Row][Col]; }
      template <int Row,int Col> static scalar_type & w( Ogre::Matrix4 & x ) { return x[Row][Col]; }
        
      static scalar_type ir( int row, int col, Ogre::Matrix4 const & x ) { return x[row][col]; }
      static scalar_type & iw( int row, int col, Ogre::Matrix4 & x ) { return x[row][col]; }
    };


  }
}
