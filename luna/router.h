//
//      _
//  ___/_)
// (, /      ,_   _
//   /   (_(_/ (_(_(_
// CX________________
//                   )
//
// Luna
// A web application and API framework in modern C++
//
// Copyright © 2016–2017 D.E. Goodman-Wilson
//

#pragma once

#include <luna/types.h>
#include <luna/config.h>
#include <luna/optional.hpp>
#include <regex>
#include <functional>

namespace luna
{

// Forward declaration for friendship
class server;

class router
{
public:
    router(std::string route_base = "/");

    void set_mime_type(std::string mime_type);

    using endpoint_handler_cb = std::function<response (const request &req)>;

    void handle_request(request_method method,
                        std::regex route,
                        endpoint_handler_cb callback,
                        parameter::validators validations = {});

    void handle_request(request_method method,
                        std::string route,
                        endpoint_handler_cb callback,
                        parameter::validators validations = {});

    void serve_files(std::string mount_point, std::string path_to_files);

    void add_header(std::string &&key, std::string &&value);

protected:
    // for use by the Server object
    friend ::luna::server;
    std::experimental::optional<luna::response> process_request(request &request);

private:
    class router_impl;
    std::shared_ptr<router_impl> impl_;
};


} //namespace luna