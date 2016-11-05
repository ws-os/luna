---
layout: default
title: Luna
---

# Luna

## An embedded HTTP server in C++14

You are writing in C++ (because C++ is _awesome_), and your app needs to provide a lightweight HTTP server to communicate with other web services. `libmicrohttpd` is super-awesome, except for that idiomatically C API. Luna is an idiomatically C++ wrapper for `libmicrohttpd`.

Luna is designed to be easy to use. HTTP server creation, start, shut down, and deletion are all handled behind the scenes with the magic of [RAII](https://en.wikipedia.org/wiki/Resource_Acquisition_Is_Initialization). Starting a server is automatic with instantiating a `server` object, and allowing your `server` object to fall out of scope is all that is needed to cleanly shut it down. There is nothing else for you to keep track of, or allocate.

Adding endpoints to your server is likewise meant to be simple. Nominate an endpoint with a string or regex and an HTTP verb, and pass in a lambda or other `std::functional`-compatible object (function pointers, bound class member functions), and return a string containing the desired response body. Of course, you can set headers and mime types, too. (TODO: returning binary data.)

## Example code

But don't take my word for it. Here is some code for serving a simple JSON snippet from a single endpoint.

```
#include <string>
#include <luna/server.h>

using namespace luna;

int main(void)
{
    //start a server delivering JSON by default on the default port 8080
    server server{
        server::mime_type{"application/json"}, //the default is "text/html; charset=UTF-8"
    };

    // Handle GET requests to "localhost:8080/endpoint"
    // Respond with a tiny bit of fun JSON
    server.handle_response(request_method::GET, "/endpoint",
                           [](auto request) -> response
    {
        return {"{\"made_it\": true}"};
    });

    // idle while the server is running.
    // Totally not the best way.
    // But this is demo code!
    while (server);
}
```

## Prerequisites

A C++14 compiler (gcc 4.9, clang 3.6), cmake 2.8. [Conan](https://www.conan.io) for installing dev dependencies.

## License

[MIT](https://github.com/DEGoodmanWilson/luna/blob/master/LICENSE)

## Disclaimer

This library has only begun, and is a contant state of flux.