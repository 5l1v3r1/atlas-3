/*
 * (C) Copyright 1996-2016 ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#ifndef atlas_functionspace_functionspace__ReducedGridPoint_h
#define atlas_functionspace_functionspace__ReducedGridPoint_h

#include "atlas/atlas_defines.h"
#include "atlas/functionspace/FunctionSpace.h"

namespace atlas {
namespace util {
namespace parallel {
namespace mpl {
    class GatherScatter;
    class Checksum;
} } } }

namespace atlas {
namespace field {
    class Field;
    class FieldSet;
} }

namespace atlas {
namespace grid {
    class ReducedGrid;
} }

namespace atlas {
namespace numerics {
namespace trans {
    class Trans;
} } }

namespace atlas {
namespace functionspace {

// -------------------------------------------------------------------

class ReducedGridPoint : public FunctionSpace
{
public:

  ReducedGridPoint( const grid::Grid& );

  virtual ~ReducedGridPoint();

  virtual std::string name() const { return "ReducedGridPoint"; }

  /// @brief Create a ReducedGrid field
  template <typename DATATYPE> field::Field* createField(const std::string& name) const;
  template <typename DATATYPE> field::Field* createField(const std::string& name, size_t levels) const;

  /// @brief Create a global ReducedGrid field
  template <typename DATATYPE> field::Field* createGlobalField(const std::string& name) const;
  template <typename DATATYPE> field::Field* createGlobalField(const std::string& name, size_t levels) const;

  void gather( const field::FieldSet&, field::FieldSet& ) const;
  void gather( const field::Field&, field::Field& ) const;

  void scatter( const field::FieldSet&, field::FieldSet& ) const;
  void scatter( const field::Field&, field::Field& ) const;

  size_t npts() const            { return npts_; }
  size_t nlat() const            { return nlat_; }
  size_t nlon(size_t jlat) const { return nlon_[jlat]; }

  double lat(size_t jlat) const;
  double lon(size_t jlat, size_t jlon) const;

  std::string checksum( const field::FieldSet& ) const;
  std::string checksum( const field::Field& ) const;

  const grid::ReducedGrid& grid() const { return *grid_; }

private: // data

  size_t npts_;
  size_t nlat_;
  size_t first_lat_;
  std::vector<size_t> nlon_;
  std::vector<size_t> first_lon_;

  numerics::trans::Trans* trans_;
  const grid::ReducedGrid* grid_;
  util::parallel::mpl::GatherScatter* gather_scatter_;
  util::parallel::mpl::Checksum* checksum_;

};

// -------------------------------------------------------------------
// C wrapper interfaces to C++ routines
#define Char char
#define grid_Grid grid::Grid
#define field_Field field::Field
#define field_FieldSet field::FieldSet
extern "C"
{
  ReducedGridPoint* atlas__functionspace__ReducedGridPoint__new__grid (const grid_Grid* grid);
  void atlas__functionspace__ReducedGridPoint__delete (ReducedGridPoint* This);
  field_Field* atlas__functionspace__ReducedGridPoint__create_field (const ReducedGridPoint* This, const char* name);
  field_Field* atlas__functionspace__ReducedGridPoint__create_field_lev (const ReducedGridPoint* This, const char* name, int levels);
  field_Field* atlas__functionspace__ReducedGridPoint__create_gfield (const ReducedGridPoint* This, const char* name);
  field_Field* atlas__functionspace__ReducedGridPoint__create_gfield_lev (const ReducedGridPoint* This, const char* name, int levels);
  void atlas__functionspace__ReducedGridPoint__gather (const ReducedGridPoint* This, const field_Field* local, field_Field* global);
  void atlas__functionspace__ReducedGridPoint__scatter (const ReducedGridPoint* This, const field_Field* global, field_Field* local);
  void atlas__fs__ReducedGridPoint__checksum_fieldset(const ReducedGridPoint* This, const field_FieldSet* fieldset, Char* &checksum, int &size, int &allocated);
  void atlas__fs__ReducedGridPoint__checksum_field(const ReducedGridPoint* This, const field_Field* field, Char* &checksum, int &size, int &allocated);
}

#undef grid_Grid
#undef field_FieldSet
#undef field_Field
#undef Char


} // namespace functionspace
} // namespace atlas

#endif // atlas_functionspace_functionspace__ReducedGridPoint_h
