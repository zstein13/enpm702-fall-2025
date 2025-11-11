#include "location.hpp"

double transportation::Location::distance_to(const Location &other) const
{
    // Haversine Formula
    const double R = 6371.0; // Earth radius in km

    double lat1_rad = latitude_ * M_PI / 180.0;
    double lat2_rad = other.latitude_ * M_PI / 180.0;
    double dlat_rad = (other.latitude_ - latitude_) * M_PI / 180.0;
    double dlon_rad = (other.longitude_ - longitude_) * M_PI / 180.0;

    double a = std::sin(dlat_rad / 2) * std::sin(dlat_rad / 2) +
               std::cos(lat1_rad) * std::cos(lat2_rad) *
                   std::sin(dlon_rad / 2) * std::sin(dlon_rad / 2);

    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));

    return R * c; // Distance in km
}