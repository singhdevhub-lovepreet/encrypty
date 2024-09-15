#pragma once

#include <drogon/HttpSimpleController.h>

using namespace drogon;

class FileController : public drogon::HttpSimpleController<FileController>{
    public:
        void asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) override;
        PATH_LIST_BEGIN;
        PATH_ADD("/upload", Post);
        PATH_LIST_END;
}