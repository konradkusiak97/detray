/** Detray library, part of the ACTS project (R&D line)
 * 
 * (c) 2021 CERN for the benefit of the ACTS project
 * 
 * Mozilla Public License Version 2.0
 */

#include "core/track.hpp"
#include "core/transform_store.hpp"
#include "tools/line_stepper.hpp"
#include "tools/navigator.hpp"
#include "tools/propagator.hpp"
#include "io/csv_io.hpp"

#include <gtest/gtest.h>

/// @note __plugin has to be defined with a preprocessor command

// This tests the basic functionality of the propagator
TEST(__plugin, propagator)
{
    using namespace detray;
    using namespace __plugin;

    auto env_d_d = std::getenv("DETRAY_TEST_DATA_DIR");
    if (env_d_d == nullptr)
    {
        throw std::ios_base::failure("Test data directory not found. Please set DETRAY_TEST_DATA_DIR.");
    }
    auto data_directory = std::string(env_d_d);

    std::string surface_file = data_directory + std::string("tml.csv");
    std::string surface_grid_file = data_directory + std::string("tml-surface-grids.csv");
    std::string layer_volume_file = data_directory + std::string("tml-layer-volumes.csv");

    auto d = detector_from_csv<static_transform_store>("tml", surface_file, surface_grid_file, layer_volume_file);

    // Create the navigator
    using detray_navigator = navigator<decltype(d)>;    
    using detray_track = track<static_transform_store::context>;

    detray_track traj;
    traj.pos = {0., 0., 0.};
    traj.dir = vector::normalize(vector3{1., 1., 0.});
    traj.ctx = static_transform_store::context{};
    traj.momentum = 100.;
    traj.overstep_tolerance = -1e-4;

    using detray_stepper = line_stepper<detray_track>;

    detray_stepper s;
    detray_navigator n(std::move(d));

    using detray_propagator = propagator<detray_stepper,detray_navigator>;
    detray_propagator p(std::move(s), std::move(n));

    void_track_inspector vi;

    auto end = p.propagate(traj, vi);


}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
