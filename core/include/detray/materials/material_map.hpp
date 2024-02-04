/** Detray library, part of the ACTS project (R&D line)
 *
 * (c) 2023-2024 CERN for the benefit of the ACTS project
 *
 * Mozilla Public License Version 2.0
 */

#pragma once

// Detray include(s)
#include "detray/definitions/containers.hpp"
#include "detray/materials/material_slab.hpp"
#include "detray/surface_finders/grid/detail/axis_helpers.hpp"
#include "detray/surface_finders/grid/detail/grid_bins.hpp"
#include "detray/surface_finders/grid/grid.hpp"
#include "detray/surface_finders/grid/serializers.hpp"
#include "detray/tools/grid_factory.hpp"

namespace detray {

/// Definition of binned material
template <typename shape, typename scalar_t,
          typename container_t = host_container_types, bool owning = false>
using material_map = grid<axes<shape>, bins::single<material_slab<scalar_t>>,
                          simple_serializer, container_t, owning>;

/// How to build material maps of various shapes
// TODO: Move to material_map_builder once available
template <typename scalar_t = detray::scalar>
using material_map_factory =
    grid_factory<bins::single<material_slab<scalar_t>>, simple_serializer>;

}  // namespace detray