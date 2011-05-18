// QVM Adapter for OpenCollada Vector3, Quaternion, and Matrix4 classes
// Jeff Trull <jetrull@sbcglobal.net> 2011-05-17 
#include <Math/COLLADABUMathMatrix4.h>
#include <Math/COLLADABUMathVector3.h>
#include <Math/COLLADABUMathQuaternion.h>

#include <boost/qvm/v_traits.hpp>
#include <boost/qvm/q_traits.hpp>
#include <boost/qvm/m_traits.hpp>

namespace boost {
  namespace qvm {
    template<> struct v_traits<COLLADABU::Math::Vector3> {
      static int const dim = 3;
      typedef COLLADABU::Math::Real scalar_type;

      template <int I> static inline scalar_type & w( COLLADABU::Math::Vector3 & v );
      template <int I> static inline scalar_type r( COLLADABU::Math::Vector3 const & v );

      static inline scalar_type & iw( int i, COLLADABU::Math::Vector3 & v ) { return v[i]; }
      static inline scalar_type ir( int i, COLLADABU::Math::Vector3 const & v ) { return v[i]; }
    };

    // specialize compile-time constant accesses for speed
    template<> v_traits<COLLADABU::Math::Vector3>::scalar_type & v_traits<COLLADABU::Math::Vector3>::w<0>( COLLADABU::Math::Vector3 & v) { return v.x; }
    template<> v_traits<COLLADABU::Math::Vector3>::scalar_type & v_traits<COLLADABU::Math::Vector3>::w<1>( COLLADABU::Math::Vector3 & v) { return v.y; }
    template<> v_traits<COLLADABU::Math::Vector3>::scalar_type & v_traits<COLLADABU::Math::Vector3>::w<2>( COLLADABU::Math::Vector3 & v) { return v.z; }

    template<> v_traits<COLLADABU::Math::Vector3>::scalar_type v_traits<COLLADABU::Math::Vector3>::r<0>( COLLADABU::Math::Vector3 const & v) { return v.x; }
    template<> v_traits<COLLADABU::Math::Vector3>::scalar_type v_traits<COLLADABU::Math::Vector3>::r<1>( COLLADABU::Math::Vector3 const & v) { return v.y; }
    template<> v_traits<COLLADABU::Math::Vector3>::scalar_type v_traits<COLLADABU::Math::Vector3>::r<2>( COLLADABU::Math::Vector3 const & v) { return v.z; }

    template<> struct q_traits<COLLADABU::Math::Quaternion> {
      typedef COLLADABU::Math::Real scalar_type;

      // I think that 0-3 is W, X, Y, Z...
      template <int I> static inline scalar_type & w( COLLADABU::Math::Quaternion & q );
      template <int I> static inline scalar_type   r( COLLADABU::Math::Quaternion const & q );
    };

    // specialize for each of W, X, Y, Z (not stored as vector in Ogre)
    template <> q_traits<COLLADABU::Math::Quaternion>::scalar_type & q_traits<COLLADABU::Math::Quaternion>::w<0>( COLLADABU::Math::Quaternion & q ) { return q.w; }
    template <> q_traits<COLLADABU::Math::Quaternion>::scalar_type & q_traits<COLLADABU::Math::Quaternion>::w<1>( COLLADABU::Math::Quaternion & q ) { return q.x; }
    template <> q_traits<COLLADABU::Math::Quaternion>::scalar_type & q_traits<COLLADABU::Math::Quaternion>::w<2>( COLLADABU::Math::Quaternion & q ) { return q.y; }
    template <> q_traits<COLLADABU::Math::Quaternion>::scalar_type & q_traits<COLLADABU::Math::Quaternion>::w<3>( COLLADABU::Math::Quaternion & q ) { return q.z; }

    template <> q_traits<COLLADABU::Math::Quaternion>::scalar_type q_traits<COLLADABU::Math::Quaternion>::r<0>( COLLADABU::Math::Quaternion const & q ) { return q.w; }
    template <> q_traits<COLLADABU::Math::Quaternion>::scalar_type q_traits<COLLADABU::Math::Quaternion>::r<1>( COLLADABU::Math::Quaternion const & q ) { return q.x; }
    template <> q_traits<COLLADABU::Math::Quaternion>::scalar_type q_traits<COLLADABU::Math::Quaternion>::r<2>( COLLADABU::Math::Quaternion const & q ) { return q.y; }
    template <> q_traits<COLLADABU::Math::Quaternion>::scalar_type q_traits<COLLADABU::Math::Quaternion>::r<3>( COLLADABU::Math::Quaternion const & q ) { return q.z; }

    // COLLADABU::Math::Matrix4 skipped.  No 
    template<> struct m_traits<COLLADABU::Math::Matrix4> {
      typedef COLLADABU::Math::Real scalar_type;
      static int const rows = 4;
      static int const cols = 4;

      // COLLADABU::Math::Matrix4 provides no special named access for individual entries
      template <int Row,int Col> static scalar_type r( COLLADABU::Math::Matrix4 const & x ) { return x[Row][Col]; }
      // sadly Collada does not provide non-const references to its matrix elements
      // this means some operations in QVM will fail...
      template <int Row,int Col> static scalar_type & w( COLLADABU::Math::Matrix4 & x ) { return x[Row][Col]; }
        
      static scalar_type ir( int row, int col, COLLADABU::Math::Matrix4 const & x ) { return x[row][col]; }
      // static scalar_type & iw( int row, int col, COLLADABU::Math::Matrix4 & x ) { return x[row][col]; }
    };

  }
}
