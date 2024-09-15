#include "FileController.h"
#include <drogon/HttpRequest.h>
#include <drogon/orm/Criteria.h>
#include <json/json.h>


using namespace drogon;

void FileController::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback){

    shared_ptr<Json::Value> *jsonPtr = req->getJsonObject();
    if(!jsonPtr){

    } 
    Json::Value requestBody = *jsonPtr;



}