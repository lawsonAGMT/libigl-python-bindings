// TODO: __example

//difficult to test
#include <npe.h>
#include <typedefs.h>






#include <igl/boundary_conditions.h>

const char* ds_boundary_conditions = R"igl_Qu8mg5v7(

Compute boundary conditions for automatic weights computation. This
  function expects that the given mesh (V,Ele) has sufficient samples
  (vertices) exactly at point handle locations and exactly along bone and
  cage edges.

Parameters
----------
V  #V by dim list of domain vertices
Ele  #Ele by simplex-size list of simplex indices
C  #C by dim list of handle positions
P  #P by 1 list of point handle indices into C
BE  #BE by 2 list of bone edge indices into C
CE  #CE by 2 list of cage edge indices into *P*

Returns
-------
b  #b list of boundary indices (indices into V of vertices which have
  known, fixed values)
bc #b by #weights list of known/fixed values for boundary vertices
  (notice the #b != #weights in general because #b will include all the
  intermediary samples along each bone, etc.. The ordering of the
  weights corresponds to [P;BE]
Returns false if boundary conditions are suspicious:
  P and BE are empty
  bc is empty
  some column of bc doesn't have a 0 (assuming bc has >1 columns)
  some column of bc doesn't have a 1 (assuming bc has >1 columns)

See also
--------

Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(boundary_conditions)
npe_doc(ds_boundary_conditions)

npe_arg(v, dense_float, dense_double)
npe_arg(ele, dense_int, dense_long)
npe_arg(c, npe_matches(v))
npe_arg(p, npe_matches(ele))
npe_arg(be, npe_matches(ele))
npe_arg(ce, npe_matches(ele))


npe_begin_code()
  //TODO: remove __copy
  Eigen::MatrixXd v_copy = v.template cast<double>();
  Eigen::MatrixXi ele_copy = ele.template cast<int>();
  Eigen::MatrixXd c_copy = c.template cast<double>();
  Eigen::VectorXi p_copy = p.template cast<int>();
  Eigen::MatrixXi be_copy = be.template cast<int>();
  Eigen::MatrixXi ce_copy = ce.template cast<int>();
  Eigen::VectorXi b;
  Eigen::MatrixXd bc;
  bool success = igl::boundary_conditions(v_copy, ele_copy, c_copy, p_copy, be_copy, ce_copy, b, bc);
  return std::make_tuple(success, npe::move(b), npe::move(bc));

npe_end_code()


