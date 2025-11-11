#include <iostream>
#include "location.hpp"
#include "route.hpp"
#include "vehicle.hpp"

int main()
{
    // testing Location class
    transportation::Location times_square(40.7580, -74.0060);
    transportation::Location central_park(40.7829, -73.9654);
    transportation::Location brooklyn_bridge(40.7061, -73.9969);
    transportation::Location jfk_airport(40.6413, -73.7781);
    std::cout << times_square.distance_to(central_park) << '\n';

    // testing Route class
    transportation::Route new_york_trip("NewYorkTrip");
    new_york_trip.add_waypoint(times_square);
    new_york_trip.add_waypoint(central_park);
    new_york_trip.add_waypoint(brooklyn_bridge);
    new_york_trip.add_waypoint(jfk_airport);
    std::cout << "Number of waypoints: " << new_york_trip.get_waypoint_count() << '\n';
    std::cout << "Trip distance: " << new_york_trip.get_distance() << " km" << '\n';

    // testing Vehicle class
    transportation::Vehicle waymo("waymo", times_square);
    std::cout << "Current latitude: " << waymo.get_current_location().get_latitude() << '\n';
    std::cout << "Current longitude: " << waymo.get_current_location().get_longitude() << '\n';
    std::cout << "Current status: " << waymo.vehicle_status_to_string(waymo.get_status()) << '\n';

}