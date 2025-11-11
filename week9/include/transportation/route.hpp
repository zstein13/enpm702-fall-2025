#pragma once

#include "location.hpp"
#include <string>
#include <vector>
#include <memory>

namespace transportation
{

    /**
     * @class Route
     * @brief Represents a navigation route with waypoints
     */
    class Route
    {
    private:
        std::string id_;
        std::vector<Location> waypoints_; // Route consists of Locations (association)

    public:
        /**
         * @brief Construct a new Route object
         * @param route_id Unique route identifier
         */
        Route(const std::string &route_id) : id_{route_id} {}

        /**
         * @brief Add a waypoint to the route
         * @param location Location to add as waypoint
         */
        void add_waypoint(const Location &location);

        /**
         * @brief Calculate total route distance
         * @return Total distance through all waypoints
         */
        double get_distance() const;

        /**
         * @brief Get number of waypoints
         * @return Waypoint count
         */
        size_t get_waypoint_count() const;
        
        /**
         * @brief Get all waypoints
         * @return Vector of waypoint locations
         */
        const std::vector<Location> &get_waypoints() const
        {
            return waypoints_;
        }

        /**
         * @brief Get route ID
         * @return Route identifier
         */
        std::string get_id() const
        {
            return id_;
        }
    };

} // namespace transportation