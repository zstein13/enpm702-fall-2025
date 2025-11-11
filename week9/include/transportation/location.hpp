#pragma once

#include <cmath>

namespace transportation
{

    /**
     * @class Location
     * @brief Represents a geographic coordinate
     */
    class Location
    {
    private:
        double latitude_;
        double longitude_;

    public:
        /**
         * @brief Construct a new Location object
         * @param lat Latitude coordinate
         * @param lon Longitude coordinate
         */
        Location(double lat, double lon) : latitude_(lat), longitude_(lon) {}

        /**
         * @brief Calculate distance to another location (simplified Euclidean distance)
         * @param other The other location
         * @return Distance in arbitrary units
         */
        double distance_to(const Location &other) const;

        /**
         * @brief Get latitude
         * @return Latitude value
         */
        [[nodiscard]] double get_latitude() const noexcept
        {
            return latitude_;
        }

        /**
         * @brief Get longitude
         * @return Longitude value
         */
        [[nodiscard]] double get_longitude() const noexcept
        {
            return longitude_;
        }
    }; // class Location

} // namespace transportation