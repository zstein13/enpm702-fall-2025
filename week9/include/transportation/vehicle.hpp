#pragma once

#include "route.hpp"
#include "location.hpp"
#include "vehicle_status.hpp"
#include <string>
#include <memory>

namespace transportation
{

    /**
     * @class Vehicle
     * @brief Represents a vehicle that can follow a route
     */
    class Vehicle
    {
    private:
        std::string id_;
        Location current_location_;
        std::shared_ptr<Route> route_; // Vehicle follows Route (0..1 association)
        VehicleStatus status_{VehicleStatus::IDLE};

    public:
        /**
         * @brief Construct a new Vehicle object
         * @param vehicle_id Unique vehicle identifier
         * @param initial_location Starting location
         */
        Vehicle(const std::string &vehicle_id, const Location &initial_location)
            : id_{vehicle_id}, current_location_{initial_location}, route_{nullptr} {}

        /**
         * @brief Clear the current route
         */
        void clear_route();

        /**
         * @brief Update vehicle's current location
         * @param location New location
         */
        void update_location(const Location &location);

        /**
         * @brief Check if vehicle has a route assigned
         * @return True if route is assigned, false otherwise
         */
        [[nodiscard]] bool has_route() const noexcept
        {
            return route_ != nullptr;
        }

        // Getters and Setters
        /**
         * @brief Get the current route
         * @return Shared pointer to route, or nullptr if no route assigned
         */
        [[nodiscard]] std::shared_ptr<Route> get_route() const noexcept
        {
            return route_;
        }

        /**
         * @brief Get current location
         * @return Current vehicle location
         */
        [[nodiscard]] Location get_current_location() const noexcept
        {
            return current_location_;
        }

        /**
         * @brief Get vehicle ID
         * @return Vehicle identifier
         */
        [[nodiscard]] std::string get_id() const noexcept
        {
            return id_;
        }

        /**
         * @brief Get vehicle status
         * @return Current vehicle status
         */
        [[nodiscard]] VehicleStatus get_status() const noexcept
        {
            return status_;
        }

        std::string vehicle_status_to_string(VehicleStatus status) const noexcept;

        /**
         * @brief Set vehicle status
         * @param new_status New status to set
         */
        void set_status(VehicleStatus new_status) noexcept
        {
            status_ = new_status;
        }

        /**
         * @brief Set the route for the vehicle to follow
         * @param new_route Route to follow
         */
        void set_route(std::shared_ptr<Route> new_route)
        {
            route_ = new_route;
            if (new_route)
            {
                status_ = VehicleStatus::EN_ROUTE;
            }
        }
    }; // class Vehicle

} // namespace transportation