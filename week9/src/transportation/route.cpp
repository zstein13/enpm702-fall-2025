#include "route.hpp"

void transportation::Route::add_waypoint(const Location &location)
{
    waypoints_.push_back(location);
}

double transportation::Route::get_distance() const
{
    double total_distance{0.0};
    for (size_t i = 1; i < waypoints_.size(); ++i)
    {
        total_distance += waypoints_[i - 1].distance_to(waypoints_[i]);
    }
    return total_distance;
}

size_t transportation::Route::get_waypoint_count() const
{
    return waypoints_.size();
}