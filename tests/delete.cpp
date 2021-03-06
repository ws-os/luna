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


#include <gtest/gtest.h>
#include <luna/luna.h>
#include <cpr/cpr.h>

TEST(delete, default_404)
{
    luna::server server;
    server.start_async();

    auto res = cpr::Delete(cpr::Url{"http://localhost:8080/"});
    ASSERT_EQ(404, res.status_code);
}

TEST(delete, default_200)
{
    luna::router router{"/"};
    router.handle_request(luna::request_method::DELETE,
                          "/test",
                          [](auto req) -> luna::response
                              {
                                  return {"hello"};
                              });

    luna::server server;
    server.add_router(router);
    server.start_async();

    auto res = cpr::Delete(cpr::Url{"http://localhost:8080/test"}, cpr::Parameters{});
    ASSERT_EQ(200, res.status_code);
    ASSERT_EQ("hello", res.text);
}