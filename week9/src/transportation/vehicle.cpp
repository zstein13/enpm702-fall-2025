#include "location.hpp"
#include "vehicle.hpp"
#include "vehicle_status.hpp"

void transportation::Vehicle::clear_route()
{
    route_ = nullptr;
    status_ = VehicleStatus::IDLE;
}

void transportation::Vehicle::update_location(const Location &location)
{
    current_location_ = location;
}

std::string transportation::Vehicle::vehicle_status_to_string(VehicleStatus status) const noexcept
{
    switch (status)
    {
    case VehicleStatus::IDLE:
        return "IDLE";
    case VehicleStatus::IN_SERVICE:
        return "IN_SERVICE";
    case VehicleStatus::EN_ROUTE:
        return "EN_ROUTE";
    case VehicleStatus::CHARGING:
        return "CHARGING";
    case VehicleStatus::MAINTENANCE:
        return "MAINTENANCE";
    case VehicleStatus::OUT_OF_SERVICE:
        return "OUT_OF_SERVICE";
    default:
        return "UNKNOWN";
    }
}