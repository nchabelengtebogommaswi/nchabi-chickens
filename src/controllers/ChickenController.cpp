#include "controllers/ChickenController.h"

#include <nlohmann/json.hpp>

using Json = nlohmann::json;

ChickenController::ChickenController(ChickenService& service): service(service)
{
}

void ChickenController::registerRoutes(httplib::Server& server)
{
    server.Get(
        "/api/chickens/tag",
        [this]
        (
            const httplib::Request& request,
            httplib::Response& response
        )
        {
            if (!request.has_param("tag"))
            {
                response.status = 400;
                response.set_content(
                    "Missing tag parameter",
                    "text/plain");

                return;
            }

            auto chicken =
                service.findByTagNumber(
                    request.get_param_value("tag"));

            if (!chicken)
            {
                response.status = 404;
                response.set_content(
                    "Chicken not found",
                    "text/plain");

                return;
            }

            Json chickenJson;

            chickenJson["id"] = chicken->id;
            chickenJson["tagNumber"] = chicken->tagNumber;
            chickenJson["breed"] = chicken->breed;
            chickenJson["gender"] = chicken->gender;
            chickenJson["hatchDate"] = chicken->hatchDate;
            chickenJson["purchaseDate"] = chicken->purchaseDate;
            chickenJson["weightKg"] = chicken->weightKg;
            chickenJson["status"] = chicken->status;
            chickenJson["pen"] = chicken->pen;
            chickenJson["notes"] = chicken->notes;
            chickenJson["createdAt"] = chicken->createdAt;
            chickenJson["updatedAt"] = chicken->updatedAt;

            response.set_content(
                chickenJson.dump(4),
                "application/json");
        });
}